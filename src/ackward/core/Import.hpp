#ifndef INCLUDE_ACKWARD_CORE_IMPORT_HPP
#define INCLUDE_ACKWARD_CORE_IMPORT_HPP

#include <Python.h>

#include <string>

#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/Exceptions.hpp>
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
    namespace bp=boost::python;

    try {
        
        if (begin == end)
            return builtins();
        
        Itr itr = begin;

        std::string name(*itr);
        bp::object mod = bp::import(name.c_str());
        ++itr;
        for (; itr != end; ++itr)
        {
            name = *itr;
            mod = mod.attr(name.c_str());
        }

        return mod;

    } catch (const bp::error_already_set&) {
        try {
            translatePythonException();
        } catch (const AttributeError&) {
            throw ImportError();
        }
        throw;
    }
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
