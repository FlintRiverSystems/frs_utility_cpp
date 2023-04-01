
#include "../split_hostname_port.h"

using namespace std;
using namespace boost;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(split_hostname_port_tests);

BOOST_AUTO_TEST_CASE(test1) 
{
	TestWatcher::EnterTest();

	/*** Arrange ***/
	string hostname;
	int port;

	/*** Act ***/
	tie(hostname,port) = split_hostname_port ("hostname:9999");

	/*** Assert ***/
	BOOST_CHECK_EQUAL ("hostname", hostname);
	BOOST_CHECK_EQUAL (9999, port);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test2) 
{
	TestWatcher::EnterTest();

	/*** Arrange ***/
	string hostname;
	int port;

	/*** Act ***/
	tie(hostname,port) = split_hostname_port ("hostname");

	/*** Assert ***/
	BOOST_CHECK_EQUAL ("hostname", hostname);
	BOOST_CHECK_EQUAL (0, port);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test3) 
{
	TestWatcher::EnterTest();

	/*** Arrange ***/
	string hostname;
	int port;

	/*** Act ***/
	tie(hostname,port) = split_hostname_port ("hostname:");

	/*** Assert ***/
	BOOST_CHECK_EQUAL ("hostname", hostname);
	BOOST_CHECK_EQUAL (0, port);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test4) 
{
	TestWatcher::EnterTest();

	/*** Arrange ***/
	string hostname;
	int port;

	/*** Act ***/
	tie(hostname,port) = split_hostname_port ("");

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("", hostname);
	BOOST_REQUIRE_EQUAL (0, port);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_SUITE_END();
