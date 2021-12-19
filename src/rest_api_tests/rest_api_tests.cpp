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
