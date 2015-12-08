#include "Outfile.h"

#include <iostream>
using namespace std;

#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>

#include <vector>
#include <Pythia8/Pythia.h>
namespace py = Pythia8;

#include "deltaE.h"

OutFile::OutFile()
	: f(0)
	, t(0)
	, vparts()
	, pvparts(&vparts)
{
	;
}

OutFile::OutFile(const char *name)
	: f(new TFile(name, "recreate"))
	, t(new TTree("t", "t"))
	, vparts()
	, pvparts(&vparts)
{
	t->Branch("p", &pvparts);
}

OutFile::~OutFile()
{
	f->Write();
	f->Close();
	delete f;
}

void OutFile::AddParticle(py::Particle &p)
{
	TParticle tp(p.id(), p.status(), p.mother1(), p.mother2(), p.daughter1(), p.daughter2(), p.px(), p.py(), p.pz(), p.e(), 0 , 0, 0, 0);
	vparts.push_back(tp);
}

void OutFile::ProcessEvent(py::Pythia &pythia)
{
	Double_t v[6];
	TBranch *b = t->GetBranch("head");
	if (b == 0)
	{
		cout << "[i] Creating a branch: head" << endl;
		b = t->Branch("head", &v[0], "xsec/D:pThat/D:weight/D:eA/D:eB/D:eCM/D");
	}
	else
	{
		b->SetAddress(&v[0]);
	}
	v[0] = pythia.info.sigmaGen();
	v[1] = pythia.info.pTHat();
	v[2] = pythia.info.weight();
	v[3] = pythia.event[1].e(); //pythia.info.eA();
	v[4] = pythia.event[2].e(); //pythia.info.eB();
	double mA = pythia.event[1].m();
	double mB = pythia.event[2].m();
	v[5] = sqrts(v[3], v[4], mA, mB);
	py::Event& event = pythia.event;
	for (Int_t i = 0; i < event.size(); i++)
	{
		// store only the final particles
		if (event[i].isFinal())
			AddParticle(event[i]);
	}
	t->Fill();
	vparts.clear();
}
