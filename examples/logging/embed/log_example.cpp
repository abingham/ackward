#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

namespace al=ackward::logging;
namespace bp=boost::python;

int main(int, char**)
{
    Py_Initialize();
    al::initialize();
    
    al::basicConfig();

    // Create a logger
    al::Logger logger = al::getLogger(L"log_example");
    logger.critical(L"The widget is broken!");

    return 0;
}
