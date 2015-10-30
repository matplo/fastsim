#include "analysis.h"

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH2F.h>

#include <iostream>
using namespace std;

ClassImp(Analysis);

Analysis::Analysis()
	: TObject()
{
	;
}

Analysis::~Analysis()
{
	;
}

Bool_t Analysis::Notify()
{
	return kTRUE;
}

Int_t Analysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
	if (!fChain) return 0;
	return fChain->GetEntry(entry);
}

Long64_t Analysis::LoadTree(Long64_t entry)
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

TBranch *Analysis::GetBranch(const char *name, std::vector<TLorentzVector> **p)
{
	TBranch *b = 0;
	fChain->SetBranchStatus(name, kTRUE);
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

TBranch *Analysis::GetBranch(const char *name, Double_t *p)
{
	TBranch *b = 0;
	fChain->SetBranchStatus(name, kTRUE);
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

//TBranch *Analysis::GetBranch(const char *name, Header &p)
//{
//	TBranch *b = 0;
//	fChain->SetBranchAddress(name, &p.xsec, &b);
//	cout << "    activated branch " << name << " at " << b << endl;
//	return b;
//}

void Analysis::AnalyzeFile(const char *fname, const char *foutname, Long64_t nev)
{
	TFile *fout = new TFile(foutname, "RECREATE");
	fout->cd();
	TH2F *hptcentn = new TH2F("hptcentn", "hptcentn", 300, 0, 300, 100, 0, 100);
	TH2F *hptcentw = new TH2F("hptcentw", "hptcentw", 300, 0, 300, 100, 0, 100);

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
	std::vector<TLorentzVector> *pjE  = 0;
	std::vector<TLorentzVector> *pjD  = 0;
	std::vector<TLorentzVector> *pjEr = 0;
	std::vector<TLorentzVector> *pjDr = 0;

	std::vector<TLorentzVector> *ptgEJE = 0;
	std::vector<TLorentzVector> *ptgEGA = 0;
	std::vector<TLorentzVector> *ptgDJE = 0;
	std::vector<TLorentzVector> *ptgDGA = 0;

	//fChain->SetBranchStatus("*", kFALSE);

	GetBranch("hd", 	&hd.xsec);
	GetBranch("tg", 	&tg.maxjECAL);

	GetBranch("jE", 	&pjE );
	GetBranch("jD", 	&pjD );
	GetBranch("jEr", 	&pjEr);
	GetBranch("jDr", 	&pjDr);

	GetBranch("tgEJE", 	&ptgEJE);
	GetBranch("tgEGA", 	&ptgEGA);
	GetBranch("tgDJE", 	&ptgDJE);
	GetBranch("tgDGA", 	&ptgDGA);

	std::vector<TLorentzVector> &jE = *pjE;

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < nentries; jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;
		if (jentry % 1000 == 0 && jentry > 0)
		{
			//printf("    %lld of %lld \n", jentry, nentries);
			cout << "    " << jentry << " of " << nentries << endl;
		}
		for (std::vector<TLorentzVector>::iterator i = pjE->begin(); i != pjE->end(); ++i)
		{
			cout << "    " << " " << i->Pt() << " " << hd.cent << endl;
			hptcentn->Fill(i->Pt(), hd.cent);
			hptcentw->Fill(i->Pt(), hd.cent, hd.xsec);
		}
		cout << "    "
		     << jE.size() << " \t"
		     << hd.xsec 	<< " \t"
		     << hd.cent 	<< " \t"
		     << tg.maxjECAL << " \t"
		     << tg.maxgDCAL
		     << endl;
	}
	fin->Close();
	fout->Write();
}
