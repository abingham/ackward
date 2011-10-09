#ifndef INCLUDE_ACKWARD_CORE_VERSION_HPP
#define INCLUDE_ACKWARD_CORE_VERSION_HPP

/** The major version of the ackward library. */
#define ACKWARD_MAJOR_VERSION 0

/** The minor version of the ackward library. */
#define ACKWARD_MINOR_VERSION 5

namespace ackward {
namespace core {

/** A class containing major and minor version information.
 */
class VersionInfo
{
public:
    VersionInfo();

    /** Get the major version. */
    unsigned int majorVersion() const;

    /** Get the minor version. */
    unsigned int minorVersion() const;

private:
    unsigned int major_;
    unsigned int minor_;
};

/** \rst

    Get a ``VersionInfo`` containing the version of ``ackward``.

    \endrst
*/
VersionInfo versionInfo();

}
}

#endif /* INCLUDE_ACKWARD_CORE_VERSION_HPP */
