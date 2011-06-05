#include <Python.h>

#include <ackward/core/PythonVersion.hpp>

int main(int, char**)
{
#if ACKWARD_PYTHON_MAJOR_VERSION == 2
    // Python 2 specific code goes here.
#elif ACKWARD_PYTHON_MAJOR_VERSION == 3
    // Python 3 specific code goes here
#else
    // Something is seriously wrong!
#endif

    return 0;
}
