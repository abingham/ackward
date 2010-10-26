#ifndef INCLUDE_ACKWARD_CORE_TUPLE_HPP
#define INCLUDE_ACKWARD_CORE_TUPLE_HPP

#include <Python.h>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/tuple.hpp>
#include <boost/tuple/tuple.hpp>

#include <ackward/core/detail/Tuple.hpp>

/** Functions for converting between boost::tuple and
 * boost::python::tuple
 */

namespace ackward {
namespace core {

/** Convert a boost::python::tuple to a boost::tuple
    
    This uses the boost::python from-python type conversion system to
    convert each element in the input tuple into an element in the
    output tuple.
    
    @tparam T The boost::tuple type to convert to
    @param t The boost::python::tuple to convert from
    @return A tuple of type T containing the converted elements from
    `t`
 */
template <typename T>
T convertTuple(boost::python::tuple t)
{
    return detail::ConvertTuple<T, boost::tuples::length<T>::value>()(t);
}

/** Convert a boost::tuple into a boost::python::tuple
    
    This uses the boost::python to-python type conversion system to
    convert each element in the input tuple into an element in the
    output tuple.
    
    @tparam T The boost::tuple type to convert from
    @param t The boost::tuple to convert
    @return A boost::python::tuple containing the converted elements from `t`
*/
template <typename T>
boost::python::tuple
convertTuple(const T& t)
{
    return detail::ConvertTuple<T, boost::tuples::length<T>::value>()(t);
}

template <typename Tuple>
class TupleConverter {
public:
    typedef detail::convert_tuple<Tuple, boost::tuples::length<Tuple>::value> Impl;

    /* The convert function for boost.python's converter system
     */
    static PyObject* convert(const Tuple& t)
        {
            return Impl::convert(t);
        }

    /* Register this converter with boost.python. This can be
       called as many times as you want; only the first one has any
       effect.
    */
    static void registerConverter()
        {
            static bool initialized = false;
            
            if (initialized) return;
            
            initialized = true;
            
            boost::python::to_python_converter<
            Tuple, ackward::core::TupleConverter<Tuple> >();
            
            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<Tuple>());
        }

private:
    /* The convertible function for boost.python's converter system
     */
    static void* convertible(PyObject* obj_ptr)
        {
            return Impl::convertible(obj_ptr);
        }
    
     /* The construct function for boost.python's converter system
      */
     static void construct(
         PyObject* obj_ptr,
         boost::python::converter::rvalue_from_python_stage1_data* data)
         {
             return Impl::construct(obj_ptr, data);
         }
};

} // namespace core
} // namespace ackward

#endif
