#ifndef __RESPONSE_HH
#define __RESPONSE_HH

#include <cmath>
#include <vector>

class Wrapper;
class TParticle;
namespace fastjet
{
	class PseudoJet;
};

class Response
{
public:

	Response();
	virtual ~Response();

	virtual bool Accept(const TParticle &p);

	virtual bool AcceptEta(const TParticle &p);

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

  bool operator () (const TParticle &p);
  bool operator () (const fastjet::PseudoJet &pj);

  std::vector<TParticle> operator () (const std::vector<TParticle> &v);
  std::vector<fastjet::PseudoJet> operator () (const std::vector<fastjet::PseudoJet> &v);

private:

	Wrapper* 	fStorage;
	double      fEtaMin;
	double      fEtaMax;

};

#endif //__RESPONSE_HH