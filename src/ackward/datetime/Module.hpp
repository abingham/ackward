#ifndef INCLUDE_ACKWARD_DATETIME_MODULE_HPP
#define INCLUDE_ACKWARD_DATETIME_MODULE_HPP

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace datetime
{

boost::python::object module();

int MINYEAR();
int MAXYEAR();

}}

#endif
