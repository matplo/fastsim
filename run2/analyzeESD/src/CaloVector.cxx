#include "CaloVector.h"

ClassImp(CaloVector);

#include <iostream>
using namespace std;

CaloVector::CaloVector()
: TObject()
, fPhi(0)
, fEta(0)
, fE(0)
, fDet(-1)
, fA(0)
{
	;
}

CaloVector::CaloVector(const CaloVector &v)
: TObject()
, fPhi(v.fPhi)
, fEta(v.fEta)
, fE(v.fE)
, fDet(v.fDet)
, fA(v.fA)
{
	;
}

CaloVector::CaloVector(Double_t eta, Double_t phi, Double_t e, Int_t det, Double_t a)
: TObject()
, fPhi(phi)
, fEta(eta)
, fE(e)
, fDet(det)
, fA(a)
{
	;
}

CaloVector::~CaloVector()
{
	;
}

Bool_t CaloVector::IsEMCAL02pi()
{
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 1.40413) && (fPhi < 3.26149) );
}

Bool_t CaloVector::IsDCAL02pi()
{
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 4.54573) && (fPhi < 5.70495) );
}

Bool_t CaloVector::IsEMCAL()
{
	// this is for -pi - pi
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 1.40413 - PI ) && (fPhi < 3.26149 - PI ) );
}

Bool_t CaloVector::IsDCAL()
{
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 4.54573 - PI ) && (fPhi < 5.70495 - PI ) );
}

void CaloVector::ResetPhi()
{
	if (fPhi < 0)
		fPhi = TVector2::Phi_0_2pi(fPhi);
}

CaloVector & CaloVector::operator = (const CaloVector &v)
{
	fEta = v.fEta;
	fPhi = v.fPhi;
	fE   = v.fE;
	fDet = v.fDet;
	fA   = v.fA;
	ResetPhi();
	return *this;
}

Bool_t CaloVector::operator == (const CaloVector & v) const
{
	return ( fEta == v.fEta && fPhi == v.fPhi && fE == v.fE);
}

void CaloVector::GetEtaPhiE(Double_t &eta, Double_t &phi, Double_t &e) const
{
	phi = fPhi;
	eta = fEta;
	e   = fE;
}

void CaloVector::SetEtaPhiE(Double_t eta, Double_t phi, Double_t e)
{
	fPhi = phi;
	fEta = eta;
	fE   = e;
	ResetPhi();
	fDet = GetDet02pi();
}

Int_t CaloVector::GetDet()
{
	fDet = -1;
	if (IsEMCAL()) fDet = 0;
	if (IsDCAL())  fDet = 1;
	return fDet;
}

Int_t CaloVector::GetDet02pi()
{
	fDet = -1;
	if (IsEMCAL02pi()) fDet = 0;
	if (IsDCAL02pi())  fDet = 1;
	// cout << "setting det to " << fDet << endl;
	return fDet;
}

void CaloVector::GetTLV(TLorentzVector &v)
{
	Double_t pT = fE / TMath::CosH(fEta);
	v.SetPtEtaPhiE(pT, fEta, fPhi, fE);
}

Double_t CaloVector::Pt()
{
	return fE / TMath::CosH(fEta);
}
