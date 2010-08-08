#include <ackward/datetime/Module.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

using namespace boost::python;

namespace ackward { namespace datetime
{

object module()
{
    static object mod;
    static bool initialized = false;

    if (!initialized)
    {
        mod = import("datetime");
        initialized = true;
    }

    return mod;
}

int MINYEAR()
{
    return extract<int>(
        module().attr("MINYEAR"));
}

int MAXYEAR()
{
    return extract<int>(
        module().attr("MAXYEAR"));
}

}}
