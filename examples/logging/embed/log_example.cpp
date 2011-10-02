#include <ackward/logging/BasicConfig.hpp>               // 1
#include <ackward/logging/Initialize.hpp>                // 2
#include <ackward/logging/Logger.hpp>                    // 3
#include <ackward/logging/Module.hpp>                    // 4

namespace al=ackward::logging;
namespace bp=boost::python;

int main(int, char**)
{
    Py_Initialize();                                     // 5
    al::initialize();                                    // 6

    al::basicConfig();                                   // 7

    // Create a logger
    al::Logger logger = al::getLogger(L"log_example");   // 8
    logger.critical(L"The widget is broken!");           // 9

    return 0;
}
