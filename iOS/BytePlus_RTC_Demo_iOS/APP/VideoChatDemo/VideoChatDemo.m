/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "JoinRTSParams.h"
#import "VideoChatDemo.h"
#import "VideoChatRoomListsViewController.h"
#import "NetworkReachabilityManager.h"

@implementation VideoChatDemo

- (void)pushDemoViewControllerBlock:(void (^)(BOOL))block {
    [[ToastComponent shareToastComponent] showLoading];
    [VideoChatRTCManager shareRtc].networkDelegate = [NetworkReachabilityManager sharedManager];
    JoinRTSInputModel *inputModel = [[JoinRTSInputModel alloc] init];
    inputModel.scenesName = @"videochat";
    inputModel.loginToken = [LocalUserComponent userModel].loginToken;
    __weak __typeof(self) wself = self;
    [JoinRTSParams getJoinRTSParams:inputModel
                              block:^(JoinRTSParamsModel * _Nonnull model) {
        [wself joinRTS:model block:block];
    }];
}

- (void)joinRTS:(JoinRTSParamsModel * _Nonnull)model
          block:(void (^)(BOOL result))block{
    if (!model) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Connection failed")];
        if (block) {
            block(NO);
        }
        return;
    }
    // Connect RTS
    [[VideoChatRTCManager shareRtc] connect:model.appId
                                   RTSToken:model.RTSToken
                                  serverUrl:model.serverUrl
                                  serverSig:model.serverSignature
                                        bid:model.bid
                                      block:^(BOOL result) {
        if (result) {
            [[ToastComponent shareToastComponent] dismiss];
            VideoChatRoomListsViewController *next = [[VideoChatRoomListsViewController alloc] init];
            UIViewController *topVC = [DeviceInforTool topViewController];
            [topVC.navigationController pushViewController:next animated:YES];
        } else {
            [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"Connection failed")];
        }
        if (block) {
            block(result);
        }
    }];
}

@end

