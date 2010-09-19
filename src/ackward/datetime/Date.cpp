#include <ackward/datetime/Date.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>

using namespace boost::python;

namespace ackward { namespace datetime
{

Date Date::replace(unsigned int y,
                   unsigned int m,
                   unsigned int d) const
{
    if (y == 0) y = year();
    if (m == 0) m = month();
    if (d == 0) d = day();
 
    return _replace(y, m, d);
}

boost::tuple<int, int, int> Date::isocalendar() const
{
    tuple t = _isocalendar();
    return boost::make_tuple(
        extract<int>(t[0])(),
        extract<int>(t[1])(),
        extract<int>(t[2])());
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.isoformat();
    return os;
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return (lhs.year() == rhs.year() &&
            lhs.month() == rhs.month() &&
            lhs.day() == rhs.day());
}

}}
