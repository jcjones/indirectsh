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

#include <string>
#include <sstream>
#include <iostream>

#include <unistd.h>
#include <stdio.h>
#include <vector>

#include <json.h>

#include "icommandprocessor.hpp"
#include "channel.hpp"
#include "shell.hpp"

/** This Processor opens a shell and waits for commands. Sample command would be: 
  * {"command":"shell", "in":"uptime\n"} */
class ShellProcessor : public ICommandProcessor
{
    public:
        ShellProcessor(Channel *);
        void processCommand(Channel *, json_object *);

        std::string commandName();
    private:
        Shell shell_;

};
