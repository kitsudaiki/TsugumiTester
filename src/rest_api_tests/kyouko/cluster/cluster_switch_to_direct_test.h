#ifndef CLUSTERSWITCHTODIRECTTEST_H
#define CLUSTERSWITCHTODIRECTTEST_H

#include <common/test_step.h>

class ClusterSwitchToDirectTest
        : public TestStep
{
public:
    ClusterSwitchToDirectTest(const bool expectSuccess);

    bool runTest(Kitsunemimi::Json::JsonItem &inputData,
                 Kitsunemimi::ErrorContainer &error);
};

#endif // CLUSTERSWITCHTODIRECTTEST_H
