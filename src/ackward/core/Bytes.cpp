#include <ackward/core/Bytes.hpp>

namespace bp=boost::python;

namespace ackward {
namespace core {

Bytes::Bytes(bp::object obj) :
    Object (obj)
{
    if (!PyBytes_Check(obj.ptr()))
        throw ValueError();
}

Bytes::Bytes(const char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyBytes_FromStringAndSize(data, len))))
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

}}
