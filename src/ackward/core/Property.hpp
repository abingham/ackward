#ifndef INCLUDE_ACKWARD_CORE_PROPERTY_HPP
#define INCLUDE_ACKWARD_CORE_PROPERTY_HPP

#include <iostream>
#include <string>

#include <boost/call_traits.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Object.hpp>

namespace ackward {
namespace core {

/** Property<T> is a value-like C++ interface to an underlying Python
    property. It provides a C++ API for properties which is similar to
    what you get in Python.

    \rst
    General use is like this::

      class MyClass {
      public:
        Property<int> myProperty;
      };
      ...
      MyClass c;
      c.myProperty = 3;
      int x = c.myProperty;

    \endrst
 */
template <typename T>
class Property : private Object
{
public:
    typedef T value_type;

    /** Construct a new property.

        @param obj The underlying Python object.
        @param pythonName The name of the property on `obj`.
     */
    Property(boost::python::object obj,
             const std::string& pythonName) :
        Object (obj),
        pythonName_ (pythonName)
        {}

    /** Get the underlying property value.
     */
    operator value_type () const
        {
            try {
                return boost::python::extract<value_type>(
                    obj().attr(pythonName_.c_str()));
            } TRANSLATE_PYTHON_EXCEPTION();
        }

    /** Assign to the underlying property.

        @param v The value to assign.
        @returns This object.
     */
    Property<value_type>& operator=(typename boost::call_traits<value_type>::const_reference v)
        {
            try {
                obj().attr(pythonName_.c_str()) = v;
            } TRANSLATE_PYTHON_EXCEPTION();

            return *this;
        }

    using Object::obj;

private:
    std::string pythonName_;

};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Property<T>& p)
{
    os << static_cast<T>(p);
    return os;
}

}
}

#endif
