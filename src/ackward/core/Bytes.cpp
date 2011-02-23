#include <ackward/core/Bytes.hpp>

#include <ackward/core/ByteArray.hpp>
#include <ackward/core/Exceptions.hpp>

namespace bp=boost::python;

/* Check to see if:
     a) `obj` is a bytes object, or
     b) `obj` supports the buffer protocol.

   If either is true, this returns a bytes object with data from
   `obj`.

   Otherwise, it throws ValueError.
 */
bp::object validateObject(bp::object obj)
{
    if (PyBytes_Check(obj.ptr()))
        return obj;

    if (PyObject_CheckBuffer(obj.ptr()))
    {
        bp::object rval = bp::object(
            bp::handle<>(
                PyBytes_FromObject(obj.ptr())));
        return rval;
    }

    throw ackward::core::ValueError();
}

namespace ackward {
namespace core {

Bytes::Bytes(bp::object obj) :
    Object (::validateObject(obj))
{}

Bytes::Bytes(const char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyBytes_FromStringAndSize(data, len))))
{}

Bytes::Bytes(const ByteArray& b) :
    Object(
        bp::object(
            bp::handle<>(
                PyBytes_FromObject(b.obj().ptr()))))
{}

Bytes::Bytes() :
    Object (
        bp::object(
            bp::handle<>(
                PyBytes_FromStringAndSize(NULL, 0))))
{
}

Py_ssize_t Bytes::size() const
{
    return PyBytes_Size(obj().ptr());
}

char Bytes::operator[](std::size_t idx) const
{
    if (idx >= (std::size_t)size())
        throw IndexError();

    return PyBytes_AsString(obj().ptr())[idx];
}

bool Bytes::operator==(const Bytes& b) const
{
    return obj() == b.obj();
}

bool Bytes::operator==(const ByteArray& b) const
{
    return obj() == b.obj();
}

Bytes::iterator Bytes::begin() 
{
    return PyBytes_AsString(obj().ptr());
}

Bytes::iterator Bytes::end()
{
    return PyBytes_AsString(obj().ptr()) + size();
}

Bytes::const_iterator Bytes::begin() const
{
    return PyBytes_AsString(obj().ptr());
}

Bytes::const_iterator Bytes::end() const
{
    return PyBytes_AsString(obj().ptr()) + size();
}

template <>
boost::python::object
Bytes::copyData<const char*>(const char* begin, 
                             const char* end)
{
    using namespace boost::python;

    object obj = object(
        handle<>(
            PyBytes_FromStringAndSize(
                begin, 
                end - begin)));

    return obj;
}

}}
