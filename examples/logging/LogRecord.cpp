#include <Python.h>

#include <ackward/logging/BasicConfig.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp>

#include <boost/python/tuple.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    basicConfig();
    Logger logger = getLogger();

    // Construct a new LogRecord
    LogRecord rec(
        L"my record",
        ERROR(),
        L"some.path",
        100,
        L"my message",
        boost::python::tuple());

    // Let the logger handle the record.
    logger.handle(rec);

    return 0;
}
