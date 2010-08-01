#include <ackward/logging/Types.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

Level DEBUG()
{
    static Level l = 
        extract<Level>(
            module().attr("DEBUG"));
    return l;
}

Level INFO()
{
    static Level l = 
        extract<Level>(
            module().attr("INFO"));
    return l;
}

Level WARNING()
{
    static Level l = 
        extract<Level>(
            module().attr("WARNING"));
    return l;
}

Level ERROR()
{
    static Level l = 
        extract<Level>(
            module().attr("ERROR"));
    return l;
}

Level CRITICAL()
{
    static Level l = 
        extract<Level>(
            module().attr("CRITICAL"));
    return l;
}

}}
