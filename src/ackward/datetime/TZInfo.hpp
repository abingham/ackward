#ifndef INCLUDE_ACKWARD_DATETIME_TZINFO_HPP
#define INCLUDE_ACKWARD_DATETIME_TZINFO_HPP

#include <boost/shared_ptr.hpp>

#include <ackward/core/Object.hpp>

namespace ackward { namespace datetime
{

class DateTime;
class TimeDelta;

class TZInfo : private core::Object
{
public:
    TZInfo(boost::python::object);

    boost::shared_ptr<TimeDelta> 
    dst(const DateTime&) const;

    DateTime fromutc(const DateTime&) const;

    std::wstring tzname() const;

    boost::shared_ptr<TimeDelta> 
    utcoffset(const DateTime&) const;

    using Object::obj;
};

}}

#endif
