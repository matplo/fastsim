#include "emctrig_test.h"

#include <iostream> // needed for io
using namespace std;

#include <fastjet/PseudoJet.hh>
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

#include "util.h"
#include <AliGenFastModelingEvent.h>
#include <TriggerMaker.h>
#include <EMPartResp.h>
#include <r2util.h>
#include "revent.h"

int emctrig_test( int argc, char *argv[])
{
	gSystem->Load("libR2Util"); // this is needed on ubuntu but not on mac os x (?)
	cout << "[i] This is emctrig_test ." << endl;
	int verbosity = 0;
	verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	TString outputFname = SysUtil::getArg("--out", argc, argv);
	if (outputFname.Length() == 0)
	{
		outputFname = "default_emctrig_test_out.root";
	}
	cout << "[i] Output file: " << outputFname.Data() << endl;

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

	Double_t multTune = 1.;
	if (SysUtil::isSet("--mtune", argc, argv))
	{
		multTune = SysUtil::getArgD("--mtune", argc, argv, 1.);
		if (multTune != 1.)
		{
			outputFname.ReplaceAll(".root", TString::Format("_mtune_%1.1f.root", multTune));
		}
	}
	cout << "[i] tune multiplicity factor: " << multTune << endl;

	TString sPathFME = "$RUN2EMCTRIGGER/AliGenFME/inputs";
	AliGenFastModelingEvent *pFME = GenerUtil::make_par_background(0, 100, sPathFME, boltzmanBG);
	if (pFME == 0)
	{
		cerr << "[e] Response not initialized. Quit here." << endl;
		return 1;
	}
	if (multTune != 1.0)
	{
		pFME->SetTuneMeanPt(multTune);
		pFME->SetTuneMult(multTune);
	}

	int nEvent      = 1000;
	int nEventUser = atoi(SysUtil::getArg("--nev", argc, argv));
	if (nEventUser > 0)
	{
		nEvent = nEventUser;
	}

	cout << "[i] Run for " << nEvent << " events." << endl;

	//ROOT IO
	REvent revent;
	TString outputFnameTree = "tree-";
	outputFnameTree += outputFname;
	revent.Init(outputFnameTree.Data());

	TFile *fout = new TFile (outputFname.Data(), "RECREATE");
	fout->cd();

	// remember to create the ntuples and histograms within the file
	TH2F *hbgcl				= new TH2F("hbgcl", "hbgcl;#eta;#phi", 100, -1, 1, 360, 0, TMath::Pi() * 2.);
	TH2F *hcentmult			= new TH2F("hcentmult", "hcentmult;cent;mult", 100, 0, 100, 5000, 0, 5000);

	TH2F *hgenBGecal		= new TH2F("hgenBGecal", "hgenBGecal;centrality;N_{gen}", 100, 0, 100, 100, 0, 2500);
	TH2F *hgenBGdcal		= new TH2F("hgenBGdcal", "hgenBGecal;centrality;N_{gen}", 100, 0, 100, 100, 0, 2500);

	TH2F *haccBGecal		= new TH2F("haccBGecal", "haccBGecal;centrality;N_{acc}/N_{gen}", 100, 0, 100, 100, 0, 1);
	TH2F *haccBGdcal		= new TH2F("haccBGdcal", "haccBGdcal;centrality;N_{acc}/N_{gen}", 100, 0, 100, 100, 0, 1);

	TH2F *hphietacl			= new TH2F("hphietacl", 	"hphietacl", 	3600, 0, TMath::Pi() * 2., 2000, -1, 1);
	TH2F *hphietaclT		= new TH2F("hphietaclT", 	"hphietaclT", 	3600, 0, TMath::Pi() * 2., 2000, -1, 1);

	TH2F *hEcl 				= new TH2F("hEcl", "hEcl;centrality;Energy", 10	, 0, 100, 100, 0, 10);

	TriggerMappingEmcalSimple emcalmapping;
	int nRejectedEvents = 0;

	std::vector <fj::PseudoJet> bg_event_all; // boltzman background
	std::vector <fj::PseudoJet> bg_event_tracks; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters_ecal; // boltzman background
	std::vector <fj::PseudoJet> bg_event_clusters_dcal; // boltzman background

	std::vector <fj::PseudoJet> bg_event_clusters_dcal_rot; // boltzman background

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		double xsec = 1.0;
		if (iEvent % 100 == 0)
		{
			cout << "[info] event #" << iEvent << " rejected #" << nRejectedEvents << endl;
		}

		// Begin FastJet analysis: extract particles from event record.
		bg_event_all.clear(); // boltzman background
		bg_event_tracks.clear(); // boltzman background
		bg_event_clusters.clear(); // boltzman background
		bg_event_clusters_ecal.clear(); // boltzman background
		bg_event_clusters_dcal.clear(); // boltzman background
		bg_event_clusters_dcal_rot.clear(); // boltzman background

		py::Vec4   pTemp;
		double mTemp;
		int nAnalyze = 0;

		double eta = 0;
		double phi = 0;
		double pt  = 0;

		unsigned int ncharged = 0;
		unsigned int nneutral = 0;

		// generate background particiles
		Double_t centRandom = gRandom->Rndm() * 99.;
		pFME->SetCentralityRange(centRandom, centRandom + 1.);

		if (!pFME->InitEvent())
		{
			// we do this here just to get the multiplicity
			cerr << "[e] ::InitEvent failed." << endl;
			return 1;
		}

		Double_t bg_event_centrality = pFME->GetCentrality();

		bg_event_tracks        = GenerUtil::param_vectors(pFME, GenerUtil::kTrack);
		bg_event_clusters_ecal = GenerUtil::param_vectors(pFME, GenerUtil::kCluster);
		bg_event_all           = GenerUtil::param_vectors(pFME, GenerUtil::kAny);

		// now for DCal
		if (!pFME->InitEvent())
		{
			cerr << "[e] ::InitEvent failed." << endl;
			//return 1;
			continue;
		}
		bg_event_clusters_dcal = GenerUtil::param_vectors(pFME, GenerUtil::kCluster);

		GenerUtil::add_particles(bg_event_clusters, bg_event_clusters_ecal, 0);
		GenerUtil::add_particles(bg_event_clusters, bg_event_clusters_dcal, 2.8); //3.1416); //rotate in phi by 2.8 rad
		GenerUtil::add_particles(bg_event_clusters_dcal_rot, bg_event_clusters_dcal, 2.8); //3.1416); //rotate in phi by 2.8 rad

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

		// run the trigger algorithms

		TriggerSetup tsetup;
		tsetup.SetThresholds(0., 0., 0., 0.);
		tsetup.SetTriggerBitConfig(TriggerBitConfigNew());

		TriggerMaker tm;
		tm.SetTriggerSetup(tsetup);

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
				//hbgcl->Fill(bg_event_clusters[ip].eta(), bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].e());
				hphietaclT->Fill(bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].eta());
			}
			hphietacl->Fill(bg_event_clusters[ip].phi_02pi(), bg_event_clusters[ip].eta());
		}

		double acceptedBGecal = 0;
		double acceptedBGdcal = 0;

		for (unsigned int ip = 0; ip < bg_event_clusters_ecal.size(); ip++)
		{
			if ( emcalmapping.IsEMCAL(bg_event_clusters_ecal[ip].eta(), bg_event_clusters_ecal[ip].phi_02pi()) )
			{
				hbgcl->Fill(bg_event_clusters_ecal[ip].eta(), bg_event_clusters_ecal[ip].phi_02pi(), bg_event_clusters_ecal[ip].e());
				hEcl->Fill(centRandom, bg_event_clusters_ecal[ip].e());
				acceptedBGecal++;
			}
		}

		unsigned int possibleDCal = 0;
		for (unsigned int ip = 0; ip < bg_event_clusters_dcal_rot.size(); ip++)
		{
			if ( R2Util::IsDCALPHOS02pi(bg_event_clusters_dcal_rot[ip].eta(), bg_event_clusters_dcal_rot[ip].phi_02pi()) )
			{
				possibleDCal++;
			}
		}

		for (unsigned int ip = 0; ip < bg_event_clusters_dcal_rot.size(); ip++)
		{
			if ( emcalmapping.IsDCALPHOS(bg_event_clusters_dcal_rot[ip].eta(), bg_event_clusters_dcal_rot[ip].phi_02pi()) )
			{
				hbgcl->Fill(bg_event_clusters_dcal_rot[ip].eta(), bg_event_clusters_dcal_rot[ip].phi_02pi(), bg_event_clusters_dcal_rot[ip].e());
				acceptedBGdcal++;
			}
		}

		hgenBGecal->Fill(centRandom, bg_event_clusters_ecal.size());
		//hgenBGdcal->Fill(bg_event_clusters_dcal.size(), centRandom);
		hgenBGdcal->Fill(centRandom, possibleDCal);

		if (bg_event_clusters_ecal.size() > 0)
		{
			haccBGecal->Fill(centRandom, acceptedBGecal / bg_event_clusters_ecal.size());
			if (verbosity > 8)
				cout << "[i] event bg cluster stat ECAL [acc | gen | a/g ratio]: " << acceptedBGecal << " " << bg_event_clusters_ecal.size() << " " << acceptedBGecal / bg_event_clusters_ecal.size() << endl;
		}
		if (bg_event_clusters_dcal.size() > 0)
		{
			haccBGdcal->Fill(centRandom, acceptedBGdcal / possibleDCal);
			//haccBGdcal->Fill(acceptedBGdcal / bg_event_clusters_dcal.size(), centRandom);
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

		Header head;
		head.rho   = -1;
		head.sigma = -1;

		//revent.SetPythia(&pythia);
		revent.SetBackground(pFME);
		//revent.SetEMCresponse(EMCresponse);

		revent.FillHeader("hd", 	&head);

		revent.FillBranch("bgcl", 	bg_event_clusters);
		revent.FillBranch("bgtrk", 	bg_event_tracks);

		revent.FillTrigger("tg", 	&tm);
		revent.FillTrigger("tgbg", 	&tm_bg);

		revent.FinishEvent();
	} // end of event loop

	fout->Write();
	fout->Close();

	revent.Write();
	//delete EMCresponse;

	return 0;
}
