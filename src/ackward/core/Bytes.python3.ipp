// -*- c++ -*-

namespace bp=boost::python;

namespace {

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

}

namespace ackward {
namespace core {

Bytes::Bytes(bp::object obj) :
    Object (::validateObject(obj))
{}

Bytes::Bytes(const unsigned char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyBytes_FromStringAndSize(
                    reinterpret_cast<const char*>(data), 
                    len))))
{}

Bytes::Bytes(const char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyBytes_FromStringAndSize(
                    data, 
                    len))))
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

unsigned char Bytes::operator[](std::size_t idx) const
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
    return reinterpret_cast<iterator>(
        PyBytes_AsString(obj().ptr()));
}

Bytes::iterator Bytes::end()
{
    return reinterpret_cast<iterator>(
        PyBytes_AsString(obj().ptr()) + size());
}

Bytes::const_iterator Bytes::begin() const
{
    return reinterpret_cast<const_iterator>(
        PyBytes_AsString(obj().ptr()));
}

Bytes::const_iterator Bytes::end() const
{
    return reinterpret_cast<const_iterator>(
        PyBytes_AsString(obj().ptr()) + size());
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

}
}
