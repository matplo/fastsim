#include "emctrig_par.h"

#include <Pythia8/Pythia.h>

#include <Pythia8Plugins/FastJet3.h>

//#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"
#include "fastjet/tools/JetMedianBackgroundEstimator.hh"
#include "fastjet/tools/Subtractor.hh"

#include <iostream> // needed for io
using namespace std;

//using namespace fastjet; - conflicts with root
namespace fj = fastjet;

// this is for root output
#include <TFile.h>
#include <TNtuple.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TF1.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TSystem.h>

//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

#include "util.h"
#include <AliGenFastModelingEvent.h>

#include <TriggerMaker.h>

#include <EMPartResp.h>

#include "revent.h"

int emctrig_par_revent( int argc, char *argv[])
{
	cout << "[i] This is emctrig_par ." << endl;
	int verbosity = 0;
	verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	TString outputFname = SysUtil::getArg("-out", argc, argv);
	if (outputFname.Length() == 0)
	{
		outputFname = "default_emctrig_out.root";
	}
	cout << "[i] Output file: " << outputFname.Data() << endl;

	// Select common parameters FastJet analyses.
	int    power   = -1;     // -1 = anti-kT; 0 = C/A; 1 = kT.
	double R       = 0.4;    // Jet size.
	double pTMin   = 0.0;    // Min jet pT.
	double etaMax  = 1.1;    // Pseudorapidity range of detector.
	int    select  = 2;      // Which particles are included?
	int    massSet = 2;      // Which mass are they assumed to have? 2-self masses; 1-pions; 0-zero

	if (SysUtil::isSet("-R", argc, argv))
	{
		R = strtod(SysUtil::getArg("-R", argc, argv), 0);
	}
	cout << "[i] R parameter set to : " << R << endl;
	outputFname.ReplaceAll(".root", TString::Format("_R_%1.1f.root", R));

	Double_t EMCalTotal2EMfactor = 1.0;
	if (SysUtil::isSet("--femc", argc, argv))
	{
		EMCalTotal2EMfactor = strtod(SysUtil::getArg("--femc", argc, argv), 0);
		cout << "[i] EMCalTotal2EMfactor set to : " << EMCalTotal2EMfactor << endl;
		outputFname.ReplaceAll(".root", TString::Format("_femc_%1.1f.root", EMCalTotal2EMfactor));
	}

	TString EMCparPIDfile = "";
	EMPartResp *EMCresponse = 0;
	if (SysUtil::isSet("--femcpar", argc, argv))
	{
		EMCparPIDfile = SysUtil::getArg("--femcpar", argc, argv);
		if (gSystem->IsAbsoluteFileName(EMCparPIDfile))
		{
			cout << "[i] EMCparPIDfile set to: " << EMCparPIDfile << endl;
		}
		else
		{
			EMCparPIDfile = gSystem->ExpandPathName("$RUN2EMCTRIGGER/EMCpidPar/files/EMPartResp.root");
			cout << "[i] EMCparPIDfile reset to: " << EMCparPIDfile << endl;
		}
		EMCresponse = new EMPartResp(EMCparPIDfile.Data());
		outputFname.ReplaceAll(".root", "_femcpar.root");
	}

	if (SysUtil::isSet("--femc", argc, argv) && SysUtil::isSet("--femcpar", argc, argv))
	{
		cerr << "[e] only one --femc or --femcpar allowed" << endl;
		return 1;
	}

	Bool_t boltzmanBG = kTRUE;
	if (SysUtil::isSet("--realbg", argc, argv))
	{
		boltzmanBG = kFALSE;
	}
	if (boltzmanBG)
	{
		cout << "[i] boltzman background: " << boltzmanBG << endl;
	}
	else
	{
		cout << "[i] real data background: " << !boltzmanBG << endl;
	}

	AliGenFastModelingEvent *pResp = GenerUtil::make_par_background(0, 100, "$RUN2EMCTRIGGER/AliGenFME/inputs", boltzmanBG);
	if (pResp == 0)
	{
		cerr << "[e] Response not initialized. Quit here." << endl;
		return 1;
	}

	// PYTHIA INIT
	// Generator. Shorthand for event.
	py::Pythia pythia;
	py::Info& info   = pythia.info;
	py::Event& event = pythia.event;

	// Read in commands from external file.
	pythia.readFile("emctrig.cmnd");

	// Extract settings to be used in the main program.
	int nEvent      = pythia.mode("Main:numberOfEvents");
	int nAbort      = pythia.mode("Main:timesAllowErrors");
	double minpThat = pythia.mode("PhaseSpace:pTHatMin");
	double maxpThat = pythia.mode("PhaseSpace:pTHatMax");

	int nEventUser = atoi(SysUtil::getArg("--nev", argc, argv));
	if (nEventUser > 0)
	{
		nEvent = nEventUser;
	}

	cout << "[i] Run for " << nEvent << " events." << endl;

	bool cutHardMidRap = SysUtil::isSet("--hardeta", argc, argv);
	cout << "[i] Cut hard eta: " << cutHardMidRap << endl;

	pythia.init();

	//ROOT IO
	// for the root IO...
	REvent revent;
	revent.Init("tree_output.root");

	TFile *fout = new TFile (outputFname.Data(), "RECREATE");
	fout->cd();

	// remember to create the ntuples and histograms within the file
	TH1F *thnef             = new TH1F("thnef", "thnef;NEF;counts", 100, 0, 1);
	TH1F *thnefw            = new TH1F("thnefw", "thnefw;NEF;counts x xsec", 100, 0, 1);
	TH2F *hbgcl				= new TH2F("hbgcl", "hbgcl;#eta;#phi", 100, -1, 1, 360, 0, TMath::Pi() * 2.);
	TH2F *hcentmult			= new TH2F("hcentmult", "hcentmult;cent;mult", 100, 0, 100, 5000, 0, 5000);
	TH2F *heop              = new TH2F("heop", "heop;p;E/p", 100, 0, 100, 10, 0, 10);

	double lead_pT        = 0;
	double matched_pT     = 0;
	double matched_pT_tmp = 0;

	TriggerMappingEmcalSimple emcalmapping;
	int nRejectedEvents = 0;

	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia
	std::vector <fj::PseudoJet> bg_event_all; // boltzman background
	std::vector <fj::PseudoJet> bg_event_tracks; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters_ecal; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters_dcal; // boltzman background
	std::vector <fj::PseudoJet> full_event; //signal+background

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		clock_t befGen = clock();
		if (!pythia.next()) continue;
		clock_t aftGen = clock();

		double xsec = info.sigmaGen();

		if (cutHardMidRap == true)
		{
			if ( fabs(event[5].eta()) > 1.2 && fabs(event[6].eta()) > 1.2 )
			{
				//iEvent--;
				nRejectedEvents++;
				continue;
			}
		}

		if (iEvent % 100 == 0)
		{
			cout << "[info] event #" << iEvent << " rejected #" << nRejectedEvents << endl;
		}

		// Begin FastJet analysis: extract particles from event record.
		py_hard_event.clear(); // signal from pythia
		bg_event_all.clear(); // boltzman background
		bg_event_tracks.clear(); // boltzman background
		bg_event_clusters.clear(); // boltzman background
		bg_event_clusters_ecal.clear(); // boltzman background
		bg_event_clusters_dcal.clear(); // boltzman background
		full_event.clear(); //signal+background

		py::Vec4   pTemp;
		double mTemp;
		int nAnalyze = 0;

		double eta = 0;
		double phi = 0;
		double pt  = 0;

		unsigned int ncharged = 0;
		unsigned int nneutral = 0;

		for (int i = 0; i < event.size(); ++i)
		{
			if (event[i].isFinal())
			{

				// Require visible/charged particles inside detector.
				//if      (select > 2 &&  event[i].isNeutral() ) continue;
				//else if (select == 2 && !event[i].isVisible()) continue;
				//if (!event[i].isNeutral() || !event[i].isCharged()) continue;

				if (etaMax < 20. && abs(event[i].eta()) > etaMax) continue;
				if (!event[i].isVisible()) continue;

				if (event[i].isCharged()) ncharged++;
				if (event[i].isNeutral()) nneutral++;

				pt  = event[i].pT();
				phi = event[i].phi();
				eta = event[i].eta();

				// Create a PseudoJet from the complete Pythia particle.
				fj::PseudoJet particleTemp = event[i];
				particleTemp.set_user_index(i);

				// Optionally modify mass and energy.
				pTemp = event[i].p();
				mTemp = event[i].m();
				if (massSet < 2)
				{
					mTemp = (massSet == 0 || event[i].id() == 22) ? 0. : 0.13957;
					pTemp.e( sqrt(pTemp.pAbs2() + mTemp * mTemp) );
					particleTemp.reset_momentum( pTemp.px(), pTemp.py(),
					                             pTemp.pz(), pTemp.e() );
				}

				// Store acceptable particles as input to Fastjet.
				// Conversion to PseudoJet is performed automatically
				// with the help of the code in FastJet3.h.
				py_hard_event.push_back( particleTemp );
				++nAnalyze;
			} // for the final particles
		}// end particle loop within the event

		thnef->Fill(1.* nneutral / py_hard_event.size());
		thnefw->Fill(1.* nneutral / py_hard_event.size(), xsec);

		if (verbosity > 6)
		{
			cout << "[i] charged/all: " << ncharged << "/" << py_hard_event.size() << "=" << 1.* ncharged / py_hard_event.size()
			     << " neutral/all: " << nneutral << "/" << py_hard_event.size() << "=" << 1.* nneutral / py_hard_event.size() << endl;
		}

		// generate background particiles
		Double_t centRandom = gRandom->Rndm() * 99.;
		pResp->SetCentralityRange(centRandom, centRandom + 1.);

		if (!pResp->InitEvent())
		{
			cerr << "[e] ::InitEvent failed." << endl;
			return 1;
		}

		Double_t bg_event_centrality = pResp->GetCentrality();

		bg_event_tracks        = GenerUtil::param_vectors(pResp, GenerUtil::kTrack);
		bg_event_clusters_ecal = GenerUtil::param_vectors(pResp, GenerUtil::kCluster);
		bg_event_all           = GenerUtil::param_vectors(pResp, GenerUtil::kAny);

		// now for DCal
		if (!pResp->InitEvent())
		{
			cerr << "[e] ::InitEvent failed." << endl;
			return 1;
		}
		bg_event_clusters_dcal = GenerUtil::param_vectors(pResp, GenerUtil::kCluster);

		GenerUtil::add_particles(bg_event_clusters, bg_event_clusters_ecal, 0);
		GenerUtil::add_particles(bg_event_clusters, bg_event_clusters_dcal, 2.8);

		if (verbosity > 7)
		{
			cout << "[i] bg event centrality: " << bg_event_centrality << endl;
			cout << "    number of            clusters in bg_event ECAL : " << bg_event_clusters_ecal.size() << endl;
			cout << "    number of tracks              in bg_event      : " << bg_event_tracks.size() << endl;
			cout << "    number of tracks and clusters in bg_event      : " << bg_event_all.size() << endl;
			cout << "    number of tracks and clusters in bg_event DCAL : " << bg_event_clusters_dcal.size() << endl;
			cout << "    number of tracks and clusters in bg_event E+DC : " << bg_event_clusters.size() << endl;
		}

		hcentmult->Fill(bg_event_centrality, bg_event_tracks.size());

		// first set the full event with the pythia event
		full_event = py_hard_event;
		for (unsigned int ibg = 0; ibg < bg_event_tracks.size(); ibg++)
		{
			fj::PseudoJet v = bg_event_tracks[ibg];
			v.set_user_index(GenerUtil::gpyParticleOffset + ibg);
			full_event.push_back(v); //adding only charged tracks to the jet
		}

		if (verbosity > 7)
		{
			cout << "[i] number of particles in hard event: " << py_hard_event.size() << endl;
			cout << "[i] number of particles in bg   event: " << full_event.size() << endl;
		}

		// BACKGROUND AND SIGNAL IN THE BG+SIGNAL EVENTS
		// directly taken from the example (07) of fastjet

		double ghost_maxrap = etaMax; // this is the range of the detector

		// ------------ pure pythia
		fj::JetDefinition jet_def_hard(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
		fj::ClusterSequence clust_seq_hard(py_hard_event, jet_def_hard);
		vector <fj::PseudoJet> inclusive_jets_hard = clust_seq_hard.inclusive_jets(pTMin);
		vector <fj::PseudoJet> sorted_jets_hard    = fj::sorted_by_pt(inclusive_jets_hard);

		// ------------- now with background
		fj::JetDefinition jet_def_full(fj::antikt_algorithm, R);
		fj::GhostedAreaSpec area_spec(ghost_maxrap);
		fj::AreaDefinition area_def_full(fj::active_area, area_spec);
		fj::ClusterSequenceArea clust_seq_full(full_event, jet_def_full, area_def_full);
		vector<fj::PseudoJet> full_jets = fj::sorted_by_pt(clust_seq_full.inclusive_jets(pTMin));

		// Run the fastjet background estimation - kT
		fj::JetDefinition jet_def_bkgd(fj::kt_algorithm, R);
		fj::AreaDefinition area_def_bkgd(fj::active_area_explicit_ghosts,
		                                 fj::GhostedAreaSpec(ghost_maxrap));
		fj::Selector selector = fj::SelectorAbsRapMax(ghost_maxrap) * (!fj::SelectorNHardest(2));
		fj::JetMedianBackgroundEstimator bkgd_estimator(selector, jet_def_bkgd, area_def_bkgd);

		// ----------------------------------------------------------
		fj::Subtractor subtractor(&bkgd_estimator);
		subtractor.set_use_rho_m(true);

		// ----------------------------------------------------------
		bkgd_estimator.set_particles(full_event);
		double rho   = bkgd_estimator.rho();
		double sigma = bkgd_estimator.sigma();

		// get the subtracted jets
		vector<fj::PseudoJet> subtracted_jets_full = subtractor(full_jets);

		if (verbosity > 7)
		{
			double particle_maxrap = etaMax;

			cout << "Main clustering:" << endl;
			cout << "  Ran:   " << jet_def_full.description() << endl;
			cout << "  Area:  " << area_def_full.description() << endl;
			cout << "  Particles up to |y|=" << particle_maxrap << endl;
			cout << endl;

			cout << "Background estimation:" << endl;
			cout << "  " << bkgd_estimator.description() << endl << endl;;
			cout << "  Giving, for the full event" << endl;
			cout << "    rho   = " << bkgd_estimator.rho()   << endl;
			cout << "    sigma = " << bkgd_estimator.sigma() << endl;
			cout << endl;
		}

		// run the trigger algorithms

		TriggerSetup tsetup;
		tsetup.SetThresholds(0., 0., 0., 0.);
		tsetup.SetTriggerBitConfig(TriggerBitConfigNew());

		TriggerMaker tm;
		tm.SetTriggerSetup(tsetup);
		for (unsigned int ip = 0; ip < py_hard_event.size(); ip++)
		{
			if (emcalmapping.IsEMCAL(py_hard_event[ip].eta(), py_hard_event[ip].phi_02pi()) ||
			        emcalmapping.IsDCALPHOS(py_hard_event[ip].eta(), py_hard_event[ip].phi_02pi()) )
			{
				//tm.FillChannelMap(full_event[ip].eta(), full_event[ip].phi_02pi(), full_event[ip].e());
				unsigned int pyidx = py_hard_event[ip].user_index();
				Double_t emc = 0;
				if ( event[pyidx].isCharged() )
				{
					int ipid = event[pyidx].id();
					TVector3 pvector(py_hard_event[ip].px(), py_hard_event[ip].py(), py_hard_event[ip].pz());
					if (EMCresponse != 0)
					{
						// use the parametrized response
						emc = pvector.Mag() * EMCresponse->GetEop(ipid, pvector.Mag());
					}
					else
					{
						if ( ipid == 11 || ipid == -11)
						{
							// electrons are special
							emc = py_hard_event[ip].e();
						}
						else
						{
							// constant fraction of momentum
							emc = pvector.Mag() * EMCalTotal2EMfactor;
						}
					}
					heop->Fill(pvector.Mag(), emc);
				}
				else
				{
					// neutral particles deposit full energy
					emc = py_hard_event[ip].e();
				}
				tm.FillChannelMap(py_hard_event[ip].eta(), py_hard_event[ip].phi_02pi(), emc);
			}
		}

		TriggerSetup tsetup_bg;
		tsetup_bg.SetThresholds(0., 0., 0., 0.);
		tsetup_bg.SetTriggerBitConfig(TriggerBitConfigNew());

		TriggerMaker tm_bg;
		tm_bg.SetTriggerSetup(tsetup_bg);

		unsigned int npartbg   = bg_event_clusters.size();
		for (unsigned int ip = 0; ip < npartbg; ip++)
		{
			if (emcalmapping.IsEMCAL(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi()) ||
			        emcalmapping.IsDCALPHOS(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi()) )
			{
				tm.FillChannelMap(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].e());
				tm_bg.FillChannelMap(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].e());
				hbgcl->Fill(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].e());
			}
		}

		if (verbosity > 8)
		{
			std::cout << "gam emcal max: " << tm.GetMaxGammaEMCAL().GetADC() 	<< std::endl;
			std::cout << "gam  dcal max: " << tm.GetMaxGammaDCALPHOS().GetADC() << std::endl;
			std::cout << "jet emcal max: " << tm.GetMaxJetEMCAL().GetADC() 		<< std::endl;
			std::cout << "jet  dcal max: " << tm.GetMaxJetDCALPHOS().GetADC() 	<< std::endl;

			std::cout << "gam emcal median: " << tm.GetMedianGammaEMCAL() 		<< std::endl;
			std::cout << "gam  dcal median: " << tm.GetMedianGammaDCALPHOS() 	<< std::endl;
			std::cout << "jet emcal median: " << tm.GetMedianJetEMCAL() 		<< std::endl;
			std::cout << "jet  dcal median: " << tm.GetMedianJetDCALPHOS() 		<< std::endl;

			double pgaA =  4 *  4 * 0.014 * 0.014;
			double pjeA = 32 * 32 * 0.014 * 0.014;

			std::cout << "per unit area... ga: " << pgaA << " je: " << pjeA << std::endl;
			std::cout << "gam emcal median: " << tm.GetMedianGammaEMCAL() 		/ pgaA << std::endl;
			std::cout << "gam  dcal median: " << tm.GetMedianGammaDCALPHOS() 	/ pgaA << std::endl;
			std::cout << "jet emcal median: " << tm.GetMedianJetEMCAL() 		/ pjeA << std::endl;
			std::cout << "jet  dcal median: " << tm.GetMedianJetDCALPHOS() 		/ pjeA << std::endl;

			std::cout << "background only: " << std::endl;
			std::cout << "gam emcal max: " << tm_bg.GetMaxGammaEMCAL().GetADC() 	<< std::endl;
			std::cout << "gam  dcal max: " << tm_bg.GetMaxGammaDCALPHOS().GetADC()  << std::endl;
			std::cout << "jet emcal max: " << tm_bg.GetMaxJetEMCAL().GetADC() 		<< std::endl;
			std::cout << "jet  dcal max: " << tm_bg.GetMaxJetDCALPHOS().GetADC() 	<< std::endl;

			std::cout << "gam emcal median: " << tm_bg.GetMedianGammaEMCAL() 		<< std::endl;
			std::cout << "gam  dcal median: " << tm_bg.GetMedianGammaDCALPHOS() 	<< std::endl;
			std::cout << "jet emcal median: " << tm_bg.GetMedianJetEMCAL() 			<< std::endl;
			std::cout << "jet  dcal median: " << tm_bg.GetMedianJetDCALPHOS() 		<< std::endl;

		}

		//("triggers", "triggers", "nEv:xsec:
		//maxjECAL:maxjDCAL:maxgECAL:maxgDCAL:
		//medjECAL:medjDCAL:medgECAL:medgDCAL");
		tm.FindPatches();
		tm_bg.FindPatches();

		std::vector <fj::PseudoJet> ej;
		std::vector <fj::PseudoJet> dj;		
		for (unsigned int i = 0; i < sorted_jets_hard.size(); i++)
		{
			phi = sorted_jets_hard[i].phi_02pi();
			eta = sorted_jets_hard[i].eta();
			if (emcalmapping.IsEMCAL(eta, phi))
				ej.push_back(sorted_jets_hard[i]);
			if (emcalmapping.IsDCALPHOS(eta, phi))
				dj.push_back(sorted_jets_hard[i]);
		}

		// PHOTONS
		vector<fj::PseudoJet> photons;
		if (info.code() > 200)
		{
			for (int ig = 5; ig <= 6; ig++)
			{
				if (event[ig].id() == 22)
				{
					fj::PseudoJet particleTemp = event[ig];
					photons.push_back(particleTemp);
				}
			}
		}

		std::vector <fj::PseudoJet> eg;
		std::vector <fj::PseudoJet> dg;		
		for (unsigned int i = 0; i < photons.size(); i++)
		{
			phi = photons[i].phi_02pi();
			eta = photons[i].eta();
			if (emcalmapping.IsEMCAL(eta, phi))
				eg.push_back(photons[i]);
			if (emcalmapping.IsDCALPHOS(eta, phi))
				dg.push_back(photons[i]);
		}

		// END PHOTONS


		if (verbosity > 8)
		{
			cout << "Full Event: Jets above " << pTMin << " GeV in the hard event (" << full_event.size() << " particles)" << endl;
			cout << "---------------------------------------\n";
			printf("%5s %15s %15s %15s %15s\n", "jet #", "rapidity", "phi", "pt", "area");
			if (verbosity > 9)
			{
				for (unsigned int i = 0; i < full_jets.size(); i++)
				{
					printf("%5u %15.8f %15.8f %15.8f %15.8f\n", i,
					       full_jets[i].rap(), full_jets[i].phi_02pi(), full_jets[i].perp(),
					       full_jets[i].area());
				}
			}
			cout << endl;
		}

		// Once the background properties have been computed, subtraction
		// can be applied on the jets. Subtraction is performed on the
		// full 4-vector
		//
		// We output the jets before and after subtraction
		// ----------------------------------------------------------
		if (verbosity > 8)
		{
			cout << "Full Event: Jets above " << pTMin << " GeV in the full event (" << full_event.size() << " particles)" << endl;
			cout << "---------------------------------------\n";
			printf("%5s %15s %15s %15s %15s %15s %15s %15s\n", "jet #", "rapidity", "phi", "pt", "area", "rap_sub", "phi_sub", "pt_sub");
		}

		// ----------------------------------------------------
		//
		// at this point we have everything to fill the output!
		//
		// ----------------------------------------------------

		Header head;
		head.rho   = bkgd_estimator.rho();
		head.sigma = bkgd_estimator.sigma();

		revent.SetPythia(&pythia);
		revent.SetBackground(pResp);
		revent.SetEMCresponse(EMCresponse);
		revent.FillHeader("hd", &head);

		revent.FillBranch("p",  py_hard_event);
		revent.FillBranch("bgcl", bg_event_clusters);
		revent.FillBranch("bgtrk", bg_event_tracks);

		revent.FillTrigger("tg", &tm);
		revent.FillTrigger("tgbg", &tm_bg);

		revent.FillBranch("j",  sorted_jets_hard);
		revent.FillBranch("jf", full_jets);
		revent.FillBranch("jE", ej);
		revent.FillBranch("jD", dj);

		revent.FillBranch("g",  photons);
		revent.FillBranch("gE", eg);
		revent.FillBranch("gD", dg);

		revent.FinishEvent();
	} // end of event loop

	// Statistics. Histograms.
	pythia.stat();

	fout->Write();
	fout->Close();

	revent.Write();
	//delete EMCresponse;

	return 0;
}
