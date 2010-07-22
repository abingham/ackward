#include <ackward/logging/Module.hpp>

#include <boost/python/dict.hpp>

#include <ackward/logging/Logger.hpp>
#include <ackward/core/PythonModule.hpp>

using namespace boost::python;

namespace ackward { namespace logging 
{

Logger getLogger()
{
    return Logger(
        core::module().attr("getLogger")());
}

Logger getLogger(const std::wstring& name)
{
    return Logger(
        core::module().attr("getLogger")(name));
}

void basicConfig()
{
    core::module().attr("basicConfig")();
}

void basicConfig(dict kwargs)
{
    core::module().attr("basicConfig")(kwargs);
}

}}
