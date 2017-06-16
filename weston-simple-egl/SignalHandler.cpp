#include "SignalHandler.h"

#include <cerrno>
#include <cstring>
#include <iostream>

using namespace std;

SignalHandler::SignalHandler()
    : _oldMask()
{
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_BLOCK, &mask, &_oldMask);
}

SignalHandler::~SignalHandler()
{
    sigprocmask(SIG_BLOCK, &_oldMask, nullptr);
}

bool SignalHandler::CheckSignal(int signal)
{
    sigset_t activeSignals;
    if (sigpending(&activeSignals))
    {
        cerr << "Could not check signals: " <<  strerror(errno) << "(" << errno << ")" << endl;
        exit(EXIT_FAILURE);
    }
    int errorCode = sigismember(&activeSignals, signal);
    if (errorCode < 0)
    {
        cerr << "Could not check signals: " <<  strerror(errno) << "(" << errno << ")" << endl;
        exit(EXIT_FAILURE);
    }
    return (errorCode == 1);
}
