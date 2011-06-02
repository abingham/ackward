#include <Python.h>

#include <ackward/core/Initialize.hpp>

int main(int argc, char** argv)
{
    Py_Initialize();

    // Initialize ackward::core. This should be done before using
    // other parts of the library.
    ackward::core::initialize();

    // After the call, python type conversions are available for
    // ackward::core data types, among other things.

    return 0;
}
