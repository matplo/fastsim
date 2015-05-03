#include <Pythia8/Pythia.h>
using namespace Pythia8;

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TString.h>
#include <TNtuple.h>

#include "py8partongun.h"

// based on Pythia example #21 (main21.cc)

ClassImp(PGun);

PGun::PGun() : TObject()
	, fPythia(0)
	, fSpectrum(0)
	, fPartonID(21)
{
	;
}

PGun::~PGun()
{
	if (fSpectrum != 0)
	{
		delete fSpectrum;
		fSpectrum = 0;
	}			
}

void PGun::SetSpectrum(TH1 *h, int id)
{
	if (fSpectrum != 0)
	{
		delete fSpectrum;
		fSpectrum = 0;
	}	
	fSpectrum = (TH1*)h->Clone("hspectrum");
	fSpectrum->SetDirectory(0);

	if (id > 0)
	{
		fPartonID = id;
	}
}

int PGun::Generate(int nEvent)
{
	// Pick kind of events to generate:
	// 0 = single-particle gun.
	// 1 = q qbar.
	// 2 = g g.
	// more selections in main21.cc

	// Set number of events to list.
	int nList = 1;

	// Generator; shorthand for event and particleData.
	Pythia pythia;
	fPythia = &pythia;

	Event& event      = pythia.event;
	ParticleData& pdt = pythia.particleData;

	// Key requirement: switch off ProcessLevel, and thereby also PartonLevel.
	pythia.readString("ProcessLevel:all = off");

	//Optionally switch off resonance decays, or only showers in them.
	//pythia.readString("ProcessLevel:resonanceDecays = off");
	//pythia.readString("PartonLevel:FSRinResonances = off");

	// Optionally switch off ordinary decays.
	//pythia.readString("HadronLevel:Decay = off");

	// Switch off automatic event listing in favour of manual.
	pythia.readString("Next:numberShowInfo = 0");
	pythia.readString("Next:numberShowProcess = 0");
	pythia.readString("Next:numberShowEvent = 0");

	// Initialize.
	pythia.init();

	// Book histograms.

	// Begin of event loop.
	for (int iEvent = 0; iEvent < nEvent; ++iEvent) 
	{

	    // Set up parton-level configuration.
		double energy = fSpectrum->GetRandom();
		FillPartons(energy);

	    // Generate events. Quit if failure.
		if (!pythia.next()) 
		{
			cout << " Event generation aborted prematurely, owing to error!\n";
			break;
		}

	    // List first few events.
		if (iEvent < nList) 
		{
			event.list();
			// Also list junctions.
			event.listJunctions();
		}

		    // Loop over all particles.
		for (int i = 0; i < event.size(); ++i) 
		{
			int status = event[i].statusAbs();

			// Find any unrecognized particle codes.
			int id = event[i].id();
			if (id == 0 || !pdt.isParticle(id))
				cerr << "[e] Error! Unknown code id = " << id << endl;

			// Find particles with E-p mismatch.
			double eCalc = event[i].eCalc();
			if (abs(eCalc/event[i].e() - 1.) > 1e-6) 
				cout << " e mismatch, i = "
				<< i << " e_nominal = " 
				<< event[i].e() << " e-from-p = "
				<< eCalc << " m-from-e " 
				<< event[i].mCalc() << endl;
		}

		// End of event loop.
	}

	// Print statistics, histograms and done.
	pythia.stat();
	// Done.
	return 0;
}


void PGun::FillPartons(double ee)
{
	if (fPythia == 0)
	{
		cerr << "[e] Pythia not initialized" << endl;
	}
	// Reset event record to allow for new event.
	Pythia &pythia = *fPythia;
	Event  &event  = pythia.event;
	ParticleData& pdt = pythia.particleData;

	event.reset();

	// Information on a q/g qbar/glue system, to be hadronized.
	int    id = fPartonID;
	double mm = pdt.m0(id);
	double pp = sqrtpos(ee*ee - mm*mm);
	if (id != 21)
	{  
		// q qbar
		event.append(  id, 23, 101,   0, 0., 0.,  pp, ee, mm);
		event.append( -id, 23,   0, 101, 0., 0., -pp, ee, mm);
	}
	else
	{   
		// gluons
		event.append( 21, 23, 101, 102, 0., 0.,  ee, ee);
		event.append( 21, 23, 102, 101, 0., 0., -ee, ee);
	}
}
