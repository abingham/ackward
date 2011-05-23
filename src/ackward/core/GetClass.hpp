#ifndef INCLUDE_BA_LOG_DETAIL_GET_CLASS_HPP
#define INCLUDE_BA_LOG_DETAIL_GET_CLASS_HPP

#include <Python.h>

#include <string>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace core
{

/** \rst
    Get the class object for a class.

    The ``name`` parameter should be the full name of the class, with
    packages and everything. For example "uuid.UUID" or "foo.bar.Baz".

    If ``name`` is just a class name (e.g. "ClassName", no leading
    package specification), then it is assumed to be in the "builtins"
    module.
    \endrst

    @param name The full name of the class object to get.
 */
boost::python::object 
getClass(const std::string& name);

}}

#endif
