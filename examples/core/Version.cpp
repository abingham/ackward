#include <ackward/core/Version.hpp>

using namespace ackward::core;

int main(int, char**)
{
#if ACKWARD_MAJOR_VERSION < 1
// probably not ready for prime-time!
#else
// Feel free to use this code to perform brain surgery while launching a space shuttle.
#endif

    // Get the current version info.
    VersionInfo info = versionInfo();

    // Return the major version.
    return info.majorVersion();
}
