#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/NullHandler.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig();
    Logger log = getLogger();
    NullHandler h;
    log.addHandler(h);

    log.critical(L"snooze");

    return 0;
}
