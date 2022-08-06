/**
 * @file        template_generate_test.cpp
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

#include "template_generate_test.h"

#include <libKitsumiAiSdk/template.h>

TemplateGenerateTest::TemplateGenerateTest(const bool expectSuccess,
                                       const std::string &type)
            : TestStep(expectSuccess)
{
    m_testName = "generate template";
    m_type = type;
    if(expectSuccess) {
        m_testName += " (success)";
    } else {
        m_testName += " (fail)";
    }
}

bool
TemplateGenerateTest::runTest(Kitsunemimi::Json::JsonItem &inputData,
                            Kitsunemimi::ErrorContainer &error)
{
    // create new template
    std::string result;
    if(m_type == "image")
    {
        if(Kitsunemimi::Hanami::generateTemplate(result,
                                               inputData.get("template_name").getString(),
                                               inputData.get("learn_dataset_uuid").getString(),
                                               m_type,
                                               error) != m_expectSuccess)
        {
            return false;
        }
    }
    else if(m_type == "graph")
    {
        if(Kitsunemimi::Hanami::generateTemplate(result,
                                               inputData.get("template_name").getString(),
                                               inputData.get("base_dataset_uuid").getString(),
                                               m_type,
                                               error) != m_expectSuccess)
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    if(m_expectSuccess == false) {
        return true;
    }

    // parse output
    Kitsunemimi::Json::JsonItem jsonItem;
    if(jsonItem.parse(result, error) == false) {
        return false;
    }

    inputData.insert("template_uuid", jsonItem.get("uuid").getString(), true);

    return true;
}
