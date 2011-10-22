#include <Python.h>

#include <fstream>

#include <boost/python/tuple.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/LogRecord.hpp>

using namespace ackward::logging;

BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( logRecord )

BOOST_AUTO_TEST_CASE( constructor )
{
    LogRecord(L"foo",
              DEBUG(),
              L"/some/path/name",
              101,
              L"Message",
              boost::python::tuple());

    LogRecord(L"foo",
              DEBUG(),
              L"/some/path/name",
              101,
              L"Message",
              boost::python::tuple(),
              boost::python::make_tuple(
                  boost::python::object(),
                  boost::python::object(),
                  boost::python::object()));
}

BOOST_AUTO_TEST_CASE( getMessage )
{
    LogRecord r(L"foo",
                DEBUG(),
                L"/some/path/name",
                101,
                L"Message",
                boost::python::tuple());
    BOOST_CHECK(r.getMessage() == L"Message");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
