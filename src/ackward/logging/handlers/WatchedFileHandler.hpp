#ifndef INCLUDE_ACKWARD_LOGGING_WATCHED_FILE_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_WATCHED_FILE_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { 
namespace logging { 
namespace handlers {

/** \rst
    A wrapper around Python `logging.handlers.WatchedFileHandler <http://docs.python.org/py3k/library/logging.handlers.html#watchedfilehandler>`_ objects.
    \endrst
 */
class WatchedFileHandler : public Handler {
public:
    /** \rst

        Construct a new instance of a ``WatchedFileHandler`` writing to
        ``filename`` with the specified mode and encoding.

        If ``delay`` is true, then the file is not opened until the
        first call to ``emit()``.

        \endrst
    */
    WatchedFileHandler(
        const std::wstring& filename,
        const std::string& mode="a", 
        const std::string& encoding="", 
        bool delay=false);
};

}
}
}

#endif
