#ifndef CLUSTERTESTS_H
#define CLUSTERTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class ClusterTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    ClusterTests();

private:
    bool create_generate_test();
    bool create_template_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    std::string m_clusterName = "test_cluster";
    std::string m_templateUuid = "test_template";
};

#endif // CLUSTERTESTS_H
