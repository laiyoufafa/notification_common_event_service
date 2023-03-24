/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "common_event_manager_service.h"
#undef private
#include "ces_inner_error_code.h"

extern void MockVerifyNativeToken(bool mockRet);
extern void MockIsSystemApp(bool mockRet);
extern void MockIsDlpHap(bool mockRet);
extern void MockVerifyShellToken(bool mockRet);

using namespace testing::ext;
using namespace OHOS;
using namespace OHOS::EventFwk;
using namespace OHOS::Notification;
using namespace OHOS::AppExecFwk;

class CommonEventManagerServiceTest : public testing::Test {
public:
    CommonEventManagerServiceTest()
    {}
    ~CommonEventManagerServiceTest()
    {}

    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void CommonEventManagerServiceTest::SetUpTestCase(void)
{}

void CommonEventManagerServiceTest::TearDownTestCase(void)
{}

void CommonEventManagerServiceTest::SetUp(void)
{}

void CommonEventManagerServiceTest::TearDown(void)
{}

/**
 * @tc.name: CommonEventManagerServiceBranch_0100
 * @tc.desc: test PublishCommonEvent function, shell is system app and return true.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0100, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0100 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set VerifyNativeToken is true
    MockVerifyNativeToken(true);
    // set IsDlpHap is false
    MockIsDlpHap(false);
    // test PublishCommonEvent
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    uid_t uid = 1;
    int32_t userId = 2;
    int32_t callerToken = 0;
    EXPECT_EQ(true, comm->PublishCommonEvent(event, publishinfo, commonEventListener, uid, callerToken, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0100 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0200
 * @tc.desc: test SubscribeCommonEvent function and IsReady is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0200, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0200 start";
    std::shared_ptr<CommonEventManagerService> comm = std::make_shared<CommonEventManagerService>();
    ASSERT_NE(nullptr, comm);
    // set IsReady is false
    comm->innerCommonEventManager_ = nullptr;
    // test SubscribeCommonEvent
    CommonEventSubscribeInfo subscribeInfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    EXPECT_EQ(
        ERR_NOTIFICATION_CES_COMMON_PARAM_INVALID, comm->SubscribeCommonEvent(subscribeInfo, commonEventListener));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0200 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0300
 * @tc.desc: test UnsubscribeCommonEvent function and IsReady is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0300, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0300 start";
    std::shared_ptr<CommonEventManagerService> comm = std::make_shared<CommonEventManagerService>();
    ASSERT_NE(nullptr, comm);
    // set IsReady is false
    comm->innerCommonEventManager_ = nullptr;
    // test SubscribeCommonEvent
    sptr<IRemoteObject> commonEventListener = nullptr;
    EXPECT_EQ(
        ERR_NOTIFICATION_CES_COMMON_PARAM_INVALID, comm->UnsubscribeCommonEvent(commonEventListener));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0300 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0400
 * @tc.desc: test GetStickyCommonEvent function and IsReady is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0400, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0400 start";
    std::shared_ptr<CommonEventManagerService> comm = std::make_shared<CommonEventManagerService>();
    ASSERT_NE(nullptr, comm);
    // set IsReady is false
    comm->innerCommonEventManager_ = nullptr;
    // test SubscribeCommonEvent
    std::string event = "aa";
    CommonEventData eventData;
    EXPECT_EQ(false, comm->GetStickyCommonEvent(event, eventData));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0400 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0500
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.isSubsystem is false and IsSystemApp is false
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0500, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0500 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set VerifyNativeToken is false
    MockVerifyNativeToken(false);
    // set IsSystemApp is false
    MockIsSystemApp(false);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    int32_t userId = 1;
    EXPECT_EQ(ERR_NOTIFICATION_CES_COMMON_NOT_SYSTEM_APP,
        comm->PublishCommonEvent(event, publishinfo, commonEventListener, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0500 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0600
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.isSubsystem is true and IsSystemApp is true
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0600, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0600 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set VerifyNativeToken is false
    MockVerifyNativeToken(true);
    // set IsSystemApp is false
    MockIsSystemApp(true);
    // set IsDlpHap is true
    MockIsDlpHap(true);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    int32_t userId = 1;
    EXPECT_EQ(ERR_NOTIFICATION_CES_NOT_SA_SYSTEM_APP,
        comm->PublishCommonEvent(event, publishinfo, commonEventListener, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0600 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0700
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.userId is ALL_USER.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0700, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0700 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set IsDlpHap is true
    MockIsDlpHap(true);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    int32_t userId = -1;
    EXPECT_EQ(ERR_NOTIFICATION_CES_NOT_SA_SYSTEM_APP,
        comm->PublishCommonEvent(event, publishinfo, commonEventListener, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0700 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0800
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.userId is CURRENT_USER.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0800, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0800 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set IsDlpHap is true
    MockIsDlpHap(true);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    int32_t userId = -2;
    EXPECT_EQ(ERR_NOTIFICATION_CES_NOT_SA_SYSTEM_APP,
        comm->PublishCommonEvent(event, publishinfo, commonEventListener, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0800 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_0900
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.userId is UNDEFINED_USER.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_0900, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0900 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set IsDlpHap is true
    MockIsDlpHap(true);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    int32_t userId = -3;
    EXPECT_EQ(ERR_NOTIFICATION_CES_NOT_SA_SYSTEM_APP,
        comm->PublishCommonEvent(event, publishinfo, commonEventListener, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_0900 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1000
 * @tc.desc: 1.test PublishCommonEvent function IsReady is true.
 *           2.VerifyNativeToken is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1000, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1000 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // set VerifyNativeToken is false
    MockVerifyNativeToken(false);
    // test PublishCommonEvent function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    uid_t uid = 1;
    int32_t callerToken = 2;
    int32_t userId = 1;
    EXPECT_EQ(false, comm->PublishCommonEvent(event, publishinfo, commonEventListener, uid, callerToken, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1000 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1100
 * @tc.desc: 1.test PublishCommonEventDetailed function.
 *           2.IsDlpHap is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1100, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1100 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsDlpHap is true
    MockIsDlpHap(true);
    // test PublishCommonEventDetailed function
    CommonEventData event;
    CommonEventPublishInfo publishinfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    pid_t pid = 1;
    uid_t uid = 2;
    int32_t clientToken = 1;
    int32_t userId = 1;
    EXPECT_EQ(ERR_NOTIFICATION_CES_NOT_SA_SYSTEM_APP,
        comm->PublishCommonEventDetailed(event, publishinfo, commonEventListener, pid, uid, clientToken, userId));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1100 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1200
 * @tc.desc: 1.test SubscribeCommonEvent function.
 *           2.IsReady is true and return ERR_OK.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1200, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1200 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    // test SubscribeCommonEvent function
    CommonEventSubscribeInfo subscribeInfo;
    sptr<IRemoteObject> commonEventListener = nullptr;
    EXPECT_EQ(ERR_OK, comm->SubscribeCommonEvent(subscribeInfo, commonEventListener));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1200 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1300
 * @tc.desc: 1.test DumpState function.
 *           2.VerifyShellToken is false and VerifyNativeToken is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1300, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1300 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set VerifyNativeToken is false
    MockVerifyNativeToken(false);
    // set VerifyShellToken is false
    MockVerifyShellToken(false);
    // test SubscribeCommonEvent function
    uint8_t dumpType = 1;
    std::string event = "<event>";
    int32_t userId = 1;
    std::vector<std::string> state;
    state.emplace_back(event);
    EXPECT_EQ(false, comm->DumpState(dumpType, event, userId, state));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1300 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1400
 * @tc.desc: 1.test DumpState function.
 *           2.VerifyShellToken is true and VerifyNativeToken is true.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1400, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1400 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set VerifyNativeToken is true
    MockVerifyNativeToken(true);
    // set VerifyShellToken is true
    MockVerifyShellToken(true);
    // test SubscribeCommonEvent function
    uint8_t dumpType = 1;
    std::string event = "<event>";
    int32_t userId = 1;
    std::vector<std::string> state;
    state.emplace_back(event);
    EXPECT_EQ(false, comm->DumpState(dumpType, event, userId, state));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1400 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1500
 * @tc.desc: 1.test Dump function.
 *           2.VerifyShellToken is false and VerifyNativeToken is false.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1500, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1500 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set VerifyNativeToken is false
    MockVerifyNativeToken(false);
    // set VerifyShellToken is false
    MockVerifyShellToken(false);
    // test SubscribeCommonEvent function
    int fd = 1;
    std::vector<std::u16string> args;
    EXPECT_EQ(ERR_NOTIFICATION_CES_COMMON_PERMISSION_DENIED, comm->Dump(fd, args));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1500 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1600
 * @tc.desc: 1.test Dump function.
 *           2.VerifyShellToken is true and VerifyNativeToken is true.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1600, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1600 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set VerifyNativeToken is true
    MockVerifyNativeToken(true);
    // set VerifyShellToken is true
    MockVerifyShellToken(true);
    // test SubscribeCommonEvent function
    int fd = 1;
    std::vector<std::u16string> args;
    EXPECT_EQ(ERR_INVALID_VALUE, comm->Dump(fd, args));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1600 end";
}

/**
 * @tc.name: CommonEventManagerServiceBranch_1700
 * @tc.desc: 1.test UnsubscribeCommonEvent function.
 *           2.IsReady is true.
 * @tc.type: FUNC
 */
HWTEST_F(CommonEventManagerServiceTest, CommonEventManagerServiceBranch_1700, Level1)
{
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1700 start";
    sptr<CommonEventManagerService> comm = new (std::nothrow) CommonEventManagerService();
    ASSERT_NE(nullptr, comm);
    // set IsReady is true
    comm->innerCommonEventManager_ = std::make_shared<InnerCommonEventManager>();
    comm->runner_ = EventRunner::Create("CesSrvMain");
    comm->handler_ = std::make_shared<EventHandler>(comm->runner_);
    EXPECT_EQ(ERR_OK, comm->UnsubscribeCommonEvent(nullptr));
    GTEST_LOG_(INFO) << "CommonEventManagerServiceBranch_1700 end";
}