#include <Python.h>

#include <string>

#include <ackward/core/Tuple.hpp>
#include <boost/python/extract.hpp>

typedef boost::tuple<int, float, std::string> Tuple3;

int main(int, char**)
{
    Py_Initialize();

    // The convertTuple methods can convert explicitly between
    // Python tuples and boost::tuples.

    { // Conversion from python to C++
        boost::python::tuple python_tuple = 
            boost::python::make_tuple(1, float(2.3), "test");
        
        Tuple3 cpp_tuple = 
            ackward::core::convertTuple<Tuple3>(python_tuple);
        assert(cpp_tuple.get<0>() == 1);
        assert(cpp_tuple.get<1>() == float(2.3));
        assert(cpp_tuple.get<2>() == "test");
    }

    { // Conversion from C++ to python
        Tuple3 cpp_tuple = 
            boost::make_tuple(42, 12.34, "llama");
        
        boost::python::tuple python_tuple =
            ackward::core::convertTuple(cpp_tuple);

        assert(boost::python::extract<int>(python_tuple[0]) == 42);
        assert(boost::python::extract<float>(python_tuple[1]) == float(12.34));
        assert(boost::python::extract<std::string>(python_tuple[2])() == "llama");
    }

    return 0;
}
