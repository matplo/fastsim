#include "toymcpy8.h"
#include "emctrig.h"
#include "emctrig_par.h"
#include "util.h"
int main ( int argc, char *argv[] )
{
	if ( SysUtil::isSet("--emc", argc, argv) )
	{
		return emctrig ( argc, argv );
	}
	if ( SysUtil::isSet("--emc-par", argc, argv) )
	{
		return emctrig_par ( argc, argv );
	}
	return toymcpy8 ( argc, argv );
};

