/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief Objective-C BytePlusRTC Common Defines
*/

#import <CoreMedia/CMTime.h>
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
typedef UIView   ByteRTCView;
typedef UIImage  ByteRTCImage;
#elif TARGET_OS_MAC
#import <AppKit/AppKit.h>
typedef NSView   ByteRTCView;
typedef NSImage  ByteRTCImage;
#endif

#define BYTERTC_APPLE_EXPORT __attribute__((visibility("default")))

/** 
 *  @type keytype
 *  @brief  The reason why the user leaves the room.   <br>
 */
typedef NS_ENUM(NSUInteger, ByteRTCUserOfflineReason) {
    /** 
     * @brief The remote user calls `leaveRoom` and leaves the room. <br>
     */
    ByteRTCUserOfflineReasonQuit = 0,
    /** 
     * @brief The remote user is offline.   <br>
     */
    ByteRTCUserOfflineReasonDropped = 1,
    /** 
      * @brief The remote user switches to invisible.   <br>
      */
    ByteRTCUserOfflineReasonSwitchToInvisible = 2,
    /** 
     * @brief The remote user is kicked out of the room.
     *        Is kicked out of the room due to calling the kicked out user's OpenAPI.
     */
    ByteRTCUserOfflineReasonKickedByAdmin = 3,
};

/** 
 * @type keytype
 * @brief The reason for the removal of the remote flow in the room.   <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamRemoveReason) {
    /** 
     * @brief The remote user stops publishing the flow.   <br>
     */
    ByteRTCStreamRemoveReasonUnpublish = 0,
    /** 
     * @brief The remote user failed to publish the flow.   <br>
     */
    ByteRTCStreamRemoveReasonPublishFailed = 1,
    /** 
     * @brief Keep alive failed.   <br>
     */
    ByteRTCStreamRemoveReasonKeepLiveFailed = 2,
    /** 
     * @brief The remote user is disconnected.   <br>
     */
    ByteRTCStreamRemoveReasonClientDisconnected = 3,
    /** 
     * @brief The remote user republishes the flow.   <br>
     */
    ByteRTCStreamRemoveReasonRepublish = 4,
    /** 
     * @brief Other reasons.   <br>
     */
    ByteRTCStreamRemoveReasonOther = 5,
};

/** 
 * @type keytype
 * @brief  Room profile
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomProfile) {
  /** 
     * @brief Normal call mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        You should use this mode for 1V1 calls. This mode works fine even if the network quality is poor.
     */
    ByteRTCRoomProfileCommunication = 0,
    /** 
     * @brief Live broadcasting mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        Use this mode for high quality of the media. <br>
     *        In this mode, audio plays in media mode for Bluetooth earphones.
     */
    ByteRTCRoomProfileLiveBroadcasting = 1,
    /** 
     * @brief Game voice mode. <br>
     *        Mono, the sampling frequency is 16kHz.
     *        When the low-end machine is running in this mode, additional performance optimizations have been made: <br>
     *             + Acquisition and playback use 16kHz single-channel sampling <br>
     *             + Some low-end models are configured to encode frame length 40/60 <br>
     *             + Some low-end models close software 3A audio processing <br>
     *        Enhance iOS Compatibility with other screen recordings to avoid audio recordings being interrupted by RTC.
     */
    ByteRTCRoomProfileGame = 2,
    /** 
     * @brief Cloud game mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        Use this mode for scenerios of low latency and high bitrate. <br>
     *        This mode works poor when the network quality is poor.
     */
    ByteRTCRoomProfileCloudGame = 3,
    /** 
     * @brief Low latency mode. <br>
     *        Use this mode when the scenario is neither a game or cloud game but requires very low latency. <br>
     *        In this mode, call delay will be significantly reduced. But the audio quality and the redundancy for weak network are poor. <br>
     *        You must consult the technical support specialist before using this mode.
     */
    ByteRTCRoomProfileLowLatency = 4,
    /** 
     * @brief For 1:1 audio calls
     */
    ByteRTCRoomProfileChat = 5,
    /** 
     * @brief For audio meetings for 3 or more people
     */
    ByteRTCRoomProfileChatRoom = 6,
    /** 
     * @brief For scenarios such as "Watch together." and "Listen together."
     */
    ByteRTCRoomProfileLwTogether = 7,
    /** 
     * @brief For the game apps demanding high-resolution audio
     */
    ByteRTCRoomProfileGameHD = 8,
    /** 
     * @brief For the event of co-hosting in the live streaming
     */
    ByteRTCRoomProfileCoHost = 9,
    /** 
     * @brief For interactive podcasts
     */
    ByteRTCRoomProfileInteractivePodcast = 10,
    /** 
     * @brief For the online karaoke with high-quality audio and low latency
     */
    ByteRTCRoomProfileKTV = 11,
    /** 
     * @brief For the online-chorusing scenarios with high-quality audio and low latency
     */
    ByteRTCRoomProfileChorus = 12,
    /** 
     * @brief For VR chat with support for 192 KHz audio sample rate and feature of 360 Reality Audio
     */
    ByteRTCRoomProfileVRChat = 13,
    /** 
     * @brief For 1 : 1 video chat in the game scenario using game stream technology
     */
    ByteRTCRoomProfileGameStreaming = 14,
    /** 
     * @brief For the live streaming within LAN with the support of 60fps @8K video stream with the bitrate of 100 Mbps
     */
    ByteRTCRoomProfileLanLiveStreaming = 15,
    /** 
     * @brief For online meetings
     */
    ByteRTCRoomProfileMeeting = 16,
    /** 
     * @brief  For the meeting app using in meeting rooms
     */
    ByteRTCRoomProfileMeetingRoom = 17,
    /** 
     * @brief For the online classrooms and lectures
     */
    ByteRTCRoomProfileClassroom = 18,
};

/** 
 * @hidden
 * @type keytype
 * @brief  User persona.   <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCUserRoleType) {
    /** 
     * @brief Live streaming host role. This role user can publish and subscribe to audio & video streams in the room, and other users in the room can perceive the presence of this user.   <br>
     */
    ByteRTCUserRoleTypeBroadcaster = 1,
    /** 
     * @brief Stealth user persona. This role user can only subscribe to audio & video streams in the room, and other users in the room cannot perceive the presence of this user.   <br>
     */
    ByteRTCUserRoleTypeSilentAudience = 2,
};
/** 
 * @type keytype
 * @brief SDK  Connection status with the signaling server.
 */
typedef NS_ENUM(NSInteger, ByteRTCConnectionState) {
    /** 
     * @brief The connection is disconnected for more than 12s.
     */
    ByteRTCConnectionStateDisconnected = 1,
    /** 
     * @brief The first request to connect to the server. Connecting.
     */
    ByteRTCConnectionStateConnecting = 2,
    /** 
     * @brief The first connection was successful.
     */
    ByteRTCConnectionStateConnected = 3,
    /** 
     * @brief The code includes the following status: <br>
     *        + The first connection is not successful for 10s. <br>
     *        + The connection has been lost for 10s. Auto reconnecting.
     */
    ByteRTCConnectionStateReconnecting = 4,
    /** 
     * @brief Successful reconnection after disconnection.
     */
    ByteRTCConnectionStateReconnected = 5,
    /** 
     * @brief Be in status `DISCONNECTION` for more than 10s. The requests to reconnect failed.
     */
    ByteRTCConnectionStateLost = 6,
};

/** 
 * @type keytype
 * @brief SDK  Network connection type.
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkType) {
    /** 
     * @brief Network connection type unknown.
     */
    ByteRTCNetworkTypeUnknown = -1,
    /** 
     * @brief The network connection has been disconnected.
     */
    ByteRTCNetworkTypeDisconnected = 0,
    /** 
     * @brief The network connection type is LAN.
     */
    ByteRTCNetworkTypeLAN = 1,
    /** 
     * @brief The network connection type is Wi-Fi (including hotspots).
     */
    ByteRTCNetworkTypeWIFI = 2,
    /** 
     * @brief The network connection type is 2G mobile network.
     */
    ByteRTCNetworkTypeMobile2G = 3,
    /** 
     * @brief The network connection type is 3G mobile network.
     */
    ByteRTCNetworkTypeMobile3G = 4,
    /** 
     * @brief The network connection type is 4G mobile network.
     */
    ByteRTCNetworkTypeMobile4G = 5,
    /** 
     * @brief The network connection type is 5G mobile network.
     */
    ByteRTCNetworkTypeMobile5G = 6,
};

/** 
 * @type keytype
 * @brief  Reason for stopping pre-call detection
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionStopReason) {
    /** 
     * @brief The user actively stops.
     */
    ByteRTCNetworkDetectionStopReasonUser = 0,
    /** 
     * @brief Detection takes more than three minutes.
     */
    ByteRTCNetworkDetectionStopReasonTimeout = 1,
    /** 
     * @brief Probe network connection disconnected.
     */
    ByteRTCNetworkDetectionStopReasonConnectionLost = 2,
    /** 
     * @brief Begin push-pull flow and stop probing.
     */
    ByteRTCNetworkDetectionStopReasonStreaming = 3,
    /** 
     * @brief Network probe failure, internal anomaly
     */
    ByteRTCNetworkDetectionStopReasonInnerErr = 4,
};

/** 
 * @type errorcode
 * @brief  Return value to start probing
 */
typedef NS_ENUM(NSInteger, ByteRTCNetworkDetectionStartReturn) {
    /** 
     * @brief Successfully initiated detection.
     */
    ByteRTCNetworkDetectionStartReturnSuccess = 0,
    /** 
     * @brief Failed to start probing. Parameter error, both uplink and downlink probes are false, or the expected bandwidth exceeds the range [100,10000]
     */
    ByteRTCNetworkDetectionStartReturnParamErr = 1,
    /** 
     * @brief Failed to start probing. Push-pull flow has begun
     */
    ByteRTCNetworkDetectionStartReturnStreaming = 2,
    /** 
     * @brief Has begun to detect
     */
    ByteRTCNetworkDetectionStartReturnStarted = 3,
    /** 
     * @brief Not Support
     */
    ByteRTCNNetworkDetectionStartReturnNotSupport = 4,
};

/** 
 * @type keytype
 * @brief The type of probe link before the call.
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkDetectionLinkType) {
    /** 
     * @brief Uplink network probing.
     */
    ByteRTCNetworkDetectionLinkTypeUp = 0,
    /** 
     * @brief Downlink network probing.
     */
    ByteRTCNetworkDetectionLinkTypeDown = 1,
};

/** 
 * @type keytype
 * @brief Media streaming network quality.
 */
typedef NS_ENUM(NSUInteger, ByteRTCNetworkQuality) {
    /** 
     * @brief Network quality unknown.
     */
    ByteRTCNetworkQualityUnknown = 0,
    /** 
     * @brief The network quality is excellent.
     */
    ByteRTCNetworkQualityExcellent = 1,
    /** 
     * @brief The subjective feeling is similar to kNetworkQualityExcellent, but the bit rate may be slightly lower.
     */
    ByteRTCNetworkQualityGood = 2,
    /** 
     * @brief Subjective feelings are flawed but do not affect communication.
     */
    ByteRTCNetworkQualityPoor = 3,
    /** 
     * @brief Can barely communicate but not smoothly.
     */
    ByteRTCNetworkQualityBad = 4,
    /** 
     * @brief The quality of the network is very poor and communication is basically impossible.
     */
    ByteRTCNetworkQualityVeryBad = 5,
};

