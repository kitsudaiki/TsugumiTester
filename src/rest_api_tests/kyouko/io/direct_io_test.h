#ifndef DIRECTIOTEST_H
#define DIRECTIOTEST_H

#include <common/test_step.h>

class DirectIoTest
        : public TestStep
{
public:
    DirectIoTest(const bool expectSuccess);

    bool runTest(Kitsunemimi::Json::JsonItem &inputData,
                 Kitsunemimi::ErrorContainer &error);

private:
    void fillInputValues(float* inputValues);
    void fillShouldValues(float* shouldValues);

    bool learnTest();
    bool requestTest();
};

#endif // DIRECTIOTEST_H
