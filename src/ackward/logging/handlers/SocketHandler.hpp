#ifndef INCLUDE_ACKWARD_LOGGING_SOCKET_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_SOCKET_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { 
namespace logging { 
namespace handlers {

class SocketHandler : public Handler {
public:
    SocketHandler(const std::wstring& host,
                  unsigned int port);
};

}
}
}

#endif
