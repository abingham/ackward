#include <ackward/uuid/Module.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

#include <ackward/core/Exceptions.hpp>
#include <ackward/uuid/UUID.hpp>

using namespace boost::python;

namespace ackward {
namespace uuid {

#include <ackward/uuid/Module_akw.ipp>

} // namespace uuid
} // namespace ackward
