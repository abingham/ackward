#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp>

using namespace ackward::core;
using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig(
        kwargs(L"filename", "example.log")
              (L"filemode", 'w'));

    Logger log = getLogger(L"module1.impl.logger");
    log.error(L"This is an error!");

    disable(DEBUG());

    debug(L"You should not see this.");

    shutdown();

    return 0;
}
