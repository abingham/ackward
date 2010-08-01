#ifndef INCLUDE_BA_LOG_DETAIL_PYTHON_CONVERTER_HPP
#define INCLUDE_BA_LOG_DETAIL_PYTHON_CONVERTER_HPP

#include <string>

#include <boost/python.hpp>

#include <ackward/core/GetClass.hpp>

namespace ackward { namespace core 
{

template <typename T>
struct to_python_object_
{
    static PyObject* convert(const T& t)
        {
            return boost::python::incref(
                t.obj().ptr());
        }
};

template <typename T>
struct from_python_object_
{
    from_python_object_(const std::string& className)
        {
            className_ = className;

            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<T>());
        }
    
    static void* convertible(PyObject* obj_ptr)
        {
            boost::python::object cls = 
                ackward::core::getClass(className_);
            if (!PyObject_IsSubclass(obj_ptr, cls.ptr())) return 0;
            return obj_ptr;
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
                        obj_ptr)));
            
            // Stash the memory chunk pointer for later use by boost.python
            data->convertible = storage;
        }

private:
    static std::string className_;
};

template <typename T>
std::string from_python_object_<T>::className_;

template <typename T>
void initializePythonConverter(const std::string& className)
{
    boost::python::to_python_converter<
        T,
        to_python_object_<T> >();

    from_python_object_<T> temp(className);
}

}}

#endif