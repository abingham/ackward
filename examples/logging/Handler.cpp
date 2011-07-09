#include <Python.h>

#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp>
#include <boost/foreach.hpp>

using namespace ackward::logging;

int main(int, char**)
{
    Py_Initialize();
    initialize();

    // Do basic configuration of the logging system.
    basicConfig();

    // Set the level of each Handler in the top-level
    // logger to "info".
    BOOST_FOREACH(Handler hnd, getLogger().handlers())
    {
        hnd.setLevel(INFO());
    }

    return 0;
}
