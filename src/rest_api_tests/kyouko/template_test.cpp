#include "template_test.h"

#include <libKitsunemimiHanamiSdk/actions/template.h>

#include <libKitsunemimiJson/json_item.h>

TemplateTest::TemplateTest()
    : Kitsunemimi::CompareTestHelper("TemplateTest")
{
    create_test();
    show_test();
    list_test();
    delete_test();
}

/**
 * @brief create_test
 */
void
TemplateTest::create_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // create new template
    std::string result;
    ret = Kitsunemimi::Hanami::createTemplate(result, m_templateName, 784, 10, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // try to create template a second time with same name
    ret = Kitsunemimi::Hanami::createTemplate(result, m_templateName, 784, 10, error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief show_test
 */
void
TemplateTest::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // get template by name
    std::string result;
    ret = Kitsunemimi::Hanami::getTemplate(result, m_templateName, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // try to get non-existing user
    ret = Kitsunemimi::Hanami::getTemplate(result, "fail", error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief list_test
 */
void
TemplateTest::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // list templates
    std::string result;
    ret = Kitsunemimi::Hanami::listTemplate(result, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
}

/**
 * @brief delete_test
 */
void
TemplateTest::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // delete template by name
    std::string result;
    ret = Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    // try the delete a non-existing user
    ret = Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error);
    TEST_EQUAL(ret, false);
}
