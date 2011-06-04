#ifndef INCLUDE_ACKWARD_CORE_DETAIL_PYTHON_CONVERTER_HPP
#define INCLUDE_ACKWARD_CORE_DETAIL_PYTHON_CONVERTER_HPP

#include <Python.h>

#include <string>
#include <vector>

#include <ackward/core/GetClass.hpp>
#include <boost/foreach.hpp>
#include <boost/python.hpp>

namespace ackward {
namespace core {
namespace detail {

/** Implements to-python conversion for objects that use the "object"
 * protocol.
 */
template <typename T>
struct to_python_object_
{
    static PyObject* convert(const T& t)
        {
            return boost::python::incref(
                t.obj().ptr());
        }
};

/** Implements from-python conversion for objects that support the
 * object protocol.
 */
template <typename T>
struct from_python_object_
{
    /** 
        @param className The full name of the python class that this
                         converts from.
     */
    from_python_object_(const std::string& className)
        {
            // We track the things that have been declared
            // from-python-convertible by remembering their class name
            // in a container. Later, the static ``convertible``
            // method checks this container to see if they've been
            // registered as convertible.
            classNames_.push_back(className);

            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<T>());
        }
    
    static void* convertible(PyObject* obj_ptr)
        {
            // Check the class-name of ``obj_ptr`` to see if it's been
            // registered.
            BOOST_FOREACH(const std::string& name, classNames_)
            {
                boost::python::object cls = 
                    ackward::core::getClass(name);
                if (PyObject_IsInstance(obj_ptr, cls.ptr()))
                    return obj_ptr;
            }

            return 0;
        }
    
    static void construct(
        PyObject* obj_ptr,
        boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost::python;

            void* storage = (
                (boost::python::converter::rvalue_from_python_storage<T>*)
                data)->storage.bytes;
            
            // in-place construct the new QString using the character data
            // extraced from the python object
            new (storage) T(
                object(
                    handle<>(
                        borrowed(
                            obj_ptr))));
            
            // Stash the memory chunk pointer for later use by boost.python
            data->convertible = storage;
        }

private:
    static std::vector<std::string> classNames_;
};

template <typename T>
std::vector<std::string> from_python_object_<T>::classNames_;

}
}
}

#endif
