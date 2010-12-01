#ifndef INCLUDE_ACKWARD_LOGGING_LOGGER_HPP
#define INCLUDE_ACKWARD_LOGGING_LOGGER_HPP

#include <ackward/core/Iterable.hpp>
#include <ackward/logging/LoggerBase.hpp>

namespace ackward { namespace logging 
{

class Filter;
class Handler;

class Logger : public LoggerBase {
public:
    Logger(boost::python::object);

    typedef core::Iterable<Filter> Filters;
    typedef core::Iterable<const Filter> ConstFilters;
    Filters filters();
    ConstFilters filters() const;

    typedef core::Iterable<Handler> Handlers;
    typedef core::Iterable<const Handler> ConstHandlers;
    Handlers handlers();
    ConstHandlers handlers() const;

    // /**
    //    This is a factory method which can be overridden in subclasses
    //    to create specialized LogRecord instances.

    //    Changed in version 2.5: func and extra were added.
    // */
    // // Record makeRecord(
    // //     const std::wstring& name, 
    // //     Level lvl, 
    // //     const std::wstring& fn, 
    // //     unsigned int lno, 
    // //     const std::wstring& msg
    // //     // args, exc_info[, func, extra]
    // //     ) const;

    // using core::Object::obj;
};                                                                                                                                                                                                                                                       
}}

#endif
