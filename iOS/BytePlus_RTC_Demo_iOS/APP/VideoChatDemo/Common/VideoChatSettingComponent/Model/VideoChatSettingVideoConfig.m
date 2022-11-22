/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatSettingVideoConfig.h"

@implementation VideoChatSettingVideoConfig

+ (instancetype)defultVideoConfig {
    static VideoChatSettingVideoConfig *_instance;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
      _instance = [[self alloc] init];
    });

    return _instance;
}

+ (NSString *)defultResPullKey {
    return @"720";
}

- (instancetype)init {
    if (self = [super init]) {
        self.fpsType = VideoChatSettingVideoFpsType_15;
        self.resolutionType = VideoChatSettingVideoResolutionType_720P;
        self.bitrate = 1600;
    }
    return self;
}

- (void)setFpsType:(VideoChatSettingVideoFpsType)fpsType {
    _fpsType = fpsType;

    CGFloat fps = 0.0;
    switch (fpsType) {
        case VideoChatSettingVideoFpsType_15: {
            fps = 15.0;
        } break;
        case VideoChatSettingVideoFpsType_20: {
            fps = 20.0;
        } break;

        default: {
            fps = 15.0;
        } break;
    }
    self.fps = fps;
}

- (void)setResolutionType:(VideoChatSettingVideoResolutionType)resolutionType {
    _resolutionType = resolutionType;

    NSInteger minKbps = 0;
    NSInteger maxKbps = 0;
    NSInteger defultKbps = 0;
    CGSize videoSize = CGSizeZero;

    switch (resolutionType) {
        case 0: {
            minKbps = 320;
            maxKbps = 1266;
            defultKbps = 1000;
            videoSize = CGSizeMake(450, 800);
        } break;
        case 1: {
            minKbps = 500;
            maxKbps = 1520;
            defultKbps = 1200;
            videoSize = CGSizeMake(540, 960);
        } break;
        case 2: {
            minKbps = 800;
            maxKbps = 1900;
            defultKbps = 1600;
            videoSize = CGSizeMake(720, 1280);
        } break;
        case 3: {
            minKbps = 1000;
            maxKbps = 3800;
            defultKbps = 2800;
            videoSize = CGSizeMake(1080, 1920);
        } break;

        default:
            break;
    }

    if (self.bitrate == 0) {
        self.bitrate = defultKbps;
    }
    if (self.bitrate < minKbps) {
        self.bitrate = minKbps;
    }
    if (self.bitrate > maxKbps) {
        self.bitrate = maxKbps;
    }

    self.minBitrate = minKbps;
    self.maxBitrate = maxKbps;
    self.defultBitrate = defultKbps;
    self.videoSize = videoSize;
}
@end
