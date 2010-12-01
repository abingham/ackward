#ifndef INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP

#include <boost/python/make_function.hpp>
#include <boost/python/object.hpp>

#include <ackward/logging/Handler.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward { namespace logging {

template <typename Impl>
class Handler_ : public Handler
{
public:
    Handler_() :
        Handler ( module().attr("Handler")() )
        {
            boost::python::object func = 
                boost::python::make_function(
                    Handler_<Impl>::emit_impl);
            obj().attr("emit") = func;
        }
    
private:
    static void emit_impl(boost::python::object o)
        {
            LogRecord lr(o);
            Impl::emit_(lr);
        }
};

}}

#endif
