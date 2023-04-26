// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "MenuLoginHome.h"
#import "NetworkingManager.h"
#import "MenuLoginViewController.h"

@implementation MenuLoginHome

#pragma mark - Publish Action

+ (void)showLoginViewControllerAnimated:(BOOL)isAnimation {
    // 开启网络监听
    [[NetworkReachabilityManager sharedManager] startMonitoring];
    
    if (IsEmptyStr([LocalUserComponent userModel].loginToken)) {
        [MenuLoginHome showLoginVC:isAnimation];
    }
}

+ (void)closeAccount:(void (^)(BOOL result))block {
    if (block) {
        block(YES);
    }
}

#pragma mark - Private Action

+ (void)showLoginVC:(BOOL)isAnimation {
    UIViewController *topVC = [DeviceInforTool topViewController];
    MenuLoginViewController *loginVC = [[MenuLoginViewController alloc] init];
    loginVC.modalPresentationStyle = UIModalPresentationFullScreen;
    [topVC presentViewController:loginVC animated:isAnimation completion:^{

    }];
}

@end
