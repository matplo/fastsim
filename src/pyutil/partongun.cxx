#include <Pythia8/Pythia.h>

#include <cmath>
#include <TH1.h>
#include <TH1F.h>

#include "partongun.h"

// based on Pythia example #21 (main21.cc)

#include <iostream>     // std::cout, std::endl
//#include <iomanip>      // std::setfill, std::setw

namespace PyUtil
{
	PartonGun::PartonGun(int id) 
	: fDebug(false)
	, fPythia(0x0)
	, fSpectrum(0x0)
	, fWeight(0)
	, fPartonID(id)
	{
		;
	}

	PartonGun::~PartonGun()
	{
		delete fSpectrum;
		delete fPythia;
	}

	void PartonGun::SetSpectrum(int id, TH1 *h)
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

	void PartonGun::SetSpectrum(int id, Double_t pt, Double_t ptmax /* = -1 */)
	{
		if (fSpectrum != 0)
		{
			delete fSpectrum;
			fSpectrum = 0;
		}	

		if (pt <= 0)
		{
			std::cerr << "[e] pt of a parton below/or zero? resetting to 1 GeV" << std::endl;
			pt = 1.;
		}
		if (ptmax > pt)
			fSpectrum = new TH1F("fSpectrum", "fSpectrum", 1, pt, ptmax);
		else
			fSpectrum = new TH1F("fSpectrum", "fSpectrum", 1, pt - 1e-1, pt + 1e-1);	
		fSpectrum->SetDirectory(0);
		fSpectrum->SetBinContent(1, pt);

		if (id > 0)
		{
			fPartonID = id;
		}
	}

	void PartonGun::InitPythia()
	{

	// Generator; shorthand for event and particleData.
		fPythia = new Pythia8::Pythia();

		Pythia8::Pythia  &pythia   = *fPythia;

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

	}

	int PartonGun::NextEvent(Double_t pt /* = -1 */)
	{
		// more selections in main21.cc

		if (fPythia == 0x0)
			InitPythia();

		Pythia8::Pythia  &pythia   = *fPythia;

		if (pt < 0)
		{
			if (fSpectrum != 0x0)
			{
				pt = fSpectrum->GetRandom();
			}
			else
			{
				SetSpectrum(fPartonID, 50.);
				pt = fSpectrum->GetRandom();
			}
		}

		InsertPartons(pt);

		//if (!pythia.next()) 
		//{
		//	std::cerr << "[e] Event generation aborted prematurely, owing to error in ::next !\n";
		//	return false;
		//}

		return true;
	}

	void PartonGun::InsertPartons(double pt, bool ispt /*= true*/)
	{
		if (fPythia == 0)
		{
			std::cerr << "[e] Pythia not initialized" << std::endl;
		}
		// Reset event record to allow for new event.
		Pythia8::Pythia &pythia = *fPythia;
		Pythia8::Event  &event  = pythia.event;
		Pythia8::ParticleData& pdt = pythia.particleData;

		event.reset();

		// Information on a q/g qbar/glue system, to be hadronized.
		int    id = fPartonID;
		double mm = pdt.m0(id);
		double et = sqrt(pt*pt + mm*mm);
		if (ispt == false)
		{
			et = pt;
			pt = Pythia8::sqrtpos(et*et - mm*mm);
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

	//	int PartonGun::NextEventFlat()
	//	{
	//		// under development!
	//
	//		if (fPythia == 0x0)
	//			InitPythia();
	//
	//		Pythia8::Pythia  &pythia   = *fPythia;
	//		Pythia8::Event& event      = pythia.event;
	//		Pythia8::ParticleData& pdt = pythia.particleData;
	//
	//		//double partonMass = pdt.m0(fPartonID);
	//
	//		if (fSpectrum == 0x0)
	//		{
	//			std::cerr << "[w] empty spectrum; setting default 50/c GeV gluon" << std::endl;
	//			SetSpectrum(50., 21);
	//		}
	//
	//		Double_t inputIntegral = fSpectrum->Integral();
	//
	//		// now this will be per bin of the input histogram!
	//		for (Int_t ib = 1; ib <= fSpectrum->GetNbinsX(); ib++)
	//		{
	//			// Set up parton-level configuration.
	//			//double qKine = fSpectrum->GetRandom();
	//			//Int_t ib     = fSpectrum->FindBin(qKine);
	//			double qKine = fSpectrum->GetBinLowEdge(ib) + fSpectrum->GetBinWidth(ib) * gRandom->Rndm();
	//			//double qKine = fSpectrum->GetBinCenter(ib);
	//			//double e   = TMath::Sqrt(qKine * qKine + partonMass * partonMass);
	//			//double thr = partonMass * 2.;
	//			//if (e < thr)
	//			//	continue;
	//			fWeight      = fSpectrum->GetBinContent(ib)/nEvent; //fSpectrum->GetBinContent(ib) / inputIntegral;
	//
	//			InsertPartons(qKine);
	//
	//			// Generate events. Quit if failure.
	//			if (!pythia.next()) 
	//			{
	//				cout << "[i] Event generation aborted prematurely, owing to error in ::next !\n";
	//				break;
	//			}
	//		}
	//
	//		return true;	
	//	}

}