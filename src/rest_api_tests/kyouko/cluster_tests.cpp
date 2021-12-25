#include "cluster_tests.h"

#include <libKitsunemimiHanamiSdk/actions/cluster.h>

#include <libKitsunemimiJson/json_item.h>

ClusterTests::ClusterTests()
    : Kitsunemimi::CompareTestHelper("ClusterTests")
{

}

void
ClusterTests::runTest()
{
    TEST_EQUAL(create_generate_test(), true);
    TEST_EQUAL(create_template_test(), true);
    TEST_EQUAL(show_test(), true);
    TEST_EQUAL(list_test(), true);
    TEST_EQUAL(delete_test(), true);
}

bool
ClusterTests::create_generate_test()
{
    std::cout<<"cluster create"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::createClusterGenerate(result,
                                                  m_clusterName,
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

    std::cout<<jsonItem.toString(true)<<std::endl;

    // try to create user a second time with same name
    if(Kitsunemimi::Hanami::createClusterGenerate(result,
                                                  m_clusterName,
                                                  784,
                                                  10,
                                                  error) == false)
    {
        return false;
    }

    return true;
}

bool
ClusterTests::create_template_test()
{
    return true;
}

bool
ClusterTests::show_test()
{
    std::cout<<"cluster show"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::getCluster(result, m_clusterName, error) == false)
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
    if(Kitsunemimi::Hanami::getCluster(result, "fail_user", error)) {
        return false;
    }

    return true;
}

bool
ClusterTests::list_test()
{
    std::cout<<"cluster list"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::listCluster(result, error) == false)
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

bool
ClusterTests::delete_test()
{
    std::cout<<"cluster delete"<<std::endl;

    Kitsunemimi::ErrorContainer error;

    std::string result;
    if(Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error) == false)
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
    if(Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error)) {
        return false;
    }

    return true;
}
