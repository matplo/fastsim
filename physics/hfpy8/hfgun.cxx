#include "HFGun.h"

#include <Pythia8/Pythia.h>
using namespace Pythia8;

#include <TObjArray.h>
#include <TH1F.h>

enum {kin, kqpt};

ClassImp(HFGun)

HFGun::HFGun()
	: PGun()
{
	fOutputName = "hfgun_default_output.root";
}

HFGun::~HFGun()
{
	;
}

void HFGun::InitOutput()
{
	PGun::InitOutput();
	TH1F *h = new TH1F("qpt", "qpt", 100, 0, 100);
	fOutput->Add(fSpectrum->Clone("input"));
	fOutput->Add(h);
}

void HFGun::FillOutput()
{
	Pythia    &pythia = *fPythia;
	Event     &event  = pythia.event;
	TObjArray &out    = *fOutput;

	for (int i = 0; i < event.size(); ++i) 
	{
		//int status = event[i].statusAbs();
		int id = event[i].id();
		cout << id << " " << event[i].e() << endl;
		if (id == fPartonID)
		{
			Out1D(kqpt)->Fill(event[i].pT());			
		}
		// now find an electron and check whether the mother is fPartonID
	}
}
