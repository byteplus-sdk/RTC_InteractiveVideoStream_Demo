// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, VideoChatSettingVideoFpsType) {
    VideoChatSettingVideoFpsType_15,
    VideoChatSettingVideoFpsType_20
};

typedef NS_ENUM(NSUInteger, VideoChatSettingVideoResolutionType) {
    VideoChatSettingVideoResolutionType_480P = 0,
    VideoChatSettingVideoResolutionType_540P,
    VideoChatSettingVideoResolutionType_720P,
    VideoChatSettingVideoResolutionType_1080P
};

@interface VideoChatSettingVideoConfig : NSObject
@property (nonatomic, assign) VideoChatSettingVideoFpsType fpsType;
@property (nonatomic, assign) VideoChatSettingVideoResolutionType resolutionType;

@property (nonatomic, assign) CGFloat fps;
@property (nonatomic, assign) CGSize videoSize;
@property (nonatomic, assign) NSInteger bitrate;
@property (nonatomic, assign) NSInteger minBitrate;
@property (nonatomic, assign) NSInteger maxBitrate;
@property (nonatomic, assign) NSInteger defultBitrate;

+ (instancetype)defultVideoConfig;

+ (NSString *)defultResPullKey;

@end

NS_ASSUME_NONNULL_END
