#ifndef INCLUDE_ACKWARD_LOGGING_NULL_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_NULL_HANDLER_HPP

#include <ackward/logging/UserHandler.hpp>

namespace ackward { namespace logging {

/** \rst
    A Handler instance that does nothing with the ``LogRecord``\ s passed to ``emit()``.

    This is primarily just an example of how to use ``Handler_<T>``.
    \endrst */
class NullHandler : public UserHandler
{
private:
    void emit_impl(const LogRecord&) const;
};

}}

#endif
