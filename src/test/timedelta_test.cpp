#include <Python.h>

#include <cmath>
#include <cstdlib>

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
    for (unsigned int i = 0; i < 2000; ++i)
    {
        TimeDelta td(0, i);
        BOOST_ASSERT(td.seconds() == i);
    }
}

BOOST_AUTO_TEST_CASE( microseconds )
{
    for (unsigned int i = 0; i < 2000; ++i)
    {
        TimeDelta td(0, 0, i);
        BOOST_ASSERT(td.microseconds() == i);
    }
}

BOOST_AUTO_TEST_CASE( add )
{
    TimeDelta td1(1);
    TimeDelta td2(1);
    TimeDelta td3 = td1 + td2;
    BOOST_ASSERT(td3.days() == td1.days() + td2.days());
    BOOST_ASSERT(td3.days() == 2);
}

BOOST_AUTO_TEST_CASE( subtract )
{
    TimeDelta td1(123);
    TimeDelta td2(456);
    TimeDelta td3 = td1 - td2;
    BOOST_ASSERT(td3.days() == td1.days() - td2.days());
    BOOST_ASSERT(td3.days() == 123 - 456);
}

BOOST_AUTO_TEST_CASE( multiply )
{
    TimeDelta td(2);
    TimeDelta m = td * 3;
    BOOST_ASSERT(m.days() == td.days() * 3);
    BOOST_ASSERT(m.days() == 2 * 3);
}

BOOST_AUTO_TEST_CASE( floordiv )
{
    TimeDelta td(12);
    for (int i = 1; i < 12; ++i)
    {
        TimeDelta d = td / i;
        BOOST_ASSERT(floor(td.days() / i) == d.days());
    }
}

BOOST_AUTO_TEST_CASE( negate )
{
    TimeDelta td(123);
    TimeDelta n = -td;
    BOOST_ASSERT( n.days() == -1 * td.days());
    BOOST_ASSERT( n.days() == -123);
}

BOOST_AUTO_TEST_CASE( abs )
{
    TimeDelta td(-123, -456, -789);
    TimeDelta a = ackward::datetime::abs(td);
    BOOST_ASSERT(a == -td);

    td = TimeDelta(123, 456, 789);
    BOOST_ASSERT(ackward::datetime::abs(td) == td);
}

BOOST_AUTO_TEST_CASE( equal )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(123, 456);
    TimeDelta td3(456, 123);
    
    BOOST_ASSERT(td1 == td2);
    BOOST_ASSERT(!(td1 == td3));
}

BOOST_AUTO_TEST_CASE( not_equal )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(123, 456);
    TimeDelta td3(456, 123);
    
    BOOST_ASSERT(td1 != td3);
    BOOST_ASSERT(!(td1 != td2));
}

BOOST_AUTO_TEST_CASE( less_than )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(456, 123);

    BOOST_ASSERT(td1 < td2);
    BOOST_ASSERT(!(td2 < td1));
}

BOOST_AUTO_TEST_CASE( less_than_equal )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(123, 456);
    TimeDelta td3(456, 123);
    
    BOOST_ASSERT(td1 <= td2);
    BOOST_ASSERT(td1 <= td3);
    BOOST_ASSERT(!(td3 <= td1));
}

BOOST_AUTO_TEST_CASE( greater_than )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(456, 123);

    BOOST_ASSERT(td2 > td1);
    BOOST_ASSERT(!(td1 > td2));
}

BOOST_AUTO_TEST_CASE( greater_than_equal )
{
    TimeDelta td1(123, 456);
    TimeDelta td2(123, 456);
    TimeDelta td3(456, 123);
    
    BOOST_ASSERT(td1 >= td2);
    BOOST_ASSERT(td3 >= td1);
    BOOST_ASSERT(!(td1 >= td3));
}

BOOST_AUTO_TEST_SUITE_END()
