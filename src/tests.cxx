#ifndef __TESTS__HH
#define __TESTS__HH

#include <string>
#include <vector>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequenceArea.hh"
namespace fj = fastjet;

class Wrapper
{
	public:
		Wrapper(const char *name)
		: fName(name)
		{
			;
		}

		virtual 		~Wrapper()
		{
			;
		}

		template <class T>
		unsigned int 	add(T *p, const char *name)
		{
			std::unique_ptr<T> unqp(p);
			fPointers.push_back((void*)&unqp);
			fNames.push_back(std::string(name));
			return fPointers.size() - 1;
		}

		void *			get(const char *named)
		{
			for (unsigned int i = 0; i < fNames.size(); i++)
			{
				if (fNames[i] == named)
				{
					return (void*)fPointers[i].get();
				}
			}
			return (void*)0x0;
		}

	protected:
		Wrapper() 
		: fName("default name") 
		{
			;
		}
		std::string 						fName;
		std::vector< void* > 				fPointers;
		std::vector<std::string> 			fNames;

	private:

};

Wrapper *default_wrapper();
void test_fj_wrapper();

#endif // __TESTS__HH
