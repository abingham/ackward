#include <Python.h>

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/tuple.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LoggerAdapter.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

#include "LoggerFixture.hpp"
#include "../util.hpp"

using namespace ackward::logging;
namespace bfs=boost::filesystem;

struct Fixture : LoggerFixture
{
    Fixture() :
        adapter (
            logger,
            boost::python::dict())
        {}

    LoggerAdapter adapter;
};

// Logger method
BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( LoggerAdapter )

BOOST_AUTO_TEST_CASE( debug )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(INFO());
    f.adapter.debug(L"debug");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(DEBUG());
    f.adapter.debug(L"debug");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( info )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(WARNING());
    f.adapter.info(L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(INFO());
    f.adapter.info(L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( warning )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.adapter.warning(L"warning");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(WARNING());
    f.adapter.warning(L"warning");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( error )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(CRITICAL());
    f.adapter.error(L"error");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.adapter.error(L"error");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_CASE( critical )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.adapter.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);

    f.logger.setLevel(DEBUG());
    f.adapter.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 2);

    f.logger.setLevel(CRITICAL());
    f.adapter.critical(L"critical");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 3);
}

BOOST_AUTO_TEST_CASE( log )
{
    Fixture f;

    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(ERROR());
    f.adapter.log(INFO(), L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 0);

    f.logger.setLevel(DEBUG());
    f.adapter.log(INFO(), L"info");
    f.handler.flush();
    BOOST_CHECK(::lineCount(f.filename) == 1);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
