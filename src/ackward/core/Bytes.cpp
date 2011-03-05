#include <ackward/core/Bytes.hpp>

#include <ackward/core/ByteArray.hpp>
#include <ackward/core/Exceptions.hpp>
#include <ackward/core/PythonVersion.hpp>

#if ACKWARD_PYTHON_VERSION == 2

#include "Bytes.python2.ipp"

#elif ACKWARD_PYTHON_VERSION == 3

#include "Bytes.python3.ipp"

#endif
