#include "deltaE.h"

#include <Pythia8/Pythia.h>

#include <iostream> // needed for io
using namespace std;

// this is for root output
#include <TFile.h>
#include <TNtuple.h>
#include <TString.h>
#include <TLorentzVector.h>
#include <TF1.h>
#include <TRandom.h>
#include <TH1F.h>
#include <TH1I.h>
#include <TSystem.h>

//using namespace Pythia8; - conflicts with root
namespace py = Pythia8;

#include "util.h"

int deltaE( int argc, char *argv[])
{
	int verbosity = 0;
	verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	// PYTHIA INIT
	// Generator. Shorthand for event.
	py::Pythia pythia;
	py::Info& info   = pythia.info;
	py::Event& event = pythia.event;

	// Read in commands from external file.
	TString spath = gSystem->ExpandPathName(gSystem->Getenv("GLAUBERDIR"));
	TString pycfg = spath + "/GlauberMC/config/pythia8.cfg";
	pythia.readFile(pycfg.Data());

	// Extract settings to be used in the main program.
	int nEvent      = 1000;

	int nEventUser = atoi(SysUtil::getArg("--nev", argc, argv));
	if (nEventUser > 0)
	{
		nEvent = nEventUser;
	}

	cout << "[i] Run for " << nEvent << " events." << endl;

	pythia.init();

	//ROOT IO
	// for the root IO...

	TString outputFname = SysUtil::getArg("-out", argc, argv);
	if (outputFname.Length() == 0)
	{
		outputFname = "default_emctrig_out.root";
	}
	cout << "[i] Output file: " << outputFname.Data() << endl;

	TFile *fout = new TFile (outputFname.Data(), "RECREATE");
	fout->cd();

	TH1I *hnefn            = new TH1I("hnefn", 	"hnefn;NEF;counts", 		10, 0, 1);
	TH1I *hnefw            = new TH1I("hnefw", 	"hnefw;NEF;counts x xsec", 	10, 0, 1);

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		if (!pythia.next()) continue;
		double xsec = info.sigmaGen();

		hnefn->Fill(1);
		hnefw->Fill(1, xsec);

		if (iEvent % 100 == 0)
		{
			cout << "[info] event #" << iEvent << endl;
		}

		for (int i = 0; i < event.size(); ++i)
		{
			if (event[i].isFinal())
			{
				cout << event[i].name() << endl;
			} // for the final particles
		}// end particle loop within the event

	} // end of event loop

	// Statistics. Histograms.
	pythia.stat();

	fout->Write();
	fout->Close();

	return 0;
}
