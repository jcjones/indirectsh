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

#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <json.h>

#include "channel.hpp"
#include "icommandprocessor.hpp"

/** A simple command that queries for the external IP address and returns it. 
  * An example query would be {"command":"ip"} */
class IpLocation: public ICommandProcessor
{
    public:
        /** The command name is ip */
        std::string commandName();
        /** Return a structure representing the IP location */
        void processCommand(Channel *channel, json_object *data);

    private:
        /** Perform a remote lookup of our IP location. */
        void get_ip(json_object *data);        
};
