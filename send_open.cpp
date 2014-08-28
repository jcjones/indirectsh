#include <iostream>
#include <string>
#include <vector>
#ifndef _MSC_VER
#include <unistd.h>
#endif
#include <stdlib.h>

#include <json.h>

#include "pubnub.hpp"
#include "pubnub-sync.hpp"

#include "pubnub_account.hpp"

int
main() {
    pubnub_sync *sync = pubnub_sync_init();
    PubNub p(
        /* publish_key */ PUBLISH_KEY,
        /* subscribe_key */ SUBSCRIBE_KEY,
        /* pubnub_callbacks */ &pubnub_sync_callbacks,
        /* pubnub_callbacks data */ sync);
    json_object *msg;

    /* Publish */

    msg = json_object_new_object();
    json_object_object_add(msg, "num", json_object_new_int(42));
    json_object_object_add(msg, "str", json_object_new_string("Online."));
    p.publish(/* channel */ "my_channel", /* message */ *msg);
    json_object_put(msg);

    PubNub_sync_reply publish_reply = pubnub_sync_last_reply(sync);
    if (publish_reply.result() != PNR_OK)
        return EXIT_FAILURE;
    std::cout << "pubnub publish ok: " << json_object_get_string(publish_reply.response()) << std::endl;

    /* Subscribe */

    do {
        std::vector<std::string> channels;
        channels.push_back("my_channel");
        channels.push_back("demo_channel");

        p.subscribe_multi(/* list of channels */ channels);

        PubNub_sync_reply subscribe_reply = pubnub_sync_last_reply(sync);
        if (subscribe_reply.result() != PNR_OK)
            return EXIT_FAILURE;
        msg = subscribe_reply.response();
        if (json_object_array_length(msg) == 0) {
            std::cout << "pubnub subscribe ok, no news" << std::endl;
        }
        else {
            for (int i = 0; i < json_object_array_length(msg); i++) {
                json_object *msg1 = json_object_array_get_idx(msg, i);
                std::cout << "pubnub subscribe ["
                    << subscribe_reply.channels()[i]
                    << "]: " << json_object_get_string(msg1)
                    << std::endl;
            }
        }
        #ifndef _MSC_VER
        sleep(1);
        #endif
    } while (1);

    return EXIT_SUCCESS;
}
