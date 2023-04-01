
#pragma once

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/optional/optional.hpp>
#include <boost/uuid/uuid.hpp>
#include <nlohmann/json_fwd.hpp>

namespace FRS { namespace utility {

boost::posix_time::ptime get_ptime(const nlohmann::json& j, const std::string& key);

boost::posix_time::time_duration get_time_duration(const nlohmann::json& j, const std::string& key);

boost::uuids::uuid get_uuid(const nlohmann::json& j, const std::string& key);

void add_prop(nlohmann::json& j, const std::string& name, const boost::posix_time::ptime& x);
void add_prop(nlohmann::json& j, const std::string& name, const boost::gregorian::date& x);
void add_prop(nlohmann::json& j, const std::string& name, const std::vector<boost::gregorian::date>& x);

void add_prop(nlohmann::json& j, const std::string& name, const boost::optional<boost::posix_time::time_duration>& x);

void add_prop_if_valid(nlohmann::json& j, const std::string& name, const boost::posix_time::ptime& x);

void add_prop_if_valid(nlohmann::json& j, const std::string& name, const boost::optional<boost::posix_time::time_duration>& x);

}}

