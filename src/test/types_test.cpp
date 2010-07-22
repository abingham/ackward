#include <ackward/logging/Types.hpp>

#include <boost/test/unit_test.hpp>

using namespace ackward::logging;

BOOST_AUTO_TEST_SUITE( Types_methods )

BOOST_AUTO_TEST_CASE( levels )
{
    Level l = DEBUG();
    l = INFO();
    l = WARNING();
    l = ERROR();
    l = CRITICAL();
}

BOOST_AUTO_TEST_SUITE_END()
