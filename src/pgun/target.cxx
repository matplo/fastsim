// main00.cc Modified from the main01.cc which is a part of the PYTHIA
// event generator.  Copyright (C) 2008 Torbjorn Sjostrand.  PYTHIA is
// licenced under the GNU GPL version 2, see COPYING for details.
// Please respect the MCnet Guidelines, see GUIDELINES for details.

// This is a simple test program.

#include "target.h"

#include <Pythia8/Pythia.h>

#include <TROOT.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TProfile.h>
#include <TString.h>
#include <TNtuple.h>

int gwhich = 0;
int gonia = 0;

bool isBHadron(int id)
{
// This snippet is meant to capture all B hadrons
// as given in the PDG.
	if (id<0) id*=-1;
	if (id<500) return false;
	return (fmod(id/100,5.)==0.0 || id/1000==5);
}

bool isDHadron(int id)
{
// This snippet is meant to capture all B hadrons
// as given in the PDG.
	if (id<0) id*=-1;
	if (id<400 || id >= 500) return false;
	return (fmod(id/100,4.)==0.0 || id/1000==4);
}

bool isCOnia(int id)
{
	if (id==443)
		return kTRUE;
	return kFALSE;
}

bool isBOnia(int id)
{
	if (id==553)
		return kTRUE;
	return kFALSE;
}

