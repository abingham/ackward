#ifndef BA_LOGGING_LOGGER_ADAPTER_HPP
#define BA_LOGGING_LOGGER_ADAPTER_HPP

#include <string>

#include <ackward/logging/Types.hpp>
#include <ackward/core/Object.hpp>

namespace boost { namespace python {

class dict;

}}

namespace ackward { namespace logging
{

class Logger;

class LoggerAdapter : private core::Object
{
public:
    LoggerAdapter(const Logger& logger,
                  boost::python::dict);

    void debug(const std::wstring& msg) const;
    void info(const std::wstring& msg) const;
    void warning(const std::wstring& msg) const;
    void error(const std::wstring& msg) const;
    void critical(const std::wstring& msg) const;
    void log(Level l, const std::wstring& msg) const;
    void process(const std::wstring& msg,
                 boost::python::dict kwargs) const;
};

}}

#endif
