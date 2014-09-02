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

#ifndef _PUBNUB_CHANNEL_HPP
#define _PUBNUB_CHANNEL_HPP

#include <vector>
#include <string>

#include <pubnub.hpp>
#include <pubnub-sync.hpp>

#include "ichannel.hpp"

/** Interface defining a communication channel to/from clients. */
class PubnubChannel : public Channel
{
    public:
        PubnubChannel(std::string subkey, std::string pubkey, std::string channel);
	/** Obtain a message from a client; this method will block until a message arrives. */
        json_object *getMessage();
	/** Send a message to a client; this method will block until the channel accepts the message. */
        void sendMessage(json_object *);
    private:
        PubNub *pubnub_;
        pubnub_sync *sync_;
        std::string channel_;
};
#endif                           // _PUBNUB_CHANNEL_HPP
