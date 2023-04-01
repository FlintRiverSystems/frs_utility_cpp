
#pragma once

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

namespace FRS {
namespace utility {

/* vector of strings */	
using strvec = std::vector<std::string>;

inline std::ostream& operator<< (std::ostream& os, const strvec& svec) 
{
	strvec::const_iterator it = svec.begin();
	strvec::const_iterator end = svec.end();

	for (; it != end; ++it) 
	{
		if (it != svec.begin())
			os << ", ";
		os << *it;
	}

	return os;
}

}}

