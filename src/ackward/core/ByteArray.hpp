#ifndef INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP
#define INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP

#include <Python.h>

#include <boost/array.hpp>
#include <boost/python/converter/registry.hpp>
#include <boost/python/str.hpp>
#include <boost/python/to_python_converter.hpp>

namespace ackward {
namespace core {

/** A to-/from-python converter template for boost::arrays<unsigned char, N>. 

    To setup a converter for a particular size of array N, just
    instantiate a ByteArray_python_converter<N> somewhere. Generally
    you should do this in some sort of initialization method, or
    somewhere early in your execution.
 */
template <unsigned int Size>
struct ByteArray_python_converter
{
    typedef boost::array<unsigned char, Size> Array;

    ByteArray_python_converter()
        {
            static bool initialized = false;

            if (initialized) return;

            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<Array>());

            boost::python::to_python_converter<
                Array,
                ByteArray_python_converter<Size> >();

            initialized = true;
        }
    
    static void* convertible(PyObject* obj_ptr)
        {
            if (PyBytes_Check(obj_ptr))
            {
                if (PyBytes_Size(obj_ptr) != Size) return 0;
            }
            else if (PyByteArray_Check(obj_ptr)) 
            {
                if (PyByteArray_Size(obj_ptr) != Size) return 0;
            }
            else
                return 0;

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

            const char* chardata = 
                PyByteArray_Check(obj_ptr)
                ? PyByteArray_AsString(obj_ptr)
                : PyBytes_AsString(obj_ptr);

            std::copy(chardata, 
                      chardata + Size,
                      arr->begin());
            
            // Stash the memory chunk pointer for later use by boost.python
            data->convertible = storage;
        }

    static PyObject* convert(const Array& arr)
        {
            namespace bp=boost::python;

            bp::object bytes = bp::object(
                bp::handle<>(
                    PyBytes_FromStringAndSize(
                        reinterpret_cast<const char*>(arr.data()), 
                        arr.size())));

            return boost::python::incref(
                bytes.ptr());
        }
};

} // namepace core
} // namespace ackward

#endif
