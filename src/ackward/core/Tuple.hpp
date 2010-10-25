#ifndef INCLUDE_ACKWARD_CORE_TUPLE_HPP
#define INCLUDE_ACKWARD_CORE_TUPLE_HPP

#include <Python.h>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/python/extract.hpp>
#include <boost/python/to_python_converter.hpp>
#include <boost/python/tuple.hpp>
#include <boost/tuple/tuple.hpp>

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

namespace detail {

template <typename Tuple, int Size>
struct convert_tuple {
    static PyObject* convert(const Tuple& t);
};

// template <typename Tuple>
// PyObject* convert<Tuple, 1>(const Tuple& t) { ... }

// template <typename Tuple>
// PyObject* convert<Tuple, 2>(const Tuple& t) { ... }

#define CONVERT_ELEMENT(z, n, _) boost::get<n>(t)

#define CONVERT_TUPLE(z, size, _)                    \
template <typename Tuple>                            \
struct convert_tuple<Tuple, size> {                  \
    static PyObject* convert(const Tuple& t) {       \
        using namespace boost::python;               \
                                                     \
        tuple rval =                                 \
            make_tuple(                              \
                BOOST_PP_ENUM(size, CONVERT_ELEMENT, _) \
                );                                      \
                                                        \
        return incref(rval.ptr());                      \
    }                                                   \
};

#ifndef TUPLE_CONVERTER_SIZE_LIMIT
#define TUPLE_CONVERTER_SIZE_LIMIT 11
#endif

BOOST_PP_REPEAT_FROM_TO(1, TUPLE_CONVERTER_SIZE_LIMIT, CONVERT_TUPLE, _)

} // namespace detail

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

    /* initialize the boost.python conversion system. This can be
       called as many times as you want; only the first one has any
       effect.
    */
    static void initialize()
        {
            static bool initialized = false;
            
            if (initialized) return;
            
            initialized = true;
            
            boost::python::to_python_converter<
            Tuple, ackward::core::TupleConverter<Tuple> >();
            
            //boost::python::converter::registry::push_back(
            //    &convertible,
            //    &construct,
            //    boost::python::type_id<Tuple>());
        }

private:
    /* The convertible function for boost.python's converter system
     */
    // static void* convertible(PyObject* obj_ptr)
    //     {
    //         return Impl::convertible(obj_ptr);
    //     }

//     /* The construct function for boost.python's converter system
//      */
//     static void construct(
//         PyObject* obj_ptr,
//         boost::python::converter::rvalue_from_python_stage1_data* data)
//         {
//             using namespace boost::python;

//             BOOST_FOREACH(const typename Entries::value_type& entry, entries_)
//             {
//                 if (PyObject_Compare(entry.second.ptr(), obj_ptr) == 0)
//                 {
//                     void* storage = (
//                         (converter::rvalue_from_python_storage<E>*)
//                         data)->storage.bytes;
//                     new (storage) E(entry.first);
//                     data->convertible = storage;
                    
//                     return;
//                 }
//             }

//             throw error_already_set();
//         }
};

} // namespace core
} // namespace ackward

#endif
