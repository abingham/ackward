#ifndef INCLUDE_ACKWARD_CORE_TYPED_OBJECT_HPP
#define INCLUDE_ACKWARD_CORE_TYPED_OBJECT_HPP

#include <ackward/core/Object.hpp>

namespace ackward { namespace core
{

class TypedObject : public Object
{
public:
    TypedObject(boost::python::object obj,
                const std::string& typeName);
};

}}

#endif
