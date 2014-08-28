#include "ip_location_cmd.hpp"

#define API_URL "http://ip-api.com/json"

std::string IpLocation::commandName() { return "ip"; }

void IpLocation::processCommand(Channel *channel, json_object *data) {
    json_object *msg;
    msg = json_object_new_object();

    json_object_object_add(msg, "num", json_object_new_int(42));
    json_object_object_add(msg, "str", json_object_new_string("Online."));
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
