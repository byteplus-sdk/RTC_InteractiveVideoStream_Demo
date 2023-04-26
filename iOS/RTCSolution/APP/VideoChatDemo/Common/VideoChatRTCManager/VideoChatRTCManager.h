// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import "VideoChatRTCManager.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, VideoChatNetworkQualityStatus) {
    VideoChatNetworkQualityStatusNone,
    VideoChatNetworkQualityStatusGood,
    VideoChatNetworkQualityStatusBad,
};
typedef void(^VideoChatNetworkQualityChangeBlock)(VideoChatNetworkQualityStatus status, NSString *uid);

@class VideoChatRTCManager;
@protocol VideoChatRTCManagerDelegate <NSObject>

/**
 * @brief Callback on room state changes. Via this callback you get notified of room relating warnings, errors and events. For example, the user joins the room, the user is removed from the room, and so on.
 * @param manager GameRTCManager model
 * @param userID UserID
 */
- (void)videoChatRTCManager:(VideoChatRTCManager *)manager
         onRoomStateChanged:(RTCJoinModel *)joinModel;


/**
 * @brief Callback for volume information changes
 * @param videoChatRTCManager GameRTCManager object
 * @param volumeInfo Voice volume data, key is user id, value is volume decibel range [0,255].
 */
- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager reportAllAudioVolume:(NSDictionary<NSString *, NSNumber *> *_Nonnull)volumeInfo;

/**
 * @brief The first frame callback received from the remote end
 * @param videoChatRTCManager GameRTCManager object
 * @param uid RTC user ID
 */
- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager onFirstRemoteVideoUid:(NSString *)uid;

/**
 * @brief Receive local and remote user RTC network status callback
 * @param status network quality enumeration
 * @param uid user ID
 */
- (void)videoChatRTCManager:(VideoChatRTCManager *_Nonnull)videoChatRTCManager
    didChangeNetworkQuality:(VideoChatNetworkQualityStatus)status
                        uid:(NSString *)uid;

@end

@interface VideoChatRTCManager : BaseRTCManager

@property (nonatomic, weak) id<VideoChatRTCManagerDelegate> delegate;

+ (VideoChatRTCManager *_Nullable)shareRtc;

/**
 * @brief Join the RTC room
 * @param token RTC Token
 * @param roomID RTC room ID
 * @param uid RTC user ID
 * @param isHost user role. YES: anchor, NO: audience
 */
- (void)joinRTCRoomWithToken:(NSString *)token
                      roomID:(NSString *)roomID
                         uid:(NSString *)uid
                    userRole:(BOOL)isHost;

/**
 * @brief Leave RTC room
 */
- (void)leaveRTCRoom;

#pragma mark - Audience on mic

/**
 * @brief Make guest
 * @param camera switch status of the camera. YES: On, NO: Off
 * @param microphone microphone switch status. YES: On, NO: Off
 */
- (void)makeGuest:(BOOL)camera
       microphone:(BOOL)microphone;

/**
 * @brief Make audience, the guest becomes an audience after the mic
 */
- (void)makeAudience;

#pragma mark - Host PK

/**
 * @brief enable forward stream RTC rooms
 * @param roomID The other party's room ID
 * @param token RTC Token required to join the other party's room
 */
- (void)startForwardStream:(NSString *)roomID
                     token:(NSString *)token;


/**
 * @brief turn off forward stream RTC rooms
 */
- (void)stopForwardStream;

#pragma mark - Setting

/**
 * @brief switch front/rear camera
 * @param enable true: open, false: close
 */
- (void)switchVideoCapture:(BOOL)enable;

/**
 * @brief switch front/rear camera
 */
- (void)switchCamera;

/**
 * @brief Control the sending status of the local video stream: send/not send
 * @param isPublish ture:Send, false：Not send
 */
- (void)publishVideoStream:(BOOL)isPublish;

/**
 * @brief Control the sending status of the local audio stream: send/not send
 * @param isPublish ture:Send, false：Not send
 */
- (void)publishAudioStream:(BOOL)isPublish;

/**
 * @brief subscribe to remote audio stay
 * @param userID RTC user ID
 * @param isSubscribe true: subscribe, false: unsubscribe
 */
- (void)subscribeRemoteAudioStream:(NSString *)userID
                         subscribe:(BOOL)isSubscribe;

/**
 * @brief Update RTC video encoding parameters according to user roles
 * @param isHost true: host, false: audience
 */
- (void)updateVideoConfigWithHost:(BOOL)isHost;

/**
 * @brief Update RTC encoding resolution.
 * @param size resolution
 */
- (void)updateResolution:(CGSize)size;

/**
 * @brief update RTC encoding frame rate
 * @param fps frame rate
 */
- (void)updateFrameRate:(CGFloat)fps;

/**
 * @brief update RTC code rate
 * @param kbitrate code rate
 */
- (void)updateBitRate:(NSInteger)bitRate;

#pragma mark - Background Music Method

/**
 * @brief Turn on the background music
 * @param filePath music sandbox path
 */
- (void)startBackgroundMusic:(NSString *)filePath;

/**
 * @brief Pause background music
 */
- (void)pauseBackgroundMusic;

/**
 * @brief Resume background music playback
 */
- (void)resumeBackgroundMusic;

/**
 * @brief set vocal volume
 * @param volume volume
 */
- (void)setRecordingVolume:(NSInteger)volume;

/**
 * @brief set background volume
 * @param volume volume
 */
- (void)setMusicVolume:(NSInteger)volume;

#pragma mark - Render

/**
 * @brief Get RTC rendering UIView
 * @param uid user ID
 */
- (UIView *)getStreamViewWithUid:(NSString *)uid;

/**
 * @brief user ID and RTC rendering View for binding
 * @param uid User id
 */

/**
 * @brief 用户 ID 和 RTC 渲染 View 进行绑定
 * @param uid 用户ID
 */
- (void)bindCanvasViewToUid:(NSString *)uid;

@end

NS_ASSUME_NONNULL_END
