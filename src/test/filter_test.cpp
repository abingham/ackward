#include <ackward/logging/Filter.hpp>

#include <boost/test/unit_test.hpp>

using namespace ackward::logging;

BOOST_AUTO_TEST_SUITE( Filter_methods )

BOOST_AUTO_TEST_CASE( constructor )
{
    Filter f;
    Filter f2(L"A.B.C.D");
}

BOOST_AUTO_TEST_SUITE_END()
