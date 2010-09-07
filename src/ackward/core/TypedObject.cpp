#include <ackward/core/TypedObject.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

TypedObject::TypedObject(boost::python::object obj,
                         const std::wstring& typeName) :
    Object (obj)
{
    object typeObj(
        handle<>(
            PyObject_Type(obj.ptr())));
    
    // TODO: Lookup class from name and call issubclass with typeObj
    // and the resulting type.
}

}}
