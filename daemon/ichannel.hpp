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

#ifndef _CHANNEL_HPP
#define _CHANNEL_HPP

#include <vector>
#include <string>
#include <json.h>

/** Interface defining a communication channel to/from clients. */
class Channel
{
    public:
	/** Obtain a message from a client; this method will block until a message arrives. */
        virtual json_object *getMessage() = 0;
	/** Send a message to a client; this method will block until the channel accepts the message. */
        virtual void sendMessage(json_object *) = 0;

        virtual ~Channel() {};
    private:
};
#endif                           // _CHANNEL_HPP
