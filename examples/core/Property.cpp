#include <Python.h>

#include <iostream>
#include <string>

#include <ackward/core/Property.hpp>

int main(int, char**)
{
    Py_Initialize();

    // Construct a Property which accesses ``sys.version``. 
    ackward::core::Property<std::string> sys_version(
        ackward::core::import("sys"),
        "version");

    std::cout << sys_version << std::endl;

    sys_version = "4!";
    std::cout << sys_version << std::endl;

    return 0;
}
