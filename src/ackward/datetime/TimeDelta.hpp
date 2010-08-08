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

    // t1 = t2 + t3	Sum of t2 and t3. Afterwards t1-t2 == t3 and t1-t3 == t2 are true. (1)
    //     t1 = t2 - t3	Difference of t2 and t3. Afterwards t1 == t2 - t3 and t2 == t1 + t3 are true. (1)
    //     t1 = t2 * i or t1 = i * t2	Delta multiplied by an integer or long. Afterwards t1 // i == t2 is true, provided i != 0.
    //     In general, t1 * i == t1 * (i-1) + t1 is true. (1)
    //     t1 = t2 // i	The floor is computed and the remainder (if any) is thrown away. (3)
    //     +t1	Returns a timedelta object with the same value. (2)
    //     -t1	equivalent to timedelta(-t1.days, -t1.seconds, -t1.microseconds), and to t1* -1. (1)(4)
    //     abs(t)

    using core::Object::obj;
};

}}

#endif
