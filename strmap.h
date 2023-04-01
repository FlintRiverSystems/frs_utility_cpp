
#pragma once

#include <string>
#include <map>

namespace FRS { namespace utility {

/* map of strings to strings */	
typedef std::map<std::string, std::string> strmap;	

inline std::ostream& operator<< (std::ostream& os, const strmap& smap) 
{
	strmap::const_iterator it = smap.begin();
	strmap::const_iterator end = smap.end();

	for (; it!=end; ++it)
	{
		os << it->first << " = " << it->second << " , ";
	}

	return os;
}

}}
