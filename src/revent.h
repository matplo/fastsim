#ifndef REVENT__HH
#define REVENT__HH

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>

#include <Rtypes.h>

struct Header;
class TFile;
class TTree;

class REvent
{
public:
	REvent();
	virtual ~REvent();
	void Init(const char *foutname);
	void Write();
	void FillBranch(const char* name, std::vector <fastjet::PseudoJet> in);
	void FillHeader(Header *hp);
	void FinishEvent();

	void SetPythia(Pythia8::Pythia *p);

private:
	TFile *fout;
	TTree *tree;
	Pythia8::Pythia *pPythia;
};

#endif //REVENT__HH
