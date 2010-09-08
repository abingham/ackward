#ifndef INCLUDE_BA_LOG_DETAIL_UTIL_HPP
#define INCLUDE_BA_LOG_DETAIL_UTIL_HPP

#include <string>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace core
{

bool is_none(const boost::python::object&);

boost::python::object 
iter(boost::python::object);

boost::python::object
next(boost::python::object iterator);

std::wstring repr(boost::python::object);

bool isInstance(boost::python::object obj,
                const std::string& typeName);

}}

#endif
