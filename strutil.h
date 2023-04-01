
#pragma once

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <map>
#include <locale>
#include <codecvt>

#include "strlist.h"
#include "strvec.h"
#include "list2vector.h"

namespace FRS {
namespace utility {

inline strvec str_split (const std::string& s, char delim = '\n') 
{
	strlist result;

	std::stringstream ss (s);
	std::string item;

	while (std::getline(ss, item, delim))
	{
		result.push_back(item);
	}

	return list2vector(result);
}

inline std::tuple<std::string, std::string> parse_name_val(const std::string& s)
{
	/* use std::tie to get the result:
	 *
	 * string name;
	 * string val;
	 * tie(name, val) = parse_name_val(...);
	 *
	 */

	auto name_val = str_split(s, '=');

	if (name_val.size() == 1 && s[0] != '=')
	{
		/* variable is blank */
		return std::make_tuple(name_val[0], std::string());
	}

	if (name_val.size() == 2)
	{
		return std::make_tuple(name_val[0], name_val[1]);
	}

	return std::make_tuple(std::string(), std::string());
}


inline std::map<std::string, std::string> parse_property_list(const std::string& s)
{
	/* parses "Name1=Val1;Name2=Val2" */

	auto props = str_split(s, ';');

	std::map<std::string, std::string> result;

	std::string name;
	std::string val;

	for (unsigned int i=0; i<props.size(); ++i)
	{
		std::tie(name, val) = parse_name_val(props[i]);

		if (name.empty()) continue;

		result[name] = val;
	}

	return result;
}

inline std::string tail (const std::string& source, const size_t length)
{
	if (length >= source.size())
	{
		return source;
	}

	return source.substr(source.size() - length);
}

inline std::string& toupper (std::string& s) 
{
	std::transform (s.begin(), s.end(), s.begin(), (int(*)(int))std::toupper);
	return s;
}

inline std::string toupper (const std::string& s) 
{
	std::string s2(s);
	std::transform (s2.begin(), s2.end(), s2.begin(), (int(*)(int))std::toupper);
	return s2;
}

inline std::string& tolower (std::string& s) 
{
	std::transform (s.begin(), s.end(), s.begin(), (int(*)(int))std::tolower);
	return s;
}

inline std::string tolower (const std::string& s) 
{
	std::string s2(s);
	std::transform (s2.begin(), s2.end(), s2.begin(), (int(*)(int))std::tolower);
	return s2;
}

inline void toupper(strlist& s) 
{
	std::for_each (s.begin(), s.end(), (std::string&(*)(std::string&))toupper);
}

inline void tolower(strlist& s) 
{
	std::for_each (s.begin(), s.end(), (std::string&(*)(std::string&))tolower);
}

inline void toupper(strvec& s) 
{
	std::for_each (s.begin(), s.end(), (std::string&(*)(std::string&))toupper);
}

inline void tolower(strvec& s) 
{
	std::for_each (s.begin(), s.end(), (std::string&(*)(std::string&))tolower);
}

inline bool str_ci_equal (const std::string& s1, const std::string& s2) 
{
	if (s1.size() != s2.size())
	{
		return false;
	}

	for (unsigned int i=0; i<s1.size(); ++i)
	{
		if (std::tolower(s1[i]) != std::tolower(s2[i]))
		{
			return false;
		}
	}

	return true;
}

class str_ci_less_than : public std::less<std::string> 
{
	public:
		bool operator() (const std::string& s1, const std::string& s2) const 
		{
			std::string s1_uc = s1;
			std::string s2_uc = s2;
			toupper(s1_uc);
			toupper(s2_uc);

			return s1_uc < s2_uc;
		}
};

/***************************************************/
/* From https://stackoverflow.com/a/18374698/70964 */

inline std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

inline std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

/***************************************************/

}}


