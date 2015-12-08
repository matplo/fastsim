#ifndef GLAUBERUTIL_HH
#define GLAUBERUTIL_HH

namespace SysUtil
{
bool        isSet(const char *what, int argc, char **argv);
const char *getArg(const char *what, int argc, char **argv);
double      getArgD(const char *what, int argc, char **argv, double defret);
};

#endif // GLAUBERUTIL_HH
