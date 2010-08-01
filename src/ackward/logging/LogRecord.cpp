#include <ackward/logging/LogRecord.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>

#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

LogRecord::LogRecord(const std::wstring& name, 
                     Level lvl, 
                     const std::wstring& pathname, 
                     int lineno, 
                     const std::wstring& msg, 
                     boost::python::tuple args) :
    Object(
        module().attr("LogRecord")(
            name, lvl, pathname, lineno, msg, args,
            make_tuple(object(), object(), object())))
{}

LogRecord::LogRecord(const std::wstring& name, 
                     Level lvl, 
                     const std::wstring& pathname, 
                     int lineno, 
                     const std::wstring& msg, 
                     boost::python::tuple args, 
                     boost::python::tuple exc_info) :
    Object(
        module().attr("LogRecord")(
            name, lvl, pathname, lineno, msg, args, exc_info))
{}

LogRecord::LogRecord(object lr) :
    Object (lr)
{}

std::wstring LogRecord::getMessage() const 
{
    return extract<std::wstring>(
        obj().attr("getMessage")());
}

}}
