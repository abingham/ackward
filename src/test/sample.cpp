#include <ackward/logging/Handler.hpp>
#include <ackward/logging/Initialize.hpp>
#include <ackward/logging/Logger.hpp>
#include <ackward/logging/Module.hpp>

using namespace ackward::logging;

int main(void)
{
    Py_Initialize();
    initialize();

    Logger l = getLogger();
    Handler h = FileHandler(L"test.log");
    l.addHandler(h);
    l.error(L"yo!");

    return 0;
}
