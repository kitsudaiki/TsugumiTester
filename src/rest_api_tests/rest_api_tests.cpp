/**
 * @file        rest_api_tests.cpp
 *
 * @author      Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2021 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include "rest_api_tests.h"

#include <libKitsunemimiConfig/config_handler.h>

#include <libKitsunemimiHanamiSdk/common/hanami_request.h>

#include <rest_api_tests/misaka/user_tests.h>

bool
initClient()
{
    bool success = false;
    const std::string host = GET_STRING_CONFIG("connection", "host", success);
    const std::string port = std::to_string(GET_INT_CONFIG("connection", "port", success));
    const std::string user = GET_STRING_CONFIG("connection", "test_user", success);
    const std::string pw = GET_STRING_CONFIG("connection", "test_pw", success);

    Kitsunemimi::Hanami::HanamiRequest* request = Kitsunemimi::Hanami::HanamiRequest::getInstance();
    if(request->init(host, port, user, pw) == false) {
        return false;
    }

    return true;
}

bool
testMisaka()
{
    std::cout<<"test users"<<std::endl;
    UserTests userTests;
    if(userTests.runTest() == false)
    {
        std::cout<<"test users failed"<<std::endl;
        return false;
    }

    return true;
}

bool
runRestApiTests()
{
    if(initClient() == false) {
        return false;
    }

    std::cout<<"test misaka"<<std::endl;
    if(testMisaka() == false)
    {
        return false;
    }

    return true;
}
