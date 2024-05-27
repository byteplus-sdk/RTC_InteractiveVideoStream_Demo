//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatSeatModel.h"

@implementation VideoChatSeatModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"userModel": @"guest_info"};
}

@end
