#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/handlers/WatchedFileHandler.hpp>

#include <boost/python.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig();
    Logger log = getLogger(L"airplane!");

    handlers::WatchedFileHandler h(
        L"watched.log");

    log.addHandler(h);

    log.warning(L"I'm serious. And stop calling me Shirley.");

    return 0;
}
