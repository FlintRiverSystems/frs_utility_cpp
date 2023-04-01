
#pragma once

#include <ostream>
#include <map>
#include <algorithm>

namespace FRS { namespace utility {

template<class T1, class T2>
class print_pair 
{
	private:
		std::ostream& _os;
	public:
		print_pair (std::ostream& os) : _os(os) {}
		void operator() (const std::pair<T1, T2>& p) 
		{
			_os << p.first << " : " << p.second << std::endl;
		}
};

}}

namespace std { /* this is illegal but required for this to work */

template<class T1, class T2>
inline std::ostream& operator<< (std::ostream& os, const std::map<T1, T2>& m) 
{
	utility::print_pair<T1, T2> printer(os);
	std::for_each(m.begin(), m.end(), printer);
	return os;
}

}

