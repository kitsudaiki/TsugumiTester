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

    void create_test();
    void show_test();
    void list_test();
    void delete_test();

    void cleanup();

    std::string m_clusterName = "test_cluster";
    std::string m_clusterUuid = "";

    std::string m_templateName = "test_template";
    std::string m_templateUuid = "";

    std::string m_testType = "";
    std::string m_learnInputsB64 = "";
    std::string m_learnLabelsB64 = "";
    std::string m_requestInputsB64 = "";
    std::string m_requestLabelsB64 = "";
};

#endif // TASKTESTS_H
