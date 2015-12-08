#include "deltaE.h"
#include "util.h"
#include "gen_from_coll.h"

#include <TString.h>

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
		gen_from_coll(fname.Data());
		return 0;
	}

	return 0;
};

