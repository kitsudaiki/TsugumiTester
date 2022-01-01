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

/**
 * @brief prepare
 */
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

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    m_templateUuid = jsonItem.get("uuid").getString();
    assert(m_templateUuid != "");
}

/**
 * @brief create_test
 */
void
ClusterTests::create_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::createCluster(result, m_clusterName,  m_templateUuid, error);
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
    ret = Kitsunemimi::Hanami::createCluster(result, m_clusterName, m_templateUuid, error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief show_test
 */
void
ClusterTests::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::getCluster(result, m_clusterName, error);
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
    ret = Kitsunemimi::Hanami::getCluster(result, "fail", error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief list_test
 */
void
ClusterTests::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::listCluster(result, error);
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
ClusterTests::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
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
    ret = Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
    TEST_EQUAL(ret, false);
}

/**
 * @brief cleanup
 */
void
ClusterTests::cleanup()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error);
    TEST_EQUAL(ret, true);
}
