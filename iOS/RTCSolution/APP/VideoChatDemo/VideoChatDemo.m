//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatDemo.h"
#import "JoinRTSParams.h"
#import "NetworkReachabilityManager.h"
#import "VideoChatRoomListsViewController.h"

@implementation VideoChatDemo

- (void)pushDemoViewControllerBlock:(void (^)(BOOL))block {
    [super pushDemoViewControllerBlock:block];

    JoinRTSInputModel *inputModel = [[JoinRTSInputModel alloc] init];
    inputModel.scenesName = self.scenesName;
    inputModel.loginToken = [LocalUserComponent userModel].loginToken;
    __weak __typeof(self) wself = self;
    [JoinRTSParams getJoinRTSParams:inputModel
                              block:^(JoinRTSParamsModel *_Nonnull model) {
                                  [wself joinRTS:model block:block];
                              }];
}

- (void)joinRTS:(JoinRTSParamsModel *_Nonnull)model
          block:(void (^)(BOOL result))block {
    if (!model) {
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"connection_failed")];
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
                                              VideoChatRoomListsViewController *next = [[VideoChatRoomListsViewController alloc] init];
                                              UIViewController *topVC = [DeviceInforTool topViewController];
                                              [topVC.navigationController pushViewController:next animated:YES];
                                          } else {
                                              [[ToastComponent shareToastComponent] showWithMessage:LocalizedString(@"connection_failed")];
                                          }
                                          if (block) {
                                              block(result);
                                          }
                                      }];
}

@end
