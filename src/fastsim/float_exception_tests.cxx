#include "float_exception_tests.h"

#include <csignal>
#include <cfenv>
#include <cstdio>
#include <cstdlib>

#include <limits>
#include <cmath>

#include <vector>
#include <iostream> // needed for io
using namespace std;

namespace ExceptionTests
{
	void handler(int sig) 
	{
		cerr << "[signal handler] Floating Point Exception... signal is: " << sig << endl;
		exit(0);
	}

	void setup_floatp_exceptions()
	{
		std::numeric_limits<int>::signaling_NaN();
		std::numeric_limits<double>::signaling_NaN();
		cout << std::numeric_limits<double>::has_signaling_NaN << endl;
		cout << "[i] setup floatp exceptions..." << endl;
		std::vector<int> flags;
		flags.push_back(FE_INVALID);
		flags.push_back(FE_DIVBYZERO);
		flags.push_back(FE_OVERFLOW);
		flags.push_back(FE_UNDERFLOW);
		flags.push_back(FE_ALL_EXCEPT);
		flags.push_back(FE_ALL_EXCEPT & ~FE_INEXACT);
		for (unsigned int i = 0; i < flags.size(); i++)
		{
			int  test = fetestexcept(flags[i]);
			cout << "    flag: " << flags[i] << " : " << test << endl;
		}
		int itmp = feraiseexcept(FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);
		cout << "[i] feraiseexcept returned with " << itmp << endl;
		for (unsigned int i = 0; i < flags.size(); i++)
		{
			int  test = fetestexcept(flags[i]);
			cout << "    flag: " << flags[i] << " : " << test << endl;
		}

	#ifndef __clang__
	// this is enough with gcc to get the nans as exceptions(!)
		feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
	#endif
		signal(SIGFPE, handler);

		cout << "[i] log of a -1: " << log(-1.) << endl;
		cout << "[i] sqrt of a -1: " << sqrt(-1.) << endl;

		cout << "    -> trying division by double zero.." << endl;
		double dirty = 0.0;
		double nanval=0.0/dirty;

		int zero = 0;
		cout << "    -> trying division by int zero.." << endl;
		int trouble = zero/zero;
		cout << "    -> trying zero x 1.e350 .." << endl;
		double what = trouble * 1.e350;
		cout << "[i] trouble is: " << trouble << " what is: " << 0/what << endl;

		int modulo = 10 % 0;

		printf("[end] Succeeded! dirty=%lf, nanval=%lf\n",dirty,nanval);
	}

}