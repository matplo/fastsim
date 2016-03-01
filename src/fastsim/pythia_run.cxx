#include "pythia_run.h"

#include <fjwrapper/fjwrapper.h>
#include <wrapper/wrapper.h>

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>
#include <iostream> // needed for io
using namespace std;

//using namespace fastjet; - conflicts with root
namespace fj = fastjet;

#include "util.h"
#include "revent.h"
#include "header.h"

//ROOT
#include <TFile.h>

void pythia_run ( int argc, char *argv[] )
{
	int verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	TString outputFname = SysUtil::getArg("-out", argc, argv);
	if (outputFname.Length() == 0)
	{
		outputFname = "default_toymcpy8_out.root";
	}
	cout << "[i] Output file: " << outputFname.Data() << endl;

	// setup generator
	Wrapper pywrapp;
	pywrapp.set_debug(1);
	py::Pythia *ppythia = GenerUtil::get_pythia();
	pywrapp.add(ppythia); // no need to remember to delete

	py::Pythia &pythia  = *ppythia;
	py::Info& info      = pythia.info;
	py::Event& event    = pythia.event;

	// Extract settings to be used in the main program.
	int nEvent      = pythia.mode("Main:numberOfEvents");
	int nAbort      = pythia.mode("Main:timesAllowErrors");
	double minpThat = pythia.mode("PhaseSpace:pTHatMin");
	double maxpThat = pythia.mode("PhaseSpace:pTHatMax");

	Header head;
	head.fName     = "header";
	head.fVarNames = "nev/D:sigma/D";

	// for the root IO...
	REvent revent;
	TString outputFnameTree = "tree-";
	outputFnameTree += outputFname;
	revent.Init(outputFnameTree.Data());

	GenerUtil::pythia_fj_record pyrecord;
	// Begin event loop. Generate event. Skip if error.
	for (int iEvent = 0; iEvent < nEvent; ++iEvent) 
	{
	    if (!pythia.next()) continue;

		double xsec = info.sigmaGen();

		// deal with the header
	    head.clear();
		head.fValues.push_back(iEvent);
		head.fValues.push_back(xsec);
		revent.FillHeader(&head);

		// particles into vectors
		pyrecord.clear();
		pyrecord.fill_event(pythia);

		// py8 particles into TParticles
		std::vector<TParticle> v = GenerUtil::py8_event_to_vector(ppythia, true); //only final
		//for (unsigned int i = 0; i < v.size(); i++)
		//	std::cout << v[i].GetName() << endl;

		// run jet finders
	    FJWrapper w;
	    Wrapper *jf = w.run(pyrecord.f);
	    std::vector<fj::PseudoJet> j = jf->get<fj::ClusterSequence>()->inclusive_jets();
    	//std::cout << " event #" << iEvent << " => #jets: " << v.size() << endl;
    	revent.FillBranch("j", fj::sorted_by_pt(j));

		std::vector<fj::PseudoJet> sjets;
	    for (unsigned int i = 0; i < j.size(); i++)
	    {
	    	std::vector<fj::PseudoJet> cons = j[i].constituents();
		    Wrapper *sj = w.run(cons, 0.1);
		    std::vector<fj::PseudoJet> v = fj::sorted_by_pt(sj->get<fj::ClusterSequence>()->inclusive_jets());
		    sjets.insert(sjets.end(), v.begin(), v.end());
	    }
    	revent.FillBranch("sjs", sjets);

	    Wrapper *jfr = w.run(pyrecord.f, 0.1);
    	revent.FillBranch("jr", fj::sorted_by_pt(jfr->get<fj::ClusterSequence>()->inclusive_jets()));

	    Wrapper *jfvc = w.run(pyrecord.fv_charged);
	    std::vector<fj::PseudoJet> jvc = jfvc->get<fj::ClusterSequence>()->inclusive_jets();
    	revent.FillBranch("jvc", fj::sorted_by_pt(jvc));

		revent.FinishEvent();

	} // end event loop

	revent.Write();
	std::cout << "[i] Done." << endl;
}
