#ifndef GENERUTIL_HH
#define GENERUTIL_HH

#include <Rtypes.h>
#include <vector>

class TH2I;
class TF1;
class TRandom;
class TLorentzVector;
#include <TString.h>

#include <Pythia8/Pythia.h>
//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

//#include <fastjet/PseudoJet.hh>
#include <Pythia8Plugins/FastJet3.h>

namespace SysUtil
{
bool 		isSet(const char *what, int argc, char **argv);
const char *getArg(const char *what, int argc, char **argv);
double 		getArgD(const char *what, int argc, char **argv, double defret);
};

class AliGenFastModelingEvent;

namespace GenerUtil
{

extern TRandom 				*grnd;
extern Int_t 				gpyParticleOffset;

bool 						has_pythia(const fastjet::PseudoJet v);
double 						pt_matched(const fastjet::PseudoJet pyjet, const fastjet::PseudoJet fulljet);
void 						add_particles(std::vector <fastjet::PseudoJet> &to, std::vector <fastjet::PseudoJet> &from, double rotate_phi = 0);
bool 						add_pythia_particles(py::Pythia &pythia, std::vector <fastjet::PseudoJet> &parts, double etaMax = 4., UInt_t offset = 0);

};

#endif // GENERUTIL_HH
