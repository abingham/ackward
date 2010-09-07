#include <ackward/datetime/TZInfo.hpp>

namespace ackward { namespace datetime
{

TZInfo::TZInfo(boost::python::object o) :
    Object (o)
{}

TimeDelta TZInfo::dst(const DateTime& dt) const
{
    return TimeDelta(
        obj().attr("dst")(dt));
}

DateTime TZInfo::fromutc(const DateTime& dt) const
{
    return DateTime(
        obj().attr("fromutc")(dt));
}

std::wstring TZInfo::tzname() const
{
    return extract<std::wstring>(
        obj().attr("tzname")());
}

TimeDelta TZInfo::utcoffset(const DateTime& dt) const
{
    return TimeDelta(
        obj().attr("utcoffset")(dt));
}

}}
