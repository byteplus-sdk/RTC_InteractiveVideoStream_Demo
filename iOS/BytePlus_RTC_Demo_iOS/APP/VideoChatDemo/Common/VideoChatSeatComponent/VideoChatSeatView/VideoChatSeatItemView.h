/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

@interface VideoChatSeatItemView : UIView

@property (nonatomic, assign) NSInteger index;

@property (nonatomic, strong) VideoChatSeatModel *seatModel;

@property (nonatomic, copy) void (^clickBlock)(VideoChatSeatModel *seatModel);

- (void)updateRender;

- (void)updateNetworkQualityStstus:(VideoChatNetworkQualityStatus)status;

@end
