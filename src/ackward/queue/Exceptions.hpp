#ifndef INCLUDE_ACKWARD_QUEUE_EXCEPTIONS_HPP
#define INCLUDE_ACKWARD_QUEUE_EXCEPTIONS_HPP

#include <ackward/core/Exceptions.hpp>

namespace ackward { 
namespace queue {

/** 
\\rst

Exception raised when non-blocking ``get()`` (or ``get_nowait()``) is called on a ``Queue`` object which is empty.

See `<http://docs.python.org/library/queue.html#Queue.Empty>`_.

\endrst
 */
class Full : public core::Exception {};

/**
\\rst

Exception raised when non-blocking ``put()`` (or ``put_nowait()``) is called on a ``Queue`` object which is full.

See `<http://docs.python.org/library/queue.html#Queue.Full>`_.

\endrst
 */
class Empty : public core::Exception {};

}
}

#endif
