#ifndef INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP
#define INCLUDE_ACKWARD_LOGGING_USER_HANDLER_HPP

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/object.hpp>
#include <boost/shared_ptr.hpp>

#include <ackward/logging/Handler.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward { 
namespace logging {

template<typename T>
class UserHandler : public Handler
{
public:
    struct Body
    {
        Body(boost::python::object);
        ~Body();

        static void emit(
            UserHandler<T>::Body* b, 
            const LogRecord& lr);

        T impl_;
        boost::python::object hdlr_;
    };

public:
    UserHandler() :
        Handler( module().attr("Handler")() ),
        body_ ( new Body(obj()) )
        {}

    T& impl() { return body_->impl_; }
    const T& impl() const { return body_->impl_; }

private:
    boost::shared_ptr<Body> body_;
};

template <typename T>
UserHandler<T>::Body::Body(boost::python::object hdlr) :
    hdlr_ (hdlr)
{
    boost::function<void(Body*, const LogRecord&)> f =
        &UserHandler<T>::Body::emit;
    
    typedef boost::mpl::vector<
        void,
        const LogRecord&> EmitArgs;
    
    boost::python::object func = 
        boost::python::make_function(
            boost::bind(f, this, _1),
            boost::python::default_call_policies(),
            EmitArgs());
    
    hdlr_.attr("emit") = func;
}

template <typename T>
UserHandler<T>::Body::~Body()
{
    hdlr_.attr("close")();
}

template <typename T>
void UserHandler<T>::Body::emit(
    UserHandler<T>::Body* b, 
    const LogRecord& lr)
{
    b->impl_.emit(lr);
}

}
}

#endif
