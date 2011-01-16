#include <ackward/core/ByteArray.hpp>

#include <ackward/core/Bytes.hpp>
#include <ackward/core/Exceptions.hpp>

namespace bp=boost::python;

namespace
{

/* Check to see if:
     a) `obj` is a bytearray, or
     b) `obj` supports the buffer protocol.

   If either is true, this returns a bytearray object with data from
   `obj`.

   Otherwise, it throws ValueError.
 */
bp::object validateObject(bp::object obj)
{
    if (PyByteArray_Check(obj.ptr()))
        return obj;

    if (PyObject_CheckBuffer(obj.ptr()))
    {
        bp::object rval = bp::object(
            bp::handle<>(
                PyByteArray_FromObject(obj.ptr())));
        return rval;
    }

    throw ackward::core::ValueError();
}

}

namespace ackward {
namespace core {

ByteArray::ByteArray(bp::object obj) :
    Object (::validateObject(obj))
{}

ByteArray::ByteArray(const char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyByteArray_FromStringAndSize(data, len))))
{}

ByteArray::ByteArray(const Bytes& b) :
    Object(
        bp::object(
            bp::handle<>(
                PyByteArray_FromObject(
                    b.obj().ptr()))))
{}

ByteArray::ByteArray() :
    Object (
        bp::object(
            bp::handle<>(
                PyByteArray_FromStringAndSize(NULL, 0))))
{
}

Py_ssize_t ByteArray::size() const
{
    return PyByteArray_Size(obj().ptr());
}

char ByteArray::operator[](std::size_t idx) const
{
    if (idx >= (std::size_t)size())
        throw IndexError();

    return PyByteArray_AsString(obj().ptr())[idx];
}

bool ByteArray::operator==(const ByteArray& b) const
{
    return obj() == b.obj();
}

bool ByteArray::operator==(const Bytes& b) const
{
    return obj() == b.obj();
}

char& ByteArray::operator[](std::size_t idx)
{
    if (idx >= (std::size_t)size())
        throw IndexError();

    return PyByteArray_AsString(obj().ptr())[idx];
}

ByteArray::iterator ByteArray::begin() 
{
    return PyByteArray_AsString(obj().ptr());
}

ByteArray::iterator ByteArray::end()
{
    return PyByteArray_AsString(obj().ptr()) + size();
}

ByteArray::const_iterator ByteArray::begin() const
{
    return PyByteArray_AsString(obj().ptr());
}

ByteArray::const_iterator ByteArray::end() const
{
    return PyByteArray_AsString(obj().ptr()) + size();
}

template <>
boost::python::object
ByteArray::copyData<const char*>(const char* begin, 
                                 const char* end)
{
    using namespace boost::python;

    object obj = object(
        handle<>(
            PyByteArray_FromStringAndSize(
                begin,
                end - begin)));

    return obj;
}

}}
