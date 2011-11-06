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

/** \rst

    A ``Handler`` subclass that allows you to define new ``Handler``\ s
    in C++.

    ``UserHandler`` forwards "emit" calls to a user-defined type which
    is passed as a template parameter to ``UserHandler``. To define a
    new ``Handler`` type, first create a class with a method ``void
    emit(const LogRecord&)``::

      struct MyHandlerImpl
      {
          void emit(const LogRecord& lr) {
             ...do something...
          }
      }

    Then, create the UserHandler instance::

      typedef UserHandler<MyHandlerImpl> MyHandler;

      Logger l = getLogger();
      MyHandler h;
      l.addHandler(h);

    \endrst
 */
template<typename T>
class UserHandler : public Handler
{
public:

    /** The pimpl-body for a UserHandler.
     */
    struct Body
    {
        Body(boost::python::object);
        ~Body();

        static void emit(
            UserHandler<T>::Body* b,
            const LogRecord& lr);

        static void null(
            const LogRecord& lr) {}

        T impl_;

        // The python handler instance.
        boost::python::object hdlr_;
    };

public:
    UserHandler() :
        Handler( module().attr("Handler")() ),
        body_ ( new Body(obj()) )
        {}

    /** Get the T instance used by this UserHandler. */
    T& impl() { return body_->impl_; }

    /** Get the T instance used by this UserHandler. */
    const T& impl() const { return body_->impl_; }

private:
    boost::shared_ptr<Body> body_;
};

template <typename T>
UserHandler<T>::Body::Body(boost::python::object hdlr) :
    hdlr_ (hdlr)
{
    // Grab a pointer to the static emit() method.
    boost::function<void(Body*, const LogRecord&)> f =
        &UserHandler<T>::Body::emit;

    // These args tell make_function() the signature of emit() after
    // "this" is bound to the first argument.
    typedef boost::mpl::vector<
        void,
        const LogRecord&> EmitArgs;

    // This makes a python callable which calls the static emit
    // method.
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
    // Reset the "emit" function to one which does nothing.

    // Grab a pointer to the static null() method.
    boost::function<void(const LogRecord&)> f =
        &UserHandler<T>::Body::null;

    // These args tell make_function() the signature of emit() after
    // "this" is bound to the first argument.
    typedef boost::mpl::vector<
        void,
        const LogRecord&> EmitArgs;

    // This makes a python callable which calls the static null
    // method.
    boost::python::object func =
        boost::python::make_function(
            boost::bind(f, _1),
            boost::python::default_call_policies(),
            EmitArgs());

    hdlr_.attr("emit") = func;

    hdlr_.attr("close")();
}

template <typename T>
void UserHandler<T>::Body::emit(
    UserHandler<T>::Body* b,
    const LogRecord& lr)
{
    // Body::emit() just forwards the call to the user-supplied impl.
    b->impl_.emit(lr);
}

}
}

#endif
