#include "deltaE.h"
#include "util.h"

int main ( int argc, char *argv[] )
{
	if ( SysUtil::isSet("--deltaE", argc, argv) )
	{
		return deltaE ( argc, argv );
	}

	return 0;
};

