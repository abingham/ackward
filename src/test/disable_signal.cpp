#include "disable_signal.hpp"

DisableSignal::DisableSignal(int sig) :
    sig_ (sig)
{
    temp_.sa_handler = SIG_IGN;
    sigemptyset(&temp_.sa_mask);
    temp_.sa_flags = 0;
    sigaction(sig_, &temp_, &orig_);
}

DisableSignal::~DisableSignal()
{
    sigaction(sig_, &orig_, 0x00);
}
