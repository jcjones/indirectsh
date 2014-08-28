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

#include "ichannel.hpp"
#include "icommandprocessor.hpp"

/** This is the shell loop processor; its' mainLoop() method runs until a shutdown is requested. */
class EventLoop
{
    public:
        EventLoop();
	/** Run forever. Never surrender. */
        int mainLoop();

	/** Sets the Channel to use. */
        void setChannel(Channel *);

	/** Adds a new Command Processor to the list of those consulted in processMessage(). */
        void addProcessor(ICommandProcessor *);
    private:
	/** Channel in use */
        Channel *channel_;

	/** List of processors; you can add to it with addProcessor() */
        std::vector<ICommandProcessor*> commandProcessors_;

	/** Decode a message and provide it to the appropriate CommandProcessor. */
        void processMessage(json_object *);

};
