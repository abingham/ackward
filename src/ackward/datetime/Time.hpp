#ifndef INCLUDE_ACKWARD_DATETIME_TIME_HPP
#define INCLUDE_ACKWARD_DATETIME_TIME_HPP

#include <iosfwd>

#include <ackward/core/Object.hpp>
#include <ackward/core/GetClass.hpp>

namespace ackward { namespace datetime
{

class TimeDelta;

class Time : private core::Object
{
public:
    #include <ackward/datetime/Time_akw.hpp>

public:
    Time replace(unsigned int hour=0,
                 unsigned int minute=0,
                 unsigned int second=0,
                 unsigned int microsecond=0) const;

    bool operator<(const Time&) const;
};

bool operator==(const Time&, const Time&);
std::ostream& operator<<(std::ostream&, const Time&);

}}

#endif
