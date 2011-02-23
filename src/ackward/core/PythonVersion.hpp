#include <Python.h>

#if PY_MAJOR_VERSION == 2

#define ACKWARD_PYTHON_VERSION 2

#elif PY_MAJOR_VERSION == 3

#define ACKWARD_PYTHON_VERSION 3

#else

#error "ackward requires Python version 2 or 3"

#endif
