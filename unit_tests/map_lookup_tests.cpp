
#include "../map_lookup.h"

using namespace std;
using namespace boost;
using namespace FRS::utility;

BOOST_AUTO_TEST_CASE(test01) 
{
	TestWatcher::EnterTest();

	map<string,string> data;
	data["key1"] = "val1";

	BOOST_CHECK_EQUAL("val1", map_lookup(data, "key1"));
	BOOST_CHECK_EQUAL(string(), map_lookup(data, "key2"));
	BOOST_CHECK_EQUAL("def", map_lookup(data, "key2", "def"));

	TestWatcher::ExitTest();
}

