#ifndef INCLUDE_ACKWARD_CORE_BYTES_HPP
#define INCLUDE_ACKWARD_CORE_BYTES_HPP

#include <Python.h>

#include <vector>

#include <ackward/core/Object.hpp>

namespace ackward {
namespace core {

class ByteArray;

class Bytes : private Object
{
public:
    /** Construct Bytes from existing python bytes object 

        @throw ValueError `obj` is not a Bytes object.
     */
    Bytes(boost::python::object obj);

    /** Construct Bytes from existing data.

        @param data The data to copy into the new Bytes object
        @param len The number of bytes in `data`.
    */
    Bytes(const char* data, Py_ssize_t len);

    Bytes(const ByteArray&);

    /** Construct Bytes from a range of values */
    template <typename Itr>
    Bytes(Itr, Itr);

    /** Construct a new, empty Bytes object
     */
    Bytes();

    /** Get the number of bytes in the Bytes 
     */
    Py_ssize_t size() const;

    /** Get the byte at a particuar index.
        @param idx The index of the byte to get.
        @throw IndexError Index is out of range.
     */
    char operator[](std::size_t idx) const;

    bool operator==(const Bytes&) const;
    bool operator==(const ByteArray&) const;

    using Object::obj;

    // iteration
public:
    typedef const char* iterator;
    typedef const char* const_iterator;
    
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    template <typename Itr>
    static boost::python::object copyData(Itr, Itr);
};

template <typename Itr>
Bytes::Bytes(Itr begin, Itr end) :
    Object ( Bytes::copyData(begin, end) )
{}

template <typename Itr>
boost::python::object
Bytes::copyData(Itr begin, Itr end)
{
    using namespace boost::python;

    std::vector<char> data(begin, end);

    object obj = object(
        handle<>(
            PyBytes_FromStringAndSize(
                &data[0], 
                data.size())));

    return obj;
}

template <>
boost::python::object
Bytes::copyData<const char*>(const char* begin, 
                             const char* end);

} // core
} // ackward

#endif
