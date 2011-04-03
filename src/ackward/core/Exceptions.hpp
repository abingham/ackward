#ifndef INCLUDE_ACKWARD_CORE_EXCEPTIONS_HPP
#define INCLUDE_ACKWARD_CORE_EXCEPTIONS_HPP

/** C++ counterparts to the standard Python exceptions.
 */

#include <Python.h>

#include <exception>

#include <boost/exception/all.hpp>

namespace boost { namespace python { class tuple; } }

namespace ackward { 
namespace core {

/** The base for all ackward exceptions. */
class Exception : public virtual boost::exception,
                  public virtual std::exception
{};

/** A collection of C++ analogues for the standard Python exceptions.
 */
class AttributeError : public Exception {};
class ImportError : public Exception {};
class IndexError : public Exception {};
class IOError : public Exception {};
class KeyError : public Exception {};
class TypeError : public Exception {};
class ReferenceError : public Exception {};
class ValueError : public Exception {};
class StopIteration : public Exception {};

}}

#endif
