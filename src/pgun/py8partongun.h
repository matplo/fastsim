#ifndef __PGUN__HH
#define __PGUN__HH

#include <vector>

#include <TObject.h>
#include <TString.h>

namespace Pythia8
{
	class Pythia;
	class Particle;
}

class TH1;
class TH2;
class TFile;
class TObjArray;
class TGraphErrors;

class PGun : public TObject
{
public:
	PGun();
	virtual ~PGun();

	void SetDebug(bool dbg)
	{
		fDebug = dbg;
	}

	void SetSpectrum(TH1 *h, int id = -1);
	void SetSpectrum(TGraphErrors *gr, int id = -1);

	void SetPartonID(int id)
	{
		fPartonID = id;
	}

	void PrintNEvents(int d)
	{
		fPrintN = d;
	}

	int Generate(int nEvent);

	virtual void InitOutput();
	virtual void FillOutput();
	virtual void WriteOutput();

	void SetOutputFileName(const char *outname)
	{
		fOutputName = outname;
	}

	void PrintParticle(Pythia8::Particle &p);
	void PrintParticle(int idx);
	std::vector<int> GetDaughters(int idx, int minID = 0, int maxID = 10000, bool quiet = true); // default is all
	std::vector<int> FollowDaughters(int idx, int minID = 0, int maxID = 10000, bool quiet = true);

private:

	// by default qKine == px; otherwise == ex (full pT in x-direction)
	void FillPartons(double qKine, bool ispt = true); 

protected:
	TH1 *Out1D(int index);
	TH2 *Out2D(int index);

	bool             fDebug;
	int              fPrintN;
	Pythia8::Pythia *fPythia; //!
	TH1             *fSpectrum; //!
	Double_t         fWeight;
	int              fPartonID;

	TString          fOutputName;
	TFile           *fOutputFile;
	TObjArray       *fOutput;
	ClassDef(PGun, 0)
};

#endif //__PGUN__HH