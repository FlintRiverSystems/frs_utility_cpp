
#include "../read_text_file.h"

using namespace std;
using namespace boost;
using namespace FRS::utility;

BOOST_AUTO_TEST_CASE(read_entire_file) 
{
	TestWatcher::EnterTest();

	auto result = read_text_file("../testfile.txt");
	string expected = "this is\na test\nfile\nthat has\n5 lines\n";

	BOOST_REQUIRE_EQUAL (expected.size(), result.size());
	BOOST_REQUIRE_EQUAL (expected, result);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(read_into_lines) 
{
	TestWatcher::EnterTest();

	auto result = read_text_file_lines("../testfile.txt");

	BOOST_REQUIRE_EQUAL (5u			, result.size());

	BOOST_REQUIRE_EQUAL ("this is"	, result[0]);
	BOOST_REQUIRE_EQUAL ("a test"		, result[1]);
	BOOST_REQUIRE_EQUAL ("file"		, result[2]);
	BOOST_REQUIRE_EQUAL ("that has"	, result[3]);
	BOOST_REQUIRE_EQUAL ("5 lines"	, result[4]);

	TestWatcher::ExitTest();
}
