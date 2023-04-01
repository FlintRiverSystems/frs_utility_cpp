
#pragma once

#include <string>
#include <map>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/ptime.hpp>

#include "date_helpers.h"

namespace FRS { namespace utility
{

class sql_upsert_query_builder
{
private:
	std::string _table;

	std::map<std::string,std::string> data;

public:
	sql_upsert_query_builder(const std::string table);

	void add_col (const std::string& name, const std::string& val, bool quote=true);

	template<class T>
	void add_col_T(const std::string& name, const T& val)
	{
		this->add_col(name, boost::lexical_cast<std::string>(val), true);
	}

	template<class T>
	void add_col_T(const std::string& name, T& val)
	{
		this->add_col(name, boost::lexical_cast<std::string>(val), true);
	}

	void add_col_T(const std::string& name, const boost::posix_time::ptime& val)
	{
		if (date_helpers::valid(val))
		{
			this->add_col(name, boost::lexical_cast<std::string>(val), true);
		}
		else
		{
			this->add_col(name, "NULL", false);
		}
	}

	void add_col_T(const std::string& name, const boost::posix_time::time_duration& val)
	{
		if (date_helpers::valid(val))
		{
			this->add_col(name, boost::lexical_cast<std::string>(val), true);
		}
		else
		{
			this->add_col(name, "NULL", false);
		}
	}

	void add_col_T(const std::string& name, boost::posix_time::ptime& val)
	{
		if (date_helpers::valid(val))
		{
			this->add_col(name, boost::lexical_cast<std::string>(val), true);
		}
		else
		{
			this->add_col(name, "NULL", false);
		}
	}

	void remove_col(const std::string& name);

	std::string build_insert_query();

	/* generate a SQLite upsert (insert on conflict update) query */
	std::string build_upsert_query(const std::string& unique_col);

	std::string build_update_query(const std::string& where);

	std::string table() { return this->_table; }
};

}}
