#include <Python.h>

#include <fstream>

#include <boost/filesystem.hpp>
#include <boost/python/dict.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/logging/config/Config.hpp>

#include "../util.hpp"

using namespace ackward::logging::config;

namespace
{

struct FileConfigFixture
{
    FileConfigFixture() :
        filename ("logging_config.test")
        {
            std::ofstream cfg(filename.string());
            cfg <<
                "[loggers]\n"
                "keys=root\n"

                "[handlers]\n"
                "keys=hand01\n"

                "[formatters]\n"
                "keys=form01\n"

                "[logger_root]\n"
                "level=NOTSET\n"
                "handlers=hand01\n"

                "[handler_hand01]\n"
                "class=StreamHandler\n"
                "level=NOTSET\n"
                "formatter=form01\n"
                "args=(sys.stdout,)\n"

                "[formatter_form01]\n"
                "format=F1 %(asctime)s %(levelname)s %(message)s\n"
                "datefmt=\n"
                "class=logging.Formatter\n";
        }

    ~FileConfigFixture()
        {
            boost::filesystem::remove(filename);
        }

    boost::filesystem::path filename;
};

}

// logging.config methods
BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( config )

BOOST_AUTO_TEST_CASE( fileConfig_1 )
{
    FileConfigFixture f;
    fileConfig(toWString(f.filename.string()));
}

BOOST_AUTO_TEST_CASE( fileConfig_2 )
{
    FileConfigFixture f;
    fileConfig(
        toWString(f.filename.string()),
        boost::python::dict());
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
