#include <ackward/logging/Initialize.hpp>                // 1
#include <ackward/logging/Logger.hpp>                    // 2
#include <ackward/logging/Module.hpp>                    // 3

namespace al=ackward::logging;
namespace bp=boost::python;

int main(int, char**)
{
    Py_Initialize();                                     // 4
    al::initialize();                                    // 5
    
    al::basicConfig();                                   // 6

    // Create a logger
    al::Logger logger = al::getLogger(L"log_example");   // 7
    logger.critical(L"The widget is broken!");           // 8

    return 0;
}
