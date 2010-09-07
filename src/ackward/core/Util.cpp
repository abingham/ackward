#include <ackward/core/Util.hpp>

#include <string>
#include <vector>

#include <boost/python/import.hpp>
#include <boost/python/object.hpp>
#include <boost/tokenizer.hpp>

#include <ackward/core/Exceptions.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

bool is_none(const object & obj)
{
    static object null_obj;
    return obj.ptr() == null_obj.ptr();
}

object
iter(object obj)
{
    using namespace boost::python;

    try
    {
        object itr =
            object(
                handle<>(
                    PyObject_GetIter(obj.ptr())));
        return itr;
    } TRANSLATE_PYTHON_EXCEPTION();
}

object
next(object iterator)
{
    using namespace boost::python;

    PyObject* rval_ptr =
        PyIter_Next(iterator.ptr());

    translatePythonException();

    if (!rval_ptr)
        throw StopIteration();

    return object(handle<>(rval_ptr));
}

std::wstring repr(object obj)
{
    object r = object(handle<>(PyObject_Repr(obj.ptr())));
    std::string sz(PyString_AsString(r.ptr()));
    return std::wstring(sz.begin(), sz.end());
}

/*
using namespace boost::python;

    if (begin == end)
        return false;

    // Assume that a length-1 range implies the __builtins__ module
    else if (distance(begin, end) == 1)
    {
        return excx.add(import("__builtin__").attr(*begin), t);
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
*/

object
import(const std::string& name)
{
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep(".");
    tokenizer tokens(name, sep);

    try {

        if (tokens.begin() == tokens.end())
            return import("__builtin__");
        
        std::vector<std::string> toks(tokens.begin(),
                                      tokens.end());
        std::vector<std::string>::const_iterator itr = toks.begin();

        object mod = boost::python::import(itr->c_str());
        ++itr;
        for (; itr != toks.end(); ++itr)
            mod = mod.attr(itr->c_str());

        return mod;

    } catch (const error_already_set&) {
        translatePythonException();
        throw;
    }
}

object
findObject(const std::string& module,
           const std::string& name)
{
    object mod = import(module);
    
    try {
        return mod.attr(name.c_str());
    } catch (const boost::python::error_already_set&) {
        translatePythonException();
        throw;
    }
}

}}