bool isXHadron(int id)
{
  if (gwhich == 0)
	{
		if (gonia == 0)
			return isDHadron(id);
		else
			return isCOnia(id);
	}
  else
	{
		if (gonia == 0)
			return isBHadron(id);
		else
			return isBOnia(id);
	}
  return false;
}
using namespace Pythia8;
int run(unsigned int nevents, double pThatmin, int corb, int qqbarflag)
{
// Initialize root
	TROOT root("Manuel's ROOT Session","PYTHIA Histograms");

	gwhich = corb;
	int qID    =  5;
	int qbarID = -5;	
	if (gwhich == 0)
	{
		qID    =  4;
		qbarID = -4;
	}

	gonia = qqbarflag;
	int qqbarID = qID*100+qID*10+3;
	cout << "qqbar id is:" << qqbarID << endl;
// Generator. Process selection. LHC initialization. Histogram.
	Pythia pythia;

// Uncomment line below to turns on all HardQCD processses
// These are 111-116 and  121-124
//pythia.readString("HardQCD:all = on");

// Turn on only bbar production:
// g g    -> b bbar (subprocess 123)
// q qbar -> b bbar (subprocess 124)
	
	if (gwhich == 0)
	  {
	  	pythia.readString("HardQCD:gg2ccbar = on");
	  	pythia.readString("HardQCD:qqbar2ccbar = on");
	  	if (qqbarflag > 0)
	  	{		
	  		pythia.readString("Charmonium:all = on");
	  	}
	  }
	else
	  {
		pythia.readString("HardQCD:gg2bbbar = on");
		pythia.readString("HardQCD:qqbar2bbbar = on");
		if (qqbarflag > 0)
		{
			pythia.readString("Bottomonium:all = on");
		}
	  }
	// see more at: http://hepmcanalysistool.desy.de/ValidationRelease3.0/Doxygen/html/standardSettings__all_8cmnd-source.html

	pythia.readString(TString::Format("PhaseSpace:pTHatMin = %f", pThatmin).Data());

// Random number Generator Should be Set Here if needed (before pythia.init())
// On seeds:
// seed = -1 : default (any number < 0 will revert to the default).  seed = 19780503
// seed = 0 : calls Stdlib time(0) to provide a seed based on the unix time
// seed = 1 through 900 000 000: various numbers that can be used as seeds

//pythia.readString("Random.setSeed = on");// doesn't work needs fixing
//pythia.readString("Random.seed = 3000000");

	pythia.readString("Beams:eCM = 2760.");
	//pythia.init( 2212, 2212, 2760.);
	pythia.init();
	Hist mult("charged multiplicity", 100, -0.5, 799.5);

	TH1D* multHist = new TH1D("multHist","Multiplicity",100,-0.5,99.5);
	TH1D* aquarkPt = new TH1D("aquarkPt","aquarkPt",100,0,50);
	TH1D* abarquarkPt = new TH1D("abarquarkPt","abar quark Pt",100,0,50);
	TH1D* B0mesonPt = new TH1D("BOmesonPt","B0mesonPt",100,0,50);
	TH1D* B0barmesonPt = new TH1D("BObarmesonPt","B0bar meson Pt",100,0,50);
	TH1D* electronFrombPt = new TH1D("electronFrombPt","electrons from b",100,0,30);
	TH1D* positronFrombPt = new TH1D("positronFrombPt","positrons from b",100,0,30);
	TH1D* epluseminusMinv = new TH1D("epluseminusMinv","e+ e- Inv. Mass",300,0,30);
	TH1D* epluseminusMinvw = new TH1D("epluseminusMinvw","e+ e- Inv. Mass",300,0,30);

	TH2D* qpTepT  = new TH2D("qpTepT",  "qpTepT;quark p_{T};electron p_{T}",  100, 0, 100, 100, 0, 100);
	TH2D* qpTepTw = new TH2D("qpTepTw", "qpTepTw;quark p_{T};electron p_{T}", 100, 0, 100, 100, 0, 100);

	TProfile* sigmaGen = new TProfile("sigmaGen", "sigmaGen", 100, 0, nevents);

	TNtuple *tnqe  = new TNtuple("tnqe",  "tnqe",  "qpT:qy:epT:ey:w");
	TNtuple *tnqee = new TNtuple("tnqee", "tnqee", "epT:ey:ppT:py:minv:w");
	TNtuple *tnqqbar = new TNtuple("tnqqbar", "tnqqbar", "pT:y:m:w");
	
// Begin event loop. Generate event. Skip if error. List first one.
	int iEventAccepted = 0;
	for (int iEvent = 0; iEvent < nevents; ++iEvent) {
		if (!pythia.next()) continue;
		//if (iEvent < 1) {
		//	pythia.info.list();
		//	pythia.event.list();
		//}
// Find number of all final charged particles and fill histogram.
// Find the b (id = 5) and bbar (id = -5), find their daughters,
// if daughters include electron (id = 11) and positron (id=-11), calculate their
// invariant mass
// Status flags:
//   21 incoming particles of hardest subprocess
//   23 outgoing particles of hardest subprocess
//   81-89 primary hadrons produced by hadronization process (B mesons, e.g.)
//   91-99 particles produced in decay process or by B-E effects (e.g. the electrons)

		Double_t fSigmaGen = pythia.info.sigmaGen();
		cout << "[i] sigmaGen = " << TString::Format("%1.10f", fSigmaGen) << endl;

		int nCharged = 0;
		int indexaquark(0), indexabarquark(0);
		Bool_t qqbarfound = kFALSE;
		for (int i = 0; i < pythia.event.size(); ++i) {
			if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) 
			{
				++nCharged;
			}
			Particle& theParticle = pythia.event[i];

			if (theParticle.id() == qID ) 
			{
				indexaquark = i;
//cout << "Mother 1, Mother 2 = " << theParticle.mother1() << ", " << theParticle.mother2() << endl;
			}
			if (theParticle.id() == qbarID ) 
			{
				indexabarquark = i;
//cout << "Mother 1, Mother 2 = " << theParticle.mother1() << ", " << theParticle.mother2() << endl;
			}

			if ( theParticle.id() == qqbarID )
			{
				qqbarfound = kTRUE;
				tnqqbar->Fill(theParticle.pT(),theParticle.y(),theParticle.m(),fSigmaGen);
			}
		} // particle loop

		if (iEvent % 1000 == 0)
		{
			cerr << "Nevent:" << iEvent << " accepted:" << iEventAccepted << endl;
			cerr << "- pThatmin:" << pThatmin << " Event " << iEvent << ", Nch= " << nCharged << endl;
		}

		if (qqbarflag > 0 && qqbarfound == kFALSE)
		{
			continue;
		}
		//if (qqbarfound == kTRUE)
		//{
			//cerr << "qqbar found:" << qqbarID << endl;
		//}

		iEventAccepted++;

		cout << "Found a quark at index " << indexaquark << endl;
		cout << "Found abar quark at index " << indexabarquark << endl;
		aquarkPt->Fill(pythia.event[indexaquark].pT());
		abarquarkPt->Fill(pythia.event[indexabarquark].pT());
		mult.fill( nCharged );
		multHist->Fill(nCharged);
		sigmaGen->Fill(iEvent, fSigmaGen);

//Find hadronization products of b and bbar.
		int aquarkDaughter1 = pythia.event[indexaquark].daughter1();
		int aquarkDaughter2 = pythia.event[indexaquark].daughter2();
		int abarquarkDaughter1 = pythia.event[indexabarquark].daughter1();
		int abarquarkDaughter2 = pythia.event[indexabarquark].daughter2();

// Obtain the two hadrons from the fragmentation process
// Use the PDG id's for this.  All B mesons id's are of the form xx5xx, and
// all B baryons are of the form 5xxx.
// So we obtain the id, (make it positive if needed) and then test
// to see if it is a meson with fmod(currId/100,5)==0.0
// to see if it is a baryon with currId/1000==5
		int HadronFromaquark(0), HadronFromabarquark(0);
		if (aquarkDaughter1<aquarkDaughter2) {
			cout << "Daughters of a quark" << endl;
			for (int j=aquarkDaughter1; j<=aquarkDaughter2; ++j) {
				if (isXHadron(pythia.event[j].id())) {
					cout << "Fragmentation: b -> " << pythia.event[j].name() << endl;
					cout << "                 id " << pythia.event[j].id() << " at index " << j << endl;
					HadronFromaquark = j;
				}
			}
		}
		if (abarquarkDaughter1<abarquarkDaughter2) {
			cout << "Daughters of abar quark" << endl;
			for (int k=abarquarkDaughter1; k<=abarquarkDaughter2; ++k) {
				if (isXHadron(pythia.event[k].id())) {
					cout << "Fragmentation : bbar -> " << pythia.event[k].name()  << endl;
					cout << "                     id " << pythia.event[k].id() << " at index " << k << endl;
					HadronFromabarquark = k;
				}
			}
		}
// Search the daughters of the hadrons until electrons and positrons are found
// if there are any from a semileptonic decay of a beauty hadron
// Start with the a quark
		int Daughter(HadronFromaquark), electronIndex(0), positronIndex(0);
		while (Daughter!=0) {
			cout << "Checking " << pythia.event[Daughter].name() << " for e+/e- daughters" << endl;
			if (pythia.event[Daughter].id()==-511) {
				// This is a Bbar0, enter its pT
				cout << "Filling Bbar0 pT" << endl;
				B0barmesonPt->Fill(pythia.event[Daughter].pT());
			}
			if (pythia.event[Daughter].id()==511) {
				// This is a B0, enter its pT
				cout << "Filling Bbar0 pT" << endl;
				B0mesonPt->Fill(pythia.event[Daughter].pT());
			}
			int nextDaughter1 = pythia.event[Daughter].daughter1();
			int nextDaughter2 = pythia.event[Daughter].daughter2();
			// search for electron or positron
			for (int iDaughter = nextDaughter1; iDaughter<=nextDaughter2; ++iDaughter) {
				if (pythia.event[iDaughter].id()==11) {
					cout << "Found electron" << endl;
					cout << pythia.event[iDaughter].name() << endl;
					electronIndex=iDaughter;
					electronFrombPt->Fill(pythia.event[electronIndex].pT());
					qpTepT->Fill(pythia.event[indexaquark].pT(), pythia.event[electronIndex].pT());
					qpTepTw->Fill(pythia.event[indexaquark].pT(), pythia.event[electronIndex].pT(), fSigmaGen);
					tnqe->Fill(pythia.event[indexaquark].pT(), pythia.event[indexaquark].y(),
								pythia.event[electronIndex].pT(), pythia.event[electronIndex].y(),
								fSigmaGen);
					break;
				}
				if (pythia.event[iDaughter].id()==-11) {
					cout << "Found positron" << endl;
					cout << pythia.event[iDaughter].name() << endl;
					positronIndex=iDaughter;
					positronFrombPt->Fill(pythia.event[positronIndex].pT());
					qpTepT->Fill(pythia.event[indexaquark].pT(), pythia.event[positronIndex].pT());		    
					qpTepTw->Fill(pythia.event[indexaquark].pT(), pythia.event[positronIndex].pT(), fSigmaGen);		    
					tnqe->Fill(pythia.event[indexaquark].pT(), pythia.event[indexaquark].y(),
								pythia.event[positronIndex].pT(), pythia.event[positronIndex].y(),
								fSigmaGen);
					break;
				}
			}// loop over daughters to check for e+e-

			// If we get here, that means there were no electrons nor positrons.
			// Set the Daughter index to zero now.
			Daughter = 0;
			// If any of the daughters is still a beauty-hadron, we can try again
			// and reset the Daughter index, but only if one of the daughters contains a
			// a quark.
			for (int jDaughter = nextDaughter1; jDaughter<=nextDaughter2; ++jDaughter) {
				if (isXHadron(pythia.event[jDaughter].id())) {
					//One of the daughters is a beauty hadron.
					Daughter = jDaughter;
				}
			}// loop over daughters to check for another b hadron
		}// end of search for electrons in all the daughters of the a quark

// Now search among the daughters of the abar quark
		Daughter=HadronFromabarquark;
		while (Daughter!=0) {
			cout << "Checking " << pythia.event[Daughter].name() << " for e+/e- daughters" << endl;
			if (pythia.event[Daughter].id()==-511) {
				// This is a Bbar0, enter its pT
				cout << "Filling Bbar0 pT" << endl;
				B0barmesonPt->Fill(pythia.event[Daughter].pT());
			}
			if (pythia.event[Daughter].id()==511) {
				// This is a B0, enter its pT
				cout << "Filling B0 pT" << endl;
				B0mesonPt->Fill(pythia.event[Daughter].pT());
			}
			int nextDaughter1 = pythia.event[Daughter].daughter1();
			int nextDaughter2 = pythia.event[Daughter].daughter2();
			// search for electron or positron
			for (int iDaughter = nextDaughter1; iDaughter<=nextDaughter2; ++iDaughter) {
				//cout << "daughter is a " << pythia.event[iDaughter].name() << endl;
				if (pythia.event[iDaughter].id()==11) {
					cout << "Found electron" << endl;
					cout << pythia.event[iDaughter].name() << endl;
					electronIndex=iDaughter;
					electronFrombPt->Fill(pythia.event[electronIndex].pT());
					qpTepT->Fill(pythia.event[indexabarquark].pT(), pythia.event[electronIndex].pT());
					qpTepTw->Fill(pythia.event[indexabarquark].pT(), pythia.event[electronIndex].pT(), fSigmaGen);
					break;
				}
				if (pythia.event[iDaughter].id()==-11) {
					cout << "Found positron" << endl;
					cout << pythia.event[iDaughter].name() << endl;
					positronIndex=iDaughter;
					positronFrombPt->Fill(pythia.event[positronIndex].pT());
					qpTepT->Fill(pythia.event[indexabarquark].pT(), pythia.event[positronIndex].pT());
					qpTepTw->Fill(pythia.event[indexabarquark].pT(), pythia.event[positronIndex].pT(), fSigmaGen);					
					break;
				}
			}// loop over daughters to check for e+e-

			// If we get here, that means there were no electrons nor positrons.
			// Set the Daughter index to zero now.
			Daughter = 0;
			// If any of the daughters is still a beauty-hadron, we can try again
			// and reset the Daughter index, but only if one of the daughters contains a
			// a quark.
			for (int jDaughter = nextDaughter1; jDaughter<=nextDaughter2; ++jDaughter) {
				if (isXHadron(pythia.event[jDaughter].id())) {
					//One of the daughters is a beauty hadron.
					Daughter = jDaughter;
				}
			}// loop over daughters to check for another b hadron
		}//end of search for electron among daughters of abar quark

		if (electronIndex!=0 && positronIndex!=0) {
			cout << "Found an e+e- pair from bbar" << endl;
			cout << "Ele 4-mom = " << pythia.event[electronIndex].p() << endl;
			cout << "Pos 4-mom = " << pythia.event[positronIndex].p() << endl;
			Vec4 epluseminus(pythia.event[electronIndex].p()+pythia.event[positronIndex].p());
			epluseminusMinv->Fill(epluseminus.mCalc());
			epluseminusMinvw->Fill(epluseminus.mCalc(), fSigmaGen);
			tnqee->Fill(pythia.event[electronIndex].pT(), pythia.event[electronIndex].y(),
						pythia.event[positronIndex].pT(), pythia.event[positronIndex].y(),
						epluseminus.mCalc(), epluseminus.rap(),
						fSigmaGen);
		}
		else {
			cout << "No e+e- pair in event" << endl;
		}

// End of event loop. Statistics. Histogram. Done.
	}// event loop
	//pythia.statistics();
	pythia.stat();
	cout << "WeightSum:=" << pythia.info.weightSum() << endl;    
//cout << mult << endl;

//Write Output ROOT hisotgram into ROOT file
	TString foutname = TString::Format("quark-%d-pThatmin-%1.1f-onia-%d-nev%d.root", gwhich, pThatmin, qqbarflag, nevents);
	TFile* outFile = new TFile(foutname.Data(),"RECREATE");
	multHist->Write();
	aquarkPt->Write();
	abarquarkPt->Write();
	B0mesonPt->Write();
	B0barmesonPt->Write();
	electronFrombPt->Write();
	positronFrombPt->Write();
	epluseminusMinv->Write();
	epluseminusMinvw->Write();	
	qpTepT->Write();
	qpTepTw->Write();	
	sigmaGen->Write();

	tnqe->Write();
	tnqee->Write();
	tnqqbar->Write();
	outFile->Close();

	return 0;
}

