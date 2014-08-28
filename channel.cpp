#include <system_error>
#include <iostream>

#include "channel.hpp"

#include "pubnub_account.hpp"

Channel::Channel() {
    sync = pubnub_sync_init();
    pubnub = new PubNub(
        /* publish_key */ PUBLISH_KEY,
        /* subscribe_key */ SUBSCRIBE_KEY,
        /* pubnub_callbacks */ &pubnub_sync_callbacks,
        /* pubnub_callbacks data */ sync);
}


void Channel::sendMessage(json_object *msg) {
    pubnub->publish(CHANNEL, /* message */ *msg);

    PubNub_sync_reply publish_reply = pubnub_sync_last_reply(sync);
    if (publish_reply.result() != PNR_OK)
        throw std::logic_error("PubNub publish failure.");

    std::cout << "pubnub publish ok: " << json_object_get_string(publish_reply.response()) << std::endl;
}


json_object *Channel::getMessage() {
    pubnub->subscribe(CHANNEL);

    PubNub_sync_reply subscribe_reply = pubnub_sync_last_reply(sync);
    if (subscribe_reply.result() != PNR_OK)
        throw std::logic_error("PubNub subscribe failure.");

    return subscribe_reply.response();
}
