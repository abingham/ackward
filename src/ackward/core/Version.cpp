#include <ackward/core/Version.hpp>

namespace ackward {
namespace core {

VersionInfo::VersionInfo() :
    major_ (ACKWARD_MAJOR_VERSION),
    minor_ (ACKWARD_MINOR_VERSION)
{}

unsigned int VersionInfo::majorVersion() const {
    return major_;
}

unsigned int VersionInfo::minorVersion() const {
    return minor_;
}

VersionInfo versionInfo()
{
    return VersionInfo();
}

}
}
