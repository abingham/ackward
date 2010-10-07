#include <boost/test/unit_test.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/uuid/UUID.hpp>

using namespace ackward::core;
using namespace ackward::uuid;

BOOST_AUTO_TEST_SUITE( UUID_methods )

BOOST_AUTO_TEST_CASE( uuid_fromHex )
{
    UUID uuid = UUID::fromHex("{12345678-1234-5678-1234-567812345678}");
    uuid = UUID::fromHex("12345678123456781234567812345678");
    uuid = UUID::fromHex("urn:uuid:12345678-1234-5678-1234-567812345678");

    BOOST_CHECK_THROW(
        UUID::fromHex("hello there"),
        ValueError);
}

BOOST_AUTO_TEST_SUITE_END()
