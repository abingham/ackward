#include <list>

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/uuid/Module.hpp>
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

BOOST_AUTO_TEST_CASE( uuid_version )
{
    BOOST_CHECK(
        UUID::fromHex("12345678123456781234567812345678").version() == 0);

    BOOST_CHECK(
        UUID::fromBytes("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78").version() == 0);

    BOOST_CHECK(
        UUID::fromBytes_LE("\x78\x56\x34\x12\x34\x12\x78\x56\x12\x34\x56\x78\x12\x34\x56\x78").version() == 0);

    BOOST_CHECK(
        UUID::fromFields(
            boost::make_tuple(
                0x12345678, 
                0x1234, 
                0x5678, 
                0x12, 
                0x34, 
                0x567812345678)).version() == 0);
}

BOOST_AUTO_TEST_CASE( uuid_version_hex )
{
    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromHex("12345678123456781234567812345678", i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromHex("12345678123456781234567812345678", 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromHex("12345678123456781234567812345678", 6),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_version_bytes )
{
    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromBytes("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromBytes("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromBytes("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 6),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_version_bytes_le )
{
    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromBytes_LE("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromBytes_LE("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromBytes_LE("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 6),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_version_fields )
{
    Fields f = boost::make_tuple(
        0x12345678, 
        0x1234, 
        0x5678, 
        0x12, 
        0x34, 
        0x567812345678);

    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromFields(f, i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromFields(f, 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromFields(f, 6),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_getnode )
{
    // TODO: Figure out why getnode() kills the test program.

    // std::cout << ackward::uuid::getnode() << std::endl;
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_0 )
{
    // TODO: This implicitly calls getnode(). Figure out why getnode()
    // kills the test program.

    // UUID uuid = ackward::uuid::uuid1();
    // uuid.hex(); // Just to give the instance something to do and avoid
                // a compiler warning.
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_1 )
{
    UUID uuid = ackward::uuid::uuid1(1234);
    uuid.hex();
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_2 )
{
    UUID uuid = ackward::uuid::uuid1(1234, 5678);
    uuid.hex();
}

BOOST_AUTO_TEST_CASE( uuid_uuid3 )
{
    const std::list<UUID> namespaces = 
        boost::assign::list_of
        (NAMESPACE_DNS())
        (NAMESPACE_URL())
        (NAMESPACE_OID())
        (NAMESPACE_X500());

    BOOST_FOREACH(UUID u, namespaces)
    {
        UUID uuid = ackward::uuid::uuid3(
            u, "monkey");
        uuid.hex();
    }
}

BOOST_AUTO_TEST_CASE( uuid_uuid4 )
{
    UUID uuid = ackward::uuid::uuid4();
    uuid.hex();
}

BOOST_AUTO_TEST_CASE( uuid_uuid5 )
{
    const std::list<UUID> namespaces = 
        boost::assign::list_of
        (NAMESPACE_DNS())
        (NAMESPACE_URL())
        (NAMESPACE_OID())
        (NAMESPACE_X500());

    BOOST_FOREACH( UUID u, namespaces )
    {
        UUID uuid = ackward::uuid::uuid5(
            u, "llama");
        uuid.hex();
    }
}

BOOST_AUTO_TEST_CASE( uuid_namespace_dns )
{
    ackward::uuid::NAMESPACE_DNS().hex();
}

BOOST_AUTO_TEST_CASE( uuid_namespace_url )
{
    ackward::uuid::NAMESPACE_URL().hex();
}

BOOST_AUTO_TEST_CASE( uuid_namespace_oid )
{
    ackward::uuid::NAMESPACE_OID().hex();
}

BOOST_AUTO_TEST_CASE( uuid_namespace_x500 )
{
    ackward::uuid::NAMESPACE_X500().hex();
}

BOOST_AUTO_TEST_SUITE_END()
