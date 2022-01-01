#include "template_test.h"

#include <libKitsunemimiHanamiSdk/actions/template.h>

#include <libKitsunemimiJson/json_item.h>

TemplateTest::TemplateTest()
    : Kitsunemimi::CompareTestHelper("TemplateTest")
{
    TEST_EQUAL(create_test(), true);
    TEST_EQUAL(show_test(), true);
    TEST_EQUAL(list_test(), true);
    TEST_EQUAL(delete_test(), true);
}

bool
TemplateTest::create_test()
{
    std::cout<<"template create"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::createTemplate(result,
                                           m_templateName,
                                           784,
                                           10,
                                           error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    // try to create user a second time with same name
    if(Kitsunemimi::Hanami::createTemplate(result,
                                           m_templateName,
                                           784,
                                           10,
                                           error))
    {
        return false;
    }

    return true;
}

bool
TemplateTest::show_test()
{
    std::cout<<"template show"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::getTemplate(result, m_templateName, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    // try to get non-existing user
    if(Kitsunemimi::Hanami::getTemplate(result, "fail", error)) {
        return false;
    }

    return true;
}

bool
TemplateTest::list_test()
{
    std::cout<<"template list"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::listTemplate(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    return true;
}

bool
TemplateTest::delete_test()
{
    std::cout<<"template delete"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return false;
    }

    // try the delete a non-existing user
    if(Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error)) {
        return false;
    }

    return true;
}