/** 
 * @type errorcode
 * @brief  Callback error code. When an unrecoverable error is encountered internally in the
 *        SDK, the user is notified via an `rtcEngine:onError:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCErrorCode) {
    /** 
     * @brief Token  is invalid.
     *         The token used when joining the room is invalid or expired. The user is required to retrieve the token and update it by calling `updateToken:`.
     */
    ByteRTCErrorCodeInvalidToken               = -1000,
    /** 
     * @brief Join room error.
     *        An unknown error occurred when joining the room, which caused the room to fail to join. Users are required to rejoin the room.
     */
    ByteRTCErrorCodeJoinRoom             = -1001,
    /** 
     * @brief No permission to publish audio & video streams.
     *        The user failed to publish the audio & video stream in the room. The reason for the failure is that the user does not have permission to publish the stream.
     */
    ByteRTCErrorCodeNoPublishPermission       = -1002,
    /** 
     * @brief No subscription permissions for audio & video streams.
     *        The user failed to subscribe to the audio & video stream in the room where the user is located. The reason for the failure is that the user does not have permission to subscribe to the stream.
     */
    ByteRTCErrorCodeNoSubscribePermission     = -1003,
    /** 
     * @brief The user has been removed from the room because the same user joined the room on the other client.
     */
    ByteRTCErrorCodeDuplicateLogin             = -1004,

    /** 
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    ByteRTCErrorCodeKickedOut = -1006,

    /** 
     * @brief When calling `createRtcRoom:`, if the roomId is illegal, it will return null and throw the error
     */
    ByteRTCErrorCodeRoomIdIllegal = -1007,


    /** 
     * @brief Token expired. Call `joinRoomByKey:roomId:userInfo:rtcRoomConfig:` to rejoin with a valid Token.
     */
    ByteRTCErrorCodeTokenExpired            = -1009,
        /** 
     * @brief The Token you provided when calling `updateToken:` is invalid.
     */
    ByteRTCErrorCodeUpdateTokenWithInvalidToken     = -1010,

    /** 
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    ByteRTCErrorCodeRoomDismiss = -1011,

    /** 
     * @brief Join room error. <br>
     *        The LICENSE billing account does not use the LICENSE_AUTHENTICATE SDK while calling `joinRoomByToken:userInfo:roomConfig:`, which caused the joining room to fail.
     */
    ByteRTCJoinRoomWithoutLicenseAuthenticateSDK = -1012,

    /** 
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    ByteRTCRoomAlreadyExist = -1013,

    /** 
     * @brief Subscription to audio & video stream failed, the total number of subscribed audio & video streams exceeded the upper limit.
     *        In the game scenario, in order to ensure the performance and quality of audio & video calls, the server will limit the total number of audio & video streams subscribed by the user. When the total number of audio & video streams subscribed by the user has reached the maximum, continuing to subscribe to more streams will fail, and the user will receive this error notification.
     */
    ByteRTCErrorCodeOverStreamSubscribeLimit        = -1070,
    /** 
     * @brief Publishing flow failed, the total number of publishing flows exceeds the upper limit. The
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    ByteRTCErrorCodeOverStreamPublishLimit = -1080,
    /** 
     * @brief Publishing the screen stream failed, and the total number of publishing streams exceeded the upper limit. The
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    ByteRTCErrorCodeOverScreenPublishLimit = -1081,
    /** 
     * @brief The total number of published video streams exceeds the upper limit.
     *        The RTC system limits the number of video streams posted in a single room. If the maximum number of video streams posted in the room has been reached, local users will fail to post video streams to the room again and will receive this error notification.
     */
    ByteRTCErrorCodeOverVideoPublishLimit = -1082,
    /** 
     * @brief A/V synchronization failed.  <br>
     *        Current source audio ID has been set by other video publishers in the same room.  <br>
     *        One single audio source cannot be synchronized with multiple video sources at the same time.
     */
    ByteRTCErrorCodInvalidAudioSyncUidRepeated = -1083,
};

/** 
 * @type keytype
 * @brief Subscription status of media streams
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeState) {
    /** 
     * @brief Successfully changed the subscription status
     */
    ByteRTCSubscribeStateSuccess,
    /** 
     * @brief Failed to change the subscription status, because you were not in the room.
     */
    ByteRTCSubscribeStateFailedNotInRoom,
    /** 
     * @brief Failed to change the subscription status, because the target audio/video stream was not found.
     */
    ByteRTCSubscribeStateFailedStreamNotFound,
    /** 
     * @brief Failed to change the subscription status, because the number of streams you have subscribed to has exceeded the limit.
     */
    ByteRTCSubscribeStateFailedOverLimit,
};

/** 
 * @type errorcode
 * @brief  Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes are for notification only.
 */
typedef NS_ENUM(NSInteger, ByteRTCWarningCode) {
    /**
     * @hidden
     */
    ByteRTCWarningCodeGetRoomFailed              = -2000,
    /** 
     * @brief Failed to enter the room.   <br>
     *        When entering the room for the first time or when the network is disconnected and reconnected due to poor network conditions, entering the room failed due to a server error. The SDK automatically retries the room.
     */
    ByteRTCWarningCodeJoinRoomFailed             = -2001,
    /** 
     * @brief Release audio & video stream failed.
     *        When you publish audio & video streams in your room, the release fails due to a server error. The SDK automatically retries the release.
     */
    ByteRTCWarningCodePublishStreamFailed        = -2002,
    /** 
     * @brief Subscription to audio & video stream failed.
     *        The subscription failed because the audio & video stream for the subscription was not found in the current room. The SDK will automatically retry the subscription. If the subscription fails, it is recommended that you exit the retry.
     */
    ByteRTCWarningCodeSubscribeStreamFailed404  = -2003,
    /** 
     * @brief Subscription to audio & video stream failed.
     *        When you subscribe to audio & video streams in your room, the subscription fails due to a server error. The SDK automatically retries the subscription.
     */
    ByteRTCWarningCodeSubscribeStreamFailed5xx  = -2004,
    /** 
     * @hidden
     * @brief  Function call order is wrong and is not used in the current code.
     */
    ByteRTCWarningCodeInvokeError = -2005,
    /** 
     * @hidden
     * @brief Scheduling exception, the media server address returned by the server is unavailable.
     */
    ByteRTCWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief This warning is triggered when you call `setUserVisibility:`to set yourself unvisible to others before attempting to publish the flow. <br>
     */
    ByteRTCWarningCodePublishStreamForbiden = -2009,
    /** 
     * @hidden
     * @brief When automatic subscription mode is not turned off, trying to turn on manual subscription mode will trigger this warning.   <br>
     *        You need to call the enableAutoSubscribe:videoMode:{@link #ByteRTCEngineKit#enableAutoSubscribe:videoMode:} method to turn off the automatic subscription mode before entering the room, and then call the subscribeStream:subscribeConfig:{@link #ByteRTCEngineKit#subscribeStream:subscribeConfig:} method to manually subscribe to the audio & video stream.
     */
    ByteRTCWarningCodeSubscribeStreamForbiden = -2010,
    /** 
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    ByteRTCWarningCodeSendCustomMessage = -2011,
    /** 
     * @brief When the number of people in the room exceeds 500, stop sending `rtcEngine:onUserJoined:elapsed:` and `rtcEngine:onUserLeave:reason:` callbacks to existing users in the room, and prompt all users in the room via broadcast.
     */
    ByteRTCWarningCodeCodeUserNotifyStop = -2013,
    /** 
     * @brief user had published in other room or had published public stream.
     */
    ByteRTCWarningCodeUserInPublish = -2014,
    /** 
     * @brief there is a room with the same roomId
     */
    ByteRTCWarningCodeRoomAlreadyExist = -2015,

    /** 
     * @brief The old room has been replaced by new room with the same roomId
     */
    ByteRTCWarningCodeOldRoomBeenReplaced = -2016,

    /** 
     * @brief this inteface has been banned for the engine is in echo testing mode
     */
    ByteRTCWarningCodeInEchoTestMode = -2017,
    /** 
     * @brief The camera permission is abnormal, the current application does not get the camera permission
     */
    ByteRTCWarningCodeNoCameraPermission            = -5001,
    /** 
     * @brief The microphone permission is abnormal, the current application does not get microphone permission
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoMicrophonePermission        = -5002,
    /** 
     * @brief The audio capture device failed to start.   <br>
     *        Failed to start the audio capture device, the current device may be occupied by other applications.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeAudioDeviceManagerRecordingStartFail     = -5003,
    /** 
     * @brief Audio playback device startup failure warning.   <br>
     *         It may be due to insufficient system resources or wrong parameters.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeAudioDeviceManagerPlayoutStartFail = -5004,
    /** 
     * @brief No audio acquisition equipment available.   <br>
     *        Failed to start the audio capture device, please insert the available audio capture device.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoRecordingDevice = -5005,
    /** 
     * @brief No audio playback device available.   <br>
     *        Failed to start the audio playback device, please insert the available audio playback device.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeNoPlayoutDevice = -5006,
    /** 
     * @brief The current audio equipment has not collected valid sound data, please check and replace the audio acquisition equipment.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeRecordingSilence = -5007,
    /** 
     * @brief Media device misoperation warning.   <br>
     *        When using custom acquisition, the internal acquisition switch cannot be called, and this warning is triggered when called.
     * @deprecated since 333.1, use ByteRTCMediaDeviceWarning instead
     */
    ByteRTCWarningCodeMediaDeviceOperationDennied = -5008,
    /** 
     * @brief Setting the screen audio capture type via `setScreenAudioSourceType` after `publishScreen` is not supported
     */
    ByteRTCWarningSetScreenAudioSourceTypeFailed = -5009,

    /** 
     * @brief Setting the screen audio mix type via `setScreenAudioStreamIndex` after `publishScreen` is not supported
     */
    ByteRTCWarningSetScreenAudioStreamIndexFailed = -5010,
    /** 
     * @brief Invalid pitch value setting
     */
    ByteRTCWarningInvalidVoicePitch = -5011,
    /** 
     * @brief Mixed use of old and new interfaces for external audio sources
     */
    ByteRTCWarningInvalidCallForExtAudio = -5013,
    /** 
     * @brief The specified internal rendering canvas handle is invalid.   <br>
     *        An invalid canvas handle is specified when you call setLocalVideoCanvas:withCanvas:{@link #ByteRTCEngineKit#setLocalVideoCanvas:withCanvas:} or setRemoteVideoCanvas:withIndex:withCanvas:{@link #ByteRTCEngineKit#setRemoteVideoCanvas:withIndex:withCanvas:}, triggering this callback.
     */
    ByteRTCWarningCodeInvalidCanvasHandle = -6001
};

