#include <ackward/logging/Module.hpp>

#include <boost/python/dict.hpp>
#include <boost/python/import.hpp>

#include <ackward/logging/Logger.hpp>

using namespace boost::python;

namespace ackward { namespace logging 
{

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

Logger getLogger()
{
    return Logger(
        module().attr("getLogger")());
}

Logger getLogger(const std::wstring& name)
{
    return Logger(
        module().attr("getLogger")(name));
}

void basicConfig()
{
    module().attr("basicConfig")();
}

void basicConfig(dict kwargs)
{
    module().attr("basicConfig")(kwargs);
}

}}
