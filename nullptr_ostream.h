
#pragma once

/* give operator<< the ability to handle nullptr
 *
 * Hopefully this will no longer be necessary in C++17
 */

#include <iostream>

namespace std
{
	template<class C, class T>
	basic_ostream<C, T>& operator<<(basic_ostream<C, T>& os, nullptr_t) 
	{ 
	  return os << (void*) nullptr; 
	}
}


