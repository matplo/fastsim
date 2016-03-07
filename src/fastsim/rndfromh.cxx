#include "rndfromh.h"

#include <TFile.h>
#include <TH1.h>
#include <TRandom.h>

#include <iostream>
using namespace std;

RndFromH::RndFromH(const char *fname, const char* hname)
	: fH(0)
{
	TFile *fin = TFile::Open(fname);
	if (fin != 0)
	{
		TH1 *htmp = (TH1*)fin->Get(hname);
		string newname = hname;
		newname += "_clone";
		fH = (TH1*)htmp->Clone(newname.c_str());
		fH->SetDirectory(0);
		fin->Close();
		delete fin;
	}
	cout << "[i] RndFromH::RndFromH histogram at: " << fH << endl;
}

RndFromH::~RndFromH()
{
	delete fH;
}

bool RndFromH::Accept(double v) const
{
	if (fH == 0)
	{
		cerr << "[w] RndFromH::Accept with fH == 0 -> returns always false!" << endl;
		return false;
	}
	// treat histogram as efficiency
	Int_t ibin = fH->FindBin(v);
	if (ibin > fH->GetNbinsX())
	{
		// warning: take the last filled bin as the efficiency beyond the range
		ibin = fH->GetNbinsX();
	}
	return (gRandom->Rndm() < fH->GetBinContent(ibin));
}