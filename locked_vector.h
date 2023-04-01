
#pragma once

/* locked_vector
 *
 * simple vector wrapper that provides thread-safe methods
 *
 * This is not intended to be high-performance or complete.
 */

#include <vector>
#include <mutex>
#include <algorithm>

namespace FRS { namespace utility {

template<class T>
class locked_vector
{
public:
	locked_vector()
	{
	}

	void push_back(const T& value)
	{
		lock_t lk(_m);
		_v.push_back(value);
	}

	void clear()
	{
		lock_t lk(_m);
		_v.clear();
	}

	std::size_t size()
	{
		lock_t lk(_m);
		return _v.size();
	}

	template<typename F>
	void for_each(F lambda) const
	{
		lock_t lk(_m);
		for (auto& v : _v) lambda(v);
	}

	template<typename F>
	void erase_if(F lambda)
	{
		lock_t lk(_m);
		_v.erase (std::remove_if(_v.begin(), _v.end(), lambda), _v.end());
	}

	void operator= (const std::vector<T>& rhs)
	{
		lock_t lk(_m);
		_v.clear();
		_v = rhs;
	}

	void operator= (std::vector<T>&& rhs)
	{
		lock_t lk(_m);
		_v.clear();
		_v = rhs;
	}

	std::vector<T> copy() const
	{
		std::vector<T> result;
		lock_t lk(_m);
		for (const auto& v : _v)
		{
			result.push_back(v);
		}
		return result;
	}

private:
	std::vector<T> _v;
	mutable std::recursive_mutex _m;
	using lock_t = std::lock_guard<std::recursive_mutex>;

};

}}

