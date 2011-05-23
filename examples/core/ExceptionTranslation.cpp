#include <Python.h>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/Import.hpp>

namespace ac=ackward::core;

class PickleError : public ac::Exception {};

int main(int argc, char** argv)
{
    Py_Initialize();

    // registerExceptionTranslation() is a convience method for
    // mapping a Python exception to a `throw-with-python-info`
    // action.
    ac::registerExceptionTranslation<PickleError>(
        ac::import("pickle").attr("PickleError"));

    try {
        ac::import("my_module").attr("my_method")();
    } catch (const boost::python::error_already_set&) {
        // The following two expressions do the same thing: translate
        // the active Python exception with the singleton
        // ExceptionTranslator exposed through the
        // `exceptionTranslator()` method.

        ac::translatePythonException();

        // ...and...
        
        ac::translatePythonException(
            ac::getExceptionInfo());
    }

    // Also, you can use the TRANSLATE_PYTHON_EXCEPTION macro to
    // perform the most common form of translation.
    try {
        ac::import("my_module").attr("another_method")();
    } TRANSLATE_PYTHON_EXCEPTION();

    return 1;
}
