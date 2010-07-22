#ifndef INCLUDE_BA_LOG_DETAIL_GET_CLASS_HPP
#define INCLUDE_BA_LOG_DETAIL_GET_CLASS_HPP

#include <string>

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace core
{

boost::python::object 
getClass(const std::string& name);

}}

#endif
