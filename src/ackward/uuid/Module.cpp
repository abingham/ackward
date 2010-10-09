#include <ackward/uuid/Module.hpp>

#include <boost/python/import.hpp>
#include <boost/python/object.hpp>

using namespace boost::python;

namespace ackward {
namespace uuid {

object module()
{
    static object mod;
    static bool initialized = false;

    if (!initialized)
    {
        mod = import("uuid");
        initialized = true;
    }

    return mod;
}

} // namespace uuid
} // namespace ackward
