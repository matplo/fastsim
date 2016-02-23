#include "wrapper.h"
#include <iostream>

void test_wrapper()
{
	Wrapper wr;

	WrapTestClass *tc = new WrapTestClass();
	wr.add(tc);

	WrapTestClass *tc1 = 0;
	tc1 = wr.get(tc1);

	WrapTestClass *tc2 = 0;
	wr.get(&tc2);

	//cout << "tc  at " << tc  << endl;
	//cout << "tc1 at " << tc1 << endl;
	//cout << "tc2 at " << tc2 << endl;

}

int main ( int argc, char *argv[] )
{
	for (unsigned int i = 0; i < 1e12; i++)
	{		
		if (i % 100000 == 0)
		{
			std::cout << i << std::endl;
		}
		test_wrapper();
	}
	return 0;
};

