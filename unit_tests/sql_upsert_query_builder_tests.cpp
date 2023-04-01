
#include "../sql_upsert_query_builder.h"

using namespace std;
using namespace boost;
using namespace boost::uuids;
using namespace FRS::utility;

BOOST_AUTO_TEST_SUITE(sql_upsert_query_builder_tests)

BOOST_AUTO_TEST_CASE(test1) 
{
	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col ("col1", "val1");

	/*** Act ***/
	auto insert = builder.build_insert_query();
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col1\") VALUES ('val1');", insert);
	BOOST_REQUIRE_EQUAL ("update table set \"col1\"='val1' where this=that;", update);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test2) 
{
	/* multiple columns */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col ("col1", "val1");
	builder.add_col ("col2", "val2");

	/*** Act ***/
	auto insert = builder.build_insert_query();
	auto upsert = builder.build_upsert_query("col1");
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Upsert Query:" << endl;
	cout << upsert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col1\", \"col2\") VALUES ('val1', 'val2');", insert);
	BOOST_REQUIRE_EQUAL ("insert into table (\"col1\", \"col2\") VALUES ('val1', 'val2') on conflict(\"col1\") do update set \"col2\"='val2';", upsert);
	BOOST_REQUIRE_EQUAL ("update table set \"col1\"='val1', \"col2\"='val2' where this=that;", update);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test2_1) 
{
	/* upsert with second column ask key */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col ("col1", "val1");
	builder.add_col ("col2", "val2");

	/*** Act ***/
	auto upsert = builder.build_upsert_query("col2");

	cout << "Upsert Query:" << endl;
	cout << upsert << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col1\", \"col2\") VALUES ('val1', 'val2') on conflict(\"col2\") do update set \"col1\"='val1';", upsert);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test3) 
{
	/* remove column */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col ("col1", "val1");
	builder.add_col ("col2", "val2");

	/*** Act ***/
	builder.remove_col("col1");
	auto insert = builder.build_insert_query();
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col2\") VALUES ('val2');", insert);
	BOOST_REQUIRE_EQUAL ("update table set \"col2\"='val2' where this=that;", update);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test4) 
{
	/* testing the template methods */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col   ("col0", "val0");
	builder.add_col_T ("col1", 1.2f);
	builder.add_col_T ("col2", 1);
	builder.add_col_T ("col3", uuid());

	/*** Act ***/
	auto insert = builder.build_insert_query();
	auto upsert = builder.build_upsert_query("col0");
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Upsert Query:" << endl;
	cout << upsert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col0\", \"col1\", \"col2\", \"col3\") VALUES ('val0', '1.20000005', '1', '00000000-0000-0000-0000-000000000000');", insert);
	BOOST_REQUIRE_EQUAL ("insert into table (\"col0\", \"col1\", \"col2\", \"col3\") VALUES ('val0', '1.20000005', '1', '00000000-0000-0000-0000-000000000000') on conflict(\"col0\") do update set \"col1\"='1.20000005', \"col2\"='1', \"col3\"='00000000-0000-0000-0000-000000000000';", upsert);
	BOOST_REQUIRE_EQUAL ("update table set \"col0\"='val0', \"col1\"='1.20000005', \"col2\"='1', \"col3\"='00000000-0000-0000-0000-000000000000' where this=that;", update);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test5) 
{
	/* test ptime */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col_T("col0", date_helpers::make_ptime(2020, 1, 2));

	/*** Act ***/
	auto insert = builder.build_insert_query();
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col0\") VALUES ('2020-Jan-02 00:00:00');", insert);
	BOOST_REQUIRE_EQUAL ("update table set \"col0\"='2020-Jan-02 00:00:00' where this=that;", update);

	TestWatcher::ExitTest();
}	

BOOST_AUTO_TEST_CASE(test6) 
{
	/* test invalid ptime */

	TestWatcher::EnterTest();

	/*** Arrange ***/
	sql_upsert_query_builder builder("table");
	builder.add_col_T("col0", posix_time::ptime());

	/*** Act ***/
	auto insert = builder.build_insert_query();
	auto update = builder.build_update_query("this=that");

	cout << "Insert Query:" << endl;
	cout << insert << endl << endl;

	cout << "Update Query:" << endl;
	cout << update << endl << endl;

	/*** Assert ***/
	BOOST_REQUIRE_EQUAL ("insert into table (\"col0\") VALUES (NULL);", insert);
	BOOST_REQUIRE_EQUAL ("update table set \"col0\"=NULL where this=that;", update);

	TestWatcher::ExitTest();
}	


BOOST_AUTO_TEST_SUITE_END()
