#include "pythia_run.h"

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>
#include <iostream> // needed for io
using namespace std;

//using namespace fastjet; - conflicts with root
namespace fj = fastjet;

#include "fjwrapper.h"
#include <wrapper.h>

#include "util.h"
#include "revent.h"
#include "header.h"

//ROOT
#include <TFile.h>

py::Pythia* get_pythia()
{
	// Generator. Shorthand for event.
	py::Pythia *ppythia = new py::Pythia();
	// Read in commands from external file.
	ppythia->readFile("pythia.cmnd");
	ppythia->init();

	return ppythia;
}

struct pythia_fj_record
{
	std::vector <fj::PseudoJet> f; // final
	std::vector <fj::PseudoJet> fv; // final and visible
	std::vector <fj::PseudoJet> fv_charged; // ...&charged
	std::vector <fj::PseudoJet> fv_neutral; // ...&neutral
	std::vector <fj::PseudoJet> partons;

	void clear()
	{
		partons.clear();
		f.clear(); // final
		fv.clear(); // final and visible
		fv_charged.clear(); // ...&charged
		fv_neutral.clear(); // ...&neutral
	}

	void fill_event(const py::Pythia &pythia, double etamax = 5)
	{
		const py::Event& event    = pythia.event;
		for (int i = 0; i < event.size(); ++i)
		{
			// now the partons
			if ( i == 5 || i == 6)
			{
				fj::PseudoJet p = event[i];
				partons.push_back(p);
	    	}

			if (abs(event[i].eta()) > etamax) continue;

			if ( event[i].isFinal() )
			{
				fj::PseudoJet particleTemp = event[i];
				particleTemp.set_user_index(i);

				f.push_back(particleTemp);

				if (event[i].isVisible())
				{
					fv.push_back(particleTemp);

					if (event[i].isCharged())
					{
						fv_charged.push_back( particleTemp );
					}
					else
					{
						fv_neutral.push_back( particleTemp );
					}
				} // for the visible particles
			} // for the final particles
	    } // particle loop within an event
	} // fill_event
}; //end pythia_fj_record

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
	py::Pythia *ppythia = get_pythia();
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

	pythia_fj_record pyrecord;
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

		// run jet finders
	    FJWrapper w;
	    Wrapper *jf = w.run(pyrecord.f);
	    std::vector<fj::PseudoJet> j = jf->get<fj::ClusterSequence>()->inclusive_jets();
    	//std::cout << " event #" << iEvent << " => #jets: " << v.size() << endl;

	    Wrapper *jfvc = w.run(pyrecord.fv_charged);
	    std::vector<fj::PseudoJet> jvc = jfvc->get<fj::ClusterSequence>()->inclusive_jets();

    	revent.FillBranch("j", fj::sorted_by_pt(j));
    	revent.FillBranch("jvc", fj::sorted_by_pt(jvc));

		revent.FinishEvent();

	} // end event loop

	revent.Write();
	std::cout << "[i] Done." << endl;
}
