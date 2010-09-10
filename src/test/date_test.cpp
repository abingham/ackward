#include <ctime>
#include <limits>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/datetime/Date.hpp>
#include <ackward/datetime/Module.hpp>
#include <ackward/datetime/TimeDelta.hpp>

using namespace ackward::core;
using namespace ackward::datetime;
using namespace boost::python;

BOOST_AUTO_TEST_SUITE( Date_methods )

BOOST_AUTO_TEST_CASE( objectConstructor)
{
    object obj = ackward::datetime::module().attr("date")(1,1,1);
    Date d(obj);
}

BOOST_AUTO_TEST_CASE( normalConstructor)
{
    std::vector<unsigned int> years;
    years.push_back(MINYEAR());
    years.push_back(MAXYEAR());
    years.push_back(MAXYEAR() - MINYEAR() / 2);

    // standard range
    BOOST_FOREACH(unsigned int year, years)
    {
        for (unsigned int month = 1; month < 13; ++month)
        {
            for (unsigned int day = 1; day < 32; ++day)
            {
                try {
                    Date d(year,month,day);
                    BOOST_ASSERT(d.year() == year);
                    BOOST_ASSERT(d.month() == month);
                    BOOST_ASSERT(d.day() == day);
                } catch (const ValueError&) {
                    BOOST_ASSERT(day > 28);
                }
            }
        }
    }

    // year too small
    if (MINYEAR() > 0)
    {
        BOOST_CHECK_THROW(         
            Date d(MINYEAR() - 1, 1, 1),
            ValueError);
    }
    
    // year too big
    if (MAXYEAR() < std::numeric_limits<unsigned int>::max())
    {
        BOOST_CHECK_THROW(
            Date d(MAXYEAR() + 1, 1, 1),
            ValueError);
    }

    // month too small
    BOOST_CHECK_THROW(
        Date d(MINYEAR(), 0, 1),
        ValueError);

    // month too big
    BOOST_CHECK_THROW(
        Date d(MINYEAR(), 13, 1),
        ValueError);

    // day too small
    BOOST_CHECK_THROW(
        Date d(MINYEAR(), 1, 0),
        ValueError);

    // day too big
    BOOST_CHECK_THROW(
        Date d(MINYEAR(), 1, 32),
        ValueError);
    
}

BOOST_AUTO_TEST_CASE( today )
{
    Date d = Date::today();
}

BOOST_AUTO_TEST_CASE( fromtimestamp )
{
    Date d = Date::fromtimestamp(time(NULL));
}

BOOST_AUTO_TEST_CASE( fromordinal )
{
    Date d = Date::fromordinal(1);
    BOOST_ASSERT(d.toordinal() == 1);

    d = Date::fromordinal(Date::max().toordinal());
    BOOST_ASSERT(d.toordinal() == Date::max().toordinal());

    d = Date::fromordinal(Date::max().toordinal() / 2);
    BOOST_ASSERT(d.toordinal() == Date::max().toordinal() / 2);
    
    BOOST_CHECK_THROW(
        d = Date::fromordinal(0),
        ValueError);

    BOOST_CHECK_THROW(
        d = Date::fromordinal(Date::max().toordinal() + 1),
        ValueError);
}

BOOST_AUTO_TEST_CASE( min )
{
    Date d = Date::min();
    BOOST_ASSERT( d == Date(1,1,1) );
}

BOOST_AUTO_TEST_CASE( max )
{
    Date d = Date::max();
}

BOOST_AUTO_TEST_CASE( toordinal )
{
    Date d(1,1,1);
    BOOST_ASSERT(d.toordinal() == 1);
}

BOOST_AUTO_TEST_CASE( resolution )
{
    TimeDelta td = Date::resolution();
    BOOST_ASSERT( td == TimeDelta(1) );
}

BOOST_AUTO_TEST_CASE( replace_test )
{
    Date d(2002, 12, 31);
    BOOST_ASSERT( d.replace(0, 0, 26) == Date(2002, 12, 26) );
}

BOOST_AUTO_TEST_CASE( timetuple_test )
{
    Date d = Date::today();
    tm ttuple = d.timetuple();
}

BOOST_AUTO_TEST_CASE( weekday_test )
{
    Date d = Date::today();
    int wd = d.weekday();
}

BOOST_AUTO_TEST_SUITE_END()
