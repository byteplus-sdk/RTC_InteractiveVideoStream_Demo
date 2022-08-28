/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#import <BytePlusRTC/objc/rtc/ByteRTCEngineKit.h>
#import <BytePlusRTC/objc/rtc/ByteRTCRoom.h>
#import <YYModel/YYModel.h>
#import "RTMRequestModel.h"
#import "RTMACKModel.h"
#import "RTMNoticeModel.h"
#import "LocalUserComponents.h"
#import "PublicParameterCompoments.h"

NS_ASSUME_NONNULL_BEGIN

@protocol RTCNetworkProtocol <NSObject>

@optional

- (void)networkTypeChangedToType:(ByteRTCNetworkType)type;

- (void)didStartNetworkMonitoring;

- (void)didStopNetworkMonitoring;

@end

typedef void (^RTCRoomMessageBlock)(RTMNoticeModel *noticeModel);

@interface BaseRTCManager : NSObject <ByteRTCEngineDelegate, RTCRoomDelegate>

@property (nonatomic, strong, nullable) ByteRTCEngineKit *rtcEngineKit;

@property (nonatomic, copy, nullable) void (^rtcJoinRoomBlock)(NSString *roomId, NSInteger errorCode, NSInteger joinType);

@property (nonatomic, weak, nullable) id<RTCNetworkProtocol> networkDelegate;

/// 开启连接
/// @param scenes 场景标记
/// @param loginToken 用户登录token
/// @param block Callback
- (void)connect:(NSString *)scenes
     loginToken:(NSString *)loginToken
          block:(void (^)(BOOL result))block;

/// 关闭连接
- (void)disconnect;

/// 接口请求
- (void)emitWithAck:(NSString *)event
               with:(NSDictionary *)item
              block:(__nullable RTCSendServerMessageBlock)block;
           
/// 注册广播监听
- (void)onSceneListener:(NSString *)key
                  block:(RTCRoomMessageBlock)block;

/// 移除广播监听
- (void)offSceneListener;

/// 多房间,用于需要额外房间需求时使用
- (void)joinMultiRoomByToken:(NSString *)token
                    roomID:(NSString *)roomID
                    userID:(NSString *)userID;

/// 多房间,离开房间
- (void)leaveMultiRoom;

/// Get Sdk Version
+ (NSString *_Nullable)getSdkVersion;

#pragma mark - config

/// 父类每次初始化rtcEngineKit时会调用，子类直接覆写实现。
- (void)configeRTCEngine;

@end

NS_ASSUME_NONNULL_END
