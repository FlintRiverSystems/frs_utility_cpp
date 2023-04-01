
#pragma once

#include <fstream>

#include "strvec.h"
#include "strlist.h"
#include "list2vector.h"

namespace FRS {
namespace utility {

inline std::string read_text_file (const std::string& filename) 
{
	/* open file */
	std::ifstream f (filename.c_str());

	if (!f)
	{
		throw std::runtime_error (std::string("Could not open file: ") + filename); 
	}

	/* initialize string with stream iterators */
	std::string result (
		(std::istreambuf_iterator<char>(f)),
		std::istreambuf_iterator<char>());

	return result;
}

inline strvec read_text_file_lines (const std::string& filename) 
{
	strlist lines;

	/* open file */
	std::ifstream f (filename.c_str());

	if (!f)
	{
		throw std::runtime_error (std::string("Could not open file: ") + filename); 
	}

	std::string buf;

	while (std::getline(f, buf))
	{
		lines.push_back(buf);
	}

	return list2vector (lines);
}

}}

