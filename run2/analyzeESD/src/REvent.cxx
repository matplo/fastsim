#include "REvent.h"
#include "CaloVector.h"

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

void REvent::DumpListOfBranches()
{
	TObjArray *arr = tree->GetListOfBranches();
	cout << "[i] Dump list of branches of " << tree->GetName() << endl;
	for (Int_t i = 0; i < arr->GetEntries(); i++)
	{
		TBranch *b = (TBranch*)arr->At(i);
		cout << "    Branch: " << b->GetName() << endl;
	}
}

void REvent::CreateTriggerBranch(const char* name)
{
	double tinfo[13];
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &tinfo[0], "type/D:maxjECAL/D:maxjDCAL/D:maxjECAL8x8/D:maxjDCAL8x8/D:maxgECAL/D:maxgDCAL/D:medjECAL/D:medjDCAL/D:medjECAL8x8/D:medjDCAL8x8/D:medgECAL/D:medgDCAL/D");
	}
	b->SetAddress(&tinfo[0]);
}

void REvent::CreateBranchTLV(const char* name)
{
	std::vector<TLorentzVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	delete pv;
}

void REvent::FillBranchTLV(const char* name, std::vector <fj::PseudoJet> in, unsigned int maxn)
{
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
		if (maxn > 0 && i >= maxn)
			break;
		tlv.SetPtEtaPhiE(in[i].perp(), in[i].eta(), in[i].phi_02pi(), in[i].e());
		v.push_back(tlv);
	}
	b->Fill();
	pv->clear();
	delete pv;
}

void REvent::FillBranchTLV(const char *name, std::vector<RawPatch> in)
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

void REvent::CreateBranch(const char* name)
{
	std::vector<CaloVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	delete pv;
}

void REvent::FillBranch(const char* name, std::vector <fj::PseudoJet> in, unsigned int maxn)
{
	std::vector<CaloVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	std::vector<CaloVector> &v  = *pv;
	CaloVector tlv;
	for (int i = 0; i < in.size(); ++i)
	{
		if (maxn > 0 && i >= maxn)
			break;
		tlv.SetEtaPhiE(in[i].eta(), in[i].phi_02pi(), in[i].e());
		tlv.SetArea(in[i].area());
		cout << tlv.Area() << endl;
		v.push_back(tlv);
	}
	b->Fill();
	pv->clear();
	delete pv;
}

void REvent::FillBranch(const char *name, std::vector<RawPatch> in)
{
	//cout << "[i] Fill branch: " << name << " n = " << in.size() << endl;
	std::vector<CaloVector> *pv = 0;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &pv, 1);
	}
	b->SetAddress(&pv);
	std::vector<CaloVector> &v  = *pv;
	CaloVector tlv;
	for (int i = 0; i < in.size(); ++i)
	{
		tlv.SetEtaPhiE(in[i].GetRowStart() / 64., // phi will not be accurate for DCal
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

void REvent::FillTrigger(const char* name, TriggerMaker *tm, Int_t etype, Bool_t patches)
{
	double tinfo[13];
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &tinfo[0], "type/D:maxjECAL/D:maxjDCAL/D:maxjECAL8x8/D:maxjDCAL8x8/D:maxgECAL/D:maxgDCAL/D:medjECAL/D:medjDCAL/D:medjECAL8x8/D:medjDCAL8x8/D:medgECAL/D:medgDCAL/D");
	}
	b->SetAddress(&tinfo[0]);
	tinfo[0]  = etype * 1.;
	tinfo[1]  = tm->GetMaxJetEMCAL().GetADC();
	tinfo[2]  = tm->GetMaxJetDCALPHOS().GetADC();
	tinfo[3]  = tm->GetMaxJetEMCAL8x8().GetADC();
	tinfo[4]  = tm->GetMaxJetDCALPHOS8x8().GetADC();
	tinfo[5]  = tm->GetMaxGammaEMCAL().GetADC();
	tinfo[6]  = tm->GetMaxGammaDCALPHOS().GetADC();
	tinfo[7]  = tm->GetMedianJetEMCAL();
	tinfo[8]  = tm->GetMedianJetDCALPHOS();
	tinfo[9]  = tm->GetMedianJetEMCAL8x8();  		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo[10] = tm->GetMedianJetDCALPHOS8x8();		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo[11] = tm->GetMedianGammaEMCAL();
	tinfo[12] = tm->GetMedianGammaDCALPHOS();
	b->Fill();

	if (patches == kTRUE)
	{
		FillBranch(TString::Format("%sEJE", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE));
		FillBranch(TString::Format("%sEJE8x8", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE8x8));
		FillBranch(TString::Format("%sEGA", name).Data(), tm->GetPatches(RawPatch::kEMCALpatchGA));

		FillBranch(TString::Format("%sDJE", name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE) );
		FillBranch(TString::Format("%sDJE8x8", name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE8x8) );
		FillBranch(TString::Format("%sDGA", name).Data(), tm->GetPatches(RawPatch::kDCALpatchGA) );
	}
}
