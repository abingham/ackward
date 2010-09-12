#ifndef INCLUDE_ACKWARD_CORE_OBJECT_HPP
#define INCLUDE_ACKWARD_CORE_OBJECT_HPP

#include <boost/python/object.hpp>

namespace ackward { namespace core
{

class Object
{
public:
    Object(boost::python::object);

    boost::python::object obj();
    const boost::python::object obj() const;

private:
    boost::python::object obj_;
};

}}

// TEMPLATES GO HERE


#endif
