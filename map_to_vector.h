#ifndef MAP_TO_VECTOR_H_INCLUDED_63A394E1_7C51A463_6FB6F3BE_3559B99B
#define MAP_TO_VECTOR_H_INCLUDED_63A394E1_7C51A463_6FB6F3BE_3559B99B

#include <string>
#include <vector>
#include <map>

namespace FRS { namespace utility {

template <class T, class U>	
inline std::vector<T> map_first_to_vector (std::map<T,U> map_) 
{
	std::vector<T> ret;
	typename std::map<T,U>::iterator it (map_.begin());
	for (; it!=map_.end(); ++it)
		ret.push_back (it->first);
	return ret;
}

template <class T, class U>	
inline std::vector<U> map_second_to_vector (std::map<T,U> map_) 
{
	std::vector<U> ret;
	typename std::map<T,U>::iterator it (map_.begin());
	for (; it!=map_.end(); ++it)
		ret.push_back (it->second);
	return ret;
}

}}

#endif /* MAP_TO_VECTOR_H_INCLUDED_63A394E1_7C51A463_6FB6F3BE_3559B99B */ 
