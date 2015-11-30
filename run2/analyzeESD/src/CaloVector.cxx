#include "CaloVector.h"

ClassImp(CaloVector);

CaloVector::CaloVector()
: TObject()
, fPhi(0)
, fEta(0)
, fE(0)
{
	;
}

CaloVector::CaloVector(const CaloVector &v)
: TObject()
, fPhi(v.fPhi)
, fEta(v.fEta)
, fE(v.fE)
{
	;
}

CaloVector::CaloVector(Double_t eta, Double_t phi, Double_t e)
: TObject()
, fPhi(phi)
, fEta(eta)
, fE(e)
{
	;
}

CaloVector::~CaloVector()
{
	;
}
