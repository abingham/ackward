#include <Python.h>

#include <boost/python/extract.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/core/Kwargs.hpp>

using namespace ackward::core;
using namespace boost::python;

BOOST_AUTO_TEST_SUITE( kwargs_test )

BOOST_AUTO_TEST_CASE( why_is_this_a_problem )
{
    Kwargs kw;
    kw(L"foo", "bar")
      (L"yak", 3);

    BOOST_CHECK_EQUAL(
        extract<std::string>(kw.getDict()[std::wstring(L"foo")])(), "bar");
    BOOST_CHECK_EQUAL(
        extract<int>(kw.getDict()[std::wstring(L"yak")]), 3);
}

BOOST_AUTO_TEST_SUITE_END()
