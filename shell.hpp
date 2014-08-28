#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <vector>
#include <string>
#include <thread>
#include <ostream>

#include <unistd.h>
#include <stdio.h>

#include "channel.hpp"
#include "pipe.hpp"

class Shell
{
    public:
        void runCommand(std::string);
        void setChannel(Channel *);
        void spawnShell();
        void shellReaderThread();
    private:
        Pipe toChild;
        Pipe fromChild;
        Channel *channel;

        std::thread *readerThread;
};
#endif                           // _SHELL_HPP
