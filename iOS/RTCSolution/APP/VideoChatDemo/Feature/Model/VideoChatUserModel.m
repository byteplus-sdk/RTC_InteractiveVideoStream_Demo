// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatUserModel.h"

@implementation VideoChatUserModel

+ (NSDictionary *)modelCustomPropertyMapper {
    return @{@"roomID" : @[@"room_id", @"from_room_id", @"to_room_id"],
             @"uid" : @[@"user_id", @"from_user_id", @"to_user_id"],
             @"name" : @[@"user_name", @"from_user_name", @"to_user_name"],
             @"userRole" : @"user_role",
             @"otherAnchorMicType" : @"audio_status_this_room",
             @"pkToken" : @"token",
    };
}

- (BOOL)isSpeak {
    if (self.volume >= 60) {
        _isSpeak = YES;
    } else {
        _isSpeak = NO;
    }
    return _isSpeak;
}

- (void)bindOtherAnchorMicType:(NSDictionary *)dict {
    if (dict[@"audio_status_this_room"]) {
        self.otherAnchorMicType = [dict[@"audio_status_this_room"] integerValue];
    }
}


@end
