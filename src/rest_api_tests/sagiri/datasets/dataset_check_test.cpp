/**
 * @file        dataset_check_test.cpp
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

#include "dataset_check_test.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiHanamiSdk/actions/data_set.h>

DataSetCheckTest::DataSetCheckTest(const bool expectSuccess)
          : TestStep(expectSuccess)
{
    m_testName = "check data-set";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
DataSetCheckTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                          Kitsunemimi::ErrorContainer &error)
{
    // get template by name
    std::string result;
    if(Kitsunemimi::Hanami::checkDataset(result,
                                         inputData.get("request_dataset_uuid").getString(),
                                         inputData.get("request_task_uuid").getString(),
                                         error) != m_expectSuccess)
    {
        return false;
    }

    if(m_expectSuccess == false) {
        return true;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false) {
        return false;
    }

    std::cout<<jsonItem.toString(true)<<std::endl;

    return true;
}
