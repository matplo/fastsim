#include "glauberutil.h"

#include <string>
#include <cstdlib>
#include <cstring>

using namespace std;

namespace SysUtil
{
bool isSet(const char *what, int argc, char **argv)
{
	string swhat = what;
	for (int i = 0; i < argc; i++)
	{
		string ar = argv[i];
		//if (strcmp(what, argv[i]) == 0)
		if (ar.compare(swhat) == 0 && swhat.compare(ar) == 0)
		{
			return true;
		}
	}
	return false;
}

const char *getArg(const char *what, int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return argv[i + 1];
	}
	return "";
}

double getArgD(const char *what, int argc, char **argv, double defret = 0.0)
{
	double retval = defret;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(what, argv[i]) == 0)
			if ( i + 1 < argc)
				return strtod(argv[i + 1], 0);
		//return std::stod(argv[i + 1]);
	}
	return defret;
}

};
