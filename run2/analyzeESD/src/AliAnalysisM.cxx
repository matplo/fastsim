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
	, fHManager(0)
{
	;
}

AliAnalysisM::AliAnalysisM(const char* name)
	: AliAnalysisTaskSE(name)
	, fREvent(new REvent)
	, fGeom(0)
	, fTM(new TriggerMaker)
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
}

void AliAnalysisM::UserCreateOutputObjects()
{
	OpenFile(1);
	//create the output
	REvent *revent = (REvent*)fREvent;
	revent->Init();
	TTree *t = (TTree*)revent->GetTree();
	CreateBranches();

	fHManager = new THistManager("histos");
	fHManager->CreateTH1("fHcellsN", "fHcellsN;absId", 20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW", "fHcellsW;absId", 20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsN200", "fHcellsN200;absId", 20000., 0, 20000.);
	fHManager->CreateTH1("fHcellsW200", "fHcellsW200;absId", 20000., 0, 20000.);

	PostData(1, t);
	PostData(2, fHManager->GetListOfHistograms());
}

void AliAnalysisM::CreateBranches()
{
	REvent *revent = (REvent*)fREvent;
	const char *ts[] = {"other", "CINT7", "EJ1", "EG1", "DJ1", "DG1", 0};
	int i = 0;
	while (ts[i]!=0)
	{
		TString tsIs = ts[i];
		TString sbname;

		sbname = TString::Format("jets_%s", tsIs.Data());
		revent->CreateBranch(sbname.Data());

		sbname = TString::Format("maxEjet_%s", tsIs.Data());
		revent->CreateBranch(sbname.Data());

		sbname = TString::Format("trig_%s", tsIs.Data());
		revent->CreateTriggerBranch(sbname.Data());

		i++;
	}
	revent->DumpListOfBranches();
}

void AliAnalysisM::UserExec(Option_t* /*option*/)
{
	REvent *revent = (REvent*)fREvent;
	TTree *t = (TTree*)revent->GetTree();

	TString ts = InputEvent()->GetFiredTriggerClasses();

	TString tsIs = "other";

	if (ts.Contains("CINT7-"))
	{
		tsIs = "CINT7";
	}

	if (ts.Contains("CINT7EJ1"))
	{
		tsIs = "EJ1";
	}

	if (ts.Contains("CINT7EG1"))
	{
		tsIs = "EG1";
	}

	if (ts.Contains("CINT7DJ1"))
	{
		tsIs = "DJ1";
	}

	if (ts.Contains("CINT7DG1"))
	{
		tsIs = "DG1";
	}

	if (fGeom == 0)
	{
		Int_t runNo = InputEvent()->GetRunNumber();
		fGeom = AliEMCALGeometry::GetInstanceFromRunNumber(runNo);
	}

	TriggerMaker *tm = (TriggerMaker*)fTM;
	tm->Reset();

	// jet finder
	std::vector <fj::PseudoJet> fjcells; // signal from pythia
	// loop over cells...
	AliVCaloCells *cells = InputEvent()->GetEMCALCells();
	for (Int_t iCell = 0; iCell < cells->GetNumberOfCells(); ++iCell)
	{
		// get the cell info, based in index in array
		Short_t 	absId = cells->GetCellNumber(iCell);
		if ( IsBadChannel(absId) )
			continue;
		Double_t amp = cells->GetAmplitude(iCell); // * 0.0162;
		if (amp < 0)
			continue;
		Double_t 	phi   = -2000;
		Double_t 	eta   =  2000;
		fGeom->EtaPhiFromIndex(absId, eta, phi);

		tm->FillChannelMap(eta, phi, amp);

		fHManager->FillTH1("fHcellsN", absId);
		fHManager->FillTH1("fHcellsW", absId, amp);
		if (amp < 0.200)
		{
			continue;
		}

		fHManager->FillTH1("fHcellsN200", absId);
		fHManager->FillTH1("fHcellsW200", absId, amp);			

		fj::PseudoJet fjc;
		Double_t pT = amp / TMath::CosH(eta);
		fjc.reset_PtYPhiM(pT, eta, phi, 0.0);
		fjcells.push_back(fjc);
		//cout << "E=" << fjc.e() << " pt=" << fjc.perp() << " amp=" << amp << endl;
		//cout << "dE=" << fjc.e() - amp << endl;
	}

	double R     = 0.2;
	int    power = -1;
	double pTmin = 1;

	TString sbname;

	fj::JetDefinition 		jet_def(fj::genkt_algorithm, R, power); // this is for signal - anti-kT
	fj::ClusterSequence 	clust_seq(fjcells, jet_def);
	vector <fj::PseudoJet> 	inclusive_jets = clust_seq.inclusive_jets(pTmin);
	vector <fj::PseudoJet> 	sorted_jets    = fj::sorted_by_pt(inclusive_jets);

	sbname = TString::Format("jets_%s", tsIs.Data());
	revent->FillBranch(sbname.Data(),  sorted_jets);
	sbname = TString::Format("maxEjet_%s", tsIs.Data());
	revent->FillBranch(sbname.Data(),  sorted_jets, 1);

	sbname = TString::Format("trig_%s", tsIs.Data());
	revent->FillTrigger(sbname.Data(), tm, kFALSE);

	revent->FinishEvent();

	PostData(1, t);
	PostData(2, fHManager->GetListOfHistograms() );
}

