#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/Util.hpp>

using namespace ackward::core;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( core_util_test )

BOOST_AUTO_TEST_CASE( import_test )
{
    bp::object mod = import("sys");
    mod = import("os.path");
    mod = import("");

    BOOST_CHECK_THROW(
        import("foo.bar.llama.yak"),
        ImportError);
}

BOOST_AUTO_TEST_CASE( findObject_test )
{
    bp::object obj = findObject("os.path",
                                "split");
    obj = findObject("", "str");
    
    BOOST_CHECK_THROW(
        findObject("os.path", "llamas_ate_my_cereal"),
        AttributeError);

    BOOST_CHECK_THROW(
        findObject("yak.gnu.fozzy.kermit", "puddle"),
        ImportError);
}

BOOST_AUTO_TEST_SUITE_END()
