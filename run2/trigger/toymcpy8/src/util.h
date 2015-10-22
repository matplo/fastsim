#ifndef GENERUTIL_HH
#define GENERUTIL_HH

#include <Rtypes.h>
#include <vector>

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
bool isSet(const char *what, int argc, char **argv);
const char *getArg(const char *what, int argc, char **argv);
};

class AliGenFastModelingEvent;

namespace GenerUtil
{
extern TF1 					*gfunbg;
extern Double_t 			gmean_pt_LHC;
extern Double_t 			gmean_pt_RHIC;
extern Double_t 			gmultLHC;
extern Double_t 			gmultRHIC;
extern Int_t				gNbinLHC;
extern Int_t 				gNbinRHIC;
extern TRandom 				*grnd;
extern Int_t 				gpyParticleOffset;

void						init_defaults();
Double_t					boltzmann(Double_t x[], Double_t par[]);
Double_t					boltzmannRHIC(Double_t x[]);
Double_t					boltzmannLHC(Double_t x[]);
void 						bg_particle(Int_t collider, TLorentzVector &v);
bool 						has_pythia(const fastjet::PseudoJet v);
double 						pt_matched(const fastjet::PseudoJet pyjet, const fastjet::PseudoJet fulljet);
void 						add_particles(std::vector <fastjet::PseudoJet> &to, std::vector <fastjet::PseudoJet> &from, double rotate_phi = 0);
bool 						add_pythia_particles(py::Pythia &pythia, std::vector <fastjet::PseudoJet> &parts, double etaMax = 4., UInt_t offset = 0);

enum
{
	kAny     = 10000,
	kTrack   = 10001,
	kCluster = 10002
} ParType;

AliGenFastModelingEvent*
make_par_response(const Int_t dCentMin, const Int_t dCentMax,
                  const TString sPath = "$RUN2EMCTRIGGER/AliGenFME/inputs",
                  const Bool_t bUseBoltzmann = kTRUE,
                  const Double_t dTrkMeanPt = 0.7,
                  const Double_t dCluMeanPt = 0.7);

std::vector <fastjet::PseudoJet> param_vectors(AliGenFastModelingEvent *gen, Int_t select);

};

#endif // GENERUTIL_HH
