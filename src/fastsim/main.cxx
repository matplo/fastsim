#include "pythia_run.h"
#include "util.h"
#include "float_exception_tests.h"

int main ( int argc, char *argv[] )
{
	if (SysUtil::isSet("--exceptions-test", argc, argv))
	{
		ExceptionTests::setup_floatp_exceptions();
		return 0;
	}

	pythia_run(argc, argv);

	return 0;
};

