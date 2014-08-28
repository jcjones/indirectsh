/*
 * Copyright 2014 James 'J.C.' Jones <pug@pugsplace.net>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <stdio.h>
#include <system_error>

#include "pipe.hpp"

#define PIPE_READ  0
#define PIPE_WRITE 1

Pipe::Pipe() {
    if (0 != pipe(pipeArray_)) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not open pipe.");
    }
}

Pipe::~Pipe() {
    this->closeAll();
}


int Pipe::getReadFd() {
    if (-1 == pipeArray_[PIPE_READ]) {
        throw std::logic_error("Pipe is already closed.");
    }

    return pipeArray_[PIPE_READ];
}


int Pipe::getWriteFd() {
    if (-1 == pipeArray_[PIPE_WRITE]) {
        throw std::logic_error("Pipe is already closed.");
    }

    return pipeArray_[PIPE_WRITE];
}


void Pipe::closeAll() {
    this->closeRead();
    this->closeWrite();
}


void Pipe::closeRead() {
    if (-1 == pipeArray_[PIPE_WRITE]) {
        /* Pipe is already closed. */
        return;
    }

    if (0 != close(pipeArray_[PIPE_READ])) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not close read pipe.");
    }
    pipeArray_[PIPE_READ] = -1;
}


void Pipe::closeWrite() {
    if (-1 == pipeArray_[PIPE_WRITE]) {
        /* Pipe is already closed. */
        return;
    }

    if (0 != close(pipeArray_[PIPE_WRITE])) {
        std::error_code ec (errno, std::generic_category());
        throw std::system_error(ec, "Could not close write pipe.");
    }
    pipeArray_[PIPE_WRITE] = -1;
}
