#ifndef INCLUDE_ACKWARD_LOGGING_WATCHED_FILE_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_WATCHED_FILE_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { 
namespace logging { 
namespace handlers {

class WatchedFileHandler : public Handler {
public:
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
