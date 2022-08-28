/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "RTMRequestModel.h"

@implementation RTMRequestModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"eventName" : @"event_name",
             @"appID" : @"app_id",
             @"roomID" : @"room_id",
             @"userID" : @"user_id",
             @"requestID" : @"request_id",
             @"deviceID" : @"device_id"};
}

@end
