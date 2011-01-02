#include <ackward/datetime/Initialize.hpp>

#include <ackward/core/Initialize.hpp>
#include <ackward/core/PythonConverter.hpp>
#include <ackward/core/Tuple.hpp>
#include <ackward/datetime/Date.hpp>
#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/Time.hpp>
#include <ackward/datetime/TimeDelta.hpp>
#include <ackward/datetime/TZInfo.hpp>
#include <ackward/time/Initialize.hpp>

void ackward::datetime::initialize()
{
    ackward::core::initialize();
    ackward::time::initialize();

    ackward::core::initializePythonConverter<Date>(
        "datetime.date");
    ackward::core::initializePythonConverter<DateTime>(
        "datetime.datetime");
    ackward::core::initializePythonConverter<Time>(
        "datetime.time");
    ackward::core::initializePythonConverter<TimeDelta>(
        "datetime.timedelta");
    // ackward::core::initializePythonConverter<TZInfo>(
    //    "datetime.tzinfo");

    // For Date::isocalendar()
    ackward::core::TupleConverter< boost::tuple<int, int, int> >::registerConverter();
}
