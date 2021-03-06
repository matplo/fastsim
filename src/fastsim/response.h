#ifndef __RESPONSE_HH
#define __RESPONSE_HH

#include <cmath>
#include <vector>
#include <limits>

class Wrapper;
namespace fastjet
{
	class PseudoJet;
};

#include <Pythia8/Pythia.h>
#include <TParticle.h>

class Response
{
public:

	enum 
	{
		kAny          = -1,	// -1 - do not care - default behavior
		kKnown        = 0,	// 0 - accept particles with this flag 
		kFinal        = 1,	// 1 - accept only particles with this glag - isFinal
		kFinalVisible = 2, 	// similar to 1 but no neutrons etc...
		kParton       = 10, // 2 - only partons
		kFinalParton  = 11	// 3 - only "final" branch partons		
	};

	Response();
	virtual ~Response();

	virtual bool Accept(TParticle &p) const;
	virtual bool Transform(TParticle &p) const {return true;}
	virtual bool IsInAcceptance(const TParticle &p) const;
	virtual bool AcceptEta(const TParticle &p) const;
	virtual bool AcceptPhi(const TParticle &p) const;
	virtual bool AcceptPt(const TParticle &p) const;
	virtual bool AcceptCharge(const TParticle &p) const;
	virtual bool AcceptStatus(const TParticle &p) const;

	bool IsVisible(const TParticle &p) const;
	bool IsCharged(const TParticle &p) const;

	virtual void SetPtCut(double pt, double ptmax = std::numeric_limits<double>::max())
	{
		fPtMin = pt;
		fPtMax = ptmax;
	}

	virtual void SetEtaCut(double emin, double emax)
	{
		fEtaMin = emin;
		fEtaMax = emax;
	}

	virtual void SetPhiCut(double phimin, double phimax)
	{
		fPhiMin = phimin;
		fPhiMax = phimax;
	}

	virtual void SetEtaAbsCut(double emax)
	{
		fEtaMin = -1. * fabs(emax);
		fEtaMax = +1. * fabs(emax);
	}

	virtual void SetAcceptChargedParticles(bool flag)
	{
		fChargedParticles = flag;
	}

	virtual void SetAcceptNeutralParticles(bool flag)
	{
		fNeutralParticles = flag;
	}

	virtual void SetAcceptChargedNeutral(bool chflag, bool nflag)
	{
		fChargedParticles = chflag;
		fNeutralParticles = nflag;		
	}

	virtual void SetAcceptStatus(int flag)
	{
		fStatusFlag = flag;
	}

	bool IsGluon(const TParticle &p) const;
	bool IsQuark(const TParticle &p) const;
	bool IsFinalBranchParton(const TParticle &p) const;
	bool IsParton(const TParticle &p) const;

	bool 							operator () (const fastjet::PseudoJet &pj);
	std::vector<TParticle> 			operator () (const Pythia8::Pythia &py);
	std::vector<TParticle> 			operator () (const std::vector<TParticle> &v);
	std::vector<fastjet::PseudoJet> operator () (const std::vector<fastjet::PseudoJet> &v);

	static std::vector<fastjet::PseudoJet> convert(const std::vector<TParticle> &v);
	static std::vector<fastjet::PseudoJet> convert(const std::vector<TParticle> &v, const Response &resp);

protected:

	Wrapper* 	fStorage;

private:

	double      fEtaMin;
	double      fEtaMax;

	double      fPhiMin;
	double      fPhiMax;

	double      fPtMin;
	double		fPtMax;

	bool    	fChargedParticles;
	bool    	fNeutralParticles;

	int 		fStatusFlag;

	const Pythia8::Pythia *fPythia; // !set only when () called
	std::vector<TParticle> fPythiaStack; // !set only when () called
};

#endif //__RESPONSE_HH
