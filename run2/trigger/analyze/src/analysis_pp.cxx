#include "analysis_pp.h"

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TNtuple.h>

#include <rstructures.h>

#include <iostream>
using namespace std;

ClassImp(Analysis_pp);

Analysis_pp::Analysis_pp()
	: TObject()
	, fCurrent(0)
	, frflag(kFALSE)
{
	;
}

Analysis_pp::~Analysis_pp()
{
	;
}

Bool_t Analysis_pp::Notify()
{
	return kTRUE;
}

Int_t Analysis_pp::GetEntry(Long64_t entry)
{
// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}

Long64_t Analysis_pp::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
	if (!fChain) return -5;
	Long64_t centry = fChain->LoadTree(entry);
	if (centry < 0) return centry;
	if (fChain->GetTreeNumber() != fCurrent)
	{
		fCurrent = fChain->GetTreeNumber();
		Notify();
	}
	return centry;
}

TBranch *Analysis_pp::GetBranch(const char *name, std::vector<TLorentzVector> **p)
{
	TBranch *b = 0;
	fChain->SetBranchStatus(name, kTRUE);
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

TBranch *Analysis_pp::GetBranch(const char *name, Double_t *p)
{
	TBranch *b = 0;
	fChain->SetBranchStatus(name, kTRUE);
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

//TBranch *Analysis_pp::GetBranch(const char *name, Header &p)
//{
//	TBranch *b = 0;
//	fChain->SetBranchAddress(name, &p.xsec, &b);
//	cout << "    activated branch " << name << " at " << b << endl;
//	return b;
//}

void Analysis_pp::AnalyzeFile(const char *fname, const char *foutname, Long64_t nev)
{
	TFile *fout = new TFile(foutname, "RECREATE");
	fout->cd();

	Double_t maxpt   	= 300;
	Int_t    nptbins 	= 300;

	TH1F *hNev          = new TH1F("hNev",   			"hNev", 	10, 0, 10);

	TH1F *hptn 			= new TH1F("hptn",				"hptn",	 nptbins, 0, maxpt);
	TH1F *hptw 			= new TH1F("hptw",				"hptw",	 nptbins, 0, maxpt);

	TH1F *hEptn         = new TH1F("hEptn", 			"hEptn", nptbins, 0, maxpt);
	TH1F *hEptw         = new TH1F("hEptw", 			"hEptw", nptbins, 0, maxpt);

	TH1F *hDptn         = new TH1F("hDptn", 			"hDptn", nptbins, 0, maxpt);
	TH1F *hDptw         = new TH1F("hDptw", 			"hDptw", nptbins, 0, maxpt);

	// just to count
	TNtuple *tn   = new TNtuple("tn", "tn",
	                            "xsec:maxEJE:maxEJE8x8:maxEGA:medEJE:medEJE8x8:medEGA:maxDJE:maxDJE8x8:maxDGA:medDJE:medDJE8x8:medDGA");

	TNtuple *tnj   = new TNtuple("tnjet", 	"tnjet", 	"cal:xsec:pt:maxJE:maxJE8x8:maxGA:medJE:medGA");
	TNtuple *tnjr  = new TNtuple("tnjetr", 	"tnjet", 	"cal:xsec:pt:maxJE:maxJE8x8:maxGA:medJE:medGA");
	TNtuple *tnpi0 = new TNtuple("tnpi0", 	"tnpi0", 	"cal:xsec:pt:maxJE:maxJE8x8:maxGA:medJE:medGA");
	TNtuple *tng   = new TNtuple("tng", 	"tng", 		"cal:xsec:pt:maxJE:maxJE8x8:maxGA:medJE:medGA");

	// in case cal=0 the max is ECAL and med is DCAL
	// in case cal=1 the max is DCAL and med is ECAL
	TNtuple *tnpi0jet = 	new TNtuple("tnpi0jet", 	"tnpi0jet",
	                                    "cal:xsec:cent:ptT:jpt:dphi:maxJE:maxJE8x8:maxGA:medJE:medGA");

	// in case cal=0 the max is ECAL and med is DCAL
	// in case cal=1 the max is DCAL and med is ECAL
	TNtuple *tngjet = 	new TNtuple("tngjet", 	"tngjet", 	"cal:xsec:cent:ptT:jpt:dphi:maxJE:maxJE8x8:maxGA:medJE:medGA");
	TNtuple *tnghad = 	new TNtuple("tnghad", 	"tnghad", 	"cal:xsec:cent:ptT:hpt:dphi:maxJE:maxJE8x8:maxGA:medJE:medGA");

	// begin output

	TFile *fin = new TFile(fname);
	cout << "[i] Open file: " << fname << " at " << fin << endl;
	fChain = (TTree*)fin->Get("t");
	cout << "    Chain is at " << fChain << endl;
	Long64_t nentries = fChain->GetEntries();
	cout << "    Number of events in the tree: " << nentries << endl;
	if (nev > -1)
	{
		nentries = nev;
	}
	cout << "    will run for " << nentries << endl;

	Header hd;
	TriggerInfo tg;
	TriggerInfo tgbg;
	std::vector<TLorentzVector> *pjE       = 0;
	std::vector<TLorentzVector> *pjD       = 0;
	std::vector<TLorentzVector> *pjEr      = 0;
	std::vector<TLorentzVector> *pjDr      = 0;

	std::vector<TLorentzVector> *ptgEJE    = 0;
	std::vector<TLorentzVector> *ptgEJE8x8 = 0;
	std::vector<TLorentzVector> *ptgEGA    = 0;
	std::vector<TLorentzVector> *ptgDJE    = 0;
	std::vector<TLorentzVector> *ptgDJE8x8 = 0;
	std::vector<TLorentzVector> *ptgDGA    = 0;

	std::vector<TLorentzVector> *pjch      = 0;
	std::vector<TLorentzVector> *pjrch     = 0;

	std::vector<TLorentzVector> *pch       = 0;
	std::vector<TLorentzVector> *pi0E      = 0;
	std::vector<TLorentzVector> *pi0D      = 0;

	std::vector<TLorentzVector> *gE        = 0;
	std::vector<TLorentzVector> *gD        = 0;

	//fChain->SetBranchStatus("*", kFALSE);
	//fChain->SetBranchStatus("p", kFALSE);
	//fChain->SetBranchStatus("bgcl", kFALSE);
	//fChain->SetBranchStatus("bgtrk", kFALSE);
	//fChain->SetBranchStatus("jf", kFALSE);
	fChain->SetBranchStatus("j", kFALSE);

	GetBranch("hd", 	&hd.xsec);
	GetBranch("tg", 	&tg.maxjECAL);
	GetBranch("tgbg", 	&tgbg.maxjECAL);

	GetBranch("pch",  	&pch); //charged particles from hard event

	GetBranch("pi0E",  	&pi0E);
	GetBranch("pi0D",  	&pi0D);

	GetBranch("gE", 	&gE);
	GetBranch("gD", 	&gD);

	GetBranch("jE", 	&pjE );
	GetBranch("jD", 	&pjD );
	GetBranch("jEr", 	&pjEr);
	GetBranch("jDr", 	&pjDr);

	GetBranch("jch",	&pjch);
	GetBranch("jrch",	&pjrch);

	GetBranch("tgEJE", 		&ptgEJE);
	GetBranch("tgEJE8x8", 	&ptgEJE8x8);
	GetBranch("tgEGA", 		&ptgEGA);
	GetBranch("tgDJE", 		&ptgDJE);
	GetBranch("tgDJE8x8", 	&ptgDJE8x8);
	GetBranch("tgDGA", 		&ptgDGA);

	//std::vector<TLorentzVector> &jE = *pjE;

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		if (jentry % 1000 == 0 && jentry > 0)
			cout << "    " << jentry << " of " << nentries << endl;

		hNev->Fill(0.1);
		hNev->Fill(1.1, hd.xsec);

		tn->Fill(hd.xsec,
		         tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjECAL, tg.medjECAL8x8, tg.medgECAL,
		         tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjDCAL, tg.medjDCAL8x8, tg.medgDCAL);

		// jE
		for (std::vector<TLorentzVector>::iterator i = pjE->begin(); i != pjE->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnj->Fill(0, hd.xsec, i->Pt(), tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}

			hEptn->Fill(i->Pt());
			hEptw->Fill(i->Pt(), hd.xsec);
		}

		// jEr
		for (std::vector<TLorentzVector>::iterator i = pjEr->begin(); i != pjEr->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnjr->Fill(0, hd.xsec, i->Pt(), tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}
		}

		// jD
		for (std::vector<TLorentzVector>::iterator i = pjD->begin(); i != pjD->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnj->Fill(1, hd.xsec, i->Pt(), tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}

			hDptn->Fill(i->Pt());
			hDptw->Fill(i->Pt(), hd.xsec);
		}

		// jDr
		for (std::vector<TLorentzVector>::iterator i = pjDr->begin(); i != pjDr->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnjr->Fill(1, hd.xsec, i->Pt(), tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
		}

		// in case cal=0 the max is ECAL and med is DCAL
		// in case cal=1 the max is DCAL and med is ECAL
		//TNtuple *tnpi0jet = new TNtuple("tnpi0jet", "cal:xsec:cent:ptT:jpt:dphi:maxJE:maxGA:medJE:medGA:");
		for (std::vector<TLorentzVector>::iterator i = pi0E->begin(); i != pi0E->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tnpi0->Fill(0, hd.xsec, i->Pt(), tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tnpi0jet->Fill(0, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						               tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
			}
		}
		for (std::vector<TLorentzVector>::iterator i = pi0D->begin(); i != pi0D->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tnpi0->Fill(1, hd.xsec, i->Pt(), tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tnpi0jet->Fill(1, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						               tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
					}
				}
			}
		}

		// in case cal=0 the max is ECAL and med is DCAL
		// in case cal=1 the max is DCAL and med is ECAL
		//TNtuple *tngjet = new TNtuple("tnpi0jet", "cal:xsec:cent:ptT:jpt:dphi:maxJE:maxGA:medJE:medGA:");
		//TNtuple *tnghad = new TNtuple("tnpi0jet", "cal:xsec:cent:ptT:hpt:dphi:maxJE:maxGA:medJE:medGA:");
		for (std::vector<TLorentzVector>::iterator i = gE->begin(); i != gE->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tng->Fill(0, hd.xsec, i->Pt(), tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tngjet->Fill(0, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
				for (std::vector<TLorentzVector>::iterator j = pch->begin(); j != pch->end(); ++j)
				{
					if (j->Pt() > 1 && TMath::Abs(j->Eta()) < 0.9)
					{
						tnghad->Fill(0, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
			}
		}
		for (std::vector<TLorentzVector>::iterator i = gD->begin(); i != gD->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tng->Fill(1, hd.xsec, i->Pt(), tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tngjet->Fill(1, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
					}
				}
				for (std::vector<TLorentzVector>::iterator j = pch->begin(); j != pch->end(); ++j)
				{
					if (j->Pt() > 1 && TMath::Abs(j->Eta()) < 0.9)
					{
						tnghad->Fill(1, hd.xsec, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
					}
				}
			}
		}

		pjE       ->clear();
		pjD       ->clear();
		pjEr      ->clear();
		pjDr      ->clear();
		ptgEJE    ->clear();
		ptgEJE8x8 ->clear();
		ptgEGA    ->clear();
		ptgDJE    ->clear();
		ptgDJE8x8 ->clear();
		ptgDGA    ->clear();
		pjch      ->clear();
		pjrch     ->clear();
		pch       ->clear();
		pi0E      ->clear();
		pi0D      ->clear();
		gE        ->clear();
		gD        ->clear();

	} //end event loop
	fin->Close();
	fout->Write();
}
