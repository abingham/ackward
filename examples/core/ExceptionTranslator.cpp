#include <Python.h>

#include <ackward/core/Import.hpp>
#include <ackward/core/Exceptions.hpp>
#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/ExceptionTranslator.hpp>

namespace ac=ackward::core;

class ExampleException : public ac::Exception
{};

int main(int argc, char** argv)
{
    Py_Initialize();

    // Construct an exception translator instance.
    ac::ExceptionTranslator ex_translator;

    // Populate it with translation mappings. These map from Python
    // exception types to actions that the translator will take when
    // ``translate()`` is called. These actions are typically to throw
    // a C++ exception.
    
    // In this example, the Python exception
    // ``pickle.PickleError`` will be translated into a
    // throw of the C++ exception ``ExampleException``.
    ex_translator.add(
        ac::import("pickle").attr("PickleError"),
        &ac::throw_with_python_info<ExampleException>);

    try {
        ac::import("my_module").attr("my_function")();
    } catch (const boost::python::error_already_set&) {

        // This attempts to translate any active Python exception,
        // based on the contents of the Python exception registers.
        // If the code in the try-block resulted in an
        // ``PickleError``, then this call will result in a
        // throw of an ``ExampleException``.
        ex_translator.translate(
            ac::getExceptionInfo());

        // If: 
        //   1. The translator doesn't know what to do with the
        //      Python exception, or
        //   2. The action doesn't result in a throw, or
        //   3. There is no active python exception
        // then we get here. It's often best to just rethrow.
        throw;
    }

    return 0;
}
