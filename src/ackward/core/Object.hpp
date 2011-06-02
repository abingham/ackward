#ifndef INCLUDE_ACKWARD_CORE_OBJECT_HPP
#define INCLUDE_ACKWARD_CORE_OBJECT_HPP

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/Import.hpp>

namespace ackward { namespace core
{

/** A base class for types that expose a python object in C++.

    Essentially, this just manages an underlying
    boost::python::object. There is no more magic than that. In
    general, it's probably best to derive from this class privately;
    this class just defines a small protocol.
 */
class Object
{
public:
    Object(boost::python::object);

    /** Get the underlying boost::python::object.
     */
    boost::python::object obj();

    /** Get the underlying boost::python::object.
     */
    const boost::python::object obj() const;

private:
    boost::python::object obj_;
};

}}

/** \rst
    
    Define an interface to an attribute on the underlying Python
    object.

    This adds a member function to a core::Object that returns the
    value of an attribute on the Python object wrapped by a
    core::Object. The value of the underlying attribute is converted
    to a C++ type using ``boost::python::extract`` to ``result_type``.

    Args:
      * result_type: The type of the attribute in C++.
      * name: The name of the attribute on the object.

    \endrst
 */
#define ACKWARD_ATTR(result_type, name)               \
    result_type name() const {                        \
        return boost::python::extract<result_type>(   \
            obj().attr(#name));                       \
    }

/** \rst

    Define an interface to a 0-arity method on the underlying Python
    object.

    This is just like ACKWARD_ATTR except that this calls the
    underlying attribute and return the resulting value rather than
    just returning the attribute itself.

    Args:
      * result_type: The type of the attribute in C++.
      * name: The name of the attribute on the object.

    \endrst
 */
#define ACKWARD_METHOD(result_type, name)       \
    result_type name() const {                  \
    return boost::python::extract<result_type>( \
        obj().attr(#name)());                   \
    }

// Getter/Setter

/*
// #define ACKWARD_CLASS_METHOD(result_type, mod, cls, name)  \
//     static result_type name() {                           \
//         return boost::python::extract<result_type>(       \
//             ackward::core::findObject(#mod, #cls).attr(#name)); \
//     }
*/

#endif
