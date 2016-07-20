#include "hfgun.h"

#include <Pythia8/Pythia.h>
using namespace Pythia8;

#include <TObjArray.h>
#include <TH1F.h>
#include <TNtuple.h>
#include <TFile.h>

enum {kin, kqpt, kqptw, ktne, ktnh};

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
	TH1F *h = new TH1F("qpt", "qpt", 200, 0, 400);
	fOutput->Add(h);
	TH1F *hw = new TH1F("qptw", "qptw", 200, 0, 400);
	fOutput->Add(hw);
	fOutputFile->cd();
	TNtuple *tne = new TNtuple("tne", "tne", "qpt:qid:hpt:hy:hid:ept:ey:eid:w");
	tne->SetDirectory(fOutputFile);
	fOutput->Add(tne);
	fOutputFile->cd();
	TNtuple *tnh = new TNtuple("tnh", "tnh", "qpt:qid:hpt:hy:id:nd:w");
	tnh->SetDirectory(fOutputFile);
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
			Out1D(kqptw)->Fill(event[i].pT(), fWeight);
			parton = event[i];
			if (fDebug) PrintParticle(pIndex);
			vector<int> decayH  = FollowDaughters(pIndex, hadronIDmin, hadronIDmax, !fDebug);
			for (unsigned int ih = 0; ih < decayH.size(); ih++)
			{
				if (fDebug) PrintParticle(decayH[ih]);
				vector<int> electrons = GetDaughters(decayH[ih], 11, 11, !fDebug);
				Particle &hadron = event[decayH[ih]];
				int hDaughters = GetDaughters(decayH[ih], hadronIDmin, hadronIDmax, !fDebug).size();
				tnh->Fill(parton.pT(), parton.id(), hadron.pT(), hadron.y(), hadron.id(), hDaughters, fWeight);
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
