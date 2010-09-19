#ifndef INCLUDE_ACKWARD_DATETIME_DATE_HPP
#define INCLUDE_ACKWARD_DATETIME_DATE_HPP

#include <ctime>
#include <iostream>

#include <boost/python/object_fwd.hpp>
#include <boost/tuple/tuple.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Object.hpp>
#include <ackward/datetime/TimeDelta.hpp>

namespace ackward { namespace datetime
{

class TimeDelta;

class Date : private core::Object
{
public:

    Date(boost::python::object obj) :
        core::Object (obj)
        {}

#include <ackward/datetime/DateBase.ipp>

    boost::tuple<int, int, int> isocalendar() const;

};

/** Writes the date's isoformat to the stream */
std::ostream& operator<<(std::ostream&, const Date&);

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
