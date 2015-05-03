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

	if (event.size() < 1)
		return;

	event.list();

	bool quiet = true;

	Particle parton = event[0];
	int pIndex = -1;
	for (int i = 0; i < event.size(); i++) 
	{
		//PrintParticle(i);
		//int status = event[i].statusAbs();
		int id = event[i].id();
		if (id == fPartonID)
		{
			pIndex = i;
			Out1D(kqpt)->Fill(event[i].pT());
			parton = event[i];
			PrintParticle(pIndex);
			cout << "    -> selected parton" << endl;
			// now check the daughters
			vector<int> charmH  = FollowDaughters(pIndex, 400, 499, quiet);
			// now find an electron and check whether the mother is fPartonID
			cout << "number of charmH: " << charmH.size() << endl;
			for (unsigned int ic = 0; ic < charmH.size(); ic++)
			{
				PrintParticle(charmH[ic]);
				vector<int> electrons = GetDaughters(charmH[ic], 11, 11, quiet);
				cout << " charmH:" << ic << " - number of electrons: " << electrons.size() << endl;
				for (unsigned int ip = 0; ip < electrons.size(); ip++)
				{
					PrintParticle(electrons[ip]);
				}
			}
		}
	}
	cout << "::FillOutput done." << endl; cout << endl;
}
