#include "toymcpy8.h"
#include "emctrig.h"
#include "emctrig_par.h"
#include "emctrig_par_revent.h"
#include "emctrig_test.h"
#include "util.h"
int main ( int argc, char *argv[] )
{
	if ( SysUtil::isSet("--emc", argc, argv) )
	{
		return emctrig ( argc, argv );
	}
	if ( SysUtil::isSet("--emc-par", argc, argv) )
	{
		if ( SysUtil::isSet("--old", argc, argv) )
		{
			return emctrig_par ( argc, argv );
		}
		else
		{
			return emctrig_par_revent( argc, argv);
		}
	}
	if ( SysUtil::isSet("--emc-test", argc, argv) )
	{
		return emctrig_test( argc, argv);		
	}
	return toymcpy8 ( argc, argv );
};

