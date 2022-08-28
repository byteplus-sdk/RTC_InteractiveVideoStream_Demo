/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Core/Localizator.h>
#import "VideoChatDemo.h"
#import "VideoChatRoomListsViewController.h"
#import "NetworkReachabilityManager.h"

@implementation VideoChatDemo

- (void)pushDemoViewControllerBlock:(void (^)(BOOL))block {
    [[ToastComponents shareToastComponents] showLoading];
    [VideoChatRTCManager shareRtc].networkDelegate = [NetworkReachabilityManager sharedManager];
    [[VideoChatRTCManager shareRtc] connect:@"videochat"
                                 loginToken:[LocalUserComponents userModel].loginToken
                                      block:^(BOOL result) {
        if (result) {
            [[ToastComponents shareToastComponents] dismiss];
            VideoChatRoomListsViewController *next = [[VideoChatRoomListsViewController alloc] init];
            UIViewController *topVC = [DeviceInforTool topViewController];
            [topVC.navigationController pushViewController:next animated:YES];
        } else {
            [[ToastComponents shareToastComponents] showWithMessage:LocalizedString(@"Connection failed")];
        }
        if (block) {
            block(result);
        }
    }];
}

@end
