#include "deltaE.h"
#include "util.h"

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

	return 0;
};

