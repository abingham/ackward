#ifndef INCLUDE_ACKWARD_LOGGING_SOCKET_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_SOCKET_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { 
namespace logging { 
namespace handlers {

/** \rst
    A wrapper around Python `logging.handlers.SocketHandler <http://docs.python.org/py3k/library/logging.handlers.html#sockethandler>`_ objects.
    \endrst
 */
class SocketHandler : public Handler {
public:
    /** \rst
        Construct a new instance of a ``SocketHandler``.
        \endrst
     */
    SocketHandler(const std::wstring& host,
                  unsigned int port);
};

}
}
}

#endif
