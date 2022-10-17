/**
 * @file        cluster_switch_to_direct_test.cpp
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

#include "cluster_switch_to_direct_test.h"

#include <common/test_thread.h>

#include <libHanamiAiSdk/cluster.h>
#include <libHanamiAiSdk/common/websocket_client.h>

ClusterSwitchToDirectTest::ClusterSwitchToDirectTest(const bool expectSuccess)
    : TestStep(expectSuccess)
{
    m_testName = "switch cluster to direct mode";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
ClusterSwitchToDirectTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                                   Kitsunemimi::ErrorContainer &error)
{
    // create new cluster
    std::string result;
    HanamiAI::WebsocketClient* client = nullptr;
    client = HanamiAI::switchToDirectMode(result,
                                          inputData.get("cluster_uuid").getString(),
                                          error);
    bool success = client != nullptr;
    if(success != m_expectSuccess)
    {
        return false;
    }

    TestThread::m_wsClient = client;

    return true;
}
