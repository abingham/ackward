#include <exception>

#include <boost/exception.hpp>

namespace boost { namespace python { class tuple; } }

namespace ackward { namespace core
{

void translatePythonException();
void translatePythonException(boost::python::tuple);
boost::python::tuple getExceptionInfo();

#define TRANSLATE_PYTHON_EXCEPTION()                \
catch (const boost::python::error_already_set&) {   \
    translatePythonException();                     \
    throw;                                          \
}

class Exception : public virtual boost::exception,
                  public virtual std::exception
{};
class AttributeError : public Exception {};
class IndexError : public Exception {};
class IOError : public Exception {};
class KeyError : public Exception {};
class TypeError : public Exception {};
class ReferenceError : public Exception {};
class ValueError : public Exception {};
class StopIteration : public Exception {};

}}