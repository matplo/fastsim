#include "hfgun.h"

#include <Pythia8/Pythia.h>
using namespace Pythia8;

#include <TObjArray.h>
#include <TH1F.h>
#include <TNtuple.h>

enum {kin, kqpt, ktne, ktnh};

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
	fOutput->Add(fSpectrum->Clone("input"));
	TH1F *h = new TH1F("qpt", "qpt", 100, 0, 100);
	fOutput->Add(h);
	TNtuple *tne = new TNtuple("tne", "tne", "qpt:qid:hpt:hy:hid:ept:ey:eid:w");
	fOutput->Add(tne);
	TNtuple *tnh = new TNtuple("tnh", "tnh", "qpt:hpt:hy:id:nd:w");
	fOutput->Add(tnh);
}

void HFGun::FillOutput()
{
	Pythia    &pythia = *fPythia;
	Event     &event  = pythia.event;
	TObjArray &out    = *fOutput;

	TNtuple *tne = (TNtuple*)fOutput->At(ktne);
	TNtuple *tnh = (TNtuple*)fOutput->At(ktnh);

	if (event.size() < 1)
		return;

	//int hadronIDmin = fPartonID * 100;
	//int hadronIDmax = fPartonID * 100 + 99;

	//get all D's and B's
	int hadronIDmin = 4 * 100;
	int hadronIDmax = 5 * 100 + 99;

	Particle parton = event[0];
	int pIndex = -1;
	for (int i = 0; i < event.size(); i++) 
	{
		//int status = event[i].statusAbs();
		int id = event[i].id();
		if (abs(id) == fPartonID)
		{
			pIndex = i;
			Out1D(kqpt)->Fill(event[i].pT());
			parton = event[i];
			if (fDebug) PrintParticle(pIndex);
			vector<int> decayH  = FollowDaughters(pIndex, hadronIDmin, hadronIDmax, !fDebug);
			for (unsigned int ih = 0; ih < decayH.size(); ih++)
			{
				if (fDebug) PrintParticle(decayH[ih]);
				vector<int> electrons = GetDaughters(decayH[ih], 11, 11, !fDebug);
				Particle &hadron = event[decayH[ih]];
				int hDaughters = GetDaughters(decayH[ih], hadronIDmin, hadronIDmax, !fDebug).size();
				tnh->Fill(parton.pT(), hadron.pT(), hadron.y(), hadron.id(), hDaughters, fWeight);
				for (unsigned int ip = 0; ip < electrons.size(); ip++)
				{
					if (fDebug) PrintParticle(electrons[ip]);
					//TNtuple *tne = new TNtuple("tne", "qpt:hpt:ept:ey");
					Particle &electron = event[electrons[ip]];
					tne->Fill(parton.pT(), parton.id(),
								hadron.pT(), hadron.y(), hadron.id(), 
								electron.pT(), electron.y(), electron.id(),
								fWeight);
				}				
			}
		}
	}
}
