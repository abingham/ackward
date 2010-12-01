#include <ackward/logging/SocketHandler.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward { namespace logging {

SocketHandler::SocketHandler(
    const std::wstring& host,
    unsigned int port) :
    Handler(
        core::getClass("logging.handlers.SocketHandler")(
            host, port))
{}

}}
