// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatSettingVideoConfig.h"
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@class VideoChatCreateRoomSettingView;

@protocol VideoChatCreateRoomSettingViewDelegate <NSObject>

- (void)videoChatCreateRoomSettingView:(VideoChatCreateRoomSettingView *)settingView didChangefpsType:(VideoChatSettingVideoFpsType)fpsType;

- (void)videoChatCreateRoomSettingView:(VideoChatCreateRoomSettingView *)settingView didChangeResolution:(NSInteger)index;

- (void)videoChatCreateRoomSettingView:(VideoChatCreateRoomSettingView *)settingView didChangeBitrate:(NSInteger)bitrate;

@end

@interface VideoChatCreateRoomSettingView : UIView
@property (nonatomic, weak) id<VideoChatCreateRoomSettingViewDelegate> delegate;

@property (nonatomic, strong) VideoChatSettingVideoConfig *videoConfig;
@end

NS_ASSUME_NONNULL_END
