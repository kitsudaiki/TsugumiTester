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

    void create_test();
    void show_test();
    void list_test();
    void delete_test();

    void cleanup();

    std::string m_clusterName = "test_cluster";
    std::string m_templateName = "test_template";
    std::string m_templateUuid = "";
};

#endif // CLUSTERTESTS_H
