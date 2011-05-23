#include <Python.h>

#include <vector>

#include <ackward/core/Import.hpp>

int main(int argc, char** argv)
{
    Py_Initialize();

    // You can import by fully-qualified name.
    ackward::core::import("os.path");

    // Or via a collection
    std::vector<std::string> modname;
    modname.push_back("os");
    modname.push_back("path");
    ackward::core::import(modname.begin(), modname.end());

    return 0;
}