/** 
 * @type keytype
 * @brief  Reasons for performance rollback or recovery
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmReason) {
    /** 
     * @brief The poor network causes the transmission performance to fall back. This reason is only received when sending performance fallback is turned on.
     */
    ByteRTCPerformanceAlarmReasonBandwidthFallback = 0,
    /** 
     * @brief Network performance recovery, transmission performance rollback recovery. This reason is only received when sending performance fallback is turned on.
     */
    ByteRTCPerformanceAlarmReasonBandwidthResumed = 1,
    /** 
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance is insufficient; <br>
     *        If the send performance fallback is turned on, when receiving this alarm, it means that the performance is insufficient and the send performance fallback has occurred.
     */
    ByteRTCPerformanceAlarmReasonFallback = 2,
    /** 
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance shortage has been restored; <br>
     *         If the send performance fallback is turned on, when receiving this alarm, it means that the performance shortage has been restored and the send performance fallback has occurred. Recovery.
     */
    ByteRTCPerformanceAlarmReasonResumed = 3,
};

/** 
 * @type keytype
 * @brief  Mode of performance fallback
 */
typedef NS_ENUM(NSInteger, ByteRTCPerformanceAlarmMode) {
    /** 
     * @brief Not enabled Release performance fallback
     */
    ByteRTCPerformanceAlarmModeNormal = 0,
    /** 
     * @brief Open Release Performance Rollback
     */
    ByteRTCPerformanceAlarmModeSimulcast = 1,
};

/** 
 * @type keytype
 * @hidden
 * @brief  Log level.
 */
typedef NS_ENUM(NSUInteger, ByteRTCLogLevel) {
    /** 
     * @hidden
     * @brief Print trace level and above information.
     */
    ByteRTCLogLevelTrace,
    /** 
     * @hidden
     * @brief  Print debug level and above information.
     */
    ByteRTCLogLevelDebug,
    /** 
     * @hidden
     * @brief  Print info level and above information.
     */
    ByteRTCLogLevelInfo,
    /** 
     * @hidden
     * @brief  Print warning level and above information.
     */
    ByteRTCLogLevelWarning,
    /** 
     * @hidden
     * @brief  Print error level information.
     */
    ByteRTCLogLevelError,
};

/** 
 * @type errorcode
 * @brief  Login result   <br>
 *        The result of calling `login:uid:` will notify the user through `rtcEngine:onLoginResult:errorCode:elapsed:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCLoginErrorCode) {
    /** 
     * @brief Call the `login:uid:` method to log in successfully.
     */
    ByteRTCLoginErrorCodeSuccess = 0,
    /** 
     * @brief The token used when calling the `login:uid:` method is invalid or expired. The user is required to re-acquire the token.
     */
    ByteRTCLoginErrorCodeInvalidToken = -1000,
    /** 
     * @brief Login error   <br>
     *        An unknown error occurred when calling the `login:uid:` method, which caused the login to fail. The user is required to log in again.
     */
    ByteRTCLoginErrorCodeLoginFailed = -1001,
    /** 
     * @brief There was a problem with the incoming user ID when the `login:uid:` method was called.
     */
    ByteRTCLoginErrorCodeInvalidUserId = -1002,
    /** 
     * @brief Call `login:uid:` server error while logging in.
     */
    ByteRTCLoginErrorCodeServerError = -1003,
};

/** 
 * @type keytype
 * @brief Reliable orderliness of sent messages
 */
typedef NS_ENUM(NSInteger, ByteRTCMessageConfig) {
    /** 
     * @brief Low latency reliable and orderly message
     */
    ByteRTCMessageConfigReliableOrdered = 0,
    /** 
     * @brief Ultra-low latency ordered message
     */
    ByteRTCMessageConfigUnreliableOrdered = 1,
    /** 
     * @brief Ultra-low latency unordered message
     */
    ByteRTCMessageConfigUnreliableUnordered = 2,
};

/** 
 * @type keytype
 * @brief Result of sending messages and the reason of failure if it fails.
 */
typedef NS_ENUM(NSInteger, ByteRTCUserMessageSendResult) {
    /** 
     * @brief The message has been sent successfully.
     */
    ByteRTCUserMessageSendResultSuccess = 0,
    /** 
     * @brief Failure. Sending timeout.
     */
    ByteRTCUserMessageSendResultTimeout = 1,
    /** 
     * @brief Failure. Channel disconnected.
     */
    ByteRTCUserMessageSendResultBroken = 2,
    /** 
     * @brief Failure. Recipient not found.
     */
    ByteRTCUserMessageSendResultNoReceiver = 3,
    /** 
     * @brief Failure. Failed to get cascade path
     */
    ByteRTCUserMessageSendResultNoRelayPath = 4,
    /** 
     * @brief Failure. The sender of the message did not join the room
     */
    ByteRTCUserMessageSendResultNotJoin = 100,
    /** 
     * @brief Failure. Connection initialization not completed
     */
    ByteRTCUserMessageSendResultInit = 101,
    /** 
     * @brief Failure. No data transmission channel connection available
     */
    ByteRTCUserMessageSendResultNoConnection = 102,
    /** 
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    ByteRTCUserMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief Failure. The id of the recipient is empty
     */
    ByteRTCUserMessageSendResultEmptyUser = 104,
    /** 
     * @hidden
     * @brief Failure. The sender of the message did not log in.
     */
    ByteRTCUserMessageSendResultNotLogin = 105,
    /** 
     * @brief Failure. No parameters were set before sending the message to the server
     */
    ByteRTCUserMessageSendResultServerParamsNotSet = 106,
    /** 
     * @brief Failure. Unknown error.
     */
    ByteRTCUserMessageSendResultUnknown = 1000,
};

/** 
 * @type keytype
 * @brief  User online status
 */
typedef NS_ENUM(NSInteger, ByteRTCUserOnlineStatus) {
    /** 
     * @brief The peer user is offline
     *        The peer user has called `logout`, or has not called `login:uid:` to log in
     */
    ByteRTCUserOnlineStatusOffline = 0,
    /** 
     * @brief The peer user is online
     *        The peer user calls `login:uid:` to log in and the connection status is normal
     */
    ByteRTCUserOnlineStatusOnline = 1,
    /** 
     * @brief Unable to get the online state of the peer user
     *        Returned when a cascade error occurs and the online state of the peer user is abnormal
     */
    ByteRTCUserOnlineStatusUnreachable = 2,
};

/** 
 * @type keytype
 * @brief Result of broadcasting messages in the room
 */
typedef NS_ENUM(NSInteger, ByteRTCRoomMessageSendResult) {
    /** 
     * @brief The message sent successfully.
     */
    ByteRTCRoomMessageSendResultSuccess = 200,
    /** 
     * @brief Failure. The sender has not joined a room.
     */
    ByteRTCRoomMessageSendResultNotJoin = 100,
    /** 
     * @brief Failure. The connection has not completed initialization.
     */
    ByteRTCRoomMessageSendResultInit = 101,
    /** 
     * @brief Failure. No connection available.
     */
    ByteRTCRoomMessageSendResultNoConnection = 102,
    /** 
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    ByteRTCRoomMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief Failure. Unknown error.
     */
    ByteRTCRoomMessageSendResultUnknown = 1000,
};

/** 
 * @hidden
 * @type keytype
 * @brief SDK  server environment.
 */
typedef NS_ENUM(NSInteger, ByteRTCEnv) {
    /** 
     * @hidden
     * @brief  Online environment.
     */
    ByteRTCEnvProduct = 0,
    /** 
     * @hidden
     * @brief BOE  environment.
     */
    ByteRTCEnvBOE = 1,
    /** 
     * @hidden
     * @brief  Test environment.
     */
    ByteRTCEnvTest = 2,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Set engine working mode
 */
typedef NS_ENUM(NSUInteger, ByteRTCMode) {
    /** 
     * @brief General mode, in which only voice calls in normal meeting mode can be made and automatic subscription publishing can be started.
     */
    ByteRTCModeGeneral = 0,
    /** 
     * @brief The game voice mode, in which automatic subscription publishing is turned off, will actively publish subscription voice according to the strategy of the game business.
     */
    ByteRTCModeLocalAudio = 1,
};
/** 
 * @type keytype
 * @brief Stream fallback options of publisher
 */
typedef NS_ENUM(NSUInteger, ByteRTCPublishFallbackOption) {
    /** 
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    ByteRTCPublishFallbackOptionDisabled = 0,
    /** 
     * @brief Under limited network conditions, the video streams that you published will degrade sequentially from the highest-quality stream to the lowest-quality stream until it can match current network conditions.
     */
    ByteRTCPublishFallbackOptionSimulcast = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Subscription mode option.
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeMode) {
    /** 
     * @brief Automatic subscription mode. The SDK  automatically subscribes to every stream in the room for you. <br>
     */
    ByteRTCSubscribeModeAuto = 0,
    /** 
     * @brief Manual subscription mode. The SDK  does not automatically subscribe to in-room audio & video streams. You should call the `subscribeStream` to manually subscribe to audio & video streams posted by other users as needed.
     */
    ByteRTCSubscribeModeManual = 1
};
/** 
 * @type keytype
 * @brief Stream fallback options of subscriber
 */
typedef NS_ENUM(NSUInteger, ByteRTCSubscribeFallbackOption) {
    /** 
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    ByteRTCSubscribeFallbackOptionDisabled = 0,
    /** 
     * @brief The resolution of currently subscribed video stream will be reduced under limited network conditions, see [Video Fallback](70137) for details.  <br>
     *        You can only select this setting after the stream publisher calls `enableSimulcastMode:` to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    ByteRTCSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief Receive audio only under poor network condition.
     */
    ByteRTCSubscribeFallbackOptionAudioOnly = 2,
};

/** 
 * @type keytype
 * @brief Priority of the publisher. When a user encounters performance insufficiency of either the network or the device, the media stream  will fall back in the ascending order of `RemoteUserPriority`.
 */
typedef NS_ENUM(NSUInteger, ByteRTCRemoteUserPriority) {
    /** 
     * @brief Low, the default
     */
    ByteRTCRemoteUserPriorityLow = 0,
    /** 
     * @brief Medium
     */
    ByteRTCRemoteUserPriorityMedium = 100,
    /** 
     * @brief High
     */
    ByteRTCRemoteUserPriorityHigh = 200,
};

/** 
 * @type keytype
 * @brief Reason of the Fallback or reverting from a Fallback of the subscribed stream or the publishing stream
 */
typedef NS_ENUM(NSInteger, ByteRTCFallbackOrRecoverReason) {
    /** 
     * @brief The default: Fallback due to an unknown reason that is neither infufficienclt bandwidth of the network nor poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonUnknown = -1,
    /** 
     * @brief Fallback of the subscribed stream due to insufficient bandwidth of the network
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /** 
     * @brief Fallback of the subscribed stream for poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /** 
     * @brief Reverting from a Fallback of the subscribed stream due to the recovery of the network bandwidth
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /** 
     * @brief Reverting from a Fallback of the subscribed stream due to the amelioration of the device performance
     */
    ByteRTCFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /** 
     * @brief Fallback of the publishing stream due to Insufficient bandwidth of the network
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /** 
     * @brief Fallback of the publishing stream due to poor-performance of the device
     */
    ByteRTCFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /** 
     * @brief Reverting from a Fallback of the publishing stream due to the recovery of the network bandwidth
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /** 
     * @brief Reverting from a Fallback of the publishing stream due to the amelioration of the device performance
     */
    ByteRTCFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/** 
 * @type keytype
 * @brief  Local audio stream status.   <br>
 *        SDK callbacks the state via `onLocalAudioStateChanged`. <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamState) {
    /** 
     * @brief The default initial state of the local audio.
     *         Callback to this state when the microphone stops working, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateStopped = 0,
    /** 
     * @brief The local audio recording device started successfully.
     *         Callback to this state when the first audio frame is collected, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateRecording = 1,
    /** 
     * @brief The first frame of the local audio was successfully encoded.
     *         Callback to this state when the audio first frame encoding is successful, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamErrorOk
     */
    ByteRTCLocalAudioStreamStateEncoding = 2,
    /** 
     * @brief  The local audio startup failed, and the status is called back at the following times:   <br>
     *        + The local recording device failed to start, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} ByteRTCLocalAudioStreamErrorRecordFailure <br>
     *        + No recording device permission was detected, corresponding to the error code ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError} ByteRTCLocalAudioStreamErrorDeviceNoPermission <br>
     *        + The audio encoding failed, corresponding to the error code ByteRTCLocalAudioStreamError { @Link #ByteRTCLocalAudioStreamError} in ByteRTCLocalAudioStreamError <br>
     */
    ByteRTCLocalAudioStreamStateFailed = 3,
};

/** 
 * @type keytype
 * @brief Error code when the state of the local audio stream changes. The
 *        SDK calls back the error code via `onLocalAudioStateChanged`.
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalAudioStreamError) {
    /** 
     * @brief Local audio status is normal
     */
    ByteRTCLocalAudioStreamErrorOk = 0,
    /** 
     * @brief Local audio error cause unknown
     */
    ByteRTCLocalAudioStreamErrorFailure = 1,
    /** 
     * @brief No permission to start local audio recording device
     */
    ByteRTCLocalAudioStreamErrorDeviceNoPermission = 2,
    /** 
     * @hidden
     * @brief The local audio recording device is already in use
     * @notes The error code is not yet in use
     */
    ByteRTCLocalAudioStreamErrorDeviceBusy = 3,
    /** 
     * @brief Local audio recording failed, it is recommended that you check whether the recording device is working properly
     */
    ByteRTCLocalAudioStreamErrorRecordFailure = 4,
    /** 
     * @brief Local audio encoding failed
     */
    ByteRTCLocalAudioStreamErrorEncodeFailure = 5,
    /** 
     * @brief No audio recording equipment available
     */
    ByteRTCLocalAudioStreamErrorNoRecordingDevice = 6
};

