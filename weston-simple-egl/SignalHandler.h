#pragma once

#include <csignal>

class SignalHandler
{
public:
    SignalHandler();
    ~SignalHandler();

    bool CheckSignal(int signal);

private:
    sigset_t _oldMask;
};
