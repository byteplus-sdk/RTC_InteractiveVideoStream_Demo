// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VideoChatRoomStatus) {
    VideoChatRoomStatusCreate = 1,
    VideoChatRoomStatusLiving = 2,
    VideoChatRoomStatusEnd = 3,
    VideoChatRoomStatusMakeGuest = 4,
    VideoChatRoomStatusMakeCoHost = 5,
};

@interface VideoChatRoomModel : NSObject

@property (nonatomic, copy) NSString *appID;
@property (nonatomic, copy) NSString *roomID;
@property (nonatomic, copy) NSString *roomName;
@property (nonatomic, copy) NSString *hostUid;
@property (nonatomic, copy) NSString *hostName;
@property (nonatomic, assign) NSInteger enableAudienceApply;
@property (nonatomic, copy) NSString *ext;
@property (nonatomic, copy) NSDictionary *extDic;
@property (nonatomic, assign) NSInteger audienceCount;
@property (nonatomic, assign) VideoChatRoomStatus roomStatus;

@end

NS_ASSUME_NONNULL_END
