/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatRoomSettingResolutionView : UIView
@property (nonatomic, copy) void (^resolutionChangeBlock)(NSInteger index);

- (void)setSelectedResKey:(NSString *)resKey;
@end

NS_ASSUME_NONNULL_END
