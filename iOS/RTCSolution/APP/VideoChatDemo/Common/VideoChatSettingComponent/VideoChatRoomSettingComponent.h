//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "VideoChatUserModel.h"
#import <UIKit/UIKit.h>

typedef NS_ENUM(NSUInteger, VideoChatRoomSettingType) {
    VideoChatRoomSettingTypeCreateRoom,
    VideoChatRoomSettingTypeGuest
};

@interface VideoChatRoomSettingComponent : NSObject

@property (nonatomic, assign) BOOL mic;
@property (nonatomic, assign) BOOL camera;
@property (nonatomic, copy) void (^clickMusicBlock)(void);

- (instancetype)initWithHost:(BOOL)isHost;

- (void)showWithType:(VideoChatRoomSettingType)type
       fromSuperView:(UIView *)superView
           roomModel:(VideoChatRoomModel *)videoChatRoomModel;

- (void)updateUserMic:(BOOL)isEnable;

- (void)resetMicAndCameraStatus;

@end
