#include "REvent.h"

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include <TriggerMaker.h>

#include <iostream> // needed for io
using namespace std;

namespace fj = fastjet;

REvent::REvent()
	: tree(0)
{
	;
}

REvent::~REvent()
{
	;
}

void REvent::Init(const char *tname)
{
	tree = new TTree(tname, tname);
}

void REvent::Write()
{
	;
}

void REvent::FillBranch(const char* name, std::vector <fj::PseudoJet> in)
{
	//std::vector<TLorentzVector> *pv = new std::vector<TLorentzVector>;
	std::vector<TLorentzVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	std::vector<TLorentzVector> &v  = *pv;
	TLorentzVector tlv;
	for (int i = 0; i < in.size(); ++i)
	{
		tlv.SetPtEtaPhiE(in[i].perp(), in[i].eta(), in[i].phi_02pi(), in[i].e());
		v.push_back(tlv);
	}
	b->Fill();
	pv->clear();
	delete pv;
}

void REvent::FillBranch(const char *name, std::vector<RawPatch> in)
{
	//cout << "[i] Fill branch: " << name << " n = " << in.size() << endl;
	std::vector<TLorentzVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	std::vector<TLorentzVector> &v  = *pv;
	TLorentzVector tlv;
	for (int i = 0; i < in.size(); ++i)
	{
		tlv.SetPtEtaPhiE(in[i].GetADC(),
		                 in[i].GetRowStart() / 64., // phi will not be accurate for DCal
		                 in[i].GetColStart() / 48., // fixed 48
		                 in[i].GetADC());
		v.push_back(tlv);
	}
	b->Fill();
	pv->clear();
	delete pv;
}

void REvent::FinishEvent()
{
	//tree->Fill();
	Int_t n = tree->GetEntries();
	tree->SetEntries(n + 1);
}

void REvent::FillTrigger(const char* name, TriggerMaker *tm)
{
	double tinfo[12];
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &tinfo[0], "maxjECAL/D:maxjDCAL/D:maxjECAL8x8/D:maxjDCAL8x8/D:maxgECAL/D:maxgDCAL/D:medjECAL/D:medjDCAL/D:medjECAL8x8/D:medjDCAL8x8/D:medgECAL/D:medgDCAL/D");
	}
	b->SetAddress(&tinfo[0]);
	tinfo[0] = tm->GetMaxJetEMCAL().GetADC();
	tinfo[1] = tm->GetMaxJetDCALPHOS().GetADC();
	tinfo[2] = tm->GetMaxJetEMCAL8x8().GetADC();
	tinfo[3] = tm->GetMaxJetDCALPHOS8x8().GetADC();
	tinfo[4] = tm->GetMaxGammaEMCAL().GetADC();
	tinfo[5] = tm->GetMaxGammaDCALPHOS().GetADC();
	tinfo[6] = tm->GetMedianJetEMCAL();
	tinfo[7] = tm->GetMedianJetDCALPHOS();
	tinfo[8] = tm->GetMedianJetEMCAL8x8();  		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo[9] = tm->GetMedianJetDCALPHOS8x8();		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo[10] = tm->GetMedianGammaEMCAL();
	tinfo[11] = tm->GetMedianGammaDCALPHOS();
	b->Fill();

	FillBranch(TString::Format("%sEJE", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE));
	FillBranch(TString::Format("%sEJE8x8", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE8x8));
	FillBranch(TString::Format("%sEGA", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchGA));

	FillBranch(TString::Format("%sDJE", name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE) );
	FillBranch(TString::Format("%sDJE8x8", name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE8x8) );
	FillBranch(TString::Format("%sDGA", name).Data(), tm->GetPatches(RawPatch::kDCALpatchGA) );

}
