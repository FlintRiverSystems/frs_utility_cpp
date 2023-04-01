
#include <algorithm>

namespace FRS { namespace utility {

/* call the function for each combination of elements
 * from the two sequences
 */
template<class In1, class In2, class Fn>
void for_each_comb (In1 first1, In1 last1, In2 first2, In2 last2, Fn f) 
{

	In2 it2;

	while (first1 != last1) 
	{

		it2 = first2;
		while (it2 != last2)
			f (*first1, *it2++);

		first1++;
	}
}

}}

