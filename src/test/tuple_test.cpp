#include <Python.h>

#include <string>

#include <ackward/core/Tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple.hpp>

using namespace ackward::core;
using namespace boost::python;

namespace {

typedef boost::tuple<int, float, std::string> Tuple;

}

BOOST_AUTO_TEST_SUITE( Core_tuple )

BOOST_AUTO_TEST_CASE( initialize )
{
    TupleConverter< ::Tuple >::initialize();
}

BOOST_AUTO_TEST_CASE( round_trip )
{
    TupleConverter< ::Tuple >::initialize();

    Tuple t(42, 6.9, "hola bili!");
    object obj(t);
    tuple pytup = extract<tuple>(obj);
    BOOST_CHECK(extract<int>(pytup[0])() == 42);
    BOOST_CHECK(extract<float>(pytup[1])() == float(6.9));
    BOOST_CHECK(extract<std::string>(pytup[2])() == "hola bili!");

    // Tuple t2 = extract<Tuple>(obj);
    // BOOST_CHECK(boost::get<0>(t2) == 42);
    // BOOST_CHECK(boost::get<1>(t2) == 6.9);
    // BOOST_CHECK(boost::get<2>(t2) == "hola bili!");
}

BOOST_AUTO_TEST_SUITE_END()
