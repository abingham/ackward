#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

#include <boost/foreach.hpp>
#include <boost/python/import.hpp>
#include <boost/test/unit_test.hpp>

using namespace ackward::logging;

BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( filter )

BOOST_AUTO_TEST_CASE( empty_constructor )
{
    Filter f;
}

BOOST_AUTO_TEST_CASE( object_constructor )
{
    Filter f(boost::python::import("logging").attr("Filter")());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
