#ifndef INCLUDE_ACKWARD_LOGGING_NULL_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_NULL_HANDLER_HPP

#include <ackward/logging/UserHandler.hpp>

namespace ackward { namespace logging {

class NullHandler : public Handler_<NullHandler>
{
public:
    static void emit_(const LogRecord&);
};

}}

#endif
