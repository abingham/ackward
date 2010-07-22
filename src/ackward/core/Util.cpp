#include <ackward/core/Util.hpp>

#include <boost/python/object.hpp>

#include <ackward/core/Exceptions.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

bool is_none(const object & obj)
{
    static object null_obj;
    return obj.ptr() == null_obj.ptr();
}

boost::python::object
iter(boost::python::object obj)
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

boost::python::object
next(boost::python::object iterator)
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

}}
