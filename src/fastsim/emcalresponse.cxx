#include "emcalresponse.h"
#include "wrapper/wrapper.h"

#include <TParticle.h>
#include <TSystem.h>

#include <fastjet/PseudoJet.hh>

#include "rndfromh.h"
#include "util.h"
#include <EMCpidPar/EMPartResp.h>

#include <iostream>
using namespace std;

EMCalResponse::EMCalResponse()
	: AliResponse()
	, fEMCalTotal2EMfactor(1)
	, fEMCresponse(0)
{
	SetupForEMCal();
	SetPtCut(0.01);
	SetAcceptStatus(kFinalVisible); // exclude massive neutral
}

void EMCalResponse::SetupForEMCal()
{
	SetEtaAbsCut(0.7);
	SetPhiCut(1.4, 3.267);
}

void EMCalResponse::SetupForDCal()
{
	SetEtaAbsCut(0.7);
	SetPhiCut(4.55, 5.7);
}

EMCalResponse::~EMCalResponse()
{
	;
}

bool EMCalResponse::Transform(TParticle &p) const
{
	// PID response is expensive so do check acceptance first
	if (IsInAcceptance(p) && AcceptStatus(p))
	{
		//do PID transform
		cout << "[d] particle:" << p.GetName() << " p = " << p.P() << " E = " << p.Energy();
		double emcE = EMCalEnergy(p);
		cout << " new E = " << emcE;
		p.SetMomentum(p.Px() / p.P() * emcE, p.Py() / p.P() * emcE, p.Pz() / p.P() * emcE, emcE);
		cout << " after transform p = " << p.P() << " E = " << p.Energy() << endl;
	}
	else
	{
		return false;
	}
	return true;
}

bool EMCalResponse::SetupFromArgs(int argc, char *argv[])
{
	fEMCalTotal2EMfactor = 1.0;
	if (SysUtil::isSet("--femc", argc, argv))
	{
		fEMCalTotal2EMfactor = strtod(SysUtil::getArg("--femc", argc, argv), 0);
	}

	TString EMCparPIDfile = "";
	fEMCresponse = 0;
	if (SysUtil::isSet("--femcpar", argc, argv))
	{
		EMCparPIDfile = SysUtil::getArg("--femcpar", argc, argv);
		if (gSystem->IsAbsoluteFileName(EMCparPIDfile))
		{
			cout << "[i] EMCparPIDfile set to: " << EMCparPIDfile << endl;
		}
		else
		{
			EMCparPIDfile = gSystem->ExpandPathName("$FASTSIM/params/alice/EMPartResp.root");
			cout << "[i] EMCparPIDfile reset to: " << EMCparPIDfile << endl;
		}
		fEMCresponse = new EMPartResp(EMCparPIDfile.Data());
	}

	if (SysUtil::isSet("--femc", argc, argv) && SysUtil::isSet("--femcpar", argc, argv))
	{
		cerr << "[e] only one --femc or --femcpar allowed" << endl;
		return false;
	}

	if (fEMCresponse)
	{
		cout << "[i] EMC response at:" << fEMCresponse << endl;
	}
	else
	{
		cout << "[i] EMCalTotal2EMfactor set to : " << fEMCalTotal2EMfactor << endl;
	}

	return true;
}

double EMCalResponse::EMCalEnergy(const TParticle &p) const
{
	Double_t emc = 0;
	if ( IsCharged(p) )
	{
		Int_t ipid = p.GetPdgCode();
		if (fEMCresponse != 0)
		{
			// use the parametrized response
			emc = p.P() * fEMCresponse->GetEop(ipid, p.P());
			if (emc > p.Energy())
			{
				//cout << endl;
				//cout << "param E larger than incident energy? new E = " << emc;
				//cout << " old E = " << p.Energy() << endl;
				//cout << endl;
				emc = p.Energy(); // kill fluctuations beyond inc. particle energy

			}
		}
		else
		{
			if ( ipid == 11 || ipid == -11)
			{
				// electrons are special
				emc = p.Energy();
			}
			else
			{
				// constant fraction of energy!!!
				// emc = p.Energy() * fEMCalTotal2EMfactor;
				// constant fraction of momentum!!!
				emc = p.P() * fEMCalTotal2EMfactor;
			}
		}
	}
	else
	{
		// neutral particles deposit full energy
		// status already checked 
		// needs a check whether visible in pythia!
		// default setting is final
		emc = p.Energy();
	}
	return emc;
}