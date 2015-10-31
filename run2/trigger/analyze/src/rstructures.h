#ifndef STRUCTURES_HH
#define STRUCTURES_HH

#include <Rtypes.h>

struct TriggerInfo
{
	Double_t maxjECAL;
	Double_t maxjDCAL;
	Double_t maxgECAL;
	Double_t maxgDCAL;

	Double_t medjECAL;
	Double_t medjDCAL;
	Double_t medgECAL;
	Double_t medgDCAL;
};

struct Header
{
	Double_t xsec;
	Double_t cent;
	Double_t rho;
	Double_t sigma;
};

#endif // STRUCTURES_HH