/** 
 * @type keytype
 * @brief  Local video stream status
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamState) {
    /** 
     * @brief Local video default initial state
     *         Callback the state when the camera stops working, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateStopped = 0,
    /** 
     * @brief The local video recording device starts successfully
     *         Callback the state when the first frame of the video is collected, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateRecording = 1,
    /** 
     * @brief Local video first frame encoding success
     *         Local video first frame encoding success callback to the state, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} in ByteRTCLocalVideoStreamErrorOk
     */
    ByteRTCLocalVideoStreamStateEncoding = 2,
    /** 
     * @brief  Local video startup failed,  the status is called back at the following times: <br>
     *        + The local acquisition device failed to start, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorCaptureFailure <br>
     *        + No camera permission was detected, corresponding to the error code ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError} ByteRTCLocalVideoStreamErrorDeviceNoPermission <br>
     *        + The video encoding failed, corresponding to the error code ByteRTCLocalVideoStreamError { @Link #ByteRTCLocalVideoStreamError} in ByteRTCLocalVideoStreamErrorEncodeFailure <br>
     */
    ByteRTCLocalVideoStreamStateFailed = 3,
};

/** 
 * @type keytype
 * @brief  Error code when the local video state changes
 */
typedef NS_ENUM(NSInteger, ByteRTCLocalVideoStreamError) {
    /** 
     * @brief Local video status is normal (the default return value when the local video status changes to normal)
     */
    ByteRTCLocalVideoStreamErrorOk = 0,
    /** 
     * @brief Local video stream publishing failed
     */
    ByteRTCLocalVideoStreamErrorFailure = 1,
    /** 
     * @brief No access to the local video capture device
     */
    ByteRTCLocalVideoStreamErrorDeviceNoPermission = 2,
    /** 
     * @brief Local video capture equipment is occupied
     */
    ByteRTCLocalVideoStreamErrorDeviceBusy = 3,
    /** 
     * @brief The local video capture device does not exist or has been removed
     */
    ByteRTCLocalVideoStreamErrorDeviceNotFound = 4,
    /** 
     * @brief Local video capture failed, it is recommended to check whether the acquisition device is working properly
     */
    ByteRTCLocalVideoStreamErrorCaptureFailure = 5,
    /** 
     * @brief Local video encoding failed
     */
    ByteRTCLocalVideoStreamErrorEncodeFailure = 6,
    /** 
     * @brief Local video capture device removed
     */
    ByteRTCLocalVideoStreamErrorDeviceDisconnected = 7,
};

/** 
 * @type keytype
 * @brief  The remote audio stream state of the user subscription.   <br>
 *        SDK callbacks the state via `onRemoteAudioStateChanged`. <br>
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioState) {
    /** 
     * @brief  The default initial state of the remote audio stream is called back at the following time:   <br>
     *        + Local users stop receiving the remote audio stream, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonLocalMuted` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user stopped sending the audio stream, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonRemoteMuted` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user left the room, the corresponding reason is `ByteRTCRemoteAudioStateChangeReasonRemoteOffline` in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     */
    ByteRTCRemoteAudioStateStopped = 0,
    /** 
     * @brief Start receiving the remote audio stream header.   <br>
     *        When the remote audio stream header is just received, a `onRemoteAudioStateChanged` callback will be triggered,
     *        The corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}.
     */
    ByteRTCRemoteAudioStateStarting = 1,
    /** 
     * @brief  The remote audio stream is decoding and playing normally. The state will be called back at the following time:   <br>
     *        + The first frame of the remote audio is successfully decoded, and the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The network returned to normal from blocking, and the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + Local users recover receiving remote audio streams due to ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     *        + The remote user resumes sending audio streams, the corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason} <br>
     */
    ByteRTCRemoteAudioStateDecoding = 2,
    /** 
     * @brief Remote audio streaming card. <br>
     *        Network blocking causes a packet loss rate greater than 40%, which triggers a callback `onRemoteAudioStateChanged`,
     *        The corresponding reason is ByteRTCRemoteAudioStateChangeReason in ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
     */
    ByteRTCRemoteAudioStateFrozen = 3,
    /** 
     * @hidden
     * @brief  The remote audio stream failed to play
     * @notes  The error code is not yet used
     */
    ByteRTCRemoteAudioStateFailed = 4,
};

/** 
 * @type keytype
 * @brief  Receives the cause of the remote audio stream state change. <br>
 *         Users can learn about this state through `onRemoteAudioStateChanged`.
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteAudioStateChangeReason) {
    /** 
     * @brief Internal reasons
     */
    ByteRTCRemoteAudioStateChangeReasonInternal = 0,
    /** 
     * @brief Network blocking
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkCongestion = 1,
    /** 
     * @brief Network back to normal
     */
    ByteRTCRemoteAudioStateChangeReasonNetworkRecovery = 2,
    /** 
     * @brief Local user stops receiving remote audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonLocalMuted = 3,
    /** 
     * @brief Local users resume receiving remote audio streams
     */
    ByteRTCRemoteAudioStateChangeReasonLocalUnmuted = 4,
    /** 
     * @brief Remote user stops sending audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteMuted = 5,
    /** 
     * @brief Remote user resumes sending audio stream
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteUnmuted = 6,
    /** 
     * @brief Remote user leaves room
     */
    ByteRTCRemoteAudioStateChangeReasonRemoteOffline = 7,
};

/** 
 * @type keytype
 * @brief  Remote video stream status
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoState) {
    /** 
     * @brief  The default initial state of the remote video stream,  callback the state at the following times: <br>
     *        + The local user stops receiving the remote video stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalMuted <br>
     *        + The remote user stops sending the video stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReasonRemoteMuted <br>
     *        + The remote user leaves the room, corresponding to Error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} in ByteRTCRemoteVideoStateChangeReasonRemoteOffline <br>
     */
    ByteRTCRemoteVideoStateStopped = 0,
    /** 
     * @brief Local users have received the remote video header package  <br>
     *         Callback this state when the remote video header package is received, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted
     */
    ByteRTCRemoteVideoStateStarting = 1,
    /** 
     * @brief  The remote video stream is decoding and playing normally,  callback the status at the following times: <br>
     *        + ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *        + The network returned to normal from blocking, corresponding to the error code ByteRTCRemoteVideoStateChangeReasonNetworkRecovery <br>
     *        + The local user recovers the received remote video Stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonLocalUnmuted <br>
     *        + The remote user resumes sending the video stream, corresponding to the error code in ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} <br>
     */
    ByteRTCRemoteVideoStateDecoding = 2,
    /** 
     * @brief Remote video streaming card  <br>
     *         Network blocking, packet loss rate and other reasons will report the status of the video card stream, corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonNetworkCongestion
     */
    ByteRTCRemoteVideoStateFrozen = 3,
     /** 
      * @brief The remote audio stream failed to play  <br>
      * @notes If the internal processing of the remote video stream fails, the method will be called back,  corresponding to the error code ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason} ByteRTCRemoteVideoStateChangeReasonInternal
      */
    ByteRTCRemoteVideoStateFailed = 4,
};

/** 
 * @type keytype
 * @brief  Cause of remote video stream state change
 */
typedef NS_ENUM(NSInteger, ByteRTCRemoteVideoStateChangeReason) {
    /** 
     * @brief Internal reasons
     */
    ByteRTCRemoteVideoStateChangeReasonInternal = 0,
    /** 
     * @brief Network blocking
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkCongestion = 1,
    /** 
     * @brief Network back to normal
     */
    ByteRTCRemoteVideoStateChangeReasonNetworkRecovery = 2,
    /** 
     * @brief Local user stops receiving remote video stream or local user disables video module
     */
    ByteRTCRemoteVideoStateChangeReasonLocalMuted = 3,
    /** 
     * @brief Local user resumes receiving remote video streams or local user enables video modules
     */
    ByteRTCRemoteVideoStateChangeReasonLocalUnmuted = 4,
    /** 
     * @brief The remote user stops sending the video stream or the remote user disables the video module
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteMuted = 5,
    /** 
     * @brief Remote user resumes sending video stream or remote user enables video module
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteUnmuted = 6,
    /** 
     * @brief Remote user leaves room
     */
    ByteRTCRemoteVideoStateChangeReasonRemoteOffline = 7,
};

