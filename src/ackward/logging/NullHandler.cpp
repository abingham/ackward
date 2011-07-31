#include <Python.h>

#include <ackward/logging/NullHandler.hpp>

#include <iostream>

namespace ackward { 
namespace logging {

void NullHandlerImpl::emit(const LogRecord&) {}

}
}
