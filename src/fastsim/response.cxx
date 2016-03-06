#include "response.h"
#include "wrapper/wrapper.h"

#include <TParticle.h>
#include <fastjet/PseudoJet.hh>

Response::Response()
: fStorage(new Wrapper)
, fEtaMin(-20.)
, fEtaMax(20.)
{
	;
}

Response::~Response()
{
	delete fStorage;
}

bool Response::AcceptEta(const TParticle &p)
{
	return (p.Eta() > fEtaMin) && (p.Eta() < fEtaMax);
}

bool Response::Accept(const TParticle &p)
{
	return AcceptEta(p);
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

