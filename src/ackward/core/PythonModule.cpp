#include <ackward/core/PythonModule.hpp>

#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

using namespace boost::python;

namespace ackward { namespace core {

object module() 
{
    static object mod;
    static bool initialized = false;

    if (!initialized)
    {
        mod = import("logging");
        initialized = true;
    }

    return mod;
}

}}
