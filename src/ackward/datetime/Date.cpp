#include <ackward/datetime/Date.hpp>

#include <boost/python.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/Util.hpp>
#include <ackward/datetime/Module.hpp>
#include <ackward/datetime/TimeDelta.hpp>

using namespace boost::python;

namespace ackward { namespace datetime
{

Date::Date(boost::python::object obj) :
    core::Object (obj)
{
    core::verifyType(obj, "datetime.date");
}

Date::Date(unsigned int year, unsigned int month, unsigned int day) 
try :
    core::Object (
        module().attr("date")(year, month, day) )
{
}
catch (const error_already_set&)
{
    core::translatePythonException();
}

Date Date::today()
{
    return Date(module().attr("date").attr("today")());
}

Date Date::fromtimestamp(double timestamp)
{
    try {
        return Date(module().attr("date").attr("fromtimestamp")(timestamp));
    } catch (const error_already_set&) {
        core::translatePythonException();
        throw;
    }
}

Date Date::fromordinal(unsigned int ordinal)
{
    try {
        return Date(module().attr("date").attr("fromordinal")(ordinal));
    } catch (const error_already_set&) {
        core::translatePythonException();
        throw;
    }
}

Date Date::min()
{
    return Date(module().attr("date").attr("min"));
}

Date Date::max()
{
    return Date(module().attr("date").attr("max"));
}

TimeDelta Date::resolution()
{
    return TimeDelta(module().attr("date").attr("resolution"));
}

unsigned int Date::year() const
{
    return extract<unsigned int>(
        obj().attr("year"));
}

unsigned int Date::month() const
{
    return extract<unsigned int>(
        obj().attr("month"));
}

unsigned int Date::day() const
{
    return extract<unsigned int>(
        obj().attr("day"));
}

unsigned int Date::toordinal() const
{
    return extract<unsigned int>(obj().attr("toordinal")());
}

Date Date::replace(unsigned int y,
                   unsigned int m,
                   unsigned int d) const
{
    if (y == 0) y = year();
    if (m == 0) m = month();
    if (d == 0) d = day();
    
    return Date(
        obj().attr("replace")(y, m, d));
}

bool operator==(const Date& lhs, const Date& rhs)
{
    return (lhs.year() == rhs.year() &&
            lhs.month() == rhs.month() &&
            lhs.day() == rhs.day());
}

}}
