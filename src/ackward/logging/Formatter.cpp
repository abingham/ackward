#include <ackward/logging/Formatter.hpp>

#include <boost/python.hpp>

#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

Formatter::Formatter() :
    Object(
        module().attr("Formatter")())
{}

Formatter::Formatter(boost::python::object o) :
    Object (o)
{}

std::wstring Formatter::format(const LogRecord& r) const
{
    return extract<std::wstring>(
        obj().attr("format")(r));
}

std::wstring Formatter::formatTime(const LogRecord& r) const
{
    return extract<std::wstring>(
        obj().attr("formatTime")(r));
}

std::wstring Formatter::formatTime(const LogRecord& r, 
                                   const std::wstring& datefmt) const
{
    return extract<std::wstring>(
        obj().attr("formatTime")(r, datefmt));
}

std::wstring Formatter::formatException(boost::python::tuple excInfo) const
{
    return extract<std::wstring>(
        obj().attr("formatException")(excInfo));
}

}}
