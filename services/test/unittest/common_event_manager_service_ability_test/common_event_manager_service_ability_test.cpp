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

#include <gtest/gtest.h>
#include <numeric>
#define private public
#include "common_event_manager_service_ability.h"
#undef private

extern void mockInit(bool mockRet);

namespace OHOS {
namespace EventFwk {
using namespace testing::ext;

class CommonEventManagerServiceAbilityTest : public testing::Test {
public:
    CommonEventManagerServiceAbilityTest()
    {}
    ~CommonEventManagerServiceAbilityTest()
    {}

    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void CommonEventManagerServiceAbilityTest::SetUpTestCase(void)
{}

void CommonEventManagerServiceAbilityTest::TearDownTestCase(void)
{}

void CommonEventManagerServiceAbilityTest::SetUp(void)
{}

void CommonEventManagerServiceAbilityTest::TearDown(void)
{}

/**
 * @tc.name: CommonEventManagerServiceAbility_0100
 * @tc.desc: test OnStart function and service_ is not nullptr.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceAbilityTest, CommonEventManagerServiceAbility_0100, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0100 start";
    int32_t systemAbilityId = 1;
    bool runOnCreate = true;
    CommonEventManagerServiceAbility CommonEventManagerServiceAbility(systemAbilityId, runOnCreate);
    CommonEventManagerServiceAbility.service_ = std::make_shared<CommonEventManagerService>();
    CommonEventManagerServiceAbility.OnStart();
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0100 end";
}

/**
 * @tc.name: CommonEventManagerServiceAbility_0200
 * @tc.desc: test OnStart function and errorCode != ERR_OK.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceAbilityTest, CommonEventManagerServiceAbility_0200, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0200 start";
    int32_t systemAbilityId = 1;
    bool runOnCreate = true;
    CommonEventManagerServiceAbility CommonEventManagerServiceAbility(systemAbilityId, runOnCreate);
    CommonEventManagerServiceAbility.service_ = nullptr;
    mockInit(true);
    CommonEventManagerServiceAbility.OnStart();
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0200 end";
}

/**
 * @tc.name: CommonEventManagerServiceAbility_0300
 * @tc.desc: test OnStart function and errorCode == ERR_OK.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceAbilityTest, CommonEventManagerServiceAbility_0300, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0300 start";
    int32_t systemAbilityId = 1;
    bool runOnCreate = true;
    CommonEventManagerServiceAbility CommonEventManagerServiceAbility(systemAbilityId, runOnCreate);
    CommonEventManagerServiceAbility.service_ = nullptr;
    mockInit(false);
    CommonEventManagerServiceAbility.OnStart();
    GTEST_LOG_(INFO) << "CommonEventManagerServiceAbility_0300 end";
}
}  // namespace EventFwk
}  // namespace OHOS