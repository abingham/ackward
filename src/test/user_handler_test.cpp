#include <vector>

#include <boost/test/unit_test.hpp>

#include <ackward/logging/Logger.hpp>
#include <ackward/logging/LogRecord.hpp>
#include <ackward/logging/Module.hpp>
#include <ackward/logging/Types.hpp> 
#include <ackward/logging/UserHandler.hpp>

using namespace ackward::logging;

namespace
{

struct PushBackHandler : public UserHandler
{
    void emit_impl(const LogRecord& lr)
        {
            messages.push_back(lr.getMessage());
        }
    
    std::vector<std::wstring> messages;
};

}

BOOST_AUTO_TEST_SUITE( UserHandler )

BOOST_AUTO_TEST_CASE( basic )
{
    PushBackHandler h;

    Logger l = getLogger();
    l.setLevel(DEBUG());

    l.addHandler(h);

    l.error(L"error");
    BOOST_CHECK(h.messages.size() == 1);
    BOOST_CHECK(h.messages[0] == L"error");

    l.debug(L"debug");
    BOOST_CHECK(h.messages.size() == 2);
    BOOST_CHECK(h.messages[1] == L"debug");
}

BOOST_AUTO_TEST_SUITE_END()
