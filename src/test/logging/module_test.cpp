#include <Python.h>

#include <boost/test/unit_test.hpp>

#include <ackward/core/Kwargs.hpp>
#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

using namespace ackward::logging;

// Module-level methods

BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( Module )

BOOST_AUTO_TEST_CASE( getLogger_test )
{
    Logger l = getLogger();
    l = getLogger(L"llama");
}

BOOST_AUTO_TEST_CASE( basicConfig_default )
{
    basicConfig();
}

BOOST_AUTO_TEST_CASE( basicConfig_args )
{
    basicConfig(
        ackward::core::kwargs
        (L"filename", "unittest.log")
        (L"filemode", 'w'));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
