#ifndef INCLUDE_ACKWARD_CORE_KWARGS_HPP
#define INCLUDE_ACKWARD_CORE_KWARGS_HPP

#include <boost/python/dict.hpp>

namespace ackward {
namespace core {

/** A class for creating "keyword arguments" used by some ackward
    functions.

    `Kwargs` lets you associated values with parameter names in a
    straightforward way. Functions that accept this type as they
    argument can unpack the keyword arguments and pass them to python
    methods.

    In general, you should use the `kwargs()` method to construct
    these.
 */
class Kwargs
{
public:
    template <typename T>
    Kwargs& operator()(const std::wstring& name,
                       const T& value)
        {
            d_[name] = value;
            return *this;
        }

    const boost::python::dict getDict() const;

private:
    boost::python::dict d_;
};

/** A factory method for constructing and initially populating a
    `Kwargs` object.

    Suppose you have a function `func()` that takes a `Kwargs` object as its argument. Then you would use this `kwargs` like this::

      func(kwargs(L"arg1", "val1")
                 (L"arg2", 3.1415));

    This would generally result in a python call something like this:

      func(arg1="val1", arg2=3.1415)
 */
template <typename T>
Kwargs kwargs(const std::wstring& name,
              const T& value)
{
    Kwargs args;
    return args(name, value);
}

}
}

#endif
