#include <boost/test/unit_test.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/datetime/Time.hpp>
#include <ackward/datetime/TimeDelta.hpp>

using namespace ackward::core;
using namespace ackward::datetime;

BOOST_AUTO_TEST_SUITE( DateTime_Time_methods )

BOOST_AUTO_TEST_CASE( constructor )
{
    Time t(1);
    t = Time(1,2);
    t = Time(1,2,3);
    t = Time(1,2,3,4);

    BOOST_CHECK_THROW(
        Time(24),
        ValueError);

    BOOST_CHECK_THROW(
        Time(1, 60),
        ValueError);

    BOOST_CHECK_THROW(
        Time(1,1,60),
        ValueError);

    BOOST_CHECK_THROW(
        Time(1,1,1,1000000),
        ValueError);
}

BOOST_AUTO_TEST_CASE( min )
{
    Time t = Time::min();
}

BOOST_AUTO_TEST_CASE( max )
{
    Time t = Time::max();
}

BOOST_AUTO_TEST_CASE( resolution )
{
    TimeDelta t = Time::resolution();
}

BOOST_AUTO_TEST_CASE( hour )
{
    for (int i = 0; i < 24; ++i) {
        Time t(i);
        BOOST_CHECK(t.hour() == i);
    }
}

BOOST_AUTO_TEST_CASE( minute )
{
    for (int i = 0; i < 60; ++i)
    {
        Time t(1, i);
        BOOST_CHECK(t.minute() == i);
    }
}

BOOST_AUTO_TEST_CASE( second )
{
    for (int i = 0; i < 60; ++i)
    {
        Time t(1, 1, i);
        BOOST_CHECK(t.second() == i);
    }
}

BOOST_AUTO_TEST_CASE( microsecond )
{
    for (int i = 0; i < 1000000; i += 1000)
    {
        Time t(1,1,1,i);
        BOOST_CHECK(t.microsecond() == i);
    }
}

BOOST_AUTO_TEST_SUITE_END()
