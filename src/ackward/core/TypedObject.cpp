#include <ackward/core/TypedObject.hpp>

#include <ackward/core/Exceptions.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

TypedObject::TypedObject(boost::python::object obj,
                         const std::string& typeName) :
    Object (obj)
{
    object typeObj(
        handle<>(
            PyObject_Type(
                obj.ptr())));
    
    if (!PyType_Check(typeObj.ptr()))
        throw ValueError();

    object testType(
        handle<>(
            PyRun_String(
                typeName.c_str(), 
                0, 
                NULL, 
                NULL)));
    
    if (!PyType_Check(testType.ptr()))
        throw ValueError();

    if (!PyType_IsSubtype(
            reinterpret_cast<PyTypeObject*>(typeObj.ptr()), 
            reinterpret_cast<PyTypeObject*>(testType.ptr())))
        throw ValueError();
}

}}
