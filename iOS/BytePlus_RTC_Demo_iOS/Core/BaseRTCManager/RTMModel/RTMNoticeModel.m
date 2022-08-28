/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "RTMNoticeModel.h"

@implementation RTMNoticeModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"eventName" : @"event"};
}

@end
