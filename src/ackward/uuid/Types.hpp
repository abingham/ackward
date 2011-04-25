#ifndef INCLUDE_ACKWARD_UUID_TYPES_HPP
#define INCLUDE_ACKWARD_UUID_TYPES_HPP

#include <boost/integer.hpp>
#include <boost/tuple/tuple.hpp>

namespace ackward {
namespace uuid {

/** A hardware address as returned by UUID::getnode.
 */
typedef boost::uint_t<64>::least Node;
// typedef boost::uint_t<128> Integer;

/** 
\rst
Six-integer representation of UUIDs.

See `<http://docs.python.org/library/uuid.html#uuid.UUID.fields>`_.
\endrst
 */ 
typedef boost::tuple<unsigned long, // time_low
                     unsigned long, // time_mid
                     unsigned long, // time_hi_version
                     unsigned long, // clock_seq_hi_variant
                     unsigned long, // clock_seq_low_variant
                     unsigned long> // node
    Fields;

}
}

#endif
