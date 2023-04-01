
#include "json_helpers.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <nlohmann/json.hpp>

#include "date_helpers.h"

using namespace std;
using namespace boost;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace FRS::utility;

ptime FRS::utility::get_ptime(const nlohmann::json& j, const std::string& key)
{
	try
	{
		auto x = j.at(key).get<string>();
		if (!x.empty())
		{
			return from_iso_extended_string(x);
		}
	}
	catch (...)
	{
	}

	return ptime(); /* not-a-date-time */
}

time_duration FRS::utility::get_time_duration(const nlohmann::json& j, const std::string& key)
{
	try
	{
		auto x = j.at(key).get<string>();
		if (!x.empty())
		{
			return duration_from_string(x);
		}
	}
	catch (...)
	{
	}

	return time_duration(not_a_date_time);
}

boost::uuids::uuid FRS::utility::get_uuid(const nlohmann::json& j, const std::string& key)
{
	boost::uuids::string_generator gen;
	try
	{
		auto x = j.at(key).get<string>();
		if (!x.empty())
		{
			return gen(x);
		}
	}
	catch (...)
	{
	}

	return boost::uuids::nil_uuid();
}

void FRS::utility::add_prop(nlohmann::json& j, const string& name, const ptime& x)
{
	if (date_helpers::valid(x))
	{
		j[name] = to_iso_extended_string(x);
	}
	else
	{
		j[name] = "";
	}
}

void FRS::utility::add_prop(nlohmann::json& j, const string& name, const date& x)
{
	if (date_helpers::valid(x))
	{
		j[name] = to_iso_extended_string(x);
	}
	else
	{
		j[name] = "";
	}
}

void FRS::utility::add_prop(nlohmann::json& j, const std::string& name, const std::vector<boost::gregorian::date>& x)
{
	vector<string> values;
	for (const auto& d : x)
		if (date_helpers::valid(d))
			values.push_back(to_iso_extended_string(d));

	if (!values.empty())
		j[name] = values;
}

void FRS::utility::add_prop(nlohmann::json& j, const string& name, const boost::optional<time_duration>& x)
{
	if (x)
	{
		if (date_helpers::valid(x.value()))
		{
			j[name] = to_simple_string(x.value());
			return;
		}
	}

	j[name] = "";
}

void FRS::utility::add_prop_if_valid(nlohmann::json& j, const string& name, const ptime& x)
{
	if (date_helpers::valid(x))
	{
		j[name] = to_iso_extended_string(x);
	}
}

void FRS::utility::add_prop_if_valid(nlohmann::json& j, const string& name, const boost::optional<time_duration>& x)
{
	if (x)
	{
		if (date_helpers::valid(x.value()))
		{
			j[name] = to_simple_string(x.value());
		}
	}
}

