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

	void set_type_name(const char *tname)
	{
		fTypeName = tname;
	}

	unsigned int get_id() const
	{
		return fID;
	}

	std::string get_name() const
	{
		return fName;
	}

	size_t get_hashcode() const
	{
		return fHashCode;
	}

	std::string get_type_name() const 
	{
		return fTypeName;
	}

	friend std::ostream& operator <<(std::ostream& out, const WrapType& c)
	{
		out << "> @ 0x" << &c << " type name: " << std::type_index(typeid(c)).name() << std::endl
			<< "    name:     " << c.get_name() << std::endl
			<< "    type:     " << c.get_type_name() << std::endl
			<< "    hashcode: " << c.get_hashcode() << std::endl
			<< "    id:       " << c.get_id() << std::endl;
		return out;
	} 

protected:
	std::string 		fName;
	std::string         fTypeName;
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
	, fIdx(typeid(p))
	{
		set_hashcode( fIdx.hash_code() );
		if (name != 0)
			set_name(name);
		else
			set_name( fIdx.name() );
		set_id(id);
		set_type_name(fIdx.name());
	}

	WrapContainer(const WrapContainer<T> &c)
	: WrapType()
	, fUP(c.fUP)
	, fpU(0)
	, fIdx(c.fIdx)
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
		fpU->reset();
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

	bool HasHash(size_t tmphash)
	{
		return get_hashcode() == tmphash;
	}

private:
	WrapContainer() {;}
	T*				 	fUP;
	std::unique_ptr<T> 	*fpU;
	std::type_index     fIdx;
};

class Wrapper
{
	public:
		Wrapper()
		: fPointers()
		, idcount(0)
		, debug(0)
		{
			;
		}

		virtual 		~Wrapper()
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				if (debug) 
					{
						std::cout << "[d] Deleting... " << fPointers[i]->get_name() << std::endl;
						std::cout << *fPointers[i] << std::endl;
					}

				delete fPointers[i];
			}
		}

		template <class T>
		unsigned int 	add(T *p)
		{
			if (contains(p))
			{
				std::string name = std::type_index(typeid(p)).name();
				throw std::runtime_error(std::string("adding same pointer twice (?) typeid name: ") + name);
			}
			unsigned int id = idcount;
			idcount++;
			std::string name = std::type_index(typeid(p)).name();
			WrapContainer<T> *c = new WrapContainer<T>(p, id, name.c_str());
			c->take_ownership();
			fPointers.push_back(c);
			return id;
		}

		template <class T>
		unsigned int 	add(const T &o)
		{
			T *p = new T(o);
			return add(p);
		}

		template <class T>
		bool contains(T *p)
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]); // always returns c!=0
				if (c->get() == p)
					return true;
			}
			return false;
		}

		template <class T>
		bool remove(T *p)
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]); // always returns c!=0
				if (c->get() == p)
					{
						delete fPointers[i];
						fPointers.erase(fPointers.begin() + i);
						return true;
					}
			}
			return false;			
		}

		template <class T>
		T* get() const
		{
			T *p = 0x0;
			size_t tmphash = std::type_index(typeid(p)).hash_code();
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]); // always returns c!=0
				if (c->HasHash(tmphash))
				{
					p = c->get();
				}
			}
			return p;
		}

		template <class T>
		T* get_unchecked(unsigned int iwhich) const
		{
			T *p = 0x0;
			if ( iwhich < fPointers.size())
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[iwhich]); // always returns c!=0
				p = c->get();
			}
			return p;
		}

		template <class T>
		T* get(unsigned int iwhich) const 
		{
			T *p = 0x0;
			if ( iwhich < fPointers.size() )
			{
				size_t tmphash = std::type_index(typeid(p)).hash_code();
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[iwhich]); // always returns c!=0
				if (c->HasHash(tmphash))
					p = c->get();
			}
			return p;
		}

		template <class T>
		long index()
		{
			long idx = -1;
			T *p = 0x0;
			size_t tmphash = std::type_index(typeid(p)).hash_code();
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				WrapContainer<T> *c = (WrapContainer<T>*)(fPointers[i]); // always returns c!=0
				if (c->HasHash(tmphash))
				{
					idx = i;
				}
			}
			return idx;
		}

		template <class T>
		void remove_all()
		{
			T *p = 0x0;
			long idx = index<T>();
			while (idx >= 0)
			{
				delete fPointers[idx];
				fPointers.erase(fPointers.begin() + idx);
				idx = index<T>();
			}
		}

		void list()
		{
			std::cout << "[i] Wrapper::list() ..." << std::endl << std::endl;
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				// this is a trick - we do not need a template argument here
				WrapContainer<bool> *c = (WrapContainer<bool>*)(fPointers[i]); // always returns c!=0
				WrapContainer<bool> &rc = *c;
				std::cout << rc << std::endl;
			}			
		}

		unsigned int size() const
		{
			return fPointers.size();
		}

		void set_debug(unsigned int idbg)
		{
			debug = idbg;
		}

	protected:

		std::vector< WrapType* >		fPointers;
		//std::forward_list< WrapType* >		fPointers;

	private:
		unsigned int 	idcount;
		unsigned int	debug;
};

template <class T>
class WrapperIterator
{
public:
	WrapperIterator (const Wrapper *w, bool forward = true)
	: fWrapper(w)
	, fForward(forward)
	, fPos (0)
	, fIndexes()
	{
		reset(forward);
	}

	void reset(bool forward = true)
	{
		fForward = forward;
		fIndexes.clear();
		unsigned int isize = fWrapper->size();
		for (unsigned int i = 0; i < isize; i++)
		{
			if (fWrapper->get<T>(i) != 0x0)
				fIndexes.push_back(i);
		}
		if (fForward == false)
		{
			fPos = fIndexes.size();
		}
		else
		{
			fPos = 1;
		}
	}

	~WrapperIterator() {;}

	T *next()
	{
		T *p = 0;
		if (fPos == 0)
		{
			return p;
		}
		if (fPos - 1 < fIndexes.size())
		{
			p = fWrapper->get<T>(fPos - 1);
			if (fForward == false)
			{
				fPos--;
			}
			else
			{
				fPos++;
			}
		}
		return p;
	}

private:
	const Wrapper *fWrapper;
	bool fForward;
	unsigned int fPos;
	std::vector<unsigned int> fIndexes;
};

class WrapTestClass
{
public:
	WrapTestClass() : i(counter++) {;}
	WrapTestClass(const WrapTestClass &t) : i (t.i) {;}
	virtual ~WrapTestClass()
	{
		std::cout << "debug: ---> WrapTestClass::~WrapTestClass() " << i << " at 0x" << this << std::endl;
	}
	void test_call()
	{
		std::cout << "debug: ---> WrapTestClass test_call i = " << i << std::endl;
	}
	static int counter;
private:
	int i;
};

#endif // __WRAPPER__HH
