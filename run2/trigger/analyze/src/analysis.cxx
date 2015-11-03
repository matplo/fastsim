#include "analysis.h"

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

ClassImp(Analysis);

Analysis::Analysis()
	: TObject()
	, fCurrent(0)
	, frflag(kFALSE)
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

	Double_t maxpt   	= 300;
	Int_t    nptbins 	= 300;

	TH1F *hNev          = new TH1F("hNev",   "hNev", 	10, 0, 10);
	TH1F *hCentn        = new TH1F("hCentn", "hCentn", 100, 0, 100);
	TH1F *hCentw        = new TH1F("hCentw", "hCentw", 100, 0, 100);

	TH1F *hEptn         = new TH1F("hEptn", 			"hEptn", nptbins, 0, maxpt);
	TH1F *hEptw         = new TH1F("hEptw", 			"hEptw", nptbins, 0, maxpt);
	TH2F *hEptcentn     = new TH2F("hEptcentn", 		"hEptcentn", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEptcentw     = new TH2F("hEptcentw", 		"hEptcentw", nptbins, 0, maxpt, 100, 0, 100);
	TH3F *hEptcentmedjn = new TH3F("hEptcentmedjn", 	"hEptcentmedjn;pt;cent;med JE DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmedjw = new TH3F("hEptcentmedjw", 	"hEptcentmedjw;pt;cent;med JE DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmaxjn = new TH3F("hEptcentmaxjn", 	"hEptcentmaxjn;pt;cent;max JE DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmaxjw = new TH3F("hEptcentmaxjw", 	"hEptcentmaxjw;pt;cent;max JE DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmedgn = new TH3F("hEptcentmedgn", 	"hEptcentmedgn;pt;cent;med GA DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmedgw = new TH3F("hEptcentmedgw", 	"hEptcentmedgw;pt;cent;med GA DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmaxgn = new TH3F("hEptcentmaxgn", 	"hEptcentmaxgn;pt;cent;max GA DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hEptcentmaxgw = new TH3F("hEptcentmaxgw", 	"hEptcentmaxgw;pt;cent;max GA DCAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);

	TH1F *hDptn         = new TH1F("hDptn", 			"hDptn", nptbins, 0, maxpt);
	TH1F *hDptw         = new TH1F("hDptw", 			"hDptw", nptbins, 0, maxpt);
	TH2F *hDptcentn     = new TH2F("hDptcentn", 		"hDptcentn", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDptcentw     = new TH2F("hDptcentw", 		"hDptcentw", nptbins, 0, maxpt, 100, 0, 100);
	TH3F *hDptcentmedjn = new TH3F("hDptcentmedjn", 	"hDptcentmedjn;pt;cent;med JE ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmedjw = new TH3F("hDptcentmedjw", 	"hDptcentmedjw;pt;cent;med JE ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmaxjn = new TH3F("hDptcentmaxjn", 	"hDptcentmaxjn;pt;cent;max JE ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmaxjw = new TH3F("hDptcentmaxjw", 	"hDptcentmaxjw;pt;cent;max JE ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmedgn = new TH3F("hDptcentmedgn", 	"hDptcentmedgn;pt;cent;med GA ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmedgw = new TH3F("hDptcentmedgw", 	"hDptcentmedgw;pt;cent;med GA ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmaxgn = new TH3F("hDptcentmaxgn", 	"hDptcentmaxgn;pt;cent;max GA ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);
	TH3F *hDptcentmaxgw = new TH3F("hDptcentmaxgw", 	"hDptcentmaxgw;pt;cent;max GA ECAL", nptbins, 0, maxpt, 100, 0, 100, nptbins, 0, maxpt);

	std::vector<double> cent;
	cent.push_back( 0); cent.push_back(101);
	cent.push_back( 0); cent.push_back(	10);
	cent.push_back(10); cent.push_back(	20);
	cent.push_back(20); cent.push_back(	40);
	cent.push_back(40); cent.push_back(	60);
	cent.push_back(60); cent.push_back(	80);
	cent.push_back(80); cent.push_back(100);

	TH2F *hEptCmedjn[7];
	TH2F *hEptCmedjw[7];
	TH2F *hEptCmaxjn[7];
	TH2F *hEptCmaxjw[7];

	TH2F *hEptCdiffjn[7];
	TH2F *hEptCdiffjw[7];

	TH2F *hEptCmedgn[7];
	TH2F *hEptCmedgw[7];

	// jet pT vs. JE med/max DCAL/ECAL
	for (unsigned int i = 0; i < cent.size() / 2; i++)
	{
		hEptCmedjn[i] = new TH2F(TString::Format("hEptC%dmedjn", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmedjn;pt;med JE DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEptCmedjw[i] = new TH2F(TString::Format("hEptC%dmedjw", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmedjw;pt;med JE DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEptCmaxjn[i] = new TH2F(TString::Format("hEptC%dmaxjn", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmaxjn;pt;max JE ECAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEptCmaxjw[i] = new TH2F(TString::Format("hEptC%dmaxjw", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmaxjw;pt;max JE ECAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);

		// max - med for debug only
		hEptCdiffjn[i] = new TH2F(TString::Format("hEptC%ddiffjn", i).Data(),
		                          TString::Format("hEptC%1.1f%1.1fdiffjn;pt;max JE ECAL - med DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, -maxpt, maxpt);
		hEptCdiffjw[i] = new TH2F(TString::Format("hEptC%ddiffjw", i).Data(),
		                          TString::Format("hEptC%1.1f%1.1fdiffjw;pt;max JE ECal - med DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, -maxpt, maxpt);

		//GA
		hEptCmedgn[i] = new TH2F(TString::Format("hEptC%dmedgn", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmedgn;pt;med GA DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEptCmedgw[i] = new TH2F(TString::Format("hEptC%dmedgw", i).Data(),
		                         TString::Format("hEptC_%1.1f_%1.1fmedgw;pt;med GA DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                         nptbins, 0, maxpt, nptbins, 0, maxpt);

	}

	TH2F *hErptCmedjn[7];
	TH2F *hErptCmedjw[7];
	TH2F *hErptCmaxjn[7];
	TH2F *hErptCmaxjw[7];

	TH2F *hErptCdiffjn[7];
	TH2F *hErptCdiffjw[7];

	// jet pT for small r vs. JE med/max DCAL/ECAL
	for (unsigned int i = 0; i < cent.size() / 2; i++)
	{
		hErptCmedjn[i] = new TH2F(TString::Format("hErptC%dmedjn", i).Data(),
		                          TString::Format("hErptC_%1.1f_%1.1fmedjn;pt;med JE DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hErptCmedjw[i] = new TH2F(TString::Format("hErptC%dmedjw", i).Data(),
		                          TString::Format("hErptC_%1.1f_%1.1fmedjw;pt;med JE DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hErptCmaxjn[i] = new TH2F(TString::Format("hErptC%dmaxjn", i).Data(),
		                          TString::Format("hErptC_%1.1f_%1.1fmaxjn;pt;max JE ECAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hErptCmaxjw[i] = new TH2F(TString::Format("hErptC%dmaxjw", i).Data(),
		                          TString::Format("hErptC_%1.1f_%1.1fmaxjw;pt;max JE ECAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);

		hErptCdiffjn[i] = new TH2F(TString::Format("hErptC%ddiffjn", i).Data(),
		                           TString::Format("hErptC%1.1f%1.1fdiffjn;pt;max JE ECAL - med DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                           nptbins, 0, maxpt, nptbins, -maxpt, maxpt);
		hErptCdiffjw[i] = new TH2F(TString::Format("hErptC%ddiffjw", i).Data(),
		                           TString::Format("hErptC%1.1f%1.1fdiffjw;pt;max JE ECal - med DCAL", cent[i * 2], cent[i * 2 + 1]).Data(),
		                           nptbins, 0, maxpt, nptbins, -maxpt, maxpt);

	}

	//patches
	TH2F *hEJEcentn     = new TH2F("hEJEcentn", "hEJEcentn;EJE patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEJEcentw     = new TH2F("hEJEcentw", "hEJEcentw;EJE patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAcentn     = new TH2F("hEGAcentn", "hEGAcentn;EGA patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAcentw     = new TH2F("hEGAcentw", "hEGAcentw;EGA patch;cent", nptbins, 0, maxpt, 100, 0, 100);

	TH2F *hEJEdiffcentn     = new TH2F("hEJEdiffcentn", "hEJEdiffcentn;EJE patch - median DCAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEJEdiffcentw     = new TH2F("hEJEdiffcentw", "hEJEdiffcentw;EJE patch - median DCAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffcentn     = new TH2F("hEGAdiffcentn", "hEGAdiffcentn;EGA patch - median DCAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffcentw     = new TH2F("hEGAdiffcentw", "hEGAdiffcentw;EGA patch - median DCAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	TH2F *hDJEcentn     = new TH2F("hDJEcentn", "hDJEcentn;DJE patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDJEcentw     = new TH2F("hDJEcentw", "hDJEcentw;DJE patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAcentn     = new TH2F("hDGAcentn", "hDGAcentn;DGA patch;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAcentw     = new TH2F("hDGAcentw", "hDGAcentw;DGA patch;cent", nptbins, 0, maxpt, 100, 0, 100);

	TH2F *hDJEdiffcentn     = new TH2F("hDJEdiffcentn", "hDJEdiffcentn;DJE patch - median ECAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDJEdiffcentw     = new TH2F("hDJEdiffcentw", "hDJEdiffcentw;DJE patch - median ECAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffcentn     = new TH2F("hDGAdiffcentn", "hDGAdiffcentn;DGA patch - median ECAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffcentw     = new TH2F("hDGAdiffcentw", "hDGAdiffcentw;DGA patch - median ECAL;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	// event wise trigger info
	//med
	TH2F *hEJEmedn		= new TH2F("hEJEmedn", "hEJEmedn;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEJEmedw		= new TH2F("hEJEmedw", "hEJEmedw;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDJEmedn		= new TH2F("hDJEmedn", "hDJEmedn;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDJEmedw		= new TH2F("hDJEmedw", "hDJEmedw;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAmedn		= new TH2F("hEGAmedn", "hEGAmedn;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAmedw		= new TH2F("hEGAmedw", "hEGAmedw;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAmedn		= new TH2F("hDGAmedn", "hDGAmedn;median;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAmedw		= new TH2F("hDGAmedw", "hDGAmedw;median;cent", nptbins, 0, maxpt, 100, 0, 100);

	//max
	TH2F *hEJEmaxn		= new TH2F("hEJEmaxn", "hEJEmaxn;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEJEmaxw		= new TH2F("hEJEmaxw", "hEJEmaxw;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDJEmaxn		= new TH2F("hDJEmaxn", "hDJEmaxn;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDJEmaxw		= new TH2F("hDJEmaxw", "hDJEmaxw;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAmaxn		= new TH2F("hEGAmaxn", "hEGAmaxn;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hEGAmaxw		= new TH2F("hEGAmaxw", "hEGAmaxw;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAmaxn		= new TH2F("hDGAmaxn", "hDGAmaxn;max;cent", nptbins, 0, maxpt, 100, 0, 100);
	TH2F *hDGAmaxw		= new TH2F("hDGAmaxw", "hDGAmaxw;max;cent", nptbins, 0, maxpt, 100, 0, 100);

	//diff
	TH2F *hEJEdiffmedn		= new TH2F("hEJEdiffmedn", "hEJEdiffmedn;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEJEdiffmedw		= new TH2F("hEJEdiffmedw", "hEJEdiffmedw;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffmedn		= new TH2F("hEGAdiffmedn", "hEGAdiffmedn;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffmedw		= new TH2F("hEGAdiffmedw", "hEGAdiffmedw;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	TH2F *hDJEdiffmedn		= new TH2F("hDJEdiffmedn", "hDJEdiffmedn;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDJEdiffmedw		= new TH2F("hDJEdiffmedw", "hDJEdiffmedw;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffmedn		= new TH2F("hDGAdiffmedn", "hDGAdiffmedn;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffmedw		= new TH2F("hDGAdiffmedw", "hDGAdiffmedw;s+bg - bg;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	TH2F *hEJEdiffmaxmedn		= new TH2F("hEJEdiffmaxmedn", "hEJEdiffmaxmedn;EJE max - DJE med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEJEdiffmaxmedw		= new TH2F("hEJEdiffmaxmedw", "hEJEdiffmaxmedw;EJE max - DJE med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffmaxmedn		= new TH2F("hEGAdiffmaxmedn", "hEGAdiffmaxmedn;EGA max - DGA med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hEGAdiffmaxmedw		= new TH2F("hEGAdiffmaxmedw", "hEGAdiffmaxmedw;EGA max - DGA med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	TH2F *hDJEdiffmaxmedn		= new TH2F("hDJEdiffmaxmedn", "hDJEdiffmaxmedn;DJE max - EJE med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDJEdiffmaxmedw		= new TH2F("hDJEdiffmaxmedw", "hDJEdiffmaxmedw;DJE max - EJE med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffmaxmedn		= new TH2F("hDGAdiffmaxmedn", "hDGAdiffmaxmedn;DGA max - EGA med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);
	TH2F *hDGAdiffmaxmedw		= new TH2F("hDGAdiffmaxmedw", "hDGAdiffmaxmedw;DGA max - EGA med;cent", nptbins * 2, -maxpt, maxpt, 100, 0, 100);

	// correlations between patches
	TH2F *hEGAEJEmedw[7];
	TH2F *hDGADJEmedw[7];
	TH2F *hEGAEJEmaxw[7];
	TH2F *hDGADJEmaxw[7];
	TH2F *hEGAEJEmedn[7];
	TH2F *hDGADJEmedn[7];
	TH2F *hEGAEJEmaxn[7];
	TH2F *hDGADJEmaxn[7];

	// patches vs. median [centbins]
	TH2F *hEJEpDJEmed[7];
	TH2F *hEJEpDGAmed[7];
	TH2F *hDJEpEJEmed[7];
	TH2F *hDJEpEGAmed[7];

	TH2F *hEGApDJEmed[7];
	TH2F *hEGApDGAmed[7];
	TH2F *hDGApEJEmed[7];
	TH2F *hDGApEGAmed[7];

	for (unsigned int i = 0; i < cent.size() / 2; i++)
	{
		hEGAEJEmedw[i] = new TH2F(TString::Format("hEGAEJEmedwC%d", i),
		                          TString::Format("hEGAEJEmedw %1.1f %1.1f;med EGA;med EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGADJEmedw[i] = new TH2F(TString::Format("hDGADJEmedwC%d", i),
		                          TString::Format("hDGADJEmedw %1.1f %1.1f;med DGA;med DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEGAEJEmaxw[i] = new TH2F(TString::Format("hEGAEJEmaxwC%d", i),
		                          TString::Format("hEGAEJEmaxw %1.1f %1.1f;max EGA;max EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGADJEmaxw[i] = new TH2F(TString::Format("hDGADJEmaxwC%d", i),
		                          TString::Format("hDGADJEmaxw %1.1f %1.1f;max DGA;max DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);

		hEGAEJEmedn[i] = new TH2F(TString::Format("hEGAEJEmednC%d", i),
		                          TString::Format("hEGAEJEmedn %1.1f %1.1f;med EGA;med EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGADJEmedn[i] = new TH2F(TString::Format("hDGADJEmednC%d", i),
		                          TString::Format("hDGADJEmedn %1.1f %1.1f;med DGA;med DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEGAEJEmaxn[i] = new TH2F(TString::Format("hEGAEJEmaxnC%d", i),
		                          TString::Format("hEGAEJEmaxn %1.1f %1.1f;max EGA;max EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGADJEmaxn[i] = new TH2F(TString::Format("hDGADJEmaxnC%d", i),
		                          TString::Format("hDGADJEmaxn %1.1f %1.1f;max DGA;max DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);

		// patch - median correlations
		hEJEpDJEmed[i] = new TH2F(TString::Format("hEJEpDJEmedC%d", i),
		                          TString::Format("hEJEpDJEmed %1.1f %1.1f;EJE patch;med DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEJEpDGAmed[i] = new TH2F(TString::Format("hEJEpDGAmedC%d", i),
		                          TString::Format("hEJEpDGAmed %1.1f %1.1f;EJE patch;med DGA", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDJEpEJEmed[i] = new TH2F(TString::Format("hDJEpEJEmedC%d", i),
		                          TString::Format("hDJEpEJEmed %1.1f %1.1f;DJE patch;med EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDJEpEGAmed[i] = new TH2F(TString::Format("hDJEpEGAmedC%d", i),
		                          TString::Format("hDJEpEGAmed %1.1f %1.1f;DJE patch;med EGA", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEGApDJEmed[i] = new TH2F(TString::Format("hEGApDJEmedC%d", i),
		                          TString::Format("hEGApDJEmed %1.1f %1.1f;EGA patch;med DJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hEGApDGAmed[i] = new TH2F(TString::Format("hEGApDGAmedC%d", i),
		                          TString::Format("hEGApDGAmed %1.1f %1.1f;EGA patch;med DGA", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGApEJEmed[i] = new TH2F(TString::Format("hDGApEJEmedC%d", i),
		                          TString::Format("hDGApEJEmed %1.1f %1.1f;DGA patch;med EJE", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
		hDGApEGAmed[i] = new TH2F(TString::Format("hDGApEGAmedC%d", i),
		                          TString::Format("hDGApEGAmed %1.1f %1.1f;DGA patch;med EGA", cent[i * 2], cent[i * 2 + 1]),
		                          nptbins, 0, maxpt, nptbins, 0, maxpt);
	}

	// in case cal=0 the max is ECAL and med is DCAL
	// in case cal=1 the max is DCAL and med is ECAL
	TNtuple *tnpi0jet = 	new TNtuple("tnpi0jet", 	"tnpi0jet", 	"cal:xsec:cent:ptT:jpt:dphi:maxJE:maxGA:medJE:medGA");

	// in case cal=0 the max is ECAL and med is DCAL
	// in case cal=1 the max is DCAL and med is ECAL
	TNtuple *tngjet = 	new TNtuple("tngjet", 	"tngjet", 	"cal:xsec:cent:ptT:jpt:dphi:maxJE:maxGA:medJE:medGA");
	TNtuple *tnghad = 	new TNtuple("tnghad", 	"tnghad", 	"cal:xsec:cent:ptT:hpt:dphi:maxJE:maxGA:medJE:medGA");

	// just to count
	TNtuple *tn   = new TNtuple("tn", "tn", "xsec:cent:maxEJE:maxEJE8x8:maxEGA:medEJE:medEJE8x8:medEGA:maxDJE:maxDJE8x8:maxDGA:medDJE:medDJE8x8:medDGA");

	TNtuple *tnj   = new TNtuple("tnjet", "tnjet", "cal:xsec:cent:jpt:maxJE:maxGA:medJE:medGA");
	TNtuple *tnjr  = new TNtuple("tnjetr", "tnjet", "cal:xsec:cent:jpt:maxJE:maxGA:medJE:medGA");
	TNtuple *tnpi0 = new TNtuple("tnpi0", "tnpi0", "cal:xsec:cent:jpt:maxJE:maxGA:medJE:medGA");
	TNtuple *tng   = new TNtuple("tng", "tng", "cal:xsec:cent:jpt:maxJE:maxGA:medJE:medGA");

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
	std::vector<TLorentzVector> *pjE  = 0;
	std::vector<TLorentzVector> *pjD  = 0;
	std::vector<TLorentzVector> *pjEr = 0;
	std::vector<TLorentzVector> *pjDr = 0;

	std::vector<TLorentzVector> *ptgEJE    = 0;
	std::vector<TLorentzVector> *ptgEJE8x8 = 0;
	std::vector<TLorentzVector> *ptgEGA    = 0;
	std::vector<TLorentzVector> *ptgDJE    = 0;
	std::vector<TLorentzVector> *ptgDJE8x8 = 0;
	std::vector<TLorentzVector> *ptgDGA    = 0;

	std::vector<TLorentzVector> *pjch 	= 0;
	std::vector<TLorentzVector> *pjrch 	= 0;

	std::vector<TLorentzVector> *pch	= 0;
	std::vector<TLorentzVector> *pi0E	= 0;
	std::vector<TLorentzVector> *pi0D	= 0;

	std::vector<TLorentzVector> *gE		= 0;
	std::vector<TLorentzVector> *gD		= 0;

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

		hCentn->Fill(hd.cent);
		hCentw->Fill(hd.cent, hd.xsec);

		tn->Fill(hd.xsec, hd.cent,
		         tg.maxjECAL, tg.maxjECAL8x8, tg.maxgECAL, tg.medjECAL, tg.medjECAL8x8, tg.medgECAL,
		         tg.maxjDCAL, tg.maxjDCAL8x8, tg.maxgDCAL, tg.medjDCAL, tg.medjDCAL8x8, tg.medgDCAL);

		// event trigger
		hEJEmedn->Fill(tg.medjECAL8x8, hd.cent);
		hEJEmedw->Fill(tg.medjECAL8x8, hd.cent, hd.xsec);
		hDJEmedn->Fill(tg.medjDCAL8x8, hd.cent);
		hDJEmedw->Fill(tg.medjDCAL8x8, hd.cent, hd.xsec);

		hEGAmedn->Fill(tg.medgECAL, hd.cent);
		hEGAmedw->Fill(tg.medgECAL, hd.cent, hd.xsec);
		hDGAmedn->Fill(tg.medgDCAL, hd.cent);
		hDGAmedw->Fill(tg.medgDCAL, hd.cent, hd.xsec);

		hEJEmaxn->Fill(tg.maxjECAL, hd.cent);
		hEJEmaxw->Fill(tg.maxjECAL, hd.cent, hd.xsec);
		hDJEmaxn->Fill(tg.maxjDCAL, hd.cent);
		hDJEmaxw->Fill(tg.maxjDCAL, hd.cent, hd.xsec);

		hEGAmaxn->Fill(tg.maxgECAL, hd.cent);
		hEGAmaxw->Fill(tg.maxgECAL, hd.cent, hd.xsec);
		hDGAmaxn->Fill(tg.maxgDCAL, hd.cent);
		hDGAmaxw->Fill(tg.maxgDCAL, hd.cent, hd.xsec);

		hEJEdiffmedn->Fill(tg.medjECAL8x8 - tgbg.medjECAL8x8, hd.cent);
		hEJEdiffmedw->Fill(tg.medjECAL8x8 - tgbg.medjECAL8x8, hd.cent, hd.xsec);
		hDJEdiffmedn->Fill(tg.medjDCAL8x8 - tgbg.medjDCAL8x8, hd.cent);
		hDJEdiffmedw->Fill(tg.medjDCAL8x8 - tgbg.medjDCAL8x8, hd.cent, hd.xsec);
		hEGAdiffmedn->Fill(tg.medgECAL - tgbg.medgECAL, hd.cent);
		hEGAdiffmedw->Fill(tg.medgECAL - tgbg.medgECAL, hd.cent, hd.xsec);
		hDGAdiffmedn->Fill(tg.medgDCAL - tgbg.medgDCAL, hd.cent);
		hDGAdiffmedw->Fill(tg.medgDCAL - tgbg.medgDCAL, hd.cent, hd.xsec);

		hEJEdiffmaxmedn->Fill(tg.maxjECAL - tgbg.medjDCAL, hd.cent);
		hEJEdiffmaxmedw->Fill(tg.maxjECAL - tgbg.medjDCAL, hd.cent, hd.xsec);
		hDJEdiffmaxmedn->Fill(tg.maxjDCAL - tgbg.medjECAL, hd.cent);
		hDJEdiffmaxmedw->Fill(tg.maxjDCAL - tgbg.medjECAL, hd.cent, hd.xsec);
		hEGAdiffmaxmedn->Fill(tg.maxgECAL - tgbg.medgDCAL, hd.cent);
		hEGAdiffmaxmedw->Fill(tg.maxgECAL - tgbg.medgDCAL, hd.cent, hd.xsec);
		hDGAdiffmaxmedn->Fill(tg.maxgDCAL - tgbg.medgECAL, hd.cent);
		hDGAdiffmaxmedw->Fill(tg.maxgDCAL - tgbg.medgECAL, hd.cent, hd.xsec);

		for (unsigned int i = 0; i < cent.size() / 2; i++)
		{
			hEGAEJEmedw[i]->Fill(tg.medgECAL, tg.medjECAL8x8, hd.xsec);
			hDGADJEmedw[i]->Fill(tg.medgDCAL, tg.medjDCAL8x8, hd.xsec);
			hEGAEJEmaxw[i]->Fill(tg.maxgECAL, tg.maxjECAL, hd.xsec);
			hDGADJEmaxw[i]->Fill(tg.maxgDCAL, tg.maxjDCAL, hd.xsec);

			hEGAEJEmedn[i]->Fill(tg.medgECAL, tg.medjECAL8x8);
			hDGADJEmedn[i]->Fill(tg.medgDCAL, tg.medjDCAL8x8);
			hEGAEJEmaxn[i]->Fill(tg.maxgECAL, tg.maxjECAL);
			hDGADJEmaxn[i]->Fill(tg.maxgDCAL, tg.maxjDCAL);
		}

		Int_t icent = 0;
		for (unsigned int ic = 1; ic < cent.size() / 2; ic++)
		{
			if (hd.cent >= cent[ic * 2] && hd.cent < cent[ic * 2 + 1])
			{
				icent = ic;
			}
		}
		//cout << "[i] icent bin: " << icent << " actual: " << hd.cent << endl;

		// jE
		for (std::vector<TLorentzVector>::iterator i = pjE->begin(); i != pjE->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnj->Fill(0, hd.xsec, hd.cent, i->Pt(), tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}

			hEptn->Fill(i->Pt());
			hEptw->Fill(i->Pt(), hd.xsec);
			hEptcentn->Fill(i->Pt(), hd.cent);
			hEptcentw->Fill(i->Pt(), hd.cent, hd.xsec);
			hEptcentmedjn->Fill(i->Pt(), hd.cent, tg.medjDCAL8x8);
			hEptcentmedjw->Fill(i->Pt(), hd.cent, tg.medjDCAL8x8, hd.xsec);
			hEptcentmaxjn->Fill(i->Pt(), hd.cent, tg.maxjDCAL);
			hEptcentmaxjw->Fill(i->Pt(), hd.cent, tg.maxjDCAL, hd.xsec);
			hEptcentmedgn->Fill(i->Pt(), hd.cent, tg.medgDCAL);
			hEptcentmedgw->Fill(i->Pt(), hd.cent, tg.medgDCAL, hd.xsec);
			hEptcentmaxgn->Fill(i->Pt(), hd.cent, tg.maxgDCAL);
			hEptcentmaxgw->Fill(i->Pt(), hd.cent, tg.maxgDCAL, hd.xsec);

			for (unsigned int ic = 0; ic < cent.size() / 2; ic++)
			{
				if (hd.cent >= cent[ic * 2] && hd.cent < cent[ic * 2 + 1])
				{
					hEptCmedjn[ic]->Fill(i->Pt(), tg.medjDCAL8x8);
					hEptCmedjw[ic]->Fill(i->Pt(), tg.medjDCAL8x8, hd.xsec);
					hEptCmaxjn[ic]->Fill(i->Pt(), tg.maxjECAL);
					hEptCmaxjw[ic]->Fill(i->Pt(), tg.maxjECAL, hd.xsec);

					hEptCdiffjn[ic]->Fill(i->Pt(), tg.maxjECAL - tg.medjDCAL8x8);
					hEptCdiffjw[ic]->Fill(i->Pt(), tg.maxjECAL - tg.medjDCAL8x8, hd.xsec);

					hEptCmedgn[ic]->Fill(i->Pt(), tg.medgDCAL);
					hEptCmedgw[ic]->Fill(i->Pt(), tg.medgDCAL, hd.xsec);
				}
			}
		}
		// jEr
		for (std::vector<TLorentzVector>::iterator i = pjEr->begin(); i != pjEr->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnjr->Fill(0, hd.xsec, hd.cent, i->Pt(), tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}

			for (unsigned int ic = 0; ic < cent.size() / 2; ic++)
			{
				if (hd.cent >= cent[ic * 2] && hd.cent < cent[ic * 2 + 1])
				{
					hErptCmedjn[ic]->Fill(i->Pt(), tg.medjDCAL8x8);
					hErptCmedjw[ic]->Fill(i->Pt(), tg.medjDCAL8x8, hd.xsec);
					hErptCmaxjn[ic]->Fill(i->Pt(), tg.maxjECAL);
					hErptCmaxjw[ic]->Fill(i->Pt(), tg.maxjECAL, hd.xsec);

					hErptCdiffjn[ic]->Fill(i->Pt(), tg.maxjECAL - tg.medjDCAL8x8);
					hErptCdiffjw[ic]->Fill(i->Pt(), tg.maxjECAL - tg.medjDCAL8x8, hd.xsec);
				}
			}
		}

		// jD
		for (std::vector<TLorentzVector>::iterator i = pjD->begin(); i != pjD->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnj->Fill(1, hd.xsec, hd.cent, i->Pt(), tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}

			hDptn->Fill(i->Pt());
			hDptw->Fill(i->Pt(), hd.xsec);
			hDptcentn->Fill(i->Pt(), hd.cent);
			hDptcentw->Fill(i->Pt(), hd.cent, hd.xsec);
			hDptcentmedjn->Fill(i->Pt(), hd.cent, tg.medjECAL8x8);
			hDptcentmedjw->Fill(i->Pt(), hd.cent, tg.medjECAL8x8, hd.xsec);
			hDptcentmaxjn->Fill(i->Pt(), hd.cent, tg.maxjECAL);
			hDptcentmaxjw->Fill(i->Pt(), hd.cent, tg.maxjECAL, hd.xsec);
			hDptcentmedgn->Fill(i->Pt(), hd.cent, tg.medgECAL);
			hDptcentmedgw->Fill(i->Pt(), hd.cent, tg.medgECAL, hd.xsec);
			hDptcentmaxgn->Fill(i->Pt(), hd.cent, tg.maxgECAL);
			hDptcentmaxgw->Fill(i->Pt(), hd.cent, tg.maxgECAL, hd.xsec);
		}

		// jDr
		for (std::vector<TLorentzVector>::iterator i = pjDr->begin(); i != pjDr->end(); ++i)
		{
			if (i->Pt() > 10)
			{
				tnjr->Fill(1, hd.xsec, hd.cent, i->Pt(), tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
		}

		// patches
		for (std::vector<TLorentzVector>::iterator i = ptgEJE->begin(); i != ptgEJE->end(); ++i)
		{
			hEJEcentn->Fill(i->E(), hd.cent);
			hEJEcentw->Fill(i->E(), hd.cent, hd.xsec);
			hEJEdiffcentn->Fill(i->E() - tg.medjDCAL8x8, hd.cent);
			hEJEdiffcentw->Fill(i->E() - tg.medjDCAL8x8, hd.cent, hd.xsec);

			hEJEpDJEmed[0]->Fill(i->E(), tg.medjDCAL8x8, hd.xsec);
			hEJEpDGAmed[0]->Fill(i->E(), tg.medgDCAL, hd.xsec);
			hEJEpDJEmed[icent]->Fill(i->E(), tg.medjDCAL8x8, hd.xsec);
			hEJEpDGAmed[icent]->Fill(i->E(), tg.medgDCAL, hd.xsec);
		}
		for (std::vector<TLorentzVector>::iterator i = ptgEGA->begin(); i != ptgEGA->end(); ++i)
		{
			hEGAcentn->Fill(i->E(), hd.cent);
			hEGAcentw->Fill(i->E(), hd.cent, hd.xsec);
			hEGAdiffcentn->Fill(i->E() - tg.medgDCAL, hd.cent);
			hEGAdiffcentw->Fill(i->E() - tg.medgDCAL, hd.cent, hd.xsec);

			hEGApDJEmed[0]->Fill(i->E(), tg.medjDCAL8x8, hd.xsec);
			hEGApDGAmed[0]->Fill(i->E(), tg.medgDCAL, hd.xsec);
			hEGApDJEmed[icent]->Fill(i->E(), tg.medjDCAL8x8, hd.xsec);
			hEGApDGAmed[icent]->Fill(i->E(), tg.medgDCAL, hd.xsec);
		}
		for (std::vector<TLorentzVector>::iterator i = ptgDJE->begin(); i != ptgDJE->end(); ++i)
		{
			hDJEcentn->Fill(i->E(), hd.cent);
			hDJEcentw->Fill(i->E(), hd.cent, hd.xsec);
			hDJEdiffcentn->Fill(i->E() - tg.medjECAL8x8, hd.cent);
			hDJEdiffcentw->Fill(i->E() - tg.medjECAL8x8, hd.cent, hd.xsec);

			hDJEpEJEmed[0]->Fill(i->E(), tg.medjECAL8x8, hd.xsec);
			hDJEpEGAmed[0]->Fill(i->E(), tg.medgECAL, hd.xsec);
			hDJEpEJEmed[icent]->Fill(i->E(), tg.medjECAL8x8, hd.xsec);
			hDJEpEGAmed[icent]->Fill(i->E(), tg.medgECAL, hd.xsec);
		}
		for (std::vector<TLorentzVector>::iterator i = ptgDGA->begin(); i != ptgDGA->end(); ++i)
		{
			hDGAcentn->Fill(i->E(), hd.cent);
			hDGAcentw->Fill(i->E(), hd.cent, hd.xsec);
			hDGAdiffcentn->Fill(i->E() - tg.medgECAL, hd.cent);
			hDGAdiffcentw->Fill(i->E() - tg.medgECAL, hd.cent, hd.xsec);

			hDGApEJEmed[0]->Fill(i->E(), tg.medjECAL8x8, hd.xsec);
			hDGApEGAmed[0]->Fill(i->E(), tg.medgECAL, hd.xsec);
			hDGApEJEmed[icent]->Fill(i->E(), tg.medjECAL8x8, hd.xsec);
			hDGApEGAmed[icent]->Fill(i->E(), tg.medgECAL, hd.xsec);
		}


		// in case cal=0 the max is ECAL and med is DCAL
		// in case cal=1 the max is DCAL and med is ECAL
		//TNtuple *tnpi0jet = new TNtuple("tnpi0jet", "cal:xsec:cent:ptT:jpt:dphi:maxJE:maxGA:medJE:medGA:");
		for (std::vector<TLorentzVector>::iterator i = pi0E->begin(); i != pi0E->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tnpi0->Fill(0, hd.xsec, hd.cent, i->Pt(), tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tnpi0jet->Fill(0, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						               tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
			}
		}
		for (std::vector<TLorentzVector>::iterator i = pi0D->begin(); i != pi0D->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tnpi0->Fill(1, hd.xsec, hd.cent, i->Pt(), tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tnpi0jet->Fill(1, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						               tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
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
				tng->Fill(0, hd.xsec, hd.cent, i->Pt(), tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tngjet->Fill(0, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
				for (std::vector<TLorentzVector>::iterator j = pch->begin(); j != pch->end(); ++j)
				{
					if (j->Pt() > 1 && TMath::Abs(j->Eta()) < 0.9)
					{
						tnghad->Fill(0, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjECAL, tg.maxgECAL, tg.medjDCAL8x8, tg.medgDCAL);
					}
				}
			}
		}
		for (std::vector<TLorentzVector>::iterator i = gD->begin(); i != gD->end(); ++i)
		{
			if (i->Pt() > 5)
			{
				tng->Fill(1, hd.xsec, hd.cent, i->Pt(), tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
			}
			if (i->Pt() > 20)
			{
				for (std::vector<TLorentzVector>::iterator j = pjch->begin(); j != pjch->end(); ++j)
				{
					if (j->Pt() > 10 && TMath::Abs(j->Eta()) < 0.9 - 0.4)
					{
						tngjet->Fill(1, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
					}
				}
				for (std::vector<TLorentzVector>::iterator j = pch->begin(); j != pch->end(); ++j)
				{
					if (j->Pt() > 1 && TMath::Abs(j->Eta()) < 0.9)
					{
						tnghad->Fill(1, hd.xsec, hd.cent, i->Pt(), j->Pt(), j->DeltaPhi(*i),
						             tg.maxjDCAL, tg.maxgDCAL, tg.medjECAL8x8, tg.medgECAL);
					}
				}
			}
		}

	} //end event loop
	fin->Close();
	fout->Write();
}
