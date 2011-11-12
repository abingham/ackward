#include <string>
#include <vector>

#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/UserHandler.hpp>

using namespace ackward::logging;

struct PushBackHandlerImpl
{
    void emit(const LogRecord& lr)
        {
            messages.push_back(lr.getMessage());
        }

    std::vector<std::wstring> messages;
};

typedef UserHandler<PushBackHandlerImpl> PushBackHandler;
