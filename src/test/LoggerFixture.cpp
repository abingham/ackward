#include "LoggerFixture.hpp"

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Module.hpp>

#include "util.hpp"

using namespace ackward::logging;

LoggerFixture::LoggerFixture() :
    filename ("logger_test.log"),
    logger (getLogger()),
    handler (FileHandler(::toWString(filename.string()),
                         "a", "", false))
{
    logger.addHandler(handler);
    
    BOOST_REQUIRE(::lineCount(filename) == 0);
}

LoggerFixture::~LoggerFixture()
{
    BOOST_FOREACH(Filter f, logger.filters())
    {
        logger.removeFilter(f);
    }
    
    BOOST_FOREACH(Handler h, logger.handlers())
    {
        logger.removeHandler(h);
    }
    
    boost::filesystem::remove(filename);
}
