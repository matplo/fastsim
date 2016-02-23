#ifndef __FJWRAPPER__HH
#define __FJWRAPPER__HH

#include <string>
#include <vector>
#include <memory>
#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/RangeDefinition.hh"
#include "fastjet/PseudoJet.hh"

class VoidType
{
public:
	VoidType() {;}
	virtual ~VoidType() {;}
};

template <class T> class Container : public VoidType
{
public:
	Container(T* p, const char *name, unsigned int id)
	: VoidType()
	, fUP(p)
	, fpU(0)
	, fName(name)
	, fUID(id)
	{
		;
	}

	Container(const Container<T> &c)
	: VoidType()
	, fUP(c.fUP)
	, fpU(0)
	, fName(c.fName)
	, fUID(c.fUID)
	{
		TakeOwnership();
	}

	void TakeOwnership()
	{
		if (fpU != 0)
		{
			delete fpU;
			fpU = 0;
		}
		fpU = new std::unique_ptr<T>(fUP);		
	}

	virtual ~Container()
	{
		Delete();
	}

	void Delete()
	{
		delete fpU;		
	}

	T* get(unsigned int i) const
	{
		if (i == fUID)
			return fUP;
		return 0x0;
	}

	T* get() const
	{
		return fUP;
	}

	bool IsNamed(const char *name)
	{
		if (fName == name)
			return true;
		return false;
	}

private:
	Container() {;}
	T*				 	fUP;
	std::unique_ptr<T> 	*fpU;
	std::string 		fName;
	unsigned int		fUID;
};

class Wrapper
{
	enum {
		kCS  = 0,  // ClusterSequence
		kJD  = 1,  // JetDefinition
		kAD  = 2,  // AreaDefinition
		kRD  = 3,  // RangeDefinition
		kPJ  = 10  // PseudoJet
	};

	public:
		Wrapper(const char *name)
		: fCSv()
		, fJDv()
		, fADv()
		, fRDv()
		, fPVv()
		, fUniqueIDs()
		{
			;
		}

		virtual 		~Wrapper();

		unsigned int 				addCS(fastjet::ClusterSequence *cs, const char *name = "ClusterSequence");
		fastjet::ClusterSequence *	getCS(const char *name = "ClusterSequence");

		unsigned int 				addJD(fastjet::JetDefinition *JD, const char *name = "JetDefinition");
		fastjet::JetDefinition *	getJD(const char *name = "JetDefinition");

	protected:
		Wrapper() 
		{
			;
		}

		std::vector < Container<fastjet::ClusterSequence> > fCSv;
		std::vector < Container<fastjet::JetDefinition>   > fJDv;
		std::vector < Container<fastjet::AreaDefinition>  > fADv;
		std::vector < Container<fastjet::RangeDefinition> > fRDv;
		std::vector < Container<fastjet::PseudoJet>       >	fPVv;

		std::vector < unsigned int > 						fUniqueIDs;

	private:

};

class TestGC
{
public:
	TestGC() : i(1) {;}
	TestGC(const TestGC &t) : i (t.i) {;}
	virtual ~TestGC()
	{
		std::cout << "test deleted " << i << std::endl;
	}
	void test_call()
	{
		std::cout << "test call ok " << i << std::endl;
	}
private:
	int i;
};

Wrapper *default_wrapper();
void test_fj_wrapper();
void test_wrapp();

#endif // __FJWRAPPER__HH
