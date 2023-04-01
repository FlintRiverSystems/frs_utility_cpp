
#pragma once

/* BOOST Format shortcut */

#ifdef _WIN32
#pragma warning (disable: 4244 4267)
#endif

#include <boost/format.hpp>

/* passthrough */
inline std::string bf (std::string fmt) 
{
	return fmt;
}

template <class T1>
std::string bf (std::string fmt, T1 arg1) 
{
	return boost::str(boost::format (fmt) % arg1);
}

template <class T1, class T2>
std::string bf (std::string fmt, T1 arg1, T2 arg2) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2);
}

template <class T1, class T2, class T3>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3);
}

template <class T1, class T2, class T3, class T4>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4);
}

template <class T1, class T2, class T3, class T4, class T5>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5);
}

template <class T1, class T2, class T3, class T4, class T5, class T6>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5 % arg6);
}

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5 % arg6 % arg7);
}

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5 % arg6 % arg7 % arg8);
}

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5 % arg6 % arg7 % arg8 % arg9);
}

template <class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T10>
std::string bf (std::string fmt, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9, T10 arg10) 
{
	return boost::str(boost::format (fmt) % arg1 % arg2 % arg3 % arg4 % arg5 % arg6 % arg7 % arg8 % arg9 % arg10);
}

#ifdef _WIN32
#pragma warning (default: 4244 4267)
#endif

