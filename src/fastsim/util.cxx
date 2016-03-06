#include "util.h"

#include <TF1.h>
#include <TRandom.h>
#include <TMath.h>
#include <TLorentzVector.h>
#include <TParticle.h>
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

TRandom 	*grnd;
Int_t 		gpyParticleOffset;

void init_defaults()
{

	grnd              = new TRandom;
	gpyParticleOffset = 10001;

	cout << "[i] GenerUtil::init_defaults() " << endl;
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

	//parts.resize(0);
	parts.clear();

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

//pythia helpers

py::Pythia* get_pythia(string cmndfile /*= "pythia.cmnd"*/)
{
	// Generator. Shorthand for event.
	py::Pythia *ppythia = new py::Pythia();
	// Read in commands from external file.
	ppythia->readFile(cmndfile.c_str());
	ppythia->init();

	return ppythia;
}

void pythia_fj_record::clear()
{
	partons.clear();
	f.clear(); // final
	fv.clear(); // final and visible
	fv_charged.clear(); // ...&charged
	fv_neutral.clear(); // ...&neutral
}

void pythia_fj_record::fill_event(const py::Pythia &pythia, double etamax /*= 10*/)
{
	const py::Event& event    = pythia.event;
	for (int i = 0; i < event.size(); ++i)
	{
		// now the partons
		if ( i == 5 || i == 6)
		{
			fj::PseudoJet p = event[i];
			p.set_user_index(i);
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


// pythia -> root TParticle

	TParticle py8particle_to_TParticle(py::Particle &part)
	{
		TParticle p(
		part.id(),
		part.isFinal(),
		part.mother1(),
		part.mother2(),
		part.daughter1(),
		part.daughter2(),
		part.px(),     // [GeV/c]
		part.py(),     // [GeV/c]
		part.pz(),     // [GeV/c]
		part.e(),      // [GeV]
		part.xProd(),  // [mm]
		part.yProd(),  // [mm]
		part.zProd(),  // [mm]
		part.tProd()); // [mm/c]
		return p;
	};

	void add_py8particle_to_TParticle_vector(std::vector<TParticle> &v, py::Particle &part)
	{
		TParticle p(
		part.id(),
		part.isFinal(),
		part.mother1(),
		part.mother2(),
		part.daughter1(),
		part.daughter2(),
		part.px(),     // [GeV/c]
		part.py(),     // [GeV/c]
		part.pz(),     // [GeV/c]
		part.e(),      // [GeV]
		part.xProd(),  // [mm]
		part.yProd(),  // [mm]
		part.zProd(),  // [mm]
		part.tProd()); // [mm/c]
		v.push_back(p);
	};

	void add_py8particle_to_TParticle_vector(std::vector<TParticle> &v, py::Pythia *py, int i)
	{
		//TParticle p(
		//py->event[i].id(),
		//py->event[i].isFinal(),
		//py->event[i].mother1(),
		//py->event[i].mother2(),
		//py->event[i].daughter1(),
		//py->event[i].daughter2(),
		//py->event[i].px(),     // [GeV/c]
		//py->event[i].py(),     // [GeV/c]
		//py->event[i].pz(),     // [GeV/c]
		//py->event[i].e(),      // [GeV]
		//py->event[i].xProd(),  // [mm]
		//py->event[i].yProd(),  // [mm]
		//py->event[i].zProd(),  // [mm]
		//py->event[i].tProd()); // [mm/c]

		TParticle p = py8particle_to_TParticle(py->event[i]);
		v.push_back(p);
	};

	std::vector<TParticle> py8_event_to_vector(py::Pythia *py, bool final /*= false */)
	{
		std::vector<TParticle> v;
		const py::Event& event    = py->event;
		for (int i = 0; i < event.size(); ++i)
			{
				if (final == true && !event[i].isFinal())
					continue;
				add_py8particle_to_TParticle_vector(v, py, i);
			}
		return v;
	};
};
