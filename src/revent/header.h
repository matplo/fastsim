#ifndef __HEADER__HH
#define __HEADER__HH

#include <string>
#include <vector>

struct Header
{
	//double 		fValues[20];
	std::vector<double> fValues;
	std::string fName;
	std::string fVarNames;

	void clear()
	{
		fValues.clear();
	}
};

#endif // __HEADER__HH
