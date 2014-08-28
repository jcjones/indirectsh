#ifndef _CHANNEL_HPP
#define _CHANNEL_HPP

#include <vector>
#include <string>

#include <pubnub.hpp>
#include <pubnub-sync.hpp>

class Channel
{
    public:
        Channel();
        json_object *getMessage();
        void sendMessage(json_object *);
    private:
        PubNub *pubnub;
        pubnub_sync *sync;
};
#endif                           // _CHANNEL_HPP
