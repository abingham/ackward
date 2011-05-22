#ifndef INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP
#define INCLUDE_ACKWARD_CORE_BYTEARRAY_HPP

#include <Python.h>

#include <vector>

#include <ackward/core/Object.hpp>

namespace ackward {
namespace core {

class Bytes;

/** Wraps a Python `bytearray` object.
 */
class ByteArray : private Object
{
public:
    /** Construct ByteArray from existing python bytearray.

        @param ba A Python ``bytearray`` object.
        @throw ValueError `ba` is not a bytearray object.
     */
    explicit ByteArray(boost::python::object ba);

    /** Construct ByteArray from existing data.

        @param data The data to copy into the new Bytes object
        @param len The number of bytes in `data`.
    */
    ByteArray(const unsigned char* data, Py_ssize_t len);

    /** Conversion constructor from Bytes.

        @param b A ``Bytes`` object from which to copy data.
     */ 
    explicit ByteArray(const Bytes& b);
    
    /** Construct Bytes from a range of values 
        
        @param b The `begin` iterator to copy from.
        @param e The `end` iterator to copy from.
     */
    template <typename Itr>
    ByteArray(Itr b, Itr e);

    /** Construct empty ByteArray */
    ByteArray();

    /** Get number of bytes in array */
    Py_ssize_t size() const;
    
    /** Get/set the byte at a particuar index.
        @param idx The index of the byte to get.
        @throw IndexError Index is out of range.
    */
    unsigned char operator[](std::size_t idx) const;
    unsigned char& operator[](std::size_t idx);

    bool operator==(const ByteArray&) const;
    bool operator==(const Bytes&) const;

    using Object::obj;

    // iteration
public:
    typedef unsigned char* iterator;
    typedef const unsigned char* const_iterator;
    
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
    return copyData<const char*>(
        &data[0],
        &data[0] + data.size());
}

template <>
boost::python::object
ByteArray::copyData<const char*>(
    const char* begin, 
    const char* end);

} // namepace core
} // namespace ackward

#endif
