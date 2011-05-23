#include <Python.h>

#include <ackward/core/GetClass.hpp>
#include <boost/python/object.hpp>

int main(int argc, char** argv)
{
    Py_Initialize();

    // Get the class object for ``uuid.UUID`` in the Python standard
    // library.
    boost::python::object classObj =
        ackward::core::getClass("uuid.UUID");

    return 0;
}
