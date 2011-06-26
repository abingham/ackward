#include <Python.h>

#include <string>

#include <ackward/logging/Formatter.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Types.hpp>
#include <boost/python/tuple.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Formatter f;

    // Use a Formatter to format a LogRecord.
    std::wstring msg = 
        f.format(
            LogRecord(
                L"record name",
                DEBUG(),
                L"some.path",
                100,
                L"A message!",
                boost::python::tuple()));

    return 0;
}
