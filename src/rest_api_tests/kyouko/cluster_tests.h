#ifndef CLUSTERTESTS_H
#define CLUSTERTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class ClusterTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    ClusterTests();
    void runTest();

private:
    bool create_generate_test();
    bool create_template_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    std::string m_clusterName = "test_cluster";
};

#endif // CLUSTERTESTS_H
