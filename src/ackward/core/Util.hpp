#ifndef INCLUDE_BA_LOG_DETAIL_UTIL_HPP
#define INCLUDE_BA_LOG_DETAIL_UTIL_HPP

#include <string>

#include <boost/python/object.hpp>

#include <ackward/core/Exceptions.hpp>

namespace ackward { namespace core
{

bool is_none(const boost::python::object&);

boost::python::object 
iter(boost::python::object);

boost::python::object
next(boost::python::object iterator);

std::wstring repr(boost::python::object);
std::wstring str(boost::python::object);
template <typename T>
std::wstring str(const T& t) { return ackward::core::str(t.obj()); }

/** Determine if an object is of a specified type.

    @param obj The object to test
    @param typeName The full name of the type to test for
    @return True of `obj` is of type `typeName`, false otherwise.
 */
bool isInstance(boost::python::object obj,
                const std::string& typeName);

/** Verify that an object is of a given type, throwing a specified exception if it is not.

    @param obj The object to test
    @param typeName The full name of the expected type of `obj`
    @tparam ExcType The type of exception to throw if `obj` is not a `typeName`. This exception will be default-constructed.
 */
template <typename ExcType=ValueError>
void verifyType(boost::python::object obj,
                const std::string& typeName)
{
    if (!isInstance(obj, typeName))
        throw ExcType();
}

/** Determines if a python object can be converted to a particular C++
    type.

    @param obj_ptr The python object to check
    @tparam T The C++ type to convert `obj_ptr` into.
    @return true if there is a registered converter that can convert
            `obj_ptr` into an object of type `T`; false otherwise.
 */
template <typename T>
bool fromPythonConvertible(PyObject* obj_ptr)
{
    namespace bp = boost::python;

    const bp::converter::registration* reg =
        bp::converter::registry::query(
            bp::type_id<T>());

    if (!reg) return false;
    
    bp::converter::rvalue_from_python_chain* link = 
        reg->rvalue_chain;

    while (link)
    {
        if (link->convertible(obj_ptr))
            return true;
        link = link->next;
    }

    return false;
}

}}

#endif
