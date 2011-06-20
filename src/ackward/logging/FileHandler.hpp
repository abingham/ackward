#ifndef INCLUDE_ACKWARD_LOGGING_FILE_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_FILE_HANDLER_HPP

#include <ackward/logging/Handler.hpp>

namespace ackward { namespace logging {

/** A logging handler that sends logging output to a disk file.
 */
class FileHandler : public Handler {
public:
    /** Constructor

        @param filename The name of the file to save log data into.
        @param mode The mode to use when opening the file.
        @param encoding Encoding to use for the file.
        @param delay If true, then file opening is deferred until the
                     first call to emit()
     */
    FileHandler(
        const std::wstring& filename,
        const std::string& mode="a", 
        const std::string& encoding="", 
        bool delay=false);
};

}}

#endif
