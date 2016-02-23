#ifndef __WRAPPER__HH
#define __WRAPPER__HH

#include <string>
#include <vector>
#include <memory>
#include <typeindex>

#include <iostream>

class WrapType
{
public:
	WrapType()
	: fName("no name")
	, fID(0)
	, fHashCode(0)
	{
		;
	}

	virtual ~WrapType() 
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

template <class T> class WrapContainer : public WrapType
{
public:
	WrapContainer(T* p, unsigned int id = 0, const char *name = 0)
	: WrapType()
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

	WrapContainer(const WrapContainer<T> &c)
	: WrapType()
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

	virtual ~WrapContainer()
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
		//std::cout << "- comparing: " << fHashCode << " : " << tmphash << std::endl;
		return get_hashcode() == tmphash;
	}

private:
	WrapContainer() {;}
	T*				 	fUP;
	std::unique_ptr<T> 	*fpU;
};

class Wrapper
{
	public:
		Wrapper()
		{
			;
		}

		virtual 		~Wrapper()
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				//std::cout << "Deleting " << fPointers[i]->get_name() << std::endl;
				delete fPointers[i];
			}
		}

		template <class T>
		unsigned int 	add(T *p)
		{
			unsigned int id = fPointers.size();
			std::string name = std::type_index(typeid(p)).name();
			WrapContainer<T> *c = new WrapContainer<T>(p, id, name.c_str());
			c->take_ownership();
			fPointers.push_back(c);
			return id;
		}

		template <class T>
		T* get(T **p)
		{
			*p = 0x0;
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				bool has_hash = c->HasHash(*p);
				//std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					//std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						//std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
					}
					*p = c->get();
					return c->get();
				}
			}
			return 0x0;
		}

		template <class T>
		T* get(T *)
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				T *p = 0;
				bool has_hash = c->HasHash(p);
				//std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					//std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						//std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
					}
					return c->get();
				}
			}
			return 0x0;
		}

	protected:

		std::vector< WrapType* >		fPointers;

	private:

};

class WrapTestClass
{
public:
	WrapTestClass() : i(1) {;}
	WrapTestClass(const WrapTestClass &t) : i (t.i) {;}
	virtual ~WrapTestClass()
	{
		//std::cout << "WrapTestClass::~WrapTestClass() " << i << " at 0x" << this << std::endl;
	}
	void test_call()
	{
		//std::cout << "WrapTestClass test_call" << i << std::endl;
	}
private:
	int i;
};

#endif // __WRAPPER__HH
