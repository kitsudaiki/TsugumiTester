/**
 * @file        cluster_tests.cpp
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

#include "cluster_tests.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiCrypto/common.h>

#include <libKitsunemimiHanamiSdk/actions/cluster.h>
#include <libKitsunemimiHanamiSdk/actions/template.h>
#include <libKitsunemimiHanamiSdk/actions/data_set.h>

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
    Kitsunemimi::Json::JsonItem jsonItem;
    bool ret = false;
    bool success = false;
    std::string result;

    Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error);
    error._errorMessages.clear();

    //----------------------------------------------------------------------------------------------
    Kitsunemimi::Hanami::uploadMnistData(result,
                                         "learn_data",
                                         GET_STRING_CONFIG("test_data", "learn_inputs", success),
                                         GET_STRING_CONFIG("test_data", "learn_labels", success),
                                         error);

    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }
    m_learnInputUuid = jsonItem.get("uuid").getString();

    //----------------------------------------------------------------------------------------------

    // create new template for tests
    ret = Kitsunemimi::Hanami::createTemplate(result, m_templateName, m_learnInputUuid, error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    // parse output
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

    // create new cluster
    std::string result;
    ret = Kitsunemimi::Hanami::createCluster(result, m_clusterName, m_templateUuid, error);
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

    // get cluster-infos
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

    // list clusters
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

    // delete cluster
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

    assert(Kitsunemimi::Hanami::deleteDataset(result, m_learnInputUuid, error));
}
