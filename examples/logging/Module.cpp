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

    basicConfig();

    Logger log = getLogger(L"module1.impl.logger");
    log.error(L"This is an error!");

    disable(DEBUG());

    debug(L"You should not see this.");

    shutdown();

    return 0;
}
