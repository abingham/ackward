#include <Python.h>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

#include <boost/foreach.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    ackward::logging::initialize();

    // Copy filters from one logger to another.
    Logger l1 = getLogger(L"my_logger");
    Logger l2 = getLogger(L"my_other_logger");
    BOOST_FOREACH(Filter f, l1.filters())
    {
        l2.addFilter(f);
    }

    return 0;
}
