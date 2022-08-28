/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class VideoChatRoomGuestSettingView;
@protocol VideoChatRoomGuestSettingViewDelegate <NSObject>

- (void)videoChatRoomGuestSettingView:(VideoChatRoomGuestSettingView *)settingView didSwitchCamera:(BOOL)isFront;
- (void)videoChatRoomGuestSettingView:(VideoChatRoomGuestSettingView *)settingView didChangeMicState:(BOOL)isOn;
- (void)videoChatRoomGuestSettingView:(VideoChatRoomGuestSettingView *)settingView didChangeCameraState:(BOOL)isOn;
- (void)videoChatRoomGuestSettingViewDidClickMusic:(VideoChatRoomGuestSettingView *)settingView;

@end

@interface VideoChatRoomGuestSettingView : UIView
@property (nonatomic, weak) id<VideoChatRoomGuestSettingViewDelegate> delegate;

@property (nonatomic, assign) BOOL isMicOn;
@property (nonatomic, assign) BOOL isCameraOn;

- (instancetype)initWithHost:(BOOL)isHost;

@end

NS_ASSUME_NONNULL_END
