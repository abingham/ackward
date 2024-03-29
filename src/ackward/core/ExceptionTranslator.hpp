#ifndef INCLUDE_BA_LOG_DETAIL_EXCEPTION_TRANSLATOR_HPP
#define INCLUDE_BA_LOG_DETAIL_EXCEPTION_TRANSLATOR_HPP

/** \file

    This defines the central class used for exception-translation in ackward.

    This should not be confused with `ExceptionTranslation.h/cpp`
    which defined the methods and macros that are actually used to
    *perform* the translation. Those methods are implemented in terms
    of the class defined here. Sorry for the confusion...
 */

#include <Python.h>

#include <utility>
#include <vector>

#include <boost/function.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>
#include <boost/python/tuple.hpp>

#include <ackward/core/Util.hpp>

namespace ackward { 
namespace core {

/** A registry of python-to-c++ exception translations.
 */
class ExceptionTranslator
{
public:

    void translate(boost::python::tuple excInfo);

    typedef boost::function<void(boost::python::object,
                                 boost::python::object,
                                 boost::python::object)>
    Thrower;

    bool add(boost::python::object excType,
             Thrower thrower);

    bool remove(boost::python::object excType);

private:
    typedef std::pair<boost::python::object, Thrower> Mapping;
    typedef std::vector<Mapping> ThrowMap;
    ThrowMap map_;
};

template <typename Itr>
bool add(ExceptionTranslator& excx,
         Itr begin,
         Itr end,
         ExceptionTranslator::Thrower t)
{
    using namespace boost::python;

    if (begin == end)
        return false;

    // Assume that a length-1 range implies the __builtins__ module
    else if (distance(begin, end) == 1)
    {
        return excx.add(builtins().attr(*begin), t);
    }
    else
    {
        Itr itr = begin;
        object obj(import(*itr));
        ++itr;
        for (; itr != end; ++itr)
        {
            obj = obj.attr(*itr);
        }

        return excx.add(obj, t);
    }
}

template <class Container>
bool add(ExceptionTranslator& excx,
         const Container& c,
         ExceptionTranslator::Thrower t)
{
    return add(excx, c.begin(), c.end(), t);
}

template <typename Exc>
void throw_(boost::python::object /* type */,
            boost::python::object /* value */,
            boost::python::object /* traceback */)
{
    throw Exc();
}

typedef boost::error_info<struct tag_exc_info, boost::python::tuple> exc_info;

template <typename Exc>
void throw_with_python_info(boost::python::object type,
                            boost::python::object value,
                            boost::python::object traceback)
{
    Exc e;

    boost::python::tuple t =
        boost::python::make_tuple(type, value, traceback);
    e << exc_info(t);

    throw e;
}

}
}

#endif
