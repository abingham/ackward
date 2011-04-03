#ifndef INCLUDE_ACKWARD_CORE_EXCEPTION_TRANSLATION_HPP
#define INCLUDE_ACKWARD_CORE_EXCEPTION_TRANSLATION_HPP

#include <boost/python/object.hpp>
#include <boost/python/tuple.hpp>

#include <ackward/core/ExceptionTranslator.hpp>

namespace ackward {
namespace core {

/** Get the ExceptionTranslator object used by ackward.

    This is the ExceptionTranslator instance used by
    e.g. `translatePythonException()` and
    `registerExceptionTranslation()`.
 */
ExceptionTranslator& exceptionTranslator();

/** Register a translation from a Python exception class to a C++
    exception type.

    This associates T with `pythonEx' using a `throw_with_python_info`
    action.

    @param pythonEx The Python exception object to be translated into
      C++.
    @tparam T The C++ class into which the Python exception will be
      translated.
    
 */
template <typename T>
void registerExceptionTranslation(boost::python::object pythonEx)
{
    exceptionTranslator().add(
        pythonEx, 
        &throw_with_python_info<T>);
}

void translatePythonException();
void translatePythonException(boost::python::tuple);
boost::python::tuple getExceptionInfo();

}
}

#define TRANSLATE_PYTHON_EXCEPTION()                \
catch (const boost::python::error_already_set&) {   \
    ackward::core::translatePythonException();      \
    throw;                                          \
}

#endif
