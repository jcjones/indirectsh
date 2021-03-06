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

#include <system_error>
#include <iostream>

#include "pubnub_channel.hpp"

PubnubChannel::PubnubChannel(std::string subkey, std::string pubkey, std::string channel) {
    channel_ = channel;
    sync_ = pubnub_sync_init();
    pubnub_ = new PubNub(
        /* publish_key */ pubkey,
        /* subscribe_key */ subkey,
        /* pubnub_callbacks */ &pubnub_sync_callbacks,
        /* pubnub_callbacks data */ sync_);
}


void PubnubChannel::sendMessage(json_object *msg) {
    pubnub_->publish(channel_, /* message */ *msg);

    PubNub_sync_reply publish_reply = pubnub_sync_last_reply(sync_);
    if (publish_reply.result() != PNR_OK)
        throw std::logic_error("PubNub publish failure.");

    std::cout << "pubnub publish ok: " << json_object_get_string(publish_reply.response()) << std::endl;
}


json_object *PubnubChannel::getMessage() {
    pubnub_->subscribe(channel_);

    PubNub_sync_reply subscribe_reply = pubnub_sync_last_reply(sync_);
    if (subscribe_reply.result() != PNR_OK)
        throw std::logic_error("PubNub subscribe failure.");

    return subscribe_reply.response();
}
