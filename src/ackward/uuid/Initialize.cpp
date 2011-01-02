#include <ackward/uuid/Initialize.hpp>

#include <ackward/core/ByteArray.hpp>
#include <ackward/core/Enum.hpp>
#include <ackward/core/Initialize.hpp>
#include <ackward/core/PythonConverter.hpp>
#include <ackward/core/Tuple.hpp>
#include <ackward/uuid/Module.hpp>
#include <ackward/uuid/Types.hpp>
#include <ackward/uuid/UUID.hpp>
#include <ackward/uuid/Variant.hpp>

namespace ackward {
namespace uuid {

void initialize()
{
    ackward::core::initialize();

    ackward::core::initializePythonConverter<UUID>(
        "uuid.UUID");

    core::Enum<Variant>()
        .add(RESERVED_NCS, module().attr("RESERVED_NCS"))
        .add(RFC_4122, module().attr("RFC_4122"))
        .add(RESERVED_MICROSOFT, module().attr("RESERVED_MICROSOFT"))
        .add(RESERVED_FUTURE, module().attr("RESERVED_FUTURE"))
        ;

    core::TupleConverter<Fields>::registerConverter();

    ackward::core::ByteArray_python_converter<16> temp;
}

} // namespace uuid
} // namespace ackward
