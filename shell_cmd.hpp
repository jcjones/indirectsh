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

class ShellProcessor : public ICommandProcessor
{
    public:
        ShellProcessor(Channel *);
        void processCommand(Channel *, json_object *);

        std::string commandName();
    private:
        Shell shell;
};
