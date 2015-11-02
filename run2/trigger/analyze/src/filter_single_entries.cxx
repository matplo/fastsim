#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TSystem.h>
#include <TFile.h>
#include <TList.h>
#include <TKey.h>
#include <TClass.h>

#include <iostream>
using namespace std;

const char *getArg(const char *what, int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return argv[i + 1];
	}
	return "";
}

double getArgD(const char *what, int argc, char **argv, double defret = 0.0)
{
	double retval = defret;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return strtod(argv[i + 1], 0);
		//return std::stod(argv[i + 1]);
	}
	return defret;
}

void filter_single_entries_h(TH1 *h, TH1 *href = 0, Double_t thr = 10)
{
	if (href == 0)
		href = h;
	Int_t nfiltered = 0;
	for (Int_t ib = 1; ib < h->GetNbinsX() + 1; ib++)
	{
		if ((href->GetBinContent(ib) > 0) && (href->GetBinContent(ib) < thr))
		{
			h->SetBinContent(ib, 0);
			h->SetBinError(ib, 0);
			nfiltered++;
		}
	}
	if (nfiltered > 0)
		cout << "    " << h->IsA()->GetName() << " " << h->GetName() << " filtered: " << nfiltered << endl;
}

void filter_single_entries_h(TH2 *h, TH2 *href = 0, Double_t thr = 10)
{
	if (href == 0)
		href = h;
	Int_t nfiltered = 0;
	for (Int_t ibx = 1; ibx < h->GetNbinsX() + 1; ibx++)
	{
		for (Int_t iby = 1; iby < h->GetNbinsY() + 1; iby++)
		{
			if (href->GetBinContent(ibx, iby) > 0 && href->GetBinContent(ibx, iby) < thr)
			{
				h->SetBinContent(ibx, iby, 0);
				h->SetBinError(ibx, iby, 0);
				nfiltered++;
			}
		}
	}
	if (nfiltered > 0)
		cout << "    " << h->IsA()->GetName() << " " << h->GetName() << " filtered: " << nfiltered << endl;
}

void filter_single_entries_h(TH3 *h, TH3 *href = 0, Double_t thr = 10)
{
	if (href == 0)
		href = h;
	Int_t nfiltered = 0;
	for (Int_t ibx = 1; ibx < h->GetNbinsX() + 1; ibx++)
	{
		for (Int_t iby = 1; iby < h->GetNbinsY() + 1; iby++)
		{
			for (Int_t ibz = 1; ibz < h->GetNbinsZ() + 1; ibz++)
			{
				if (href->GetBinContent(ibx, iby, ibz) > 0 && href->GetBinContent(ibx, iby, ibz) < thr)
				{
					h->SetBinContent(ibx, iby, ibz, 0);
					h->SetBinError(ibx, iby, ibz, 0);
					nfiltered++;
				}
			}
		}
	}
	if (nfiltered > 0)
		cout << "    " << h->IsA()->GetName() << " " << h->GetName() << " filtered: " << nfiltered << endl;
}

void filter_singles_entries_file(TString &infname, TString &outfname, Double_t thr = 10)
{
	cout << "[i] filtering: " << infname << endl;
	cout << "           to: " << outfname << endl;
	cout << "    threshold: " << thr << endl;

	gSystem->CopyFile(infname.Data(), outfname.Data(), kTRUE);

	TFile *f = new TFile(outfname.Data(), "update");
	TList *keys = f->GetListOfKeys();
	TList *outL = new TList();
	for (Int_t i = 0; i < keys->GetSize(); i++)
	{
		TKey *key       = (TKey*)keys->At(i);
		TString name    = key->GetName();
		TString nameref = name;
		TObject *obj    = f->Get(name);
		TObject *objref = 0;
		Int_t last      = name.Length();
		if (last < 4)
			continue;
		if (name[last - 2] == 'C')
		{
			if (name[last - 3] == 'w')
				nameref = nameref.Replace(last - 3, 1, 'n');
			else
				continue;
		}
		else
		{
			if (name[last - 1] == 'w')
				nameref = nameref.Replace(last - 1, 1, 'n');
			else
				continue;

		}
		TString clName = key->GetClassName();
		//cout << "    " << clName << " " << name << " " << nameref << endl;
		if (clName.Contains("TH1"))
		{
			TH1 *h    = (TH1*)f->Get(name.Data());
			TH1 *href = (TH1*)f->Get(nameref.Data());
			filter_single_entries_h(h, href, thr);
			outL->Add(h);
		}
		if (clName.Contains("TH2"))
		{
			TH2 *h    = (TH2*)f->Get(name.Data());
			TH2 *href = (TH2*)f->Get(nameref.Data());
			filter_single_entries_h(h, href, thr);
			outL->Add(h);
		}
		if (clName.Contains("TH3"))
		{
			TH3 *h    = (TH3*)f->Get(name.Data());
			TH3 *href = (TH3*)f->Get(nameref.Data());
			filter_single_entries_h(h, href, thr);
			outL->Add(h);
		}
	}
	f->cd();
	for (Int_t i = 0; i < outL->GetEntries(); i++)
	{
		outL->At(i)->Write();
	}
	//f->Write();
	f->Purge();
	f->Close();

}

int main ( int argc, char *argv[] )
{
	cout << "[i] this is filter_single_entries" << endl;
	TString infname  = getArg("--in", argc, argv);
	TString outfname = getArg("--out", argc, argv);
	if (outfname.Length() < 1)
	{
		outfname = infname;
		//outfname = outfname.ReplaceAll(".root", "_filtered.root");
		TString dname = gSystem->DirName(infname);
		if (dname.Length() <= 0)
			dname = ".";
		outfname = TString::Format("%s/%s-%s", dname.Data(), "filtered", gSystem->BaseName(infname));
	}

	if (infname.Length() < 1)
	{
		cout << "[w] input file name is short:" << infname.Data() << endl;
	}

	if (gSystem->AccessPathName(infname.Data()) == kFALSE)
	{
		Double_t thr = getArgD("--thr", argc, argv, 1.);
		filter_singles_entries_file(infname, outfname, thr);
	}
	else
	{
		cout << "[e] unable to access input: " << infname << endl;
	}
	cout << "[i] filter_singles_entries - done." << endl;
	return 0;
}
