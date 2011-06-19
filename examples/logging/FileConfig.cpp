#include <Python.h>

#include <ackward/logging/config/Config.hpp>
#include <boost/python/dict.hpp>

int main(int, char**)
{
    Py_Initialize();

    // You can configure logging with just a file.
    ackward::logging::config::fileConfig(L"example.conf");

    // You can also pass in a defaults dict.
    boost::python::dict defaults;
    defaults["level"] = "error";
    ackward::logging::config::fileConfig(L"example.conf", 
                                         defaults);

    return 0;
}
