#include <ackward/logging/UserHandler.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/object.hpp>

namespace ackward {
namespace logging {

UserHandler::UserHandler() :
    Handler ( module().attr("Handler")() )
{
    boost::function<void(const UserHandler*, const LogRecord&)> f =
        &UserHandler::emit_;
    
    typedef boost::mpl::vector<
        void,
        const LogRecord&> EmitArgs;
    
    boost::python::object func = 
        boost::python::make_function(
            boost::bind(f, this, _1),
            boost::python::default_call_policies(),
            EmitArgs());
    
    obj().attr("emit") = func;
}

void UserHandler::emit_(const UserHandler* h, const LogRecord& lr)
{
    h->emit_impl(lr);
}

}
}
