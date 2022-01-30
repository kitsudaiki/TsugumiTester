/**
 * @file        train_data_tests.cpp
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

#include "train_data_tests.h"

#include <libKitsunemimiHanamiSdk/actions/data_set.h>

#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiConfig/config_handler.h>

TrainDataTests::TrainDataTests()
    : Kitsunemimi::CompareTestHelper("TrainDataTests")
{
    create_test();
    show_test();
    list_test();
    delete_test();
}

/**
 * @brief create_test
 */
void
TrainDataTests::create_test()
{
    bool ret = false;
    bool success = false;
    Kitsunemimi::ErrorContainer error;

    // get test-configs
    const std::string dataPath = GET_STRING_CONFIG("test_data", "learn_inputs", success);
    const std::string dataType = GET_STRING_CONFIG("test_data", "type", success);

    // test data-upload
    std::string result;
    ret = Kitsunemimi::Hanami::uploadMnistData(result,
                                               m_trainDataName,
                                               GET_STRING_CONFIG("test_data", "learn_inputs", success),
                                               GET_STRING_CONFIG("test_data", "learn_labels", success),
                                               error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse result
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // get uuid of the uploaded data for the get and delete tests
    m_trainDataUuid = jsonItem.get("uuid").getString();
}

/**
 * @brief show_test
 */
void
TrainDataTests::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // get data
    std::string result;
    ret = Kitsunemimi::Hanami::getDataset(result, m_trainDataUuid, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // try to get non-existing data
    ret = Kitsunemimi::Hanami::getDataset(result, "fail", error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief list_test
 */
void
TrainDataTests::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // list all data
    std::string result;
    ret = Kitsunemimi::Hanami::listDatasets(result, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
}

/**
 * @brief delete_test
 */
void
TrainDataTests::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // delete data
    std::string result;
    ret = Kitsunemimi::Hanami::deleteDataset(result, m_trainDataUuid, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // try the delete a non-existing data
    ret = Kitsunemimi::Hanami::deleteDataset(result, m_trainDataUuid, error);
    TEST_EQUAL(ret, false);
}

