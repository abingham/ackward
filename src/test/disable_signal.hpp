#include <csignal>

struct DisableSignal
{
    struct sigaction temp_;
    struct sigaction orig_;
    int sig_;

    DisableSignal(int sig);
    ~DisableSignal();
};
