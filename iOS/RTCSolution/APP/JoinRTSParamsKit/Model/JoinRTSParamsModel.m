// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "JoinRTSParamsModel.h"

@implementation JoinRTSParamsModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"appId" : @"app_id",
             @"RTSToken" : @"rtm_token",
             @"serverUrl" : @"server_url",
             @"serverSignature" : @"server_signature",
             @"bid" : @"bid"
    };
}

@end
