/**
 * @file        template_test.cpp
 *
 * @author      Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2021 Tobias Anker
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

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