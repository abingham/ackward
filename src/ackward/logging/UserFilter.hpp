#ifndef INCLUDE_ACKWARD_LOGGING_USERFILTER_HPP
#define INCLUDE_ACKWARD_LOGGING_USERFILTER_HPP

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/python/default_call_policies.hpp>
#include <boost/python/make_function.hpp>
#include <boost/python/object.hpp>
#include <boost/shared_ptr.hpp>

#include <ackward/logging/Filter.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward {
namespace logging {

/** \rst

    A ``Filter`` subclass that allows you to define new ``Filter``\ s
    in C++.

    ``UserFilter`` forwards "filter" calls to a user-defined type which
    is passed as a template parameter to ``UserFilter``. To define a
    new ``Filter`` type, first create a class with a method ``int
    filter(const LogRecord&)``::

      struct MyFilterImpl
      {
          int filter(const LogRecord& lr) {
             ...do something...
          }
      }

    Then, create the UserHandler instance::

      typedef UserFilter<MyFilterImpl> MyFilter;

      Logger l = getLogger();
      MyFilter f;
      l.addFilter(f);

    \endrst
 */
template <typename T>
class UserFilter : public Filter
{
public:
    /** The pimpl-body for a UserFilter. */
    struct Body
    {
        Body(boost::python::object);

        // TODO: Does this need a destructor that replaces the target
        // function will something benign when this goes out of scope?

        static int filter(
            UserFilter<T>::Body* b,
            const LogRecord& lr);

        T impl_;

        // Python filter instance.
        boost::python::object filter_;
    };

public:
    UserFilter() :
        Filter( module().attr("Filter")() ),
        body_ (new Body(obj()))
        {}

    T& impl() { return body_->impl_; }
    const T& impl() const { return body_->impl_; }

private:
    boost::shared_ptr<Body> body_;
};

template <typename T>
UserFilter<T>::Body::Body(boost::python::object filter) :
    filter_ (filter)
{
    // Grab a pointer to the static filter() method.
    boost::function<int(Body*, const LogRecord&)> f =
        &UserFilter<T>::Body::filter;

    // These args tell make_function() the signature of filter() after
    // "this" is bound to the first argument.
    typedef boost::mpl::vector<
        int,
        const LogRecord&> FilterArgs;

    // This makes a python callable which calls the static filter
    // method.
    boost::python::object func =
        boost::python::make_function(
            boost::bind(f, this, _1),
            boost::python::default_call_policies(),
            FilterArgs());

    // Assign the python callable we just constructed to the "filter"
    // attribute of the handler.
    filter_.attr("filter") = func;
}

template <typename T>
int UserFilter<T>::Body::filter(
    UserFilter<T>::Body* b,
    const LogRecord& lr)
{
    // Body::emit() just forwards the call to the user-supplied impl.
    return b->impl_.filter(lr);
}

}
}

#endif /* INCLUDE_ACKWARD_LOGGING_USERFILTER_HPP */
