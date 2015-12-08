#include "gen_from_coll.h"

#include "Collision.h"

#include <TFile.h>
#include <TTree.h>

#include <vector>
#include <iostream>
using namespace std;


class Nucleon
{
public:
	Nucleon()
		: fEnergy(0.0)
		, fNcoll(0)
	{ ; }
	Nucleon(double e, double ncoll = 0)
		: fEnergy(0.0)
		, fNcoll(0)
	{ ; }

	~Nucleon() {;}

	double E() { return fEnergy;}
	int    NColl() {return fNcoll;}

	void setE(double ve) {fEnergy = ve;}
	void setNcoll(int nc) {fNcoll = nc;}

private:
	double fEnergy;
	int    fNcoll;
};

// fname is the glauber root tree file
void gen_from_coll(const char* fname)
{
	TFile fin(fname);
	if ( fin.IsOpen() == kFALSE )
	{
		cerr << "[e] unable to r-open " << fname << endl;
		return;
	}

	TTree *t = (TTree*)fin.Get("t");

	std::vector<Collision> *pv = 0;
	t->SetBranchAddress("cls", &pv);
	std::vector<Collision> &v = *pv;

	Long64_t userNentries = 100;

	for (Long64_t i = 0; i < userNentries; i++)
	{
		t->GetEntry(i);
		cout << "[i] Nev "		<< i << endl;
		cout << "    Ncoll:" 	<< v.size() << endl;

		std::vector<Nucleon> nA;
		std::vector<Nucleon> nB;
	}

	fin.Close();

}