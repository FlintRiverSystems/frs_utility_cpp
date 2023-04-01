
#pragma once

#include <vector>
#include <list>

namespace FRS { namespace utility {

template<class T>
std::vector<T> list2vector (std::list<T> l)
{
	std::vector<T> result;
	result.reserve (l.size());
	result.insert (result.end(), l.begin(), l.end());
	return result;
}

}}

