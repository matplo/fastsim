#ifndef REVENT__HH
#define REVENT__HH

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>

#include <Rtypes.h>

struct Header;
class TFile;
class TTree;
class TParticle;
class TLorentzVector;

class REvent
{
public:
	REvent();
	virtual ~REvent();
	void Init(const char *foutname);
	void Write();

	void FillBranch(const char* name, std::vector <fastjet::PseudoJet> in);
	void FillBranch(const char* name, std::vector <TParticle> in);
	void FillBranch(const char* name, std::vector <TLorentzVector> in);

	void FillHeader(Header *hp);
	void FinishEvent();

	void SetPythia(Pythia8::Pythia *p);

	static void LoadLibs();

private:
	TFile *fout;
	TTree *tree;
	Pythia8::Pythia *pPythia;
	static bool sLibsLoaded;
};

#endif //REVENT__HH
