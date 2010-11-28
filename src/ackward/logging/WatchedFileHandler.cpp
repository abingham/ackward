#include <ackward/logging/WatchedFileHandler.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging {

WatchedFileHandler::WatchedFileHandler(
    const std::wstring& filename,
    const std::string& mode, 
    const std::string& encoding, 
    bool delay) :
    Handler( 
        core::getClass("logging.handlers.WatchedFileHandler")(
            filename,
            mode,
            encoding == "" ? object() : object(encoding),
            delay))
{}

}}
