/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_RECORD_H
#define FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_RECORD_H

#include "common_event_constant.h"
#include "common_event_data.h"
#include "common_event_publish_info.h"

namespace OHOS {
namespace EventFwk {
struct CommonEventRecord {
    std::shared_ptr<CommonEventData> commonEventData;
    std::shared_ptr<CommonEventPublishInfo> publishInfo;
    struct tm recordTime {};
    pid_t pid;
    uid_t uid;
    int32_t userId;
    std::string bundleName;
    bool isSubsystem;
    bool isSystemApp;
    bool isProxy;
    bool isSystemEvent;

    CommonEventRecord()
        : commonEventData(nullptr),
          publishInfo(nullptr),
          pid(0),
          uid(0),
          userId(UNDEFINED_USER),
          isSubsystem(false),
          isSystemApp(false),
          isProxy(false),
          isSystemEvent(false)
    {}
};
}  // namespace EventFwk
}  // namespace OHOS
#endif  // FOUNDATION_EVENT_CESFWK_SERVICES_INCLUDE_COMMON_EVENT_RECORD_H