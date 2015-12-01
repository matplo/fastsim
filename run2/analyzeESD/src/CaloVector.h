#ifndef CALOVECTOR_HH
#define CALOVECTOR_HH

#include <TObject.h>
#include <TLorentzVector.h>

#define PI 3.14159265358979312

class CaloVector : public TObject
{
public:
	CaloVector();
	CaloVector(const CaloVector &);
	CaloVector(Double_t eta, Double_t phi, Double_t e, Int_t det, Double_t a);
	virtual ~CaloVector();

	void SetEtaPhiE(Double_t eta, Double_t phi, Double_t e);
	void GetEtaPhiE(Double_t &eta, Double_t &phi, Double_t &e) const;
	void GetTLV(TLorentzVector &v);
	TLorentzVector TLV() { TLorentzVector v; GetTLV(v); return v;}
	Double_t Phi() 	{return fPhi;}
	Double_t Eta() 	{return fEta;}
	Double_t E()   	{return fE;}
	Double_t Pt();
	Int_t 	 Det() 	{return fDet;}
	Double_t Area() {return fA;}

	void     SetArea(Double_t a) {fA = a;}

	CaloVector & operator = (const CaloVector &);
	Bool_t 		operator == (const CaloVector & v) const ;

	Bool_t IsEMCAL();
	Bool_t IsEMCAL02pi();
	Bool_t IsDCAL();
	Bool_t IsDCAL02pi();

	Int_t GetDet();
	Int_t GetDet02pi();


private:

	void ResetPhi();

	Double_t fPhi;
	Double_t fEta;
	Double_t fE;

	Int_t	 fDet; //0 for EMCal; 1 for DCal

	Double_t fA;

	ClassDef(CaloVector, 1)
};

#endif //CALOVECTOR_HH