#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

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

    bp::object obj = import("datetime.datetime");
    obj = obj.attr("now")();
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

BOOST_AUTO_TEST_SUITE_END()
