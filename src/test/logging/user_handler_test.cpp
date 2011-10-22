#include <Python.h>

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

struct PushBackHandlerImpl
{
    void emit(const LogRecord& lr)
        {
            messages.push_back(lr.getMessage());
        }

    std::vector<std::wstring> messages;
};

typedef UserHandler<PushBackHandlerImpl> PushBackHandler;

}

BOOST_AUTO_TEST_SUITE( logging )
BOOST_AUTO_TEST_SUITE( userHandler )

BOOST_AUTO_TEST_CASE( basic )
{
    PushBackHandler h;

    Logger l = getLogger(L"basic_test");
    l.setLevel(DEBUG());

    l.addHandler(h);

    l.error(L"error");
    BOOST_CHECK(h.impl().messages.size() == 1);
    BOOST_CHECK(h.impl().messages[0] == L"error");

    l.debug(L"debug");
    BOOST_CHECK(h.impl().messages.size() == 2);
    BOOST_CHECK(h.impl().messages[1] == L"debug");
}

BOOST_AUTO_TEST_CASE( auto_disconnect )
{
    Logger l = getLogger(L"auto_disconnect_test");
    l.setLevel(DEBUG());
    BOOST_CHECK(l.handlers().size() == 0);

    { // Add a handler which we then let go out of scope.
        PushBackHandler h;
        l.addHandler(h);
        BOOST_CHECK(l.handlers().size() == 1);

        l.error(L"test");
        BOOST_CHECK(h.impl().messages.size() == 1);
    }

    // When the UserHandler goes out of scope, it doesn't actually
    // "delete" the underlying Python object. That is kept alive by
    // virtue of its being referenced by the logger. However, the
    // UserHandler resets the "emit" method of the underlying Python
    // object so that any loggers referring to it can still safely
    // call it without causing a segfault.
    BOOST_CHECK(l.handlers().size() == 1);
    l.error(L"test2");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
