#ifndef __PGUN__HH
#define __PGUN__HH

#include <TObject.h>
#include <TString.h>

namespace Pythia8
{
	class Pythia;
}

class TH1;
class TH2;
class TFile;
class TObjArray;

class PGun : public TObject
{
public:
	PGun();
	virtual ~PGun();

	void SetSpectrum(TH1 *h, int id = -1);
	void SetPartonID(int id)
	{
		fPartonID = id;
	}

	int Generate(int nEvent);

	virtual void InitOutput();
	virtual void FillOutput();
	virtual void WriteOutput();

	void SetOutputFileName(const char *outname)
	{
		fOutputName = outname;
	}

private:

	// by default qKine == px; otherwise == ex (full pT in x-direction)
	void FillPartons(double qKine, bool ispt = true); 

protected:
	TH1 *Out1D(int index);
	TH2 *Out2D(int index);

	Pythia8::Pythia *fPythia; //!
	TH1             *fSpectrum; //!
	int              fPartonID;

	TString          fOutputName;
	TFile           *fOutputFile;
	TObjArray       *fOutput;

	ClassDef(PGun, 0)
};

#endif //__PGUN__HH