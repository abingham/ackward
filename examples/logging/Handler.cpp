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

    basicConfig();

    // Set the level of each Handler in the top-level
    // logger to "info".
    Logger l = getLogger();
    Logger::Handlers h = l.handlers();
    std::size_t x = h.size();
    // for (Logger::Handlers::iterator hli = h.begin();
    //      hli != h.end();
    //      ++hli)
    // {
    //     Handler hndlr = *hli;
    //     hndlr.setLevel(INFO());
    // }
 
    BOOST_FOREACH(Handler hnd, getLogger().handlers())
    {
        hnd.setLevel(INFO());
    }

    return 0;
}
