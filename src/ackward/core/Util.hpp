#ifndef INCLUDE_ACKWARD_CORE_UTIL_HPP
#define INCLUDE_ACKWARD_CORE_UTIL_HPP

#include <Python.h>

#include <string>

#include <boost/python/object.hpp>
#include <boost/python/str.hpp>

#include <ackward/core/Exceptions.hpp>

namespace ackward { 
namespace core {

/** \rst

    Determine if an object is the None object.
    
    This is equivalent to the following Python code::

      obj is None

    \endrst

    @param obj The object to test.
    @return True if `obj` is `None`, False otherwise.
 */
bool is_none(const boost::python::object& obj);

/** Create in iterator over some Python object.

    @param obj The object to create an iterator over.
    @return An iterator object
    @throw TypeError `obj` is not iterable.
 */ 
boost::python::object 
iter(boost::python::object obj);

/** Call "obj.next()" on some object (generally an iterator, but no
    check it made to that effect.) 
  
    @param iterator The iterator to get the next element from.
    @return The next element from `iterator`.
    @throw TypeError `iterator` is not an iterator.
 */
boost::python::object
next(boost::python::object iterator);

/** Convert a bp::str to a std::wstring 
    
    @param s The Python string to convert into a wstring.
    @return The wstring copied from `s`.
 */
std::wstring strToWString(boost::python::str s);

/** Call "repr(obj)" on an object.

    @param obj The object to get a repr for.
    @return The result of `repr(obj)`.
 */
std::wstring repr(boost::python::object obj);

/** Call "str(obj)" on an object.
    
    @param obj The object to get a string for.
    @return The result of `str(obj)`.
 */
std::wstring str(boost::python::object obj);

/** Call str() on an object that supports the object protocol.

    @param t The object-protocol object to call `str` on.
    @return The result of `str(t)`.
 */
template <typename T>
std::wstring str(const T& t) { return ackward::core::str(t.obj()); }

/** Get the "builtins" module.

    @return The "builtins" module object.
 */
boost::python::object builtins();

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
    @tparam ExcType The type of exception to throw if `obj` is not a
      `typeName`. This exception will be default-constructed.
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

} // core
} // ackward

#endif
