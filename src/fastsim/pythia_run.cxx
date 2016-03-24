#include "pythia_run.h"

#include <TNtuple.h>

#include <fjwrapper/fjwrapper.h>
#include <wrapper/wrapper.h>
#include <pyutil/partongun.h>

#include <Pythia8/Pythia.h>
#include <Pythia8Plugins/FastJet3.h>
#include <iostream> // needed for io
using namespace std;

//using namespace fastjet; - conflicts with root
namespace fj = fastjet;

#include "util.h"
#include "response.h"
#include "aliresponse.h"
#include "emcalresponse.h"

#include <revent/revent.h>
#include <revent/header.h>

//ROOT
#include <TFile.h>

void pythia_run ( int argc, char *argv[] )
{
	int verbosity = atoi(SysUtil::getArg("-v", argc, argv));
	cout << "[i] Verbosity : " << verbosity << endl;

	TString outputFname = SysUtil::getArg("-out", argc, argv);
	if (outputFname.Length() == 0)
	{
		outputFname = "default_fastsim_out.root";
	}
	cout << "[i] Output file: " << outputFname.Data() << endl;

	// setup generator
	py::Pythia *ppythia = 0;

	Wrapper pywrapp;
	pywrapp.set_debug(1);

	double pgunpt           = atof(SysUtil::getArg("-pgunpt", argc, argv));
	double pgunptmax        = atof(SysUtil::getArg("-pgunptmax", argc, argv));
	PyUtil::PartonGun *pgun = 0x0;
	if (pgunpt > 0)
	{
		int pgunid = atoi(SysUtil::getArg("-pgunid", argc, argv));
		if (pgunid <= 0) pgunid = 21;
		pgun       = new PyUtil::PartonGun(pgunid);
		pgun->SetSpectrum(pgunid, pgunpt, pgunptmax);
		pgun->InitPythia();
		ppythia = pgun->GetPythia();

		cout << "[i] Setup parton gun... id:" << pgunid << " pt: " << pgunpt << endl;

		pywrapp.add(pgun);
	}
	else
	{
		string cfgfile = SysUtil::getArg("-config", argc, argv);
		if (cfgfile.length() == 0)
		{
			cfgfile = "./pythia.cmnd";
		}
		ppythia = GenerUtil::get_pythia(cfgfile);
		pywrapp.add(ppythia); // no need to remember to delete

		cout << "[i] Setup standard pythia..." << endl;
	}

	cout << "[i] ppythia is at " << ppythia << endl;

	py::Pythia &pythia  = *ppythia;
	py::Info& info      = pythia.info;
	py::Event& event    = pythia.event;

	// Extract settings to be used in the main program.
	int nEvent        = 1;
	//int nAbort      = pythia.mode("Main:timesAllowErrors");
	//double minpThat = pythia.mode("PhaseSpace:pTHatMin");
	//double maxpThat = pythia.mode("PhaseSpace:pTHatMax");

	int userNEvent = atoi(SysUtil::getArg("-nev", argc, argv));
	if (userNEvent > 0)
	{
		cout << "[i] User set number of events: " << userNEvent << endl;
		nEvent 		= userNEvent;
	}
	else
	{
		nEvent      = pythia.mode("Main:numberOfEvents");
	}

	// for the root IO...
	REvent revent;
	TString outputFnameTree = "tree-";
	outputFnameTree += outputFname;
	revent.Init(outputFnameTree.Data());
	TNtuple *tnjptresol = new TNtuple("jptresol", "jptresol", "sigma:pt0:pt1:dpt:dr");

	Header head;
	head.fName     = "header";
	head.fVarNames = "nev/D:sigma/D";

	// filtering of jets and particles
	double jetR = 0.4;

    Response respPartons;
	respPartons.SetEtaAbsCut(0.9 - jetR);
    respPartons.SetPtCut(0.05);
    respPartons.SetAcceptStatus(Response::kParton);

    Response resp;
    resp.SetEtaAbsCut(0.9);
    resp.SetPtCut(0.05);
    resp.SetAcceptStatus(Response::kFinal);

    Response charged;
    charged.SetEtaAbsCut(0.9);
    charged.SetPtCut(0.05);
    charged.SetAcceptStatus(Response::kFinal);
    charged.SetAcceptChargedNeutral(true, false);

    AliResponse alicharged;
    alicharged.SetAcceptChargedNeutral(true, false);
	alicharged.SetEfficiency(	"$FASTSIM/params/alice/CombinedEfficiencies_centeta_smooth.root", 
								"ratiocent_MB_true_effi_tmp_CombinedEfficiencies_centeta_smooth");

	EMCalResponse emcal;
	emcal.SetupFromArgs(argc, argv);
	EMCalResponse dcal;
	dcal.SetupForDCal();
	dcal.SetupFromArgs(argc, argv);

    Response jet_resp;
    jet_resp.SetPtCut(0.1);
    jet_resp.SetEtaAbsCut(0.9 - jetR);

    Response jet_resp5;
    jet_resp5.SetPtCut(5);
    jet_resp5.SetEtaAbsCut(0.9 - jetR);

    Response jet_resp10;
    jet_resp10.SetPtCut(10);
    jet_resp10.SetEtaAbsCut(0.9 - jetR);

    Response jet_resp20;
    jet_resp20.SetPtCut(20);
    jet_resp20.SetEtaAbsCut(0.9 - jetR);

	cout << "[i] Starting event loop..." << endl;
	// Begin event loop. Generate event. Skip if error.
	for (int iEvent = 0; iEvent < nEvent; ++iEvent) 
	{		
		if (pgun != 0x0)
		{
			if (pgun->NextEvent() == false)
				break;
			//cout << "[d] next pgun ok..." << endl;
		}

		//cout << "[d] before next..." << endl;

	    if (!pythia.next()) 
	    	continue;

		//cout << "[d] next was ok..." << endl;

		double xsec = info.sigmaGen();
		if (xsec == 0.0)
		{
			if (pgun != 0x0)
				xsec = 1.; // just a safe thing to do
		}

		//cout << "[d] xsec is: " << xsec << endl;

		// deal with the header
	    head.clear();
		head.fValues.push_back(iEvent);
		head.fValues.push_back(xsec);
		revent.FillHeader(&head);

	    respPartons.SetAcceptStatus(Response::kParton);
		std::vector<TParticle> 		partons       = respPartons(pythia);
	    respPartons.SetAcceptStatus(Response::kFinalParton);
		std::vector<TParticle> 		partonsf      = respPartons(pythia);
		//GenerUtil::dump(partons);
		//GenerUtil::dump(partonsf);
		std::vector<fj::PseudoJet> 	psjpartons    = Response::convert(partonsf);

		std::vector<TParticle> 		pfinal        = resp(pythia);
		std::vector<fj::PseudoJet> 	psjfinal      = Response::convert(pfinal);		

		std::vector<TParticle> 		pcharged      = charged(pythia);
		//std::vector<fj::PseudoJet> 	psjcharged    = Response::convert(pcharged);
		std::vector<fj::PseudoJet> 	psjcharged    = Response::convert(pfinal, charged); // keep indexes

		std::vector<TParticle> 		pchargedali   = alicharged(pythia);
		//std::vector<fj::PseudoJet> 	psjchargedali = Response::convert(pchargedali);
		std::vector<fj::PseudoJet> 	psjchargedali = Response::convert(pfinal, alicharged);

		std::vector<TParticle>		emcal_parts   = emcal(pythia);
		std::vector<TParticle>		dcal_parts    = dcal(pythia);

		// run jet finders
	    FJWrapper w;

	    // jet finder on partons
	    Wrapper *jfpartons = w.run( psjpartons, jetR );
		std::vector<fj::PseudoJet> jpartons 		= fj::sorted_by_pt(jfpartons->get<fj::ClusterSequence>()->inclusive_jets());
		std::vector<fj::PseudoJet> jpartonscut		= jet_resp(jpartons);

	    // all particles
	    Wrapper *jf = w.run( psjfinal, jetR );
		std::vector<fj::PseudoJet> j    			= fj::sorted_by_pt(jf->get<fj::ClusterSequence>()->inclusive_jets());
		std::vector<fj::PseudoJet> jcut 			= jet_resp(j);

	    // first on charged particles
	    Wrapper *jfch = w.run( psjcharged, jetR );
		std::vector<fj::PseudoJet> jcharged    		= fj::sorted_by_pt(jfch->get<fj::ClusterSequence>()->inclusive_jets());
		std::vector<fj::PseudoJet> jchargedcut 		= jet_resp(jcharged);

		// charged particles with ALICE cuts
	    Wrapper *jfalich = w.run( psjchargedali, jetR );
		std::vector<fj::PseudoJet> jchargedali    	= fj::sorted_by_pt(jfalich->get<fj::ClusterSequence>()->inclusive_jets());
		std::vector<fj::PseudoJet> jchargedalicut 	= jet_resp(jchargedali);

		// check what what jets were found from the input
		std::vector<fj::PseudoJet> jfound  			= GenerUtil::matched_jets_any(jcut, 	   		jchargedalicut);
		std::vector<fj::PseudoJet> jfound5			= GenerUtil::matched_jets_any(jcut, 	   		jet_resp5(jchargedalicut));
		std::vector<fj::PseudoJet> jfound10			= GenerUtil::matched_jets_any(jcut, 	   		jet_resp10(jchargedalicut));
		std::vector<fj::PseudoJet> jfound20			= GenerUtil::matched_jets_any(jcut, 	   		jet_resp20(jchargedalicut));
		std::vector<fj::PseudoJet> jchargedfound  	= GenerUtil::matched_jets_any(jchargedcut, 		jchargedalicut);

		std::vector<fj::PseudoJet> jfoundpartonsfull= GenerUtil::matched_jets_dr(jpartonscut,		jcut, jetR / 2.);

		//std::vector<fj::PseudoJet> jfoundpartons	= GenerUtil::matched_jets_dr(psjpartons,   		jchargedalicut, jetR / 2.);
		std::vector<fj::PseudoJet> jfoundpartons	= GenerUtil::matched_jets_dr(jpartonscut,		jchargedalicut, jetR / 2.);

		std::vector<fj::PseudoJet> jfoundpartons5	= GenerUtil::matched_jets_dr(jpartonscut,		jet_resp5(jchargedalicut), jetR / 2.);
		std::vector<fj::PseudoJet> jfoundpartons10	= GenerUtil::matched_jets_dr(jpartonscut,		jet_resp10(jchargedalicut), jetR / 2.);
		std::vector<fj::PseudoJet> jfoundpartons20	= GenerUtil::matched_jets_dr(jpartonscut, 		jet_resp20(jchargedalicut), jetR / 2.);

		//GenerUtil::dump(partons);
		//GenerUtil::dump(jpartons);

		// fill output
		for (unsigned int ij = 0; ij < jfound.size(); ij++)
		{
			float pt0       = jfound[ij].perp();
			unsigned int ik = jfound[ij].user_index();
			float pt1       = jchargedalicut[ik].perp();
			float dpt       = (pt0-pt1);
			float dr		= jfound[ij].delta_R(jchargedalicut[ik]);
			if (dpt < -1000.)
			{
				cerr << "[w] strange dpt:" << dpt << " = (" << pt0 << " - " << pt1 << ") / " << pt0 << endl;
			}
			tnjptresol->Fill(xsec, pt0, pt1, dpt, dr);
		}

    	revent.FillBranch("parton", 			partons);
    	revent.FillBranch("partonf", 			partonsf);

    	revent.FillBranch("pfinal", 			pfinal);
    	revent.FillBranch("pcharged", 			pcharged);
    	revent.FillBranch("pchargedali", 		pchargedali);

    	revent.FillBranch("jparton", 			jpartonscut);
    	revent.FillBranch("jfoundpartonfull", 	jfoundpartonsfull);
    	revent.FillBranch("jfoundparton", 		jfoundpartons);
    	revent.FillBranch("jfoundparton5",		jfoundpartons5);
    	revent.FillBranch("jfoundparton10",		jfoundpartons10);
    	revent.FillBranch("jfoundparton20",		jfoundpartons20);

    	revent.FillBranch("jcut",		 		jcut);
    	revent.FillBranch("jfound",		 		jfound);
    	revent.FillBranch("jfound5",	 		jfound5);
    	revent.FillBranch("jfound10",	 		jfound10);
    	revent.FillBranch("jfound20",	 		jfound20);

    	revent.FillBranch("jchargedcut", 		jchargedcut);
    	revent.FillBranch("jchargedalicut",		jchargedalicut);
    	revent.FillBranch("jchargedfound",		jchargedfound);

    	revent.FillBranch("emcal_parts", 		emcal_parts);
    	revent.FillBranch("dcal_parts", 		dcal_parts);

		revent.FinishEvent();

	} // end event loop

	revent.Write();
	std::cout << "[i] Done." << endl;
}
