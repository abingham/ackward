#include <ackward/core/Initialize.hpp>

#include <ackward/core/ByteArray.hpp>
#include <ackward/core/Bytes.hpp>
#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/PythonConverter.hpp>

namespace
{

void initializeExceptions()
{
    using namespace ackward::core;

    registerExceptionTranslation<AttributeError>(
        builtins().attr("AttributeError"));
    registerExceptionTranslation<ImportError>(
        builtins().attr("ImportError"));
    registerExceptionTranslation<IndexError>(
        builtins().attr("IndexError"));
    registerExceptionTranslation<IOError>(
        builtins().attr("IOError"));
    registerExceptionTranslation<KeyError>(
        builtins().attr("KeyError"));
    registerExceptionTranslation<TypeError>(
        builtins().attr("TypeError"));
    registerExceptionTranslation<ReferenceError>(
        builtins().attr("ReferenceError"));
    registerExceptionTranslation<ValueError>(
        builtins().attr("ValueError"));
    registerExceptionTranslation<StopIteration>(
        builtins().attr("StopIteration"));
}

}

namespace ackward {
namespace core {

void initialize()
{
    static bool initialized = false;

    if (!initialized)
    {
        ::initializeExceptions();

        initializePythonConverter<ByteArray>(
            "bytearray");
        initializeFromPythonConverter<ByteArray>(
            "bytes");

        initializePythonConverter<Bytes>(
            "bytes");
        initializeFromPythonConverter<Bytes>(
            "bytearray");

#if ACKWARD_PYTHON_MAJOR_VERSION == 2
        initializeFromPythonConverter<Bytes>(
            "str");
#endif

        initialized = true;
    }
}

}}
