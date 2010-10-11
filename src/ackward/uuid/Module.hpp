#ifndef INCLUDE_ACKWARD_UUID_MODULE_HPP
#define INCLUDE_ACKWARD_UUID_MODULE_HPP

#include <string>

#include <boost/call_traits.hpp>
#include <boost/integer.hpp>
#include <boost/python/object_fwd.hpp>

namespace ackward {
namespace uuid {

class UUID;

typedef boost::uint_t<64>::least Node;

#include <ackward/uuid/Module_akw.hpp>

} // namespace uuid
} // namespace ackward

#endif
