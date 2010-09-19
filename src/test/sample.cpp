#include <iostream>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/python.hpp>

using namespace boost;
using namespace boost::python;

object getMod(const std::string modName)
{
    return import(modName.c_str());
}

object getClass(object mod, const std::string& cls)
{
    return mod.attr(cls.c_str());
}

void handleObject(object obj)
{
    std::cout << PyString_AsString(PyObject_Repr(obj.ptr())) << "\n";
}

int main(int argc, char** argv)
{
    try {
        Py_Initialize();
        
        typedef std::vector<std::string> SV; 
        
        SV splitVec;
        split(splitVec, "datetime.date", is_any_of("."));
        std::string className = splitVec.back();
        splitVec.pop_back();
        std::string modName = join(splitVec, ".");

        if (modName.empty())
            modName = "__builtin__";

        object mod = getMod(modName);
        object cls = getClass(mod, className);
        object date = cls(10,10,10);
        handleObject(date);
        // std::cout << date.ptr() << "\n";
        // object max = d.attr("max");
        // object cls = 
        //     object(
        //         handle<>(
        //             PyObject_GetAttrString(
        //                 mod.ptr(), 
        //                 className.c_str())));
    
        // object max = cls.attr("max");

        
        std::cout << PyString_AsString(PyObject_Repr(date.ptr())) << "\n";
        // std::cout << PyString_AsString(PyObject_Repr(max.ptr())) << "\n";
    }
    catch (...) {
        PyErr_Print();
    }

    return 0;
}
