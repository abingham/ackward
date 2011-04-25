#ifndef INCLUDE_ACKWARD_UUID_VARIANT_HPP
#define INCLUDE_ACKWARD_UUID_VARIANT_HPP

namespace ackward {
namespace uuid {

/** These represent the various internal layouts of a UUID.
 */
enum Variant
{
    RESERVED_NCS, 
    RFC_4122, 
    RESERVED_MICROSOFT, 
    RESERVED_FUTURE
};

} // namespace uuid
} // namespace ackward

#endif
