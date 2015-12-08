#include "gen_from_coll.h"

#include "Collision.h"

#include <TFile.h>
#include <TTree.h>

#include <vector>
#include <iostream>
using namespace std;

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
	}

	fin.Close();

}