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

int verbosity = 0;

double getTotalE(py::Event &event)
{
	double totalE = 0;

	for (int i = 0; i < event.size(); ++i)
	{
		if (event[i].isFinal())
		{
			if (verbosity > 5)
			{
				cout << i << " " << event[i].name() << " " << event[i].e() << endl;
				vector<int> vmoms = event[i].motherList();
				for (int im = 0; im < vmoms.size(); im++)
				{
					cout << "    " << im << " " << event[im].name() << endl;
				}
			}
			totalE = totalE + event[i].e();
		}
	}

	return totalE;
}

double getHardE(py::Event &event)
{
	double hardE = event[5].e() + event[6].e();
	return hardE;
}

int runPythia(py::Pythia *ppythia, int nEvent)
{
	py::Pythia& pythia = *ppythia;
	py::Info&   info   = pythia.info;
	py::Event&  event  = pythia.event;
	pythia.init();

	TString outputFname = ""; //SysUtil::getArg("-out", argc, argv);
	if (outputFname.Length() == 0)
	{
		//double sqrts = pythia.settings.parm("Beams:eCM");
		//outputFname  = TString::Format("sqrts_%1.3f_deltaE_out.root", sqrts);
		double eA = pythia.settings.parm("Beams:eA");
		double eB = pythia.settings.parm("Beams:eB");
		outputFname  = TString::Format("deltaE_eA_%1.3f_eB_%1.3f.root", eA, eB);		
	}

	cout << "[i] Output file: " << outputFname.Data() << endl;

	TFile *fout = new TFile (outputFname.Data(), "RECREATE");
	fout->cd();

	TH1I *hevn            = new TH1I("hevn", 	"hevn;bin number;counts", 			10, 0, 10);
	TH1I *hevw            = new TH1I("hevw", 	"hevw;bin number;counts x xsec", 	10, 0, 10);

	TNtuple *tn = new TNtuple("tn", "tn", "n:xsec:hardE:deltaE1:deltaE2:nFinal");

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		if (!pythia.next()) continue;
		double xsec = info.sigmaGen();

		hevn->Fill(1);
		hevw->Fill(1, xsec);

		cout << info.eA() << event[2].e() << endl;

		double totalE  = getTotalE(event);
		double hardE   = getHardE(event);
		double deltaE1 = info.eA() - event[5].e();
		double deltaE2 = info.eB() - event[6].e();
		int    nFinal  = info.nFinal();
		if (nFinal > 2)
		{
			cout << "    number of final partons:" << nFinal << endl;
		}
		if (verbosity > 2)
		{
			cout << "event: " << iEvent << " total energy (final particles): " << totalE << endl;
			if (totalE <= 0)
			{
				event.list();
			}
		}
		tn->Fill(iEvent, xsec, hardE, deltaE1, deltaE2, nFinal);
	} // end of event loop

	// Statistics. Histograms.
	pythia.stat();

	fout->Write();
	fout->Close();
	delete fout;

	return 0;
}

int deltaE( int argc, char *argv[] )
{
	verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	// Extract settings to be used in the main program.
	int nEvent     = 1;
	int nEventUser = atoi(SysUtil::getArg("--nev", argc, argv));
	if (nEventUser > 0)
	{
		nEvent = nEventUser;
	}
	cout << "[i] Run for " << nEvent << " events." << endl;

	// PYTHIA INIT

	// Read in commands from external file.
	TString spath = gSystem->ExpandPathName(gSystem->Getenv("GLAUBERDIR"));
	TString pycfg = spath + "/GlauberMC/config/pythia8.cfg";

	// Generator. Shorthand for event.
	py::Pythia pythia;
	pythia.readFile(pycfg.Data());
	runPythia(&pythia, nEvent);

	return 0;
}
