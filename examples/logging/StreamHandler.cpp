#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/handlers/StreamHandler.hpp>

#include <boost/python.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig();
    Logger log = getLogger();

    // This handler will log to stderr
    log.addHandler(handlers::StreamHandler());

    // This will log to stdout
    log.addHandler(
        handlers::StreamHandler(
            boost::python::import("sys").attr("stdout")));

    log.error(L"Te Occidere Possunt Sed Te Edere Non Possunt Nefas Est.");

    return 0;
}
