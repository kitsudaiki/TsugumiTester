/**
 * @file        task_tests.cpp
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

#include "task_tests.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiCrypto/common.h>

#include <libKitsunemimiHanamiSdk/actions/cluster.h>
#include <libKitsunemimiHanamiSdk/actions/template.h>
#include <libKitsunemimiHanamiSdk/actions/task.h>
#include <libKitsunemimiHanamiSdk/actions/data_set.h>

#include <libKitsunemimiJson/json_item.h>

TaskTests::TaskTests()
    : Kitsunemimi::CompareTestHelper("TaskTests")
{
    prepare();

    learn_test();
    request_test();
    list_test();
    delete_test();

    cleanup();
}

/**
 * @brief prepare
 */
void
TaskTests::prepare()
{
    Kitsunemimi::ErrorContainer error;
    Kitsunemimi::Json::JsonItem jsonItem;
    bool success = false;
    std::string result;

    Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error);
    Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
    error._errorMessages.clear();

    //----------------------------------------------------------------------------------------------
    // create template

    assert(Kitsunemimi::Hanami::createTemplate(result, m_templateName, 784, 10, error));
    assert(jsonItem.parse(result, error));

    m_templateUuid = jsonItem.get("uuid").getString();

    //----------------------------------------------------------------------------------------------
    // create cluster from template

    result.clear();

    assert(Kitsunemimi::Hanami::createCluster(result, m_clusterName, m_templateUuid, error));
    assert(jsonItem.parse(result, error));

    m_clusterUuid = jsonItem.get("uuid").getString();

    //----------------------------------------------------------------------------------------------
    // get data-type

    const std::string dataType = GET_STRING_CONFIG("test_data", "type", success);

    //----------------------------------------------------------------------------------------------
    Kitsunemimi::Hanami::uploadMnistData(result,
                                         "learn_data",
                                         GET_STRING_CONFIG("test_data", "learn_inputs", success),
                                         GET_STRING_CONFIG("test_data", "learn_labels", success),
                                         error);

    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
    m_learnInputUuid = jsonItem.get("uuid").getString();

    //----------------------------------------------------------------------------------------------
    Kitsunemimi::Hanami::uploadMnistData(result,
                                         "request_data",
                                         GET_STRING_CONFIG("test_data", "request_inputs", success),
                                         GET_STRING_CONFIG("test_data", "request_labels", success),
                                         error);

    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
    m_requestInputUuid = jsonItem.get("uuid").getString();

    //----------------------------------------------------------------------------------------------
}

/**
 * @brief create_test
 */
void
TaskTests::learn_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;
    bool success = false;
    std::string result;
    Kitsunemimi::Json::JsonItem jsonItem;

    const std::string dataType = GET_STRING_CONFIG("test_data", "type", success);

    // create new learn-task
    ret = Kitsunemimi::Hanami::createLearnTask(result,
                                               m_clusterUuid,
                                               m_learnInputUuid,
                                               error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse result
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // get uuid of the new task
    m_taskUuid = jsonItem.get("uuid").getString();
    //std::cout<<"uuid: "<<m_taskUuid<<std::endl;

    // wait until task is finished
    do
    {
        sleep(1);

        Kitsunemimi::Hanami::getTask(result, m_taskUuid, m_clusterUuid, false, error);

        // parse output
        if(jsonItem.parse(result, error) == false)
        {
            LOG_ERROR(error);
            return;
        }
        //std::cout<<jsonItem.toString(true)<<std::endl;
    }
    while(jsonItem.get("state").getString() != "finished");
}

void
TaskTests::request_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;
    bool success = false;
    std::string result;
    Kitsunemimi::Json::JsonItem jsonItem;

    const std::string dataType = GET_STRING_CONFIG("test_data", "type", success);

    // create new request-task
    ret = Kitsunemimi::Hanami::createRequestTask(result,
                                                 m_clusterUuid,
                                                 m_requestInputUuid,
                                                 error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse result
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // get uuid of the new task
    m_taskUuid = jsonItem.get("uuid").getString();
    //std::cout<<"uuid: "<<m_taskUuid<<std::endl;

    // wait until task is finished
    do
    {
        sleep(1);
        Kitsunemimi::Hanami::getTask(result, m_taskUuid, m_clusterUuid, false, error);

        // parse output
        if(jsonItem.parse(result, error) == false)
        {
            LOG_ERROR(error);
            return;
        }
        //std::cout<<jsonItem.toString(true)<<std::endl;
    }
    while(jsonItem.get("state").getString() != "finished");

    // get task-result
    Kitsunemimi::Hanami::getTask(result, m_taskUuid, m_clusterUuid, true, error);

    // parse output
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
    //std::cout<<jsonItem.toString(true)<<std::endl;
}

/**
 * @brief list_test
 */
void
TaskTests::list_test()
{
    // TODO
}

/**
 * @brief delete_test
 */
void
TaskTests::delete_test()
{
    // TODO
}

/**
 * @brief cleanup
 */
void
TaskTests::cleanup()
{
    Kitsunemimi::ErrorContainer error;
    std::string result;

    assert(Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error));
    assert(Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error));

    assert(Kitsunemimi::Hanami::deleteDataset(result, m_learnInputUuid, error));
    assert(Kitsunemimi::Hanami::deleteDataset(result, m_requestInputUuid, error));
}
