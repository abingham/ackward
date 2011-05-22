#include <Python.h>

#include <string>

#include <boost/test/unit_test.hpp>

#include <ackward/core/Bytes.hpp>
#include <ackward/core/Exceptions.hpp>

using namespace ackward::core;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( bytes_test )

BOOST_AUTO_TEST_CASE( existing_ctor )
{
    static const std::string data("asdf");

    bp::object pb = bp::object(
        bp::handle<>(
            PyBytes_FromString(data.c_str())));

    Bytes b(pb);
    
    BOOST_CHECK((std::size_t)b.size() == data.size());
    BOOST_CHECK(std::string(b.begin(), b.end()) == data);
}

BOOST_AUTO_TEST_CASE( existing_ctor_throws_value_error )
{
    BOOST_CHECK_THROW(
        Bytes(bp::object(4)),
        ackward::core::ValueError);
}

BOOST_AUTO_TEST_CASE( from_data_ctor )
{
    std::string data("asdf");

    Bytes b(
        reinterpret_cast<const unsigned char*>(data.c_str()), 
        data.size());
    BOOST_CHECK((std::size_t)b.size() == data.size());
    BOOST_CHECK(std::string(b.begin(), b.end()) == data);
}

BOOST_AUTO_TEST_CASE( default_ctor )
{
    Bytes b;
    BOOST_CHECK(b.size() == 0);
}

BOOST_AUTO_TEST_CASE( index )
{
    std::string data("1234");
    Bytes b(
        reinterpret_cast<const unsigned char*>(data.c_str()), 
        data.size());
    
    for (int i = 0; i < b.size(); ++i)
    {
        BOOST_CHECK(data[i] == b[i]);
    }
}

BOOST_AUTO_TEST_CASE( index_throw )
{
    std::string data("1234");
    Bytes b(
        reinterpret_cast<const unsigned char*>(data.c_str()), 
        data.size());

    BOOST_CHECK_THROW(
        b[5],
        IndexError);
}

BOOST_AUTO_TEST_SUITE_END()
