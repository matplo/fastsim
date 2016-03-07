#include "response.h"
#include "wrapper/wrapper.h"

#include <TParticle.h>
#include <TParticlePDG.h>
#include <fastjet/PseudoJet.hh>

#include <iostream>
using namespace std;

Response::Response()
	: fStorage(new Wrapper)
	, fEtaMin(-20.)
	, fEtaMax(20.)
	, fPtMin(1e-3)
	, fPtMax(std::numeric_limits<double>::max())
	, fChargedParticles(true)
	, fNeutralParticles(true)
	, fStatusFlag(-1)
{
	fStorage->set_debug(1);
}

Response::~Response()
{	
	delete fStorage;
}

bool Response::AcceptEta(const TParticle &p) const
{
	return (p.Eta() > fEtaMin) && (p.Eta() < fEtaMax);
}

bool Response::AcceptPt(const TParticle &p) const
{
	return (p.Pt() > fPtMin) && (p.Pt() < fPtMax);
}

bool Response::AcceptCharge(const TParticle &p) const
{
	TParticlePDG *pdg = p.GetPDG ( 1 );
	if ( pdg == 0x0 )
	{
		// by default reject unknown particles
		return false;
	}
	Double_t ch          = pdg->Charge();
	if (fabs(ch) > 0 && fChargedParticles)
	{
		return true;
	}
	if (ch == 0 && fNeutralParticles)
	{
		return true;
	}	
	return false;
}

bool Response::AcceptStatus(const TParticle &p) const
{
	if (fStatusFlag == -1)
		return true;
	if (fStatusFlag == 2)
	{
		if (p.GetPdgCode() == 21)
			return true;
		TParticlePDG *pdg = p.GetPDG ( 1 );
		if ( pdg == 0x0 )
		{
			// by default reject unknown particles
			return false;
		}
		Double_t ch          = pdg->Charge();
		//std::cout << " charge: " << fabs(ch) << " name: " << p.GetName() << std::endl;
		if ( fabs(ch) < 3.0 && fabs(ch) > 0.0) // ROOT returns charge in units |e|/3.
			return true;
		return false;
	}
	return (p.GetStatusCode() == fStatusFlag);
}

bool Response::Accept(const TParticle &p) const
{
	return AcceptEta(p) && AcceptPt(p) && AcceptCharge(p) && AcceptStatus(p);
}

bool Response::operator () (const TParticle &p)
{
	return Accept(p);
}

bool Response::operator () (const fastjet::PseudoJet &pj)
{
	TParticle p(-1, 1, 0, 0, 0, 0,
				pj.px(), pj.py(), pj.pz(), pj.e(),
				0, 0, 0, 0);
	return Accept(p);
}

std::vector<TParticle> Response::operator () (const std::vector<TParticle> &v)
{
	std::vector<TParticle> ret;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (Accept(v[i]))
			ret.push_back(v[i]);
	}
	return ret;
}

std::vector<fastjet::PseudoJet> Response::operator () (const std::vector<fastjet::PseudoJet> &v)
{
	std::vector<fastjet::PseudoJet> ret;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		//TParticle(Int_t pdg, Int_t status,
	    //          Int_t mother1, Int_t mother2,
	    //          Int_t daughter1, Int_t daughter2,
	    //          Double_t px, Double_t py, Double_t pz, Double_t etot,
	    //          Double_t vx, Double_t vy, Double_t vz, Double_t time);
		//TParticle p(-1, 1, 0, 0, 0, 0,
		//			v[i].px(), v[i].py(), v[i].pz(), v[i].e(),
		//			0, 0, 0, 0);
		TParticle p;
		p.SetMomentum(v[i].px(), v[i].py(), v[i].pz(), v[i].e());
		if (Accept(p))
			ret.push_back(v[i]);
	}
	return ret;
}

std::vector<TParticle> Response::operator () (const Pythia8::Pythia &py)
{
	std::vector<TParticle> ret;
	const Pythia8::Event& event    = py.event;
	for (int i = 0; i < event.size(); ++i)
		{
			TParticle p(
						event[i].id(),
						event[i].isFinal(),
						event[i].mother1(),
						event[i].mother2(),
						event[i].daughter1(),
						event[i].daughter2(),
						event[i].px(),     // [GeV/c]
						event[i].py(),     // [GeV/c]
						event[i].pz(),     // [GeV/c]
						event[i].e(),      // [GeV]
						event[i].xProd(),  // [mm]
						event[i].yProd(),  // [mm]
						event[i].zProd(),  // [mm]
						event[i].tProd()); // [mm/c]

			if (Accept(p))
			{
				//if (fStatusFlag == 2)
				//	std::cout << " - accepted " << p.GetName() << " accept status: " << AcceptStatus(p) << endl;
				ret.push_back(p);
			}
		}
	return ret;
}

std::vector<fastjet::PseudoJet> Response::convert(const std::vector<TParticle> &v)
{
	std::vector<fastjet::PseudoJet> ret;		
	for (unsigned int i = 0; i < v.size(); i++)
	{
		fastjet::PseudoJet p(v[i].Px(), v[i].Py(), v[i].Pz(), v[i].Energy());
		p.set_user_index(i);
		ret.push_back(p);
	}
	return ret;
}

std::vector<fastjet::PseudoJet> Response::convert(const std::vector<TParticle> &v, const Response &resp)
{
	std::vector<fastjet::PseudoJet> ret;		
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (resp.Accept(v[i]))
		{
			fastjet::PseudoJet p(v[i].Px(), v[i].Py(), v[i].Pz(), v[i].Energy());
			p.set_user_index(i);
			ret.push_back(p);
		}
	}
	return ret;
}
