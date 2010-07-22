#include <ackward/logging/LoggerAdapter.hpp>

#include <boost/python/dict.hpp>

#include <ackward/logging/Logger.hpp>
#include <ackward/core/PythonModule.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

LoggerAdapter::LoggerAdapter(const Logger& logger,
                             boost::python::dict extra) :
    Object (
        core::module().attr("LoggerAdapter")(
            logger, extra) )
{}

void LoggerAdapter::debug(const std::wstring& msg) const
{
    obj().attr("debug")(msg);
}

void LoggerAdapter::info(const std::wstring& msg) const
{
    obj().attr("info")(msg);
}

void LoggerAdapter::warning(const std::wstring& msg) const
{
    obj().attr("warning")(msg);
}

void LoggerAdapter::error(const std::wstring& msg) const
{
    obj().attr("error")(msg);
}

void LoggerAdapter::critical(const std::wstring& msg) const
{
    obj().attr("critical")(msg);
}

void LoggerAdapter::log(Level l, const std::wstring& msg) const
{
    obj().attr("log")(l, msg);
}

void LoggerAdapter::process(const std::wstring& msg,
                            dict kwargs) const
{
    obj().attr("process")(msg, kwargs);
}

}}
