#ifndef INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP
#define INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP

#include <Python.h>

#include <boost/array.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/str.hpp>
#include <boost/python/to_python_converter.hpp>

namespace ackward {
namespace core {

template <unsigned int Size>
struct ByteArray_python_converter
{
    typedef boost::array<unsigned char, Size> Array;

    ByteArray_python_converter()
        {
            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<Array>());

            boost::python::to_python_converter<
                Array,
                ByteArray_python_converter<Size> >();
        }
    
    static void* convertible(PyObject* obj_ptr)
        {
            if (!PyString_Check(obj_ptr)) return 0;
            if (PyString_Size(obj_ptr) != Size) return 0;
            return obj_ptr;
        }
    
    static void construct(
        PyObject* obj_ptr,
        boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost::python;

            void* storage = (
                (boost::python::converter::rvalue_from_python_storage<Array>*)
                data)->storage.bytes;
            
            // in-place construct the new QString using the character data
            // extraced from the python object
            Array* arr = new (storage) Array;

            const char* chardata = PyString_AsString(obj_ptr);
            std::copy(chardata, 
                      chardata + Size,
                      arr->begin());
            
            // Stash the memory chunk pointer for later use by boost.python
            data->convertible = storage;
        }

    static PyObject* convert(const Array& arr)
        {
            boost::python::str pyvalue(
                reinterpret_cast<const char*>(arr.begin()),
                reinterpret_cast<const char*>(arr.end()));
            return boost::python::incref(
                pyvalue.ptr());
        }
};

} // namepace core
} // namespace ackward

#endif
