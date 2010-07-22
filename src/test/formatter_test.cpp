#include <boost/python/tuple.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/Formatter.hpp>
#include <ackward/logging/LogRecord.hpp>

using namespace ackward::logging;
using namespace boost::python;

#include <iostream>

BOOST_AUTO_TEST_SUITE( Formatter_methods )

BOOST_AUTO_TEST_CASE( constructor )
{
    Formatter f;
}

BOOST_AUTO_TEST_CASE( format )
{
    Formatter f;
    LogRecord r(
        L"record",
        ERROR(),
        L"/some/path/name",
        123,
        L"Message",
        tuple());
    // TODO: Look up f.format(r).starts_with(L"Message") in c++
    // BOOST_CHECK(f.format(r) == L"Message");
};

BOOST_AUTO_TEST_CASE( formatTime )
{
    Formatter f;
    // TODO: Complete when LogRecord is constructible
    // LogRecord r;
    // f.formatTime(r);
    // f.formatTime(r, 
};

BOOST_AUTO_TEST_CASE( formatException )
{
    Formatter f;
    f.formatException(
        boost::python::make_tuple(
            boost::python::object(),
            boost::python::object(),
            boost::python::object()));
}

BOOST_AUTO_TEST_SUITE_END()
