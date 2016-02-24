#include <typeinfo>

			std::string s = typeid(*p).name();
			std::cout << "[i] add pointer type: " << s << std::endl;

#include "tests.h"
#ifndef __TESTS_HH
#define __TESTS_HH

#include "fjwrapper.h"

class Wrapp
{
	public:
		Wrapp()
		{
			;
		}

		virtual 		~Wrapp()
		{
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				std::cout << "Deleting " << fPointers[i]->get_name() << std::endl;
				delete fPointers[i];
			}
		}

		template <class T>
		unsigned int 	add(T *p)
		{
			unsigned int id = fPointers.size();
			std::string name = std::type_index(typeid(p)).name();
			Container<T> *c = new Container<T>(p, id, name.c_str());
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
				Container<T> *c = (Container<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				bool has_hash = c->HasHash(*p);
				std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
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
				Container<T> *c = (Container<T>*)(fPointers[i]);
				if (c == 0x0)
					continue;
				T *p = 0;
				bool has_hash = c->HasHash(p);
				std::cout << "---> is of the same type?:" << has_hash << std::endl;
				if (has_hash)
				{
					std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
					T *tmp = (T*)c->get();
					if (tmp != 0x0)
					{
						std::cout << "    " << " cast to " << typeid(T).name() << " " << typeid(c->get()).name() << " ok " << std::endl;
					}
					return c->get();
				}
			}
			return 0x0;
		}

	protected:

		std::vector< VoidType* >		fPointers;

	private:

};

#endif