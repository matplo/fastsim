#ifndef __ALIRESPONSE_HH
#define __ALIRESPONSE_HH

#include "response.h"

class AliResponse : public Response
{
public:

	AliResponse();
	virtual ~AliResponse();

	virtual bool Accept(const TParticle &p) const;
	virtual bool Efficiency(const TParticle &p) const;

	virtual void SetEfficiency(const char *fname, const char *hname);

private:

	int 	fEffiIndex;

};

#endif //__ALIRESPONSE_HH