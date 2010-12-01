#include <ackward/logging/FileHandler.hpp>

#include <ackward/logging/Module.hpp>

namespace ackward { namespace logging {

FileHandler::FileHandler(
    const std::wstring& filename,
    const std::string& mode, 
    const std::string& encoding, 
    bool delay) :
    Handler( 
        module().attr("FileHandler")(
            filename,
            mode,
            encoding == "" ? boost::python::object() : boost::python::object(encoding),
            delay))
{}

}}
