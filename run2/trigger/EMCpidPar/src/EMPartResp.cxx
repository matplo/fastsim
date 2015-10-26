#include <EMPartResp.h>
#include <TH2F.h>
#include <TString.h>
#include <TFile.h>

#include <TDatabasePDG.h>
#include <TParticlePDG.h>

#include <iostream>
using namespace std;

ClassImp(EMPartResp)

EMPartResp::EMPartResp()
	: TNamed("EMPartResp", "EMPartResp")
	, fpBins(0)
	, fpids()
	, fhpE()
	, fLproj(new TList())
	, fout(0)
{
	fLproj->SetOwner(kTRUE);

	SetBins();
	SetPids();

	TDatabasePDG db;
	TString hname, htitle;

	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		TParticlePDG *ppdg = db.GetParticle(fpids.GetAt(i));
		TString pname = "unknown";
		if (ppdg)
		{
			pname = ppdg->GetName();
		}
		hname    = TString::Format("hepp_pdg_%1.0f", fpids.GetAt(i));
		htitle   = TString::Format("pdg %1.0f %s;p;E/p", fpids.GetAt(i), pname.Data());
		fhpEp[i] = new TH2F(hname, htitle, fpBins.GetSize()-1, fpBins.GetArray(), 1000, 0, 10);
		hname    = TString::Format("hep_pdg_%1.0f", fpids.GetAt(i));
		htitle   = TString::Format("pdg %1.0f %s;p;E", fpids.GetAt(i), pname.Data());
		fhpE[i]  = new TH2F(hname, htitle, fpBins.GetSize()-1, fpBins.GetArray(), fpBins.GetSize()-1, fpBins.GetArray());
	}

}

EMPartResp::EMPartResp(const char *fname)
	: TNamed("EMPartResp", "EMPartResp")
	, fpBins(0)
	, fpids()
	, fhpE()
	, fLproj(new TList())
	, fout()
{
	fLproj->SetOwner(kTRUE);

	SetBins();
	SetPids();

	TFile *fin = TFile::Open(fname);
	TDatabasePDG db;
	TString hname, hnamecl, htitle;

	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		TParticlePDG *ppdg = db.GetParticle(fpids.GetAt(i));
		TString pname = "unknown";
		if (ppdg)
		{
			pname = ppdg->GetName();
		}
		hname    = TString::Format("hepp_pdg_%1.0f", fpids.GetAt(i));
		hnamecl  = TString::Format("hepp_pdg_%1.0f_clone", fpids.GetAt(i));
		fhpEp[i] = (TH2F*)fin->Get(hname)->Clone(hnamecl);
		fhpEp[i]->SetDirectory(0);
		hname    = TString::Format("hep_pdg_%1.0f", fpids.GetAt(i));
		hnamecl  = TString::Format("hep_pdg_%1.0f_clone", fpids.GetAt(i));
		fhpE[i]  = (TH2F*)fin->Get(hname)->Clone(hnamecl);
		fhpE[i]->SetDirectory(0);
	}
	fin->Close();
}

void EMPartResp::SetPids()
{
	Int_t cpids[] = 
	{
		 11,  13,  22,  111,  211,  221,  321,  2212,  2112,
		-11, -13, -22, -111, -211, -221, -321, -2212, -2112
	};
	fpids.Set(18, cpids);
}

void EMPartResp::SetBins()
{
	const Int_t npbins = 14;
	Double_t bins[npbins + 1] = { 0.,   0.5,  1.,   2.,   3.,
	                              5.,  10.,  20.,  40.,  60.,
	                             90., 120., 150., 200., 300.
	                            };

	fpBins.Set(npbins + 1, &bins[0]);

	//for (int i = 0; i < fpBins.GetSize() - 1; ++i)
	//{
	//	cout << "[i] bin: " << i
	//	     << "    " << fpBins[i] << " " << fpBins[i + 1]
	//	     << endl;
	//}
}

EMPartResp::~EMPartResp()
{
	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		delete fhpE[i];
		delete fhpEp[i];
	}
	delete fLproj;
	if (fout)
	{
		fout->Delete();
	}
}

void EMPartResp::Fill(Int_t pdg, Double_t p, Double_t E)
{
	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		if (pdg == fpids[i])
		{
			fhpEp[i]->Fill(p, E / p);
			fhpE[i]->Fill(p, E);
		}
	}
}

Double_t EMPartResp::GetEop(Int_t pdg, Double_t p, Bool_t noalter)
{
	Double_t retval = 0;
	Double_t pchecked = 0;
	TString hname;
	Int_t pbin = 0;
	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		if (pdg == fpids[i])
		{
			pchecked = p;
			if (p > fhpEp[i]->GetXaxis()->GetXmax())
			{
				pchecked = fpBins[fpBins.GetSize() - 1] + 1.;
				//cout << "[w] p out of bounds " << p << " reset to:" << pchecked << endl;
			}
			pbin = fhpEp[i]->GetXaxis()->FindBin(pchecked);
			hname = TString::Format("hepp_pdg_%1.0f_clone_pbin_%d", fpids.GetAt(i), pbin);
			TH1D *hproj = (TH1D*)fLproj->FindObject(hname);
			if (hproj == 0)
			{
				hproj = fhpEp[i]->ProjectionY(hname, pbin, pbin);
				fLproj->Add(hproj);
			}
			retval = hproj->GetRandom();
			//cout << "[i] return E =" << retval << " hist: " << hproj->GetName() << endl;
			return retval;
		}
	}
	if (noalter == kFALSE)
		return GetEop(211, p, kTRUE); //return pion E/p
	else
		return 0;
}

void EMPartResp::WriteToFile(const char *fname)
{
	fout = new TFile(fname, "RECREATE");
	fout->cd();
	for (Int_t i = 0; i < fpids.GetSize(); i++)
	{
		fhpEp[i]->Write();
		fhpE[i]->Write();
	}
	fout->Close();
}
