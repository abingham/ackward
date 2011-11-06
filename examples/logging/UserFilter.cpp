#include <Python.h>

#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/UserFilter.hpp>

using namespace ackward::logging;

struct ExampleFilterImpl
{
    int filter(const LogRecord& r) {
        // only emit Records from even levels.
        if (r.levelno % 2)
            return 1;
        else
            return 0;
    }
};

typedef UserFilter<ExampleFilterImpl> ExampleFilter;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    Logger l = getLogger(L"my_logger");
    ExampleFilter f;
    l.addFilter(f);

    l.error(L"They've shut down the main reactor. We'll be destroyed for sure.");

    return 0;
}