Int_t AliAnalysisM::fgBadChannels[] = {
//warm
74, 3197, 8352, 8356, 8368, 8369, 8373, 9927, 10313, 10314, 10364, 10365, 10366, 10367, 14153,14673, 14678 ,14867,
//bad
3,58,60,62,103,177,287,655,917,1002,1204,1386,1535,1892,2112,2114,2115,2116,2119,2120,2123,2124,2125,2395,2397,2399,2575,2929,3039,3488,4320,4817,4835,4837,4838,4839,4846,5328,5330,5332,5334,5336,5338,5340,5555,5662,5663,5824,5826,5832,5833,6080,6081,6082,6083,6084,6085,6086,6087,6088,6089,6090,6091,6092,6093,6094,6095,6104,6128,6129,6130,6131,6132,6133,6134,6135,6136,6137,6138,6139,6140,6141,6142,6143,6275,6331,6481,6645,6649,6650,6651,6690,6811,8047,8357,8372,9217,9269,9703,9706,9769,9872,9878,9940,9942,9945,9951,10203,10363,10451,10560,10561,10562,10563,10564,10565,10566,10567,10568,10569,10570,10571,10572,10573,10574,10575,10608,10609,10610,10611,10612,10613,10614,10615,10616,10617,10618,10619,10620,10621,10622,10623,10982,11738,12160,12163,12320,12321,12322,12323,12324,12325,12326,12327,12328,12329,12330,12331,12332,12333,12334,12335,12368,12369,12370,12371,12372,12373,12374,12375,12376,12377,12378,12379,12380,12381,12382,12383,12610,12613,12802,12803,12805,12806,12809,12810,12824,12825,12871,12914,12917,12925,12927,13049,13053,13055,13056,13064,13068,13120,13126,13282,13284,13287,13292,13402,13405,13460,13462,13463,13464,13465,13471,13476,13477,13484,13485,13512,13513,13524,13558,13559,13828,13835,13953,13968,13969,13971,13978,13980,13982,14191,14193,14207,14228,14234,14236,14239,14249,14305,14309,14313,14317,14319,14328,14363,14374,14402,14410,14411,14438,14447,14498,14502,14544,14545,14549,14557,14592,14594,14600,14601,14606,14621,14625,14641,14644,14647,14666,14669,14679,14681,14688,14689,14691,14694,14696,14697,14711,14713,14717,14718,14719,14721,14726,14727,14736,14744,14746,14750,14751,14753,14757,14758,14761,14762,14766,14772,14775,14862,14874,14986,14993,15012,15090,15093,15152,15158,15266,15272,15284,15288,15290,15291,15294,15301,15304,15338,15354,15358,15440,15446,15460,15469,15690,15780,15783,15785,15789,15867,15870,15877,15908,15938,15941,15955,15963,16088,16091,16094,16308,16317,16349,16473,16476,16477,16479,16480,16482,16483,16488,16491,16496,16498,16499,16506,16634,16784,16785,16867,16886,17046,17095,17100,17101,17202,17204,17233,17237,17291,17312,17313,17314,17315,17316,17317,17318,17319,17320,17321,17322,17323,17324,17325,17326,17327,17328,17329,17330,17331,17332,17333,17334,17335,17336,17337,17338,17339,17340,17341,17342,17343, -1};
