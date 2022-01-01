#ifndef CLUSTERTESTS_H
#define CLUSTERTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class ClusterTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    ClusterTests();

private:
    void prepare();

    bool create_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    void cleanup();

    std::string m_clusterName = "test_cluster";
    std::string m_templateName = "test_template";
    std::string m_templateUuid = "";
};

#endif // CLUSTERTESTS_H
