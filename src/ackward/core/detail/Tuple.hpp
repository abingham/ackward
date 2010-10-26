#ifndef INCLUDE_ACKWARD_CORE_DETAIL_TUPLE_HPP
#define INCLUDE_ACKWARD_CORE_DETAIL_TUPLE_HPP

#include <ackward/core/Util.hpp>

namespace ackward {
namespace core {
namespace detail {

/* These are the details of the tuple conversion process. See
 * ackward/core/Tuple.hpp for the public functions.
 */

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

template <typename Tuple, int Size>
struct convert_tuple {
    static PyObject* convert(const Tuple& t);
};

#define ACKWARD_CORE_TUPLE_CONVERT_ELEMENT_TO(z, n, _) boost::get<n>(t)

#define ACKWARD_CORE_TUPLE_CHECK_ELEMENT_CONVERTIBLE(z, n, _) \
    {                                                         \
        PyObject* elem_ptr = PyTuple_GetItem(obj_ptr, n);               \
                                                                        \
        if (!fromPythonConvertible<typename boost::tuples::element<n, Tuple>::type>(elem_ptr)) \
            return 0;                                                   \
    }

#define ACKWARD_CORE_TUPLE_CONVERT_ELEMENT_FROM(z, n, _)                \
extract<typename boost::tuples::element<n, Tuple>::type>(object(handle<>(borrowed(PyTuple_GetItem(obj_ptr, n)))))

#define CONVERT_TUPLE(z, size, _)                                       \
template <typename Tuple>                                               \
struct convert_tuple<Tuple, size> {                                     \
    static PyObject* convert(const Tuple& t) {                          \
        using namespace boost::python;                                  \
                                                                        \
        tuple rval =                                                    \
            make_tuple(                                                 \
                BOOST_PP_ENUM(size, ACKWARD_CORE_TUPLE_CONVERT_ELEMENT_TO, _) \
                );                                                      \
                                                                        \
        return incref(rval.ptr());                                      \
    }                                                                   \
                                                                        \
    static void* convertible(PyObject* obj_ptr) {                       \
        using namespace boost::python;                                  \
                                                                        \
        if (!PyTuple_Check(obj_ptr)) return 0;                          \
        if (!PyTuple_Size(obj_ptr) == size) return 0;                   \
                                                                        \
        BOOST_PP_REPEAT(size, ACKWARD_CORE_TUPLE_CHECK_ELEMENT_CONVERTIBLE, _) \
                                                                        \
            return obj_ptr;                                             \
    }                                                                   \
                                                                        \
    static void construct(                                              \
        PyObject* obj_ptr,                                              \
        boost::python::converter::rvalue_from_python_stage1_data* data) \
        {                                                               \
            using namespace boost::python;                              \
                                                                        \
            void* storage = (                                           \
                (converter::rvalue_from_python_storage<Tuple>*)         \
                data)->storage.bytes;                                   \
                                                                        \
            new (storage) Tuple(                                        \
                BOOST_PP_ENUM(size, ACKWARD_CORE_TUPLE_CONVERT_ELEMENT_FROM, _) \
                );                                                      \
                                                                        \
            data->convertible = storage;                                \
        }                                                               \
};

#ifndef TUPLE_CONVERTER_SIZE_LIMIT
#define TUPLE_CONVERTER_SIZE_LIMIT 11
#endif

BOOST_PP_REPEAT_FROM_TO(1, TUPLE_CONVERTER_SIZE_LIMIT, CONVERT_TUPLE, _)

} // namespace detail
} // namespace core
} // namespace ackward

#endif
