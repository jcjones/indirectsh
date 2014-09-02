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

#include <string>
#include <fstream>
#include <streambuf>
#include <system_error>

#include "config.hpp"

Config::Config() {
    std::ifstream t;

    t.open("ishrc.json");
    if (!t.is_open()) {
        std::string homepath = std::string(getenv("HOME"));

        t.open(homepath + "/.ishrc.json");
    }
    if (!t.is_open()) {
        throw std::logic_error("Could not load configuration file.");
    }

    std::string str((std::istreambuf_iterator<char>(t)),
                             std::istreambuf_iterator<char>());
    database_ = json_tokener_parse(str.c_str());
}

std::string Config::getConfig(std::string module, std::string key) {
    json_object *moduleObj, *keyValue;

    /* Obtain the module structure */
    if (json_object_object_get_ex(database_, module.c_str(), &moduleObj)) {
        /* Obtain the key from the module structure */
        if (json_object_object_get_ex(moduleObj, key.c_str(), &keyValue)) {
            return std::string(json_object_get_string(keyValue));
        }

    }

    throw std::logic_error("Configuration missing: " + key);
}

std::string Config::getConfig(std::string module, std::string key, std::string def) {
    json_object *moduleObj, *keyValue;

    /* Obtain the module structure */
    if (json_object_object_get_ex(database_, module.c_str(), &moduleObj)) {
        /* Obtain the key from the module structure */
        if (json_object_object_get_ex(moduleObj, key.c_str(), &keyValue)) {
            return std::string(json_object_get_string(keyValue));
        }

    }

    return def;
}
