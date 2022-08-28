/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#import "VideoChatSheetView.h"
@class VideoChatSeatCompoments;

NS_ASSUME_NONNULL_BEGIN

@protocol VideoChatSeatDelegate <NSObject>

- (void)VideoChatSeatCompoments:(VideoChatSeatCompoments *)VideoChatSeatCompoments
                    clickButton:(VideoChatSeatModel *)seatModel
                    sheetStatus:(VideoChatSheetStatus)sheetStatus;

@end

@interface VideoChatSeatCompoments : NSObject

@property (nonatomic, weak) id<VideoChatSeatDelegate> delegate;
@property (nonatomic, strong) VideoChatUserModel *loginUserModel;
@property (nonatomic, strong) VideoChatUserModel *hostUserModel;

- (instancetype)initWithSuperView:(UIView *)superView;

- (void)showSeatView:(NSArray<VideoChatSeatModel *> *)seatList
      loginUserModel:(VideoChatUserModel *)loginUserModel
       hostUserModel:(VideoChatUserModel *)hostUserModel;

- (void)addSeatModel:(VideoChatSeatModel *)seatModel;

- (void)removeUserModel:(VideoChatUserModel *)userModel;

- (void)updateSeatModel:(VideoChatSeatModel *)seatModel;

- (void)updateSeatVolume:(NSDictionary *)volumeDic;

- (void)updateSeatRender:(NSString *)uid;

- (void)updateNetworkQuality:(VideoChatNetworkQualityStatus)status uid:(NSString *)uid;

- (void)changeChatRoomMode:(VideoChatRoomMode)mode;

- (void)audienceApplyInteraction;

@end

NS_ASSUME_NONNULL_END
