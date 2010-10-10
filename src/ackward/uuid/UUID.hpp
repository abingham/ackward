#ifndef INCLUDE_ACKWARD_UUID_UUID_HPP
#define INCLUDE_ACKWARD_UUID_UUID_HPP

#include <string>

// #include <boost/call_traits.hpp>
#include <boost/cstdint.hpp>
// #include <boost/integer.hpp>
#include <boost/tuple/tuple.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Object.hpp>
#include <ackward/uuid/Variant.hpp>

namespace ackward
{
namespace uuid
{

// typedef boost::uint_t<128> uint128_t;
// typedef boost::call_traits<uint128_t::fast>::const_reference uint128_ref;

typedef boost::tuple<unsigned long, // time_low
                     unsigned long, // time_mid
                     unsigned long, // time_hi_version
                     unsigned long, // clock_seq_hi_variant
                     unsigned long, // clock_seq_low_variant
                     unsigned long> // node
    Fields;

class UUID : private ackward::core::Object
{
public:
    static UUID fromHex(const std::string&);
    static UUID fromHex(const std::string&, 
                        uint8_t version);

    static UUID fromBytes(const std::string&);
    static UUID fromBytes(const std::string&,
                          uint8_t version);

    static UUID fromBytes_LE(const std::string&_le);
    static UUID fromBytes_LE(const std::string&_le,
                             uint8_t version);

    static UUID fromFields(const Fields&);
    static UUID fromFields(const Fields&,
                           uint8_t version);

    // static UUID fromInt(uint128_ref);
    // static UUID fromInt(uint128_ref,
    //                     uint8_t version);

    Fields fields() const;

    /* This returns 0 if version is undefined */
    uint8_t version() const;

public:
    #include <ackward/uuid/UUID_akw.hpp>
};

} // namespace uuid
} // namespace ackward

#endif
