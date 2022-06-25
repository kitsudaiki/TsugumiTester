/**
 * @file        test_thread.h
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

#ifndef TSUGUMI_TESTTHREAD_H
#define TSUGUMI_TESTTHREAD_H

#include <deque>
#include <mutex>

#include <libKitsunemimiHanamiSdk/common/websocket_client.h>

#include <libKitsunemimiCommon/threading/thread.h>
#include <libKitsunemimiJson/json_item.h>

class TestStep;

class TestThread
        : public Kitsunemimi::Thread
{
public:
    TestThread(const std::string &name,
               Kitsunemimi::Json::JsonItem &inputData);
    ~TestThread();

    void addTest(TestStep* newStep);

    bool isFinished = false;
    static Kitsunemimi::Hanami::WebsocketClient* m_wsClient;

protected:
    void run();

private:
    std::deque<TestStep*> m_taskQueue;
    std::mutex m_queueLock;
    Kitsunemimi::Json::JsonItem m_inputData;

    TestStep* getTest();
};

#endif // TSUGUMI_TESTTHREAD_H