/** 
 * @type keytype
 * @brief Type of media device
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceType) {
    /** 
     * @brief Unknow device
     */
    ByteRTCMediaDeviceTypeAudioUnknown = -1,
    /** 
     * @brief Screen audio recorder
     */
    ByteRTCMediaDeviceTypeAudioRenderDevice = 0,
    /** 
     * @brief Microphone
     */
    ByteRTCMediaDeviceTypeAudioCaptureDevice = 1,
    /** 
     *@hidden
     *@brief  Video rendering device type, this type is not used yet
     */
    ByteRTCMediaDeviceTypeVideoRenderDevice = 2,
    /** 
     *@brief Video capture device
     */
    ByteRTCMediaDeviceTypeVideoCaptureDevice = 3,
    /** 
     *@brief Screen video capture device
     */
    ByteRTCMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /** 
     *@brief Screen audio recorder
     */
    ByteRTCMediaDeviceTypeScreenAudioCaptureDevice = 5
};

/** 
 * @type keytype
 * @brief Media device state<br>
 *        You will be informed of device state by `rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:` or `rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:`.
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceState) {
    /** 
     * @brief On
     */
    ByteRTCMediaDeviceStateStarted = 1,
    /** 
     * @brief Off
     */
    ByteRTCMediaDeviceStateStopped = 2,
    /** 
     * @brief Runtime error<br>
     *        For example, when the media device is expected to be working but no data is received.
     */
    ByteRTCMediaDeviceStateRuntimeError = 3,
    /** 
     * @brief Added
     */
    ByteRTCMediaDeviceStateAdded = 10,
    /** 
     * @brief Removed
     */
    ByteRTCMediaDeviceStateRemoved = 11,
    /** 
     * @brief Phone calls, locking screen or the other Apps interrupted the RTC call. RTC call will resume once the call ends or the other Apps release the media devices.
     */
    ByteRTCMediaDeviceStateInterruptionBegan = 12,
    /** 
     * @brief RTC call resumed from the interruption caused by the phone calls or the other Apps.
     */
    ByteRTCMediaDeviceStateInterruptionEnded = 13
};

/** 
 * @type keytype
 * @brief  Media device error
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceError) {
    /** 
     *@brief Normal
     */
    ByteRTCMediaDeviceErrorOK = 0,
    /** 
     *@brief No permission
     */
    ByteRTCMediaDeviceErrorDeviceNoPermission = 1,
    /** 
     *@brief Occupied by the other application
     */
    ByteRTCMediaDeviceErrorDeviceBusy = 2,
    /** 
     *@brief Error
     */
    ByteRTCMediaDeviceErrorDeviceFailure = 3,
    /** 
     *@brief Not found
     */
    ByteRTCMediaDeviceErrorDeviceNotFound = 4,
    /** 
     *@brief Disconnected
     */
    ByteRTCMediaDeviceErrorDeviceDisconnected = 5,
    /** 
     * @brief No data callback from the capture devices. <br>
     *        RTC emits this error when the media device is expected to be working but no data is received.
     */
    ByteRTCMediaDeviceErrorDeviceNoCallback = 6,
    /** 
     *@brief Not supported sample rate
     */
    ByteRTCMediaDeviceErrorUNSupportFormat = 7,
    /** 
     * @brief ios screen capture not find group id parameter
     */
    ByteRTCMediaDeviceErrorNotFindGroupId = 8
};

/** 
 * @type keytype
 * @brief Media device warning
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaDeviceWarning) {
    /** 
     * @brief No warning
     */
    ByteRTCMediaDeviceWarningOK = 0,
    /** 
     * @brief Illegal device operation. Calls the API for internal device when using the external device.
     */
    ByteRTCMediaDeviceWarningOperationDenied = 1,
    /** 
     * @brief The media device is capturing silent frames.
     */
    ByteRTCMediaDeviceWarningCaptureSilence = 2,
    // The following warning codes are only valid for meeting scenarios.
    /** 
     * @hidden
     * @brief The volume is too loud and exceeds the acquisition range of the device. Lower the microphone volume or lower the volume of the audio source.
     */
    ByteRTCMediaDeviceWarningDetectClipping = 10,
    /** 
     * @hidden
     * @brief Leaking echo detected.
     */
    ByteRTCMediaDeviceWarningDetectLeakEcho = 11,
    /** 
     * @hidden
     * @brief Low SNR.
     */
    ByteRTCMediaDeviceWarningDetectLowSNR = 12,
    /** 
     * @hidden
     * @brief Silence inserted during capture.
     */
    ByteRTCMediaDeviceWarningDetectInsertSilence = 13,
    /** 
     * @hidden
     * @brief Silence during capture.
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilence = 14,
    /** 
     * @hidden
     * @brief Silence disappears during capture.
     */
    ByteRTCMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /** 
     * @hidden
     * @brief Howling
     */
    ByteRTCMediaDeviceWarningCaptureDetectHowling = 16,
    /** 
     * @hidden(Mac)
     * @brief Setting audio route failed because the audio route can not be changed in the current Audio Scenario. 
     */
    ByteRTCMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /** 
     * @hidden(iOS,Mac)
     * @brief Setting audio route failed because the routing device did not exist.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotExists = 21,
    /** 
     * @hidden(Mac)
     * @brief Setting audio route failed because the audio route was occupied by the system or the other Apps.
  */
    ByteRTCMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /** 
     * @hidden(iOS,Mac)
     * @brief Setting audio route failed because the audio route can only be changed in the communication audio mode.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /** 
     * @hidden(Mac)
     * @brief Setting audio route failed because the audio route did not initiate.
     */
    ByteRTCMediaDeviceWarningSetAudioRouteDeviceNotStart = 24
};

/** 
 *  @type keytype
 *  @brief  Audio & video quality feedback problem type
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCProblemFeedbackOption){
    /** 
     * @brief No problem
     */
    ByteRTCProblemFeedbackOptionNone = 0,
    /** 
     * @brief Other issues
     */
    ByteRTCProblemFeedbackOptionOtherMessage = (1 << 0),
    /** 
     * @brief Unclear voice
     */
    ByteRTCProblemFeedbackOptionAudioNotClear = (1 << 1),
    /** 
     * @brief Video is not clear
     */
    ByteRTCProblemFeedbackOptionVideoNotClear = (1 << 2),
    /** 
     * @brief Audio & video out of sync
     */
    ByteRTCProblemFeedbackOptionNotSync = (1 << 3),
    /** 
     * @brief Audio card
     */
    ByteRTCProblemFeedbackOptionAudioLagging = (1 << 4),
    /** 
     * @brief Video card
     */
    ByteRTCProblemFeedbackOptionVideoLagging = (1 << 5),
    /** 
     * @brief Connection disconnected
     */
    ByteRTCProblemFeedbackOptionDisconnected = (1 << 6),
    /** 
     * @brief No sound
     */
    ByteRTCProblemFeedbackOptionNoAudio = (1 << 7),
    /** 
     * @brief No picture
     */
    ByteRTCProblemFeedbackOptionNoVideo = (1 << 8),
    /** 
     * @brief Too little sound
     */
    ByteRTCProblemFeedbackOptionAudioStrength = (1 << 9),
    /** 
     * @brief Echo noise
     */
    ByteRTCProblemFeedbackOptionEcho = (1 << 10),
    /** 
     * @brief Large delay in earphone monitoring
     */
    ByteRTCFeedBackProblemTypeEarBackDelay = (1 << 11),
};

/** 
 * @hidden
 * @brief notes missing
 */
BYTERTC_APPLE_EXPORT  @interface ByteRTCProblemOption: NSObject
/** 
 * @hidden
 * @brief notes missing
 */
- (instancetype _Nonnull)initWithOption:(ByteRTCProblemFeedbackOption)option;
/** 
 * @hidden
 * @brief notes missing
 */
@property(nonatomic, assign, readonly) ByteRTCProblemFeedbackOption option;
/** 
 * @hidden
 * @brief notes missing
 */
@property(nonatomic, copy, readonly) NSString * _Nonnull desc;
@end


/** 
 * @type keytype
 * @brief  First frame sending status
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFrameSendState) {
    /** 
     * @brief Sending
     */
    ByteRTCFirstFrameSendStateSending = 0,
    /** 
     * @brief Sent successfully
     */
    ByteRTCFirstFrameSendStateSent = 1,
    /** 
     * @brief Send failed
     */
    ByteRTCFirstFrameSendStateEnd = 2,
};

/** 
 * @type keytype
 * @brief  First frame playback status
 */
typedef NS_ENUM(NSUInteger, ByteRTCFirstFramePlayState) {
    /** 
     * Playing
     */
    ByteRTCFirstFramePlayStatePlaying = 0,
    /** 
     * Play success
     */
    ByteRTCFirstFramePlayStatePlay = 1,
    /** 
     * Play failed
     */
    ByteRTCFirstFramePlayStateEnd = 2,
};

/** 
 * @type keytype
 * @brief  Custom encryption type
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCEncryptType) {
    /** 
     * @brief Built-in encryption is not used. Default value.
     */
    ByteRTCEncryptTypeCustomize = 0,
    /** 
     * @brief AES-128-CBC  encryption algorithm
     */
    ByteRTCEncryptTypeAES128CBC = 1,
    /** 
     * @brief AES-256-CBC  encryption algorithm
     */
    ByteRTCEncryptTypeAES256CBC = 2,
    /** 
     * @brief AES-128-ECB  encryption algorithm
     */
    ByteRTCEncryptTypeAES128ECB = 3,
    /** 
     * @brief AES-256-ECB  encryption algorithm
     */
    ByteRTCEncryptTypeAES256ECB = 4
};

/** 
 * @type keytype
 * @brief Video encoding type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecType) {
    /** 
     * @brief Unknown type
     */
    ByteRTCVideoCodecTypeUnknown = 0,
    /** 
     * @brief H264 encoder
     */
    ByteRTCVideoCodecTypeH264 = 1,
    /** 
     * @brief ByteVC1 encoder
     */
    ByteRTCVideoCodecTypeByteVC1 = 2,
};

/** 
 * @type keytype
 * @brief  Transmission/Playback state of the media stream
 */
