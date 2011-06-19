#include <ackward/logging/handlers/SocketHandler.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/logging/handlers/Module.hpp>

namespace ackward { 
namespace logging {
namespace handlers {

SocketHandler::SocketHandler(
    const std::wstring& host,
    unsigned int port) :
    Handler(
        core::getClass("logging.handlers.SocketHandler")(
            host, port))
{}

}
}
}
