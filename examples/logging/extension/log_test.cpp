#include <string>

#include <boost/python.hpp>

#include <ackward/logging/Logger.hpp>

namespace bp=boost::python;

namespace
{

void log_message(bp::object logger,
                 const std::wstring& msg)
{
    ackward::logging::Logger l(logger);
    l.error(msg);
}

}

BOOST_PYTHON_MODULE(log_test)
{
    bp::def("log_message", ::log_message);
}
