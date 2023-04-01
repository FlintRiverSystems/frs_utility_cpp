
#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>

namespace FRS { namespace utility {

namespace date_helpers
{
	inline bool valid (const boost::posix_time::ptime& x)
	{
		return x.is_not_a_date_time() == false;
	}

	inline bool valid (const boost::posix_time::time_duration& x)
	{
		return x.is_not_a_date_time() == false;
	}

	inline bool valid (const boost::gregorian::date& x)
	{
		return x.is_not_a_date() == false;
	}

	auto first_valid(const boost::posix_time::ptime& x,
	                 const boost::posix_time::ptime& deflt) -> boost::posix_time::ptime
	;

	auto now() -> boost::posix_time::ptime;

	auto beg_of_day(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto beg_of_day(const boost::gregorian::date& now) -> boost::posix_time::ptime;

	auto end_of_day(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto end_of_day(const boost::gregorian::date& now) -> boost::posix_time::ptime;

	auto beginning_of_week(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto beginning_of_next_work_week(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto beginning_of_next_weekend(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto end_of_work_week(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto end_of_weekend(const boost::posix_time::ptime& now) -> boost::posix_time::ptime;

	auto make_ptime(int year, int month, int day, int hour, int min, int sec) -> boost::posix_time::ptime;

	auto make_ptime(boost::posix_time::ptime date, int hour, int min, int sec) -> boost::posix_time::ptime;

	auto make_ptime(boost::gregorian::date date, int hour, int min, int sec) -> boost::posix_time::ptime;

	auto make_ptime(boost::gregorian::date date, std::string time_str) -> boost::posix_time::ptime;

	auto make_ptime(int year, int month, int day) -> boost::posix_time::ptime;

	auto days_until(boost::gregorian::gregorian_calendar::day_of_week_type current_dow,
	                boost::gregorian::gregorian_calendar::day_of_week_type desired_dow) -> int;

	auto add_minutes_to_workdays(boost::posix_time::ptime start, int minutes, int workday_start, int workday_stop,
	                              bool exclude_weekends = true) -> boost::posix_time::ptime;

	/* parse strings such as "1 hr", "10 min", "3 days" */
	auto parse_time_duration(const std::string& s) -> boost::posix_time::time_duration;

};

}}
