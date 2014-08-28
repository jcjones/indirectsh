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

#ifndef _PIPE_HPP
#define _PIPE_HPP

#include <unistd.h>
#include <stdio.h>

/** Represents a UNIX pipe with a read and write side. */
class Pipe
{
    public:
        Pipe();
        ~Pipe();
        /** Returns the file descriptor for the read side. 
          * If the descriptor is closed, this routine throws an exception. */ 
        int getReadFd();
        /** Returns the file descriptor for the write side. 
          * If the descriptor is closed, this routine throws an exception. */
        int getWriteFd();
        /** Closes the write side. */
        void closeWrite();
        /** Closes the read side. */
        void closeRead();
        /** Closes both sides; like calling closeRead() and closeWrite(). */
        void closeAll();
    private:
        int pipeArray_[2];
};
#endif                           // _PIPE_HPP
