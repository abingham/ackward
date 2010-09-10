#ifndef INCLUDE_ACKWARD_DATETIME_DATE_HPP
#define INCLUDE_ACKWARD_DATETIME_DATE_HPP

#include <ctime>

#include <boost/python/object_fwd.hpp>
#include <boost/tuple/tuple.hpp>

#include <ackward/core/Object.hpp>

namespace ackward { namespace datetime
{

class TimeDelta;

class Date : private core::Object
{
public:
    Date(boost::python::object);

    /**
       @param year MINYEAR <= year <= MAXYEAR
       @param month 1 <= month <= 12
       @param day 1 <= day <= number of days in the given month and 

       @except ValueError If an argument outside those ranges is
         given, ValueError is raised.
    */
    Date(unsigned int year, 
         unsigned int month, 
         unsigned int day);

    /** Return the current local date. This is equivalent to
     * \code fromtimestamp(time()) \endcode
     */
    static Date today();

    /** Return the local date corresponding to the POSIX timestamp,
     * such as is returned by \code time() \endcode. This may raise ValueError,
     * if the timestamp is out of the range of values supported by the
     * platform C localtime() function. It’s common for this to be
     * restricted to years from 1970 through 2038. Note that on
     * non-POSIX systems that include leap seconds in their notion of
     * a timestamp, leap seconds are ignored by fromtimestamp(). */
    static Date fromtimestamp(double timestamp);

    /** Return the date corresponding to the proleptic Gregorian
     * ordinal, where January 1 of year 1 has ordinal 1. ValueError is
     * raised unless 1 <= ordinal <= date.max.toordinal(). For any
     * date d, date.fromordinal(d.toordinal()) == d. */
    static Date fromordinal(unsigned int ordinal);

    /** The earliest representable date, Date(MINYEAR, 1, 1). */
    static Date min();

    /** The latest representable date, date(MAXYEAR, 12, 31). */
    static Date max();

    /** The smallest possible difference between non-equal date
     * objects, timedelta(days=1). */
    static TimeDelta resolution();

    /** Between MINYEAR and MAXYEAR inclusive. */
    unsigned int year() const;

    /** Between 1 and 12 inclusive. */
    unsigned int month() const;

    /** Between 1 and the number of days in the given month of the given year. */
    unsigned int day() const;

    /** Return a date with the same value, except for those members
     *  given new values by whichever arguments are not equal to
     *  0. For example, if d == date(2002, 12, 31), then d.replace(0,
     *  0, 26) == date(2002, 12, 26).
     */
    Date replace(unsigned int year=0, 
                 unsigned int month=0, 
                 unsigned int day=0) const;

    /** Return a time.struct_time such as returned by
     * time.localtime(). The hours, minutes and seconds are 0, and the
     * DST flag is -1. d.timetuple() is equivalent to
     * time.struct_time((d.year, d.month, d.day, 0, 0, 0, d.weekday(),
     * d.toordinal() - date(d.year, 1, 1).toordinal() + 1, -1)) */
    tm timetuple() const;


    /** Return the proleptic Gregorian ordinal of the date, where
     * January 1 of year 1 has ordinal 1. For any date object d,
     * date.fromordinal(d.toordinal()) == d. */
    unsigned int toordinal() const;

    /** Return the day of the week as an integer, where Monday is 0
     * and Sunday is 6. For example, date(2002, 12, 4).weekday() == 2,
     * a Wednesday. See also isoweekday(). */
    int weekday() const;

    /** Return the day of the week as an integer, where Monday is 1
     * and Sunday is 7. For example, date(2002, 12, 4).isoweekday() ==
     * 3, a Wednesday. See also weekday(), isocalendar(). */
    int isoweekday() const;

    /** Return a 3-tuple, (ISO year, ISO week number, ISO weekday). */
    boost::tuple<int, int, int> isocalendar() const;


// The ISO calendar is a widely used variant of the Gregorian calendar. See http://www.phys.uu.nl/~vgent/calendar/isocalendar.htm for a good explanation.

// The ISO year consists of 52 or 53 full weeks, and where a week starts on a Monday and ends on a Sunday. The first week of an ISO year is the first (Gregorian) calendar week of a year containing a Thursday. This is called week number 1, and the ISO year of that Thursday is the same as its Gregorian year.

// For example, 2004 begins on a Thursday, so the first week of ISO year 2004 begins on Monday, 29 Dec 2003 and ends on Sunday, 4 Jan 2004, so that date(2003, 12, 29).isocalendar() == (2004, 1, 1) and date(2004, 1, 4).isocalendar() == (2004, 1, 7).

// date.isoformat()
// Return a string representing the date in ISO 8601 format, ‘YYYY-MM-DD’. For example, date(2002, 12, 4).isoformat() == '2002-12-04'.
// date.__str__()
// For a date d, str(d) is equivalent to d.isoformat().
// date.ctime()
// Return a string representing the date, for example date(2002, 12, 4).ctime() == 'Wed Dec 4 00:00:00 2002'. d.ctime() is equivalent to time.ctime(time.mktime(d.timetuple())) on platforms where the native C ctime() function (which time.ctime() invokes, but which date.ctime() does not invoke) conforms to the C standard.
// date.strftime(format)
// Return a string representing the date, controlled by an explicit format string. Format codes referring to hours, minutes or seconds will see 0 values. See section strftime() Behavior.

    using Object::obj;
};

bool operator==(const Date&, const Date&);

/** In other words, date1 < date2 if and only if date1.toordinal() <
 * date2.toordinal(). In order to stop comparison from falling back to
 * the default scheme of comparing object addresses, date comparison
 * normally raises TypeError if the other comparand isn’t also a date
 * object. However, NotImplemented is returned instead if the other
 * comparand has a timetuple() attribute. This hook gives other kinds
 * of date objects a chance at implementing mixed-type comparison. If
 * not, when a date object is compared to an object of a different
 * type, TypeError is raised unless the comparison is == or !=. The
 * latter cases return False or True, respectively.
 */
bool operator<(const Date&, const Date&);

/** date2 is moved forward in time if timedelta.days > 0, or backward
 * if timedelta.days < 0. Afterward date2 - date1 ==
 * timedelta.days. timedelta.seconds and timedelta.microseconds are
 * ignored. OverflowError is raised if date2.year would be smaller
 * than MINYEAR or larger than MAXYEAR. 
 */
Date operator+(const Date&, const TimeDelta&);

/** This isn’t quite equivalent to date1 + (-timedelta), because
 * -timedelta in isolation can overflow in cases where date1 -
 * timedelta does not. timedelta.seconds and timedelta.microseconds
 * are ignored.
 */
Date operator-(const Date&, const TimeDelta&);

/** This is exact, and cannot overflow. timedelta.seconds and
 * timedelta.microseconds are 0, and date2 + timedelta == date1 after.
 */
TimeDelta operator-(const Date&, const Date&);

}}

#endif
