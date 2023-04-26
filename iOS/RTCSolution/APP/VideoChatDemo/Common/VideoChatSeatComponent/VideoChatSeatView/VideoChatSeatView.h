// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface VideoChatSeatView : UIView

@property (nonatomic, copy) void (^clickBlock)(VideoChatSeatModel *seatModel);

@property (nonatomic, copy) NSArray<VideoChatSeatModel *> *seatList;

- (void)addSeatModel:(VideoChatSeatModel *)seatModel;

- (void)removeUserModel:(VideoChatUserModel *)userModel;

- (void)updateSeatModel:(VideoChatSeatModel *)seatModel;

- (void)updateSeatRender:(NSString *)uid;

- (void)updateSeatVolume:(NSDictionary *)volumeDic;

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid;

@end

NS_ASSUME_NONNULL_END
