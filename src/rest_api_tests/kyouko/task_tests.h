#ifndef TASKTESTS_H
#define TASKTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class TaskTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    TaskTests();

private:
    void prepare();

    void learn_test();
    void request_test();

    void list_test();
    void delete_test();

    void cleanup();

    std::string m_clusterName = "test_cluster";
    std::string m_clusterUuid = "";
    std::string m_taskUuid = "";

    std::string m_templateName = "test_template";
    std::string m_templateUuid = "";

    std::string m_learnInputUuid = "";
    std::string m_learnLabelUuid = "";

    std::string m_requestInputUuid = "";
    std::string m_requestLabelUuid = "";
};

#endif // TASKTESTS_H
