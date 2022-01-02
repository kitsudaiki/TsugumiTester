#include "train_data_tests.h"

#include <libKitsunemimiHanamiSdk/actions/train_data.h>

#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiConfig/config_handler.h>

TrainDataTests::TrainDataTests()
    : Kitsunemimi::CompareTestHelper("TrainDataTests")
{
    create_test();
    show_test();
    list_test();
    delete_test();
}

void
TrainDataTests::create_test()
{
    bool ret = false;
    bool success = false;
    Kitsunemimi::ErrorContainer error;

    const std::string dataPath = GET_STRING_CONFIG("test_data", "learn_inputs", success);
    const std::string dataType = GET_STRING_CONFIG("test_data", "type", success);

    std::string result;

    ret = Kitsunemimi::Hanami::uploadTrainData(result,
                                               m_trainDataName,
                                               dataType,
                                               dataPath,
                                               error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }

    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false)
    {
        LOG_ERROR(error);
        return;
    }

    m_trainDataUuid = jsonItem.get("uuid").getString();
}

void
TrainDataTests::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // get data
    std::string result;
    ret = Kitsunemimi::Hanami::getTrainData(result, m_trainDataUuid, error);
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

    // try to get non-existing data
    ret = Kitsunemimi::Hanami::getTrainData(result, "fail", error);
    TEST_EQUAL(ret, false);
}

void
TrainDataTests::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // list all data
    std::string result;
    ret = Kitsunemimi::Hanami::listTrainData(result, error);
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

void
TrainDataTests::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    // delete data
    std::string result;
    ret = Kitsunemimi::Hanami::deleteTrainData(result, m_trainDataUuid, error);
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

    // try the delete a non-existing data
    ret = Kitsunemimi::Hanami::deleteTrainData(result, m_trainDataUuid, error);
    TEST_EQUAL(ret, false);
}

