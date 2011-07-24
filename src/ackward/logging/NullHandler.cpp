#include <ackward/logging/NullHandler.hpp>

#include <iostream>

namespace ackward { 
namespace logging {

void NullHandler::emit_impl(const LogRecord&)  const {}

}
}
