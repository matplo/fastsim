#ifndef __FJWRAPPER__HH
#define __FJWRAPPER__HH

#include <string>
#include <vector>
#include <memory>
#include <typeindex>

#include "fastjet/ClusterSequence.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/AreaDefinition.hh"
#include "fastjet/RangeDefinition.hh"
#include "fastjet/PseudoJet.hh"

class VoidType
{
public:
	VoidType()
	: fName("no name")
	, fID(0)
	, fHashCode(0)
	{
		;
	}

	virtual ~VoidType() 
	{
		;
	}

	void set_name(const char *name)
	{
		fName = name;
	}

	void set_hashcode(size_t hash)
	{
		fHashCode = hash;
	}

	void set_id(unsigned int uid)
	{
		fID = uid;
	}

	unsigned int get_id()
	{
		return fID;
	}

	std::string get_name()
	{
		return fName;
	}

	size_t get_hashcode()
	{
		return fHashCode;
	}

protected:
	std::string 		fName;
	unsigned int		fID;
	size_t				fHashCode;
};

template <class T> class Container : public VoidType
{
public:
	Container(T* p, unsigned int id = 0, const char *name = 0)
	: VoidType()
	, fUP(p)
	, fpU(0)
	{
		set_hashcode( std::type_index(typeid(p)).hash_code() );
		if (name != 0)
			set_name(name);
		else
			set_name( std::type_index(typeid(p)).name() );
		set_id(id);
	}

	Container(const Container<T> &c)
	: VoidType()
	, fUP(c.fUP)
	, fpU(0)
	{
		set_name(c.fName.c_str());
		set_id(c.fID);
		set_hashcode(c.fHashCode);

		take_ownership();
	}

	void take_ownership()
	{
		if (fpU != 0)
		{
			delete fpU;
			fpU = 0;
		}
		fpU   = new std::unique_ptr<T>(fUP);
	}

	virtual ~Container()
	{
		self_delete();
	}

	void self_delete()
	{
		delete fpU;		
	}

	T* get(unsigned int i) const
	{
		if (i == get_id())
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

	template <class X>
	bool HasHash(X* p)
	{
		size_t tmphash = std::type_index(typeid(p)).hash_code();
		std::cout << "- comparing: " << fHashCode << " : " << tmphash << std::endl;
		return get_hashcode() == tmphash;
	}

private:
	Container() {;}
	T*				 	fUP;
	std::unique_ptr<T> 	*fpU;
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
