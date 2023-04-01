
#pragma once

#include<algorithm>

namespace FRS { namespace utility {

template<class C, class T, class UnaryPredicate>
T& find_if_w_default (C& v, T&& def, UnaryPredicate p)
{
	auto res = std::find_if(std::begin(v), std::end(v), p);
	if (res != std::end(v))
	{
		return *res;
	}

	return def;
}

}}
