#include <Python.h>

#include <boost/test/unit_test.hpp>

#include <ackward/time/Module.hpp>

using namespace ackward::time;

BOOST_AUTO_TEST_SUITE( time_module )
BOOST_AUTO_TEST_SUITE( module )

BOOST_AUTO_TEST_CASE( ctor )
{
    time();
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
