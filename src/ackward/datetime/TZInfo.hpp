#ifndef INCLUDE_ACKWARD_DATETIME_TZINFO_HPP
#define INCLUDE_ACKWARD_DATETIME_TZINFO_HPP

#include <Python.h>

#include <boost/shared_ptr.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/make_function.hpp>

#include <ackward/core/Object.hpp>
#include <ackward/core/Util.hpp>
#include <ackward/datetime/DateTime.hpp>
#include <ackward/datetime/Module.hpp>
#include <ackward/datetime/TimeDelta.hpp>

using namespace boost::python;

namespace ackward { namespace datetime
{

class DateTime;
class TimeDelta;

class TZInfo : private core::Object
{
public:
    TZInfo(boost::python::object);

    virtual 
    TimeDelta dst(const DateTime&) const;

    virtual 
    DateTime fromutc(const DateTime&) const;

    virtual 
    std::wstring tzname() const;

    virtual
    TimeDelta utcoffset(const DateTime&) const;

    using Object::obj;
};

template <class Impl>
class TZInfo_ : public TZInfo
{
public:
    TZInfo_() :
        TZInfo ( module().attr("tzinfo")() )
        {
            obj().attr("dst") = 
                boost::python::make_function(
                    TZInfo_<Impl>::dst_impl);

            obj().attr("fromutc") = 
                boost::python::make_function(
                    TZInfo_<Impl>::fromutc_impl);

            obj().attr("tzname") = 
                boost::python::make_function(
                    TZInfo_<Impl>::tzname_impl);

            obj().attr("utcoffset") = 
                boost::python::make_function(
                    TZInfo_<Impl>::utcoffset_impl);
        }

private:
    static boost::python::object dst_impl(boost::python::object o)
        {
            DateTime dt(o);
            return Impl::dst(dt).obj();
        }

    static boost::python::object fromutc_impl(boost::python::object o)
        {
            DateTime dt(o);
            return Impl::fromutc(dt).obj();
        }

    static boost::python::object tzname_impl()
        {
            return boost::python::object(Impl::tzname());
        }

    static boost::python::object utcoffset_impl(boost::python::object o)
        {
            DateTime dt(o);
            return Impl::utcoffset(dt).obj();
        }
};

}}

#endif
