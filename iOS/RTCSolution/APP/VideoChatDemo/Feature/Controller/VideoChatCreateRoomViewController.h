// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "BaseViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatCreateRoomViewController : BaseViewController

- (instancetype)initWithRoomModel:(VideoChatRoomModel *)roomModel
                        userModel:(VideoChatUserModel *)userModel
                         rtcToekn:(NSString *)rtcToekn;

@end

NS_ASSUME_NONNULL_END
