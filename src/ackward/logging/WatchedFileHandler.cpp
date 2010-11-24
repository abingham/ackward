#include <ackward/logging/WatchedFileHandler.hpp>

#include <ackward/logging/Module.hpp>

namespace ackward { namespace logging {

WatchedFileHandler::WatchedFileHandler(
    const std::wstring& filename,
    const std::string& mode, 
    const std::string& encoding, 
    bool delay) :
    Handler( 
        module().attr("WatchedFileHandler")(
            filename,
            mode,
            encoding,
            delay))
{}

}}
