
#include "../locked_vector.h"

using namespace std;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(locked_vector_test);

BOOST_AUTO_TEST_CASE(test1)
{
	TestWatcher::EnterTest();

	locked_vector<int> v;

	v.push_back(1);
	v.push_back(2);

	BOOST_REQUIRE_EQUAL(v.size(), 2);

	v.clear();

	BOOST_REQUIRE_EQUAL(v.size(), 0);

	TestWatcher::ExitTest();
}


BOOST_AUTO_TEST_CASE(test2)
{
	TestWatcher::EnterTest();

	locked_vector<int> v;

	v.push_back(1);
	v.push_back(2);

	int total = 0;
	v.for_each([&](const int& x) { total += x; });

	BOOST_REQUIRE_EQUAL(total, 3);

	TestWatcher::ExitTest();
}

BOOST_AUTO_TEST_CASE(test3)
{
	TestWatcher::EnterTest();

	locked_vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	BOOST_REQUIRE_EQUAL(v.size(), 4);

	v.erase_if([](int& x) { return x % 2 == 0; });

	BOOST_REQUIRE_EQUAL(v.size(), 2);

	auto v2 = v.copy();

	BOOST_REQUIRE_EQUAL(v2[0], 1);
	BOOST_REQUIRE_EQUAL(v2[1], 3);


	TestWatcher::ExitTest();
}


BOOST_AUTO_TEST_SUITE_END();
