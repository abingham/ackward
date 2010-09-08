#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/core/Import.hpp>

using namespace ackward::core;
namespace bp=boost::python;

BOOST_AUTO_TEST_SUITE( core_import_test )

BOOST_AUTO_TEST_CASE( import_test )
{
    bp::object mod = import("sys");
    mod = import("os.path");
    mod = import("");

    BOOST_CHECK_THROW(
        import("foo.bar.llama.yak"),
        ImportError);
}

BOOST_AUTO_TEST_CASE( import_template_test )
{
    std::vector<std::string> name;
    name.push_back("os");
    
    bp::object mod = import(name.begin(), name.end());
    
    name.push_back("path");
    mod = import(name.begin(), name.end());

    name.push_back("llamas");
    BOOST_CHECK_THROW(
        import(name.begin(), name.end()),
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

BOOST_AUTO_TEST_CASE( findObject_fullname_test )
{
    bp::object obj = findObject("os.path.split");
    obj = findObject("str");
    
    BOOST_CHECK_THROW(
        findObject("os.path.llamas_ate_my_cereal"),
        AttributeError);

    BOOST_CHECK_THROW(
        findObject("yak.gnu.fozzy.kermit.puddle"),
        ImportError);
}

BOOST_AUTO_TEST_SUITE_END()
