
#pragma once

#include <limits>
#include "float_compare.h"

namespace FRS {
namespace utility {

/** convert float to int without half-bit rounding error */
template<class T, class U>
T to_int (U rhs) 
{
	if (std::numeric_limits<U>::is_integer)
		return T(rhs);
	else
		return T(rhs+0.5);
}

/** add two numbers intelligently wrt int/float type */
template<class T, class U>
T smart_add (T lhs, U rhs) 
{
	if (std::numeric_limits<T>::is_integer && !std::numeric_limits<U>::is_integer) 
	{
		/* return type is an int but rhs is not, work as U */
		U result = U(lhs) + rhs;

		/* round back to int */
		return to_int<T>(result);
	}

	/* both are same type or lhs is float */
	return lhs + T(rhs);
}

/** subtract two numbers intelligently wrt int/float type */
template<class T, class U>
T smart_subtract (T lhs, U rhs) 
{
	if (std::numeric_limits<T>::is_integer && !std::numeric_limits<U>::is_integer) 
	{
		/* return type is an int but rhs is not, work as U */
		U result = U(lhs) - rhs;

		/* round back to int */
		return to_int<T>(result);
	}

	/* both are same type or lhs is float */
	return lhs - T(rhs);
}

/** multiply two numbers intelligently wrt int/float type */
template<class T, class U>
T smart_multiply (T lhs, U rhs) 
{
	if (std::numeric_limits<T>::is_integer && !std::numeric_limits<U>::is_integer) 
	{
		/* return type is an int but rhs is not, work as U */
		U result = U(lhs) * rhs;

		/* round back to int */
		return to_int<T>(result);
	}

	/* both are same type or lhs is float */
	return lhs * T(rhs);
}

/** divide two numbers intelligently wrt int/float type */
template<class T, class U>
T smart_divide (T lhs, U rhs) 
{

	if (std::numeric_limits<T>::is_integer && !std::numeric_limits<U>::is_integer) 
	{
		/* return type is an int but rhs is not, work as U */
		U result = U(lhs) / rhs;

		/* round back to int */
		return to_int<T>(result);
	}

	/* both are same type or lhs is float */
	return lhs / T(rhs);
}

/** compare to numbers intelligently */
template<class T>
bool smart_equal (T lhs, T rhs, int float_tol = 2000) 
{
	if (std::numeric_limits<T>::is_integer)
		return lhs == rhs;
	else
		return float_compare(float(lhs), float(rhs), float_tol);
}

}}


