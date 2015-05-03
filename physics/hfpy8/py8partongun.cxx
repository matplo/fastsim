#include <Pythia8/Pythia.h>
using namespace Pythia8;

#include <TROOT.h>
#include <TFile.h>
#include <TObjArray.h>
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
	, fOutputName("pgun_default_output.root")
	, fOutputFile(0)
	, fOutput(0)
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

void PGun::InitOutput()
{
	fOutputFile = new TFile(fOutputName, "recreate");
	fOutputFile->cd();
	fOutput = new TObjArray();
	fOutput->SetOwner(kTRUE);
}

void PGun::FillOutput()
{
	//do sometthing with fPythia;
}

void PGun::WriteOutput()
{
	fOutputFile->cd();
	fOutputFile->Write();
	fOutputFile->Close();
	delete fOutputFile;
	fOutputFile = 0;
}

int PGun::Generate(int nEvent)
{
	// Pick kind of events to generate:
	// 0 = single-particle gun.
	// 1 = q qbar.
	// 2 = g g.
	// more selections in main21.cc

	// Set number of events to .
	int n = 1;

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

	// Switch off automatic event ing in favour of manual.
	pythia.readString("Next:numberShowInfo = 0");
	pythia.readString("Next:numberShowProcess = 0");
	pythia.readString("Next:numberShowEvent = 0");

	// Initialize.
	pythia.init();
	InitOutput();

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

	    //  first few events.
		if (iEvent < n) 
		{
			event.list();
			// Also  junctions.
			event.listJunctions();
		}

		FillOutput();

		// End of event loop.
	}

	// Print statistics, histograms and done.
	pythia.stat();

	WriteOutput();

	// Done.
	return 0;
}


void PGun::FillPartons(double qKine, bool ispt /*= true*/)
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
	double pt = qKine;
	double et = sqrt(pt*pt + mm*mm);
	if (ispt == false)
	{
		et = qKine;
		pt = sqrtpos(et*et - mm*mm);
	}
	if (id != 21)
	{  
		// q qbar
		event.append(  id, 23, 101,   0,  pt, 0., 0., et, mm);
		event.append( -id, 23,   0, 101, -pt, 0., 0., et, mm);
	}
	else
	{   
		// gluons
		event.append( 21, 23, 101, 102,  et, 0., 0., et);
		event.append( 21, 23, 102, 101, -et, 0., 0., et);
	}
}

TH1 *PGun::Out1D(int index)
{
	return (TH1*)fOutput->At(index);
}

TH2 *PGun::Out2D(int index)
{
	return (TH2*)fOutput->At(index);
}
