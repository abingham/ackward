#include <Python.h>

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/python/tuple.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/StreamHandler.hpp>

#include "LoggerFixture.hpp"
#include "util.hpp"

using namespace ackward::logging;
namespace bfs=boost::filesystem;

// Logger method
BOOST_AUTO_TEST_SUITE( Logger_methods )

BOOST_AUTO_TEST_CASE( propagate )
{
    LoggerFixture f;
    BOOST_CHECK(f.logger.propagate);
    f.logger.propagate = false;
    BOOST_CHECK(!f.logger.propagate);
}

BOOST_AUTO_TEST_CASE( setLevel )
{
    LoggerFixture f;
    f.logger.setLevel(DEBUG());
}

BOOST_AUTO_TEST_CASE( isEnabledFor )
{
    LoggerFixture f;
    f.logger.setLevel(WARNING());
    BOOST_CHECK(f.logger.isEnabledFor(DEBUG()) == false);
    f.logger.setLevel(DEBUG());
    BOOST_CHECK(f.logger.isEnabledFor(DEBUG()) == true);
}

BOOST_AUTO_TEST_CASE( getEffectiveLevel )
{
    LoggerFixture f;
    f.logger.setLevel(ERROR());
    BOOST_CHECK(f.logger.getEffectiveLevel() == ERROR());
    f.logger.setLevel(INFO());
    BOOST_CHECK(f.logger.getEffectiveLevel() == INFO());
}

BOOST_AUTO_TEST_CASE( debug )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(INFO());
    f.logger.debug(L"debug");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(DEBUG());
    f.logger.debug(L"debug");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( info )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(WARNING());
    f.logger.info(L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(INFO());
    f.logger.info(L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( warning )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.logger.warning(L"warning");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(WARNING());
    f.logger.warning(L"warning");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( error )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(CRITICAL());
    f.logger.error(L"error");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.logger.error(L"error");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( critical )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.logger.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);

    f.logger.setLevel(DEBUG());
    f.logger.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 2);

    f.logger.setLevel(CRITICAL());
    f.logger.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 3);
}

BOOST_AUTO_TEST_CASE( log )
{
    LoggerFixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);
    
    f.logger.setLevel(ERROR());
    f.logger.log(INFO(), L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);
    
    f.logger.setLevel(DEBUG());
    f.logger.log(INFO(), L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( addFilter )
{
    LoggerFixture f;
    
    Filter filter;
    f.logger.addFilter(filter);
}

BOOST_AUTO_TEST_CASE( filters )
{
    LoggerFixture f;
    
    BOOST_CHECK(f.logger.filters().size() == 0);

    for (unsigned int i = 0; i < 10; ++i)
    {
        f.logger.addFilter(Filter());
        BOOST_CHECK(f.logger.filters().size() == i + 1);
    }
}

BOOST_AUTO_TEST_CASE( filter )
{
    LoggerFixture f;
    
    f.logger.filter(
        LogRecord(
            L"foo",
            DEBUG(),
            L"/some/path/name",
            101,
            L"Message",
            boost::python::tuple()));
}

BOOST_AUTO_TEST_CASE( addHandler )
{
    LoggerFixture f;

    f.logger.addHandler(
        StreamHandler());
}

BOOST_AUTO_TEST_CASE( removeHandler )
{
    LoggerFixture f;

    std::size_t initialCount = 
        f.logger.handlers().size();
    
    Handler h = StreamHandler();

    f.logger.addHandler(h);

    BOOST_ASSERT(f.logger.handlers().size() == initialCount + 1);

    f.logger.removeHandler(h);

    BOOST_ASSERT(f.logger.handlers().size() == initialCount);
}

BOOST_AUTO_TEST_CASE( handlers_size )
{
    LoggerFixture f;
    
    std::size_t initCount = f.logger.handlers().size();

    for (int i = 0; i < 10; ++i)
    {
        f.logger.addHandler(
            StreamHandler());
                
        BOOST_CHECK(f.logger.handlers().size() == i + 1 + initCount);
    }
}

BOOST_AUTO_TEST_CASE( handlers_iteration )
{
    LoggerFixture f;
    BOOST_FOREACH(Handler h, f.logger.handlers())
    {
        h.setLevel(INFO());
    }
}

BOOST_AUTO_TEST_CASE( handle )
{
    LoggerFixture f;
    
    LogRecord r(
        L"foo",
        DEBUG(),
        L"/some/path/name",
        101,
        L"Message",
        boost::python::tuple());

    f.logger.handle(r);
}

BOOST_AUTO_TEST_SUITE_END()
