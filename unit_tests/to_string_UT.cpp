
#include "../to_string.h"

using namespace std;
using namespace boost;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(to_string_UT);

BOOST_AUTO_TEST_CASE(to_string__test01_vector) 
{
	TestWatcher::EnterTest();

	auto v = vector<string>{ "first", "second" };

	auto result = to_string(v);

	BOOST_REQUIRE_EQUAL("first, second", result);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(to_string__test02_vector_custom_sep) 
{
	TestWatcher::EnterTest();

	auto v = vector<string>{ "first", "second" };

	auto result = to_string(v, ";");

	BOOST_REQUIRE_EQUAL("first;second", result);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(to_string__test03_list) 
{
	TestWatcher::EnterTest();

	auto l = list<string>{ "first", "second" };

	auto result = to_string(l);

	BOOST_REQUIRE_EQUAL("first, second", result);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(to_string__test04_list_custom_sep) 
{
	TestWatcher::EnterTest();

	auto l = list<string>{ "first", "second" };

	auto result = to_string(l, ";");

	BOOST_REQUIRE_EQUAL("first;second", result);

	TestWatcher::ExitTest();
}



BOOST_AUTO_TEST_SUITE_END();
