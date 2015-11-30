#include "CaloVector.h"

ClassImp(CaloVector);

CaloVector::CaloVector()
: TObject()
, fPhi(0)
, fEta(0)
, fE(0)
, fDet(-1)
{
	;
}

CaloVector::CaloVector(const CaloVector &v)
: TObject()
, fPhi(v.fPhi)
, fEta(v.fEta)
, fE(v.fE)
, fDet(v.fDet)
{
	;
}

CaloVector::CaloVector(Double_t eta, Double_t phi, Double_t e, Int_t det)
: TObject()
, fPhi(phi)
, fEta(eta)
, fE(e)
, fDet(det)
{
	;
}

CaloVector::~CaloVector()
{
	;
}
