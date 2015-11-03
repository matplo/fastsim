#include "revent.h"

#include <TFile.h>
#include <TTree.h>
#include <TLorentzVector.h>

#include <EMPartResp.h>
#include <AliGenFastModelingEvent.h>
#include <TriggerMaker.h>

#include <iostream> // needed for io
using namespace std;
//using namespace fastjet; - conflicts with root
namespace fj = fastjet;
//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

REvent::REvent()
	: fout(0)
	, tree(0)
	, pPythia(0)
	, pFME(0)
	, pEMCresponse(0)
{
	;
}

REvent::~REvent()
{
	fout->Close();
	fout->Delete();
}

void REvent::Init(const char *foutname)
{
	fout = new TFile(foutname, "RECREATE");
	fout->cd();

	tree = new TTree("t", "t");

}

void REvent::Write()
{
	fout->Write();
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
		                 in[i].GetColStart(),
		                 in[i].GetRowStart(),
		                 in[i].GetADC());
		v.push_back(tlv);
	}
	b->Fill();
}

void REvent::FinishEvent()
{
	//tree->Fill();
	Int_t n = tree->GetEntries();
	tree->SetEntries(n+1);
}

void REvent::FillTrigger(const char* name, TriggerMaker *tm)
{
	TriggerInfo tinfo;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &tinfo.maxjECAL, "maxjECAL/D:maxjDCAL/D:maxjECAL8x8/D:maxjDCAL8x8/D:maxgECAL/D:maxgDCAL/D:medjECAL/D:medjDCAL/D:medjECAL8x8/D:medjDCAL8x8/D:medgECAL/D:medgDCAL/D");
	}
	b->SetAddress(&tinfo.maxjECAL);
	tinfo.maxjECAL    = tm->GetMaxJetEMCAL().GetADC();
	tinfo.maxjDCAL    = tm->GetMaxJetDCALPHOS().GetADC();
	tinfo.maxjECAL8x8 = tm->GetMaxJetEMCAL8x8().GetADC();
	tinfo.maxjDCAL8x8 = tm->GetMaxJetDCALPHOS8x8().GetADC();
	tinfo.maxgECAL    = tm->GetMaxGammaEMCAL().GetADC();
	tinfo.maxgDCAL    = tm->GetMaxGammaDCALPHOS().GetADC();

	tinfo.medjECAL    = tm->GetMedianJetEMCAL();  		
	tinfo.medjDCAL    = tm->GetMedianJetDCALPHOS();		
	tinfo.medjECAL8x8 = tm->GetMedianJetEMCAL8x8();  		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo.medjDCAL8x8 = tm->GetMedianJetDCALPHOS8x8();		// NOTE: median is calculated based on 8x8 FOR not 16x16
	tinfo.medgECAL    = tm->GetMedianGammaEMCAL();
	tinfo.medgDCAL    = tm->GetMedianGammaDCALPHOS();
	b->Fill();

	FillBranch(TString::Format("%sEJE",name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE));
	FillBranch(TString::Format("%sEJE8x8",name).Data(), tm->GetPatches(RawPatch::kEMCALpatchJE8x8));
	FillBranch(TString::Format("%sEGA",name).Data(), tm->GetPatches(RawPatch::kEMCALpatchGA));

	FillBranch(TString::Format("%sDJE",name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE) );
	FillBranch(TString::Format("%sDJE8x8",name).Data(), tm->GetPatches(RawPatch::kDCALpatchJE8x8) );
	FillBranch(TString::Format("%sDGA",name).Data(), tm->GetPatches(RawPatch::kDCALpatchGA) );

}

void REvent::FillHeader(const char* name, Header *hp)
{
	Header &h = *hp;
	TBranch *b = tree->GetBranch(name);
	if (b == 0)
	{
		b = tree->Branch(name, &h.xsec, "xsec/D:cent/D:rho/D:sigma/D");
	}
	h.cent = -1.0;
	if (pFME != 0)
	{
		h.cent = pFME->GetCentrality();
	}
	h.xsec = -1.0;
	if (pPythia != 0)
	{
		h.xsec  = pPythia->info.sigmaGen();
	}
	b->SetAddress(&h.xsec);
	b->Fill();
}

void REvent::SetPythia(Pythia8::Pythia *p)
{
	pPythia = p;
}

void REvent::SetBackground(AliGenFastModelingEvent *p)
{
	pFME = p;
}

void REvent::SetEMCresponse(EMPartResp *p)
{
	pEMCresponse = p;
}
