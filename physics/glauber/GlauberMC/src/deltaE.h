#ifndef DELTAE_HH
#define DELTAE_HH

#include <Pythia8/Pythia.h>

int deltaE( int argc, char *argv[]);
double sqrts(double eA, double eB, double mA = 0.93827, double mB = 0.93827);

Pythia8::Pythia* createPythia(const char *cfgFile = 0);
void eventAB(Pythia8::Pythia *ppythia, double &eA, double &eB);

void testNcoll(double eCM = 5000., int ncoll = 10);

#endif // #DELTAE_HH