#include "task_tests.h"

#include <libKitsunemimiConfig/config_handler.h>
#include <libKitsunemimiCrypto/common.h>
#include <libKitsunemimiCommon/files/binary_file.h>

#include <libKitsunemimiHanamiSdk/actions/cluster.h>
#include <libKitsunemimiHanamiSdk/actions/template.h>
#include <libKitsunemimiHanamiSdk/actions/task.h>

#include <libKitsunemimiJson/json_item.h>

TaskTests::TaskTests()
    : Kitsunemimi::CompareTestHelper("TaskTests")
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
TaskTests::prepare()
{
    Kitsunemimi::ErrorContainer error;
    Kitsunemimi::Json::JsonItem jsonItem;

    std::string result;
    assert(Kitsunemimi::Hanami::createTemplate(result, m_templateName, 784, 10, error));
    assert(jsonItem.parse(result, error));

    m_templateUuid = jsonItem.get("uuid").getString();
    result.clear();

    assert(Kitsunemimi::Hanami::createCluster(result, m_clusterName, m_templateUuid, error));
    assert(jsonItem.parse(result, error));

    m_clusterUuid = jsonItem.get("uuid").getString();

    bool success = false;
    std::string tempPath = "";
    Kitsunemimi::DataBuffer fileContent;

    m_testType = GET_STRING_CONFIG("test_data", "type", success);

    tempPath = GET_STRING_CONFIG("test_data", "learn_inputs", success);
    Kitsunemimi::BinaryFile learnInputFile(tempPath);
    learnInputFile.readCompleteFile(fileContent);
    Kitsunemimi::Crypto::encodeBase64(m_learnInputsB64, fileContent.data, fileContent.usedBufferSize);
    learnInputFile.closeFile();
    fileContent.clear();

    tempPath = GET_STRING_CONFIG("test_data", "learn_labels", success);
    Kitsunemimi::BinaryFile learnLabelFile(tempPath);
    learnLabelFile.readCompleteFile(fileContent);
    Kitsunemimi::Crypto::encodeBase64(m_learnLabelsB64, fileContent.data, fileContent.usedBufferSize);
    learnLabelFile.closeFile();
    fileContent.clear();

    tempPath = GET_STRING_CONFIG("test_data", "request_inputs", success);
    Kitsunemimi::BinaryFile requestInputFile(tempPath);
    requestInputFile.readCompleteFile(fileContent);
    Kitsunemimi::Crypto::encodeBase64(m_requestInputsB64, fileContent.data, fileContent.usedBufferSize);
    requestInputFile.closeFile();
    fileContent.clear();

    tempPath = GET_STRING_CONFIG("test_data", "request_labels", success);
    Kitsunemimi::BinaryFile requestLabelFile(tempPath);
    requestLabelFile.readCompleteFile(fileContent);
    Kitsunemimi::Crypto::encodeBase64(m_requestLabelsB64, fileContent.data, fileContent.usedBufferSize);
    requestLabelFile.closeFile();
    fileContent.clear();
}

/**
 * @brief create_test
 */
void
TaskTests::create_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

    std::string result;
    ret = Kitsunemimi::Hanami::createLearnTask(result,
                                               m_clusterUuid,
                                               m_learnInputsB64,
                                               m_learnLabelsB64,
                                               m_testType,
                                               error);
    TEST_EQUAL(ret, true);
    if(ret == false)
    {
        LOG_ERROR(error);
        return;
    }
}

/**
 * @brief show_test
 */
void
TaskTests::show_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

}

/**
 * @brief list_test
 */
void
TaskTests::list_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;

}

/**
 * @brief delete_test
 */
void
TaskTests::delete_test()
{
    Kitsunemimi::ErrorContainer error;
    bool ret = false;


}

/**
 * @brief cleanup
 */
void
TaskTests::cleanup()
{
    Kitsunemimi::ErrorContainer error;
    std::string result;

    assert(Kitsunemimi::Hanami::deleteTemplate(result, m_templateName, error));
    assert(Kitsunemimi::Hanami::deleteCluster(result, m_clusterName, error));
}
