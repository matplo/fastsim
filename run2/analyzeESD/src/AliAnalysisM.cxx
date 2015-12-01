#include "AliAnalysisM.h"

#include <TTree.h>
#include <TLorentzVector.h>
#include <THashList.h>

#include <TriggerMaker.h>

#include <AliEMCALGeometry.h>
#include <THistManager.h>

#include <fastjet/PseudoJet.hh>
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/Selector.hh"

#include "bad_channels_updated.txt"

namespace fj = fastjet;

#include <iostream>
using namespace std;

#include "REvent.h"

ClassImp(AliAnalysisM)

AliAnalysisM::AliAnalysisM()
	: AliAnalysisTaskSE()
	, fREvent(new REvent)
	, fGeom(0)
	, fTM(0)
	, fTM0(0)
	, fHManager(0)
{
	;
}

AliAnalysisM::AliAnalysisM(const char* name)
	: AliAnalysisTaskSE(name)
	, fREvent(new REvent)
	, fGeom(0)
	, fTM(new TriggerMaker)
	, fTM0(new TriggerMaker)
	, fHManager(0)
{
	DefineOutput(1, TTree::Class());
	DefineOutput(2, TList::Class());

	TriggerSetup tsetup;
	tsetup.SetThresholds(0., 0., 0., 0.);
	tsetup.SetTriggerBitConfig(TriggerBitConfigNew());

	TriggerMaker *tm = 0;
	tm = (TriggerMaker*)fTM;
	tm->SetTriggerSetup(tsetup);
	tm->SetAcceptPHOSPatches(false);

	TriggerMaker *tm0 = 0;
	tm0 = (TriggerMaker*)fTM0;
	tm0->SetTriggerSetup(tsetup);
	tm0->SetAcceptPHOSPatches(false);

}

