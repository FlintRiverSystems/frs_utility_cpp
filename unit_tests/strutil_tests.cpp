
#include "../strutil.h"

using namespace std;
using namespace boost;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(strutil_tests)

BOOST_AUTO_TEST_CASE(str_split_test_1) 
{
	TestWatcher::EnterTest();

	string input = "this is\na test\nstring";

	auto result = str_split (input);

	BOOST_REQUIRE_EQUAL (3u, result.size());
	BOOST_REQUIRE_EQUAL ("this is", result[0]);
	BOOST_REQUIRE_EQUAL ("a test"	, result[1]);
	BOOST_REQUIRE_EQUAL ("string"	, result[2]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(str_split_test_2) 
{
	TestWatcher::EnterTest();

	string input = "name : value unit";

	auto result = str_split (input, ':');

	BOOST_REQUIRE_EQUAL (2u			, result.size());
	BOOST_REQUIRE_EQUAL ("name "		, result[0]);
	BOOST_REQUIRE_EQUAL (" value unit"	, result[1]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(str_split_test_3) 
{
	TestWatcher::EnterTest();

	string input = "";

	auto result = str_split (input, ':');

	BOOST_REQUIRE_EQUAL (0u, result.size());

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(parse_property_list_test1)
{
	TestWatcher::EnterTest();

	string input = "name1=val1;name2=val2";

	auto result = parse_property_list(input);

	BOOST_REQUIRE_EQUAL(2, result.size());
	BOOST_REQUIRE_EQUAL(1, result.count("name1"));
	BOOST_REQUIRE_EQUAL("val1", result["name1"]);

	BOOST_REQUIRE_EQUAL(1, result.count("name2"));
	BOOST_REQUIRE_EQUAL("val2", result["name2"]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(parse_property_list_test2)
{
	TestWatcher::EnterTest();

	/* make sure it ignores extra semicolons */

	string input = "name1=val1;name2=val2;";

	auto result = parse_property_list(input);

	BOOST_REQUIRE_EQUAL(2, result.size());
	BOOST_REQUIRE_EQUAL(1, result.count("name1"));
	BOOST_REQUIRE_EQUAL("val1", result["name1"]);

	BOOST_REQUIRE_EQUAL(1, result.count("name2"));
	BOOST_REQUIRE_EQUAL("val2", result["name2"]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(parse_property_list_test3)
{
	TestWatcher::EnterTest();

	/* make sure it ignores extra semicolons */

	string input = "name1=val1;;name2=val2;;";

	auto result = parse_property_list(input);

	BOOST_REQUIRE_EQUAL(2, result.size());
	BOOST_REQUIRE_EQUAL(1, result.count("name1"));
	BOOST_REQUIRE_EQUAL("val1", result["name1"]);

	BOOST_REQUIRE_EQUAL(1, result.count("name2"));
	BOOST_REQUIRE_EQUAL("val2", result["name2"]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(parse_property_list_test4)
{
	TestWatcher::EnterTest();

	/* handle single blank value */

	string input = "name1=";

	auto result = parse_property_list(input);

	BOOST_REQUIRE_EQUAL(1, result.size());
	BOOST_REQUIRE_EQUAL(1, result.count("name1"));
	BOOST_REQUIRE_EQUAL("", result["name1"]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(parse_property_list_test5)
{
	TestWatcher::EnterTest();

	/* one blank and one normal value */

	string input = "name1=;name2=val2;";

	auto result = parse_property_list(input);

	BOOST_REQUIRE_EQUAL(2, result.size());
	BOOST_REQUIRE_EQUAL(1, result.count("name1"));
	BOOST_REQUIRE_EQUAL("", result["name1"]);

	BOOST_REQUIRE_EQUAL(1, result.count("name2"));
	BOOST_REQUIRE_EQUAL("val2", result["name2"]);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_SUITE_END()

