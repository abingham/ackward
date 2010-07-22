#include <ackward/logging/Types.hpp>

#include <boost/python/extract.hpp>

#include <ackward/core/PythonModule.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

Level DEBUG()
{
    static Level l = 
        extract<Level>(
            core::module().attr("DEBUG"));
    return l;
}

Level INFO()
{
    static Level l = 
        extract<Level>(
            core::module().attr("INFO"));
    return l;
}

Level WARNING()
{
    static Level l = 
        extract<Level>(
            core::module().attr("WARNING"));
    return l;
}

Level ERROR()
{
    static Level l = 
        extract<Level>(
            core::module().attr("ERROR"));
    return l;
}

Level CRITICAL()
{
    static Level l = 
        extract<Level>(
            core::module().attr("CRITICAL"));
    return l;
}

}}
