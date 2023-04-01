
#include "date_helpers.h"

using namespace boost::posix_time;

auto FRS::utility::date_helpers::first_valid(const ptime& x,
	const ptime& deflt) -> ptime
{
	if (x.is_not_a_date_time()) return deflt;
	return x;
}

auto FRS::utility::date_helpers::now() -> ptime
{
	return second_clock::local_time();
}

auto FRS::utility::date_helpers::beg_of_day(const ptime& now) -> ptime
{
	/* return a ptime of 00:00 on the current day */

	return ptime(now.date());
}

auto FRS::utility::date_helpers::beg_of_day(const boost::gregorian::date& now) -> ptime
{
	/* return a ptime of 00:00 on the current day */

	return ptime(now);
}

auto FRS::utility::date_helpers::end_of_day(const ptime& now) -> ptime
{
	/* return a ptime of 23:59 on the current day */

	return ptime(now.date() + boost::gregorian::days(1)) - minutes(1);
}

auto FRS::utility::date_helpers::end_of_day(const boost::gregorian::date& now) -> ptime
{
	/* return a ptime of 23:59 on the current day */

	return ptime(now + boost::gregorian::days(1)) - minutes(1);
}

auto FRS::utility::date_helpers::beginning_of_week(const ptime& now) -> ptime
{
	/* return a ptime of midnight on the previous Sunday */

	/* day_of_week is 0-6 = Sun-Sat */

	auto offset = now.date().day_of_week() - boost::date_time::Sunday;

	return ptime(now.date() - boost::gregorian::days(offset));
}

auto FRS::utility::date_helpers::beginning_of_next_work_week(
	const ptime& now) -> ptime
{
	/* return a ptime of 0000 on the next Monday */

	/* day_of_week is 0-6 = Sun-Sat */

	auto offset = boost::date_time::Monday - now.date().day_of_week();

	if (offset < 0) offset += 7;

	return ptime(now.date() + boost::gregorian::days(offset));
}

auto FRS::utility::date_helpers::beginning_of_next_weekend(
	const ptime& now) -> ptime
{
	/* return a ptime of 0000 on the next Saturday */

	/* day_of_week is 0-6 = Sun-Sat */

	auto offset = boost::date_time::Saturday - now.date().day_of_week();

	if (offset < 0) offset += 7;

	return ptime(now.date() + boost::gregorian::days(offset));
}

auto FRS::utility::date_helpers::end_of_work_week(const ptime& now) -> ptime
{
	/* return a ptime of 2359 on the next Friday */

	/* day_of_week is 0-6 = Sun-Sat */

	auto offset = boost::date_time::Friday - now.date().day_of_week();

	if (offset < 0) offset += 7;

	return ptime(now.date() + boost::gregorian::days(offset + 1)) - minutes(1);
}

auto FRS::utility::date_helpers::end_of_weekend(const ptime& now) -> ptime
{
	/* return a ptime of 2359 on the next Sunday */

	/* day_of_week is 0-6 = Sun-Sat */

	auto offset = boost::date_time::Sunday - now.date().day_of_week();

	if (offset < 0) offset += 7;

	return ptime(now.date() + boost::gregorian::days(offset + 1)) - minutes(1);
}

auto FRS::utility::date_helpers::make_ptime(int year, int month, int day, int hour, int min,
	int sec) -> ptime
{
	return ptime(
		boost::gregorian::date(year, month, day),
		time_duration(hour, min, sec));
}

auto FRS::utility::date_helpers::make_ptime(ptime date, int hour, int min,
	int sec) -> ptime
{
	return ptime(
		date.date(),
		time_duration(hour, min, sec));
}

auto FRS::utility::date_helpers::make_ptime(boost::gregorian::date date, int hour, int min,
	int sec) -> ptime
{
	return ptime(
		date,
		time_duration(hour, min, sec));
}

auto FRS::utility::date_helpers::make_ptime(boost::gregorian::date date,
	std::string time_str) -> ptime
{
	return ptime(date, duration_from_string(time_str));
}

