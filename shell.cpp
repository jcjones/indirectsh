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
#include <vector>
#include <iostream>
#include <functional>
#include <system_error>
#include <chrono>

#include "shell.hpp"

void Shell::shellReaderThread() {
    char buffer[2048];
    int count;
    json_object *output;

    // Forever, read from the pipe
    while(true) {
        count = read(this->fromChild_.getReadFd(), buffer, sizeof(buffer));

        if (0 > count) {
            std::error_code ec (errno ,std::generic_category());
            throw std::system_error(ec, "Could not read from pipe.");
        }

        // allocate
        output = json_object_new_object();

        json_object_object_add(output, "out", json_object_new_string_len(buffer, count));

        this->channel_->sendMessage(output);

        // deallocate
        json_object_put(output);
    }
}


void Shell::setChannel(Channel *chan) {
    this->channel_ = chan;
}


void Shell::spawnShell() {

    if(!fork()) {
        std::vector<char*> args;
        args.push_back((char*)"/bin/bash");
        args.push_back(0);

        dup2(this->toChild_.getReadFd(), STDIN_FILENO);
        dup2(this->fromChild_.getWriteFd(), STDOUT_FILENO);

        // Close all file descriptors that aren't needed by the child.
        this->toChild_.closeAll();
        this->fromChild_.closeAll();

        // Child runs forever!
        execv(args[0], &args.front());
    }
    else {
        // Close the portions unneeded by the parent
        this->fromChild_.closeWrite();
        this->toChild_.closeRead();

        std::cout << "Starting thread " << std::endl;
        this->readerThread_ = new std::thread(&Shell::shellReaderThread, this);
    }
}


void Shell::runCommand(std::string command) {
    // Ensure we end with a newline
    if (command.back() != '\n') {
        std::cout << "No newline... remove my log entry when that's OK" << std::endl;
    }

    // Write to childs stdin
    if (0 > write(this->toChild_.getWriteFd(), command.c_str(), command.length())) {
        std::error_code ec (errno,std::generic_category());
        throw std::system_error(ec, "Could not write to pipe.");
    }
}
