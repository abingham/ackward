#ifndef INCLUDE_ACKWARD_QUEUE_MODULE_HPP
#define INCLUDE_ACKWARD_QUEUE_MODULE_HPP

#include <boost/python/object.hpp>

namespace ackward {
namespace queue {

/** Get the Python queue module object.
 */
boost::python::object module();

}
}

#endif
