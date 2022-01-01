#ifndef TEMPLATETEST_H
#define TEMPLATETEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class TemplateTest
        : public Kitsunemimi::CompareTestHelper
{
public:
    TemplateTest();

private:
    void create_test();
    void show_test();
    void list_test();
    void delete_test();

    std::string m_templateName = "test_template";
};

#endif // TEMPLATETEST_H
