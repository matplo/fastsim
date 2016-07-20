#ifndef __HFGUN__HH
#define __HFGUN__HH

#include "py8partongun.h"

class HFGun : public PGun
{
public:
	HFGun();
	virtual ~HFGun();

	virtual void InitOutput();
	virtual void FillOutput();

private:

	ClassDef(HFGun, 0)
};

#endif //__HFGUN__HH