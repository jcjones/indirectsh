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

#include "shell_cmd.hpp"

ShellProcessor::ShellProcessor(Channel *channel) {
    this->shell_.setChannel(channel);
    this->shell_.spawnShell();
}


std::string ShellProcessor::commandName() {
    return "shell";
}


void ShellProcessor::processCommand(Channel *channel, json_object *data) {
    json_object *input;

    if (json_object_object_get_ex(data, "in", &input)) {
        const char* cmdString = json_object_get_string(input);

        std::cout << "Got command of " << cmdString << std::endl;

        this->shell_.runCommand(std::string(cmdString));
    }
}
