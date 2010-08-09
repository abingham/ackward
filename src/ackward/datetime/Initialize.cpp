#include <ackward/datetime/Initialize.hpp>

#include <ackward/core/PythonConverter.hpp>
#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/TimeDelta.hpp>
#include <ackward/datetime/TZInfo.hpp>

void ackward::datetime::initialize()
{
    ackward::core::initializePythonConverter<DateTime>(
        "datetime.datetime");
    ackward::core::initializePythonConverter<TimeDelta>(
        "datetime.timedelta");
    ackward::core::initializePythonConverter<TZInfo>(
        "datetime.tzinfo");
}
