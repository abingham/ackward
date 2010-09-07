#include <boost/test/unit_test.hpp>

#include <ackward/core/TypedObject.hpp>
#include <ackward/datetime/DateTime.hpp>

using namespace ackward::core;
using namespace ackward::datetime;

BOOST_AUTO_TEST_SUITE( TypeObject_method )

BOOST_AUTO_TEST_CASE( match_test )
{
    try {
        //TypedObject obj(
        //    DateTime::now().obj(),
        //    "datetime.datetime");
    } catch (...) {
        PyErr_Print();
    }
}

BOOST_AUTO_TEST_SUITE_END()
