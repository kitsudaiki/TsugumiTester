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
#include <libKitsumiAiSdk/init.h>

#include <common/test_thread.h>
#include <libKitsumiAiSdk/template.h>

#include <rest_api_tests/misaki/project/project_create_test.h>
#include <rest_api_tests/misaki/project/project_delete_test.h>
#include <rest_api_tests/misaki/project/project_get_test.h>
#include <rest_api_tests/misaki/project/project_list_test.h>

#include <rest_api_tests/misaki/user/user_create_test.h>
#include <rest_api_tests/misaki/user/user_delete_test.h>
#include <rest_api_tests/misaki/user/user_get_test.h>
#include <rest_api_tests/misaki/user/user_list_test.h>

#include <rest_api_tests/sagiri/datasets/dataset_create_mnist_test.h>
#include <rest_api_tests/sagiri/datasets/dataset_create_csv_test.h>
#include <rest_api_tests/sagiri/datasets/dataset_delete_test.h>
#include <rest_api_tests/sagiri/datasets/dataset_get_test.h>
#include <rest_api_tests/sagiri/datasets/dataset_list_test.h>
#include <rest_api_tests/sagiri/datasets/dataset_check_test.h>

#include <rest_api_tests/sagiri/snapshots/snapshot_delete_test.h>
#include <rest_api_tests/sagiri/snapshots/snapshot_get_test.h>
#include <rest_api_tests/sagiri/snapshots/snapshot_list_test.h>

#include <rest_api_tests/kyouko/cluster/cluster_create_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_delete_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_get_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_list_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_save_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_load_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_switch_to_direct_test.h>
#include <rest_api_tests/kyouko/cluster/cluster_switch_to_task_test.h>

#include <rest_api_tests/kyouko/io/direct_io_test.h>

#include <rest_api_tests/kyouko/template/template_generate_test.h>
#include <rest_api_tests/kyouko/template/template_upload_test.h>
#include <rest_api_tests/kyouko/template/template_delete_test.h>
#include <rest_api_tests/kyouko/template/template_get_test.h>
#include <rest_api_tests/kyouko/template/template_list_test.h>

#include <rest_api_tests/kyouko/task/image_learn_task_test.h>
#include <rest_api_tests/kyouko/task/image_request_task_test.h>
#include <rest_api_tests/kyouko/task/graph_learn_task_test.h>
#include <rest_api_tests/kyouko/task/graph_request_task_test.h>

/**
 * @brief initialize client by requesting a token, which is used for all tests
 */
