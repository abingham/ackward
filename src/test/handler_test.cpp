#include <ackward/logging/Handler.hpp>

#include <boost/python.hpp>
#include <boost/test/unit_test.hpp>

using namespace ackward::logging;
using namespace boost::python;

BOOST_AUTO_TEST_SUITE( Handlers )

// Handler(boost::python::object);
// void setLevel(Level l);
// void setFormatter(Formatter f);
// void addFilter(Filter f);
// void removeFilter(Filter f);
// void flush() const;
// void close();

BOOST_AUTO_TEST_CASE( StreamHandler_factory )
{
    StreamHandler h;
    StreamHandler h2(import("sys").attr("stdout"));
}

BOOST_AUTO_TEST_CASE( FileHandler_factory )
{
    FileHandler(L"delete_me.log");
    FileHandler(L"delete_me2.log",
                "w");
    FileHandler(L"delete_me3.log",
                "a",
                "utf8");
    FileHandler(L"delete_me3.log",
                "a",
                "utf8",
                true);
}

BOOST_AUTO_TEST_CASE( WatchedFileHandler_factory )
{
    WatchedFileHandler(L"delete_me.log");
    WatchedFileHandler(L"delete_me2.log",
                       "w");
    WatchedFileHandler(L"delete_me3.log",
                       "a",
                       "utf8");
    WatchedFileHandler(L"delete_me3.log",
                       "a",
                       "utf8",
                       true);
}

BOOST_AUTO_TEST_CASE( SocketHandler_factory )
{
    SocketHandler(L"localhost", 1234);
}

BOOST_AUTO_TEST_CASE( NullHandler )
{
    NullHandler h;
}

BOOST_AUTO_TEST_SUITE_END()
