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
	CaloVector(Double_t eta, Double_t phi, Double_t e);
	virtual ~CaloVector();

	inline void SetEtaPhiE(Double_t eta, Double_t phi, Double_t e);
	inline void GetEtaPhiE(Double_t &eta, Double_t &phi, Double_t &e) const;
	inline void GetTLV(TLorentzVector &v);
	inline TLorentzVector TLV() { TLorentzVector v; GetTLV(v); return v;}
	inline Double_t Phi() {return fPhi;}
	inline Double_t Eta() {return fEta;}
	inline Double_t E()   {return fE;}
	inline Double_t Pt();

	inline CaloVector & operator = (const CaloVector &);
	inline Bool_t 		operator == (const CaloVector & v) const ;

	inline Bool_t IsEMCAL();
	inline Bool_t IsEMCAL02pi();
	inline Bool_t IsDCAL();
	inline Bool_t IsDCAL02pi();

private:

	Double_t fPhi;
	Double_t fEta;
	Double_t fE;

	ClassDef(CaloVector, 1)
};

inline Bool_t CaloVector::IsEMCAL02pi()
{
	return ( (fE > -0.668305) && (fE < 0.668305) && (fPhi > 1.40413) && (fPhi < 3.26149) );
}

inline Bool_t CaloVector::IsDCAL02pi()
{
	return ( (fE > -0.668305) && (fE < 0.668305) && (fPhi > 4.54573) && (fPhi < 5.70495) );
}

inline Bool_t CaloVector::IsEMCAL()
{
	// this is for -pi - pi
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 1.40413 - PI ) && (fPhi < 3.26149 - PI ) );
}

inline Bool_t CaloVector::IsDCAL()
{
	return ( (fEta > -0.668305) && (fEta < 0.668305) && (fPhi > 4.54573 - PI ) && (fPhi < 5.70495 - PI ) );
}

inline CaloVector & CaloVector::operator = (const CaloVector &v)
{
	fEta = v.fEta;
	fPhi = v.fPhi;
	fE   = v.fE;
}

inline Bool_t CaloVector::operator == (const CaloVector & v) const
{
	return ( fEta == v.fEta && fPhi == v.fPhi && fE == v.fE);
}

inline void CaloVector::GetEtaPhiE(Double_t &eta, Double_t &phi, Double_t &e) const
{
	phi = fPhi;
	eta = fEta;
	e   = fE;
}

inline void CaloVector::SetEtaPhiE(Double_t eta, Double_t phi, Double_t e)
{
	fPhi = phi;
	fEta = eta;
	fE   = e;
}

inline void CaloVector::GetTLV(TLorentzVector &v)
{
	Double_t pT = fE / TMath::CosH(fEta);
	v.SetPtEtaPhiE(pT, fEta, fPhi, fE);
}

inline Double_t CaloVector::Pt()
{
	return fE / TMath::CosH(fEta);
}

#endif //CALOVECTOR_HH