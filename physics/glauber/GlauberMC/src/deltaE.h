#ifndef DELTAE_HH
#define DELTAE_HH

int deltaE( int argc, char *argv[]);
double sqrts(double eA, double eB, double mA = 0.93827, double mB = 0.93827);

void testNcoll(double eCM = 5000., int ncoll = 10);

#ifndef __CINT__
#include <Pythia8/Pythia.h>
Pythia8::Pythia* createPythia(const char *cfgFile = 0);
void eventAB(Pythia8::Pythia *ppythia, double &eA, double &eB, int verbosity=0);
#endif // __CINT__

#endif // DELTAE_HH