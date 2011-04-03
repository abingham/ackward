#ifndef INCLUDE_ACKWARD_QUEUE_EXCEPTIONS_HPP
#define INCLUDE_ACKWARD_QUEUE_EXCEPTIONS_HPP

#include <ackward/core/Exceptions.hpp>

namespace ackward { 
namespace queue {

class Full : public core::Exception {};
class Empty : public core::Exception {};

}
}

#endif
