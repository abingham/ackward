#ifndef INCLUDE_ACKWARD_LOGGING_LOGGER_HPP
#define INCLUDE_ACKWARD_LOGGING_LOGGER_HPP

#include <ackward/core/Iterable.hpp>
#include <ackward/logging/LoggerBase.hpp>

namespace ackward { 
namespace logging {

class Filter;
class Handler;

/**
\rst

A wrapper around Python `logging.Logger
<http://docs.python.org/py3k/library/logging.html#logger-objects>`_
objects. 

\endrst
*/
class Logger : private LoggerBase {
public:
    /** Construct a Logger around an existing Python ``Logger``
        instance.
     */
    Logger(boost::python::object);

    /** An iterable of Filter objects on a Logger.
     */
    typedef core::Iterable<Filter> Filters;

    /** An iterable of const Filter objects on a Logger.
     */
    typedef core::Iterable<const Filter> ConstFilters;

    /** Get an iterable over the Filters on this Logger.
     */
    Filters filters();

    /** Get an iterable over the const Filters on this Logger.
     */
    ConstFilters filters() const;

    /** An iterable of Handler objects on a Logger.
     */
    typedef core::Iterable<Handler> Handlers;

    /** An iterable of const Handle objects on a Logger.
     */
    typedef core::Iterable<const Handler> ConstHandlers;

    /** Get an iterable over the Handlers on a Logger.
     */
    Handlers handlers();

    /** Get an iterable over the const Handlers on a Logger.
     */
    ConstHandlers handlers() const;

    // Pull in stuff from LoggerBase
    using LoggerBase::propagate;
    using LoggerBase::setLevel;
    using LoggerBase::isEnabledFor;
    using LoggerBase::getEffectiveLevel;
    using LoggerBase::log;
    using LoggerBase::addFilter;
    using LoggerBase::removeFilter;
    using LoggerBase::filter;
    using LoggerBase::addHandler;
    using LoggerBase::removeHandler;
    using LoggerBase::handle;
    using LoggerBase::debug;
    using LoggerBase::info;
    using LoggerBase::warning;
    using LoggerBase::error;
    using LoggerBase::critical;
    using LoggerBase::exception;
    using LoggerBase::obj;
    
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

}
}

#endif
