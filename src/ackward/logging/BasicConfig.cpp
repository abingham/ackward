#include <ackward/logging/BasicConfig.hpp>

#include <boost/python/tuple.hpp>

#include <ackward/core/ExceptionTranslation.hpp>
#include <ackward/core/Kwargs.hpp>
#include <ackward/logging/Module.hpp>

namespace ackward {
namespace logging {

void basicConfig()
{
    try {
        module().attr("basicConfig")();
    } TRANSLATE_PYTHON_EXCEPTION();
}

void basicConfig(const core::Kwargs& args)
{
    try {
        module().attr("basicConfig")(
            *boost::python::tuple(),
            **args.getDict());
    } TRANSLATE_PYTHON_EXCEPTION();
}

}
}
