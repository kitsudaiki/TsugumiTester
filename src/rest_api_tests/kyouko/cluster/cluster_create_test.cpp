/**
 * @file        cluster_create_test.cpp
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

#include "cluster_create_test.h"

#include <libHanamiAiSdk/cluster.h>

ClusterCreateTest::ClusterCreateTest(const bool expectSuccess)
          : TestStep(expectSuccess)
{
    m_testName = "create cluster";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
ClusterCreateTest::runTest(Kitsunemimi::JsonItem &inputData,
                           Kitsunemimi::ErrorContainer &error)
{
    // create new cluster
    std::string result;
    if(HanamiAI::createCluster(result,
                               inputData.get("cluster_name").getString(),
                               inputData.get("cluster_definition").getString(),
                               error) != m_expectSuccess)
    {
        return false;
    }

    if(m_expectSuccess == false) {
        return true;
    }

    // parse output
    Kitsunemimi::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false) {
        return false;
    }

    inputData.insert("cluster_uuid", jsonItem.get("uuid").getString(), true);

    return true;
}
