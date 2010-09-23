#ifndef INCLUDE_ACKWARD_DATETIME_DATETIME_HPP
#define INCLUDE_ACKWARD_DATETIME_DATETIME_HPP

#include <ackward/core/Object.hpp>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace datetime
{

class TZInfo;

class DateTime : private ackward::core::Object
{
public:
    #include <ackward/datetime/DateTime_akw.hpp>
};

}}

#endif
