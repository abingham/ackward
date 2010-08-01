#include <ackward/logging/Config.hpp>

#include <ackward/logging/Module.hpp>

#include <boost/python/dict.hpp>

namespace ackward { namespace logging
{

void fileConfig(const std::wstring& filename)
{
    module().attr("fileConfig")(
        filename);
}

void fileConfig(const std::wstring& filename,
                boost::python::dict defaults)
{
    module().attr("fileConfig")(
        filename, defaults);
}

void listen()
{
    module().attr("listen")();
}

void listen(unsigned int port)
{
    module().attr("listen")(port);
}

void stopListening()
{
    module().attr("stopListening")();
}

}}
