/**
 * @file        user_tests.cpp
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

#include "user_tests.h"

#include <libKitsunemimiHanamiSdk/actions/user.h>

#include <libKitsunemimiJson/json_item.h>

UserTests::UserTests()
    : Kitsunemimi::CompareTestHelper("UserTests")
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
UserTests::create_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // create new user
    std::string result;
    ret = Kitsunemimi::Hanami::createUser(result,
                                          m_userName,
                                          m_password,
                                          m_isAdmin,
                                          m_roles,
                                          m_projects,
                                          error);
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

    // try to create user a second time with same name
    ret = Kitsunemimi::Hanami::createUser(result,
                                          m_userName,
                                          m_password,
                                          m_isAdmin,
                                          m_roles,
                                          m_projects,
                                          error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief show_test
 */
void
UserTests::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // get user by name
    std::string result;
    ret = Kitsunemimi::Hanami::getUser(result, m_userName, error);
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
    ret = Kitsunemimi::Hanami::getUser(result, "fail_user", error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief list_test
 */
void
UserTests::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // list all users
    std::string result;
    ret = Kitsunemimi::Hanami::listUser(result, error);
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
UserTests::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // delete user by name
    std::string result;
    ret = Kitsunemimi::Hanami::deleteUser(result, m_userName, error);
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
    ret = Kitsunemimi::Hanami::deleteUser(result, m_userName, error);
    TEST_EQUAL(ret, false);
}
