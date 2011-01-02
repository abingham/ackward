#ifndef INCLUDE_ACKWARD_CORE_ENUM_HPP
#define INCLUDE_ACKWARD_CORE_ENUM_HPP

#include <Python.h>

#include <map>

#include <boost/foreach.hpp>
#include <boost/python/object.hpp>
#include <boost/python/to_python_converter.hpp>

#include <ackward/core/Exceptions.hpp>

namespace ackward {
namespace core {

/** A tool to simplify the construction of python converters between a
    python enum and a C++ enum. This differs from boost.python's enum
    template in that bp's enum is designed to expose C++ enumerations
    in python extension modules. This class is designed to maps python
    enumerations (such as they are) to C++ enumerations in embedded
    situations. Fundmentally, this class sets up the to/from-python
    converters needed to translate the enumeration across the
    python-C++ boundary.

    Of course, python has no native notion of enumerations. So really,
    this class establishes a mapping from the values in a C++ enum to
    arbitrary python objects; it's up to users to establish the
    mapping they want.

    Basic usage::

      enum MyEnum {
        Val1,
        Val2,
        Val3
      };

      ...
      
      // Run this during your initialization routine or something...sometime
      // before conversion is needed.
      Enum<MyEnum>()
        .add(Val1, import("my_module").attr("enum_value1")
        .add(Val2, import("my_module").attr("enum_value2")
        .add(Val3, import("my_module").attr("enum_value3")
        ;

      ...

      object obj(Val1);
      assert(obj == import("my_module").attr("enum_value1"));

      MyEnum e = extract<MyEnum>(obj);
      assert(e == Val1);
 */
template <typename E>
class Enum
{
public:
    /** Add a conversion mapping

        @param cpp The C++ enum value to map

        @param py The Python object to associate with `cpp`

        @param overwrite Whether this should replace an existing
          mapping for `cpp` if one already exists

        @throw ackward::core::KeyError If a mapping for `cpp` already exists
          and `overwrite` is false

        @return The Enum instance itself; this allows chaining of
          `add` calls.
     */
    Enum& add(E cpp, 
              boost::python::object py,
              bool overwrite=false)
        {
            init();
            
            typename Entries::const_iterator itr = entries_.find(cpp);
            if (itr != entries_.end() && !overwrite)
                throw KeyError();
            
            entries_[cpp] = py;

            return *this;
        }

    /* The convert function for boost.python's converter system
     */
    static PyObject* convert(E e)
        {
            using namespace boost::python;

            typename Entries::const_iterator itr = entries_.find(e);
            if (entries_.end() == itr)
                return incref(object().ptr());

            return incref(itr->second.ptr());
        }

private:
    /* initialize the boost.python conversion system. This can be
       called as many times as you want; only the first one has any
       effect.
     */
    static void init()
        {
            static bool initialized = false;

            if (initialized) return;

            initialized = true;

            boost::python::to_python_converter<
                E, ackward::core::Enum<E> >();

            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<E>());
        }

    /* The convertible function for boost.python's converter system
     */
    static void* convertible(PyObject* obj_ptr)
        {
            BOOST_FOREACH(const typename Entries::value_type& entry, entries_)
            {
                int rslt = PyObject_RichCompareBool(
                    entry.second.ptr(),
                    obj_ptr,
                    Py_EQ);

                if (rslt == 1)
                    return obj_ptr;
            }

            return 0;
        }

    /* The construct function for boost.python's converter system
     */
    static void construct(
        PyObject* obj_ptr,
        boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost::python;

            BOOST_FOREACH(const typename Entries::value_type& entry, entries_)
            {
                int rslt = PyObject_RichCompareBool(
                    entry.second.ptr(),
                    obj_ptr,
                    Py_EQ);

                if (rslt == 1)
                {
                    void* storage = (
                        (converter::rvalue_from_python_storage<E>*)
                        data)->storage.bytes;
                    new (storage) E(entry.first);
                    data->convertible = storage;
                    
                    return;
                }
            }

            throw error_already_set();
        }

private:
    typedef std::map<E, boost::python::object> Entries;
    static Entries entries_;
};

template <typename E>
std::map<E, boost::python::object> Enum<E>::entries_;

} // namespace core
} // namespace ackward

#endif
