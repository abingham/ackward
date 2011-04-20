#include <ackward/queue/Module.hpp>

#include <ackward/core/PythonVersion.hpp>

namespace ackward {
namespace queue {

boost::python::object module()
{
#if ACKWARD_PYTHON_MAJOR_VERSION == 2
    return import("Queue");
#else
    return import("queue");
#endif
}

}
}
