#include "cluster_switch_to_task_test.h"

#include <libKitsunemimiHanamiSdk/cluster.h>

ClusterSwitchToTaskTest::ClusterSwitchToTaskTest(const bool expectSuccess)
    : TestStep(expectSuccess)
{
    m_testName = "switch cluster to task mode";
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
ClusterSwitchToTaskTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                                 Kitsunemimi::ErrorContainer &error)
{
    // create new cluster
    std::string result;
    if(Kitsunemimi::Hanami::switchToTaskMode(result,
                                             inputData.get("cluster_uuid").getString(),
                                             error) != m_expectSuccess)
    {
        return false;
    }

    return true;
}
