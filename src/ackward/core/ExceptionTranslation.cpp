#include <ackward/core/ExceptionTranslation.hpp>

using namespace boost::python;

namespace ackward {
namespace core {

ExceptionTranslator& exceptionTranslator()
{
    static ExceptionTranslator ex;
    return ex;
}

void translatePythonException()
{
    translatePythonException(getExceptionInfo());
}

void translatePythonException(tuple einfo)
{
    return exceptionTranslator().translate(einfo);    
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

}
}
