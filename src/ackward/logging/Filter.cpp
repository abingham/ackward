#include <ackward/logging/Filter.hpp>

#include <ackward/logging/Module.hpp>

#include <boost/python.hpp>

using namespace boost::python;

namespace ackward { namespace logging
{

Filter::Filter() :
    Object (
        module().attr("Filter")())
{}

Filter::Filter(const std::wstring& name) :
    Object (
        module().attr("Filter")(name))
{}

Filter::Filter(boost::python::object f) :
    Object (f)
{}

// Retained for future use
//
// #include <boost/python/make_function.hpp>
//
// ExtensionFilter::ExtensionFilter() :
//     Filter (module().attr("Filter")())
// {
//     object callable = 
//         make_function(&ExtensionFilter::filter_);
//    
//
//     object filter = 
//         module().attr("Filter")();
//     filter.attr("filter") = callable;
//     return Filter(filter); 
// }

}}
