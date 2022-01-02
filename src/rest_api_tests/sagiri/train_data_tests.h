#ifndef TRAINDATA_H
#define TRAINDATA_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class TrainDataTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    TrainDataTests();

private:
    void create_test();
    void show_test();
    void list_test();
    void delete_test();

    std::string m_trainDataName = "test_data";
    std::string m_trainDataUuid = "";
};

#endif // TRAINDATA_H
