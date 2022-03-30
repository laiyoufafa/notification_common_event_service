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

#include "UnSubscribeCommonEvent_fuzzer.h"

#include "common_event_manager.h"

namespace OHOS {
namespace EventFwk {
class TestSubscriber : public CommonEventSubscriber {
public:
    explicit TestSubscriber(const CommonEventSubscribeInfo &sp) : CommonEventSubscriber(sp)
    {}

    ~TestSubscriber()
    {}

    void OnReceiveEvent(const CommonEventData &data) override
    {}
};
}  // namespace EventFwk

bool DoSomethingInterestingWithMyAPI(const uint8_t* data, size_t size)
{
    std::string stringData = reinterpret_cast<const char*>(data);

    EventFwk::MatchingSkills matchingSkills;
    matchingSkills.AddEvent(stringData);
    matchingSkills.AddEntity(stringData);
    matchingSkills.AddScheme(stringData);

    EventFwk::CommonEventSubscribeInfo subscribeInfo(matchingSkills);
    int32_t priority = U32_AT(data);
    subscribeInfo.SetPriority(priority);
    subscribeInfo.SetPermission(stringData);
    subscribeInfo.SetDeviceId(stringData);

    std::shared_ptr<EventFwk::TestSubscriber> subscriber =
        std::make_shared<EventFwk::TestSubscriber>(subscribeInfo);
    return EventFwk::CommonEventManager::UnSubscribeCommonEvent(subscriber);
}
}  // namespace OHOS

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DoSomethingInterestingWithMyAPI(data, size);
    return 0;
}
