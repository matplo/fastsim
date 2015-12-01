#include "RndSource.h"

#include <TH1F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTimeStamp.h>
#include <TFolder.h>
#include <TRandom.h>

ClassImp(RndSource)

#include <iostream>
using namespace std;

RndSource::RndSource(const char *name, const char *title, UInt_t seed)
  : TFolder(name, title)
  , fHSrc(0)
  , fHRnmd(0)
  , fHNormalized(0)
  , fHIntegrals(0)
  , fRndGen(new TRandom(seed))
{
  ;
}

// RndSource::RndSource(const RndSource&t)
//   : TFolder()
//   , fHSrc(0)
//   , fHRnmd(0)
//   , fHNormalized(0)
//   , fHIntegrals(0)
//   , fRndGen(t.fRndGen)
// {
//   ;
// }

RndSource::~RndSource()
{
  DeleteHistograms();
}

void RndSource::DeleteHistograms()
{
  this->Remove(fHSrc);
  if (fHSrc)
    delete fHSrc;

  this->Remove(fHRnmd);
  if (fHRnmd)
    delete fHRnmd;
  
  this->Remove(fHNormalized);
  if (fHNormalized)
    delete fHNormalized;

  this->Remove(fHIntegrals);
  if (fHIntegrals)
    delete fHIntegrals;
}

void RndSource::SetSource(TH1 *h)
{  
  DeleteHistograms();

  TTimeStamp st;

  Int_t nbins = h->GetNbinsX();
  TString newName = h->GetName();
  newName.ReplaceAll("/","_");
  newName += Form("_%u_%d", this->GetUniqueID(), st.GetNanoSec());

  newName += "_copy";
  fHSrc = (TH1*)h->Clone(newName.Data());
  fHSrc->SetTitle(newName.Data());
  fHSrc->SetDirectory(0);
  this->Add(fHSrc);

  newName += "_normalized";
  fHNormalized = (TH1*)h->Clone(newName.Data());
  fHNormalized->SetDirectory(0);
  fHNormalized->SetTitle(newName.Data());
  fHNormalized->Scale(1./fHNormalized->Integral());
  this->Add(fHNormalized);

  newName += "_integrals";
  fHIntegrals = new TH1D(newName.Data(), newName.Data(), nbins, 0., 1.);
  fHIntegrals->SetDirectory(0);
  this->Add(fHIntegrals);

  Double_t *binLowEdges = new Double_t[nbins+1];
  binLowEdges[0] = 0.;
  for (Int_t i = 0; i < nbins; i++)
    {
      Double_t xmin = 1;
      Double_t xmax = i+1;
      fHIntegrals->SetBinContent(i+1, fHNormalized->Integral(xmin, xmax));
      binLowEdges[i+1] = fHNormalized->Integral(xmin, xmax);
    }
  
  newName += "_HRnmd";
  fHRnmd = new TH1F(newName.Data(), newName.Data(), nbins, binLowEdges);
  fHRnmd->SetDirectory(0);
  this->Add(fHRnmd);
  for (Int_t i = 0; i < nbins; i++)
    {
      fHRnmd->SetBinContent(i + 1, fHSrc->GetBinCenter(i + 1));
    }  
}

void RndSource::SetSource(TF1 *f)
{
  //f->SetNDF(1000);
  f->SetNpx(1000);
  TH1 *h = f->GetHistogram();
  RndSource::SetSource(h);
}

void RndSource::DrawOnCanvases(Bool_t newC)
{
  TString tcname = Form("Canvas_%s", this->GetName());
  tcname.ReplaceAll("/","_");
  TVirtualPad *tc = 0;
  if (newC)
    {
      tc = new TCanvas(tcname.Data(), tcname.Data());
    }
  else
    {
      tc = gPad;
    }
  tc->Divide(2,2);
  tc->cd(1);
  fHSrc->SetMarkerStyle(20);
  fHSrc->SetMarkerSize(0.7);
  fHSrc->DrawCopy();
  tc->cd(1)->SetGridx();
  tc->cd(1)->SetGridy();

  tc->cd(3);
  fHNormalized->SetMarkerStyle(20);
  fHNormalized->SetMarkerSize(0.7);
  fHNormalized->DrawCopy();
  tc->cd(3)->SetGridx();
  tc->cd(3)->SetGridy();

  tc->cd(2);
  fHIntegrals->SetMarkerStyle(20);
  fHIntegrals->SetMarkerSize(0.7);
  fHIntegrals->DrawCopy();
  tc->cd(2)->SetGridx();
  tc->cd(2)->SetGridy();

  tc->cd(4);
  fHRnmd->SetMarkerStyle(20);
  fHRnmd->SetMarkerSize(0.7);
  fHRnmd->DrawCopy();
  tc->cd(4)->SetGridx();
  tc->cd(4)->SetGridy();
}

