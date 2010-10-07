#include <ackward/core/Util.hpp>

#include <boost/python/object.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Import.hpp>

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

bool isInstance(boost::python::object obj,
                const std::string& typeName)
{
    object typeObj = findObject(typeName);

    int rslt = PyObject_IsInstance(
        obj.ptr(), 
        typeObj.ptr());

    switch (rslt)
    {
        case 0:
            return false;
        case 1:
            return true;
        default:
            throw error_already_set();
    }
}

}}
