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

#include "ip_location_cmd.hpp"

#define API_URL "http://ip-api.com/json"

std::string IpLocation::commandName() { return "ip"; }

void IpLocation::processCommand(Channel *channel, json_object *data) {
    json_object *msg;
    msg = json_object_new_object();

    this->get_ip(msg);

    channel->sendMessage(msg);

    /* deallocate */
    json_object_put(msg);
}


void IpLocation::get_ip(json_object *data) {
    try
    {
        curlpp::Cleanup myCleanup;
        std::ostringstream os;
        os << curlpp::options::Url(API_URL);

        json_object* ipData;
        ipData = json_tokener_parse(os.str().c_str());

        json_object_object_add(data, "ip", ipData);
    }

    catch( curlpp::RuntimeError &e ) {
        std::cout << e.what() << std::endl;
    }

    catch( curlpp::LogicError &e ) {
        std::cout << e.what() << std::endl;
    }
};
