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

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>

#include <json.h>

#include "pubnub_channel.hpp"
#include "event_loop.hpp"

#include "ip_location_cmd.hpp"
#include "shell_cmd.hpp"

class Me: public ICommandProcessor
{
    void processCommand(Channel *channel, json_object *msg) {
        std::cout << "Me! " << json_object_get_string(msg) << " OK " << std::endl;

        json_object *cmd;
        if (json_object_object_get_ex(msg, "command", &cmd)) {
            std::cout << "Got command :" << json_object_get_string(cmd) << std::endl;
        }
    }

    std::string commandName() {
        return "test";
    }
};

int main() {
    EventLoop loop;
    Channel *channel = new PubnubChannel();

    loop.setChannel(channel);

    loop.addProcessor(new Me());
    loop.addProcessor(new IpLocation());
    loop.addProcessor(new ShellProcessor(channel));

    return loop.mainLoop();
}
