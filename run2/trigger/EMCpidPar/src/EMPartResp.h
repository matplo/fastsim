#ifndef EMPARTRESP_HH
#define EMPARTRESP_HH

#include <TNamed.h>
#include <TArrayD.h>
#include <TArrayI.h>
class TH2F;
class TFile;

class EMPartResp : public TNamed
{
	public: 	
		EMPartResp();
		EMPartResp(const char *fname);
		virtual ~EMPartResp();
		void WriteToFile(const char *fname = "EMPartResp.root");
		void Fill(Int_t pdg, Double_t p, Double_t E);
		Double_t GetEop(Int_t pdg, Double_t p, Bool_t noalter = kFALSE);
	private:
		EMPartResp(const char *name, const char *title) : TNamed(name, title) {;}
		void SetPids();
		void SetBins();
		TArrayD fpBins; //!
		TArrayI fpids;  //!
		TH2F	*fhpEp[18]; //!
		TH2F	*fhpE[18]; //!
		TList   *fLproj; //!
		TFile   *fout; //!
	ClassDef(EMPartResp, 0)
};

#endif // EMPARTRESP_HH