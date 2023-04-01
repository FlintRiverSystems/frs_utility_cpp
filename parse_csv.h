
#pragma once

#include <vector>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>

namespace FRS { namespace utility {

/*! helper function that joins boost::tokenizer with boost::lexical_cast
 * to convert a CSV string into a vector of the given type
 */
template<class T>	
std::vector<T> parse_csv (const std::string& ref) 
{
	using namespace boost;

	typedef tokenizer<escaped_list_separator<char> > tok_t;

	std::vector<T> result;

	tok_t tok(ref);
	for (tok_t::iterator it = tok.begin(); it != tok.end(); ++it) 
	{
		std::string val = *it;
		boost::trim (val);

		//std::cout << "converting '" << val << "'" << std::endl;
		result.push_back (lexical_cast<T>(val));
	}

	return result;
}

}}