auto FRS::utility::date_helpers::make_ptime(int year, int month, int day) -> ptime
{
	return ptime(
		boost::gregorian::date(year, month, day));
}

auto FRS::utility::date_helpers::days_until(boost::gregorian::gregorian_calendar::day_of_week_type current_dow,
                                            boost::gregorian::gregorian_calendar::day_of_week_type desired_dow) -> int
{
	int offset = 0;
	if (desired_dow >= current_dow)
		return desired_dow - current_dow;

	return 7 + (desired_dow - current_dow);
			
}

auto FRS::utility::date_helpers::add_minutes_to_workdays(ptime start, int minutes, int workday_start, int workday_stop, bool exclude_weekends) -> ptime
{
	auto forward = minutes > 0;

	auto workday_advance_hours = hours(24 + workday_start);
	if (!forward)
	{
		workday_advance_hours = hours(-24 + workday_stop);
	}

	auto today_work_window_beg = ptime(start.date(), time_duration(workday_start, 0, 0));
	auto today_work_window_end = ptime(start.date(), time_duration(workday_stop, 0, 0));

	/* is start within work hours? */
	if (forward)
	{
		if (start > today_work_window_end)
		{
			/* advance day */
			start = ptime(start.date()) + workday_advance_hours;
		}
	}
	else
	{
		/* start is before work window today */
		if (start < today_work_window_beg)
		{
			/* move to end of working window yesterday */
			start = ptime(start.date()) + workday_advance_hours;
		}

	}

	while (minutes != 0)
	{
		auto dow = start.date().day_of_week();
		if (exclude_weekends && (dow == boost::date_time::Saturday || dow == boost::date_time::Sunday))
		{
			/* advance day */
			start = ptime(start.date()) + workday_advance_hours;
			continue;
		}

		/* end of workday */
		auto eod = ptime(start.date(), 
		                                    time_duration(forward ? workday_stop : workday_start, 0, 0));

		/* how many minutes are left in the workday */
		auto minutes_left = (eod - start).total_seconds() / 60;

		if (abs(minutes_left) > abs(minutes))
		{
			start += boost::posix_time::minutes(minutes);
			minutes = 0;
			continue;
		}

		/* need more minutes than in this day */
		minutes -= (int)minutes_left;

		/* advance to next day */
		start = ptime(start.date()) + workday_advance_hours;
	}

	today_work_window_beg = ptime(start.date(), time_duration(workday_start, 0, 0));
	today_work_window_end = ptime(start.date(), time_duration(workday_stop, 0, 0));

	if (forward)
	{
		/* start is before work window today */
		if (start < today_work_window_beg)
		{
			/* use start of today's work window */
			start = today_work_window_beg;
		}
	}
	else
	{
		/* start is after work window today */
		if (start > today_work_window_end)
		{
			/* use end of today's work window */
			start = today_work_window_end;
		}
	}

	return start;
}

/* parse strings such as "1 hr", "10 min", "3 days" */
auto FRS::utility::date_helpers::parse_time_duration(const std::string& s) -> time_duration
{
	try
	{
		size_t pos;
		int x = stoi(s, &pos);

		auto unit = s.substr(pos);
		boost::trim (unit);
		boost::to_lower(unit);

		if (unit == "hr" || unit == "hrs" || unit == "hour" || unit == "hours")
		{
			return time_duration(x, 0, 0);
		}

		if (unit == "min" || unit == "mins")
		{
			return time_duration(0, x, 0);
		}

		if (unit == "sec" || unit == "secs" || unit == "second" || unit == "seconds")
		{
			return time_duration(0, 0, x);
		}

		if (unit == "day" || unit == "days")
		{
			return time_duration(x*24, 0, 0);
		}

		if (unit == "week" || unit == "weeks")
		{
			return time_duration(x*24*7, 0, 0);
		}

		if (unit == "month" || unit == "months")
		{
			return time_duration(x*24*30, 0, 0);
		}
	}
	catch (...)
	{
		return time_duration(boost::date_time::not_a_date_time);
	}

	return time_duration(boost::date_time::not_a_date_time);
}
