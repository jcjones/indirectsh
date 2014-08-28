#ifndef _ICOMMANDPROCESSOR
#define _ICOMMANDPROCESSOR

#include <json.h>
#include "channel.hpp"

class ICommandProcessor
{
    public:
        virtual std::string commandName() = 0;
        virtual void processCommand(Channel*, json_object*) = 0;
        virtual ~ICommandProcessor() {};
};
#endif
