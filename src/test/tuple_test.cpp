#include <Python.h>

#include <string>

#include <ackward/core/Tuple.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple.hpp>

using namespace ackward::core;

namespace {

typedef boost::tuple<int, float, std::string> Tuple;

}

BOOST_AUTO_TEST_SUITE( Core_tuple )

BOOST_AUTO_TEST_CASE( basic )
{
    TupleConverter< ::Tuple >::initialize();
}

BOOST_AUTO_TEST_SUITE_END()
