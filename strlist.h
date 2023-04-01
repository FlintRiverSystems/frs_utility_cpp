
#pragma once

#include <cctype>
#include <string>
#include <list>
#include <algorithm>

namespace FRS {
namespace utility {

/* list of strings */	
using strlist = std::list<std::string>;

inline std::ostream& operator<< (std::ostream& os, const strlist& sl) 
{
	strlist::const_iterator it = sl.begin();
	strlist::const_iterator end = sl.end();
	for (; it!=end; ++it) 
	{
		if (it != sl.begin())
		{
			os << ", ";
		}
		os << *it;
	}
	return os;
}

}}
