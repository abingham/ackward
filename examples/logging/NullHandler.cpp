#include <Python.h>

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
    log.addHandler(NullHandler());

    log.info(L"snooze");

    return 0;
}
