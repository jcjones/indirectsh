#include <iostream>
#include <string>
#include <vector>
#include <memory>

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>

#include <json.h>

#include "channel.hpp"
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
    Channel *channel = new Channel();

    loop.setChannel(channel);

    loop.addProcessor(new Me());
    loop.addProcessor(new IpLocation());
    loop.addProcessor(new ShellProcessor(channel));

    return loop.mainLoop();
}
