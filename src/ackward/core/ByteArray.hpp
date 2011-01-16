#ifndef INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP
#define INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP

#include <Python.h>

#include <vector>

#include <ackward/core/Object.hpp>

namespace ackward {
namespace core {

class Bytes;

class ByteArray : private Object
{
public:
    /** Construct ByteArray from existing python bytearray.

        @throw ValueError `ba` is not a bytearray object.
     */
    ByteArray(boost::python::object ba);

    /** Construct ByteArray from existing data.

        @param data The data to copy into the new Bytes object
        @param len The number of bytes in `data`.
    */
    ByteArray(const char* data, Py_ssize_t len);

    ByteArray(const Bytes&);
    
    /** Construct Bytes from a range of values */
    template <typename Itr>
    ByteArray(Itr, Itr);

    /** Construct empty ByteArray */
    ByteArray();

    /** Get number of bytes in array */
    Py_ssize_t size() const;
    
    /** Get/set the byte at a particuar index.
        @param idx The index of the byte to get.
        @throw IndexError Index is out of range.
    */
    char operator[](std::size_t idx) const;
    char& operator[](std::size_t idx);

    bool operator==(const ByteArray&) const;
    bool operator==(const Bytes&) const;

    using Object::obj;

    // iteration
public:
    typedef char* iterator;
    typedef const char* const_iterator;
    
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    template <typename Itr>
    static boost::python::object copyData(Itr, Itr);
};

template <typename Itr>
ByteArray::ByteArray(Itr begin, Itr end) :
    Object ( ByteArray::copyData(begin, end) )
{}

template <typename Itr>
boost::python::object
ByteArray::copyData(Itr begin, Itr end)
{
    using namespace boost::python;

    std::vector<char> data(begin, end);

    object obj = object(
        handle<>(
            PyByteArray_FromStringAndSize(
                &data[0], 
                data.size())));

    return obj;
}

template <>
boost::python::object
ByteArray::copyData<const char*>(const char* begin, 
                                 const char* end);

} // namepace core
} // namespace ackward

#endif
