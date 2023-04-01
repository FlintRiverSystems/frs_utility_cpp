
#pragma once

#include<algorithm>

namespace FRS { namespace utility {

template<class C, class T>
bool contains (const C& v, const T& x)
{
	return std::find(std::begin(v), std::end(v), x) != std::end(v);
}

}}

