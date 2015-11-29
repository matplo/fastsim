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
	void FillBranch(const char* name, std::vector <fastjet::PseudoJet> in);
	void FillBranch(const char *name, std::vector <RawPatch> in);
	void FillTrigger(const char* name, TriggerMaker *tm);
	void FinishEvent();
	TTree *GetTree() {return tree;}
private:
	TTree *tree;
};

#endif //REVENT__HH