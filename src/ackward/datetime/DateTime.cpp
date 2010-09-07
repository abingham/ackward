#include <ackward/datetime/DateTime.hpp>

#include <ackward/datetime/Module.hpp>

namespace ackward { namespace datetime
{

DateTime::DateTime(boost::python::object o) :
    Object (o)
{
}

DateTime DateTime::now()
{
    return DateTime(
        module().attr("datetime").attr("now")());
}

}}
