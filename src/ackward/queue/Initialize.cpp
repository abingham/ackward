#include <ackward/queue/Initialize.hpp>

#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/Initialize.hpp>
#include <ackward/core/PythonConverter.hpp>
#include <ackward/core/PythonVersion.hpp>

#include <ackward/queue/Exceptions.hpp>
#include <ackward/queue/Module.hpp>
#include <ackward/queue/Queue.hpp>

namespace ackward {
namespace queue {

void initialize()
{
    ackward::core::initialize();

    ackward::core::registerExceptionTranslation<Full>(
        module().attr("Full"));
    ackward::core::registerExceptionTranslation<Empty>(
        module().attr("Empty"));

    ackward::core::initializePythonConverter<Queue>(
#if ACKWARD_PYTHON_MAJOR_VERSION == 2
        "Queue.Queue"
#else
        "queue.Queue"
#endif
        );

    // ackward::core::initializePythonConverter<LifoQueue>(
    //     "queue.LifoQueue");
    // ackward::core::initializePythonConverter<PriorityQueue>(
    //     "queue.PriorityQueue");
}

}
}
