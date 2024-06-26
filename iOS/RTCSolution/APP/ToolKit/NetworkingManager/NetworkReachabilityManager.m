//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "NetworkReachabilityManager.h"
#import "DeviceInforTool.h"
#import "LocalizatorBundle.h"
#import "ToastComponent.h"
#import <AFNetworking/AFNetworkReachabilityManager.h>
#import <CoreTelephony/CTTelephonyNetworkInfo.h>

@interface NetworkReachabilityManager ()

@property (nonatomic, strong) AFNetworkReachabilityManager *reachabilityManager;

@property (nonatomic, assign) BOOL isMissConnect;

@end

@implementation NetworkReachabilityManager

+ (instancetype)sharedManager {
    static NetworkReachabilityManager *_sharedManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _sharedManager = [[self alloc] init];
    });

    return _sharedManager;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.reachabilityManager = [AFNetworkReachabilityManager manager];
        self.isMissConnect = NO;
        __weak typeof(self) weak_self = self;
        [self.reachabilityManager setReachabilityStatusChangeBlock:^(AFNetworkReachabilityStatus status) {
            [weak_self onReachabilityStatusChanged:status];
        }];
    }
    return self;
}

- (void)startMonitoring {
    [self.reachabilityManager startMonitoring];
}

- (void)stopMonitoring {
    [self.reachabilityManager stopMonitoring];
}

- (NSString *)getNetType {
    CTTelephonyNetworkInfo *info = [CTTelephonyNetworkInfo new];
    NSString *networkType = @"";
    if ([info respondsToSelector:@selector(currentRadioAccessTechnology)]) {
        NSString *currentStatus = info.currentRadioAccessTechnology;
        NSArray *network2G = @[CTRadioAccessTechnologyGPRS, CTRadioAccessTechnologyEdge, CTRadioAccessTechnologyCDMA1x];
        NSArray *network3G = @[CTRadioAccessTechnologyWCDMA, CTRadioAccessTechnologyHSDPA, CTRadioAccessTechnologyHSUPA, CTRadioAccessTechnologyCDMAEVDORev0, CTRadioAccessTechnologyCDMAEVDORevA, CTRadioAccessTechnologyCDMAEVDORevB, CTRadioAccessTechnologyeHRPD];
        NSArray *network4G = @[CTRadioAccessTechnologyLTE];

        if ([network2G containsObject:currentStatus]) {
            networkType = @"2G";
        } else if ([network3G containsObject:currentStatus]) {
            networkType = @"3G";
        } else if ([network4G containsObject:currentStatus]) {
            networkType = @"4G";
        } else {
            networkType = @"unknown network";
        }
    }
    return networkType;
}

#pragma mark - Private Action

- (void)onReachabilityStatusChanged:(AFNetworkReachabilityStatus)status {
    [self showSocketIsDisconnect:status == AFNetworkReachabilityStatusNotReachable];
}

- (void)showSocketIsDisconnect:(BOOL)isDisconnect {
    if (isDisconnect) {
        self.isMissConnect = YES;
        UIWindow *keyWindow = [UIApplication sharedApplication].keyWindow;
        [[ToastComponent shareToastComponent] showWithMessage:LocalizedStringFromBundle(@"network_link_down", @"ToolKit") view:keyWindow keep:YES block:^(BOOL result){

        }];
    } else {
        self.isMissConnect = NO;
        [[ToastComponent shareToastComponent] dismiss];
    }
}

- (BOOL)isDisconnect {
    return self.isMissConnect;
}

@end
