#include <ackward/datetime/TZInfo.hpp>

#include <boost/python/extract.hpp>

#include <ackward/core/Util.hpp>
#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/TimeDelta.hpp>

using namespace boost;
using namespace boost::python;

namespace ackward { namespace datetime
{

TZInfo::TZInfo(boost::python::object o) :
    Object (o)
{}

shared_ptr<TimeDelta> 
TZInfo::dst(const DateTime& dt) const
{
    object rslt = obj().attr("dst")(dt);
    if (ackward::core::is_none(rslt))
        shared_ptr<TimeDelta>();
    else
        return shared_ptr<TimeDelta>(
            new TimeDelta(rslt));
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

shared_ptr<TimeDelta> 
TZInfo::utcoffset(const DateTime& dt) const
{
    object rslt = 
        obj().attr("utcoffset")(dt);
    if (ackward::core::is_none(rslt))
        return shared_ptr<TimeDelta>();
    else
        return shared_ptr<TimeDelta>(
            new TimeDelta(rslt));
}


}}
