/**
 * @file        dataset_create_test.cpp
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

#include "dataset_create_test.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiHanamiSdk/actions/data_set.h>

DataSetCreateTest::DataSetCreateTest(const bool expectSuccess,
                                     const std::string &type)
          : TestStep(expectSuccess)
{
    m_testName = "create data-set";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
    m_type = type;
}

bool
DataSetCreateTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                           Kitsunemimi::ErrorContainer &error)
{
    // create new user
    std::string result;

    if(m_type == "learn")
    {
        if(Kitsunemimi::Hanami::uploadMnistData(result,
                                                inputData.get("learn_dataset_name").getString(),
                                                inputData.get("learn_inputs").getString(),
                                                inputData.get("learn_labels").getString(),
                                                error) != m_expectSuccess)
        {
            return false;
        }
    }
    else
    {
        if(Kitsunemimi::Hanami::uploadMnistData(result,
                                                inputData.get("request_dataset_name").getString(),
                                                inputData.get("request_inputs").getString(),
                                                inputData.get("request_labels").getString(),
                                                error) != m_expectSuccess)
        {
            return false;
        }
    }


    if(m_expectSuccess == false) {
        return true;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false) {
        return false;
    }

    if(m_type == "learn") {
        inputData.insert("learn_dataset_uuid", jsonItem.get("uuid").getString(), true);
    } else {
        inputData.insert("request_dataset_uuid", jsonItem.get("uuid").getString(), true);
    }

    return true;
}
