#ifndef __FJWRAPPER__HH
#define __FJWRAPPER__HH

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

		unsigned int 	add(void *p, const char *name)
		{
			fPointers.push_back(p);
			fNames.push_back(std::string(name));
			return fPointers.size() - 1;
		}

		void *			get(const char *named)
		{
			for (unsigned int i = 0; i < fNames.size(); i++)
			{
				if (fNames[i] == named)
				{
					return fPointers[i];
				}
			}
			return (void*)0x0;
		}

		void *			get(unsigned int i);

		//FJ specific
		fj::ClusterSequence *getCS(const char *named = "ClusterSequence")
		{
			for (unsigned int i = 0; i < fNames.size(); i++)
			{
				if (fNames[i] == named)
				{
					return (fj::ClusterSequence*)fPointers[i];
				}
			}
			return (fj::ClusterSequence*)0x0;
		}

		unsigned int addCS(fj::ClusterSequence *cs, const char *name = "ClusterSequence")
		{
			return add((void*)cs, name);
		}

	protected:
		Wrapper() 
		: fName("default name") 
		{
			;
		}
		std::string 					fName;
		std::vector<void*> 				fPointers;
		std::vector<std::string> 		fNames;

	private:

};

Wrapper *default_wrapper();
void test_fj_wrapper();

#endif // __FJWRAPPER__HH
