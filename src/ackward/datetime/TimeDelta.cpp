#include <ackward/datetime/TimeDelta.hpp>

#include <boost/python/extract.hpp>

#include <ackward/datetime/Module.hpp>

using namespace ackward::datetime;
using namespace boost::python;

TimeDelta::TimeDelta(double days,
                     double seconds,
                     double microseconds,
                     double milliseconds,
                     double minutes,
                     double hours,
                     double weeks) :
    Object( module().attr("timedelta")(days,
                                       seconds,
                                       microseconds,
                                       milliseconds,
                                       minutes,
                                       hours,
                                       weeks) )
{}

TimeDelta::TimeDelta(boost::python::object obj) :
    Object (obj)
{}

TimeDelta TimeDelta::min()
{
    return TimeDelta(
        module().attr("timedelta").attr("min"));
}

TimeDelta TimeDelta::max()
{
    return TimeDelta(
        module().attr("timedelta").attr("max"));
}

TimeDelta TimeDelta::resolution()
{
    return TimeDelta(
        module().attr("timedelta").attr("resolution"));
}

int TimeDelta::days() const
{
    return extract<int>(
        obj().attr("days"));
}
unsigned int TimeDelta::seconds() const
{
    return extract<unsigned int>(
        obj().attr("seconds"));
}

unsigned int TimeDelta::microseconds() const
{
    return extract<unsigned int>(
        obj().attr("microseconds"));
}

TimeDelta 
ackward::datetime::operator+(const TimeDelta& lhs,
                             const TimeDelta& rhs)
{
    return TimeDelta(lhs.obj() + rhs.obj());
}

TimeDelta 
ackward::datetime::operator-(const TimeDelta& lhs,
                             const TimeDelta& rhs)
{
    return TimeDelta(lhs.obj() - rhs.obj());
}

TimeDelta 
ackward::datetime::operator*(const TimeDelta& lhs,
                             unsigned long rhs)
{
    return TimeDelta(lhs.obj() * rhs);
}

TimeDelta 
ackward::datetime::operator*(unsigned long lhs,
                             const TimeDelta& rhs)
{
    return rhs * lhs;
}

TimeDelta 
ackward::datetime::operator/(const TimeDelta& lhs, 
                             long rhs)
{
    return lhs.obj() / rhs;
}

TimeDelta
ackward::datetime::operator-(const TimeDelta& d)
{
    return TimeDelta(
        d.obj().attr("__neg__")());
}

TimeDelta
ackward::datetime::abs(const TimeDelta& d)
{
    return TimeDelta(
        d.obj().attr("__abs__")());
}

bool TimeDelta::operator==(const TimeDelta& other) const
{
    return obj() == other.obj();
}

bool TimeDelta::operator!=(const TimeDelta& other) const
{
    return obj() != other.obj();
}
