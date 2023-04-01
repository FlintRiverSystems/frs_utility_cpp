
#pragma once

#include <string>
#include <map>

namespace FRS { namespace utility {

/* lookup key in map, return empty string if not found */
inline std::string map_lookup (const std::map<std::string,std::string>& m, const std::string& key)
{
	if (m.count(key) != 1)
	{
		return std::string();
	}

	return m.at(key);
}

/* lookup key in map, return given default if not found */
inline std::string map_lookup (const std::map<std::string,std::string>& m, const std::string& key, const std::string& def)
{
	if (m.count(key) != 1)
	{
		return def;
	}

	return m.at(key);
}

}}
