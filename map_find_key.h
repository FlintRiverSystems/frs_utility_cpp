#ifndef MAP_FIND_KEY_H_INCLUDED_1EC72CD8_128B5442_752840EE_04BD1179
#define MAP_FIND_KEY_H_INCLUDED_1EC72CD8_128B5442_752840EE_04BD1179

#include <string>
#include <vector>
#include <map>

namespace FRS {namespace utility {

/* find the first key that contains the given value */	
template <class T, class U>	
inline T map_find_key (const std::map<T,U>& map_, const U& val) 
{
	typename std::map<T,U>::const_iterator it = map_.begin();
	typename std::map<T,U>::const_iterator last = map_.end();
	for (; it!=last; ++it) 
	{
		if (it->second == val)
			return it->first;
	}
	throw std::runtime_error ("map_find_key lookup failed");
}
	
}}

#endif /* MAP_FIND_KEY_H_INCLUDED_1EC72CD8_128B5442_752840EE_04BD1179 */ 
