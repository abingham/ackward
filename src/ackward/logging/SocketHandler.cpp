#include <ackward/logging/SocketHandler.hpp>

#include <ackward/logging/Module.hpp>

namespace ackward { namespace logging {

SocketHandler::SocketHandler(
    const std::wstring& host,
    unsigned int port) :
    Handler(
        module().attr("SocketHandler")(
            host, port))
{}

}}
