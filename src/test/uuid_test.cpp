#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/uuid/UUID.hpp>

#include <iostream>

using namespace ackward::core;
using namespace ackward::uuid;

BOOST_AUTO_TEST_SUITE( UUID_methods )

BOOST_AUTO_TEST_CASE( uuid_fromHex )
{
    std::vector<std::string> values;
    values.push_back("{12345678-1234-5678-1234-567812345678}");
    values.push_back("12345678123456781234567812345678");
    values.push_back("urn:uuid:12345678-1234-5678-1234-567812345678");
    
    BOOST_FOREACH(const std::string& value, values)
    {
        UUID uuid = UUID::fromHex(value);
        BOOST_CHECK(uuid.hex() == "12345678123456781234567812345678");
    }

    BOOST_CHECK_THROW(
        UUID::fromHex("hello there"),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_fromBytes )
{
    UUID uuid = UUID::fromBytes("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78");
    BOOST_CHECK(uuid.bytes() == "\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78");
    BOOST_CHECK(uuid.hex() == "12345678123456781234567812345678");

    BOOST_CHECK_THROW(
        UUID::fromBytes("\xasdfadfadfadadf"),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_fromBytes_LE )
{
    UUID uuid = UUID::fromBytes_LE("\x78\x56\x34\x12\x34\x12\x78\x56\x12\x34\x56\x78\x12\x34\x56\x78");
    BOOST_CHECK(uuid.bytes_le() == "\x78\x56\x34\x12\x34\x12\x78\x56\x12\x34\x56\x78\x12\x34\x56\x78");
    
    BOOST_CHECK_THROW(
        UUID::fromBytes("\xde\xad\xbe\xef"),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_fromFields )
{
    Fields f = boost::make_tuple(
        0x12345678, 
        0x1234, 
        0x5678, 
        0x12, 
        0x34, 
        0x567812345678);
    
    UUID uuid = UUID::fromFields(f);

    Fields f2 = uuid.fields();

    BOOST_CHECK(uuid.fields() == f);
    BOOST_CHECK(uuid.hex() == "12345678123456781234567812345678");

    // NOTE: I kinda expect uuid to throw if values were out of range,
    //       but apparently it doesn't.
    // BOOST_CHECK_THROW(
    //     UUID::fromFields(
    //         boost::make_tuple(
    //             0x12345678, 
    //             0x1234, 
    //             0x5678, 
    //             0x12, 
    //             0x34, 
    //             0xFFFFFFFFFFFF)),
    //     ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_variant )
{
    UUID uuid = UUID::fromHex("12345678123456781234567812345678");
    uuid.variant();
}

BOOST_AUTO_TEST_SUITE_END()
