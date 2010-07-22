#include <ackward/logging/Config.hpp>

#include <boost/python/dict.hpp>

#include <ackward/core/PythonModule.hpp>

namespace ackward { namespace logging
{

void fileConfig(const std::wstring& filename)
{
    core::module().attr("fileConfig")(
        filename);
}

void fileConfig(const std::wstring& filename,
                boost::python::dict defaults)
{
    core::module().attr("fileConfig")(
        filename, defaults);
}

void listen()
{
    core::module().attr("listen")();
}

void listen(unsigned int port)
{
    core::module().attr("listen")(port);
}

void stopListening()
{
    core::module().attr("stopListening")();
}

}}
