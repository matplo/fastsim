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
	, fPhiMin(-20.)
	, fPhiMax(20.)
	, fPtMin(1e-3)
	, fPtMax(std::numeric_limits<double>::max())
	, fChargedParticles(true)
	, fNeutralParticles(true)
	, fStatusFlag(kAny)
	, fPythia(0x0)
	, fPythiaStack()
{
	fStorage->set_debug(1);
}

Response::~Response()
{	
	delete fStorage;
}

bool Response::IsInAcceptance(const TParticle &p) const
{
	return AcceptEta(p) && AcceptPhi(p);
}

bool Response::AcceptEta(const TParticle &p) const
{
	return (p.Eta() > fEtaMin) && (p.Eta() < fEtaMax);
}

bool Response::AcceptPhi(const TParticle &p) const
{
	return (p.Phi() > fPhiMin) && (p.Phi() < fPhiMax);
}

bool Response::AcceptPt(const TParticle &p) const
{
	return (p.Pt() > fPtMin) && (p.Pt() < fPtMax);
}

bool Response::IsCharged(const TParticle &p) const
{
	TParticlePDG *pdg = p.GetPDG ( 1 );
	if ( pdg == 0x0 )
	{
		// by default reject unknown particles
		return false;
	}
	Double_t ch          = pdg->Charge();
	return !(ch == 0);	
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

bool Response::IsVisible(const TParticle &p) const
{
	if (p.GetStatusCode() != 1)
		{
			return false;
		}
	if (IsCharged(p) == false)
	{
		if (p.GetMass() > 0)
		{
			return false;
		}
	}
	return true;
}

bool Response::IsGluon(const TParticle &p) const
{
	return (p.GetPdgCode() == 21);
}

bool Response::IsQuark(const TParticle &p) const
{
	return (IsParton(p) && p.GetPdgCode() != 21);
}

bool Response::IsParton(const TParticle &p) const
{
	if (p.GetPdgCode() == 21)
		return true;
	// this is a string in pythia - not a parton
	if (p.GetPdgCode() == 90)
		return false;
	TParticlePDG *pdg = p.GetPDG ( 1 );
	if ( pdg == 0x0 )
	{
		// by default reject unknown particles (including "system")
		return false;
	}
	Double_t ch          = pdg->Charge();
	//std::cout << " charge: " << fabs(ch) << " name: " << p.GetName() << std::endl;
	if ( fabs(ch) < 3.0 && fabs(ch) > 0.0) // ROOT returns charge in units |e|/3 <-> quarks
		return true;
	return false;
}

bool Response::IsFinalBranchParton(const TParticle &p) const
{
	if (fPythia == 0x0)
	{
		cerr << "[e] Response::AcceptStatus needs pythia for status fStatusFlag == 3" << endl;
		return false;
	}
	if (IsParton(p))
	{
		bool retval = true;
		for (unsigned int i = p.GetDaughter(0); i <= p.GetDaughter(1); i++)
		{
			if (fPythiaStack.size() < i)
			{
				TParticle d(fPythiaStack[i]);
				if (IsParton(d))
				{
					//cout << "parton: " << p.GetName() 
					//	<< " is not a 'final shower' parton because one of the daugters is a parton:" 
					//	<< d.GetName() << " pdg code: " << d.GetPdgCode() << endl;
					retval = false;
				}
			}
		}
		return retval;
	}
	return false;
}

bool Response::AcceptStatus(const TParticle &p) const
{
	if (fStatusFlag == kAny)
		return true;
	if (fStatusFlag == kParton)
	{
		if (IsParton(p))
			return true;
		// this is a string in pythia
		if (p.GetPdgCode() == 90)
			return true;
		return false;
	}
	if (fStatusFlag == kFinalParton)
	{
		return IsFinalBranchParton(p);
	}
	if (fStatusFlag == kFinal)
	{
		return (p.GetStatusCode() == 1);
	}
	if (fStatusFlag == kFinalVisible)
	{
		return IsVisible(p);
	}
	return false;
}

bool Response::Accept(TParticle &p) const
{
	if (Transform(p))
		return IsInAcceptance(p) && AcceptPt(p) && AcceptCharge(p) && AcceptStatus(p);
	else
		return false;
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
		TParticle p(v[i]);
		if (Accept(p))
			ret.push_back(p);
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
	fPythia = &py;
	fPythiaStack.clear();
	for (int i = 0; i < event.size(); ++i)
		{
			//if (fStatusFlag == kFinalVisible)
			//{
			//	if (!event[i].isVisible())
			//		continue;
			//}
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
			fPythiaStack.push_back(p);
			if (Accept(p))
			{
				//if (fStatusFlag == 2)
				//	std::cout << " - accepted " << p.GetName() << " accept status: " << AcceptStatus(p) << endl;
				ret.push_back(p);
			}
		}
	fPythia = 0x0;
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
		TParticle p(v[i]);
		if (resp.Accept(p))
		{
			fastjet::PseudoJet psj(v[i].Px(), v[i].Py(), v[i].Pz(), v[i].Energy());
			psj.set_user_index(i);
			ret.push_back(psj);
		}
	}
	return ret;
}
