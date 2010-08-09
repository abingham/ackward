#ifndef INCLUDE_ACKWARD_LOGGING_FILTER_HPP
#define INCLUDE_ACKWARD_LOGGING_FILTER_HPP

#include <string>

#include <ackward/core/Object.hpp>

namespace ackward { namespace logging
{

class Filter : private core::Object
{
public:
    Filter();
    Filter(const std::wstring& name);
    Filter(boost::python::object);

    using core::Object::obj;
};

}}

#endif
