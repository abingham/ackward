#ifndef INCLUDE_BA_LOG_DETAIL_PYTHON_CONVERTER_HPP
#define INCLUDE_BA_LOG_DETAIL_PYTHON_CONVERTER_HPP

#include <Python.h>

#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/python.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/detail/PythonConverter.hpp>

/** \rst
    
The family of ``initializePythonConverter`` functions register to- and
from-python conversion methods for ``ackward::core::Object``
subclasses.

\endrst
 */

namespace ackward { 
namespace core {

/** \rst    

    Register a from-python converter for an ``Object`` subclass.

\endrst

    @tparam T The C++ type for which to register a converter; the
      "convert-to" type.

    @param className The name of the Python class for which a
      converter-to-T will be registered.
 */
template <typename T>
void initializeFromPythonConverter(const std::string& className)
{
    detail::from_python_object_<T> temp(className);
}

/** \rst

    Register a to-python converter for an ``Object`` subclass.

    \endrst

    @tparam T The C++ type for which to register a converter; the
      "convert-from" type.
 */
template <typename T>
void initializeToPythonConverter()
{
    boost::python::to_python_converter<
        T,
        detail::to_python_object_<T> >();
}

/** \rst

    Register a to-/from-python converter for the python class
    `className` and C++ type `T`.

    This really just calls ``initializeToPythonConverter<T>()`` and
    ``initializeFromPythonConverter<T>(className)``.

    \endrst

    @tparam T The C++ to convert from and to.
    @param className The name of the Python class to convert from and
      to.
 */
template <typename T>
void initializePythonConverter(const std::string& className)
{
    initializeToPythonConverter<T>();
    initializeFromPythonConverter<T>(className);
}

}
}

#endif
