#include <ackward/uuid/Initialize.hpp>

#include <ackward/core/Enum.hpp>
#include <ackward/uuid/Module.hpp>
#include <ackward/uuid/Variant.hpp>

namespace ackward {
namespace uuid {

void initialize()
{
    core::Enum<Variant>()
        .add(RESERVED_NCS, module().attr("RESERVED_NCS"))
        .add(RFC_4122, module().attr("RFC_4122"))
        .add(RESERVED_MICROSOFT, module().attr("RESERVED_MICROSOFT"))
        .add(RESERVED_FUTURE, module().attr("RESERVED_FUTURE"))
        ;
}

} // namespace uuid
} // namespace ackward
