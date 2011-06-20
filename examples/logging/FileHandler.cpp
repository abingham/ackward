#include <Python.h>

#include <ackward/logging/FileHandler.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    ackward::logging::basicConfig();
    ackward::logging::Logger logger = 
        ackward::logging::getLogger();
    ackward::logging::FileHandler handler(
        L"logging_output",
        "w");
    logger.addHandler(handler);

    logger.error(L"Frobnicator misalignment.");

    return 0;
}
