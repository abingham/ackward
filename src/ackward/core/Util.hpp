#ifndef INCLUDE_BA_LOG_DETAIL_UTIL_HPP
#define INCLUDE_BA_LOG_DETAIL_UTIL_HPP

#include <string>

#include <boost/python/object.hpp>

#include <ackward/core/Exceptions.hpp>

namespace ackward { namespace core
{

bool is_none(const boost::python::object&);

boost::python::object 
iter(boost::python::object);

boost::python::object
next(boost::python::object iterator);

std::wstring repr(boost::python::object);

/** Determine if an object is of a specified type.

    @param obj The object to test
    @param typeName The full name of the type to test for
    @return True of `obj` is of type `typeName`, false otherwise.
 */
bool isInstance(boost::python::object obj,
                const std::string& typeName);

/** Verify that an object is of a given type, throwing a specified exception if it is not.

    @param obj The object to test
    @param typeName The full name of the expected type of `obj`
    @tparam ExcType The type of exception to throw if `obj` is not a `typeName`. This exception will be default-constructed.
 */
template <typename ExcType=ValueError>
void verifyType(boost::python::object obj,
                const std::string& typeName)
{
    if (!isInstance(obj, typeName))
        throw ExcType();
}

}}

#endif
