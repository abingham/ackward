#include <ackward/logging/Logger.hpp>

#include <boost/python/extract.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/Handler.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging 
{

Logger::Logger(object l) :
    Object (l)
{}

bool Logger::propagate() const
{
    return extract<bool>(
        obj().attr("propagate"));
}

void Logger::propagate(bool p)
{
    obj().attr("propagate") = int(p);
}

void Logger::setLevel(Level l)
{
    obj().attr("setLevel")(l);
}

bool Logger::isEnabledFor(Level l) const
{
    return extract<bool>(
        obj().attr("isEnabledFor")(l));
}

Level Logger::getEffectiveLevel() const
{
    return extract<Level>(
        obj().attr("getEffectiveLevel")());
}

void Logger::debug(const std::wstring& msg) const
{
    obj().attr("debug")(msg);
}

void Logger::info(const std::wstring& msg) const
{
    obj().attr("info")(msg);
}

void Logger::warning(const std::wstring& msg) const
{
    obj().attr("warning")(msg);
}

void Logger::error(const std::wstring& msg) const
{
    obj().attr("error")(msg);
}

void Logger::critical(const std::wstring& msg) const
{
    obj().attr("critical")(msg);
}

// void Logger::exception(const std::wstring& msg) const
// {
//     obj().attr("exception")(msg);
// }

void Logger::log(Level l, const std::wstring& msg) const
{
    obj().attr("log")(l, msg);
}

void Logger::addFilter(Filter f)
{
    obj().attr("addFilter")(f);
}

void Logger::removeFilter(Filter f)
{
    obj().attr("removeFilter")(f);
}

Logger::Filters Logger::filters()
{
    return Filters(obj().attr("filters"));
}

Logger::ConstFilters Logger::filters() const
{
    return ConstFilters(obj().attr("filters"));
}

bool Logger::filter(LogRecord r) const
{
    return extract<bool>(
        obj().attr("filter")(r));
}

void Logger::addHandler(const Handler& h)
{
    obj().attr("addHandler")(h);
}

void Logger::removeHandler(const Handler& h)
{
    obj().attr("removeHandler")(h);
}

Logger::Handlers Logger::handlers()
{
    return Handlers(obj().attr("handlers"));
}

Logger::ConstHandlers Logger::handlers() const
{
    return ConstHandlers(obj().attr("handlers"));
}

void Logger::handle(LogRecord r) const
{
    obj().attr("handle")(r);
}

}}
