#ifndef GENERUTIL_HH
#define GENERUTIL_HH

#include <Rtypes.h>
#include <TParticle.h>

#include <vector>
#include <string>

class TH2I;
class TF1;
class TRandom;
class TLorentzVector;
class TTree;
#include <TString.h>

#include <Pythia8/Pythia.h>
//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

//#include <fastjet/PseudoJet.hh>
#include <Pythia8Plugins/FastJet3.h>

#include <TriggerMaker.h>
#include <TriggerMappingEmcalSimple.h>

namespace SysUtil
{
bool 		isSet(const char *what, int argc, char **argv);
const char *getArg(const char *what, int argc, char **argv);
double 		getArgD(const char *what, int argc, char **argv, double defret);
};

//class AliGenFastModelingEvent;

namespace GenerUtil
{

	extern TRandom 				*grnd;
	extern Int_t 				gpyParticleOffset;

	bool 						has_pythia(const fastjet::PseudoJet v);
	double 						pt_matched(const fastjet::PseudoJet pyjet, const fastjet::PseudoJet fulljet);
	double 						pt_matched_any(const fastjet::PseudoJet pyjet, const fastjet::PseudoJet fulljet);
	std::vector<fastjet::PseudoJet> 
	matched_jets_any(const std::vector<fastjet::PseudoJet> &jets, 
					const std::vector<fastjet::PseudoJet> &jetscut);

	std::vector<fastjet::PseudoJet> 
	matched_jets_dr(const std::vector<fastjet::PseudoJet> &jets, 
					const std::vector<fastjet::PseudoJet> &jetscut, 
					double drcut);

	void 						add_particles(std::vector <fastjet::PseudoJet> &to, std::vector <fastjet::PseudoJet> &from, double rotate_phi = 0);
	bool 						add_pythia_particles(py::Pythia &pythia, std::vector <fastjet::PseudoJet> &parts, double etaMax = 4., UInt_t offset = 0);

	py::Pythia* get_pythia(std::string cmndfile = "pythia.cmnd");

	struct pythia_fj_record
	{
		std::vector <fastjet::PseudoJet> f; // final
		std::vector <fastjet::PseudoJet> fv; // final and visible
		std::vector <fastjet::PseudoJet> fv_charged; // ...&charged
		std::vector <fastjet::PseudoJet> fv_neutral; // ...&neutral
		std::vector <fastjet::PseudoJet> partons;

		void clear();
		void fill_event(const py::Pythia &pythia, double etamax = 10);
	};

	bool index_in(unsigned int idx, const fastjet::PseudoJet j);
	double sum_perp_constit(const fastjet::PseudoJet j);
	void debug_constituents(const fastjet::PseudoJet j0, const fastjet::PseudoJet j1, const fastjet::PseudoJet j2);


	void dump(const std::vector<TParticle> &v);
	void dump(const std::vector<fastjet::PseudoJet> &v);
	TParticle py8particle_to_TParticle(py::Particle &part);
	void add_py8particle_to_TParticle_vector(std::vector<TParticle> &v, py::Particle &part);
	void add_py8particle_to_TParticle_vector(std::vector<TParticle> &v, py::Pythia *py, int i);
	std::vector<TParticle> py8_event_to_vector(py::Pythia *py, bool final = false);
};

namespace EMCalTriggerUtil
{
	struct TriggerInfo
	{
		Double_t maxjECAL, maxjDCAL, maxjECAL8x8, maxjDCAL8x8, maxgECAL, maxgDCAL;
		Double_t medjECAL, medjDCAL, medjECAL8x8, medjDCAL8x8, medgECAL, medgDCAL;
	};

	class EMCTrigger
	{
	public:
		EMCTrigger();
		virtual ~EMCTrigger();
		void AddParticles(const std::vector<TParticle> &v);
		void ProcessEvent();
		// to be implemented: take the whole event; apply EMCalParamResponse...
		// void Process(const Pythia8::Pythia &py);
		void FillBranch(TTree *t, const char *bname);
		void Reset();

		const TriggerMaker * GetTM() {return &fTM;}
		const TriggerInfo * GetInfo() {return &fInfo;}

	private:
		TriggerSetup fSetup;
		TriggerMaker fTM;
		TriggerInfo  fInfo;
	};

};

#endif // GENERUTIL_HH
