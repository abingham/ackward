#include <ackward/datetime/Module.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

namespace
{

int MINYEAR = 0;
int MAXYEAR = 0;

void initialize()
{
    using namespace boost::python;

    static bool initialized = false;
    if (!initialized)
    {
        object mod = import("datetime");
        MINYEAR = extract<int>(mod.attr("MINYEAR"));
        MAXYEAR = extract<int>(mod.attr("MAXYEAR"));
        initialized = true;
    }
}

}

int ackward::datetime::MINYEAR()
{
    ::initialize();
    return ::MINYEAR;
}

int ackward::datetime::MAXYEAR()
{
    ::initialize();
    return ::MAXYEAR;
}
