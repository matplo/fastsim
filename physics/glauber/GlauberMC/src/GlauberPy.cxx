#include <Riostream.h>
#include <TMath.h>
#include <TEllipse.h>
#include <TRandom.h>
#include <TNamed.h>
#include <TObjArray.h>
#include <TNtuple.h>
#include <TFile.h>
#include <TTree.h>
#include <TF1.h>

#include <AliGlauberNucleon.h>

#include "GlauberPy.h"

using std::flush;
ClassImp(GlauberPy);

//______________________________________________________________________________
GlauberPy::GlauberPy(Option_t* NA, Option_t* NB, Double_t xsect) 
  : AliGlauberMC(NA, NB, xsect)
{

  SetName(Form("GlauberPy_%s_%s", fANucleus.GetName(), fBNucleus.GetName()));
  SetTitle(Form("Glauber Py %s+%s Version", fANucleus.GetName(), fBNucleus.GetName()));
}

//______________________________________________________________________________
GlauberPy::~GlauberPy()
{
  //dtor
  delete fnt;
}

//______________________________________________________________________________
GlauberPy::GlauberPy(const GlauberPy& in)
  : AliGlauberMC(in)
{
  ;
}

//______________________________________________________________________________
GlauberPy& GlauberPy::operator=(const GlauberPy& in)
{
  return *this;
}

//______________________________________________________________________________
Bool_t GlauberPy::CalcEvent(Double_t bgen)
{
  // prepare event

  if (fDoFluc) {
    if (!fSigFluc) {
      fSigFluc = new TF1("fSigFluc", "[0]*x/[3]/(x/[3]+[1])*exp(-((x/[1]/[3]-1)/[2])^2)", 0, 250);
      fSigFluc->SetParameters(1, fSig0, fOmega, fLambda);
      cout << "Setting fluc: " << fSig0 << " " << fOmega << " " << fLambda << endl;
    }
  }

  fANucleus.ThrowNucleons(-bgen / 2.);
  fNucleonsA = fANucleus.GetNucleons();
  fAN = fANucleus.GetN();
  fQAN = fAN * 3;
  //fAN = 3 * fANucleus.GetN(); // for Pb, Number of quark = 3*208;
  for (Int_t i = 0; i < fAN; i++)
  {
    AliGlauberNucleon *nucleonA = (AliGlauberNucleon*)(fNucleonsA->UncheckedAt(i));
    nucleonA->SetInNucleusA();
    nucleonA->SetSigNN(fXSect);
    if (fDoFluc)
      nucleonA->SetSigNN(fSigFluc->GetRandom());
  }
  fBNucleus.ThrowNucleons(bgen / 2.);
  fNucleonsB = fBNucleus.GetNucleons();
  //fBN = 3 * fBNucleus.GetN(); // Number of quark = number of nucleus*3;
  fBN = fBNucleus.GetN();
  fQBN = fBN * 3;
  for (Int_t i = 0; i < fBN; i++)
  {
    AliGlauberNucleon *nucleonB = (AliGlauberNucleon*)(fNucleonsB->UncheckedAt(i));
    nucleonB->SetInNucleusB();
    nucleonB->SetSigNN(fXSect);
    if (fDoFluc)
      nucleonB->SetSigNN(fSigFluc->GetRandom());
  }

  if (fDoFluc) {
    if (!fSigFluc) {
      fSigFluc = new TF1("fSigFluc", "[0]*x/[3]/(x/[3]+[1])*exp(-((x/[1]/[3]-1)/[2])^2)", 0, 250);
      fSigFluc->SetParameters(1, fSig0, fOmega, fLambda);
      cout << "Setting fluc: " << fSig0 << " " << fOmega << " " << fLambda << endl;
    }
    fXSect = fSigFluc->GetRandom();
  }
  // "ball" diameter = distance at which two balls interact
  Double_t d2 = (Double_t)fXSect / (TMath::Pi() * 10); // in fm^2

  Double_t bNN   = 0;
  Double_t Nco   = 0;
  Double_t Ncohc = 0; // hard core

  // for each of the A nucleons in nucleus B
  for (Int_t i = 0; i < fBN; i++)
  {
    AliGlauberNucleon *nucleonB = (AliGlauberNucleon*)(fNucleonsB->UncheckedAt(i));
    for (Int_t j = 0 ; j < fAN ; j++)
    {
      AliGlauberNucleon *nucleonA = (AliGlauberNucleon*)(fNucleonsA->UncheckedAt(j));
      Double_t dx = nucleonB->GetX() - nucleonA->GetX();
      Double_t dy = nucleonB->GetY() - nucleonA->GetY();
      Double_t dij = dx * dx + dy * dy;
      if (fDoFluc) {
        //fXSect = nucleonA->GetSigNN();
        //fXSect = (nucleonA->GetSigNN()+nucleonB->GetSigNN())/2.;
        fXSect = TMath::Max(nucleonA->GetSigNN(), nucleonB->GetSigNN());
        d2 = (Double_t)fXSect / (TMath::Pi() * 10); // in fm^2
      }
      if (dij < d2)
      {
        bNN += dij;
        ++Nco;
        nucleonB->Collide();
        nucleonA->Collide();
        if (dij < d2 / 4)
          ++Ncohc;
      }
    }
  }

  if (Nco > 0) {
    fNcollw = Ncohc;
    fBNN = bNN / Nco;
  } else {
    fNcollw = 0;
    fBNN    = 0.;
  }

  if (Nco > 0)
    fBNN = bNN / Nco;
  else
    fBNN = 0.;
  return CalcResults(bgen);
}

//---------------------------------------------------------------------------------
void GlauberPy::Reset()
{
  //delete the ntuple
  delete fnt;
  fnt = NULL;
}

void GlauberPy::Run(Int_t nevents)
{
  
}