#include <ackward/core/Util.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>
#include <boost/scoped_array.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Import.hpp>
#include <ackward/core/PythonVersion.hpp>

using namespace boost::python;

namespace {

std::wstring unicodeToWString(PyObject* s)
{
    assert(PyUnicode_Check(s));

    Py_ssize_t len = PyUnicode_GetSize(s);
    
    boost::scoped_array<wchar_t> buf(new wchar_t[len]);
    
    if (PyUnicode_AsWideChar(
#if ACKWARD_PYTHON_MAJOR_VERSION == 3 && ACKWARD_PYTHON_MINOR_VERSION == 2
            s,
#else
            reinterpret_cast<PyUnicodeObject*>(s),
#endif
            buf.get(), 
            len) == -1)
        return std::wstring();
    
    return std::wstring(buf.get(), buf.get() + len);
}

}

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
#if ACKWARD_PYTHON_MAJOR_VERSION == 2

    if (PyUnicode_Check(s.ptr()))
        return ::unicodeToWString(s.ptr());

    object unicodeObject = object(
        handle<>(
            PyUnicode_FromObject(s.ptr())));

    return ::unicodeToWString(unicodeObject.ptr());

#elif ACKWARD_PYTHON_MAJOR_VERSION == 3

    return ::unicodeToWString(s.ptr());

#endif
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

boost::python::object builtins()
{
    static boost::python::object mod;
    
    if (is_none(mod))
    {
#if ACKWARD_PYTHON_MAJOR_VERSION == 2
        mod = import("__builtin__");
#elif ACKWARD_PYTHON_MAJOR_VERSION == 3
        mod = import("builtins");
#endif
    }

    return mod;
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
