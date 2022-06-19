#ifndef CLUSTERSWITCHTOTASKTEST_H
#define CLUSTERSWITCHTOTASKTEST_H

#include <common/test_step.h>

class ClusterSwitchToTaskTest
        : public TestStep
{
public:
    ClusterSwitchToTaskTest(const bool expectSuccess);

    bool runTest(Kitsunemimi::Json::JsonItem &inputData,
                 Kitsunemimi::ErrorContainer &error);
};

#endif // CLUSTERSWITCHTOTASKTEST_H
