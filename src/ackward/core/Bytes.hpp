#ifndef INCLUDE_ACKWARD_CORE_BYTES_HPP
#define INCLUDE_ACKWARD_CORE_BYTES_HPP

#include <ackward/core/Object.hpp>

namespace ackward {
namespace core {

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

    // iteration
public:
    typedef const char* iterator;
    typedef const char* const_iterator;
    
    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;
};

} // core
} // ackward

#endif
