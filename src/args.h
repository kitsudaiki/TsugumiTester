/**
 * @file        args.h
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

#ifndef TSUGUMITESTER_ARGS_H
#define TSUGUMITESTER_ARGS_H

#include <libKitsunemimiArgs/arg_parser.h>
#include <libKitsunemimiHanamiCommon/args.h>
#include <libKitsunemimiCommon/logger.h>

/**
 * @brief register cli-arguments
 *
 * @param argparser reference to argument parser
 *
 * @return true if successful, else false
 */
bool
registerArguments(Kitsunemimi::ArgParser* argparser,
                  Kitsunemimi::ErrorContainer &error)
{
    if(Kitsunemimi::Hanami::registerArguments(*argparser, error) == false) {
        return false;
    }

    return true;
}

#endif // TSUGUMITESTER_ARGS_H
