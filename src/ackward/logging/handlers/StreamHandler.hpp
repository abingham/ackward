#ifndef INCLUDE_ACKWARD_LOGGING_STREAM_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_STREAM_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { 
namespace logging {
namespace handlers {

/** \rst
    A wrapper around Python `logging.handlers.StreamHandler <http://docs.python.org/py3k/library/logging.handlers.html#logging.StreamHandler>`_ objects.
    \endrst
 */
class StreamHandler : public Handler {
public:

     /** \rst
        Construct a new instance of a ``StreamHandler`` writing to stderr.
        \endrst
     */
    StreamHandler();

    /** \rst
        Construct a new instance of a ``StreamHandler`` writing to the
        specified stream.
        \endrst

        @param stream The stream with which to construct the StreamHandler.
     */
    StreamHandler(boost::python::object stream);
};

}
}
}

#endif
