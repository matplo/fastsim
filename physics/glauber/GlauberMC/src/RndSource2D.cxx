#include "RndSource2D.h"

#include <TH1.h>
#include <TF1.h>
#include <TH2.h>
#include <TF2.h>
#include <TCanvas.h>
#include <TString.h>
#include <TTimeStamp.h>
#include <TList.h>

#include "RndSource.h"

#include <iostream>
#include <cstdlib>

using namespace std;

ClassImp(RndSource2D)

RndSource2D::RndSource2D(const char *name, const char *title)
  : TFolder(name, title)
  , hSrc2D(0)
  , rnds(new TList())
{
  rnds->SetOwner(kFALSE);
  this->Add(rnds);
}

RndSource2D::~RndSource2D()
{
  ;
}

RndSource *RndSource2D::GetRndSource(Int_t i) 
{
  return (RndSource*)rnds->At(i);
}

void RndSource2D::SetSource(TH2 *h)
{  
  TTimeStamp st;

  TString hname = Form("%s_%d_clone2D", h->GetName(), st.GetNanoSec());
  hSrc2D = (TH2*)h->Clone(hname.Data());
  hSrc2D->SetDirectory(0);

  Int_t nbinsX = hSrc2D->GetNbinsX();
  rnds->Clear();
  RndSource *tmp = 0;
  for (Int_t ix = 0; ix < nbinsX; ix++)
    {
      TString pyname = Form("%s_projY_pxbin_%d", hSrc2D->GetName(), ix+1);
      TH1D* py = hSrc2D->ProjectionY(pyname.Data(), ix+1, ix+1);
      pyname += "_Source";

      tmp = new RndSource(pyname.Data(), pyname.Data());
      tmp->SetSource(py);
      this->Add(tmp);
      rnds->AddLast(tmp);

      //       cout << Form("[i] New RndSource : %s at 0x%x %d", 
      // 		   tmp->GetName(),
      // 		   tmp, ix) << endl;
      
      delete py;
      py = 0;
    }

  cout << Form("[i] List of sources has : %d entries", rnds->GetEntries()) << endl;
}

void RndSource2D::SetSource(TF2 *f)
{
  f->SetNpx(1000);
  f->SetNpy(1000);
  TH1 *h = f->GetHistogram();
  if (h->InheritsFrom("TH2"))
    {
      TH2 *htmp = (TH2*)h;
      this->SetSource(htmp);
    }
  else
    {
      cerr << "[e] Unable to set the source!" << endl;
    }
}

void RndSource2D::DrawOnCanvases(Int_t ibinX, Bool_t newC)
{
  if (ibinX <= hSrc2D->GetNbinsX() && ibinX > 0)
    {
      RndSource *tmp = (RndSource *)rnds->At(ibinX-1);
      if (tmp)
	{
	  tmp->DrawOnCanvases(newC);
	  cerr << "[i] Drawing " << tmp << " " << ibinX << endl;
	}
      else
	{
	  cerr << "[e] Something is really wrong!" << endl;
	  exit(-1);
	}
    }  
}

void RndSource2D::DrawOnCanvases(Double_t valx, Bool_t newC)
{
  Int_t ibinX = hSrc2D->GetXaxis()->FindBin(valx);
  this->DrawOnCanvases(ibinX, newC);
}

Double_t RndSource2D::RndmFromSource(Double_t atvalX)
{
  Double_t rndVal = 0;
  Int_t ibinX = hSrc2D->GetXaxis()->FindBin(atvalX);
  if (ibinX <= hSrc2D->GetNbinsX() && ibinX > 0)
    {
      RndSource *tmp = (RndSource *)rnds->At(ibinX-1);
      if (tmp)
	rndVal = tmp->RndmFromSource();
      else
	{
	  cerr << "[e] Something is really wrong!" << endl;
	  exit(-1);
	}
    }
  else
    {
      cerr << "[e] Wrong bin " << ibinX << " of val " << atvalX << endl;
      exit(-1);
    }
  return rndVal;
}

//

