#ifndef TEMPLATETEST_H
#define TEMPLATETEST_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class TemplateTest
        : public Kitsunemimi::CompareTestHelper
{
public:
    TemplateTest();

private:
    bool create_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    std::string m_templateName = "test_template";
};

#endif // TEMPLATETEST_H
