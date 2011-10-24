#include <Python.h>
#include <string>

#include <boost/python.hpp>

#include <ackward/logging/Logger.hpp>       // 1

namespace bp=boost::python;

namespace
{

void log_message(bp::object logger,         // 2
                 const std::wstring& msg)
{
    ackward::logging::Logger l(logger);     // 3
    l.error(msg);                           // 4
}

}

BOOST_PYTHON_MODULE(log_test)
{
    bp::def("log_message", ::log_message);
}
