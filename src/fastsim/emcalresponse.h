#ifndef __EMCALRESPONSE_HH
#define __EMCALRESPONSE_HH

#include "aliresponse.h"
class EMPartResp;

class EMCalResponse : public AliResponse
{
public:

	EMCalResponse();
	virtual ~EMCalResponse();

	virtual bool Transform(TParticle &p) const;

	virtual void SetupForEMCal();
	virtual void SetupForDCal();

	virtual bool SetupFromArgs(int argc, char *argv[]);

	virtual double EMCalEnergy(const TParticle &p) const;

private:

	Double_t fEMCalTotal2EMfactor;
	EMPartResp *fEMCresponse;

};

#endif //__EMCALRESPONSE_HH
