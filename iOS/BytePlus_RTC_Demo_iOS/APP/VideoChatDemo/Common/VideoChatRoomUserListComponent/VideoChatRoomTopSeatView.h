/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomTopSeatView : UIView

@property (nonatomic, copy) void(^clickCloseChatRoomBlock)(void);

- (void)updateCloseChatRoom:(BOOL)isHidden;

@end

NS_ASSUME_NONNULL_END
