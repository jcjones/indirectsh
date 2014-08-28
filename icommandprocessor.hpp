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

#ifndef _ICOMMANDPROCESSOR
#define _ICOMMANDPROCESSOR

#include <json.h>
#include "channel.hpp"

/** Interface defining a Class that processes commands arriving on the Channel 
 *  in JSON format. Commands must have a name that matches the JSON data's 
 *  "command" field. */
class ICommandProcessor
{
    public:
        /** Must return a string that matches the "command" field in the JSON data */
        virtual std::string commandName() = 0;
        /** Is called by EventLoop when a matching JSON data is found, and is given 
         *  the Channel to make writes. */
        virtual void processCommand(Channel*, json_object*) = 0;

        virtual ~ICommandProcessor() {};
};
#endif
