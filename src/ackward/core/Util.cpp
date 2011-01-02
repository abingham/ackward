#include <ackward/core/Util.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>
#include <boost/scoped_array.hpp>

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

std::wstring strToWString(boost::python::str s)
{
    Py_ssize_t len = PyUnicode_GetSize(s.ptr());
    
    boost::scoped_array<wchar_t> buf(new wchar_t[len]);
    
    if (PyUnicode_AsWideChar(reinterpret_cast<PyUnicodeObject*>(s.ptr()), buf.get(), len) == -1)
        return std::wstring();
    
    return std::wstring(buf.get(), buf.get() + len);
}

std::wstring repr(object obj)
{
    boost::python::str r = extract<boost::python::str>(
        object(handle<>(PyObject_Repr(obj.ptr()))));

    return strToWString(r);
}

std::wstring str(object obj)
{
    boost::python::str r = extract<boost::python::str>(
        object(handle<>(PyObject_Str(obj.ptr()))));
    return strToWString(r);
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
