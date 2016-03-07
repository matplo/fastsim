#include "aliresponse.h"
#include "wrapper/wrapper.h"

#include <TParticle.h>
#include <fastjet/PseudoJet.hh>

#include "rndfromh.h"

AliResponse::AliResponse()
	: Response()
	, fEffiIndex(-1)
{
	SetEtaAbsCut(0.9);
	SetPtCut(0.01);
	SetAcceptStatus(1);
}

AliResponse::~AliResponse()
{
	;
}

void AliResponse::SetEfficiency(const char *fname, const char *hname)
{
	RndFromH *tmp = new RndFromH(fname, hname);
	fEffiIndex = fStorage->add(tmp);
}

bool AliResponse::Efficiency(const TParticle &p) const
{
	if (fEffiIndex >= 0)
	{
		unsigned int idx = fEffiIndex;
		return fStorage->get<RndFromH>(idx)->Accept(p.Pt());
	}	
	return false;
}

bool AliResponse::Accept(const TParticle &p) const
{
	return Response::Accept(p) && Efficiency(p);
}
