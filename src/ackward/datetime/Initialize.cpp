#include <ackward/datetime/Initialize.hpp>

#include <ackward/core/PythonConverter.hpp>
#include <ackward/datetime/Date.hpp>
#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/TimeDelta.hpp>
#include <ackward/datetime/TZInfo.hpp>
#include <ackward/time/Initialize.hpp>

void ackward::datetime::initialize()
{
    ackward::time::initialize();

    ackward::core::initializePythonConverter<Date>(
        "datetime.date");
    ackward::core::initializePythonConverter<DateTime>(
        "datetime.datetime");
    ackward::core::initializePythonConverter<TimeDelta>(
        "datetime.timedelta");
    // ackward::core::initializePythonConverter<TZInfo>(
    //    "datetime.tzinfo");
}