Double_t RndSource::RndmFromSource()
{
  Int_t bin = fHRnmd->FindBin(fRndGen->Rndm());
  return fHRnmd->GetBinContent(bin);
}

TH1 *RndSource::Smear(TH1* hsrc, TH1 *hsmear, Double_t statmult,
		      Double_t ptCutOffMin, Double_t ptCutOffMax)
{
  RndSource rnd("tmpRnd");
  rnd.SetSource(hsmear);
  return RndSource::Smear(hsrc, &rnd, statmult, ptCutOffMin, ptCutOffMax);  
}

TH1 *RndSource::Smear(TH1* hsrc, TF1 *fun, Double_t statmult,
		      Double_t ptCutOffMin, Double_t ptCutOffMax)
{
  RndSource rnd("tmpRnd");
  rnd.SetSource(fun);
  //rnd.DrawOnCanvases();
  return RndSource::Smear(hsrc, &rnd, statmult, ptCutOffMin, ptCutOffMax);
}

TH1 *RndSource::Smear(TF1* fsrc, TH1 *hsmear, Double_t statmult,
		      Double_t ptCutOffMin, Double_t ptCutOffMax)
{
  //fsrc->SetNDF(1000);
  fsrc->SetNpx(1000);
  TH1 *hsrc = fsrc->GetHistogram();
  RndSource rnd("tmpRnd");
  rnd.SetSource(hsmear);
  return RndSource::Smear(hsrc, &rnd, statmult, ptCutOffMin, ptCutOffMax);  
}

TH1 *RndSource::Smear(TF1* fsrc, TF1 *fun, Double_t statmult,
		      Double_t ptCutOffMin, Double_t ptCutOffMax)
{
  //fsrc->SetNDF(1000);
  fsrc->SetNpx(1000);
  TH1 *hsrc = fsrc->GetHistogram();
  RndSource rnd("tmpRnd");
  rnd.SetSource(fun);
  //rnd.DrawOnCanvases();
  return RndSource::Smear(hsrc, &rnd, statmult, ptCutOffMin, ptCutOffMax);
}

TH1 *RndSource::Smear(TH1* hsrc, RndSource *rnd, Double_t statmult,
		      Double_t ptCutOffMin, Double_t ptCutOffMax)
{
  TTimeStamp stamp;
  TString newName = hsrc->GetName();
  newName += "_smeared";
  newName += Form("_%d_%d", stamp.GetDate(), stamp.GetTime());
  newName.ReplaceAll("/", "_");
  
  TH1 *hresult = (TH1 *)hsrc->Clone(newName.Data());
  hresult->SetTitle(newName.Data());
  hresult->Reset("ICEM");
  Int_t ibins = hsrc->GetNbinsX();
  for (Int_t i = 0; i < ibins+1; i++)
    {
      Double_t ix = hsrc->GetBinCenter(i+1);
      Double_t iter = hsrc->GetBinContent(i+1) * statmult;
      if (ix < ptCutOffMin || ix > ptCutOffMax)
	continue;
      if ( iter >= 1)
	{
	  for (Int_t ic = 0; ic < iter; ic++)
	    {
	      if (ic % 1000 == 0)
		cout << Form("\r[i] Bin %3d/%3d %3d/%3.0f", i, ibins, ic, iter); cout.flush();
	      //hresult->Fill(ix * (1. + rnd->RndmFromSource()), 1./statmult);
	      hresult->Fill(ix + rnd->RndmFromSource(), 1./statmult);
	    }
	}
    }
  cout << endl;
  return hresult;
}
