#include <ackward/logging/Initialize.hpp>

#include <ackward/core/Initialize.hpp>
#include <ackward/core/PythonConverter.hpp>
#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Formatter.hpp>
#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>

namespace ackward { namespace logging
{

void initialize()
{
    ackward::core::initialize();

    ackward::core::initializePythonConverter<Filter>(
        "logging.Filter");
    ackward::core::initializePythonConverter<Formatter>(
        "logging.Formatter");
    ackward::core::initializePythonConverter<Handler>(
        "logging.Handler");
    ackward::core::initializePythonConverter<Logger>(
        "logging.Logger");
    ackward::core::initializePythonConverter<LogRecord>(
        "logging.LogRecord");
}

}}
