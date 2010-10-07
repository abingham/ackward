#include <ackward/uuid/UUID.hpp>

#include <boost/python/object.hpp>

#include <ackward/core/ExceptionTranslator.hpp>

using namespace boost::python;

namespace ackward {
namespace uuid {

UUID UUID::fromHex(const std::string& hex) {
    try {
        object obj = UUID::cls()(hex);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

UUID UUID::fromBytes(const std::string& bytes)
{
    try {
        object obj = UUID::cls()(object(), bytes);
        return UUID(obj);
    } TRANSLATE_PYTHON_EXCEPTION();
}

// static UUID fromBytes_LE(const std::string&_le);
// static UUID fromFields(const Fields&);
// static UUID fromInt(const uint128_t);

#include <ackward/uuid/UUID_akw.ipp>

} // namespace uuid
} // namespace ackward