typedef NS_ENUM(NSInteger, ByteRTCMuteState) {
    /** 
     * @brief Enable
     */
    ByteRTCMuteStateOff = 0,
    /** 
     * @brief Disable
     */
    ByteRTCMuteStateOn = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief State of the black frame video stream
 */
typedef NS_ENUM(NSInteger,  ByteSEIStreamEventType) {
    /** 
     * @brief A black frame video stream is published from the remote user.  <br>
     *        In a voice call, when the remote user calls sendSEIMessage:andMessage:andRepeatCount:{@link #RTCVideo#sendSEIMessage:andMessage:andRepeatCount:} to send SEI data, SDK will automatically publish a black frame video stream, and trigger this callback.
     */
    ByteSEIStreamEventTypeStreamAdd = 0,
    /** 
     * @brief The black frame video stream is removed. The timing this callback will be triggered is as following:  <br>
     *        + The remote user turns on their camera, switching from a voice call to a video call.  <br>
     *        + No SEI data is sent within 1min after the remote user calls sendSEIMessage:andMessage:andRepeatCount:{@link #RTCVideo#sendSEIMessage:andMessage:andRepeatCount:}.  <br>
     *        + The remote user calls setVideoSourceType:WithStreamIndex:{@link #RTCVideo#setVideoSourceType:WithStreamIndex:} to switch to custom video capture.
     */
    ByteSEIStreamEventTypeStreamRemove = 1,
};

/** 
 * @type keytype
 * @brief Stream type
 */
typedef NS_ENUM(NSInteger, ByteRTCStreamIndex) {
    /** 
     * @brief  Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    ByteRTCStreamIndexMain = 0,
    /** 
     * @brief Screen-sharing stream. Video/Audio streams for screen sharing.
     */
    ByteRTCStreamIndexScreen = 1
};

/** 
 * @type keytype
 * @brief  Stream type for media stream information synchronization
 */
typedef NS_ENUM(NSInteger, ByteRTCSyncInfoStreamType) {
    /** 
     * @brief Audio stream
     */
    ByteRTCSyncInfoStreamTypeAudio = 0
};

/** 
 * @type keytype
 * @brief The state of the relaying for each room
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamState) {
    /** 
     * @brief Idle
     *        + States of all the rooms turns to idle after you call `stopForwardStreamToRooms`.
     *        + States of the rooms turns to idle that you call `updateForwardStreamToRooms` to remove.
     */
    ByteRTCForwardStreamStateIdle = 0,
    /** 
     * @brief Start relaying.
     *        + State of the rooms turn to this state after the relaying starts sucessfully by calling `startForwardStreamToRooms`.
     *        + State of the rooms added by calling `updateForwardStreamToRooms` turn to this state after the relaying start sucessfully.
     */
    ByteRTCForwardStreamStateSuccess = 1,
    /** 
     * @brief Relay fails. Refer to ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError} for more information for more information.
     *        Once the relaying fails, state of the room turns to this state after calling `startForwardStreamToRooms` or `updateForwardStreamToRooms`.
     */
    ByteRTCForwardStreamStateFailure = 2,
};

/** 
 * @type keytype
 * @brief Error codes during the relaying
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamError) {
    /** 
     * @brief Normal
     */
    ByteRTCForwardStreamErrorOK = 0,
    /** 
     * @brief Invalid argument
     */
    ByteRTCForwardStreamErrorInvalidArgument = 1201,
    /** 
     * @brief Invalid token
     */
    ByteRTCForwardStreamErrorInvalidToken = 1202,
    /** 
     * @brief Error returning from server
     */
    ByteRTCForwardStreamErrorResponse = 1203,
    /** 
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    ByteRTCForwardStreamErrorRemoteKicked = 1204,
    /** 
     * @brief Server denies.
     */
    ByteRTCForwardStreamErrorNotSupport = 1205,
};

/** 
 * @type keytype
 * @brief Events during the relaying
 */
typedef NS_ENUM(NSInteger, ByteRTCForwardStreamEvent) {
    /** 
     * @brief Relaying pauses for the reason of network disconnecting.
     */
    ByteRTCForwardStreamEventDisconnected = 0,
    /** 
     * @brief Relaying recovers from the disconnecting.
     */
    ByteRTCForwardStreamEventConnected = 1,
    /**  Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     * @brief
     */
    ByteRTCForwardStreamEventInterrupt = 2,
    /** 
     * @brief designated room list updates after you call `updateForwardStreamToRooms`.
     */
    ByteRTCForwardStreamEventDstRoomUpdated = 3,
    /** 
     * @brief Wrong API-calling order. For example, call `updateForwardStreamToRooms` before calling `startForwardStreamToRooms`.
     */
    ByteRTCForwardStreamEventUnExpectAPICall = 4,
};

/** 
 * @type keytype
 * @brief  Status of local recording
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingState) {
    /** 
     * @brief Recording exception
     */
    RecordingStateError = 0,
    /** 
     * @brief Recording in progress
     */
    RecordingStateProcessing = 1,
    /** 
     * @brief If the recording file is saved successfully, call `stopFileRecording:` to end the recording before receiving the status code.
     */
    RecordingStateSuccess = 2,
};

/** 
 * @type keytype
 * @brief  Local recording error code
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingErrorCode) {
    /** 
     * @brief Recording normal
     */
    RecordingErrorCodeOk = 0,
    /** 
     * @brief No file write permissions
     */
    RecordingErrorCodeNoPermission = -1,
    /** 
     * @brief The current version SDK does not support local recording, please contact technical support
     */
    RecordingErrorCodeNotSupport = -2,
    /** 
     * @brief Other anomalies
     */
    RecordingErrorCodeOther = -3,
};

/** 
 * @type keytype
 * @brief  Storage format of locally recorded files
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingFileType) {
    /** 
     * @brief Aac  format file
     */
    RecordingFileTypeAAC = 0,
    /** 
     * @brief Mp4  format file
     */
    RecordingFileTypeMP4 = 1,
};

/** 
 * @type keytype
 * @brief A/V synchronization states
 */
typedef NS_ENUM(NSInteger, ByteRTCAVSyncState) {
    /** 
     * @brief A/V synchronization begins.
     */
    AVSyncStateAVStreamSyncBegin = 0,
    /** 
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    AVSyncStateAudioStreamRemove = 1,
    /** 
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    AVSyncStateVdieoStreamRemove = 2,
    /** 
     * @hidden
     * @brief subscriber settings synchronization  <br>
     */
    AVSyncStateSetAVSyncStreamId = 3,
};
/** 
 * @type keytype
 * @brief Call test result
 */
typedef NS_ENUM(NSInteger, ByteRTCEchoTestResult) {
    /** 
     * @brief The playback of captured audio/video is received, test succeeds.
     */
    EchoTestSuccess = 0,
    /** 
     * @brief Test is not completed after 60 seconds and has been stopped automatically.
     */
    EchoTestTimeout = 1,
    /** 
     * @brief Less than 5s between the end of the last test and the start of the next test.
     */
    EchoTestIntervalShort = 2,
    /** 
     * @brief Audio capture error
     */
    EchoTestAudioDeviceError = 3,
    /** 
     * @brief Video capture error
     */
    EchoTestVideoDeviceError = 4,
    /** 
     * @brief Audio reception error
     */
    EchoTestAudioReceiveError = 5,
    /** 
     * @brief Video reception error
     */
    EchoTestVideoReceiveError = 6,
    /** 
     * @brief Unrecoverable internal error
     */
    EchoTestInternalError = 7
};
/** 
 * @type keytype
 * @brief Video/audio call test configurations
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEchoTestConfig : NSObject
/** 
 * @brief View for rendering received video
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/** 
 * @brief ID of the room that the tested user will join.  <br>
 */
@property(copy, nonatomic) NSString *_Nonnull roomId;
/** 
 * @brief User ID for testing
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
 * @brief Token used for authenticating users when they enter the room.
 */
@property(copy, nonatomic) NSString *_Nonnull token;
/** 
 * @brief Whether to test audio. The device to be tested is the default audio device.  <br>
 *        + true: Yes  <br>
 *            - If you use internal capture, the device microphone will automatically turn on and rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalAudioPropertiesReport:} will be triggered when the value of audioReportInterval is set to greater than 0, from which you can judge the working status of the microphone.  <br>
 *            - If you choose custom capture, you also need to call pushExternalAudioFrame:{@link #ByteRTCEngineKit#pushExternalAudioFrame:} to push the captured audio to the SDK.  <br>
 *        + false: No  <br>
 */
@property(assign, nonatomic) BOOL enableAudio;
/** 
 * @brief Whether to test video. If you are using a desktop PC, the device to be tested is by default the first video device in the list.  <br>
 *        + true: Yes  <br>
 *            - If you use internal capture, the device camera will automatically turn on.  <br>
 *            - If you choose custom capture, you also need to call pushExternalVideoFrame:time:{@link #ByteRTCEngineKit#pushExternalVideoFrame:time:} to push the captured video to the SDK.  <br>
 *        + false: No  <br>
 * @notes The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.
 */
@property(assign, nonatomic) BOOL enableVideo;
/** 
 * @brief Volume prompt interval in ms, the default value is 100. <br>
 *        + `<= 0`: Turn off prompt <br>
 *        + `(0,100]` Invalid interval value, and will be automatically reset to 100ms. <br>
 *        + `> 100`: the actual value of interval
 */
@property(assign, nonatomic) NSInteger audioReportInterval;
@end

/** 
 *  @type keytype
 *  @brief  User information.   <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUserInfo : NSObject
/** 
 * @brief User ID. The string matches the regular expression: `[a-zA-Z0-9_@\-]{1,128}`.
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
  * @brief Additional information of the user. The string is no more than 200 bytes. <br>
  *        The remote users will receive the info with `rtcEngine:onUserJoined:elapsed:`.
  */
@property(copy, nonatomic) NSString *_Nonnull extraInfo;
@end

/** 
 * @type keytype
 * @brief Room call statistics, reference period is 2s. <br>
 *        After the user enters the room successfully, the SDK will periodically notify the user through `onRoomStats` callback statistics in the current room. This data structure is the type of parameter that is called back to the user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomStats : NSObject
/** 
 * @brief The total time after the user enters the room and starts the call, in s, the cumulative value
 */
@property(assign, nonatomic) NSInteger duration;
/** 
 * @brief The total number of bytes sent by the local user  (bytes), the cumulative value
 */
@property(assign, nonatomic) NSInteger txBytes;
/** 
 * @brief The total number of bytes received by the local user  (bytes), the cumulative value
 */
@property(assign, nonatomic) NSInteger rxBytes;
/** 
 * @brief The instantaneous value of Tx bitrate in kbps
 */
@property(assign, nonatomic) NSInteger txKbitrate;
/** 
 * @brief The instantaneous value of Rx bitrate in kbps
 */
@property(assign, nonatomic) NSInteger rxKbitrate;
/** 
 * @brief Local user's audio transmission bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger txAudioKBitrate;
/** 
 * @brief Local user's audio receiving bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger rxAudioKBitrate;
/** 
 * @brief Local user's video transmission bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger txVideoKBitrate;
/** 
 * @brief Local user's video receiving bit rate  (kbps), instantaneous value
 */
@property(assign, nonatomic) NSInteger rxVideoKBitrate;
/** 
 * @brief The instantaneous RX bitrate of screen-sharing video in Kbps
 */
@property(assign, nonatomic) NSInteger txScreenKBitrate;
/** 
 * @brief The instantaneous TX bitrate of screen-sharing video in Kbps
 */
@property(assign, nonatomic) NSInteger rxScreenKBitrate;
/** 
 * @brief Number of visible users in the current room, including local users themselves
 */
@property(assign, nonatomic) NSInteger userCount;
/** 
 * @brief App  Current downlink packet loss rate
 */
@property(assign, nonatomic) float rxLostrate;
/** 
 * @brief App  current uplink packet loss rate
 */
@property(assign, nonatomic) float txLostrate;
/** 
 * @brief Client side round-trip time
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief Current App CPU usage
 */
// @property(assign, nonatomic) double cpuAppUsage;
/** 
 * @brief Total CPU usage of the current device
 */
// @property(assign, nonatomic) double cpuTotalUsage;


/** 
 * @brief The system downlink network jitter(ms)
 */
@property(assign, nonatomic) NSInteger txJitter;
/** 
 * @brief The system downlink network jitter(ms)
 */
@property(assign, nonatomic) NSInteger rxJitter;

@property(assign, nonatomic) NSInteger tx_cellular_kbitrate;

@property(assign, nonatomic) NSInteger rx_cellular_kbitrate;
@end

