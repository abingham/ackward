#ifndef INCLUDE_ACKWARD_CORE_EXCEPTION_TRANSLATION_HPP
#define INCLUDE_ACKWARD_CORE_EXCEPTION_TRANSLATION_HPP

#include <boost/python/object.hpp>
#include <boost/python/tuple.hpp>

#include <ackward/core/ExceptionTranslator.hpp>

namespace ackward {
namespace core {

/*! Get the ExceptionTranslator object used by ackward.

    This is the ExceptionTranslator instance used by
    e.g. `translatePythonException()` and
    `registerExceptionTranslation()`.

    @return The ackward ExceptionTranslator instance.
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

/** Translate the current Python exception (if any.)

    This uses ``getExceptionInfo()`` to get the current Python
    exception.
 */
void translatePythonException();

/** Translate the Python exception represented by the the (type,
    value, traceback) tuple argument.

    @param exc The (type,value,traceback) tuple to translate.
 */
void translatePythonException(boost::python::tuple exc);

/** Get the current Python exception info tuple

    @return A (type, value, traceback) tuple for the current Python
      exception.
 */
boost::python::tuple getExceptionInfo();

}
}

#define TRANSLATE_PYTHON_EXCEPTION()                \
catch (const boost::python::error_already_set&) {   \
    ackward::core::translatePythonException();      \
    throw;                                          \
}

#endif
