#ifndef INCLUDE_ACKWARD_LOGGING_FILE_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_FILE_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { namespace logging {

class FileHandler : public Handler {
public:
    FileHandler(const std::wstring& filename,
                const std::string& mode="a", 
                const std::string& encoding="", 
                bool delay=false);
};

}}

#endif
