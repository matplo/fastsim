#include "deltaE.h"
#include "glauberutil.h"
#include "gen_from_coll.h"

#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>

#include <iostream>
using namespace std;

TString get_token(TString s, Int_t i, const char* delim)
{
	TObjArray *a = s.Tokenize(TString(delim));
	TObjString *so = (TObjString*)a->At(i);
	if (so)
		return so->String();
	else
		return TString("0");
}

int main ( int argc, char *argv[] )
{
	if ( SysUtil::isSet("--deltaE", argc, argv) )
	{
		return deltaE ( argc, argv );
	}

	if ( SysUtil::isSet("--test", argc, argv) )
	{
		testNcoll();
		return 0;
	}

	if ( SysUtil::isSet("--gen", argc, argv) )
	{
		TString fname = SysUtil::getArg("--in", argc, argv);

		TString scoll = SysUtil::getArg("--ncoll", argc, argv);
		Int_t ncollmin = 0;
		Int_t ncollmax = 5000;		
		if (scoll.Length() > 0 && scoll.Contains(":"))			
		{
			ncollmin = get_token(scoll, 0, ":").Atoi();
			ncollmax = get_token(scoll, 1, ":").Atoi();
			if (ncollmax == 0)
				ncollmax = 5000;
			cout << "[i] ncoll min=" << ncollmin << " max=" << ncollmax << endl;
		}

		TString snev = SysUtil::getArg("--nev", argc, argv);
		Int_t nEvStart = 0;
		Int_t nEvents = -1;		
		if (snev.Length() > 0 && snev.Contains(":"))			
		{
			nEvStart = get_token(snev, 0, ":").Atoi();
			nEvents  = get_token(snev, 1, ":").Atoi();
			if (nEvents == 0)
				nEvents = -1;
			cout << "[i] nev start=" << nEvStart << " n=" << nEvents << endl;
		}

		gen_from_coll(fname.Data(), nEvStart, nEvents, ncollmin, ncollmax);
		return 0;
	}

	cout << endl << "[i] Done." << endl;
	return 0;
};

