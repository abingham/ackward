#ifndef INCLUDE_ACKWARD_DATETIME_TIMEDELTA_HPP
#define INCLUDE_ACKWARD_DATETIME_TIMEDELTA_HPP

#include <ackward/core/Object.hpp>

namespace ackward { namespace datetime
{

class TimeDelta : private core::Object
{
public:
    static TimeDelta min();
    static TimeDelta max();
    static TimeDelta resolution();

public:
    TimeDelta(double days=0,
              double seconds=0,
              double microseconds=0,
              double milliseconds=0,
              double minutes=0,
              double hours=0,
              double weeks=0);
    TimeDelta(boost::python::object);

    
    int days() const; //	Between -999999999 and 999999999 inclusive
    unsigned int seconds() const; // 	Between 0 and 86399 inclusive
    unsigned int microseconds() const; //	Between 0 and 999999 inclusive

    bool operator==(const TimeDelta&) const;
    bool operator!=(const TimeDelta&) const;
    bool operator<(const TimeDelta&) const;
    bool operator<=(const TimeDelta&) const;
    bool operator>(const TimeDelta&) const;
    bool operator>=(const TimeDelta&) const;

    using core::Object::obj;
};

TimeDelta operator+(const TimeDelta&, const TimeDelta&);
TimeDelta operator-(const TimeDelta&, const TimeDelta&);
TimeDelta operator*(const TimeDelta&, unsigned long);
TimeDelta operator*(unsigned long, const TimeDelta&);
TimeDelta operator/(const TimeDelta&, long);
TimeDelta operator-(const TimeDelta&);
TimeDelta abs(const TimeDelta&);

}}

#endif