/** 
 * @type keytype
 * @brief The cpu and memory information used by App  <br>
 *         Information is periodically (2s) notified to the user by the SDK via the `reportSysStats` callback event.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSysStats : NSObject
/** 
 * @brief Current system cpu number
 */
@property(assign, nonatomic) unsigned int cpu_cores;
/** 
 * @brief The CPU usage of the current application, the value range is [0,1].
 */
@property(assign, nonatomic) double cpu_app_usage;
/** 
 * @brief The current system CPU usage, the value range is [0,1].
 */
@property(assign, nonatomic) double cpu_total_usage;
/** 
 * @brief Memory usage of the current app (in MB)
 */
@property(assign, nonatomic) double memory_usage;
/** 
 * @brief Full memory (in MB)
 */
@property(assign, nonatomic) unsigned long long full_memory;
/** 
 * @brief System used memory (in MB)
 */
@property(assign, nonatomic) unsigned long long total_memory_usage;
/** 
 * @brief Free allocable memory (in MB)
 */
@property(assign, nonatomic) unsigned long long free_memory;
/** 
 * @brief Memory usage of the current application (in %)
 */
@property(assign, nonatomic) double memory_ratio;
/** 
 * @brief System memory usage (in %)
 */
@property(assign, nonatomic) double total_memory_ratio;
@end

/** 
 * @type keytype
 * @brief Local video stream statistics, reference period 2s. <br>
 *        After the local user publishes the video stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`
 *        The delivery status of the published video stream during this reference period. This data structure is the type of parameter that is called back to the local user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalVideoStats : NSObject
/** 
 * @brief TX bitrate in Kbps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) float sentKBitrate;
/** 
 * @brief Sampling frame rate in fps of video capture during this reference period
 */
@property(assign, nonatomic) NSInteger inputFrameRate;
/** 
 * @brief TX frame rate in fps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger sentFrameRate;
/** 
 * @brief Encoder-output frame rate in fps of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encoderOutputFrameRate;
/** 
 * @brief Local-rendering frame rate in fps during this reference period
 */
@property(assign, nonatomic) NSInteger rendererOutputFrameRate;
/** 
 * @brief Reference period in ms.
 *        This field is used to set the reference period for the callback, which is 2 s by default.
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief Video packet loss rate. The video uplink packet loss rate in the reference period, the value range is  [0,1]. <br>
 */
@property(assign, nonatomic) float videoLossRate;
/** 
 * @brief Round-trip time. The unit is ms. <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief Video encoding bitrate in Kbps of the video stream with the highest resolution within the reference period.
 */
@property(assign, nonatomic) NSInteger encodedBitrate;
/** 
 * @brief Video encoding width in px of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encodedFrameWidth;
/** 
 * @brief Video encoding height in px of the video stream with the highest resolution within the reference period
 */
@property(assign, nonatomic) NSInteger encodedFrameHeight;
/** 
 * @brief The total number of the video stream with the highest resolution within the reference period sent in the reference period.
 */
@property(assign, nonatomic) NSInteger encodedFrameCount;
/** 
 * @brief Encoding type. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType} type. <br>
 */
