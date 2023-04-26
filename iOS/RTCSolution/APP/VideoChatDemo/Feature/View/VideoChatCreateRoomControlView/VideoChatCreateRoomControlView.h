// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class VideoChatCreateRoomControlView;

@protocol VideoChatCreateRoomControlViewDelegate <NSObject>

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSwitchCameraButton:(UIButton *)button;

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedBeautyButton:(UIButton *)button;

- (void)videoChatCreateRoomControlView:(VideoChatCreateRoomControlView *)videoChatCreateRoomControlView didClickedSettingButton:(UIButton *)button;

@end

@interface VideoChatCreateRoomControlView : UIView

@property (nonatomic, weak) id<VideoChatCreateRoomControlViewDelegate> delegate;

@end

NS_ASSUME_NONNULL_END
