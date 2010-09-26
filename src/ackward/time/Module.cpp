#include <ackward/time/Module.hpp>

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>

#include <ackward/core/Exceptions.hpp>

using namespace boost::python;

namespace ackward { namespace time
{

#include <ackward/time/Module_akw.ipp>

}}
