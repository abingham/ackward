#include <Python.h>

#include <ackward/core/Import.hpp>
#include <ackward/core/Tuple.hpp>
#include <boost/python/extract.hpp>

typedef boost::tuple<int, std::string> Tuple2;

int main(int, char**)
{
    Py_Initialize();

    // This registers a converter between Tuple2 and Python tuples.
    ackward::core::TupleConverter<Tuple2>::registerConverter();

    // Now you can pass Tuple2 instances into Python easily.
    Tuple2 cpp_tuple(4, "yak");
    boost::python::object pickle =
        ackward::core::import("pickle").attr("dumps")(cpp_tuple);

    // And you can extract Python tuples as C++ tuples.
    Tuple2 extracted = 
        boost::python::extract<Tuple2>(
            ackward::core::import("pickle").attr("loads")(pickle));
    
    assert(extracted.get<0>() == 4);
    assert(extracted.get<1>() == "yak");

    // Implicit conversion will fail for unregistered C++ tuple types.
    try {
        boost::python::object obj(
            boost::tuple<int, int>(1,2));
    } catch (const boost::python::error_already_set&) {}

    return 0;
}
