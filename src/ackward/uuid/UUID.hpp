#ifndef INCLUDE_ACKWARD_UUID_UUID_HPP
#define INCLUDE_ACKWARD_UUID_UUID_HPP

#include <string>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Object.hpp>

namespace ackward
{
namespace uuid
{

// class Fields;
// class unit128_t;

class UUID : private ackward::core::Object
{
public:
    static UUID fromHex(const std::string&);
    // static UUID fromBytes(const std::string&);
    //static UUID fromBytes_LE(const std::string&_le);
    //static UUID fromFields(const Fields&);
    //static UUID fromInt(const uint128_t);

public:
    #include <ackward/uuid/UUID_akw.hpp>
};

} // namespace uuid
} // namespace ackward

#endif
