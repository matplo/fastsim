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
				std::cout << "Deleting " << typeid(fPointers[i]).name() << std::endl;
				delete fPointers[i];
			}
		}

		template <class T>
		unsigned int 	add(T *p)
		{
			unsigned int id = fPositions.size();
			Container<T> *c = new Container<T>(p, "no name", id);
			c->TakeOwnership();
			fPointers.push_back(c);
			fPositions.push_back(id);
			return id;
		}

		template <class T>
		T* get(T **p)
		{
			*p = 0x0;
			for (unsigned int i = 0; i < fPointers.size(); i++)
			{
				Container<T> *c = (Container<T>*)(fPointers[i]);
				std::cout << i << " c is: " << c << " " << typeid(c).name() << std::endl;
				if (c != 0x0)
				{
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

	protected:

		std::vector< VoidType* >		fPointers;
		std::vector<unsigned int> 		fPositions;

	private:

};

#endif