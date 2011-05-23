#include <Python.h>

#include <ackward/core/Import.hpp>

int main(int argc, char** argv)
{
    Py_Initialize();

    // You can get an object by module-name plus attribute name.
    ackward::core::findObject("os.path", "sep");

    // Or you can just use a fully-qualified name.
    ackward::core::findObject("os.path.sep");

    return 0;
}
