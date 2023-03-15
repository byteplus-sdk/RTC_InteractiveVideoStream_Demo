/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import "VideoChatRTCManager.h"
#import <BytePlusRTC/objc/ByteRTCVideo.h>

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VideoChatNetworkQualityStatus) {
    VideoChatNetworkQualityStatusNone,
    VideoChatNetworkQualityStatusGood,
    VideoChatNetworkQualityStatusBad,
};
typedef void(^VideoChatNetworkQualityChangeBlock)(VideoChatNetworkQualityStatus status, NSString *uid);

@class VideoChatRTCManager;
@protocol VideoChatRTCManagerDelegate <NSObject>

- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager reportAllAudioVolume:(NSDictionary<NSString *, NSNumber *> *_Nonnull)volumeInfo;

- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager onFirstRemoteVideoUid:(NSString *)uid;

@end

@interface VideoChatRTCManager : BaseRTCManager

@property (nonatomic, weak) id<VideoChatRTCManagerDelegate> delegate;

/*
 * RTC Manager Singletons
 */
+ (VideoChatRTCManager *_Nullable)shareRtc;

#pragma mark - Base Method

/**
 * Update video encoding parameters
 * @param isHost Host
 */
- (void)updateVideoConfigWithHost:(BOOL)isHost;

/**
 * Join room
 * @param token token
 * @param roomID roomID
 * @param uid uid
 */
- (void)joinRTCRoomWithToken:(NSString *)token roomID:(NSString *)roomID uid:(NSString *)uid userRole:(BOOL)isHost;

/*
 * Set user visibility
 * @param enable Enable
 */
- (void)setUserVisibility:(BOOL)enable;

/*
 * Switch local audio capture
 * @param enable ture:Turn on audio capture false：Turn off audio capture
 */
- (void)enableLocalAudio:(BOOL)enable;

/*
 * Switch local video capture
 * @param enable ture:Turn on audio capture false：Turn off video capture
 */
- (void)enableLocalVideo:(BOOL)enable;

/*
 * Switch the camera
 */
- (void)switchCamera;

/*
 * Set the camera is front
 */
- (void)updateCameraID:(BOOL)isFront;

/*
 * Switch local audio capture
 * @param mute ture:Turn on audio capture false：Turn off audio capture
 */
- (void)muteLocalAudio:(BOOL)mute;

/*
 * Switch local video push stream
 * @param mute ture:Turn on video push stream false：Turn off video push stream
 */
- (void)muteLocalVideo:(BOOL)mute;

/*
 * Update resolution
 */
- (void)updateRes:(CGSize)size;

/*
 * Update frame rate
 */
- (void)updateFPS:(CGFloat)fps;

/*
 * Update bit rate
 */
- (void)updateKBitrate:(NSInteger)kbitrate;

/*
 * Reset video encoder settings
 */
- (void)setDefaultVideoEncoderConfig;

/*
 * Leave the room
 */
- (void)leaveChannel;

/*
 * Get Sdk Version
 */
- (NSString *_Nullable)getSdkVersion;

#pragma mark - Background Music Method

/*
 * Turn on background music
 */
- (void)startBackgroundMusic:(NSString *)filePath;

/*
 * Pause background music
 */
- (void)pauseBackgroundMusic;

/*
 * Restore background music
 */
- (void)resumeBackgroundMusic;

/*
 * Modify the collection volume
 */
- (void)setRecordingVolume:(NSInteger)volume;

/*
 * Modify the background music volume
 */
- (void)setMusicVolume:(NSInteger)volume;

#pragma mark - Render

/*
 * Get stream render view
 */
- (UIView *)getStreamViewWithUid:(NSString *)uid;

/*
 * Bind the stream to render the view
 */
- (void)bingCanvasViewToUid:(NSString *)uid;

#pragma mark - NetworkQuality

/*
 * Monitor network changes
 */
- (void)didChangeNetworkQuality:(VideoChatNetworkQualityChangeBlock)block;

#pragma mark - PK

/*
 * Start forward stream
 */
- (void)startForwardStream:(NSString *)roomID token:(NSString *)token;

/*
 * Stop forward stream
 */
- (void)stopForwardStream;

/*
 * Turn off other user of audio
 */
- (void)muteOtherAnchorUserID:(NSString *)userID mute:(BOOL)isMute;

@end

NS_ASSUME_NONNULL_END
