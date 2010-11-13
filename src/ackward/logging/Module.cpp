#include <ackward/logging/Module.hpp>

#include <boost/python/dict.hpp>
#include <boost/python/import.hpp>

#include <ackward/logging/Logger.hpp>

using namespace boost::python;

namespace ackward { namespace logging 
{

#include <ackward/logging/Module_akw.ipp>

void basicConfig()
{
    module().attr("basicConfig")();
}

void basicConfig(dict kwargs)
{
    module().attr("basicConfig")(kwargs);
}

}}
