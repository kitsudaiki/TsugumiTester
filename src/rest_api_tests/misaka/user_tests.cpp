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

UserTests::UserTests() :
    Kitsunemimi::CompareTestHelper("UserTests")
{
}

/**
 * @brief UserTests::runTest
 * @return
 */
void
UserTests::runTest()
{
    TEST_EQUAL(create_test(), true);
    TEST_EQUAL(show_test(), true);
    TEST_EQUAL(list_test(), true);
    TEST_EQUAL(delete_test(), true);
}

/**
 * @brief UserTests::create_test
 * @return
 */
bool
UserTests::create_test()
{
    std::cout<<"user create"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::createUser(result,
                                       m_userName,
                                       m_password,
                                       m_isAdmin,
                                       m_roles,
                                       m_projects,
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

    std::cout<<jsonItem.toString(true)<<std::endl;

    // try to create user a second time with same name
    if(Kitsunemimi::Hanami::createUser(result,
                                       m_userName,
                                       m_password,
                                       m_isAdmin,
                                       m_roles,
                                       m_projects,
                                       error))
    {
        return false;
    }

    return true;
}

/**
 * @brief UserTests::show_test
 * @return
 */
bool
UserTests::show_test()
{
    std::cout<<"user show"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::getUser(result, m_userName, error) == false)
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

    std::cout<<jsonItem.toString(true)<<std::endl;

    // try to get non-existing user
    if(Kitsunemimi::Hanami::getUser(result, "fail_user", error))
    {
        return false;
    }

    return true;
}

/**
 * @brief UserTests::list_test
 * @return
 */
bool
UserTests::list_test()
{
    std::cout<<"user list"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::listUser(result, error) == false)
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

    std::cout<<jsonItem.toString(true)<<std::endl;

    return true;
}

/**
 * @brief UserTests::delete_test
 * @return
 */
bool
UserTests::delete_test()
{
    std::cout<<"user delete"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::deleteUser(result, m_userName, error) == false)
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

    std::cout<<jsonItem.toString(true)<<std::endl;

    // try the delete a non-existing user
    if(Kitsunemimi::Hanami::deleteUser(result, m_userName, error)) {
        return false;
    }

    return true;
}
