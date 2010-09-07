#ifndef INCLUDE_BA_LOG_DETAIL_UTIL_HPP
#define INCLUDE_BA_LOG_DETAIL_UTIL_HPP

#include <string>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace core
{

bool is_none(const boost::python::object&);

boost::python::object 
iter(boost::python::object);

boost::python::object
next(boost::python::object iterator);

std::wstring repr(boost::python::object);

/** Import a fully qualified module e.g. "a.b.c.d".
    
    If `module` is empty, this returns the __builtin__ module.

    @param module The name of the module
    @return The module object
    @throws ImportError if the module can't be imported
 */
boost::python::object
import(const std::string& module);

/** Find a module-level object
    
    If `module` is empty, this looks for an object in the 
    __builtin__ module.

    @param module The name of the module containing the object
    @param name The name of the object in the module
    @return The module-level object
    @throws ImportError If the module can't be imported
    @throws AttributeError If `name` doesn't resolve to an object in the module 
 */
boost::python::object
findObject(const std::string& module,
           const std::string& name);

}}

#endif
