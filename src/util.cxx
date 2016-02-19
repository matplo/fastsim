#include "util.h"

// PARAM response
#include <AliGenFastModelingEvent.h>

#include <TriggerMaker.h>
#include <TriggerMappingEmcalSimple.h>

#include <TF1.h>
#include <TRandom.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TSystem.h>
#include <TH2I.h>
#include <TFile.h>

namespace fj = fastjet;

#include <iostream> // needed for io
#include <string>
using namespace std;

namespace SysUtil
{
bool isSet(const char *what, int argc, char **argv)
{
	string swhat = what;
	for (int i = 0; i < argc; i++)
	{
		string ar = argv[i];
		//if (strcmp(what, argv[i]) == 0)
		if (ar.compare(swhat) == 0 && swhat.compare(ar) == 0)
		{
			return true;
		}
	}
	return false;
}

const char *getArg(const char *what, int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return argv[i + 1];
	}
	return "";
}

double getArgD(const char *what, int argc, char **argv, double defret = 0.0)
{
	double retval = defret;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return strtod(argv[i + 1], 0);
		//return std::stod(argv[i + 1]);
	}
	return defret;
}
};

namespace GenerUtil
{
TF1 		*gfunbg;
Double_t 	gmean_pt_LHC;
Double_t 	gmean_pt_RHIC;
Double_t 	gmultLHC;
Double_t 	gmultRHIC;
Int_t		gNbinLHC;
Int_t 		gNbinRHIC;
TRandom 	*grnd;
Int_t 		gpyParticleOffset;

void init_defaults()
{
	gfunbg            = 0;
	gmean_pt_LHC      = 0.7; // LHC energy (2.76 TeV)
	gmean_pt_RHIC     = 0.5; //RHIC energy (0.2 TeV)
	gmultLHC          = 6100;  //  LHC 0-5% in |eta|<1 is ~8000
	gmultRHIC         = 2800; // RHIC 0-5% in |eta|<1
	gNbinLHC          = 1500; // this is for 0-10%! - make it consistent
	gNbinRHIC         =  500;
	grnd              = new TRandom;
	gpyParticleOffset = 10001;

	cout << "[i] GenerUtil::init_defaults() " << endl;
}

Double_t boltzmann(Double_t x[], Double_t par[])
{
	return 2. / par[0] * x[0] * TMath::Exp(-(2. / par[0]) * x[0]);
}

Double_t boltzmannRHIC(Double_t x[])
{
	return 2. / gmean_pt_RHIC * x[0] * TMath::Exp(-(2. / gmean_pt_RHIC) * x[0]);
}

Double_t boltzmannLHC(Double_t x[])
{
	return 2. / gmean_pt_LHC * x[0] * TMath::Exp(-(2. / gmean_pt_LHC) * x[0]);
}

void bg_particle(Int_t collider, TLorentzVector &v)
{
	if (gfunbg == 0)
	{
		if (collider == 0)
		{
			// generator function
			// gfunbg = new TF1("bgfun", &boltzmannRHIC, 0, 100);
			gfunbg = new TF1("bgfun", &boltzmann, 0, 100, 1);
			gfunbg->SetParameter(0, gmean_pt_RHIC);
			gfunbg->SetNpx(1000); // to avoid finite binning randomization
		}
		else
		{
			// generator function
			// gfunbg = new TF1("bgfun", &boltzmannLHC, 0, 100);
			gfunbg = new TF1("bgfun", &boltzmann, 0, 100, 1);
			gfunbg->SetParameter(0, gmean_pt_LHC);
			gfunbg->SetNpx(1000); // to avoid finite binning randomization
		}
	}

	Double_t pt =  gfunbg->GetRandom(0, 200);
	Double_t eta = grnd->Rndm() * 2.2 - 1.1;
	Double_t phi = grnd->Rndm() * TMath::Pi() * 2. - TMath::Pi();
	v.SetPtEtaPhiM(pt, eta, phi, 0.);
}

bool has_pythia(const fj::PseudoJet v)
{
	vector<fj::PseudoJet> consts = v.constituents();
	for (UInt_t i = 0; i < consts.size(); i++)
	{
		if (consts[i].user_index() < gpyParticleOffset)
			return true;
	}
	return false;
}

double pt_matched(const fj::PseudoJet pyjet, const fj::PseudoJet fulljet)
{
	if (has_pythia(fulljet) == false) return 0;
	double ptmatch = 0;
	vector<fj::PseudoJet> consts_py   =   pyjet.constituents();
	vector<fj::PseudoJet> consts_full = fulljet.constituents();
	for (UInt_t i = 0; i < consts_py.size(); i++)
	{
		for (UInt_t j = 0; j < consts_full.size(); j++)
		{
			if (consts_py[i].user_index() == consts_full[j].user_index())
			{
				// printf("|-> %3.2f %3.2f %3.2f | %3.2f %3.2f %3.2f \n",
				// 	 consts_py[i].perp(), consts_py[i].perp(), consts_py[i].perp(),
				// 	 consts_full[j].perp(), consts_full[j].perp(), consts_full[j].perp());
				ptmatch += consts_py[i].perp();
			}
		}
	}
	return ptmatch;
}

void add_particles(std::vector <fj::PseudoJet> &to,
                   std::vector <fj::PseudoJet> &from,
                   double rotate_phi)
{
	for (UInt_t i = 0; i < from.size(); i++)
	{
		if (rotate_phi == 0)
		{
			to.push_back(from[i]);
		}
		else
		{
			fj::PseudoJet v = from[i];
			double newphi = v.phi() + rotate_phi;
			double px = v.perp() * TMath::Cos(newphi);
			double py = v.perp() * TMath::Sin(newphi);
			double pz = v.pz();
			double e  = v.e();
			v.reset(px, py, pz, e);
			//v.set_user_index(from[i].user_index()); // not needed?
			to.push_back(v);
		}
	}
}

bool add_pythia_particles(py::Pythia &pythia,
                          std::vector <fj::PseudoJet> &parts,
                          double etaMax,
                          UInt_t offset)
{
	int    select  = 2;      // Which particles are included?
	int    massSet = 0;      // Which mass are they assumed to have? 2-self masses; 1-pions; 0-zero

	parts.resize(0);

	py::Info& info = pythia.info;
	py::Event& event = pythia.event;

	if (!pythia.next()) return false;
	py::Vec4   pTemp;
	double mTemp;

	// double eta = 0;
	// double phi = 0;
	// double pt  = 0;

	for (int i = 0; i < event.size(); ++i)
	{
		if (event[i].isFinal())
		{

			// Require visible/charged particles inside detector.
			if      (select > 2 &&  event[i].isNeutral() ) continue;
			else if (select == 2 && !event[i].isVisible()) continue;
			if (etaMax < 20. && abs(event[i].eta()) > etaMax) continue;

			// pt  = event[i].pT();
			// phi = event[i].phi();
			// eta = event[i].eta();

			// Create a PseudoJet from the complete Pythia particle.
			fj::PseudoJet particleTemp = event[i];
			// Optionally modify mass and energy.
			pTemp = event[i].p();
			mTemp = event[i].m();
			if (massSet < 2)
			{
				mTemp = (massSet == 0 || event[i].id() == 22) ? 0. : 0.13957;
				pTemp.e( sqrt(pTemp.pAbs2() + mTemp * mTemp) );
				particleTemp.reset_momentum( pTemp.px(), pTemp.py(),
				                             pTemp.pz(), pTemp.e() );
			}

			// Store acceptable particles as input to Fastjet.
			// Conversion to PseudoJet is performed automatically
			// with the help of the code in FastJet3.h.
			particleTemp.set_user_index(parts.size() + offset);
			//particleTemp.set_user_index(i + offset);
			parts.push_back( particleTemp );
		} // for the final particles
	}// end particle loop within the event

	return true;
}

// PARAM background

AliGenFastModelingEvent *make_par_background(
    const Int_t dCentMin, const Int_t dCentMax,
    const TString sPath,
    const Bool_t bUseBoltzmann,
    const Double_t dTrkMeanPt,
    const Double_t dCluMeanPt)
{
	TString name = TString::Format("pResponse-bmann%d-cent%d-%d-meanpT%1.1f-meancl%1.1f",
	                               bUseBoltzmann, dCentMin, dCentMax, dTrkMeanPt, dCluMeanPt);
	AliGenFastModelingEvent * gen = new AliGenFastModelingEvent(name.Data());
	gen->SetCentralityRange(dCentMin, dCentMax);  // set centrality range
	// get track/cluster multiplicity + the fluctuations from the given cent range in LHC11h data
	// get track/cluster pT, eta, phi distribution from the given cent range in LHC11h data

	/* optional: user defined track/cluster multiplicity ranges

	  gen->SetMultiplicityUser(kTRUE);
	  gen->SetTrackMultiplicityRangeUser(dUserTrkMultMin, dUserTrkMultMax);
	  gen->SetClusterMultiplicityRangeUser(dUserCluMultMin, dUserCluMultMax); */

	gen->SetUseBoltzmann(bUseBoltzmann);  // sample track/cluster pT from bUseBoltzmann, otherwise it will be sampled from data
	gen->SetTrackMeanPt(dTrkMeanPt);      // mean pT of tracks
	gen->SetClusterMeanPt(dCluMeanPt);    // mean pT of clusters
	//=============================================================================

	TString sPathExpanded = gSystem->ExpandPathName(sPath);
	cout << "[i] AliGenFME in path: " << sPathExpanded << endl;
	if (gen->Init(sPathExpanded))
	{
		cerr << "[e] Init AliGenFastModelingEvent failed!" << endl
		     << "     path was    : " << sPath << endl
		     << "     expanded to : " << sPathExpanded
		     << endl;
		delete gen;
		gen = 0;
	}

	return gen;
}

AliGenFastModelingEvent *make_par_background_mtune(
    const Double_t dTrkMultMin, const Double_t dTrkMultMax,
    const Double_t dCluMultMin, const Double_t dCluMultMax,
    const TString sPath,
    const Bool_t bUseBoltzmann,
    const Double_t dTrkMeanPt,
    const Double_t dCluMeanPt)
{
	TString name = TString::Format("pResponse-bmann%d-mult%1.1f-%1.1f-meanpT%1.1f-meancl%1.1f",
	                               bUseBoltzmann, dTrkMultMin, dTrkMultMax, dTrkMeanPt, dCluMeanPt);
	AliGenFastModelingEvent * gen = new AliGenFastModelingEvent(name.Data());

	gen->SetMultiplicityUser(kTRUE);
	gen->SetTrackMultiplicityRangeUser  (dTrkMultMin, dTrkMultMax);
	gen->SetClusterMultiplicityRangeUser(dCluMultMin, dCluMultMax);

	gen->SetUseBoltzmann(bUseBoltzmann);  // sample track/cluster pT from bUseBoltzmann, otherwise it will be sampled from data
	gen->SetTrackMeanPt(dTrkMeanPt);      // mean pT of tracks
	gen->SetClusterMeanPt(dCluMeanPt);    // mean pT of clusters
	//=============================================================================

	TString sPathExpanded = gSystem->ExpandPathName(sPath);
	//cout << "[i] AliGenFME in path: " << sPathExpanded << endl;
	if (gen->Init(sPathExpanded))
	{
		cerr << "[e] Init AliGenFastModelingEvent failed!" << endl
		     << "     path was    : " << sPath << endl
		     << "     expanded to : " << sPathExpanded
		     << endl;
		delete gen;
		gen = 0;
	}

	return gen;
}

std::vector <fj::PseudoJet> param_vectors(AliGenFastModelingEvent *gen, Int_t select)
{
	//if (gen->InitEvent()) must be called before

	std::vector <fj::PseudoJet>	ret;

	fj::PseudoJet v;
	Double_t dPt = 0., dEta = 0., dPhi = 0.;

	if (select == kTrack || select == kAny)
	{
		for (Int_t it = 0; it < gen->GetTrackMultiplicity(); it++)
		{
			if (gen->GetTrackPtEtaPhi(dPt, dEta, dPhi)) continue;
			//reset_PtYPhiM (double pt, double y, double phi, double m=0.0)
			v.reset_PtYPhiM(dPt, dEta, dPhi, 0.0); // all tracks are zero mass
			v.set_user_index(kTrack);
			ret.push_back(v);
		}
	}
	if (select == kCluster || select == kAny)
	{
		for (Int_t ic = 0; ic < gen->GetClusterMultiplicity(); ic++)
		{
			if (gen->GetClusterPtEtaPhi(dPt, dEta, dPhi)) continue;
			v.reset_PtYPhiM(dPt, dEta, dPhi, 0.0); // all clusters are zero mass
			v.set_user_index(kCluster);
			ret.push_back(v);
		}
	}

	return ret;
}

void fillBadChannelFromHistogram(TriggerMaker *tm, TH2I *hin)
{
	for (Int_t ieta = 1; ieta < hin->GetNbinsX(); ieta++)
	{
		for (Int_t iphi = 1; iphi < hin->GetNbinsY(); iphi++)
		{
			Double_t eta = hin->GetXaxis()->GetBinCenter(ieta);
			Double_t phi = hin->GetYaxis()->GetBinCenter(iphi);
			if (hin->GetBinContent(ieta, iphi) <= 0)
				continue;
			TriggerMappingEmcalSimple map = tm->GetTriggerChannelMapping();
			if (map.IsEMCAL(eta, phi))
			{
				TriggerChannel ch = map.GetPositionFromEtaPhi(eta, phi);
				Int_t row = ch.GetRow();
				Int_t col = ch.GetCol();
				tm->AddBadChannelEMCAL(col, row);
			}
			if (map.IsDCALPHOS(eta, phi))
			{
				TriggerChannel ch = map.GetPositionFromEtaPhi(eta, phi);
				Int_t row = ch.GetRow();
				Int_t col = ch.GetCol();
				tm->AddBadChannelDCALPHOS(col, row);
			}
		}
	}
}

TriggerMaker *createTriggerMaker(const char *emcalMap, const char* dcalMap)
{
	TriggerSetup tsetup;
	tsetup.SetThresholds(0., 0., 0., 0.);
	tsetup.SetTriggerBitConfig(TriggerBitConfigNew());

	TriggerMaker *tm = new TriggerMaker();
	tm->SetTriggerSetup(tsetup);

	TFile *fin = 0;
	TH2I *hin = 0;

	if (emcalMap)
	{
		fin = TFile::Open(emcalMap);
		if (fin)
		{
			hin = (TH2I*)fin->Get("hmask");
			if (hin)
			{
				fillBadChannelFromHistogram(tm, hin);
			}
		}
		std::vector<TriggerBadChannelContainer::TriggerChannelPosition> vEMCal = tm->GetBadChannelContainerEMCAL().GetChannels();
		cout << "[i] EMCal bad channels: " << emcalMap << " N=" << vEMCal.size() << endl;
	}
	else
	{
		cout << "[i] No bad channels in ECal" << endl;
	}

	if (dcalMap)
	{
		fin = TFile::Open(dcalMap);
		if (fin)
		{
			hin = (TH2I*)fin->Get("hmask");
			if (hin)
			{
				fillBadChannelFromHistogram(tm, hin);
			}
		}
		std::vector<TriggerBadChannelContainer::TriggerChannelPosition> vDCal = tm->GetBadChannelContainerDCALPHOS().GetChannels();
		cout << "[i] DCal  bad channels: " <<  dcalMap << " N=" <<  vDCal.size() << endl;
	}
	else
	{
		cout << "[i] No bad channels in DCal" << endl;
	}


	return tm;
}

};
