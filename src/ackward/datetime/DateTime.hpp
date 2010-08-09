#ifndef INCLUDE_ACKWARD_DATETIME_DATETIME_HPP
#define INCLUDE_ACKWARD_DATETIME_DATETIME_HPP

#include <ackward/core/Object.hpp>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace datetime
{

class DateTime : private ackward::core::Object
{
public:
    DateTime(boost::python::object);

    using Object::obj;
};

}}

#endif
