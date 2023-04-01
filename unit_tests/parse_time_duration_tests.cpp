
#include "../date_helpers.h"

using namespace std;
using namespace boost::posix_time;
using namespace FRS::utility::date_helpers;

BOOST_AUTO_TEST_SUITE(parse_time_duration_test);

BOOST_AUTO_TEST_CASE(test1) 
{
	TestWatcher::EnterTest();

	BOOST_REQUIRE_EQUAL(time_duration(1, 0, 0), parse_time_duration("1 Hr"));
	BOOST_REQUIRE_EQUAL(time_duration(2, 0, 0), parse_time_duration("2 HoUrs"));

	BOOST_REQUIRE_EQUAL(time_duration(0, 1, 0), parse_time_duration("1 min"));
	BOOST_REQUIRE_EQUAL(time_duration(0, 2, 0), parse_time_duration("2 mins"));

	BOOST_REQUIRE_EQUAL(time_duration(0, 0, 1), parse_time_duration("1 sec"));
	BOOST_REQUIRE_EQUAL(time_duration(0, 0, 2), parse_time_duration("2 secs"));

	BOOST_REQUIRE_EQUAL(time_duration(24, 0, 0), parse_time_duration("1 day"));
	BOOST_REQUIRE_EQUAL(time_duration(48, 0, 0), parse_time_duration("2 days"));

	BOOST_REQUIRE_EQUAL(time_duration(7*24, 0, 0), parse_time_duration("1 week"));
	BOOST_REQUIRE_EQUAL(time_duration(14*24, 0, 0), parse_time_duration("2 weeks"));

	BOOST_REQUIRE_EQUAL(time_duration(30*24, 0, 0), parse_time_duration("1 month"));
	BOOST_REQUIRE_EQUAL(time_duration(60*24, 0, 0), parse_time_duration("2 months"));

	auto r = parse_time_duration("1 asdf");
	BOOST_REQUIRE(r.is_not_a_date_time());

	r = parse_time_duration("asdf");
	BOOST_REQUIRE(r.is_not_a_date_time());

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_SUITE_END();