@property(nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(assign, nonatomic) BOOL isScreen;
/** 
 * @brief Video uplink network jitter in ms. <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *         After the remote user subscribes to the remote audio stream successfully, the SDK will periodically notify the remote user of the reception status of the subscribed remote video stream during this reference period through `onRemoteStreamStats`
 *        . This data structure is the type of parameter that is called back to the local user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoStats : NSObject
/** 
 * @brief Distal video width.   <br>
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief Remote video height.   <br>
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief Remote video packet loss rate. The video downlink packet loss rate in the reference period, the value range is  [0,1]. <br>
 */
@property(assign, nonatomic) float videoLossRate;
/** 
 * @brief Receiving bit rate. Video reception rate within the reference period, in kbps. <br>
 */
@property(assign, nonatomic) float receivedKBitrate;
/** 
 * @brief Remote video receiving frame rate.   <br>
 */
@property(assign, nonatomic) NSInteger receivedFrameRate;
/** 
 * @brief Remote video decoding output frame rate.   <br>
 */
@property(assign, nonatomic) NSInteger decoderOutputFrameRate;
/** 
 * @brief Remote video rendering output frame rate.   <br>
 */
@property(assign, nonatomic) NSInteger renderOutputFrameRate;
/** 
 * @brief The number of remote video cards.   <br>
 */
@property(assign, nonatomic) NSInteger stallCount;
/** 
 * @brief Distal video lag duration, in ms. <br>
 */
@property(assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief End-to-end latency at the user experience level. The delay from the completion of encoding at the transmitting end to the completion of decoding at the receiving end, in units of ms. <br>
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief Whether the remote video stream is a screen share stream. You can know whether the current data comes from mainstream or screen stream.
 */
@property(assign, nonatomic) BOOL isScreen;
/** 
 * @brief Statistical interval, the interval of this reference period, in ms. <br>
 * @notes  This field is used to set the reference period for the callback, currently set to 2s.
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief Round-trip time. The unit is ms. <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief The cumulative duration of the video card of the remote user accounts for the percentage (%) of the total effective duration of the video after entering the room. The effective duration of the video refers to the duration of the video other than stopping sending the video stream and disabling the video module after the remote user enters the room to publish the video stream.
 */
@property(assign, nonatomic) NSInteger frozenRate;
/** 
 * @brief The resolution subscript of the SDK  subscribed remote video stream. <br>
 */
@property(assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief Video downlink network jitter in ms. <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief Local audio stream statistics, reference period 2s. <br>
 *        After the local user publishes the audio stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`
 *        The sending status of the published audio stream during this reference period. This data structure is the type of parameter that is called back to the local user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioStats : NSObject
/** 
 * @brief Audio packet loss rate. The audio uplink packet loss rate in this reference period is in the range of  [0,1]. <br>
 */
@property(assign, nonatomic) float audioLossRate;
/** 
 * @brief The bit rate of transmission. The audio transmission rate in the reference period is kbps. <br>
 */
@property(assign, nonatomic) float sentKBitrate;
/** 
 * @brief Acquisition sampling rate. Audio sampling rate information collected in the reference period, in units of Hz. <br>
 */
@property(assign, nonatomic) NSInteger recordSampleRate;
/** 
 * @brief Statistical interval. The interval of this reference period is in ms. <br>
 * @notes  This field is used to set the reference period for the callback. The default setting is 2s.
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief Round-trip time. The unit is ms. <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief Number of audio channels.   <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/** 
 * @brief Audio transmission sampling rate. Audio transmission sampling rate information in the reference period, in Hz. <br>
 */
@property(assign, nonatomic) NSInteger sentSampleRate;
/** 
 * @brief Audio uplink network jitter in ms. <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *         After the remote audio stream subscription is successful, the SDK will periodically notify the local user of the reception status of the subscribed audio stream during this reference period through `onRemoteStreamStats`
 *        . This data structure is the type of parameter that is called back to the local user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioStats : NSObject
/** 
 * @brief Audio packet loss rate. The audio downlink packet loss rate in the reference period, the value range is  [0,1]. <br>
 */
@property(assign, nonatomic) float audioLossRate;
/** 
 * @brief Receiving bit rate. The audio reception rate in the reference period in kbps. <br>
 */
@property(assign, nonatomic) float receivedKBitrate;
/** 
 * @brief Number of audio cards. Number of cards in the reference period.   <br>
 */
@property(assign, nonatomic) NSInteger stallCount;
/** 
 * @brief Audio Catton Duration. Catton duration in the reference period in ms. <br>
 */
@property(assign, nonatomic) NSInteger stallDuration;
/** 
 * @brief Play sample rate. Audio playback sample rate information within the reference period in Hz. <br>
 */
@property(assign, nonatomic) NSInteger playoutSampleRate;
/** 
 * @brief End-to-end latency at the user experience level. The delay from the completion of encoding at the transmitting end to the completion of decoding at the receiving end, in units of ms. <br>
 */
@property(assign, nonatomic) NSInteger e2eDelay;
/** 
 * @brief Statistical interval. The interval of this reference period is in ms. <br>
 */
@property(assign, nonatomic) NSInteger statsInterval;
/** 
 * @brief Round-trip time for client side to server level data transfer in ms. <br>
 */
@property(assign, nonatomic) NSInteger rtt;
/** 
 * @brief The sender-server level-the receiver-link data transmission round-trip time. The unit is ms. <br>
 */
@property(assign, nonatomic) NSInteger total_rtt;
/** 
 * @brief The quality of the audio stream sent by the remote user. Value meaning reference ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}. <br>
 */
@property(assign, nonatomic) NSInteger quality;
/** 
 * @brief The delay caused by the introduction of the jitter buffer mechanism. The unit is ms. <br>
 */
@property(assign, nonatomic) NSInteger jitterBufferDelay;
/** 
 * @brief Number of audio channels.   <br>
 */
@property(assign, nonatomic) NSInteger numChannels;
/** 
 * @brief Audio reception sampling rate. Remote audio sample rate information received within the reference period, in Hz. <br>
 */
@property(assign, nonatomic) NSInteger receivedSampleRate;
/** 
 * @brief The accumulated length of the audio card occurs after the remote user joins the room as a percentage of the total effective length of the audio. The effective duration of audio refers to the duration of audio other than stopping sending audio streams and disabling audio modules after remote users enter the room to publish audio streams.
 */
@property(assign, nonatomic) NSInteger frozenRate;
/** 
 * @brief Audio PLC Total number of sample points. <br>
 */
@property(assign, nonatomic) NSInteger concealedSamples;
/** 
 * @brief PLC  cumulative times. <br>
 */
@property(assign, nonatomic) NSInteger concealmentEvent;
/** 
 * @brief Audio decoding sample rate. Audio decoding sample rate information in the reference period in Hz. <br>
 */
@property(assign, nonatomic) NSInteger decSampleRate;
/** 
 * @brief Decoding duration. The total time-consuming decoding of the remote audio stream received within this reference period, in units of s. <br>
 */
@property(assign, nonatomic) NSInteger decDuration;
/** 
 * @brief Video downlink network jitter in ms. <br>
 */
@property(assign, nonatomic) NSInteger jitter;
@end

/** 
 * @type keytype
 * @brief Local audio/video stream statistics and network status, the reference period is 2s. <br>
 *        After the local user publishes the audio/video stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`
 *        The transmission status of the published audio/video stream during this reference period. This data structure is the type of parameter that is called back to the user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalStreamStats : NSObject
/** 
 * @brief For statistics on audio streams sent by local devices. See ByteRTCLocalAudioStats{@link #ByteRTCLocalAudioStats}
 */
@property(strong, nonatomic) ByteRTCLocalAudioStats *_Nonnull audio_stats;
/** 
 * @brief For statistics on video streams sent by local devices. See ByteRTCLocalVideoStats{@link #ByteRTCLocalVideoStats}
 */
@property(strong, nonatomic) ByteRTCLocalVideoStats *_Nonnull video_stats;
/** 
 * @hidden
 * @brief For the uplink network quality of the media stream of the user you belong to. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @hidden
 * @brief The downlink network quality of the media stream belongs to the user. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(nonatomic, assign) BOOL is_screen;
@end

/** 
 * @type keytype
 * @brief The remote audio/video stream statistics and network status subscribed by the user, with a reference period of 2s. <br>
 *         After the remote user subscribed to successfully publish the audio/video stream, the SDK will periodically notify the remote user of the reception status of the subscribed audio/video stream during this reference period through `onRemoteStreamStats`
 *        . This data structure is the type of parameter that is called back to the local user. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamStats : NSObject
/** 
 * @brief User ID. The user ID of the audio source. <br>
 */
@property(copy, nonatomic) NSString *_Nonnull uid;
/** 
 * @brief For statistics on remote audio streams. See ByteRTCRemoteAudioStats{@link #ByteRTCRemoteAudioStats}
 */
@property(strong, nonatomic) ByteRTCRemoteAudioStats *_Nonnull audio_stats;
/** 
 * @brief For statistics on remote video streams. See ByteRTCRemoteVideoStats{@link #ByteRTCRemoteVideoStats}
 */
@property(strong, nonatomic) ByteRTCRemoteVideoStats *_Nonnull video_stats;
/** 
 * @hidden
 * @brief For the uplink network quality of the media stream of the user you belong to. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality tx_quality;
/** 
 * @hidden
 * @brief The downlink network quality of the media stream belongs to the user. See ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality}
 * @deprecated since 336.1, use rtcEngine:onNetworkQuality:remoteQualities:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkQuality:remoteQualities:} instead
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rx_quality;
/** 
 * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
 */
@property(nonatomic, assign) BOOL is_screen;
@end

/** 
 * @type keytype
 * @brief  User information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCUser : NSObject
/** 
 * @brief User ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief Meta information
 */
@property(nonatomic, copy, nullable) NSString *metaData;
@end

/** 
 * @type keytype
 * @brief Information about the remote stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamKey : NSObject
/** 
 * @brief The ID of the user who published the stream.
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief The ID of the room from which the stream was published.
 */
@property(nonatomic, copy, nullable) NSString *roomId;
/** 
 * @brief Stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(nonatomic, assign) ByteRTCStreamIndex streamIndex;
@end

#pragma mark - EncryptHandler
/** 
 * @type callback
 * @region  encryption
 * @author wangjunlin.3182
 * @brief  Custom encryption interface
 */
@protocol ByteRTCEncryptHandler <NSObject>

@required
/** 
 * @type api
 * @region Encryption
 * @author wangjunlin.3182
 * @brief Custom encryption.   <br>
 *        Encrypts audio & video frame data before transmission using the custom encryption method set.
 * @param rawData Original audio & video frame data
 * @return Encrypted data   <br>
 *         + Non-empty, indicating that the encrypted data <br>
 *         + Is empty, indicating that the data has been discarded
 * @notes  <br>
 *         + Before using this interface for custom encryption, you must first set the custom encryption method. See `setCustomizeEncryptHandler:`.
 *         + Use ByteRTCDecryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCDecryptRawData:} to decrypt encrypted audio & video frame data.
 *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
 */
- (NSData * _Nonnull) ByteRTCEncryptRawData:(NSData * _Nonnull)rawData;

@required
/** 
 * @type api
 * @region  encryption
 * @author wangjunlin.3182
 * @brief  Custom decryption.   <br>
 *         Decrypts custom encrypted audio & video frame data. For custom encryption. See ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}.
 * @param rawData  Received encrypted audio & video frame data
 * @return  Decrypted data   <br>
 *         + Non-empty, indicating that the decrypted data <br>
 *         + Is empty, indicating that the frame is discarded
 * @notes  <br>
 *         + Before using this interface to decrypt, you must first set the decryption method. See `setCustomizeEncryptHandler:`.
 *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
 */
- (NSData * _Nonnull) ByteRTCDecryptRawData:(NSData * _Nonnull)rawData;
@end

/** 
 * @type callback
 * @region  monitoring
 * @brief  Non-business related monitoring event callback
 */
@protocol ByteRTCMonitorDelegate <NSObject>

@optional

/** 
 * @hidden
 * @type callback
 * @region monitoring
 * @brief Event tracking log callback   <br>
 * @param data   <br>
 *        Specific event tracking content <br>
 * @param type   <br>
 *        Event tracking type
 */
- (void)onMonitorLog:(NSDictionary * _Nullable)data withType:(NSString * _Nullable)type;

/** 
 * @hidden
 * @type api
 * @region  monitor
 * @brief  Whether to output from the console
 * @return
 *         Return whether to output from the console <br>
 *         + YES output all logs to the console <br>
 *         + NO output no console information
 */
- (BOOL)isConsole;

/** 
 * @hidden
 * @type callback
 * @region  monitor
 * @brief  Output more debugging information
 */
- (void)onVerboseLogWithLevel:(ByteRTCLogLevel)level
                     filename:(NSString * _Nonnull)filename
                          tag:(NSString * _Nonnull)tag
                         line:(int)line
                 functionName:(NSString * _Nonnull)funcName
                       format:(NSString * _Nonnull)format;
@end

#pragma mark - FileRecording

/** 
 * @type keytype
 * @brief  Local recording parameter configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingConfig : NSObject
/** 
 * @brief The absolute path to save the recording file. You need to specify a legal path with read and write permissions.
 */
@property(strong, nonatomic) NSString* _Nullable dirPath;
/** 
 * @brief Record the stored file format. See ByteRTCRecordingFileType{@link #ByteRTCRecordingFileType}
 */
@property(assign, nonatomic) ByteRTCRecordingFileType recordingFileType;
@end

/** 
 * @type keytype
 * @brief  Local recording progress
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingProgress : NSObject
/** 
 * @brief The cumulative recording time of the current file, in milliseconds
 */
@property(assign, nonatomic) unsigned long long duration;
/** 
 * @brief The size of the currently recorded file in bytes
 */
@property(assign, nonatomic) unsigned long long fileSize;
@end

/** 
 * @type keytype
 * @brief  Details of local recording
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRecordingInfo : NSObject
/** 
 * @brief The absolute path of the recorded file, including the file name and file suffix
 */
@property(strong, nonatomic) NSString* _Nullable filePath;
/** 
 * @brief For the video encoding type of the recorded file. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief The width of the recorded video, in pixels. Please ignore this field for audio-only recording
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief The height of the recorded video, the unit: pixels. Please ignore this field for audio-only recording
 */
@property(nonatomic, assign) NSInteger height;
@end

/** 
 * @type keytype
 * @brief  Configuration related to media stream information synchronization
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCStreamSycnInfoConfig : NSObject

/** 
 * @brief Stream properties, mainstream or screen streams. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @brief The number of duplicates sent by the message, the value range is  [0,25], it is recommended to set it to [3,5].
 */
@property(assign, nonatomic) int repeatCount;
/** 
 * @brief For the stream type for media stream information synchronization. See ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType}.
 */
@property(assign, nonatomic) ByteRTCSyncInfoStreamType streamType;
@end

/** 
 * @type keytype
 * @brief Information of the rooms where you want to relay the media stream to
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamConfiguration: NSObject
    /** 
     * @brief ID of the room where the media stream aims to relay to
     */
@property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief RoomId and UserId are required to generate the Token to forward media streams to the room.<br>
     *        During developing and testing, you can use temporary tokens generated on the console. At the production stage, Tokens are generated by the token generating application deployed on your server.<br>
     *        Forwarding will fail if the token is invalid.
     */
@property(strong, nonatomic) NSString* _Nullable token;
@end

/** 
* @type keytype
 * @brief State and error for each room during relaying
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamStateInfo: NSObject
    /** 
     * @brief ID of the room where the media stream aims to relay to
     *        An Empty string is for all rooms.
     */
@property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief State of the room during relaying. Refer to ByteRTCForwardStreamState{@link #ByteRTCForwardStreamState} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamState state;
    /** 
     * @brief Error code from the room during relaying. Refer to ByteRTCForwardStreamError{@link #ByteRTCForwardStreamError} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamError error;
@end

/** 
 * @type keytype
 * @brief Event from each room during relaying
 */
BYTERTC_APPLE_EXPORT @interface ForwardStreamEventInfo: NSObject
    /** 
     * @brief ID of the room where the media stream aims to relay to
     *        An Empty string is for all rooms.
     */
@property(strong, nonatomic) NSString* _Nullable roomId;
    /** 
     * @brief Event from the room during relaying. Refer to ByteRTCForwardStreamEvent{@link #ByteRTCForwardStreamEvent} for more information.
     */
@property(assign, nonatomic) ByteRTCForwardStreamEvent event;
@end

/** 
 * @type keytype
 * @brief Tx/Rx network quality
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCNetworkQualityStats: NSObject
/** 
 * @brief User ID
 */
@property(strong, nonatomic) NSString* _Nonnull uid;
/** 
 * @brief Packet loss ratio of the local client, ranging [0.0,1.0]
 *        For a local user, it is the sent-packet loss ratio.
 *        For a remote user, it is the loss ratio of all the packets received.
 */
@property(assign, nonatomic) double lossRatio;
/** 
 * @brief Round-trip time (RTT) from client to server. Effective for the local user. Unit: ms
 */
@property(assign, nonatomic) int rtt;
/** 
 * @brief Average transmission rate of the media RTP packages in 2s. unit: bps
 *        For a local user, it is the packet-sending speed.
 *        For a more user, it is the speed of receiving all the subsribed medias.
 */
@property(assign, nonatomic) int totalBandwidth;
/** 
 * @brief Tx network quality grade. Refer to ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} for details.
 */
@property(assign, nonatomic) ByteRTCNetworkQuality txQuality;
/** 
 * @hidden
 * @brief Rx network quality grade. Refer to ByteRTCNetworkQuality{@link #ByteRTCNetworkQuality} for details.
 */
@property(assign, nonatomic) ByteRTCNetworkQuality rxQuality;
@end
/** 
 * @type keytype
 * @brief Cloud Proxy Information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCCloudProxyInfo: NSObject
/** 
 * @type keytype
 * @brief Cloud proxy IP
 */
@property(strong, nonatomic) NSString* _Nonnull cloudProxyIp;
/** 
 * @type keytype
 * @brief Cloud proxy Port
 */
@property(assign, nonatomic) int cloudProxyPort;
@end

#pragma mark - ByteRTCDeviceCollection
/** 
 * @type api
 * @hidden(iOS)
 * @brief Media Device Info
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCDeviceCollection : NSObject
/** 
 * @type api
 * @hidden(iOS)
 * @region engine management
 * @author dixing
 * @brief Get the number of media devices
 * @return Number of media devices
 */
- (int)getCount;
/** 
 * @type api
 * @hidden(iOS)
 * @region Engine management
 * @author dixing
 * @brief Get the information of the specific device
 * @param  index Device index number, starting from 0. The index must be less than the return value of GetCount{@link #ByteRTCDeviceCollection#GetCount}.
 * @param  deviceName device name
 * @param  deviceID device ID
 * @return   <br>
 *         + 0: Success. <br>
 *         + !0: failure <br>
 */
- (int)getDevice:(int)index DeviceName:(NSString * _Nonnull * _Nonnull)deviceName DeviceID:(NSString * _Nonnull * _Nonnull) deviceID;
@end
