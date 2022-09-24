/**
 * @file        graph_learn_task_test.cpp
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

#include "graph_learn_task_test.h"

#include <libHanamiAiSdk/task.h>

GraphLearnTaskTest::GraphLearnTaskTest(const bool expectSuccess)
  : TestStep(expectSuccess)
{
    m_testName = "graph-learn-task";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
GraphLearnTaskTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                            Kitsunemimi::ErrorContainer &error)
{
    // create new user
    std::string result;
    if(Kitsunemimi::Hanami::createGraphLearnTask(result,
                                                 inputData.get("generic_task_name").getString(),
                                                 inputData.get("cluster_uuid").getString(),
                                                 inputData.get("base_dataset_uuid").getString(),
                                                 "Open",
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

    inputData.insert("learn_task_uuid", jsonItem.get("uuid").getString(), true);

    // wait until task is finished
    do
    {
        sleep(1);

        Kitsunemimi::Hanami::getTask(result,
                                     inputData.get("learn_task_uuid").getString(),
                                     inputData.get("cluster_uuid").getString(),
                                     error);

        // parse output
        if(jsonItem.parse(result, error) == false) {
            return false;
        }
        std::cout<<jsonItem.toString(true)<<std::endl;
    }
    while(jsonItem.get("state").getString() != "finished");

    return true;
}
