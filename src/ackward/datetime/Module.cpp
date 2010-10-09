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

unsigned int MINYEAR()
{
    return extract<unsigned int>(
        module().attr("MINYEAR"));
}

unsigned int MAXYEAR()
{
    return extract<unsigned int>(
        module().attr("MAXYEAR"));
}

}}
