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

#include "event_loop.hpp"

EventLoop::EventLoop() {
}


void EventLoop::setChannel(Channel *channel) {
    this->channel_ = channel;
}


void EventLoop::processMessage(json_object *msg) {
    json_object *cmd;

    if (json_object_object_get_ex(msg, "command", &cmd)) {
        const char* cmdString = json_object_get_string(cmd);

        for (auto & element : commandProcessors_) {
            if (element->commandName().compare(cmdString) == 0) {
                element->processCommand(this->channel_, msg);
                return;
            }
        }
        std::cout << "Unknown command: " << cmdString << std::endl;

    }
    else {
        std::cout << "Unknown message: " << json_object_get_string(msg) << std::endl;
    }

};

void EventLoop::addProcessor(ICommandProcessor *processor) {
    commandProcessors_.push_back(processor);
}


int EventLoop::mainLoop() {
    json_object *msg;

    /* Subscribe */
    do {
        msg = this->channel_->getMessage();
        if (json_object_array_length(msg) == 0) {
            std::cout << "pubnub subscribe ok, no news" << std::endl;
        }
        else {
            for (int i = 0; i < json_object_array_length(msg); i++) {
                json_object *msg1 = json_object_array_get_idx(msg, i);
                processMessage(msg1);
            }
        }
        #ifndef _MSC_VER
        sleep(1);
        #endif
    } while (1);

    return EXIT_SUCCESS;

}
