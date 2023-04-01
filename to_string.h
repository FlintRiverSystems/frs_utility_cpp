
#pragma once

#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <list>

namespace FRS {
namespace utility {

template<class T>
inline std::string to_string (const T& x) {
	std::stringstream s;
	s << x;
	return s.str();
	}

template<>
inline std::string to_string (const unsigned char& x) {
	std::stringstream s;
	s << int(x);
	return s.str();
	}

template<>
inline std::string to_string (const double& x) {
	std::stringstream s;
	s << std::setprecision(20) << x;
	return s.str();
	}

template<class IT>
inline std::string to_string (IT begin, IT end, const std::string& sep = ", ") {
	std::stringstream s;
	IT it = begin;
	if (it != end) {
		s << *it;
		++it;
		}
	for (; it != end; ++it)
		s << sep << *it;
	return s.str();
	}

template<class T>
inline std::string to_string (std::vector<T> v, const std::string& sep = ", ") {
	return to_string (v.begin(), v.end(), sep);
	}

template<class T>
inline std::string to_string (std::list<T> v, const std::string& sep = ", ") {
	return to_string (v.begin(), v.end(), sep);
	}

}}

