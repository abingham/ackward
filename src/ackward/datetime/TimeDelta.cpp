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
