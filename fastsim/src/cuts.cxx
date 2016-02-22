#include <typeinfo>

			std::string s = typeid(*p).name();
			std::cout << "[i] add pointer type: " << s << std::endl;

