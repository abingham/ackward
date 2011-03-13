#include <Python.h>

#include <boost/test/unit_test.hpp>

#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/Module.hpp>
#include <ackward/datetime/TimeDelta.hpp>
#include <ackward/datetime/TZInfo.hpp>

using namespace ackward::datetime;
using namespace boost::python;

namespace
{

struct TZImpl
{

    static TimeDelta 
    dst(const DateTime& datetime)
        {
            return TimeDelta();
        }

    static DateTime 
    fromutc(const DateTime& dt)
        {
            return DateTime::now();
        }

    static std::wstring 
    tzname()
        {
            return L"test_tzinfo";
        }

    static TimeDelta 
    utcoffset(const DateTime& dt)
        {
            return TimeDelta();
        }
};

}

BOOST_AUTO_TEST_SUITE( TZInfo_suite )

BOOST_AUTO_TEST_CASE( constructor_test )
{
    // TZInfo_<TZImpl> tzii;
    // TZInfo tzi(module().attr("tzinfo")());
}

BOOST_AUTO_TEST_CASE( dst_test )
{
    // TZInfo_<TZImpl> tzi;
    // DateTime dt = DateTime::now();
    // tzi.dst(dt);
}

BOOST_AUTO_TEST_SUITE_END()
