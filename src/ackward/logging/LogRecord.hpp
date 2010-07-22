#ifndef INCLUDE_BA_LOG_LOG_RECORD_HPP
#define INCLUDE_BA_LOG_LOG_RECORD_HPP

#include <string>

#include <ackward/logging/Types.hpp>
#include <ackward/core/Object.hpp>

namespace boost { namespace python {

class tuple;

}}

namespace ackward { namespace logging
{

class LogRecord : private core::Object
{
public:
    LogRecord(const std::wstring& name, 
              Level lvl, 
              const std::wstring& pathname, 
              int lineno, 
              const std::wstring& msg, 
              boost::python::tuple args);
    LogRecord(const std::wstring& name, 
              Level lvl, 
              const std::wstring& pathname, 
              int lineno, 
              const std::wstring& msg, 
              boost::python::tuple args, 
              boost::python::tuple exc_info);
    LogRecord(boost::python::object);
    
    std::wstring getMessage() const;
    
    using core::Object::obj;
};

}}

#endif
