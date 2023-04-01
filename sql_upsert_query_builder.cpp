
#include "sql_upsert_query_builder.h"

#include <sstream>
#include <boost/algorithm/string/replace.hpp>

#include "strutil.h"

using namespace std;
using namespace FRS::utility;

sql_upsert_query_builder::sql_upsert_query_builder(const string table)
{
	this->_table = table;
}

void sql_upsert_query_builder::add_col (const string& name, const string& val, bool quote)
{
	if (quote)
	{
		auto val2 = "'" + boost::replace_all_copy(val, "'", "''") + "'";
		this->data[name] = val2;
	}
	else
	{
		this->data[name] = val;
	}
}

void sql_upsert_query_builder::remove_col(const std::string& name)
{
	auto it = this->data.find(name);
	if (it != this->data.end())
	{
		this->data.erase(it);
	}
}

string sql_upsert_query_builder::build_insert_query()
{
	if (this->data.size() == 0) throw std::runtime_error("No columns");

	stringstream result;

	result << "insert into " << this->_table << " (";

	auto first = true;
	for (auto kv : this->data)
	{
		if (!first) result << ", ";

		result << "\"" << kv.first << "\"";

		first = false;
	}

	result << ") VALUES (";

	first = true;
	for (auto kv : this->data)
	{
		if (!first) result << ", ";

		result << kv.second;

		first = false;
	}

	result << ");";

	return result.str();
}

string sql_upsert_query_builder::build_upsert_query(const std::string& unique_col)
{
	stringstream result;

	auto query = build_insert_query();
	query.erase(query.size() - 1);

	result << query;
	result << " on conflict(\"" << unique_col << "\") do update set ";

	auto first = true;
	for (auto kv : this->data)
	{
		if (kv.first == unique_col) continue;

		if (!first) result << ", ";

		result << "\"" << kv.first << "\"";
		result << "=";

		result << kv.second;

		first = false;
	}

	result << ";";

	return result.str();
}

string sql_upsert_query_builder::build_update_query(const string& where)
{
	if (this->data.size() == 0) throw std::runtime_error("No columns");

	stringstream result;

	result << "update " << this->_table << " set ";

	auto first = true;
	for (auto kv : this->data)
	{
		if (!first) result << ", ";

		result << "\"" << kv.first << "\"";
		result << "=";

		result << kv.second;

		first = false;
	}

	if (!where.empty())
	{
		result << " where " << where;
	}

	result << ";";

	return result.str();
}
