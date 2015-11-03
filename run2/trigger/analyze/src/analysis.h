#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include <TObject.h>
#include <vector>
class TLorentzVector;
class TTree;
class TBranch;

class Analysis : public TObject
{
public:
						Analysis();
	virtual 			~Analysis();
	TBranch 			*GetBranch(const char *, std::vector<TLorentzVector> **);
	//TBranch 			*GetBranch(const char *name, TriggerInfo &p);
	//TBranch 			*GetBranch(const char *name, Header &p);
	TBranch 			*GetBranch(const char *, Double_t *);
	virtual Int_t    	GetEntry(Long64_t);
   	virtual Long64_t 	LoadTree(Long64_t);
	virtual Bool_t   	Notify();
	void 				AnalyzeFile(const char *fname, const char *foutname, Long64_t nev = -1);
	void 				SmallR(Bool_t v) {frflag = v;}
private:

	TTree 		*fChain;//!
	Int_t        fCurrent; //!current Tree number in a TChain
	Bool_t       frflag;
	ClassDef(Analysis, 0)
};

#endif //ANALYSIS_HH