#ifndef INCLUDE_BA_LOG_TYPES_HPP
#define INCLUDE_BA_LOG_TYPES_HPP

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
