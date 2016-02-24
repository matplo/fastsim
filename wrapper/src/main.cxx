#include "wrapper.h"
#include <iostream>

void other_function(Wrapper &wr)
{
	std::vector<int> *vp = wr.get< std::vector<int> >();
	std::vector<int> &avp = *vp;
	std::cout << " value: " << avp[1] << " (other_function) " << std::endl;
}

void test_wrapper()
{
	std::cout << "[i] testing wrapper..." << std::endl;

	WrapTestClass *tc = new WrapTestClass();
	std::cout << "   tc  at " << tc  << std::endl;

	Wrapper wr;
	wr.add(tc);

	WrapTestClass *tc1 = wr.get<WrapTestClass>();
	std::cout << "   tc1 at " << tc1 << std::endl;

	int *t = wr.get<int>();
	std::cout << "   int t at " << t << std::endl;

	std::vector<int> v;
	v.push_back(123);
	v.push_back(345);
	wr.add(v);

	std::vector<int> *vp = wr.get< std::vector<int> >();
	std::vector<int> &avp = *vp;

	std::cout << " vector size: " << avp.size() 
				<<	" should be: " << v.size()
				<< std::endl;

	std::cout << " value: " << avp[0] << std::endl;
	other_function(wr);

	// obsolete - not needed implementation
	//WrapTestClass *tc2 = 0;
	//wr.get(&tc2);
	//std::cout << "   tc2 at " << tc2 << std::endl;

	std::cout << std::endl;
	wr.list();
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

