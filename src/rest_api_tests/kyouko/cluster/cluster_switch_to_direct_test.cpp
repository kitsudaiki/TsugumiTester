#include "cluster_switch_to_direct_test.h"

#include <common/test_thread.h>

#include <libKitsunemimiHanamiSdk/cluster.h>
#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

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
    Kitsunemimi::Hanami::WebsocketClient* client = nullptr;
    client = Kitsunemimi::Hanami::switchToDirectMode(result,
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
