// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "BaseUserModel.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VideoChatUserStatus) {
    VideoChatUserStatusDefault = 1,
    VideoChatUserStatusActive,
    VideoChatUserStatusApply,
    VideoChatUserStatusInvite,
};

typedef NS_ENUM(NSInteger, VideoChatUserRole) {
    VideoChatUserRoleNone = 0,
    VideoChatUserRoleHost = 1,
    VideoChatUserRoleAudience,
};

typedef NS_ENUM(NSInteger, VideoChatUserMic) {
    VideoChatUserMicOff = 0,
    VideoChatUserMicOn = 1,
};

typedef NS_ENUM(NSInteger, VideoChatUserCamera) {
    VideoChatUserCameraOff = 0,
    VideoChatUserCameraOn = 1,
};

typedef NS_ENUM(NSInteger, VideoChatPKReply) {
    VideoChatPKReplyAccept = 1,
    VideoChatPKReplyReject = 2,
    VideoChatPKReplyTimeOut = 3,
};

typedef NS_ENUM(NSInteger, VideoChatRoomMode) {
    VideoChatRoomModeMakeCoHost = 1,
    VideoChatRoomModeChatRoom = 2,
};

typedef NS_ENUM(NSInteger, VideoChatOtherAnchorMicType) {
    VideoChatOtherAnchorMicTypeMute = 0,
    VideoChatOtherAnchorMicTypeUnmute = 1,
};

@interface VideoChatUserModel : BaseUserModel

@property (nonatomic, copy) NSString *roomID;

@property (nonatomic, assign) VideoChatUserRole userRole;

@property (nonatomic, assign) VideoChatUserStatus status;

@property (nonatomic, assign) VideoChatUserMic mic;

@property (nonatomic, assign) VideoChatUserCamera camera;

@property (nonatomic, assign) NSInteger volume;

@property (nonatomic, assign) BOOL isSpeak;

@property (nonatomic, assign) VideoChatOtherAnchorMicType otherAnchorMicType;

@property (nonatomic, copy) NSString *pkToken;

- (void)bindOtherAnchorMicType:(NSDictionary *)dict;

@end

NS_ASSUME_NONNULL_END
