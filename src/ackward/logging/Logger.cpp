#include <ackward/logging/Logger.hpp>

namespace ackward { namespace logging {

Logger::Logger(boost::python::object l) :
    LoggerBase (l)
{}

Logger::Filters Logger::filters()
{
    return Filters(obj().attr("filters"));
}

Logger::ConstFilters Logger::filters() const
{
    return ConstFilters(obj().attr("filters"));
}

Logger::Handlers Logger::handlers()
{
    return Handlers(obj().attr("handlers"));
}

Logger::ConstHandlers Logger::handlers() const
{
    return ConstHandlers(obj().attr("handlers"));
}

}}
