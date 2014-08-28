#include <string>
#include <sstream>
#include <iostream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <json.h>

#include "channel.hpp"
#include "icommandprocessor.hpp"

class IpLocation: public ICommandProcessor
{
    public:
        std::string commandName();
        void processCommand(Channel *channel, json_object *data);

    private:
        void get_ip(json_object *data);
};
