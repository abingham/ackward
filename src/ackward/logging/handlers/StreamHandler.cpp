#include <ackward/logging/handlers/StreamHandler.hpp>

#include <ackward/logging/Module.hpp>

namespace ackward { 
namespace logging {
namespace handlers {

StreamHandler::StreamHandler() :
    Handler( module().attr("StreamHandler")() )
{}

StreamHandler::StreamHandler(boost::python::object stream) :
    Handler( module().attr("StreamHandler")(stream) )
{}

}
}
}
