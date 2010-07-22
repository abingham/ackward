#include <ackward/logging/Filter.hpp>

#include <boost/python.hpp>

#include <ackward/core/PythonModule.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

Filter::Filter() :
    Object (
        core::module().attr("Filter")())
{}

Filter::Filter(const std::wstring& name) :
    Object (
        core::module().attr("Filter")(name))
{}

Filter::Filter(boost::python::object f) :
    Object (f)
{}

// Retained for future use
//
// #include <boost/python/make_function.hpp>
//
// ExtensionFilter::ExtensionFilter() :
//     Filter (core::module().attr("Filter")())
// {
//     object callable = 
//         make_function(&ExtensionFilter::filter_);
//    
//
//     object filter = 
//         core::module().attr("Filter")();
//     filter.attr("filter") = callable;
//     return Filter(filter); 
// }

}}
