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

	Response();
	virtual ~Response();

	virtual bool Accept(const TParticle &p) const;
	virtual bool AcceptEta(const TParticle &p) const;
	virtual bool AcceptPt(const TParticle &p) const;
	virtual bool AcceptCharge(const TParticle &p) const;
	virtual bool AcceptStatus(const TParticle &p) const;

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
		// -1 - do not care - default behavior
		// 0 - accept particles with this flag 
		// 1 - accept only particles with this glag - isFinal
		// 2 - only partons
		// 3 - only "final" branch partons
		fStatusFlag = flag;
	}

	bool IsGluon(const TParticle &p) const;
	bool IsQuark(const TParticle &p) const;
	bool IsFinalBranchParton(const TParticle &p) const;
	bool IsParton(const TParticle &p) const;

	bool operator () (const TParticle &p);
	bool operator () (const fastjet::PseudoJet &pj);

	std::vector<TParticle> operator () (const Pythia8::Pythia &py);
	std::vector<TParticle> operator () (const std::vector<TParticle> &v);
	std::vector<fastjet::PseudoJet> operator () (const std::vector<fastjet::PseudoJet> &v);

	static std::vector<fastjet::PseudoJet> convert(const std::vector<TParticle> &v);
	static std::vector<fastjet::PseudoJet> convert(const std::vector<TParticle> &v, const Response &resp);

protected:

	Wrapper* 	fStorage;

private:

	double      fEtaMin;
	double      fEtaMax;

	double      fPtMin;
	double		fPtMax;

	bool    	fChargedParticles;
	bool    	fNeutralParticles;

	int 		fStatusFlag;

	const Pythia8::Pythia *fPythia; // !set only when () called
	std::vector<TParticle> fPythiaStack; // !set only when () called
};

#endif //__RESPONSE_HH
