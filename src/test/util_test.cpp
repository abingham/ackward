#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/Import.hpp>
#include <ackward/core/Util.hpp>

using namespace ackward::core;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( core_util_test )

BOOST_AUTO_TEST_CASE( isInstance_test )
{
    bp::str foo;
    BOOST_ASSERT(
        isInstance(foo, "str"));

    bp::object obj = findObject("datetime.datetime").attr("now")();
    BOOST_ASSERT(
        isInstance(obj, "datetime.datetime"));
}

BOOST_AUTO_TEST_CASE( verifyType_test )
{
    bp::str foo;
    verifyType(foo, "str");
    BOOST_CHECK_THROW(verifyType(foo, "int"), ValueError);
    BOOST_CHECK_THROW(verifyType<TypeError>(foo, "int"), TypeError);
}

BOOST_AUTO_TEST_CASE( is_none_test )
{
    BOOST_CHECK( is_none(builtins().attr("None")) );
    BOOST_CHECK( !is_none(bp::object(1)) );
    BOOST_CHECK( !is_none(bp::object("asdf")) );
}

BOOST_AUTO_TEST_CASE( iter_test )
{
    bp::list l;
    l.append(1);
    l.append(2);
    
    // iter() creates a usable iterator
    bp::object i = iter(l);
    BOOST_CHECK( bp::extract<int>(next(i)) == 1);
    BOOST_CHECK( bp::extract<int>(next(i)) == 2);
    
    BOOST_CHECK_THROW(
        next(i),
        StopIteration);

    // Throw for non-iterables
    BOOST_CHECK_THROW(
        iter(bp::object(5)),
        TypeError);
}

BOOST_AUTO_TEST_CASE( next_test )
{
    bp::list l;
    l.append(1);
    l.append(2);
    
    // iter() creates a usable iterator
    bp::object i = iter(l);
    BOOST_CHECK( bp::extract<int>(next(i)) == 1);
    BOOST_CHECK( bp::extract<int>(next(i)) == 2);
    
    BOOST_CHECK_THROW(
        next(i),
        StopIteration);

    bp::object o(5);
    BOOST_CHECK_THROW(
        next(o),
        TypeError);
}

BOOST_AUTO_TEST_CASE( strToWString_test )
{
    bp::str s("åøæ");
    std::wstring ws =
        strToWString(s);
    BOOST_CHECK( ws == std::wstring(L"åøæ") );
}

BOOST_AUTO_TEST_CASE( fromPythonConvertible_test )
{
    BOOST_CHECK(
        fromPythonConvertible<int>(
            boost::python::object(5).ptr()));

    BOOST_CHECK(
        !fromPythonConvertible<int>(
            boost::python::object("Magnited we stand.").ptr()));

}

BOOST_AUTO_TEST_SUITE_END()
