#include <Python.h>

#include <fstream>

#include <boost/python/tuple.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/LogRecord.hpp>

using namespace ackward::logging;

namespace
{

struct Fixture
{
    Fixture() :
        rec (L"foo",
             DEBUG(),
             L"/some/path/name",
             101,
             L"Message",
             boost::python::tuple())
        {}

    LogRecord rec;
};

}

BOOST_AUTO_TEST_SUITE( logging )
BOOST_FIXTURE_TEST_SUITE( logRecord, Fixture )

BOOST_AUTO_TEST_CASE( constructor )
{
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
    BOOST_CHECK(rec.getMessage() == L"Message");
}

BOOST_AUTO_TEST_CASE( args )
{
    boost::python::tuple args = rec.args;
}

// BOOST_AUTO_TEST_CASE( asctime )
// {
//     std::wstring at = rec.asctime;
// }

BOOST_AUTO_TEST_CASE( created )
{
    float c = rec.created;
}

// BOOST_AUTO_TEST_CASE( exc_info )
// {
//     boost::python::tuple ei = rec.exc_info;
// }

BOOST_AUTO_TEST_CASE( filename )
{
    std::wstring fn = rec.filename;
}

// BOOST_AUTO_TEST_CASE( funcName )
// {
//     std::wstring fn = rec.funcName;
// }

BOOST_AUTO_TEST_CASE( levelname )
{
    std::wstring ln = rec.levelname;
}

BOOST_AUTO_TEST_CASE( levelno )
{
    int ln = rec.levelno;
}

BOOST_AUTO_TEST_CASE( lineno )
{
    int ln = rec.lineno;
}

BOOST_AUTO_TEST_CASE( module )
{
    std::wstring m = rec.module;
}

BOOST_AUTO_TEST_CASE( msecs )
{
    float ms = rec.msecs;
}

// BOOST_AUTO_TEST_CASE( message )
// {
//     std::wstring m = rec.message;
// }

BOOST_AUTO_TEST_CASE( msg )
{
    std::wstring m = rec.msg;
}

BOOST_AUTO_TEST_CASE( name )
{
    std::wstring n = rec.name;
}

BOOST_AUTO_TEST_CASE( pathname )
{
    std::wstring pn = rec.pathname;
}

BOOST_AUTO_TEST_CASE( process )
{
    int p  = rec.process;
}

BOOST_AUTO_TEST_CASE( processName )
{
    std::wstring pn = rec.processName;
}

BOOST_AUTO_TEST_CASE( relateveCreated )
{
    float rc = rec.relativeCreated;
}

BOOST_AUTO_TEST_CASE( stack_info )
{
    boost::python::object si = rec.stack_info;
}

BOOST_AUTO_TEST_CASE( thread )
{
    unsigned long t = rec.thread;
}

BOOST_AUTO_TEST_CASE( threadName )
{
    std::wstring tn = rec.threadName;
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
