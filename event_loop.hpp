#include <iostream>
#include <string>
#include <vector>
#include <memory>

#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>

#include <json.h>

#include <pubnub.hpp>
#include <pubnub-sync.hpp>

#include "channel.hpp"
#include "icommandprocessor.hpp"

class EventLoop
{
    public:
        EventLoop();
        int mainLoop();
        void processMessage(json_object *);

        void setChannel(Channel *);
        void addProcessor(ICommandProcessor *);
    private:
        Channel *channel;
        std::vector<ICommandProcessor*> commandProcessors;
};
