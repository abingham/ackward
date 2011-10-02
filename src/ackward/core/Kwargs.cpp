#include <ackward/core/Kwargs.hpp>

namespace ackward {
namespace core {

const boost::python::dict Kwargs::getDict() const
{
    return d_;
}


}
}
