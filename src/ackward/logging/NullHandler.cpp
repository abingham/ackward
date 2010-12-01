#include <ackward/logging/NullHandler.hpp>

namespace ackward { namespace logging {

void NullHandler::emit_(const LogRecord&) {}

}}
