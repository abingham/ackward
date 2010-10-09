#ifndef INCLUDE_ACKWARD_CORE_TUPLE_HPP
#define INCLUDE_ACKWARD_CORE_TUPLE_HPP

#include <Python.h>
#include <boost/tuple/tuple.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/tuple.hpp>

#include <iostream>

/** Functions for converting between boost::tuple and
 * boost::python::tuple
 */

namespace ackward {
namespace core {

namespace detail {

/* These are the details of the tuple conversion process. The public
 * functions for doing conversion follow.
 */

// TODO: Use boost::preprocessor (or something) to automatically generate
// the different lengths of these functions.

template <typename T, int Length>
class ConvertTuple {};

template <typename T>
struct ConvertTuple<T, 2>
{
    T operator()(boost::python::tuple t)
        {
            return boost::make_tuple(
                boost::python::extract<typename boost::tuples::element<0, T>::type>(
                    t[0])(),
                boost::python::extract<typename boost::tuples::element<1, T>::type>(
                    t[1])());
        }   
    
    boost::python::tuple operator()(const T& t)
        {
            return boost::python::make_tuple(
                boost::tuples::get<0>(t),
                boost::tuples::get<1>(t));
        }
};

template <typename T>
struct ConvertTuple<T, 3>
{
    T operator()(boost::python::tuple t)
        {
            return boost::make_tuple(
                boost::python::extract<typename boost::tuples::element<0, T>::type>(
                    t[0])(),
                boost::python::extract<typename boost::tuples::element<1, T>::type>(
                    t[1])(),
                boost::python::extract<typename boost::tuples::element<2, T>::type>(
                    t[2])());
        }   

    boost::python::tuple operator()(const T& t)
        {
            return boost::python::make_tuple(
                boost::tuples::get<0>(t),
                boost::tuples::get<1>(t),
                boost::tuples::get<2>(t));
        }
};

template <typename T>
struct ConvertTuple<T, 6>
{
    T operator()(boost::python::tuple t)
        {
            return boost::make_tuple(
                boost::python::extract<typename boost::tuples::element<0, T>::type>(
                    t[0])(),
                boost::python::extract<typename boost::tuples::element<1, T>::type>(
                    t[1])(),
                boost::python::extract<typename boost::tuples::element<2, T>::type>(
                    t[2])(),
                boost::python::extract<typename boost::tuples::element<3, T>::type>(
                    t[3])(),
                boost::python::extract<typename boost::tuples::element<4, T>::type>(
                    t[4])(),
                boost::python::extract<typename boost::tuples::element<5, T>::type>(
                    t[5])());
        }   

    boost::python::tuple operator()(const T& t)
        {
            return boost::python::make_tuple(
                boost::tuples::get<0>(t),
                boost::tuples::get<1>(t),
                boost::tuples::get<2>(t),
                boost::tuples::get<3>(t),
                boost::tuples::get<4>(t),
                boost::tuples::get<5>(t));
        }
};

}

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

} // namespace core
} // namespace ackward

#endif
