#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/handlers/SocketHandler.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig();
    Logger log = getLogger();
    log.addHandler(handlers::SocketHandler(L"http://www.slashdot.org", 80));

    log.info(L"rtfa");

    return 0;
}
