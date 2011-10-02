#ifndef INCLUDE_ACKWARD_LOGGING_BASIC_CONFIG_HPP
#define INCLUDE_ACKWARD_LOGGING_BASIC_CONFIG_HPP

#include <ackward/core/Kwargs.hpp>

namespace ackward {
namespace logging {

/** The default version of `logging.basicConfig()`.
 */
void basicConfig();

/** A version of `basicConfig` that takes keyword arguments.

    The following keywords are supported:

      filename - Specifies that a FileHandler be created, using the
                 specified filename, rather than a StreamHandler.

      filemode - Specifies the mode to open the file, if filename is
                 specified (if filemode is unspecified, it defaults to
                 ‘a’).

      format - Use the specified format string for the handler.

      datefmt - Use the specified date/time format.

      level - Set the root logger level to the specified level.

      stream - Use the specified stream to initialize the
               StreamHandler. Note that this argument is incompatible
               with ‘filename’ - if both are present, ‘stream’ is
               ignored.
 */
void basicConfig(const ackward::core::Kwargs&);

}
}

#endif /* INCLUDE_ACKWARD_LOGGING_BASIC_CONFIG_HPP */
