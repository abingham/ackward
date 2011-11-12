#include <Python.h>

#include <boost/test/unit_test.hpp>

#include <ackward/logging/UserFilter.hpp>

#include "../util.hpp"
#include "LoggerFixture.hpp"
#include "PushBackHandler.hpp"

namespace
{

// Only passes messages with an even level
struct EvenLevelFilterImpl
{
    int filter(const LogRecord& lr)
        {
            return (lr.levelno % 2 == 0);
        }
};

typedef UserFilter<EvenLevelFilterImpl> EvenLevelFilter;

}

BOOST_AUTO_TEST_SUITE( logging )
BOOST_FIXTURE_TEST_SUITE( userFilter, LoggerFixture )

BOOST_AUTO_TEST_CASE( filter_test )
{
    BOOST_CHECK_EQUAL(
        ::lineCount(filename),
        static_cast<unsigned int>(0));

    EvenLevelFilter f;
    logger.addFilter(f);

    logger.log(101, L"llama!");
    handler.flush();
    BOOST_CHECK_EQUAL(
        ::lineCount(filename),
        static_cast<unsigned int>(0));

    logger.log(102, L"yak!");
    handler.flush();
    BOOST_CHECK_EQUAL(
        ::lineCount(filename),
        static_cast<unsigned int>(1));
}

BOOST_AUTO_TEST_SUITE_END() // userFilter
BOOST_AUTO_TEST_SUITE_END() // logging
