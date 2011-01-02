#include <Python.h>

#include <boost/filesystem/path.hpp>

#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Logger.hpp>

struct LoggerFixture
{
    LoggerFixture();
    ~LoggerFixture();

    boost::filesystem::path filename;
    ackward::logging::Logger logger;
    ackward::logging::Handler handler;
};
