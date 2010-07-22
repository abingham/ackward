#include <ackward/core/Object.hpp>

namespace ackward { namespace core
{

Object::Object(boost::python::object obj) :
    obj_ (obj)
{}

boost::python::object Object::obj()
{
    return obj_;
}

const boost::python::object Object::obj() const
{
    return obj_;
}

}}
