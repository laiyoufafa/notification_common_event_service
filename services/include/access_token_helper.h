/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BASE_NOTIFICATION_CES_STANDARD_SERVICES_CES_INCLUDE_ACCESS_TOKEN_HELPER_H
#define BASE_NOTIFICATION_CES_STANDARD_SERVICES_CES_INCLUDE_ACCESS_TOKEN_HELPER_H

#include "accesstoken_kit.h"

namespace OHOS {
namespace EventFwk {
class AccessTokenHelper {
public:
    /**
     * Verifies native token.
     *
     * @param callerToken Indicates the token of caller.
     * @return Returns true if successful; false otherwise.
     */
    static bool VerifyNativeToken(const Security::AccessToken::AccessTokenID &callerToken);
    static int VerifyAccessToken(const Security::AccessToken::AccessTokenID &callerToken,
        const std::string &permission);
};
}  // namespace EventFwk
}  // namespace OHOS
#endif  // BASE_NOTIFICATION_CES_STANDARD_SERVICES_CES_INCLUDE_ACCESS_TOKEN_HELPER_H