#ifndef INCLUDE_ACKWARD_DATETIME_TIME_HPP
#define INCLUDE_ACKWARD_DATETIME_TIME_HPP

#include <ackward/core/Object.hpp>
#include <ackward/core/GetClass.hpp>

namespace ackward { namespace datetime
{

class TimeDelta;

class Time : private core::Object
{
public:
    #include <ackward/datetime/Time_akw.hpp>
};

}}

#endif
