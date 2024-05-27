//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSettingBitrateView : UIView
@property (nonatomic, assign) NSInteger minBitrate;
@property (nonatomic, assign) NSInteger maxBitrate;
@property (nonatomic, assign) NSInteger bitrate;

@property (nonatomic, copy) void (^bitrateDidChangedBlock)(NSInteger bitrate);
@end

NS_ASSUME_NONNULL_END
