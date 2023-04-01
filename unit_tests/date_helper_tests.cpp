
#include "../date_helpers.h"

using namespace std;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(date_helper_test);

BOOST_AUTO_TEST_CASE(beginning_of_week_test01) 
{
	TestWatcher::EnterTest();

	auto now = ptime(date(2016, 1, 1), time_duration(15, 0, 0));

	BOOST_REQUIRE_EQUAL(date_helpers::beginning_of_week(now), ptime(date(2015,12,27)));

	now = ptime(date(2018, 1, 7));

	BOOST_REQUIRE_EQUAL(date_helpers::beginning_of_week(now), now);

	now = ptime(date(2018, 1, 13), time_duration(23,59,59));

	BOOST_REQUIRE_EQUAL(date_helpers::beginning_of_week(now), ptime(date(2018,1,7)));

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(days_until_test01) 
{
	TestWatcher::EnterTest();

	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Sunday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Monday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Tuesday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Wednesday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Thursday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Friday, boost::date_time::Saturday));

	BOOST_REQUIRE_EQUAL(1, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Sunday));
	BOOST_REQUIRE_EQUAL(2, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Monday));
	BOOST_REQUIRE_EQUAL(3, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Tuesday));
	BOOST_REQUIRE_EQUAL(4, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Wednesday));
	BOOST_REQUIRE_EQUAL(5, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Thursday));
	BOOST_REQUIRE_EQUAL(6, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Friday));
	BOOST_REQUIRE_EQUAL(0, date_helpers::days_until(boost::date_time::Saturday, boost::date_time::Saturday));


	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(add_minutes_to_workdays_test01) 
{
	/* moving forward */

	TestWatcher::EnterTest();

	auto start = ptime(date(2016, 1, 4), time_duration(15, 0, 0)); /* monday */

	auto result = date_helpers::add_minutes_to_workdays(start, 10, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 4, 15, 10, 0));

	/* start is already past end of day */
	start = ptime(date(2016, 1, 4), time_duration(18, 0, 0)); /* monday */

	result = date_helpers::add_minutes_to_workdays(start, 10, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 5, 12, 10, 0));

	/* minutes push into next day */
	start = ptime(date(2016, 1, 4), time_duration(16, 30, 0)); /* monday */

	result = date_helpers::add_minutes_to_workdays(start, 60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 5, 12, 30, 0));

	/* minutes cross several days */
	start = ptime(date(2016, 1, 4), time_duration(16, 30, 0)); /* monday */

	result = date_helpers::add_minutes_to_workdays(start, 6*60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 6, 12, 30, 0));

	/* minutes cross weekends */
	start = ptime(date(2016, 1, 1), time_duration(16, 30, 0)); /* friday */

	result = date_helpers::add_minutes_to_workdays(start, 6*60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 5, 12, 30, 0));

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(add_minutes_to_workdays_test02) 
{
	/* moving backward */

	TestWatcher::EnterTest();

	auto start = ptime(date(2016, 1, 1), time_duration(15, 0, 0)); /* friday */

	auto result = date_helpers::add_minutes_to_workdays(start, -10, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2016, 1, 1, 14, 50, 0));

	/* start is already past begin of day */
	start = ptime(date(2016, 1, 1), time_duration(11, 0, 0)); /* friday */

	result = date_helpers::add_minutes_to_workdays(start, -10, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2015, 12, 31, 16, 50, 0));

	/* minutes push into next day */
	start = ptime(date(2016, 1, 1), time_duration(12, 30, 0)); /* friday */

	result = date_helpers::add_minutes_to_workdays(start, -60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2015, 12, 31, 16, 30, 0));

	/* minutes cross several days */
	start = ptime(date(2016, 1, 1), time_duration(12, 30, 0)); /* friday */

	result = date_helpers::add_minutes_to_workdays(start, -6*60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2015, 12, 30, 16, 30, 0));

	/* minutes cross weekends */
	start = ptime(date(2016, 1, 4), time_duration(12, 30, 0)); /* monday */

	result = date_helpers::add_minutes_to_workdays(start, -6*60, 12, 17);

	BOOST_REQUIRE_EQUAL(result, date_helpers::make_ptime(2015, 12, 31, 16, 30, 0));

	TestWatcher::ExitTest();
}


BOOST_AUTO_TEST_SUITE_END();
