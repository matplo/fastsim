#include "toymcpy8.h"
#include "emctrig.h"
#include "util.h"
int main ( int argc, char *argv[] )
{
	if ( SysUtil::isSet("--emc", argc, argv) )
	{
		return emctrig ( argc, argv );
	}
	return toymcpy8 ( argc, argv );
};

