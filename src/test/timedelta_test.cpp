#include <boost/test/unit_test.hpp>

#include <ackward/datetime/TimeDelta.hpp>

using namespace ackward::datetime;

BOOST_AUTO_TEST_SUITE( TimeDelta_methods )

BOOST_AUTO_TEST_CASE( constructor )
{

    TimeDelta();
    TimeDelta(1);
    TimeDelta(1,2);
    TimeDelta(1,2,3);
    TimeDelta(1,2,3,4);
    TimeDelta(1,2,3,4,5);
    TimeDelta(1,2,3,4,5,6);
    TimeDelta(1,2,3,4,5,6,7);

}

BOOST_AUTO_TEST_CASE( min )
{
    TimeDelta td = TimeDelta::min();
}

BOOST_AUTO_TEST_CASE( max )
{
    TimeDelta td = TimeDelta::max();
}

BOOST_AUTO_TEST_CASE( resolution )
{
    TimeDelta td = TimeDelta::resolution();
}

BOOST_AUTO_TEST_CASE( days )
{
    for (int i = -999; i < 1000; ++i)
    {
        TimeDelta td(i);
        BOOST_ASSERT(td.days() == i);
    }
}

BOOST_AUTO_TEST_CASE( seconds )
{
    for (int i = 0; i < 2000; ++i)
    {
        TimeDelta td(0, i);
        BOOST_ASSERT(td.seconds() == i);
    }
}

BOOST_AUTO_TEST_CASE( microseconds )
{
    for (int i = 0; i < 2000; ++i)
    {
        TimeDelta td(0, 0, i);
        BOOST_ASSERT(td.microseconds() == i);
    }
}

BOOST_AUTO_TEST_SUITE_END()
