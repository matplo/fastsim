#include "emctrig.h"

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

//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

#include "util.h"

int emctrig( int argc, char *argv[])
{
	Int_t 	 kCollider     = 1;
	Double_t gmultCollider = GenerUtil::gmultLHC;
	Int_t 	 gNbinCollider = GenerUtil::gNbinLHC;

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
	//double pTMin   = 1.0;    // Min jet pT.
	double pTMin   = 0.0;    // Min jet pT.
	double etaMax  = 1.1;    // Pseudorapidity range of detector.
	int    select  = 2;      // Which particles are included?
	int    massSet = 2;      // Which mass are they assumed to have? 2-self masses; 1-pions; 0-zero

	if (SysUtil::isSet("-R", argc, argv))
	{
		R = strtod(SysUtil::getArg("-R", argc, argv), 0);
	}
	cout << "[i] R parameter set to : " << R << endl;

	std::vector <fj::PseudoJet> py_hard_event; // signal from pythia
	std::vector <fj::PseudoJet> bg_event; // boltzman background
	std::vector <fj::PseudoJet> full_event; //signal+background

	TLorentzVector bgparticle;


	// PYTHIA INIT
	// Generator. Shorthand for event.
	py::Pythia pythia;
	py::Info& info = pythia.info;
	py::Event& event = pythia.event;

	// Read in commands from external file.
	pythia.readFile("emctrig.cmnd");

	// Extract settings to be used in the main program.
	int nEvent = pythia.mode("Main:numberOfEvents");
	int nAbort = pythia.mode("Main:timesAllowErrors");
	double minpThat = pythia.mode("PhaseSpace:pTHatMin");
	double maxpThat = pythia.mode("PhaseSpace:pTHatMax");

	pythia.init();

	//ROOT IO
	// for the root IO...
	TFile *fout = new TFile (outputFname.Data(), "RECREATE");
	fout->cd();
	// remember to create the ntuples and histograms within the file
	TNtuple *tnj_hard = new TNtuple("jets_hard", "jets_hard", "nEv:xsec:pT:eta:phi:lead:pTmatched:pTraw:area:rho:sigma");
	TNtuple *tnj_full = new TNtuple("jets_full", "jets_full", "nEv:xsec:pT:eta:phi:lead:pTmatched:pTraw:area:rho:sigma");
	TNtuple *tnp = new TNtuple("p", "p", "nEv:xsec:pT:eta:phi");

	double lead_pT    = 0;
	double matched_pT = 0;
	double matched_pT_tmp = 0;

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		clock_t befGen = clock();
		if (!pythia.next()) continue;
		clock_t aftGen = clock();

		double xsec = info.sigmaGen();

		tnj_hard->Fill(iEvent, xsec, -1, -9.9, -99, -1, -1, -1, -1, -1, -1);
		tnj_full->Fill(iEvent, xsec, -1, -9.9, -99, -1, -1, -1, -1, -1, -1);
		tnp->Fill(iEvent, xsec, -1, -9.9, -99);

		// Begin FastJet analysis: extract particles from event record.

		py_hard_event.resize(0);
		py::Vec4   pTemp;
		double mTemp;
		int nAnalyze = 0;

		double eta = 0;
		double phi = 0;
		double pt  = 0;

		for (int i = 0; i < event.size(); ++i)
		{
			if (event[i].isFinal())
			{

				// Require visible/charged particles inside detector.
				if      (select > 2 &&  event[i].isNeutral() ) continue;
				else if (select == 2 && !event[i].isVisible()) continue;
				if (etaMax < 20. && abs(event[i].eta()) > etaMax) continue;

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

		// first set the full event with the pythia event
		full_event = py_hard_event;

		// generate background particiles
		for (Int_t ibg = 0; ibg < gmultCollider; ibg++)
		{
			GenerUtil::bg_particle(kCollider, bgparticle);
			//cout << bgparticle.Pt() << endl;
			//if (bgparticle.Pt() < 0.1) continue;
			fj::PseudoJet ptmp( bgparticle.Px(), bgparticle.Py(),
			                    bgparticle.Pz(), bgparticle.E() );
			ptmp.set_user_index(GenerUtil::gpyParticleOffset + ibg);
			// particleTemp.reset_momentum( bgparticle.Px(), bgparticle.Py(),
			//           bgparticle.Pz(), bgparticle.E() );
			full_event.push_back(ptmp);
			// fill the ntuple for bg particles
			tnp->Fill(     -1, xsec, bgparticle.Pt(), bgparticle.Eta(), bgparticle.Phi() );
		}

		if (iEvent % 100 == 0)
		{
			cout << iEvent << ": bg gen time: " << endl;
		}

		// BACKGROUND AND SIGNAL IN THE BG+SIGNAL EVENTS
		// directly taken from the example (07) of fastjet

		double ghost_maxrap = etaMax; // this is the range of the detector

		// ------------ pure pythia
		fj::JetDefinition jet_def_hard(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
		fj::ClusterSequence clust_seq_hard(py_hard_event, jet_def_hard);
		vector <fj::PseudoJet> inclusive_jets_hard = clust_seq_hard.inclusive_jets(pTMin);
		vector <fj::PseudoJet> sorted_jets_hard    = fj::sorted_by_pt(inclusive_jets_hard);
		clock_t aftFast = clock();

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
					       full_jets[i].rap(), full_jets[i].phi(), full_jets[i].perp(),
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

		// get the subtracted jets
		vector<fj::PseudoJet> subtracted_jets_full = subtractor(full_jets);
		// ----------------------------------------------------
		//
		// at this point we have everything to fill the output!
		//
		// ----------------------------------------------------

		unsigned int idx = 0;
		// Fill inclusive FastJet jets from the pythia+bg event
		for (unsigned int i = 0; i < full_jets.size(); i++)
		{
			// re-apply the pt cut
			//if (subtracted_jets_full[i].perp2() >= pTMin*pTMin)
			if (1) // take any! jet - see what happens?
			{
				if (verbosity > 9)
				{
					printf("%5u %15.8f %15.8f %15.8f %15.8f %15.8f %15.8f %15.8f\n", idx,
					       full_jets[i].rap(), full_jets[i].phi(), full_jets[i].perp(),
					       full_jets[i].area(),
					       subtracted_jets_full[i].rap(), subtracted_jets_full[i].phi(),
					       subtracted_jets_full[i].perp());
				}

				vector<fj::PseudoJet> constituents = subtracted_jets_full[i].constituents();
				lead_pT = fj::SelectorNHardest(1)(constituents)[0].perp();
				matched_pT = 0;
				matched_pT_tmp = 0;
				for (int j = 0; j < int(sorted_jets_hard.size()); ++j)
				{
					matched_pT_tmp = GenerUtil::pt_matched(sorted_jets_hard[j], subtracted_jets_full[i]);
					if ((matched_pT_tmp > sorted_jets_hard[j].perp() / 2.) && (matched_pT_tmp > matched_pT))
					{
						matched_pT = sorted_jets_hard[j].perp();
					}
				}
				double area  = full_jets[i].area();
				double pTraw = full_jets[i].perp();

				pt  = sorted_jets_hard[i].perp();
				phi = full_jets[i].phi();
				eta = full_jets[i].eta();

				// note we do not use: - which are! different from inclusive!
				// subtracted_jets_full[i].perp(),
				// subtracted_jets_full[i].eta(),
				// subtracted_jets_full[i].phi(),

				if (subtracted_jets_full[i].perp2() <= pTMin * pTMin)
				{
					pt = 0.;
					//cout << subtracted_jets_full[i].eta() << " " << full_jets[i].eta() << endl;
				}

				tnj_full->Fill(     -1, xsec,
				                    pt, eta, phi,
				                    lead_pT, matched_pT,
				                    pTraw, area, rho, sigma);
				idx++;
			}
		}

		// Fill inclusive FastJet jet from the pythia event - hard event
		for (int i = 0; i < int(sorted_jets_hard.size()); ++i)
		{
			pt  = sorted_jets_hard[i].perp();
			phi = sorted_jets_hard[i].phi();
			eta = sorted_jets_hard[i].eta();

			vector<fj::PseudoJet> constituents = sorted_jets_hard[i].constituents();
			lead_pT = fj::SelectorNHardest(1)(constituents)[0].perp();
			matched_pT = 0;
			matched_pT_tmp = 0;
			double matched_area  = -1;
			double matched_pTraw = -1;
			for (int j = 0; j < int(subtracted_jets_full.size()); ++j)
			{
				matched_pT_tmp = GenerUtil::pt_matched(sorted_jets_hard[i], subtracted_jets_full[j]);
				if ((matched_pT_tmp > sorted_jets_hard[i].perp() / 2.) && (matched_pT_tmp > matched_pT))
				{
					matched_pT    = subtracted_jets_full[j].perp();
					matched_area  = full_jets[j].area();
					matched_pTraw = full_jets[j].perp();
				}
			}

			tnj_hard->Fill(     -1, xsec,
			                    pt, eta, phi,
			                    lead_pT, matched_pT,
			                    matched_pTraw, matched_area, rho, sigma);
		}

	} // end of event loop

	// Statistics. Histograms.
	pythia.stat();

	fout->Write();
	fout->Close();

	return 0;
}
