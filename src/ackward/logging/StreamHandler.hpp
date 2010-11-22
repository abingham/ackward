#ifndef INCLUDE_ACKWARD_LOGGING_STREAM_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_STREAM_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { namespace logging {

class StreamHandler : public Handler {
public:
    StreamHandler();
    StreamHandler(boost::python::object stream);
};

}}

#endif
