#ifndef INCLUDE_ACKWARD_CORE_IMPORT_HPP
#define INCLUDE_ACKWARD_CORE_IMPORT_HPP

#include <Python.h>

#include <string>

#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/Util.hpp>

namespace ackward { namespace core
{

/** Import a fully qualified module e.g. "a.b.c.d".
    
    If `module` is empty, this returns the builtins module.

    @param module The name of the module
    @return The module object
    @throws ImportError if the module can't be imported
 */
boost::python::object
import(const std::string& module);

template <typename Itr>
boost::python::object
import(Itr begin, Itr end)
{
    std::ostringstream oss;

    if (begin != end)
    {
        Itr itr = begin;
        oss << *itr;
        ++itr;
        
        for (; itr != end; ++itr)
            oss << "." << *itr;
    }

    return import(oss.str());
}

/** Find a module-level object
    
    If `module` is empty, this looks for an object in the 
    builtins module.

    @param module The name of the module containing the object
    @param name The name of the object in the module
    @return The module-level object
    @throws ImportError If the module can't be imported
    @throws AttributeError If `name` doesn't resolve to an object in the module 
 */
boost::python::object
findObject(const std::string& module,
           const std::string& name);

boost::python::object
findObject(const std::string& fullName);

}}

#endif
