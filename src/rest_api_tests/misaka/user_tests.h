/**
 * @file        user_tests.h
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

#ifndef USERTESTS_H
#define USERTESTS_H

#include <libKitsunemimiCommon/test_helper/compare_test_helper.h>

class UserTests
        : public Kitsunemimi::CompareTestHelper
{
public:
    UserTests();

private:
    bool create_test();
    bool show_test();
    bool list_test();
    bool delete_test();

    std::string m_userName = "tsurugi";
    std::string m_password = "new password";
    bool m_isAdmin = true;
    std::string m_roles = "tester";
    std::string m_projects = "tester";
};

#endif // USERTESTS_H
