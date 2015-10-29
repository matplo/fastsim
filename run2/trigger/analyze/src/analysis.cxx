#include "Analysis.h"

#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

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
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

TBranch *Analysis::GetBranch(const char *name, TriggerInfo **p)
{
	TBranch *b = 0;
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

TBranch *Analysis::GetBranch(const char *name, Header **p)
{
	TBranch *b = 0;
	fChain->SetBranchAddress(name, p, &b);
	cout << "    activated branch " << name << " at " << b << endl;
	return b;
}

void Analysis::AnalyzeFile(const char *fname, const char *foutname)
{
	TFile *fin = new TFile(fname);
	cout << "[i] Open file: " << fname << " at " << fin << endl;
	fChain = (TTree*)fin->Get("t");
	cout << "    Chain is at " << fChain << endl;
	Long64_t nentries = fChain->GetEntries();
	cout << "[i] number of events in the tree: " << nentries << endl;

	std::vector<TLorentzVector> *pjets = 0;
	TBranch *bj = GetBranch("j", &pjets);
	std::vector<TLorentzVector> &jets = *pjets;

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry = 0; jentry < 10; jentry++)
	{
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		cout << jets.size() << endl;

		if (ientry % 1000 == 0)
			cout << ientry << " of " << nentries << endl;
	}

}