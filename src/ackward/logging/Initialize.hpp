#ifndef INCLUDE_ACKWARD_LOGGING_INITIALIZE_HPP
#define INCLUDE_ACKWARD_LOGGING_INITIALIZE_HPP

namespace ackward { 
namespace logging {

/** \rst 
    Initialize the ``ackward::logging`` library.

    This must be called before using any other part of
    ``ackward::logging``, including any Python type translators in the
    library.

    This also calls ``ackward::core::initialize()``.
    \endrst
 */
void initialize();

}
}

#endif
