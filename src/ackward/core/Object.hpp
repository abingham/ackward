#ifndef INCLUDE_ACKWARD_CORE_OBJECT_HPP
#define INCLUDE_ACKWARD_CORE_OBJECT_HPP

#include <boost/python/extract.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/Import.hpp>

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

#define ACKWARD_ATTR(result_type, name)               \
    result_type name() const {                        \
        return boost::python::extract<result_type>(   \
            obj().attr(#name));                       \
    }

#define ACKWARD_METHOD(result_type, name)       \
    result_type name() const {                  \
    return boost::python::extract<result_type>( \
        obj().attr(#name)());                   \
    }

// Getter/Setter

// #define ACKWARD_CLASS_METHOD(result_type, mod, cls, name)  \
//     static result_type name() {                           \
//         return boost::python::extract<result_type>(       \
//             ackward::core::findObject(#mod, #cls).attr(#name)); \
//     }

#endif
