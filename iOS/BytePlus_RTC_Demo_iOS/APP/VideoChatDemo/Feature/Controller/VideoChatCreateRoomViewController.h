/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatNavViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatCreateRoomViewController : VideoChatNavViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                        userModel:(VideoChatUserModel *)userModel
                         rtcToekn:(NSString *)rtcToekn;

@end

NS_ASSUME_NONNULL_END
