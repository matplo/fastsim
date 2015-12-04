#ifndef REVENT__HH
#define REVENT__HH

#include <Rtypes.h>

class TFile;
class TTree;
class EMPartResp;
class TriggerMaker;
class RawPatch;

#include <fastjet/PseudoJet.hh>

class REvent
{
public:
	REvent();
	virtual ~REvent();
	void Init(const char *tname = "t");
	void Write();
	void CreateTriggerBranch(const char* name);

	void CreateBranchTLV(const char* name);
	void FillBranchTLV(const char* name, std::vector <fastjet::PseudoJet> in, unsigned int maxn = -1);
	void FillBranchTLV(const char *name, std::vector <RawPatch> in);

	void CreateBranch(const char* name);
	void FillBranch(const char* name, std::vector <fastjet::PseudoJet> in, unsigned int maxn = -1);
	void FillBranch(const char *name, std::vector <RawPatch> in);

	void FillTrigger(const char* name, TriggerMaker *tm, Int_t etype, Double_t totalE, Bool_t patches = kFALSE);
	void FinishEvent();
	void DumpListOfBranches();
	TTree *GetTree() {return tree;}
private:
	TTree *tree;
};

#endif //REVENT__HH