#include "wrapper.h"

#include <iostream>
using namespace std;

void test_wrapper()
{
	Wrapper wr;

	WrapTestClass *tc = new WrapTestClass();
	wr.add(tc);

	WrapTestClass *tc1 = 0;
	tc1 = wr.get(tc1);

	WrapTestClass *tc2 = 0;
	wr.get(&tc2);

	cout << "tc  at " << tc  << endl;
	cout << "tc1 at " << tc1 << endl;
	cout << "tc2 at " << tc2 << endl;

}

