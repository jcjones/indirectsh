#include <unistd.h>
#include <stdio.h>
#include <system_error>

#include "pipe.hpp"

#define PIPE_READ  0
#define PIPE_WRITE 1

Pipe::Pipe() {
    if (0 != pipe(pipeArray)) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not open pipe.");
    }
}


int Pipe::getRead() {
    return pipeArray[PIPE_READ];
}


int Pipe::getWrite() {
    return pipeArray[PIPE_WRITE];
}


void Pipe::closeAll() {
    this->closeRead();
    this->closeWrite();
}


void Pipe::closeRead() {
    if (-1 == pipeArray[PIPE_WRITE]) {
        throw std::logic_error("Pipe is already closed.");
    }

    if (0 != close(pipeArray[PIPE_READ])) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not close read pipe.");
    }
    pipeArray[PIPE_READ] = -1;
}


void Pipe::closeWrite() {
    if (-1 == pipeArray[PIPE_WRITE]) {
        throw std::logic_error("Pipe is already closed.");
    }

    if (0 != close(pipeArray[PIPE_WRITE])) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not close write pipe.");
    }
    pipeArray[PIPE_WRITE] = -1;
}
