#ifndef INCLUDE_ACKWARD_LOGGING_TYPES_HPP
#define INCLUDE_ACKWARD_LOGGING_TYPES_HPP

namespace ackward { 
namespace logging {

/** A logging level.
 */
typedef int Level;

/** \rst
    Wrapper for Python's ``logging.DEBUG``. 
    \endrst
*/
Level DEBUG();

/** \rst
    Wrapper for Python's ``logging.INFO``. 
    \endrst
*/
Level INFO();

/** \rst
    Wrapper for Python's ``logging.WARNING``. 
    \endrst
*/
Level WARNING();

/** \rst
    Wrapper for Python's ``logging.ERROR``. 
    \endrst
*/
Level ERROR();

/** \rst
    Wrapper for Python's ``logging.CRITICAL``. 
    \endrst
*/
Level CRITICAL();

}
}

#endif
