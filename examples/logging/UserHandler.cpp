#include <Python.h>

#include <iostream>

#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/UserHandler.hpp>

using namespace ackward::logging;

struct ExampleHandlerImpl
{
    void emit(const LogRecord& r) {
        std::wcout << L"[ExampleHandler] "
                   << r.getMessage()
                   << std::endl;
    }
};

typedef UserHandler<ExampleHandlerImpl> ExampleHandler;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    Logger l = getLogger(L"my_logger");
    ExampleHandler h;
    l.addHandler(h);

    l.error(L"They've shut down the main reactor. We'll be destroyed for sure.");

    return 0;
}
