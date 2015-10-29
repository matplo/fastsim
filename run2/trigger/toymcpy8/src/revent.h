#ifndef REVENT__HH
#define REVENT__HH

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>

#include <Rtypes.h>

#include "rstructures.h"

class TFile;
class TTree;
class EMPartResp;
class AliGenFastModelingEvent;
//class Pythia8::Pythia;
class TriggerMaker;
class RawPatch;

class REvent
{
public:
	REvent();
	virtual ~REvent();
	void Init(const char *foutname);
	void Write();
	void FillBranch(const char* name, std::vector <fastjet::PseudoJet> in);
	void FillBranch(const char *name, std::vector<RawPatch> in);
	void FillTrigger(const char* name, TriggerMaker *tm);
	void FillHeader(const char* name, Header *hp);
	void FinishEvent();

	void SetPythia(Pythia8::Pythia *p);
	void SetBackground(AliGenFastModelingEvent *p);
	void SetEMCresponse(EMPartResp *p);

private:
	TFile *fout;
	TTree *tree;
	Pythia8::Pythia *pPythia;
	AliGenFastModelingEvent *pFME;
	EMPartResp *pEMCresponse;
};

#endif //REVENT__HH