#include <ackward/logging/Handler.hpp>

#include <boost/python.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Formatter.hpp>
#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging 
{

Handler::Handler(boost::python::object h) :
    Object (h)
{}

void Handler::setLevel(Level l) 
{
    obj().attr("setLevel")(l);
}

void Handler::setFormatter(Formatter f) 
{
    obj().attr("setFormatter")(f);
}

void Handler::addFilter(Filter f) 
{
    obj().attr("addFilter")(f);
}
    
void Handler::removeFilter(Filter f) 
{
    obj().attr("removeFilter")(f);
}

void Handler::flush() const 
{
    obj().attr("flush")();
}

void Handler::close() 
{
    obj().attr("close")();
}

void Handler::emit(const LogRecord& r) const
{
    obj().attr("emit")(r);
}

StreamHandler::StreamHandler() :
    Handler ( module().attr("StreamHandler")() )
{}

StreamHandler::StreamHandler(boost::python::object stream) :
    Handler ( module().attr("StreamHandler")(stream) )
{}

FileHandler::FileHandler(const std::wstring& filename,
                         const std::string& mode, 
                         const std::string& encoding,
                         bool delay) :
    Handler (
        module().attr("FileHandler")(
            filename,
            mode,
            encoding.empty() 
            ? boost::python::object() 
            : boost::python::str(encoding),
            delay))
{}

WatchedFileHandler::WatchedFileHandler(const std::wstring& filename,
                                       const std::string& mode, 
                                       const std::string& encoding,
                                       bool delay) :
    Handler(
        import("logging.handlers").attr("WatchedFileHandler")(
            filename,
            mode,
            encoding.empty() 
            ? boost::python::object()
            : boost::python::str(encoding),
            delay))
{}

SocketHandler::SocketHandler(const std::wstring& host,
                             unsigned int port) :
    Handler(
        import("logging.handlers").attr("SocketHandler")(
            host, port))
{}

}}
