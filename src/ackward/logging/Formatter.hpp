#ifndef INCLUDE_BA_LOG_FORMATTER_HPP
#define INCLUDE_BA_LOG_FORMATTER_HPP

#include <string>

#include <ackward/core/Object.hpp>

namespace boost { namespace python {

class tuple;

}}

namespace ackward { namespace logging
{

class LogRecord;

class Formatter : private core::Object
{
public:
    Formatter();
    Formatter(boost::python::object);

    std::wstring format(const LogRecord&) const;
    std::wstring formatTime(const LogRecord&) const;
    std::wstring formatTime(const LogRecord&, const std::wstring& datefmt) const;
    std::wstring formatException(boost::python::tuple) const;

    using core::Object::obj;
};

}}

#endif
