#include <ackward/core/Exceptions.hpp>

#include <boost/python.hpp>

#include <ackward/core/ExceptionTranslator.hpp>
#include <ackward/core/Util.hpp>

using namespace boost::python;

namespace ackward { namespace core
{

void translatePythonException()
{
    translatePythonException(getExceptionInfo());
}

void translatePythonException(tuple einfo)
{
    static ExceptionTranslator ex;
    static bool initialized = false;

    if (!initialized)
    {
        ex.add(builtins().attr("AttributeError"),
               &throw_with_python_info<AttributeError>);
        ex.add(builtins().attr("ImportError"),
               &throw_with_python_info<ImportError>);
        ex.add(builtins().attr("IndexError"),
               &throw_with_python_info<IndexError>);
        ex.add(builtins().attr("IOError"),
               &throw_with_python_info<IOError>);
        ex.add(builtins().attr("KeyError"),
               &throw_with_python_info<KeyError>);
        ex.add(builtins().attr("TypeError"),
               &throw_with_python_info<TypeError>);
        ex.add(builtins().attr("ReferenceError"),
               &throw_with_python_info<ReferenceError>);
        ex.add(builtins().attr("ValueError"),
               &throw_with_python_info<ValueError>);
        ex.add(builtins().attr("StopIteration"),
               &throw_with_python_info<StopIteration>);
 
       initialized = true;
    }

    return ex.translate(einfo);    
}

tuple getExceptionInfo()
{
    PyObject *t, *v, *tb;
    PyErr_Fetch(&t, &v, &tb);

    object type;
    if (t)
    {
        handle<> hndl(allow_null(t));
        type = object(hndl);
    }

    object value;
    if (v)
    {
        handle<> hndl(allow_null(v));
        value = object(hndl);
    }

    object traceback;
    if (tb)
    {
        handle<> hndl(allow_null(tb));
        traceback = object(hndl);
    }

    tuple rslt = make_tuple(type, value, traceback);

    return rslt;
}

}}
