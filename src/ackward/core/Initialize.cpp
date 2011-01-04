#include <ackward/core/Initialize.hpp>

#include <ackward/core/ByteArray.hpp>
#include <ackward/core/Bytes.hpp>
#include <ackward/core/PythonConverter.hpp>

namespace ackward {
namespace core {

void initialize()
{
    static bool initialized = false;

    if (!initialized)
    {
        initializePythonConverter<ByteArray>(
            "bytearray");
        initializeFromPythonConverter<ByteArray>(
            "bytes");

        initializePythonConverter<Bytes>(
            "bytes");
        initializeFromPythonConverter<Bytes>(
            "bytearray");

        initialized = true;
    }
}

}}
