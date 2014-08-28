#ifndef _PIPE_HPP
#define _PIPE_HPP

#include <unistd.h>
#include <stdio.h>

class Pipe
{
    public:
        Pipe();
        int getRead();
        int getWrite();
        void closeWrite();
        void closeRead();
        void closeAll();
    private:
        int pipeArray[2];
};
#endif                           // _PIPE_HPP
