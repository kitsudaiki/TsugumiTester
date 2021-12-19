#include "user_tests.h"

#include <libKitsunemimiHanamiSdk/actions/user.h>

#include <libKitsunemimiJson/json_item.h>

UserTests::UserTests()
{

}

/**
 * @brief UserTests::runTest
 * @return
 */
bool
UserTests::runTest()
{
    if(create_test() == false) {
        return false;
    }
    if(show_test() == false) {
        return false;
    }
    if(list_test() == false) {
        return false;
    }
    if(delete_test() == false) {
        return false;
    }

    return true;
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

    return true;
}