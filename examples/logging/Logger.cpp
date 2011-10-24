#include <Python.h>

#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    // Access Loggers with getLogger().
    Logger log = getLogger(L"my.special.logger");

    // Set the logging level
    log.setLevel(DEBUG());

    // Query the effective level of the logger
    Level lvl = log.getEffectiveLevel();

    // Log a message to the logger
    log.log(lvl, L"The roof is on fire!");

    return 0;
}
