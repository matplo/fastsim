#include "gen_from_coll.h"

#include "Collision.h"
#include "deltaE.h"
#include "OutFile.h"

#include <TFile.h>
#include <TTree.h>
#include <TStopwatch.h>

#include <vector>
#include <iostream>
using namespace std;

namespace py = Pythia8;

class Nucleon
{
public:
	Nucleon()
		: fEnergy(0.0)
		, fNcoll(0)
	{ ; }
	Nucleon(double e, double ncoll = 0)
		: fEnergy(e)
		, fNcoll(0)
	{ ; }

	~Nucleon() {;}

	double E() { return fEnergy;}
	int    NColl() {return fNcoll;}

	void SetE(double ve) {fEnergy = ve;}
	void SetNcoll(int nc) {fNcoll = nc;}

private:
	double fEnergy;
	int    fNcoll;
};

std::vector<Nucleon> make_nucleons(Double_t eCM, Int_t n = 208)
{
	std::vector<Nucleon> v;
	for (Int_t i = 0; i < n; i++)
		v.push_back(Nucleon(eCM / 2., 0));
	return v;
}

Double_t round_energy(double e, double prec = 1.)
{
	return TMath::Ceil( e / prec) * prec;
}

// fname is the glauber root tree file
void gen_from_coll(const char* fname, Int_t nEvStart, Int_t nEvents, Int_t ncollmin, Int_t ncollmax)
{
	// pythia create
	py::Pythia *p = createPythia();
	Double_t eCM = 2760.;

	// setup output
	TString outfname = TString::Format("output_ncoll_%d_%d_nStart_%d_nEv_%d.root", ncollmin, ncollmax, nEvStart, nEvents);
	OutFile out(outfname);

	// setup input
	TFile fin(fname);
	if ( fin.IsOpen() == kFALSE )
	{
		cerr << "[e] unable to r-open " << fname << endl;
		return;
	}
	TTree *t = (TTree*)fin.Get("t");
	Long64_t nentries = t->GetEntries();
	Double_t head[7];
	//b = fTree->Branch(name, &v[0], "npart/D:ncoll/D:bMC/D:xsect/D:taa/D:bNN/D:ncollw/D");
	t->SetBranchAddress("head", &head[0]);
	std::vector<Collision> *pcolls = 0;
	t->SetBranchAddress("colls", &pcolls);
	std::vector<Collision> &colls = *pcolls;

	// figure out the events to run
	cout << "[i] N events in the tree: " << nentries << endl;
	if (nEvents > 0)
	{
		if (nentries > nEvStart + nEvents)
			nentries = nEvStart + nEvents;
	}
	cout << "[i] gen_from_coll: start: " << nEvStart << " stop:" << nentries << endl;
	for (Long64_t i = nEvStart; i < nentries; i++)
	{
		t->GetEntry(i);
		if (head[1] < ncollmin || head[1] > ncollmax)
		{
			cout << TString::Format("    skip ncoll: %4.0f looking for: %4d < ncoll < %4d", head[1], ncollmin, ncollmax) << endl;
			continue;
		}

		cout << "[i] Nev "		<< i;
		cout << " Ncoll:" 	<< colls.size() << " " << head[1];
		cout << " Npart:"	<< head[0] << endl;

		TStopwatch ts;

		std::vector<Nucleon> nA = make_nucleons(eCM);
		std::vector<Nucleon> nB = make_nucleons(eCM);
		for (unsigned int ic = 0; ic < head[1]; ic++)
		{
			Int_t iA    = colls[ic].GetNA();
			Int_t iB    = colls[ic].GetNB();
			Double_t eA = nA[iA].E();
			Double_t eB = nB[iB].E();
			cout << TString::Format("    - collision eA = %4.0f   eB = %4.0f   ncA[%3d] = %3d   ncA[%3d] = %3d",
			                        eA, eB, iA, nA[iA].NColl(), iB, nB[iB].NColl()) << endl;
			if (ic == 0) ts.Start();
			if (eA < 20 || eB < 20)
			{
				cout << TString::Format("    * not calling pythia: eA=%1.3f eB=%1.3f", eA, eB) << endl;
				continue;
			}
			else
			{
				if (eventAB(p, eA, eB) == false)
				{
					cout << "[w] eventAB failed - moving to next collision" << endl;
					continue;
				}
			}
			eA = round_energy(eA);
			eB = round_energy(eB);
			if (head[1] > 10 && ic % 10 == 0 && ic > 0)
			{
				ts.Stop();
				cout << TString::Format("    Real time per event: %1.1f s => ETA (this event): %1.1f min.",
				                        ts.RealTime() / 10.,
				                        ts.RealTime() / 60. * (head[1] - ic) / 10.)
				     << endl;
				ts.Start();
			}
			out.ProcessEvent(*p, head[0], head[1]); // including npart and ncoll from the event
			nA[iA].SetNcoll(nA[iA].NColl() + 1);
			nB[iB].SetNcoll(nB[iB].NColl() + 1);
			nA[iA].SetE(eA);
			nB[iB].SetE(eB);
		}
	}
	fin.Close();
}