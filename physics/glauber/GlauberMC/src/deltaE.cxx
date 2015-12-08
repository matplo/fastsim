#include "deltaE.h"

#include <Pythia8/Pythia.h>

#include <iostream> // needed for io
#include <fstream>
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

	TNtuple *tn = new TNtuple("tn", "tn", "n:xsec:ecm:hardE:deltaE1:deltaE2:nFinal");

	for (int iEvent = 0; iEvent < nEvent; ++iEvent)
	{
		if (!pythia.next()) continue;
		double xsec = info.sigmaGen();

		hevn->Fill(1);
		hevw->Fill(1, xsec);

		double totalE  = getTotalE(event);
		double hardE   = getHardE(event);

		double eA = event[1].e();
		double eB = event[2].e();

		double mA = event[1].m();
		double mB = event[2].m();

		double pA = TMath::Sqrt(eA * eA - mA * mA);
		double pB = TMath::Sqrt(eB * eB - mB * mB);

		double eCM = TMath::Sqrt( TMath::Power(eA + eB, 2.) - TMath::Power(pA + (-1. * pB), 2.) );

		cout << "[i] "
		     << " eA=" << eA << " eB=" << eB
		     << " mA=" << mA << " mB=" << mB
		     << " pA=" << pA << " pB=" << pB
		     << " eCM=" << eCM
		     << endl;

		double deltaE1 = eA - event[5].e();
		double deltaE2 = eB - event[6].e();

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
		tn->Fill(iEvent, xsec, eCM, hardE, deltaE1, deltaE2, nFinal);
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

double sqrts(double eA, double eB, double mA, double mB)
{
	double pA = TMath::Sqrt(eA * eA - mA * mA);
	double pB = TMath::Sqrt(eB * eB - mB * mB);
	double eCM = TMath::Sqrt( TMath::Power(eA + eB, 2.) - TMath::Power(pA + (-1. * pB), 2.) );
	return eCM;
}

py::Pythia* createPythia(const char *cfgFile)
{
	// Read in commands from external file.
	TString spath = gSystem->ExpandPathName(gSystem->Getenv("GLAUBERDIR"));
	TString pycfg = spath + "/GlauberMC/config/pythia8.cfg";
	if (cfgFile != 0)
	{
		pycfg = cfgFile;
	}
	cout << "[i] using pythia config: " << pycfg << endl;
	py::Pythia *ppythia = new py::Pythia;
	ppythia->readFile(pycfg.Data());

	fstream outset("pysettings.conf", std::fstream::out);
	ppythia->settings.listAll(outset);
	outset.close();

	return ppythia;
}

void eventAB(py::Pythia *ppythia, double& eA, double& eB)
{
	if (ppythia == 0)
	{
		return;
	}

	// assume protons
	double mA = 0.93827;
	double mB = 0.93827;
	double eCM = sqrts(eA, eB, mA, mB);

	py::Pythia &pythia = *ppythia;
	py::Info&   info   = pythia.info;
	py::Event&  event  = pythia.event;
	py::Settings sets  = pythia.settings;

	pythia.readString("Beams:frameType = 2");
	pythia.readString(TString::Format("Beams:eA = %f", eA).Data());
	pythia.readString(TString::Format("Beams:eB = %f", eB).Data());
	pythia.readString(TString::Format("Beams:eCM = %f", eCM).Data());
	//sets.mode("Beams:frameType = 2");// collision not in CM
	//sets.parm(TString::Format("Beams::eA = %f", eA).Data());
	//sets.parm(TString::Format("Beams::eA = %f", eB).Data());

	sets.parm("PhaseSpace:pTHatMin", 0);
	sets.parm("PhaseSpace:pTHatMax", -1);
	sets.parm("PhaseSpace:pTHatMinDiverge", 0.5);
	
	pythia.readString("HardQCD:all = off");
	//pythia.readString("SoftQCD:all = on");
	pythia.readString("SoftQCD:nonDiffractive = on");

	pythia.init();

	double eAcheck   = pythia.info.eA(); 		//sets.parm("Beams:eA");
	double eBcheck   = pythia.info.eB(); 		//sets.parm("Beams:eB");
	int    frameType = sets.mode("Beams:frameType");
	double pThatmin  = sets.parm("PhaseSpace:pTHatMin");
	double eCMcheck =  sqrts(eAcheck, eBcheck, mA, mB);

	cout << pythia.info.eCM() << endl;

	cout << TString::Format("    eA=%1.3f eB=%1.3f frame=%d eCM=%1.3f", eA, eB, frameType, eCM) << endl;
	cout << TString::Format("    -> eA=%1.3f eB=%1.3f pTHatMin=%1.3f eCM=%1.3f", eAcheck, eBcheck, pThatmin, eCMcheck) << endl;

	while (1)
	{
		if (!pythia.next()) continue;
		double xsec   = info.sigmaGen();
		double hardE  = getHardE(event);
		int    nFinal = info.nFinal();
		if (nFinal > 2)
		{
			cout << "    number of final partons:" << nFinal << endl;
		}
		double pTHat  = info.pTHat();
		double weight = info.weight();
		double sigma  = info.sigmaGen();
		cout << "   "
		     << " pTHat=" << pTHat
		     << " weight=" << weight
		     << " sigma=" << sigma
		     << endl;
		//double deltaE1 = eA - event[5].e();
		//double deltaE2 = eB - event[6].e();
		eA = eA - event[5].e();
		eB = eB - event[6].e();
		break;
	}
	pythia.readString("Init:showChangedSettings = off");
}

void testNcoll(double eCM, int ncoll)
{
	double eA = eCM / 2.;
	double eB = eCM / 2.;

	py::Pythia *p = createPythia();

	for (int n = 0; n < ncoll; n++)
	{
		cout << "[i] Event " << n
		     << " eA = " << eA
		     << " eB = " << eB
		     << endl;
		eventAB(p, eA, eB);
	}

	delete p;
}