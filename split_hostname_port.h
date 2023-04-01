
#pragma once

#include <string>

#include "strutil.h"

#include <boost/lexical_cast.hpp>

/********************************************************************************
 * parse "hostname:port" where ":port" is optional, 
 * if port is missing or lexical_cast failes, returns 0
 *
 * To use
 *
 * string hostname;
 * int port;
 * tie(hostname,port) = split_hostname_port (hostname_port);
 *
 *******************************************************************************/

namespace FRS {
namespace utility {

inline std::pair<std::string, int> split_hostname_port (const std::string& hostname_port)
{
	if (hostname_port.size() == 0)
	{
		return std::make_pair("", 0);
	}

	auto result = str_split(hostname_port, ':');
	if (result.size() == 1)
	{
		return std::make_pair(result[0], 0);
	}

	try
	{
		return std::make_pair(result[0], boost::lexical_cast<int>(result[1]));
	}
	catch (boost::bad_lexical_cast&)
	{
		return std::make_pair(result[0], 0);
	}
}

}}