void AliAnalysisM::UserCreateOutputObjects()
{
	OpenFile(1);
	//create the output
	REvent *revent = (REvent*)fREvent;
	revent->Init();
	TTree *t = (TTree*)revent->GetTree();

	fHManager = new THistManager("histos");
	fHManager->CreateTH1("fHcellsN0", 		"fHcellsN0;absId", 		20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW0", 		"fHcellsW0;absId", 		20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsN0200", 	"fHcellsN0200;absId", 	20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW0200", 	"fHcellsW0200;absId", 	20000., 0, 20000.);

	fHManager->CreateTH1("fHcellsN", 		"fHcellsN;absId", 		20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW", 		"fHcellsW;absId", 		20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsN200", 	"fHcellsN200;absId", 	20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW200", 	"fHcellsW200;absId", 	20000., 0, 20000.);

	fHManager->CreateTH1("fEJ1subMedian", "fEJ1subMedian; EJ1-median; counts", 221, -20, 200);
	fHManager->CreateTH1("fEG1subMedian", "fEG1subMedian; EG1-median; counts", 221, -20, 200);
	fHManager->CreateTH1("fDJ1subMedian", "fDJ1subMedian; DJ1-median; counts", 221, -20, 200);
	fHManager->CreateTH1("fDG1subMedian", "fDG1subMedian; DG1-median; counts", 221, -20, 200);

	fHManager->CreateTH2("fCells0", "fCells0;eta;phi", 	200, -1, 1, 360, 0, 6.4);
	fHManager->CreateTH2("fCells", 	"fCells;eta;phi", 	200, -1, 1, 360, 0, 6.4);

	PostData(1, t);
	PostData(2, fHManager->GetListOfHistograms());

	cout << "[i] Number of bad channels: " << GetNumberOfBadChannels() << endl;
}

void AliAnalysisM::UserExec(Option_t* /*option*/)
{
	TString ts = InputEvent()->GetFiredTriggerClasses();

	Int_t iEvType = kOther;
	TString tsIs = "o-";

	if (ts.Contains("CINT7-"))
	{
		tsIs += "-CINT7";
		iEvType = iEvType | kCINT7;
	}

	if (ts.Contains("CINT7EJ1"))
	{
		tsIs += "-EJ1";
		iEvType = iEvType | kEJ1;
	}

	if (ts.Contains("CINT7EG1"))
	{
		tsIs += "-EG1";
		iEvType = iEvType | kEG1;
	}

	if (ts.Contains("CINT7DJ1"))
	{
		tsIs += "-DJ1";
		iEvType = iEvType | kDJ1;
	}

	if (ts.Contains("CINT7DG1"))
	{
		tsIs += "-DG1";
		iEvType = iEvType | kDG1;
	}

	//cout << "[i] Trigger string is: " << tsIs << endl;
	//cout << "    Trigger mask is: " << TString::Format("0x%x", iEvType) << endl;

	if (fGeom == 0)
	{
		Int_t runNo = InputEvent()->GetRunNumber();
		fGeom = AliEMCALGeometry::GetInstanceFromRunNumber(runNo);
	}

	TriggerMaker *tm = (TriggerMaker*)fTM;
	tm->Reset();

	TriggerMaker *tm0 = (TriggerMaker*)fTM0;
	tm0->Reset();

	// cells for the jet finder
	std::vector <fj::PseudoJet> fjcells; // signal from pythia
	// loop over cells...
	AliVCaloCells *cells = InputEvent()->GetEMCALCells();
	for (Int_t iCell = 0; iCell < cells->GetNumberOfCells(); ++iCell)
	{
		// get the cell info, based in index in array
		Short_t 	absId = cells->GetCellNumber(iCell);
		Double_t 	phi   = -2000;
		Double_t 	eta   =  2000;
		fGeom->EtaPhiFromIndex(absId, eta, phi);

		if (phi < 0)
			phi = TVector2::Phi_0_2pi(phi);

		Double_t amp = cells->GetAmplitude(iCell); // * 0.0162;
		if (amp < 0)
			continue;

		tm0->FillChannelMap(eta, phi, amp);
		fHManager->FillTH2("fCells0", eta, phi);

		if (iEvType & kCINT7)
		{
			fHManager->FillTH1("fHcellsN0", absId);
			fHManager->FillTH1("fHcellsW0", absId, amp);
			if (amp > 0.200)
			{
				fHManager->FillTH1("fHcellsN0200", absId);
				fHManager->FillTH1("fHcellsW0200", absId, amp);
			}
		}

		if ( IsBadChannel(absId) )
			continue;
		tm->FillChannelMap(eta, phi, amp);

		if (iEvType & kCINT7)
		{
			fHManager->FillTH1("fHcellsN", absId);
			fHManager->FillTH1("fHcellsW", absId, amp);
			if (amp > 0.200)
			{
				fHManager->FillTH1("fHcellsN200", absId);
				fHManager->FillTH1("fHcellsW200", absId, amp);
			}
		}

		fHManager->FillTH2("fCells", eta, phi);

		if (amp < 0.200)
		{
			continue;
		}

		fj::PseudoJet fjc;
		Double_t pT = amp / TMath::CosH(eta);
		fjc.reset_PtYPhiM(pT, eta, phi, 0.0);
		fjcells.push_back(fjc);

	}

	REvent *revent = (REvent*)fREvent;

	revent->FillTrigger("trig", 	tm, 	iEvType, kFALSE);
	revent->FillTrigger("trig0", 	tm0, 	iEvType, kFALSE);

	if (iEvType & kCINT7)
	{
		double median = 0;
		double e      = 0;
		std::vector<RawPatch> v;

		v = tm->GetPatches(RawPatch::kEMCALpatchJE8x8);
		median = tm->GetMedianJetDCALPHOS8x8();
		for (Int_t i = 0; i < v.size(); i++)
		{
			e = v[i].GetADC();
			fHManager->FillTH1("fEJ1subMedian", e - median);
		}

		v = tm->GetPatches(RawPatch::kEMCALpatchGA);
		median = tm->GetMedianGammaDCALPHOS();
		for (Int_t i = 0; i < v.size(); i++)
		{
			e = v[i].GetADC();
			fHManager->FillTH1("fEG1subMedian", e - median);
		}

		v = tm->GetPatches(RawPatch::kDCALpatchJE8x8);
		median = tm->GetMedianJetEMCAL8x8();
		for (Int_t i = 0; i < v.size(); i++)
		{
			e = v[i].GetADC();
			fHManager->FillTH1("fDJ1subMedian", e - median);
		}

		v = tm->GetPatches(RawPatch::kDCALpatchGA);
		median = tm->GetMedianGammaEMCAL();
		for (Int_t i = 0; i < v.size(); i++)
		{
			e = v[i].GetADC();
			fHManager->FillTH1("fDG1subMedian", e - median);	
		}
	}

	//Jets(&fjcells, 0.1);
	Jets(&fjcells, 0.0316); // equiv to 4x4 towers
	Jets(&fjcells, 0.2);
	Jets(&fjcells, 0.4);
	revent->FinishEvent();

	TTree *t = (TTree*)revent->GetTree();
	PostData(1, t);
	PostData(2, fHManager->GetListOfHistograms() );
}

void AliAnalysisM::Jets(void *cells, double R)
{
	int    power = -1;
	double pTmin = 1;

	std::vector <fj::PseudoJet> &fjcells = *((std::vector <fj::PseudoJet>*)cells);
	TString sbname;
	fj::JetDefinition 		jet_def(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
	fj::ClusterSequence 	clust_seq(fjcells, jet_def);
	vector <fj::PseudoJet> 	inclusive_jets = clust_seq.inclusive_jets(pTmin);
	vector <fj::PseudoJet> 	sorted_jets    = fj::sorted_by_pt(inclusive_jets);

	REvent *revent = (REvent*)fREvent;
	sbname = TString::Format("jets%1.1f", R).ReplaceAll(".", "");
	revent->FillBranch(sbname.Data(),  sorted_jets);
	sbname = TString::Format("maxEjet%1.1f", R).ReplaceAll(".", "");
	revent->FillBranch(sbname.Data(),  sorted_jets, 1);
}
