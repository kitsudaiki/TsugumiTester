/**
 * @file        dataset_create_csv_test.h
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

#ifndef TSUGUMITESTER_DATASETCREATE_CSV_TEST_H
#define TSUGUMITESTER_DATASETCREATE_CSV_TEST_H

#include <common/test_step.h>

class DataSetCreateCsvTest
        : public TestStep
{
public:
    DataSetCreateCsvTest(const bool expectSuccess);

    bool runTest(Kitsunemimi::JsonItem &inputData,
                 Kitsunemimi::ErrorContainer &error);
};

#endif // TSUGUMITESTER_DATASETCREATE_CSV_TEST_H
