#ifndef INCLUDE_ACKWARD_UUID_UUID_HPP
#define INCLUDE_ACKWARD_UUID_UUID_HPP

#include <string>

#include <boost/cstdint.hpp>
#include <boost/tuple/tuple.hpp>

#include <ackward/core/GetClass.hpp>
#include <ackward/core/Object.hpp>

namespace ackward
{
namespace uuid
{

// typedef boost::tuple<boost::uint32_t, // time_low
//                      boost::uint16_t, // time_mid
//                      boost::uint16_t, // time_hi_version
//                      boost::uint8_t,  // clock_seq_hi_variant
//                      boost::uint8_t,  // clock_seq_low_variant
//                      boost::uint64_t> // node
//     Fields;

typedef boost::tuple<unsigned long, // time_low
                     unsigned long, // time_mid
                     unsigned long, // time_hi_version
                     unsigned long, // clock_seq_hi_variant
                     unsigned long, // clock_seq_low_variant
                     unsigned long> // node
    Fields;

// class Fields;
// class unit128_t;

class UUID : private ackward::core::Object
{
public:
    static UUID fromHex(const std::string&);
    static UUID fromBytes(const std::string&);
    static UUID fromBytes_LE(const std::string&_le);
    static UUID fromFields(const Fields&);
    //static UUID fromInt(const uint128_t);

    Fields fields() const;

public:
    #include <ackward/uuid/UUID_akw.hpp>
};

} // namespace uuid
} // namespace ackward

#endif
