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
#include <libKitsunemimiJson/json_item.h>

#include <libKitsunemimiHanamiSdk/common/http_client.h>

#include <common/test_thread.h>

#include <rest_api_tests/misaka/user_create_test.h>
#include <rest_api_tests/misaka/user_delete_test.h>
#include <rest_api_tests/misaka/user_get_test.h>
#include <rest_api_tests/misaka/user_list_test.h>

#include <rest_api_tests/sagiri/dataset_create_mnist_test.h>
#include <rest_api_tests/sagiri/dataset_delete_test.h>
#include <rest_api_tests/sagiri/dataset_get_test.h>
#include <rest_api_tests/sagiri/dataset_list_test.h>
#include <rest_api_tests/sagiri/dataset_check_test.h>

#include <rest_api_tests/kyouko/cluster/cluster_create_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_delete_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_get_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_list_test.h>

#include <rest_api_tests/kyouko/template/template_create_test.h>
#include <rest_api_tests/kyouko/template/template_delete_test.h>
#include <rest_api_tests/kyouko/template/template_get_test.h>
#include <rest_api_tests/kyouko/template/template_list_test.h>

#include <rest_api_tests/kyouko/task/learn_task_test.h>
#include <rest_api_tests/kyouko/task/request_task_test.h>

/**
 * @brief initialize client by requesting a token, which is used for all tests
 */
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

/**
 * @brief runRestApiTests
 */
bool
runRestApiTests()
{
    bool success = false;

    if(initClient() == false) {
        return false;
    }

    Kitsunemimi::Json::JsonItem inputData;
    inputData.insert("password", "new password");
    inputData.insert("admin", true);
    inputData.insert("roles", "tester");
    inputData.insert("projects", "tester");

    inputData.insert("learn_inputs", GET_STRING_CONFIG("test_data", "learn_inputs", success)),
    inputData.insert("learn_labels", GET_STRING_CONFIG("test_data", "learn_labels", success)),
    inputData.insert("request_inputs", GET_STRING_CONFIG("test_data", "request_inputs", success)),
    inputData.insert("request_labels", GET_STRING_CONFIG("test_data", "request_labels", success)),

    inputData.insert("user_name", "tsugumi");
    inputData.insert("cluster_name", "test_cluster");
    inputData.insert("template_name", "test_template");
    inputData.insert("request_dataset_name", "request_test_dataset");
    inputData.insert("learn_dataset_name", "learn_test_dataset");


    TestThread testThread("test_thread", inputData);

    Kitsunemimi::Json::JsonItem overrideData;
    /*testThread.addTest(new UserCreateTest(true));
    testThread.addTest(new UserCreateTest(false));
    testThread.addTest(new UserListTest(true));
    testThread.addTest(new UserGetTest(true));
    testThread.addTest(new UserGetTest(false, "fail_user"));
    testThread.addTest(new UserDeleteTest(true));
    testThread.addTest(new UserDeleteTest(false));*/

    testThread.addTest(new DataSetCreateMnistTest(true, "request"));

    testThread.addTest(new DataSetCreateMnistTest(true, "learn"));
    testThread.addTest(new DataSetListTest(true));
    testThread.addTest(new DataSetGetTest(true, "learn" ));
    //testThread.addTest(new DataSetGetTest(false, "learn", "fail_user"));

    testThread.addTest(new TemplateCreateTest( true));
    testThread.addTest(new TemplateGetTest(true));
    testThread.addTest(new TemplateListTest(true));


    testThread.addTest(new ClusterCreateTest(true));
    testThread.addTest(new ClusterGetTest(true));
    testThread.addTest(new ClusterListTest(true));

    for(int i = 0; i < 2; i++) {
        testThread.addTest(new LearnTaskTest(true));
    }
    testThread.addTest(new RequestTaskTest(true));
    testThread.addTest(new DataSetCheckTest(true));

    testThread.addTest(new ClusterDeleteTest(true));
    testThread.addTest(new ClusterDeleteTest(false));
    testThread.addTest(new TemplateDeleteTest(true));
    testThread.addTest(new TemplateDeleteTest(false));
    testThread.addTest(new DataSetDeleteTest(true, "request"));
    testThread.addTest(new DataSetDeleteTest(true, "learn"));
    testThread.addTest(new DataSetDeleteTest(false, "learn"));

    testThread.startThread();

    while(testThread.isFinished == false) {
        usleep(100000);
    }

    return true;
}
