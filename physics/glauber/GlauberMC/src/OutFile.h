#ifndef OUTFILE_HH
#define OUTFILE_HH

#include <TParticle.h>

#ifndef __CINT__
class TFile;
class TTree;

#include <vector>
#include <Pythia8/Pythia.h>
namespace py = Pythia8;

class OutFile 
{
public:
	OutFile();
	OutFile(const char *name);
	~OutFile();
	void AddParticle(py::Particle &p);
	void ProcessEvent(py::Pythia &pythia);
private:
	TFile *f; //!
	TTree *t; //!
	std::vector<TParticle> vparts;
	std::vector<TParticle> *pvparts;
};

#endif //__CINT__

#endif // OUTFILE_HH
