#include <Python.h>

#include <iostream>

#include <ackward/core/Exceptions.hpp>
#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/Import.hpp>
#include <ackward/core/Initialize.hpp>

namespace ac=ackward::core;

void callPythonFunction()
{
    try {
        // This will trigger an AttributeError in Python, and the
        // exception translation will convert that into an
        // ackward::core::AttributeError.
        ac::import("uuid").attr("non_existent_attribute")();
    } TRANSLATE_PYTHON_EXCEPTION();
}

int main(int argc, char** argv)
{
    Py_Initialize();
    ac::initialize();

    try {
        callPythonFunction();
    } catch (const ac::AttributeError&) {
        std::cerr << "No such function!" << std::endl;
    }

    return 0;
}
