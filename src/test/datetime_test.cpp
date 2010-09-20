#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/Module.hpp>

using namespace ackward::core;
using namespace ackward::datetime;
using namespace boost::python;

BOOST_AUTO_TEST_SUITE( DateTime_methods )

BOOST_AUTO_TEST_CASE( objectConstructor)
{
    object obj = ackward::datetime::module().attr("datetime")(1,1,1);
    DateTime d(obj);
}

BOOST_AUTO_TEST_CASE( today )
{
    // DateTime d = DateTime::today();
}

BOOST_AUTO_TEST_CASE( now )
{
    DateTime d = DateTime::now();
}

BOOST_AUTO_TEST_SUITE_END()
