#include <Python.h>

#include <boost/python.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Initialize.hpp>
#include <ackward/core/Object.hpp>
#include <ackward/core/PythonConverter.hpp>

// A hypothetical C++ wrapper around Python's ``fraction.Fraction``
// class.
class Fraction : private ackward::core::Object
{
public:
    Fraction(boost::python::object obj) :
        ackward::core::Object(obj)
        {}
    // ... implement Fraction API in terms of ``obj()`` ...

    using ackward::core::Object::obj;
};

int main(int, char**)
{
    Py_Initialize();

    ackward::core::initialize();
    
    // Use the ``initialize[To|From]PythonConverter functions to
    // register to-/from-python conversions based on the Object
    // protocol.

    // You can register to- and from-converters in one call. (NOTE:
    // boost.python will complain if you actually register conversions
    // twice.)
    ackward::core::initializePythonConverter<Fraction>(
        "fractions.Fraction");

    // Or you can register them independently.
    ackward::core::initializeFromPythonConverter<Fraction>(
        "fractions.Fraction");
    ackward::core::initializeToPythonConverter<Fraction>();

    // Now ``Fraction`` can be extracted from Python routines.
    Fraction f = 
        boost::python::extract<Fraction>(
            ackward::core::getClass("fractions.Fraction")(3,4));

    // And ``Fraction`` can be passed into Python routines.
    ackward::core::import("pickle").attr("dumps")(f);

    return 0;
}
