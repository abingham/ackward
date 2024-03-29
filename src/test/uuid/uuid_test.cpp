#include <Python.h>

#include <list>

#include <boost/assign/list_of.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/Util.hpp>
#include <ackward/uuid/Module.hpp>
#include <ackward/uuid/UUID.hpp>

#include "../disable_signal.hpp"

#include <iostream>

using namespace ackward::core;
using namespace ackward::uuid;

BOOST_AUTO_TEST_SUITE( uuid )

BOOST_AUTO_TEST_CASE( uuid_fromHex )
{
    std::vector<std::string> values;
    values.push_back("{12345678-1234-5678-1234-567812345678}");
    values.push_back("12345678123456781234567812345678");
    values.push_back("urn:uuid:12345678-1234-5678-1234-567812345678");

    BOOST_FOREACH(const std::string& value, values)
    {
        UUID uuid = UUID::fromHex(value);
        BOOST_CHECK(std::string(uuid.hex) == "12345678123456781234567812345678");
    }

    BOOST_CHECK_THROW(
        UUID::fromHex("hello there"),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_fromBytes )
{
    Bytes b("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 16);

    UUID uuid = UUID::fromBytes(b);
    BOOST_CHECK(Bytes(uuid.bytes) == b);
    BOOST_CHECK(std::string(uuid.hex) == "12345678123456781234567812345678");
}

BOOST_AUTO_TEST_CASE( uuid_fromBytes_LE )
{
    Bytes b("\x78\x56\x34\x12\x34\x12\x78\x56\x12\x34\x56\x78\x12\x34\x56\x78", 16);

    UUID uuid = UUID::fromBytes_LE(b);
    BOOST_CHECK(Bytes(uuid.bytes_le) == b);
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

    Fields f2 = uuid.fields;

    BOOST_CHECK(Fields(uuid.fields) == f);
    BOOST_CHECK(std::string(uuid.hex) == "12345678123456781234567812345678");

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
    Variant(uuid.variant);
}

BOOST_AUTO_TEST_CASE( uuid_version )
{
    BOOST_CHECK(
        UUID::fromHex("12345678123456781234567812345678").version() == 0);

    Bytes b("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 16);

    BOOST_CHECK(
        UUID::fromBytes(b).version() == 0);

    BOOST_CHECK(
        UUID::fromBytes_LE(b).version() == 0);

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
    Bytes b("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 16);

    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromBytes(b, i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromBytes(b, 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromBytes(b, 6),
        ValueError);
}

BOOST_AUTO_TEST_CASE( uuid_version_bytes_le )
{
    Bytes b("\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78\x12\x34\x56\x78", 16);

    for (uint8_t i = 1; i < 6; ++i)
    {
        UUID uuid = UUID::fromBytes_LE(b, i);
        BOOST_CHECK(uuid.version() == i);
    }

    BOOST_CHECK_THROW(
        UUID::fromBytes_LE(b, 0),
        ValueError);

    BOOST_CHECK_THROW(
        UUID::fromBytes_LE(b, 6),
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
    // Boost.Test sets up a handler for SIGCHLD and freaks out when
    // getnode() is called because getnode() can use an external
    // process.  So, we disable the sigchld handler for our call, and
    // then set it back when we're done.
    DisableSignal d(SIGCHLD);

    ackward::uuid::getnode();
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_0 )
{
    // Boost.Test sets up a handler for SIGCHLD and freaks out when
    // getnode() is called because getnode() can use an external
    // process.  So, we disable the sigchld handler for our call, and
    // then set it back when we're done.
    DisableSignal d(SIGCHLD);

    UUID uuid = ackward::uuid::uuid1();
    std::string sz = uuid.hex; // Just to give the instance something
                               // to do and avoid a compiler warning.
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_1 )
{
    UUID uuid = ackward::uuid::uuid1(1234);
    std::string sz = uuid.hex;
}

BOOST_AUTO_TEST_CASE( uuid_uuid1_2 )
{
    UUID uuid = ackward::uuid::uuid1(1234, 5678);
    std::string sz = uuid.hex;
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
        std::string sz = uuid.hex;
    }
}

BOOST_AUTO_TEST_CASE( uuid_uuid4 )
{
    UUID uuid = ackward::uuid::uuid4();
    std::string sz = uuid.hex;
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
        std::string sz = uuid.hex;
    }
}

BOOST_AUTO_TEST_CASE( uuid_namespace_dns )
{
    std::string sz = ackward::uuid::NAMESPACE_DNS().hex;
}

BOOST_AUTO_TEST_CASE( uuid_namespace_url )
{
    std::string sz = ackward::uuid::NAMESPACE_URL().hex;
}

BOOST_AUTO_TEST_CASE( uuid_namespace_oid )
{
    std::string sz = ackward::uuid::NAMESPACE_OID().hex;
}

BOOST_AUTO_TEST_CASE( uuid_namespace_x500 )
{
    std::string sz = ackward::uuid::NAMESPACE_X500().hex;
}

BOOST_AUTO_TEST_CASE( uuid_example_test )
{
    std::vector<char> bytes;
    for (int i = 0; i < 16; ++i) { bytes.push_back(i); }
    Bytes b(bytes.begin(), bytes.end());


    // make a UUID based on the host ID and current time
    // uuid1(); // TODO: Fails in implicit getnode()

    // make a UUID using an MD5 hash of a namespace UUID and a name
    uuid3(NAMESPACE_DNS(), "python.org");

    // make a random UUID
    uuid4();

    // make a UUID using a SHA-1 hash of a namespace UUID and a name
    uuid5(NAMESPACE_DNS(), "python.org");

    // make a UUID from a string of hex digits (braces and hyphens
    // ignored)
    UUID x = UUID::fromHex("{00010203-0405-0607-0809-0a0b0c0d0e0f}");
    BOOST_CHECK( ackward::core::str(x) == L"00010203-0405-0607-0809-0a0b0c0d0e0f" );

    x = UUID::fromBytes(b);
    BOOST_CHECK( Bytes(x.bytes) == b );

    // make a UUID from a 16-byte string
    UUID::fromBytes(Bytes(x.bytes));

    UUID::fromHex("00010203-0405-0607-0809-0a0b0c0d0e0f");
}

BOOST_AUTO_TEST_SUITE_END()
