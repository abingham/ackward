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
    if (PyObject_CheckBuffer(obj.ptr()))
        return obj;

    throw ackward::core::ValueError();
}

class BufferRelease
{
public:
    BufferRelease(Py_buffer& b) : b_ (b) {}
    ~BufferRelease() { PyBuffer_Release(&b_); }

private:
    Py_buffer& b_;
};

bp::object fromObject(bp::object obj) 
{
    validateObject(obj);

    Py_buffer view;
    if (PyObject_GetBuffer(obj.ptr(), &view, PyBUF_SIMPLE) == -1)
        throw ackward::core::ValueError();

    BufferRelease br(view);

    PyObject* sz = PyString_FromStringAndSize(
        reinterpret_cast<char*>(view.buf), 
        view.len);
    if (!sz) throw ackward::core::ValueError();

    return bp::object(
        bp::handle<>(
            PyString_FromStringAndSize(
                reinterpret_cast<char*>(view.buf), 
                view.len)));
}

}

namespace ackward {
namespace core {

Bytes::Bytes(bp::object obj) :
    Object (::fromObject(obj))
{}

Bytes::Bytes(const unsigned char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyString_FromStringAndSize(
                    reinterpret_cast<const char*>(data), 
                    len))))
{}

Bytes::Bytes(const char* data, Py_ssize_t len) :
    Object (
        bp::object(
            bp::handle<>(
                PyString_FromStringAndSize(
                    data, 
                    len))))
{}

Bytes::Bytes(const ByteArray& b) :
    Object (::fromObject(b.obj()))
{}

Bytes::Bytes() :
    Object (
        bp::object(
            bp::handle<>(
                PyString_FromStringAndSize(NULL, 0))))
{
}

Py_ssize_t Bytes::size() const
{
    return PyString_Size(obj().ptr());
}

unsigned char Bytes::operator[](std::size_t idx) const
{
    if (idx >= (std::size_t)size())
        throw IndexError();

    return PyString_AsString(obj().ptr())[idx];
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
        PyString_AsString(obj().ptr()));
}

Bytes::iterator Bytes::end()
{
    return reinterpret_cast<iterator>(
        PyString_AsString(obj().ptr()) + size());
}

Bytes::const_iterator Bytes::begin() const
{
    return reinterpret_cast<const_iterator>(
        PyString_AsString(obj().ptr()));
}

Bytes::const_iterator Bytes::end() const
{
    return reinterpret_cast<const_iterator>(
        PyString_AsString(obj().ptr()) + size());
}

template <>
boost::python::object
Bytes::copyData<const char*>(const char* begin, 
                             const char* end)
{
    using namespace boost::python;

    object obj = object(
        handle<>(
            PyString_FromStringAndSize(
                begin, 
                end - begin)));

    return obj;
}

}
}
