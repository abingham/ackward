#include <Python.h>

#include <ackward/time/Initialize.hpp>

#include <ctime>

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/GetClass.hpp>

using namespace boost::python;

namespace
{

/** from-python converter for time.struct_time -> tm */
struct struct_time_from_tm
{
    struct_time_from_tm()
        {
            boost::python::converter::registry::push_back(
                &convertible,
                &construct,
                boost::python::type_id<tm>());
        }
    
    static void* convertible(PyObject* obj_ptr)
        {
            boost::python::object cls = 
                ackward::core::getClass("time.struct_time");
            if (!PyObject_IsInstance(obj_ptr, cls.ptr())) return 0;
            return obj_ptr;
        }
    
    static void construct(
        PyObject* obj_ptr,
        boost::python::converter::rvalue_from_python_stage1_data* data)
        {
            using namespace boost::python;

            object tt = object(
                handle<>(
                    obj_ptr));

            void* storage = (
                (boost::python::converter::rvalue_from_python_storage<tm>*)
                data)->storage.bytes;
            
            // in-place construct the new QString using the character data
            // extraced from the python object
            tm* rslt = new (storage) tm;
            rslt->tm_sec = extract<int>(tt.attr("tm_sec"));
            rslt->tm_min = extract<int>(tt.attr("tm_min"));
            rslt->tm_hour = extract<int>(tt.attr("tm_hour"));
            rslt->tm_mday = extract<int>(tt.attr("tm_mday"));
            rslt->tm_mon = extract<int>(tt.attr("tm_mon"));  
            rslt->tm_year = extract<int>(tt.attr("tm_year"));
            rslt->tm_wday = extract<int>(tt.attr("tm_wday"));
            rslt->tm_yday = extract<int>(tt.attr("tm_yday"));
            rslt->tm_isdst = extract<int>(tt.attr("tm_isdst"));
            
            // Stash the memory chunk pointer for later use by boost.python
            data->convertible = storage;
        }
};

}

namespace ackward { namespace time
{

void initialize()
{
    static bool initialized = false;
    if (initialized)
        return;

    struct_time_from_tm();
}

}}
