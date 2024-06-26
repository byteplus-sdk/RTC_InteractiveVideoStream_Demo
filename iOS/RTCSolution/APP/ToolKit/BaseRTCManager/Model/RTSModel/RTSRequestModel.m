//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "RTSRequestModel.h"

@implementation RTSRequestModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{
        @"eventName": @"event_name",
        @"appID": @"app_id",
        @"roomID": @"room_id",
        @"userID": @"user_id",
        @"requestID": @"request_id",
        @"deviceID": @"device_id",
        @"imChannel": @"im_channel",
    };
}

@end
