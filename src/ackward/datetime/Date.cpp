#include <ackward/datetime/Date.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>

// #include <ackward/core/Exceptions.hpp>
// #include <ackward/datetime/Module.hpp>
// #include <ackward/datetime/TimeDelta.hpp>

using namespace boost::python;

namespace ackward { namespace datetime
{

// Date::Date(boost::python::object obj) :
//     core::Object (obj)
// {}

// Date::Date(unsigned int year, unsigned int month, unsigned int day) 
// try :
//     core::Object (
//         module().attr("date")(year, month, day) )
// {
// }
// catch (const error_already_set&)
// {
//     core::translatePythonException();
// }

// Date Date::today() {
//     return extract<Date>(
//         module().attr("date").attr("today"));
//     // return Date(module().attr("date").attr("today")());
// }

// Date Date::fromtimestamp(double timestamp)
// {
//     try {
//         return Date(module().attr("date").attr("fromtimestamp")(timestamp));
//     } catch (const error_already_set&) {
//         core::translatePythonException();
//         throw;
//     }
// }

// Date Date::fromordinal(unsigned int ordinal)
// {
//     try {
//         return Date(module().attr("date").attr("fromordinal")(ordinal));
//     } catch (const error_already_set&) {
//         core::translatePythonException();
//         throw;
//     }
// }

// Date Date::min()
// {
//     return Date(module().attr("date").attr("min"));
// }

// Date Date::max()
// {
//     return Date(module().attr("date").attr("max"));
// }

// TimeDelta Date::resolution()
// {
//     return TimeDelta(module().attr("date").attr("resolution"));
// }

// Date Date::replace(unsigned int y,
//                    unsigned int m,
//                    unsigned int d) const
// {
//     if (y == 0) y = year();
//     if (m == 0) m = month();
//     if (d == 0) d = day();
    
//     return Date(
//         obj().attr("replace")(y, m, d));
// }

// tm Date::timetuple() const
// {
//     return extract<tm>(
//         obj().attr("timetuple")());
// }

// int Date::weekday() const
// {
//     return extract<int>(obj().attr("weekday")());
// }

// int Date::isoweekday() const
// {
//     return extract<int>(obj().attr("isoweekday")());
// }

boost::tuple<int, int, int> Date::isocalendar() const
{
    tuple t = extract<tuple>(_isocalendar());
    return boost::make_tuple(
        extract<int>(t[0])(),
        extract<int>(t[1])(),
        extract<int>(t[2])());
}

// std::string Date::isoformat() const
// {
//     return extract<std::string>(obj().attr("isoformat")());
// }

// std::string Date::ctime() const
// {
//     return extract<std::string>(obj().attr("ctime")());
// }

// std::wstring Date::strftime(const std::wstring& fmt) const
// {
//     return extract<std::wstring>(obj().attr("strftime")(fmt));
// }

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
