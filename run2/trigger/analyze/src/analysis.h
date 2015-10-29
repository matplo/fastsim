#ifndef ANALYSIS_HH
#define ANALYSIS_HH

#include <TObject.h>
#include <vector>
class TLorentzVector;
class TTree;
class TBranch;

#include "rstructures.h"

class Analysis : public TObject
{
public:
	Analysis();
	virtual ~Analysis();
	TBranch *GetBranch(const char *name, std::vector<TLorentzVector> **p);
	TBranch *GetBranch(const char *name, TriggerInfo **p);
	TBranch *GetBranch(const char *name, Header **p);
	virtual Int_t    GetEntry(Long64_t entry);
   	virtual Long64_t LoadTree(Long64_t entry);
	virtual Bool_t   Notify();
	void AnalyzeFile(const char *fname, const char *foutname);
private:
	TTree 		*fChain;//!
	Int_t        fCurrent; //!current Tree number in a TChain

	ClassDef(Analysis, 0)
};

#endif //ANALYSIS_HH