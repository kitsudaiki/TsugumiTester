/**
 * @file        cluster_tests.h
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

#ifndef TSURUGITESTER_CLUSTERTESTS_H
#define TSURUGITESTER_CLUSTERTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class ClusterTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    ClusterTests();

private:
    void prepare();

    void create_test();
    void show_test();
    void list_test();
    void delete_test();

    void cleanup();

    std::string m_clusterName = "test_cluster";
    std::string m_templateName = "test_template";
    std::string m_templateUuid = "";
};

#endif // TSURUGITESTER_CLUSTERTESTS_H