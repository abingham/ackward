#ifndef INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP

#include <boost/python/object_fwd.hpp>

#include <ackward/logging/Handler.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward { 
namespace logging {

class UserHandler : public Handler
{
public:
    UserHandler();

private:
    static void emit_(UserHandler* h, const LogRecord& rec);
    
    virtual void emit_impl(const LogRecord& lr) = 0;
};

}
}

#endif
