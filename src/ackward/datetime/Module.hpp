#ifndef INCLUDE_ACKWARD_DATETIME_MODULE_HPP
#define INCLUDE_ACKWARD_DATETIME_MODULE_HPP

#include <boost/python/object_fwd.hpp>

namespace ackward { namespace datetime
{

/** Get the python 'datetime' module.
 */
boost::python::object module();

unsigned int MINYEAR();
unsigned int MAXYEAR();

}}

#endif
