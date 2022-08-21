/**
 * @file        test_step.h
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

#ifndef TSUGUMI_TESTSTEP_H
#define TSUGUMI_TESTSTEP_H

#include <vector>
#include <unistd.h>

#include <libKitsunemimiJson/json_item.h>
#include <libKitsunemimiCommon/logger.h>

class TestStep
{
public:
    TestStep(const bool expectSuccess);
    virtual ~TestStep();

    const std::string getTestName() const;

    virtual bool runTest(Kitsunemimi::Json::JsonItem &inputData,
                         Kitsunemimi::ErrorContainer &error) = 0;

protected:
    const bool m_expectSuccess;
    std::string m_testName;
};

#endif // TSUGUMI_TESTSTEP_H
