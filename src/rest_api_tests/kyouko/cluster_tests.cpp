#include "cluster_tests.h"

#include <libKitsunemimiHanamiSdk/actions/cluster.h>
#include <libKitsunemimiHanamiSdk/actions/template.h>

#include <libKitsunemimiJson/json_item.h>

ClusterTests::ClusterTests()
    : Kitsunemimi::CompareTestHelper("ClusterTests")
{
    prepare();

    create_test();
    show_test();
    list_test();
    delete_test();

    cleanup();
}

void
ClusterTests::prepare()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::createTemplate(result, m_templateName, 784, 10, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    ret = jsonItem.parse(result, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    m_templateUuid = jsonItem.get("uuid").getString();
    assert(m_templateUuid != "");
}

bool
ClusterTests::create_test()
{
    std::cout<<"cluster create"<<std::endl;

    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::createCluster(result, m_clusterName,  m_templateUuid, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
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
    ret = Kitsunemimi::Hanami::createCluster(result, m_clusterName, m_templateUuid, error);
    TEST_EQUAL(ret, false);
    if(ret) {
        return false;
    }

    return true;
}

bool
ClusterTests::show_test()
{
    std::cout<<"cluster show"<<std::endl;

    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::getCluster(result, m_clusterName, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
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
    ret = Kitsunemimi::Hanami::getCluster(result, "fail", error);
    TEST_EQUAL(ret, false);
    if(ret) {
        return false;
    }

    return true;
}

bool
ClusterTests::list_test()
{
    std::cout<<"cluster list"<<std::endl;

    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::listCluster(result, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
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
ClusterTests::delete_test()
{
    std::cout<<"cluster delete"<<std::endl;

    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
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
    ret = Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
    TEST_EQUAL(ret, false);
    if(ret) {
        return false;
    }

    return true;
}

void
ClusterTests::cleanup()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }
}
