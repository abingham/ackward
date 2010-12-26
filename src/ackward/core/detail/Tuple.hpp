#ifndef INCLUDE_ACKWARD_CORE_DETAIL_TUPLE_HPP
#define INCLUDE_ACKWARD_CORE_DETAIL_TUPLE_HPP

#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/python/extract.hpp>

#include <ackward/core/Util.hpp>

/** These are the guts of the tuple conversion routines.
 
    Mostly it's just a bunch of boost::preprocessor machination that
    builds up the (relatively) simple converters between python tuples
    and C++ tuples.
 */

namespace ackward {
namespace core {
namespace detail {

// This defines the maximum number of arguments for which a
// tuple-converter template will be created. You can define it
// externally if you want.
#ifndef ACKWARD_CORE_TUPLE_CONVERTER_SIZE_LIMIT
#define ACKWARD_CORE_TUPLE_CONVERTER_SIZE_LIMIT 11
#endif

#define ACKWARD_CORE_DETAIL_TUPLE_CONVERT_ELEMENT_FROM_PYOBJECT(z, n, _) \
boost::python::extract<typename boost::tuples::element<n, Tuple>::type>(boost::python::object(boost::python::handle<>(boost::python::borrowed(PyTuple_GetItem(obj_ptr, n)))))

#define ACKWARD_CORE_DETAIL_TUPLE_CONVERT_ELEMENT_FROM_OBJECT(z, n, _) \
boost::python::extract<typename boost::tuples::element<n, Tuple>::type>(t[n])

#define ACKWARD_CORE_DETAIL_GET_TUPLE_ELEMENT_CPP(z, n, _) boost::get<n>(t)

/* These are the details of the tuple conversion process. See
 * ackward/core/Tuple.hpp for the public functions.
 */

template <typename Tuple, int Length>
class ConvertTuple {};

#define ACKWARD_CORE_DETAIL_CONVERT_TUPLE(z, size, _) \
template <typename Tuple>                                 \
struct ConvertTuple<Tuple, size> {                        \
    Tuple operator()(boost::python::tuple t) {            \
        return Tuple(                                                   \
            BOOST_PP_ENUM(size, ACKWARD_CORE_DETAIL_TUPLE_CONVERT_ELEMENT_FROM_OBJECT, 1) \
            );                                                          \
    }                                                                   \
                                                                        \
    boost::python::tuple operator()(const Tuple&  t) {                  \
        return boost::python::make_tuple(                               \
            BOOST_PP_ENUM(size, ACKWARD_CORE_DETAIL_GET_TUPLE_ELEMENT_CPP, 1) \
            );                                                          \
    }                                                                   \
};

BOOST_PP_REPEAT_FROM_TO(1, ACKWARD_CORE_TUPLE_CONVERTER_SIZE_LIMIT, ACKWARD_CORE_DETAIL_CONVERT_TUPLE, _)

template <typename Tuple, int Size>
struct convert_tuple {
    static PyObject* convert(const Tuple& t);
};

#define ACKWARD_CORE_DETAIL_TUPLE_CHECK_ELEMENT_CONVERTIBLE(z, n, _) \
    {                                                         \
        PyObject* elem_ptr = PyTuple_GetItem(obj_ptr, n);               \
                                                                        \
        if (!fromPythonConvertible<typename boost::tuples::element<n, Tuple>::type>(elem_ptr)) \
            return 0;                                                   \
    }

#define ACKWARD_CORE_DETAIL_AUTO_CONVERT_TUPLE(z, size, _)                          \
template <typename Tuple>                                               \
struct convert_tuple<Tuple, size> {                                     \
    static PyObject* convert(const Tuple& t) {                          \
        using namespace boost::python;                                  \
                                                                        \
        tuple rval =                                                    \
            make_tuple(                                                 \
                BOOST_PP_ENUM(size, ACKWARD_CORE_DETAIL_GET_TUPLE_ELEMENT_CPP, _) \
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
        BOOST_PP_REPEAT(size, ACKWARD_CORE_DETAIL_TUPLE_CHECK_ELEMENT_CONVERTIBLE, _) \
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
                BOOST_PP_ENUM(size, ACKWARD_CORE_DETAIL_TUPLE_CONVERT_ELEMENT_FROM_PYOBJECT, _) \
                );                                                      \
                                                                        \
            data->convertible = storage;                                \
        }                                                               \
};

BOOST_PP_REPEAT_FROM_TO(1, ACKWARD_CORE_TUPLE_CONVERTER_SIZE_LIMIT, ACKWARD_CORE_DETAIL_AUTO_CONVERT_TUPLE, _)

} // namespace detail
} // namespace core
} // namespace ackward

#endif
