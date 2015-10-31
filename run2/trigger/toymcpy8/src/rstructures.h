#ifndef STRUCTURES_HH
#define STRUCTURES_HH

#include <Rtypes.h>

struct TriggerInfo
{
	Double_t maxjECAL, maxjDCAL, maxgECAL, maxgDCAL;
	Double_t medjECAL, medjDCAL, medgECAL, medgDCAL;
};

struct Header
{
	Double_t xsec;
	Double_t cent;
	Double_t rho;
	Double_t sigma;
};

#endif // STRUCTURES_HH