#include <ackward/core/Version.hpp>

#include <boost/test/unit_test.hpp>

using namespace ackward::core;

BOOST_AUTO_TEST_SUITE( core )
BOOST_AUTO_TEST_SUITE( versionInfo )

using ackward::core::versionInfo;

BOOST_AUTO_TEST_CASE( version_info )
{

    VersionInfo info = versionInfo();
    BOOST_CHECK(info.majorVersion() == ACKWARD_MAJOR_VERSION);
    BOOST_CHECK(info.minorVersion() == ACKWARD_MINOR_VERSION);

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
