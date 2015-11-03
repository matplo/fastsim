#ifndef STRUCTURES_HH
#define STRUCTURES_HH

#include <Rtypes.h>

struct TriggerInfo
{
	Double_t maxjECAL, maxjDCAL, maxjECAL8x8, maxjDCAL8x8, maxgECAL, maxgDCAL;
	Double_t medjECAL, medjDCAL, medjECAL8x8, medjDCAL8x8, medgECAL, medgDCAL;
};

struct Header
{
	Double_t xsec;
	Double_t cent;
	Double_t rho;
	Double_t sigma;
};

#endif // STRUCTURES_HH