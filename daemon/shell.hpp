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

#ifndef _SHELL_HPP
#define _SHELL_HPP

#include <vector>
#include <string>
#include <thread>
#include <ostream>

#include <unistd.h>
#include <stdio.h>

#include "ichannel.hpp"
#include "pipe.hpp"

/** This class encapsulates a shell, such as BASH or ZSH. You send it commands 
  * with runCommand() and it will write the output to the Channel provided. 
  * 
  * This class forks the shell into a child process, and then it spawns a thread
  * to read the stdout from that child process.
  */
class Shell
{
    public:
        void runCommand(std::string);
        void setChannel(Channel *);
        void spawnShell();
        void shellReaderThread();
    private:
        Pipe toChild_;
        Pipe fromChild_;
        Channel *channel_;

        std::thread *readerThread_;
};
#endif                           // _SHELL_HPP
