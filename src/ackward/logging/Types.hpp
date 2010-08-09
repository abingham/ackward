#ifndef INCLUDE_ACKWARD_LOGGING_TYPES_HPP
#define INCLUDE_ACKWARD_LOGGING_TYPES_HPP

namespace ackward { namespace logging 
{

typedef int Level;

Level DEBUG();
Level INFO();
Level WARNING();
Level ERROR();
Level CRITICAL();

}}

#endif