bool
initClient()
{
    Kitsunemimi::ErrorContainer error;

    bool success = false;
    const std::string host = GET_STRING_CONFIG("connection", "host", success);
    const std::string port = std::to_string(GET_INT_CONFIG("connection", "port", success));
    const std::string user = GET_STRING_CONFIG("connection", "test_user", success);
    const std::string pw = GET_STRING_CONFIG("connection", "test_pw", success);

    if(Kitsunemimi::Hanami::initClient(host, port, user, pw, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief delete all templates of the test-user to avoid name-conflics
 */
void
deleteTemplate()
{
    std::string result = "";
    Kitsunemimi::ErrorContainer error;
    Kitsunemimi::Hanami::listTemplate(result, error);

    Kitsunemimi::Json::JsonItem parsedList;
    parsedList.parse(result, error);

    Kitsunemimi::Json::JsonItem body = parsedList.get("body");
    for(uint64_t i = 0; i < body.size(); i++)
    {
        const std::string uuid = body.get(i).get(0).getString();
        Kitsunemimi::Hanami::deleteTemplate(result, uuid, error);
    }
}

/**
 * @brief run tests with the usage of MNIST-images
 *
 * @param inputData json-item with names and other predefined values for the tests
 */
void
runImageTest(Kitsunemimi::Json::JsonItem &inputData)
{
    deleteTemplate();

    TestThread testThread("test_thread", inputData);

    Kitsunemimi::Json::JsonItem overrideData;

    // test project in misaki
    testThread.addTest(new ProjectCreateTest(true));
    testThread.addTest(new ProjectCreateTest(false));
    testThread.addTest(new ProjectListTest(true));
    testThread.addTest(new ProjectGetTest(true));
    testThread.addTest(new ProjectGetTest(false, "fail_project"));

    // test user in misaki
    testThread.addTest(new UserCreateTest(true));
    testThread.addTest(new UserCreateTest(false));
    testThread.addTest(new UserListTest(true));
    testThread.addTest(new UserGetTest(true));
    testThread.addTest(new UserGetTest(false, "fail_user"));

    // test data-sets of sagiri
    testThread.addTest(new DataSetCreateMnistTest(true, "request"));
    testThread.addTest(new DataSetCreateMnistTest(true, "learn"));
    testThread.addTest(new DataSetListTest(true));
    testThread.addTest(new DataSetGetTest(true, "learn"));
    testThread.addTest(new DataSetGetTest(false, "learn", "fail_user"));

    // test templates of kyouko
    testThread.addTest(new TemplateUploadTest(true));
    testThread.addTest(new TemplateGetTest(true));
    testThread.addTest(new TemplateListTest(true));

    // test cluster of kyouko
    testThread.addTest(new ClusterCreateTest(true));
    testThread.addTest(new ClusterGetTest(true));
    testThread.addTest(new ClusterListTest(true));

    // test learning-tasks of kyouko
    for(int i = 0; i < 2; i++) {
        testThread.addTest(new ImageLearnTaskTest(true));
    }

    // test cluster load and restore of kyouko and sagiri
    testThread.addTest(new ClusterSaveTest(true));
    testThread.addTest(new ClusterDeleteTest(true));
    testThread.addTest(new ClusterCreateTest(true));
    testThread.addTest(new ClusterLoadTest(true));

    // test request-tasks of kyouko
    testThread.addTest(new ImageRequestTaskTest(true));
    testThread.addTest(new DataSetCheckTest(true));

    // test snapshots of sagiri
    testThread.addTest(new SnapshotGetTest(true));
    testThread.addTest(new SnapshotListTest(true));

    // test direct-io of kyouko
    testThread.addTest(new ClusterSwitchToDirectTest(true));
    testThread.addTest(new DirectIoTest(true));
    testThread.addTest(new ClusterSwitchToTaskTest(true));

    // test delete of all
    testThread.addTest(new UserDeleteTest(true));
    testThread.addTest(new UserDeleteTest(false));
    testThread.addTest(new ProjectDeleteTest(true));
    testThread.addTest(new ProjectDeleteTest(false));
    testThread.addTest(new SnapshotDeleteTest(true));
    testThread.addTest(new ClusterDeleteTest(true));
    testThread.addTest(new ClusterDeleteTest(false));
    testThread.addTest(new TemplateDeleteTest(true));
    testThread.addTest(new TemplateDeleteTest(false));
    testThread.addTest(new DataSetDeleteTest(true, "request"));
    testThread.addTest(new DataSetDeleteTest(true, "learn"));
    testThread.addTest(new DataSetDeleteTest(false, "learn"));

    // check that the running user can not delete himself
    bool success = false;
    const std::string user = GET_STRING_CONFIG("connection", "test_user", success);
    testThread.addTest(new UserDeleteTest(false, user));

    testThread.startThread();

    while(testThread.isFinished == false) {
        usleep(100000);
    }
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

    const std::string segmentTemplate = "{\n"
                                        "    \"version\": 1,\n"
                                        "    \"segment_type\": \"dynamic_segment\",\n"
                                        "    \"bricks\": [\n"
                                        "        {\n"
                                        "            \"number_of_nodes\": 784,\n"
                                        "            \"position\": [ 1, 1, 1 ],\n"
                                        "            \"type\": \"input\",\n"
                                        "            \"name\": \"test_input\"\n"
                                        "        },\n"
                                        "        {\n"
                                        "            \"number_of_nodes\": 300,\n"
                                        "            \"position\": [ 2, 1, 1 ]\n"
                                        "        },\n"
                                        "        {\n"
                                        "            \"number_of_nodes\": 10,\n"
                                        "            \"position\": [ 3, 1, 1 ],\n"
                                        "            \"type\": \"output\",\n"
                                        "            \"name\": \"test_output\"\n"
                                        "        }\n"
                                        "    ],\n"
                                        "    \"settings\": {\n"
                                        "        \"action_potential\": 5.0,\n"
                                        "        \"glia_value\": 1.1,\n"
                                        "        \"max_synapse_sections\": 100000,\n"
                                        "        \"max_synapse_weight\": 0.015,\n"
                                        "        \"memorizing\": 0.5,\n"
                                        "        \"node_cooldown\": 3000.0,\n"
                                        "        \"potential_overflow\": 1.0,\n"
                                        "        \"refraction_time\": 1,\n"
                                        "        \"sign_neg\": 0.5,\n"
                                        "        \"synapse_delete_border\": 0.0005\n"
                                        "    }\n"
                                        "}\n";
    const std::string clusterDefinition = "{\n"
                                          "    \"version\": 1,\n"
                                          "    \"segments\": [\n"
                                          "        {\n"
                                          "            \"type\":\"input\",\n"
                                          "            \"number_of_nodes\": 784,\n"
                                          "            \"name\": \"input1\",\n"
                                          "            \"out\": [\n"
                                          "                {\n"
                                          "                    \"target_segment\": \"central\",\n"
                                          "                    \"target_brick\": \"test_input\"\n"
                                          "                }\n"
                                          "            ]\n"
                                          "        },\n"
                                          "        {\n"
                                          "            \"type\":\"dynamic\",\n"
                                          "            \"name\": \"central\",\n"
                                          "            \"out\": [\n"
                                          "                {\n"
                                          "                    \"source_brick\": \"test_output\",\n"
                                          "                    \"target_segment\": \"output2\"\n"
                                          "                }\n"
                                          "            ]\n"
                                          "        },\n"
                                          "        {\n"
                                          "            \"type\": \"output\",\n"
                                          "            \"name\": \"output2\",\n"
                                          "            \"number_of_nodes\": 10\n"
                                          "        }\n"
                                          "    ]\n"
                                          "}\n";

    Kitsunemimi::Json::JsonItem inputData;

    // add data for the test-user to create
    inputData.insert("user_name", "tsugumi");
    inputData.insert("password", "new password");
    inputData.insert("admin", true);
    inputData.insert("roles", "tester");
    inputData.insert("projects", "tester");
    inputData.insert("project_name", "tester");

    // add data from config
    inputData.insert("learn_inputs", GET_STRING_CONFIG("test_data", "learn_inputs", success)),
    inputData.insert("learn_labels", GET_STRING_CONFIG("test_data", "learn_labels", success)),
    inputData.insert("request_inputs", GET_STRING_CONFIG("test_data", "request_inputs", success)),
    inputData.insert("request_labels", GET_STRING_CONFIG("test_data", "request_labels", success)),
    inputData.insert("base_inputs", GET_STRING_CONFIG("test_data", "base_inputs", success)),

    // add predefined names for the coming test-resources
    inputData.insert("cluster_name", "test_cluster");
    inputData.insert("cluster_snapshot_name", "test_snapshot");
    inputData.insert("template_name", "dynamic");
    inputData.insert("template_segment", segmentTemplate);
    inputData.insert("cluster_definition", clusterDefinition);
    inputData.insert("request_dataset_name", "request_test_dataset");
    inputData.insert("learn_dataset_name", "learn_test_dataset");
    inputData.insert("base_dataset_name", "base_test_dataset");

    runImageTest(inputData);

    return true;
}

