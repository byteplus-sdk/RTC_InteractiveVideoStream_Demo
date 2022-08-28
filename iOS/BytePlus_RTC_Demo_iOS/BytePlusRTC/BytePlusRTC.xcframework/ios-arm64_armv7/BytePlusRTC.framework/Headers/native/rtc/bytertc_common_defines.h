/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Common Defines
 */

#pragma once

#ifdef WIN32
#define BYTERTC_API extern "C" __declspec(dllexport)
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC && !(TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
#define BYTERTC_API __attribute__((__visibility__("default"))) extern "C"
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif
#else
#define BYTERTC_API __attribute__((__visibility__("default")))
#endif

#include <stdint.h>
#include <stddef.h>

namespace bytertc {

/** 
 * @type keytype
 * @brief  The reason why the user left the room.   <br>
 */
enum UserOfflineReason {
    /** 
     * @brief The remote user calls `leaveRoom` to exit the room. <br>
     */
    kUserOfflineReasonQuit = 0,
    /** 
     * @brief The remote user is offline.   <br>
     */
    kUserOfflineReasonDropped = 1,
    /** 
     * @brief The remote user switches to invisible.   <br>
     */
    kUserOfflineReasonSwitchToInvisible = 2,
    /** 
     * @brief The remote user is kicked out of the room.
     *        Is kicked out of the room due to calling the kicked out user's OpenAPI.
     */
    kUserOfflineReasonKickedByAdmin = 3,
};

/** 
 * @type keytype
 * @brief The reason why the remote flow in the room was removed.   <br>
 */
enum StreamRemoveReason {
    /** 
     * @brief The remote user stops publishing the flow.   <br>
     */
    kStreamRemoveReasonUnpublish = 0,
    /** 
     * @brief The remote user failed to publish the flow.   <br>
     */
    kStreamRemoveReasonPublishFailed = 1,
    /** 
     * @brief Keep alive failed.   <br>
     */
    kStreamRemoveReasonKeepLiveFailed = 2,
    /** 
     * @brief The remote user is disconnected.   <br>
     */
    kStreamRemoveReasonClientDisconnected = 3,
    /** 
     * @brief The remote user republishes the flow.   <br>
     */
    kStreamRemoveReasonRepublish = 4,
    /** 
     * @brief Other reasons.   <br>
     */
    kStreamRemoveReasonOther = 5,
};

/** 
 * @hidden
 * @type keytype
 * @brief  User persona.   <br>
 */
enum UserRoleType {
    /** 
     * @brief Live streaming host role. This role user can publish and subscribe to audio & video streams in the room, and other users in the room can perceive the presence of this user.   <br>
     */
    kUserRoleTypeBroadcaster = 1,
    /** 
     * @brief Stealth user persona. This role user can only subscribe to audio & video streams in the room, and other users in the room cannot perceive the presence of this user.   <br>
     */
    kUserRoleTypeSilentAudience = 2,
};

/** 
 * @type keytype
 * @brief The type of joining the room.   <br>
 */
enum JoinRoomType {
    /** 
     * @brief Join the room for the first time. The user calls `joinRoom` to join the room. <br>
     */
    kJoinRoomTypeFirst = 0,
    /** 
     * @brief Rejoin the room. The user loses connection to the server due to poor network, and rejoins the room successfully.   <br>
     */
    kJoinRoomTypeReconnected = 1,
};

/** 
 * @type keytype
 * @brief  The type of user login
 */
enum LoginType {
    /** 
     * @brief login for the first time. The user manually called `login` and received a successful login.
     */
    kLoginTypeFirst = 0,
    /** 
     * @brief Reconnect. User network is poor, lost connection with the server, SDK  automatically reconnect login success.
     */
    kLoginTypeReconnected = 1,
};

/** 
 * @type errorcode
 * @brief login result   <br>
 *        The result of calling `login` will notify the user through the `onLoginResult` callback.
 */
enum LoginErrorCode {
    /** 
     * @brief Call the `login` method to log in successfully
     */
    kLoginErrorCodeSuccess = 0,
    /** 
     * @brief The Token used when calling the `login` method is invalid or expired, requiring the user to reacquire the Token.
     */
    kLoginErrorCodeInvalidToken = -1000,
    /** 
     * @brief login error   <br>
     *        An unknown error occurred when calling the `login` method, which caused the login to fail and requires re-login.
     */
    kLoginErrorCodeLoginFailed = -1001,
    /** 
     * @brief There was a problem with the user ID passed in when the `login` method was called.
     */
    kLoginErrorCodeInvalidUserId = -1002,
    /** 
     * @brief An error occurred at the server level when calling `login` to log in.
     */
    kLoginErrorCodeServerError = -1003,
};

/** 
 * @type keytype
 * @brief User online status.
 */
enum USER_ONLINE_STATUS {
    /** 
     * @brief The peer user is offline   <br>
     *         The peer user has called `logout`, or has not called `login` to log in.
     */
    kUserOnlineStatusOffline = 0,
    /** 
     * @brief The peer user is online   <br>
     *         The peer user calls `login` to log in, and the connection status is normal.
     */
    kUserOnlineStatusOnline = 1,
    /** 
     * @brief Unable to get the online state of the peer user   <br>
     *        Returned when a cascade error occurs and the online state of the peer user is abnormal.
     */
    kUserOnlineStatusUnreachable = 2,
};

/** 
 * @type keytype
 * @brief  Server message send result content
 */
struct ServerACKMsg {
    /** 
     * @brief length
     */
    int length;
    /** 
     * @brief content of the message
     */
    char* ACKMsg;
};

/** 
 * @type keytype
 * @brief Message type
 */
 /** 
 * @type keytype
 * @brief RTM message
 */
enum MessageConfig {
    /** 
     * @brief Low latency reliable and orderly message
     */
    kMessageConfigReliableOrdered = 0,
    /** 
     * @brief Ultra-low latency ordered message
     */
    kMessageConfigUnreliableOrdered = 1,
    /** 
     * @brief Ultra-low latency unordered message
     */
    kMessageConfigUnreliableUnordered = 2
};

/** 
 * @type keytype
 * @brief Result of sending messages and the reason of failure if it fails.
 */
enum UserMessageSendResult {
    /** 
     * @brief The message has been sent successfully.
     */
    kUserMessageSendResultSuccess = 0,
    /** 
     * @brief Failure. Sending timeout.
     */
    kUserMessageSendResultTimeout = 1,
    /** 
     * @brief Failure. Channel disconnected.
     */
    kUserMessageSendResultBroken = 2,
    /** 
     * @brief Failure. Recipient not found.
     */
    kUserMessageSendResultNoReceiver = 3,
    /** 
     * @brief Failure. Failed to get cascade path
     */
    kUserMessageSendResultNoRelayPath = 4,
    /** 
     * @brief Failure. The sender of the message did not join the room
     */
    kUserMessageSendResultNotJoin = 100,
    /** 
     * @brief Failure. Connection initialization not completed
     */
    kUserMessageSendResultInit = 101,
    /** 
     * @brief Failure. No data transmission channel connection available
     */
    kUserMessageSendResultNoConnection = 102,
    /** 
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    kUserMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief Failure. The id of the recipient is empty
     */
    kUserMessageSendResultEmptyUser = 104,
    /** 
     * @brief Failure. The sender of the message did not log in.
     */
    kUserMessageSendResultNotLogin = 105,
    /** 
     * @brief Failure. No parameters were set before sending the message to the server
     */
    kUserMessageSendResultServerParamsNotSet = 106,
    /** 
     * @brief Failure. Unknown error
     */
    kUserMessageSendResultUnknown = 1000,
};

/** 
 * @type keytype
 * @brief Result of broadcasting messages in the room
 */
enum RoomMessageSendResult {
    /** 
     * @brief Message sent successfully.
     */
    kRoomMessageSendResultSuccess = 200,
    /** 
     * @brief Failure. The sender has not joined a room.
     */
    kRoomMessageSendResultNotJoin = 100,
    /** 
     * @brief Failure. No data transmission channel connection available
     */
    kRoomMessageSendResultNoConnection = 102,
    /** 
     * @brief Failure. Message exceeds the range of the permitted size, 64 KB.
     */
    kRoomMessageSendResultExceedMaxLength = 103,
    /** 
     * @brief Failure. Unknown error
     */
    kRoomMessageSendResultUnknown = 1000,
};
/** 
 * @type keytype
 * @brief SDK  Connection status with the signaling server.
 */
enum ConnectionState {
    /** 
     * @brief The connection is disconnected for more than 12s.
     */
    kConnectionStateDisconnected = 1,
    /** 
     * @brief The first request to connect to the server. Connecting.
     */
    kConnectionStateConnecting = 2,
    /** 
     * @brief The first connection was successful.
     */
    kConnectionStateConnected = 3,
    /** 
     * @brief The code includes the following status: <br>
     *        + The first connection is not successful for 10s. <br>
     *        + The connection has been lost for 10s. Auto reconnecting.
     */
    kConnectionStateReconnecting = 4,
    /** 
     * @brief Successful reconnection after disconnection.
     */
    kConnectionStateReconnected = 5,
    /** 
     * @brief Be in status `DISCONNECTION` for more than 10s. The requests to reconnect failed.
     */
    kConnectionStateLost = 6,
};

/** 
 * @type errorcode
 * @brief Return value to start probing
 *        `startNetworkDetection` Return object type
 */
enum NetworkDetectionStartReturn {
    /** 
     * @brief Network probing enabled successfully.
     */
    kNetworkDetectionStartReturnSuccess = 0,
    /** 
     * @brief Failed to start probing. Parameter error, both uplink and downlink probes are 'false ', or the expected bandwidth exceeds the range [100,10000]
     */
    kNetworkDetectionStartReturnParamErr = 1,
    /** 
     * @brief Failed to start probing. The reason for the failure is that the local push-pull flow has started
     */
    kNetworkDetectionStartReturnStreaming = 2,
    /** 
     * @brief Detection has started, no need to open it again
     */
    kNetworkDetectionStartReturnStarted = 3,
    /** 
     * @brief Do not support this function
     */
    kNetworkDetectionStartReturnNotSupport = 4,
};

/** 
 * @type keytype
 * @brief The reason why the probe stopped before the call
 *        `onNetworkDetectionStopped` The parameter type of the callback
 */
enum NetworkDetectionStopReason {
    /** 
     * @brief User actively stops
     */
    kNetworkDetectionStopReasonUser,
    /** 
     * @brief Detection over three minutes
     */
    kNetworkDetectionStopReasonTimeout,
    /** 
     * @brief Probe network connection disconnected. <br> When no reply is received beyond 12s, the SDK will disconnect the network and will not try to reconnect.
     */
    kNetworkDetectionStopReasonConnectionLost,
    /** 
     * @brief Local start push-pull flow, stop detection
     */
    kNetworkDetectionStopReasonStreaming,
    /** 
     * @brief Network probe failure, internal anomaly
     */
    kNetworkDetectionStopReasonInnerErr,
};

/** 
 * @type keytype
 * @brief The type of probe link before the call.
 *        `onNetworkDetectionResult` The parameter type for the callback
 */
enum NetworkDetectionLinkType {
    /** 
     * @brief Uplink network sounding
     */
    kNetworkDetectionLinkTypeUp = 0,
    /** 
     * @brief Downlink network detection
     */
    kNetworkDetectionLinkTypeDown,
};

/** 
 * @type keytype
 * @brief Media streaming network quality.
 */
enum NetworkQuality {
    /** 
     * @brief Network quality unknown.
     */
    kNetworkQualityUnknown = 0,
    /** 
     * @brief The network quality is excellent.
     */
    kNetworkQualityExcellent,
    /** 
     * @brief The subjective feeling is similar to kNetworkQualityExcellent, but the bit rate may be slightly lower.
     */
    kNetworkQualityGood,
    /** 
     * @brief Subjective feelings are flawed but do not affect communication.
     */
    kNetworkQualityPoor,
    /** 
     * @brief Can barely communicate but not smoothly.
     */
    kNetworkQualityBad,
    /** 
     * @brief The quality of the network is very poor and communication is basically impossible.
     */
    kNetworkQualityVbad,
};

/** 
 * @type keytype
 * @brief Tx/Rx network quality
 */
struct NetworkQualityStats {
    /** 
     * @brief User ID
     */
    const char* uid;
    /** 
     * @brief Packet loss ratio of the local client, ranging [0.0,1.0]
     *        For a local user, it is the sent-packet loss ratio.
     *        For a remote user, it is the loss ratio of all the packets received.
     */
    double fraction_lost;
    /** 
     * @brief Round-trip time (RTT) from client to server. Effective for the local user. Unit: ms
     */
    int rtt;
    /** 
     * @brief Average transmission rate of the media RTP packages in 2s. unit: bps
     *        For a local user, it is the packet-transmitting speed.
     *        For a more user, it is the speed of receiving all the subsribed media.
     */
    int total_bandwidth;
    /** 
     * @brief Tx network quality grade. Refer to NetworkQuality{@link #NetworkQuality} for details.
     */
    NetworkQuality tx_quality;
    /** 
     * @brief Rx network quality grade. Refer to NetworkQuality{@link #NetworkQuality} for details.
     */
    NetworkQuality rx_quality;
    /**
     * @hidden
     */
    NetworkQualityStats() : uid(""), fraction_lost(0.), rtt(0), total_bandwidth(0),
        tx_quality(kNetworkQualityUnknown), rx_quality(kNetworkQualityUnknown) {
    }
};

/** 
 * @type keytype
 * @brief SDK  Network connection type.
 */
enum NetworkType {
    /** 
     * @brief Network connection type unknown.
     */
    kNetworkTypeUnknown = -1,
    /** 
     * @brief The network connection has been disconnected.
     */
    kNetworkTypeDisconnected = 0,
    /** 
     * @brief The network connection type is LAN.
     */
    kNetworkTypeLAN = 1,
    /** 
     * @brief The network connection type is Wi-Fi (including hotspots).
     */
    kNetworkTypeWIFI = 2,
    /** 
     * @brief The network connection type is 2G mobile network.
     */
    kNetworkTypeMobile2G = 3,
    /** 
     * @brief The network connection type is 3G mobile network.
     */
    kNetworkTypeMobile3G = 4,
    /** 
     * @brief The network connection type is 4G mobile network.
     */
    kNetworkTypeMobile4G = 5,
    /** 
     * @brief The network connection type is 5G mobile network.
     */
    kNetworkTypeMobile5G = 6,
};

/** 
 * @type keytype
 * @brief  Room profile
 */
enum RoomProfileType {
    /** 
     * @brief Normal call mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        You should use this mode for 1V1 calls. This mode works fine even if the network quality is poor.
     */
    kRoomProfileTypeCommunication = 0,
    /** 
     * @brief Live broadcasting mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        Use this mode for high quality of the media. <br>
     *        In this mode, audio plays in media mode for Bluetooth earphones.
     */
    kRoomProfileTypeLiveBroadcasting = 1,
    /** 
     * @brief Game voice mode. <br>
     *        Mono audio channel. The sampling rate is 16kHz. <br>
     *        Additional performance optimizations have been made for low-end devices: < br >
     *             + Encodes frame length 40/60 for some low-end models. < br >
     *             + Disables software 3A audio processing for some low-end models.< br >
     *        Enhance iOS Compatibility with other screen recordings to avoid audio recordings being interrupted by RTC.
     */
    kRoomProfileTypeGame = 2,
    /** 
     * @brief Cloud game mode. <br>
     *        Mono audio channel. The sampling rate is 48kHz. <br>
     *        Use this mode for scenerios of low latency and high bitrate. <br>
     *        This mode works poor when the network quality is poor.
     */
    kRoomProfileTypeCloudGame = 3,
    /** 
     * @brief Low latency mode. <br>
     *        Use this mode when the scenario is neither a game or cloud game but requires very low latency. <br>
     *        In this mode, call delay will be significantly reduced. But the audio quality and the redundancy for weak network are poor. <br>
     *        You must consult the technical support specialist before using this mode.
     */
    kRoomProfileTypeLowLatency = 4,
    /** 
     * @brief For 1:1 audio calls
     */
    kRoomProfileTypeChat = 5,
    /** 
     * @brief For audio meetings for 3 or more people
     */
    kRoomProfileTypeChatRoom = 6,
    /** 
     * @brief For scenarios such as "Watch together." and "Listen together."
     */
    kRoomProfileTypeLwTogether = 7,
    /** 
     * @brief For the game apps demanding high-resolution audio
     */
    kRoomProfileTypeGameHD = 8,
    /** 
     * @brief For the event of co-hosting in the live streaming
     */
    kRoomProfileTypeCoHost = 9,
    /** 
     * @brief For interactive podcasts
     */
    kRoomProfileTypeInteractivePodcast = 10,
    /** 
     * @brief For the online karaoke with high-quality audio and low latency
     */
    kRoomProfileTypeKTV = 11,
    /** 
     * @brief For the online-chorusing scenarios with high-quality audio and low latency
     */
    kRoomProfileTypeChorus = 12,
    /** 
     * @brief For VR chat with support for 192 KHz audio sample rate and feature of 360 Reality Audio
     */
    kRoomProfileTypeVRChat = 13,
    /** 
     * @brief For 1 : 1 video chat in the game scenario using game stream technology
     */
    kRoomProfileTypeGameStreaming = 14,
    /** 
     * @brief For the live streaming within LAN with the support of 60fps @8K video stream with the bitrate of 100 Mbps
     */
    kRoomProfileTypeLanLiveStreaming = 15,
    /** 
     * @brief For online meetings
     */
    kRoomProfileTypeMeeting = 16,
    /** 
     * @brief  For the meeting app using in meeting rooms
     */
    kRoomProfileTypeMeetingRoom = 17,
    /** 
     * @brief For the online classrooms and lectures
     */
    kRoomProfileTypeClassroom = 18,
};

/** 
 * @type keytype
 * @brief  Multi-room parameter configuration
 */
struct AudioRoomConfig {
    /** 
     * @brief Room profile. See RoomProfileType{@link #RoomProfileType}. The default is `kRoomProfileTypeCommunication`. The setting cannot be changed after joining the room.
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
     * @brief Whether to automatically subscribe to the audio stream. The default is automatic subscription.
     */
    bool is_auto_subscribe_audio = true;
    
    bool is_auto_publish_audio = false;
};

/** 
 * @type keytype
 * @brief Type of media device
 */
enum MediaDeviceType {
    /** 
     * @brief Unknown device
     */
    kMediaDeviceTypeAudioUnknown = -1,
    /** 
     * @brief Speaker or headphone
     */
    kMediaDeviceTypeAudioRenderDevice = 0,
    /** 
     * @brief Microphone
     */
    kMediaDeviceTypeAudioCaptureDevice = 1,
    /** 
     *@hidden
     *@brief  Video rendering device type, this type is not used yet
     */
    kMediaDeviceTypeVideoRenderDevice = 2,
    /** 
     *@brief Video capture device
     */
    kMediaDeviceTypeVideoCaptureDevice = 3,
    /** 
     * @brief Screen capture device
     */
    kMediaDeviceTypeScreenVideoCaptureDevice = 4,
    /** 
     * @brief Screen audio capture device
     */
    kMediaDeviceTypeScreenAudioCaptureDevice = 5,
};

/** 
 * @type keytype
 * @brief  Media device state.
 */
enum MediaDeviceState {
    /** 
     *@brief On
     */
    kMediaDeviceStateStarted = 1,
    /** 
     *@brief Off
     */
    kMediaDeviceStateStopped = 2,
    /** 
     *@brief Runtime error<br>
     *        For example, when the media device is expected to be working but no data is received.
     */
    kMediaDeviceStateRuntimeError = 3,
    /** 
     *@brief Device paused. Including: <br>
     *         + During screen capturing, the target application window is minimized in the taskbar. <br>
     *         + Before or during screen capturing, the target application window is hidden. <br>
     *         + During screen capturing, the target application window is being stretched. <br>
     *         + During screen capturing, the target application window is being dragged. <br>
     */
    kMediaDeviceStatePaused = 4,
    /** 
     *@brief Device resumed
     */
    kMediaDeviceStateResumed = 5,
    /** 
     *@brief Added
     */
    kMediaDeviceStateAdded = 10,
    /** 
     *@brief Removed
     */
    kMediaDeviceStateRemoved = 11,
    /** 
     * @brief Closing the laptop interrupted the RTC call. RTC call will resume once the laptop is opened.
     */
    kMediaDeviceInterruptionBegan = 12,
    /** 
     * @brief RTC call resumed from the interruption caused by Closing the laptop.
     */
    kMediaDeviceInterruptionEnded = 13,
    /** 
     * @brief The device just became the default device.
     */
    kMediaDeviceBecomeSystemDefault = 14,
    /** 
     * @brief The device is no longer the default device.
     */
    kMediaDeviceResignSystemDefault = 15
};

/** 
 * @type keytype
 * @brief  Media device error type
 */
enum MediaDeviceError {
    /** 
     *@brief Media equipment is normal
     */
    kMediaDeviceErrorOK = 0,
    /** 
     *@brief No permission to start media device
     */
    kMediaDeviceErrorDeviceNoPermission = 1,
    /** 
     *@brief Media devices are already in use
     */
    kMediaDeviceErrorDeviceBusy = 2,
    /** 
     *@brief Media device error
     */
    kMediaDeviceErrorDeviceFailure = 3,
    /** 
     *@brief The specified media device was not found
     */
    kMediaDeviceErrorDeviceNotFound = 4,
    /** 
     *@brief Media device, window or monitor removed
     */
    kMediaDeviceErrorDeviceDisconnected = 5,
    /** 
     * @brief Device has no data callback
     */
    kMediaDeviceErrorDeviceNoCallback = 6,
    /** 
     * @brief Device sample rate not supported
     */
    kMediaDeviceErrorDeviceUNSupportFormat = 7,
    /** 
     * @brief ios screen capture not find group id parameter
     */
    kMediaDeviceErrorDeviceNotFindGroupId = 8,
};

/** 
 * @type keytype
 * @brief Media device warning
 */
enum MediaDeviceWarning {
    /** 
     * @brief No warning
     */
    kMediaDeviceWarningOK = 0,
    /** 
     * @brief Illegal device operation. Calls the API for internal device when using the external device.
     */
    kMediaDeviceWarningOperationDenied = 1,
    /** 
     * @brief No audio is captured.
     */
    kMediaDeviceWarningCaptureSilence = 2,
    /** 
     * @brief Silence warning by Android system.
     */
    kMediaDeviceWarningAndroidSysSilence = 3,
    /** 
     * @brief Silence disappearing warning by Android system.
     */
    kMediaDeviceWarningAndroidSysSilenceDisappear = 4,
    // The following warning codes are only valid for meeting scenarios.
    /** 
     * @hidden
     * @brief The volume is too loud and exceeds the acquisition range of the device. Lower the microphone volume or lower the volume of the audio source.
     */
    kMediaDeviceWarningDetectClipping = 10,
    /** 
     * @hidden
     * @brief Leaking echo detected.
     */
    kMediaDeviceWarningDetectLeakEcho = 11,
    /** 
     * @hidden
     * @brief Low SNR.
     */
    kMediaDeviceWarningDetectLowSNR = 12,
    /** 
     * @hidden
     * @brief Silence inserted during capture.
     */
    kMediaDeviceWarningDetectInsertSilence = 13,
    /** 
     * @hidden
     * @brief Silence during capture.
     */
    kMediaDeviceWarningCaptureDetectSilence = 14,
    /** 
     * @hidden
     * @brief Silence disappears during capture.
     */
    kMediaDeviceWarningCaptureDetectSilenceDisappear = 15,
    /** 
     * @hidden
     * @brief Howling
     */
    kMediaDeviceWarningCaptureDetectHowling = 16,
    /** 
     * @hidden
     * @brief result of api setAudioRoute callback, not support called to setAudioRoute in this scenario
     */
    kMediaDeviceWarningSetAudioRouteInvalidScenario = 20,
    /** 
     * @hidden
     * @brief result of api setAudioRoute callback, routing device not exists (Andorid)
     */
    kMediaDeviceWarningSetAudioRouteNotExists = 21,
    /** 
     * @hidden
     * @brief result of api setAudioRoute callback, failed by higher priority
     */
    kMediaDeviceWarningSetAudioRouteFailedByPriority = 22,
    /** 
     * @hidden
     * @brief result of api setAudioRoute callback, non voip mode will not be supported
     */
    kMediaDeviceWarningSetAudioRouteNotVoipMode = 23,
    /** 
     * @hidden
     * @brief result of api setAudioRoute callback, no any play or capture started
     */
    kMediaDeviceWarningSetAudioRouteDeviceNotStart = 24,
};

/** 
 * @type keytype
 * @brief Subscription status of media streams
 */
enum SubscribeState {
    /** 
     * @brief Successfully changed the subscription status
     */
    kSubscribeStateSuccess,
    /** 
     * @brief Failed to change the subscription status, because you were not in the room.
     */
    kSubscribeStateFailedNotInRoom,
    /** 
     * @brief Failed to change the subscription status, because the target audio/video stream was not found.
     */
    kSubscribeStateFailedStreamNotFound,
    /** 
     * @brief Failed to change the subscription status, because the number of streams you have subscribed to has exceeded the limit.
     */
    kSubscribeStateFailedOverLimit,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Subscription mode option. Before joining the room, the business side calls the enableAutoSubscribe{@link #IRTCRoom#enableAutoSubscribe} interface to set the subscription mode. <br>
 */
enum SubscribeMode {
    /** 
     * @brief Automatic subscription mode. The SDK  automatically subscribes to every stream in the room for you. <br>
     */
    kSubscribeModeAuto = 0,
    /** 
     * @brief Manual subscription mode. The SDK  does not automatically subscribe to audio & video streams in the room. You should call the subscribeUserStream{@link #IRTCRoom#subscribeUserStream} method to manually subscribe to audio & video streams published by other users as needed. <br>
     */
    kSubscribeModeManual = 1
};

/** 
 * @type keytype
 * @brief Priority of the publisher. When a user encounters performance insufficiency of either the network or the device, the media stream  will fall back in the ascending order of `RemoteUserPriority`.
 */
enum RemoteUserPriority {
    /** 
     * @brief Low, the default
     */
    kRemoteUserPriorityLow = 0,
    /** 
     * @brief Medium
     */
    kRemoteUserPriorityMedium = 100,
    /** 
     * @brief High
     */
    kRemoteUserPriorityHigh = 200,
};
/** 
 * @type keytype
 * @brief Stream fallback options of publisher
 */
enum PublishFallbackOption {
    /** 
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    kPublishFallbackOptionDisabled = 0,
    /** 
     * @brief Under limited network conditions, the video streams that you published will degrade sequentially from the highest-quality stream to the lowest-quality stream until it can match current network conditoins. 
     */
    kPublishFallbackOptionSimulcast = 1,
};
/** 
 * @type keytype
 * @brief Stream fallback options of subscriber
 */
enum SubscribeFallbackOption {
    /** 
     * @brief Default setting. No fallback is allowed under limited network conditions.
     */
    kSubscribeFallbackOptionDisable = 0,
    /** 
     * @brief The resolution of currently subscribed video stream will be reduced under limited network conditions.  <br>
     *        You can only select this setting after the stream publisher calls enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode}} to enable the mode of publishing multiple streams, otherwise no fallback will occur.
     */
    kSubscribeFallbackOptionVideoStreamLow = 1,
    /** 
     * @brief Receive audio only under poor network condition.
     */
    kSubscribeFallbackOptionAudioOnly = 2,
};

/** 
 * @type keytype
 * @brief Reason of the Fallback or reverting from a Fallback of the subscribed stream or the publishing stream
 */
enum FallbackOrRecoverReason {
    /** 
     * @brief The default: Fallback due to an unknown reason that is neither infufficienclt bandwidth of the network nor poor-performance of the device
     */
    kFallbackOrRecoverReasonUnknown = -1,
    /** 
     * @brief Fallback of the subscribed stream due to insufficient bandwidth of the network
     */
    kFallbackOrRecoverReasonSubscribeFallbackByBandwidth = 0,
    /** 
     * @brief Fallback of the subscribed stream for poor-performance of the device
     */
    kFallbackOrRecoverReasonSubscribeFallbackByPerformance = 1,
    /** 
     * @brief Reverting from a Fallback of the subscribed stream due to the recovery of the network bandwidth
     */
    kFallbackOrRecoverReasonSubscribeRecoverByBandwidth = 2,
    /** 
     * @brief Reverting from a Fallback of the subscribed stream due to the amelioration of the device performance
     */
    kFallbackOrRecoverReasonSubscribeRecoverByPerformance = 3,
    /** 
     * @brief Fallback of the publishing stream due to Insufficient bandwidth of the network
     */
    kFallbackOrRecoverReasonPublishFallbackByBandwidth = 4,
    /** 
     * @brief Fallback of the publishing stream due to poor-performance of the device
     */
    kFallbackOrRecoverReasonPublishFallbackByPerformance = 5,
    /** 
     * @brief Reverting from a Fallback of the publishing stream due to the recovery of the network bandwidth
     */
    kFallbackOrRecoverReasonPublishRecoverByBandwidth = 6,
    /** 
     * @brief Reverting from a Fallback of the publishing stream due to the amelioration of the device performance
     */
    kFallbackOrRecoverReasonPublishRecoverByPerformance = 7,
};

/** 
 * @type keytype
 * @brief Reasons of `onPerformanceAlarms` being triggered.
 */
enum PerformanceAlarmReason {
    /** 
     * @brief The poor network causes the transmission performance to fall back. This reason is only received when sending performance fallback is turned on.
     */
    kPerformanceAlarmReasonBandwidthFallbacked = 0,
    /** 
     * @brief Network performance recovery, transmission performance rollback recovery. This reason is only received when sending performance fallback is turned on.
     */
    kPerformanceAlarmReasonBandwidthResumed = 1,
    /** 
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance is insufficient; <br>
     *        If the send performance fallback is turned on, when receiving this alarm, it means that the performance is insufficient and the send performance fallback has occurred.
     */
    kPerformanceAlarmReasonPerformanceFallbacked = 2,
    /** 
     * @brief If the send performance fallback is not turned on, when receiving this alarm, it means that the performance shortage has been restored; <br>
     *         If the send performance fallback is turned on, when receiving this alarm, it means that the performance shortage has been restored and the send performance fallback has occurred. Recovery.
     */
    kPerformanceAlarmReasonPerformanceResumed = 3,
};

/** 
 * @type keytype
 * @brief  Whether to turn on release performance fallback
 */
enum PerformanceAlarmMode {
    /** 
     * @brief Not enabled Release performance fallback
     */
    kPerformanceAlarmModeNormal = 0,
    /** 
     * @brief Open Release Performance Rollback
     */
    kPerformanceAlarmModeSimulcast = 1,
};

/** 
 * @type errorcode
 * @brief Callback error code.   <br>
 *        When an unrecoverable error is encountered inside the SDK, the user is notified via the `onError` callback.
 */
enum ErrorCode {
    /** 
     * @brief Token  is invalid.
     *        The Token used when joining the room is invalid or expired. The user is required to retrieve the token and call the `updateToken` to update the token.
     */
    kErrorCodeInvalidToken = -1000,
    /** 
     * @brief Join room error.
     *        An unknown error occurred while joining the room, which caused the joining room to fail. Users are required to rejoin the room.
     */
    kErrorCodeJoinRoom = -1001,
    /** 
     * @brief No permission to publish audio & video streams.
     *        The user failed to publish the audio & video stream in the room. The reason for the failure is that the user does not have permission to publish the stream.
     */
    kErrorCodeNoPublishPermission = -1002,
    /** 
     * @brief No subscription permissions for audio & video streams.
     *        The user failed to subscribe to the audio & video stream in the room where the user is located. The reason for the failure is that the user does not have permission to subscribe to the stream.
     */
    kErrorCodeNoSubscribePermission = -1003,
    /** 
     * @brief The user has been removed from the room because the same user joined the room on the other client.
     */
    kErrorCodeDuplicateLogin = -1004,
    /** 
     * @brief The user has been removed from the room by the administrator via a OpenAPI call.
     */
    kErrorCodeKickedOut = -1006,
    /** 
     * @brief When calling `createRTCRoom`, if the roomid is illegal, it will return null and throw the error
     */
    kRoomErrorCodeRoomIdIllegal = -1007,
    /** 
     * @brief Token expired. Call `joinRoom` to rejoin with a valid Token.
     */
    kRoomErrorTokenExpired = -1009,
    /** 
     * @brief The Token you provided when calling `updateToken` is invalid.
     */
    kRoomErrorUpdateTokenWithInvalidToken = -1010,
    /** 
     * @brief Users have been removed from the room because the administrator dismissed the room by calling OpenAPI.
     */
    kErrorCodeRoomDismiss = -1011,
    /** 
     * @brief Join room error. <br>
     *        The LICENSE billing account does not use the LICENSE_AUTHENTICATE SDK while calling the joinRoom{@link #IRtcEngine#joinRoom} method, which caused the joining room to fail.
     */
    kErrorCodeJoinRoomWithoutLicenseAuthenticateSDK = -1012,
    /** 
     * @brief there is a room with the same roomId，whose room id is the same with echo test
     */
    kErrorCodeRoomAlreadyExist = -1013,
    /** 
     * @brief Subscription to audio & video stream failed, the total number of subscribed audio & video streams exceeded the upper limit.
     *        In the game scenario, in order to ensure the performance and quality of audio & video calls, the server will limit the total number of audio & video streams subscribed by the user. When the total number of audio & video streams subscribed by the user has reached the maximum, continuing to subscribe to more streams will fail, and the user will receive this error notification.
     */
    kErrorCodeOverStreamSubscribeLimit = -1070,
    /** 
     * @brief Publishing flow failed, the total number of publishing flows exceeds the upper limit. The
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    kErrorCodeOverStreamPublishLimit = -1080,
    /** 
     * @brief Publishing the screen stream failed, and the total number of publishing streams exceeded the upper limit. The
     *        RTC system limits the total number of streams published in a single room, including video streams, audio streams, and screen streams. Local users will fail to publish streams to the room when the maximum number of published streams in the room has been reached, and will receive this error notification.
     */
    kErrorCodeOverScreenPublishLimit = -1081,
    /** 
     * @brief The total number of published video streams exceeds the upper limit.
     *        The RTC system limits the number of video streams posted in a single room. If the maximum number of video streams posted in the room has been reached, local users will fail to post video streams to the room again and will receive this error notification.
     */
    kErrorCodeOverVideoPublishLimit = -1082,
    /** 
     * @brief A/V synchronization failed.  <br>
     *        Current source audio ID has been set by other video publishers in the same room.  <br>
     *        One single audio source cannot be synchronized with multiple video sources at the same time.
     */
    kErrorCodeInvalidAudioSyncUidRepeated = -1083,
};

/** 
 * @type errorcode
 * @brief  Callback warning code. The warning code indicates that there is a problem within the SDK and is trying to recover. Warning codes only serve as notifications.
 */
enum WarningCode {
    /**
     * @hidden
     */
    kWarningCodeGetRoomFailed = -2000,
    /** 
     * @brief Failed to enter the room.   <br>
     *        When you call the first time to join the room or disconnect and reconnect due to poor network conditions, the room entry fails due to a server error. The SDK automatically retries the room.
     */
    kWarningCodeJoinRoomFailed = -2001,
    /** 
     * @brief Release audio & video stream failed.   <br>
     *        When you publish audio & video streams in your room, the publication fails due to a server error. The SDK automatically retries the release.
     */
    kWarningCodePublishStreamFailed = -2002,
    /** 
     * @brief Subscription to audio & video stream failed.   <br>
     *         The subscription failed because the audio & video stream for the subscription could not be found in the current room. The SDK will automatically retry the subscription. If the subscription fails, it is recommended that you exit the retry.
     */
    kWarningCodeSubscribeStreamFailed404 = -2003,
    /** 
     * @brief Subscription to audio & video stream failed.   <br>
     *        When you subscribe to audio & video streams in your room, the subscription fails due to a server error. The SDK automatically retries the subscription.
     */
    kWarningCodeSubscribeStreamFailed5xx = -2004,
    /** 
     * @hidden
     * @brief  The function call order is wrong.
     */
    kWarningCodeInvokeError = -2005,
    /** 
     * @hidden
     * @brief Scheduling exception, the media server address returned by the server is unavailable.
     */
    kWarningCodeInvalidExpectMediaServerAddress = -2007,
    /** 
     * @brief This warning is triggered when you call `setUserVisibility` to set yourself unvisible to others and then try to publish the flow. <br>
     */
    kWarningCodePublishStreamForbiden = -2009,
    /** 
     * @hidden
     * @brief When automatic subscription mode is not turned off, trying to turn on manual subscription mode will trigger this warning.   <br>
     *        You need to call the enableAutoSubscribe{@link #IRTCRoom#enableAutoSubscribe} method to turn off the automatic subscription mode before entering the room, and then call the subscribeStream{@link #IRTCRoom#subscribeStream} method to manually subscribe to the audio & video stream.
     */
    kWarningCodeSubscribeStreamForbiden = -2010,
    /** 
     * @brief Sending a custom broadcast message failed, you are not currently in the room.
     */
    kWarningCodeSendCustomMessage = -2011,
    /** 
     * @brief When the number of people in the room exceeds 500, stop sending `onUserJoined` and `onUserLeave` callbacks to existing users in the room, and prompt all users in the room via broadcast.
     */
    kWarningCodeUserNotifyStop = -2013,

    /** 
     * @brief user had published in other room or had published public stream.
     */
    kWarningCodeUserInPublish = -2014,

    /** 
     * @brief The old room has been replaced by new room with the same roomId
     */
    kWarningCodeOldRoomBeenReplaced = -2016,

    /** 
     * @brief this inteface has been banned for the engine is in echo testing mode
     */
    kWarningCodeInEchoTestMode = -2017,

    /** 
     * @brief The camera permission is abnormal, and the current application does not obtain the camera permission.
     */
    kWarningCodeNoCameraPermission = -5001,
    /** 
     * @brief The microphone permission is abnormal, and the current application does not obtain microphone permission.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeNoMicrophonePermission = -5002,
   /** 
     * @brief The audio capture device failed to start, and the current device may be occupied by other applications.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeRecodingDeviceStartFailed = -5003,
    /** 
     * @brief The audio playback device failed to start warning, which may be due to insufficient system resources or wrong parameters.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodePlayoutDeviceStartFailed = -5004,
    /** 
     * @brief No audio acquisition device is available, please insert the available audio acquisition device.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeNoRecordingDevice = -5005,
    /** 
     * @brief No audio playback device is available, please insert an available audio playback device.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeNoPlayoutDevice = -5006,
    /** 
     * @brief The current audio equipment has not collected valid sound data, please check and replace the audio acquisition equipment.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeRecordingSilence = -5007,
    /** 
     * @brief Media device misoperation warning.   <br>
     *        When using custom acquisition, the internal acquisition switch cannot be called, and this warning will be triggered when called.
     * @deprecated since 333.1, use MediaDeviceWarning instead
     */
    kWarningCodeMediaDeviceOperationDenied = -5008,

    /** 
     * @brief Setting the screen audio capture type with `setScreenAudioSourceType` after calling `publishScreen` is not supported, please set before `publishScreen`.
     */
    kWarningCodeSetScreenAudioSourceTypeFailed = -5009,

    /** 
     * @brief Setting the audio capture method for screen sharing via `setScreenAudioStreamIndex` after calling `publishScreen` is not supported.
     */
    kWarningCodeSetScreenAudioStreamIndexFailed = -5010,
    /** 
     * @brief Invalid pitch value setting
     */
    kWarningCodeInvalidVoicePitch = -5011,
    /** 
     * @brief Invalid audio format setting
     */
    kWarningCodeInvalidAudioFormat = -5012,
    /** 
     * @brief Mixed use of old and new interfaces for external audio sources
     */
    kWarningCodeInvalidCallForExtAudio = -5013,
    /** 
     * @brief The specified internal rendering canvas handle is invalid.   <br>
     *        This callback is triggered when you specify an invalid canvas handle when you call setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas}.
     */
    kWarningCodeInvalidCanvasHandle = -6001,
    /** 
     * @brief The authentication file is invalid. When checking the status of the authentication file, if the local file is inconsistent with the remote file, a
     *        second warning will be triggered.   <br>
     */
    kWarningLicenseFileExpired = -7001
};

/** 
 * @type keytype
 * @brief  Business check code   <br>
 *         The error code that the API `setBusinessId` sends back. <br>
 */
enum BusinessCheckCode {
    /** 
     * @brief The user is already in the room.   <br>
     *        You must set the Business Id before joining room, otherwise it will be invalid. <br>
     */
    ERROR_ALREADY_IN_ROOM = -6001,

    /** 
     * @brief  The input is invalid.   <br>
     *         For the legal characters, see `setBusinessId`. <br>
     */
    ERROR_INPUT_INVALIDATE = -6002,
};

/** 
 * @type keytype
 * @brief  Local audio stream status.
 *        SDK callbacks local audio stream status via `onLocalAudioStateChanged`
 */
enum LocalAudioStreamState {
    /** 
     * @brief The default initial state of the local audio.
     *         Callback to this state when the microphone stops working, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateStopped = 0,

    /** 
     * @brief The local audio recording device started successfully.
     *         Callback to the state when the first frame of audio is collected, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateRecording,

    /** 
     * @brief The first frame of the local audio was successfully encoded.
     *         Callback to the state when the audio first frame encoding is successful, corresponding to the error code kLocalAudioStreamErrorOk
     */
    kLocalAudioStreamStateEncoding,

    /** 
     * @brief  The local audio startup failed, and the status is called back at the following times:   <br>
     *        + The local recording device failed to start, corresponding to the error code kLocalAudioStreamErrorRecordFailure <br>
     *        + No recording device permission was detected, corresponding to the error code kLocalAudioStreamErrorDeviceNoPermission <br>
     *        + The audio encoding failed, corresponding to the error code kLocalAudioStreamErrorEncodeFailure
     *  <br>
     */
    kLocalAudioStreamStateFailed,

    /** 
     * @brief Callback the state after the local audio is successfully muted.
     *         Callback after successful setAudioCaptureDeviceMute{@link #IAudioDeviceManager-setaudiocapturedevicemute} call, corresponding to kLocalAudioStreamErrorOk in the error code LocalAudioStreamError{@link #LocalAudioStreamError}. <br>
     */
    kLocalAudioStreamMute,

    /** 
     * @brief Callback the state after the local audio is successfully unmuted.
     *         Callback after successful setAudioCaptureDeviceMute{@link #IAudioDeviceManager-setaudiocapturedevicemute} call, corresponding to kLocalAudioStreamErrorOk in the error code LocalAudioStreamError{@link #LocalAudioStreamError}. <br>
     */
    kLocalAudioStreamUnmute
};

/** 
 * @type keytype
 * @brief Error code when the state of the local audio stream changes. The
 *        SDK calls back the error code via `onLocalAudioStateChanged`.
 */
enum LocalAudioStreamError {
    /** 
     * @brief Local audio status is normal
     */
    kLocalAudioStreamErrorOk = 0,
    /** 
     * @brief Local audio error cause unknown
     */
    kLocalAudioStreamErrorFailure,
    /** 
     * @brief No permission to start local audio recording device
     */
    kLocalAudioStreamErrorDeviceNoPermission,
    /** 
     * @brief The local audio recording device is already in use
     * @notes The error code is not yet in use
     */
    kLocalAudioStreamErrorDeviceBusy,
    /** 
     * @brief Local audio recording failed, it is recommended that you check whether the recording device is working properly
     */
    kLocalAudioStreamErrorRecordFailure,
    /** 
     * @brief Local audio encoding failed
     */
    kLocalAudioStreamErrorEncodeFailure,
    /** 
     *@brief No audio recording equipment available
     */
    kLocalAudioStreamErrorNoRecordingDevice
};

/** 
 * @type keytype
 * @brief  Local video stream status
 */
enum LocalVideoStreamState {
    /** 
     * @brief Local video capture stop state
     */
    kLocalVideoStreamStateStopped = 0,
    /** 
     * @brief Local video capture device activated
     */
    kLocalVideoStreamStateRecording,
    /** 
     * @brief After local video capture, the first frame is encoded successfully
     */
    kLocalVideoStreamStateEncoding,
    /** 
     * @brief Local video capture device failed to start
     */
    kLocalVideoStreamStateFailed,
};

/** 
 * @type errorcode
 * @brief Error code when the local video state changes
 */
enum LocalVideoStreamError {
    /** 
     * @brief Normal condition
     */
    kLocalVideoStreamErrorOk = 0,
    /** 
     * @brief Local video stream publishing failed
     */
    kLocalVideoStreamErrorFailure,
    /** 
     * @brief No access to the local video capture device
     */
    kLocalVideoStreamErrorDeviceNoPermission,
    /** 
     * @brief Local video capture equipment is occupied
     */
    kLocalVideoStreamErrorDeviceBusy,
    /** 
     * @brief Local video capture device does not exist
     */
    kLocalVideoStreamErrorDeviceNotFound,
    /** 
     * @brief Local video capture failed, it is recommended to check whether the acquisition device is working properly
     */
    kLocalVideoStreamErrorCaptureFailure,
    /** 
     * @brief Local video encoding failed
     */
    kLocalVideoStreamErrorEncodeFailure,
    /** 
     * @brief Local video capture device removed
     */
    kLocalVideoStreamErrorDeviceDisconnected
};

/** 
 * @type keytype
 * @brief  Remote audio stream state. <br>
 *         Users can learn about this status through `onRemoteAudioStateChanged`.
 */
enum RemoteAudioState {
    /** 
     * @brief  The remote audio stream is not received.  <br>
     *          The callback `onRemoteAudioStateChanged` triggers: <br>
     *        + Local users stop receiving remote audio streams due to kRemoteAudioStateChangeReasonLocalMuted {@link
     *  #RemoteAudioStateChangeReason} <br>
     *        + The remote user stops sending audio streams due to kRemoteAudioStateChangeReasonRemoteMuted {@link
     *  #RemoteAudioStateChangeReason} <br>
     *        + The remote user left the room, the corresponding reason is: kRemoteAudioStateChangeReasonRemoteOffline {@link
     *  #RemoteAudioStateChangeReason} <br>
     */
    kRemoteAudioStateStopped = 0,
    /** 
     * @brief Start receiving the remote audio stream header. <br>
     *        Just received the remote audio stream header will trigger a callback `onRemoteAudioStateChanged`,
     *         The corresponding reason is: RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason} in "kRemoteAudioStateChangeReasonLocalUnmuted"
     */
    kRemoteAudioStateStarting,
    /** 
     * @brief  The remote audio stream is decoding and playing normally.  <br>
     *          A callback is triggered in the following cases: `onRemoteAudioStateChanged`: <br>
     *        + The remote audio first frame was successfully decoded, and the corresponding reason is: 'kRemoteAudioStateChangeReasonLocalUnmuted' in RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}  <br>
     *        + The network returned to normal from blocking, and the corresponding reason is: "kRemoteAudioStateChangeReasonNetworkRecovery ' in RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}  <br>
     *        + Local users resume receiving remote audio streams, and the corresponding reason is 'kRemoteAudioStateChangeReasonLocalUnmuted ' RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason} <br>
     *        + Remote users resume sending audio streams, and the corresponding reason is 'kRemoteAudioStateChangeReasonRemoteUnmuted' in RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    kRemoteAudioStateDecoding,
    /** 
     * @brief Remote audio streaming card. <br>
     *         A callback is triggered when the network is blocked and the packet loss rate is greater than 40%. `onRemoteAudioStateChanged`,
     *         The corresponding reason is: "kRemoteAudioStateChangeReasonNetworkCongestion" in RemoteAudioStateChangeReasonNetworkCongestion} {@link #RemoteAudioStateChangeReasonNetworkCongestion}
     */
    kRemoteAudioStateFrozen,
    /** 
     * @hidden
     * @brief  The remote audio stream failed to play
     * @notes  The error code is not yet used
     */
    kRemoteAudioStateFailed,
};

/** 
 * @type keytype
 * @brief  Receives the cause of the remote audio stream state change.   <br>
 *        Users can learn about this reason through `onRemoteAudioStateChanged`.
 */
enum RemoteAudioStateChangeReason {
    /** 
     * @brief Internal reasons
     */
    kRemoteAudioStateChangeReasonInternal = 0,
    /** 
     * @brief Network blocking
     */
    kRemoteAudioStateChangeReasonNetworkCongestion,
    /** 
     * @brief Network back to normal
     */
    kRemoteAudioStateChangeReasonNetworkRecovery,
    /** 
     * @brief Local user stops receiving remote audio stream
     */
    kRemoteAudioStateChangeReasonLocalMuted,
    /** 
     * @brief Local users resume receiving remote audio streams
     */
    kRemoteAudioStateChangeReasonLocalUnmuted,
    /** 
     * @brief Remote user stops sending audio stream
     */
    kRemoteAudioStateChangeReasonRemoteMuted,
    /** 
     * @brief Remote user resumes sending audio stream
     */
    kRemoteAudioStateChangeReasonRemoteUnmuted,
    /** 
     * @brief Remote user leaves room
     */
    kRemoteAudioStateChangeReasonRemoteOffline,
};

/** 
 * @type keytype
 * @brief  Remote video stream status. You will receive `onRemoteVideoStateChanged` callback when the state changes.
 */
enum RemoteVideoState {
    /** 
     * @brief The remote video stream defaults to the initial state, and the video has not yet started playing.
     */
    kRemoteVideoStateStopped = 0,
    /** 
     * @brief Local user has received remote video stream header packet.
     */
    kRemoteVideoStateStarting,
    /** 
     * @brief The remote video stream is decoding and playing normally.
     */
    kRemoteVideoStateDecoding,
    /** 
     * @brief Remote video streaming card, there may be network and other reasons.
     */
    kRemoteVideoStateFrozen,
    /** 
     * @brief The remote video stream failed to play.
     */
    kRemoteVideoStateFailed,
};

/** 
 * @type keytype
 * @brief  Cause of remote video stream state change
 */
enum RemoteVideoStateChangeReason {
    /** 
     * @brief Internal reasons
     */
    kRemoteVideoStateChangeReasonInternal = 0,
    /** 
     * @brief Network blocking
     */
    kRemoteVideoStateChangeReasonNetworkCongestion,
    /** 
     * @brief Network back to normal
     */
    kRemoteVideoStateChangeReasonNetworkRecovery,
    /** 
     * @brief Local user stops receiving remote video stream or local user disables video module
     */
    kRemoteVideoStateChangeReasonLocalMuted,
    /** 
     * @brief Local user resumes receiving remote video streams or local user enables video modules
     */
    kRemoteVideoStateChangeReasonLocalUnmuted,
    /** 
     * @brief The remote user stops sending the video stream or the remote user disables the video module
     */
    kRemoteVideoStateChangeReasonRemoteMuted,
    /** 
     * @brief Remote user resumes sending video stream or remote user enables video module
     */
    kRemoteVideoStateChangeReasonRemoteUnmuted,
    /** 
     * @brief The remote user leaves the channel. State transition see `onUserUnPublishStream`.
     */
    kRemoteVideoStateChangeReasonRemoteOffline,
};

/** 
 * @hidden
 * @type keytype
 * @brief State of the black frame video stream
 */
enum SEIStreamEventType {
    /** 
     * @brief A black frame video stream is published from the remote user.  <br>
     *        In a voice call, when the remote user calls sendSEIMessage{@link #IRTCVideo#sendSEIMessage} to send SEI data, SDK will automatically publish a black frame video stream, and trigger this callback.
     */
    kSEIStreamEventTypeStreamAdd = 0,
    /** 
     * @brief The black frame video stream is removed. The timing this callback will be triggered is as following:  <br>
     *        + The remote user turns on their camera, switching from a voice call to a video call.  <br>
     *        + No SEI data is sent within 1min after the remote user calls sendSEIMessage{@link #IRTCVideo#sendSEIMessage}.  <br>
     *        + The remote user calls setVideoSourceType{@link #IRTCVideo#setVideoSourceType} to switch to custom video capture.
     */
    kSEIStreamEventTypeStreamRemove,
};

/** 
 * @type keytype
 * @brief  Performance fallback related data
 */
struct SourceWantedData {
    /** 
     * @brief  <br>
     * When the release rollback is not turned on, this value represents the recommended video input width. When the rollback mode is the large and small stream mode, it represents the maximum width of the current push stream
     * @brief If the send performance rollback is not turned on, this value represents the recommended Video input width;   <br>
     *        If the send performance rollback is turned on, this value represents the maximum width of the current push stream.
     */
    int width;
    /** 
     * @brief If send performance fallback is not turned on, this value represents the recommended video input height; <br>
     *         If send performance fallback is turned on, this value represents the maximum height of the current push stream.
     */
    int height;
    /** 
     * @brief If send performance fallback is not turned on, this value represents the recommended video input frame rate in fps; <br>
     *         If send performance fallback is turned on, this value represents the maximum frame rate of the current push stream in fps.
     */
    int frame_rate;
};

/** 
 * @type keytype
 * @brief  User information
 */
struct UserInfo {
    /** 
     * @brief User ID. The string matches the regular expression: `[a-zA-Z0-9_@\-]{1,128}`.
     */
    const char* uid = nullptr;
    /** 
     * @brief Additional information of the user. The maximum length is 200 bytes. The remote user will receive the info in `onUserJoined`.
     */
    const char* extra_info = nullptr;
};

/** 
 * @type keytype
 * @brief  Call related statistics
 */
struct RtcRoomStats {
    /** 
     * @brief Current Tx packet loss rate. The range is [0,1].
     */
    float txLostrate;
    /** 
     * @brief Current Rx packet loss rate. The range is [0,1].
     */
    float rxLostrate;
    /** 
     * @brief Round-trip time (in ms) from client side to server side
     */
    int rtt;
    /** 
     * @brief Cumulative time between the user joining the room and leaving the room in seconds.
     */
    unsigned int duration;
    /** 
     * @brief Cumulative data sent by the user in bytes.
     */
    unsigned int tx_bytes;
    /** 
     * @brief Cumulative data received by the user in bytes.
     */
    unsigned int rx_bytes;
    /** 
     * @brief The instantaneous value of Tx bitrate in kbps
     */
    unsigned short tx_kbitrate;
    /** 
     * @brief The instantaneous value of Rx bitrate in kbps
     */
    unsigned short rx_kbitrate;
    /** 
     * @brief The instantaneous value of audio Rx bitrate in kbps
     */
    unsigned short rx_audio_kbitrate;
    /** 
     * @brief The instantaneous value of audio Tx bitrate in kbps
     */
    unsigned short tx_audio_kbitrate;
    /** 
     * @brief The instantaneous value of video Rx bitrate in kbps
     */
    unsigned short rx_video_kbitrate;
    /** 
     * @brief The instantaneous value of video Tx bitrate in kbps
     */
    unsigned short tx_video_kbitrate;
    /** 
     * @brief The instantaneous RX bitrate of screen-sharing video in Kbps
     */
    unsigned short rx_screen_kbitrate;
    /** 
     * @brief The instantaneous TX bitrate of screen-sharing video in Kbps
     */
    unsigned short tx_screen_kbitrate;
    /** 
     * @brief Number of visible users in the current room
     */
    unsigned int user_count;
    /** 
     * @brief CPU usage (%) of the application
     */
    double cpu_app_usage;
    /** 
     * @hidden
     * @brief Current CPU usage (%)
     */
    double cpu_total_usage;
    /** 
     * @brief Tx jitter(ms)
     */
    int tx_jitter;
    /** 
     * @brief Rx jitter(ms)
     */
    int rx_jitter;
    /** 
     * @brief Cellular Link Send bit rate  (kbps), get the instantaneous value of the data
     */
    unsigned short tx_cellular_kbitrate;
    /** 
     * @brief Cellular Link Receive bit rate  (kbps), get the instantaneous value of the data
     */
    unsigned short rx_cellular_kbitrate;
};

/** 
 * @type keytype
 * @brief Video encoding type
 */
enum VideoCodecType {
    /** 
     * @hidden
     * @brief  Unknown type
     */
    kVideoCodecTypeUnknown = 0,
    /** 
     * @brief Standard H264 encoder
     */
    kVideoCodecTypeH264 = 1,
    /** 
     * @brief Standard ByteVC1 encoder
     */
    kVideoCodecTypeByteVC1 = 2,
};

/** 
 * @type keytype
 * @brief Local audio stream statistics, reference period 2s. <br>
 *         After the local user publishes the audio stream successfully, the SDK will periodically notify the user through `onLocalStreamStats`
 *         The transmission status of the published audio stream during this reference period. This data structure is the type of parameter that is called back to the user. <br>
 */
struct LocalAudioStats {
    /** 
     * @brief Audio packet loss rate. The audio uplink packet loss rate in this reference period is % and the value range is [0,1]. <br>
     */
    float audio_loss_rate;
    /** 
     * @brief Send rate. The audio transmission rate in the reference period is kbps. <br>
     */
    int send_kbitrate;
    /** 
     * @brief Acquisition sampling rate. Audio sampling rate information collected in the reference period, in units of Hz. <br>
     */
    int record_sample_rate;
    /** 
     * @brief Statistical interval. The interval of this reference period is in ms. <br>
     * @notes  This field is used to set the reference period for the callback. The default setting is 2s.
     */
    int stats_interval;
    /** 
     * @brief Round-trip time. The unit is ms. <br>
     */
    int rtt;
    /** 
     * @brief Number of audio channels.   <br>
     */
    int num_channels;
    /** 
     * @brief Audio transmission sampling rate. Audio transmission sampling rate information in the reference period, in Hz. <br>
     */
    int sent_sample_rate;
    /** 
     * @brief Audio uplink network jitter in ms. <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *         After a local user subscribes to a remote audio stream successfully, the SDK periodically notifies the local user of the reception status of the subscribed audio stream during this reference period through `onRemoteStreamStats`. This data structure is the type of parameter that is called back to the local user. <br>
 */
struct RemoteAudioStats {
    /** 
     * @brief Audio packet loss rate. The audio downlink packet loss rate in the reference period, the value range is  [0,1]. <br>
     */
    float audio_loss_rate;
    /** 
     * @brief Receiving bit rate. The audio reception rate in the reference period in kbps. <br>
     */
    int received_kbitrate;
    /** 
     * @brief Number of audio cards. Number of cards in the reference period.   <br>
     */
    int stall_count;
    /** 
     * @brief Audio Catton Duration. Catton duration in the reference period in ms. <br>
     */
    int stall_duration;
    /** 
     *@brief End-to-end latency at the user experience level. The delay from the start of encoding at the sending end to the start of decoding at the receiving end, in units of ms. <br>
     */
    long e2e_delay;
    /** 
     * @brief Play sample rate. Audio playback sample rate information within the reference period in Hz. <br>
     */
    int playout_sample_rate;
    /** 
     * @brief Statistical interval. The interval of this reference period is in ms. <br>
     */
    int stats_interval;
    /** 
     * @brief Round-trip time for client side to server level data transfer in ms. <br>
     */
    int rtt;
    /** 
     * @brief The sender-server level-the receiver-link data transmission round-trip time. The unit is ms. <br>
     */
    int total_rtt;
    /** 
     * @brief The quality of the audio stream sent by the remote user. Value meaning reference NetworkQuality{@link #NetworkQuality}. <br>
     */
    int quality;
    /** 
     * @brief The delay caused by the introduction of the jitter buffer mechanism. The unit is ms. <br>
     */
    int jitter_buffer_delay;
    /** 
     * @brief Number of audio channels.   <br>
     */
    int num_channels;
    /** 
     * @brief Audio reception sampling rate. Remote audio sampling rate information received within the reference period, in Hz. <br>
     */
    int received_sample_rate;
    /** 
     * @brief The accumulated length of the audio card occurs after the remote user joins the room as a percentage of the total effective length of the audio. The effective duration of audio refers to the duration of audio other than stopping sending audio streams and disabling audio modules after remote users enter the room to publish audio streams.
     */
    int frozen_rate;
    /** 
     * @brief Audio packet loss compensation (PLC)  total number of sample points. <br>
     */
    int concealed_samples;
    /** 
     * @brief Audio packet loss compensation (PLC)  cumulative times. <br>
     */
    int concealment_event;
    /** 
     * @brief Audio decoding sample rate. Audio decoding sample rate information in the reference period in Hz. <br>
     */
    int dec_sample_rate;
    /** 
     * @brief Decoding duration. The total time-consuming decoding of the remote audio stream received within this reference period, in units of s. <br>
     */
    int dec_duration;
    /** 
     * @brief Audio downlink network jitter in ms. <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief Local video stream statistics, reference period 2s. <br>
 *        After a local user publishes a video stream successfully, the SDK will periodically notify the user through `onLocalStreamStats`
 *        The delivery status of the published video stream during this reference period. This data structure is the type of parameter that is called back to the user. <br>
 */
struct LocalVideoStats {
    /** 
     * @brief TX bitrate in Kbps of the video stream with the highest resolution within the reference period
     */
    int sent_kbitrate;
    /** 
     * @brief Sampling frame rate in fps of video capture during this reference period
     */
    int input_frame_rate;
    /** 
     * @brief TX frame rate in fps of the video stream with the highest resolution within the reference period
     */
    int sent_frame_rate;
    /** 
     * @brief Encoder-output frame rate in fps of the video stream with the highest resolution within the reference period
     */
    int encoder_output_frame_rate;
    /** 
     * @brief Local-rendering frame rate in fps during this reference period
     */
    int renderer_output_frame_rate;
    /** 
     * @brief Reference period in ms.
     *        This field is used to set the reference period for the callback, which is 2 s by default.
     */
    int stats_interval;
    /** 
     * @brief Video packet loss rate. The video uplink packet loss rate in this reference period ranges from  [0,1].
     */
    float video_loss_rate;
    /** 
     * @brief Round-trip time in ms.
     */
    int rtt;
    /** 
     * @brief Video encoding bitrate in Kbps of the video stream with the highest resolution within the reference period.
     */
    int encoded_bitrate;
    /** 
     * @brief Video encoding width in px of the video stream with the highest resolution within the reference period
     */
    int encoded_frame_width;
    /** 
     * @brief Video encoding height in px of the video stream with the highest resolution within the reference period
     */
    int encoded_frame_height;
    /** 
     * @brief The total number of the video stream with the highest resolution within the reference period sent in the reference period.
     */
    int encoded_frame_count;
    /** 
     * @brief For the encoding type of the video, please refer to VideoCodecType{@link #VideoCodecType}.
     */
    VideoCodecType codec_type;
    /** 
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
    /** 
     * @brief Video uplink network jitter in ms. <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief Remote audio stream statistics, reference period 2s. <br>
 *         After the local user subscribes to the remote audio stream successfully, the SDK will periodically notify the local user of the reception status of the remote video stream subscribed to during this reference period through `onRemoteStreamStats`
 *        . This data structure is the type of parameter that is called back to the local user. <br>
 */
struct RemoteVideoStats {
    /** 
     * @brief Video Width
     */
    int width;
    /** 
     * @brief Video height
     */
    int height;
    /** 
     * @brief Video packet loss rate. Video downlink packet loss rate in the reference period, in units of %, and in the range of [0,1].
     */
    float video_loss_rate;
    /** 
     * @brief Receiving bit rate. Video reception rate within the reference period, in kbps.
     */
    int received_kbitrate;
    /** 
     * @brief The decoder outputs the frame rate. Video decoder output frame rate within the reference period, in fps.
     */
    int decoder_output_frame_rate;
    /** 
     * @brief Render frame rate. The video rendering frame rate in the reference period, in fps.
     */
    int renderer_output_frame_rate;
    /** 
     * @brief Number of cards. Number of cards in the reference period.
     */
    int stall_count;
    /** 
     * @brief Catton duration. The total duration of the video card in the reference period. Unit ms.
     */
    int stall_duration;
    /** 
     * @brief End-to-end latency at the user experience level. The delay from the start of encoding at the sending end to the start of decoding at the receiving end, in units of ms.
     */
    long e2e_delay;
    /** 
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current data comes from mainstream or screen stream.
     */
    bool is_screen;
    /** 
     * @brief Statistical interval, the interval of this reference period, in ms. <br>
     * @notes  This field is used to set the reference period for the callback, currently set to 2s.
     */
    int stats_interval;
    /** 
     * @brief Round-trip time in ms.
     */
    int rtt;
    /** 
     * @brief The cumulative duration of the video card of the remote user accounts for the percentage (%) of the total effective duration of the video after entering the room. The effective duration of the video refers to the duration of the video other than stopping sending the video stream and disabling the video module after the remote user enters the room to publish the video stream.
     */
    int frozen_rate;
    /** 
     * @brief For subscripts of streams with multiple resolutions. See VideoSolutionDescription{@link #VideoSolutionDescription}
     */
    int video_index;
    /** 
     * @brief Video downlink network jitter in ms. <br>
     */
    int jitter;
};

/** 
 * @type keytype
 * @brief Local audio/video stream statistics and network status, the reference period is 2s. <br>
 *        After the local user publishes the audio/video stream successfully, the SDK will periodically notify the local user through `onLocalStreamStats`
 *        The transmission status of the published audio/video stream during this reference period. This data structure is the type of parameter that is called back to the user. <br>
 */
struct LocalStreamStats {
    /** 
     * @brief For statistics on audio streams sent by local devices. See LocalAudioStats{@link #LocalAudioStats}
     */
    LocalAudioStats audio_stats;
    /** 
     * @brief For statistics on video streams sent by local devices. See LocalVideoStats{@link #LocalVideoStats}
     */
    LocalVideoStats video_stats;
    /** 
     * @hidden
     * @brief For the media stream uplink network quality of the user you belong to. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 336.1, use onNetworkQuality{@link #onNetworkQuality} instead
     */
    NetworkQuality local_tx_quality;
    /** 
     * @hidden
     * @brief The downlink network quality of the media stream belongs to the user. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 336.1, use onNetworkQuality{@link #onNetworkQuality} instead
     */
    NetworkQuality local_rx_quality;
    /** 
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
};

/** 
 * @type keytype
 * @brief The remote audio/video stream statistics and network status subscribed by the user, with a reference period of 2s. <br>
 *         After the remote user subscribed to successfully publish the audio/video stream, the SDK will periodically notify local users through `onRemoteStreamStats`
 *         The reception status of the remote audio/video stream subscribed during this reference period. This data structure is the type of parameter that is called back to the local user. <br>
 */
struct RemoteStreamStats {
    /** 
     * @brief User ID. The remote user ID of the audio source. <br>
     */
    const char* uid;
    /** 
     * @brief For statistics on remote audio streams. See RemoteAudioStats{@link #RemoteAudioStats}
     */
    RemoteAudioStats audio_stats;
    /** 
     * @brief For statistics on remote video streams. See RemoteVideoStats{@link #RemoteVideoStats}
     */
    RemoteVideoStats video_stats;
    /** 
     * @hidden
     * @brief For the media stream uplink network quality of the user you belong to. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 336.1, use onNetworkQuality{@link #onNetworkQuality} instead
     */
    NetworkQuality remote_tx_quality;
    /** 
     * @hidden
     * @brief The downlink network quality of the media stream belongs to the user. See NetworkQuality{@link #NetworkQuality}
     * @deprecated since 336.1, use onNetworkQuality{@link #onNetworkQuality} instead
     */
    NetworkQuality remote_rx_quality;
    /** 
     * @brief Whether the media stream belongs to the user is a screen stream. You can know whether the current statistics come from mainstream or screen stream.
     */
    bool is_screen;
};

/** 
 * @type keytype
 * @brief  Audio & video quality feedback problem type
 */
enum ProblemFeedbackOption {
    /** 
     * @brief No problem
     */
    kProblemFeedbackOptionNone = 0,
    /** 
     * @brief Other issues
     */
    kProblemFeedbackOptionOtherMessage = (1 << 0),
    /** 
     * @brief Unclear voice
     */
    kProblemFeedbackOptionAudioNotClear = (1 << 1),
    /** 
     * @brief Video is not clear
     */
    kProblemFeedbackOptionVideoNotClear = (1 << 2),
    /** 
     * @brief Audio & video out of sync
     */
    kProblemFeedbackOptionNotSync = (1 << 3),
    /** 
     * @brief Audio card
     */
    kProblemFeedbackOptionAudioLagging = (1 << 4),
    /** 
     * @brief Video card
     */
    kProblemFeedbackOptionVideoLagging = (1 << 5),
    /** 
     * @brief Connection failed
     */
    kProblemFeedbackOptionDisconnected = (1 << 6),
    /** 
     * @brief No sound
     */
    kProblemFeedbackOptionNoAudio = (1 << 7),
    /** 
     * @brief No picture
     */
    kProblemFeedbackOptionNoVideo = (1 << 8),
    /** 
     * @brief Too little sound
     */
    kProblemFeedbackOptionAudioStrength = (1 << 9),
    /** 
     * @brief Echo noise
     */
    kProblemFeedbackOptionEcho = (1 << 10),
    /** 
     * @brief Large delay in earphone monitoring
     */
    KFeedbackOptionEarBackDelay = (1 << 11),
};

/** 
 * @type keytype
 * @brief The cpu and memory information used by App . <br>
 *         The information is periodically (2s) notified to the user by the SDK via `onSysStats` callback.
 */
struct SysStats {
    /** 
     * @brief Current system CPU cores
     */
    unsigned int cpu_cores;
    /** 
     * @brief The cpu usage rate of the current application, the value range is [0,1].
     */
    double cpu_app_usage;
    /** 
     * @brief The cpu usage rate of the current system, the value range is [0,1].
     */
    double cpu_total_usage;
    /** 
     * @brief The memory usage of the current application (in MB)
     */
    double memory_usage;
    /** 
     * @brief Full memory (in MB)
     */
    unsigned long long full_memory;
    /** 
     * @brief System used memory (in MB)
     */
    unsigned long long total_memory_usage;
    /** 
     * @brief Free allocable memory (in MB)
     */
    unsigned long long free_memory;
    /** 
     * @brief Memory usage of the current application (in %)
     */
    double memory_ratio;
    /** 
     * @brief System memory usage (in %)
     */
    double total_memory_ratio;
};

/** 
 * @type keytype
 * @brief  Custom encryption type   <br>
 */
enum EncryptType {
    /** 
     * @brief Built-in encryption is not used. Default value.
     */
    kEncryptTypeCustomize = 0,
    /** 
     * @brief AES-128-CBC  encryption algorithm <br>
     */
    kEncryptTypeAES128CBC = 1,
    /** 
     * @brief AES-256-CBC  encryption algorithm <br>
     */
    kEncryptTypeAES256CBC = 2,
    /** 
     * @brief AES-128-ECB  encryption algorithm <br>
     */
    kEncryptTypeAES128ECB = 3,
    /** 
     * @brief AES-256-ECB  encryption algorithm <br>
     */
    kEncryptTypeAES256ECB = 4
};

/** 
 * @type callback
 * @brief  Encryption/decryption handler
 */
class IEncryptHandler {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IEncryptHandler() {
    }
    /** 
     * @type api
     * @region  encryption
     * @brief  Custom encryption.   <br>
     *        Encrypts audio & video frame data before transmission using the custom encryption method set.
     * @param data Raw audio & video frame data
     * @param length Length of raw audio & video frame data
     * @param buf Encrypted data buffer available for writing
     * @param buf_len Size of encrypted data buffer available for writing
     * @return Encrypted data   <br>
     *         + ≥ 0: size of data actually written to the buffer after encryption <br>
     *         + 0: Discard the frame <br>
     * @notes  <br>
     *         + Before using this interface for custom encryption, you must first set the custom encryption method. See `setCustomizeEncryptHandler`.
     *         + Use onDecryptData{@link #onDecryptData} to decrypt encrypted audio & video frame data.
     *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
     */
    virtual unsigned int onEncryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;

    /** 
     * @type api
     * @region  encryption
     * @brief  Custom decryption.   <br>
     *         Decrypts custom encrypted audio & video frame data. For custom encryption. See onEncryptData{@link #IEncryptHandler#onEncryptData}.
     * @param data Raw audio & video frame data
     * @param length Length of raw audio & video frame data
     * @param buf Encrypted data buffer available for writing
     * @param buf_len Size of encrypted data buffer available for writing
     * @return Encrypted data   <br>
     *         + ≥ 0: size of data actually written to the buffer after encryption <br>
     *         + 0: Discard the frame <br>
     * @notes  <br>
     *         + Before using this interface to decrypt, you must first set the decryption method. See `setCustomizeEncryptHandler`.
     *         + The returned data size should be controlled within 90%~ 120% of the original data source, otherwise it will be discarded.
    */
    virtual unsigned int onDecryptData(
            const unsigned char* data, unsigned int length, unsigned char* buf, unsigned int buf_len) = 0;
};

/** 
 * @type keytype
 * @region  room management
 * @brief  User information
 */
struct RtcUser {
    /** 
     * User id
     */
    const char* user_id;
    /** 
     * Metadata
     */
    const char* meta_data;
};

/** 
 * @type keytype
 * @region  room management
 * @brief  First frame sending status
 */
enum FirstFrameSendState {
    /** 
     * @brief Sending
     */
    kFirstFrameSendStateSending = 0,
    /** 
     * @brief Sent successfully
     */
    kFirstFrameSendStateSent = 1,
    /** 
     * @brief Send failed
     */
    kFirstFrameSendStateEnd = 2,
};

/** 
 * @type keytype
 * @region  room management
 * @brief  First frame playback status
 */
enum FirstFramePlayState {
    /** 
     * @brief Playing
     */
    kFirstFramePlayStatePlaying = 0,
    /** 
     * @brief Play success
     */
    kFirstFramePlayStatePlayed = 1,
    /** 
     * @brief Play failed
     */
    kFirstFramePlayStateEnd = 2,
};

/** 
 * @type keytype
 * @brief Transmission/Playback state of the media stream
 */
enum MuteState {
    /** 
     * @brief Enable
     */
    kMuteStateOff = 0,
    /** 
     * @brief Disable
     */
    kMuteStateOn = 1,
};

/** 
 * @type keytype
 * @brief Stream type
 */
enum StreamIndex {
    /** 
     * @brief Mainstream, including: <br>
     *       + Video/audio captured by the the camera/microphone using internal capturing; <br>
     *       + Video/audio captured by custom method.
     */
    kStreamIndexMain = 0,
    /** 
     * @brief Screen-sharing stream. Video/Audio streams for screen sharing.
     */
    kStreamIndexScreen = 1,
};

/** 
 * @type keytype
 * @brief Information about the remote stream
 */
struct RemoteStreamKey {
   /** 
     * @brief The room ID of the media stream. <br>
     *        If the media stream is the stream forwarded by `startForwardStreamToRooms`, you must set the roomID to the room ID of the target room.
     */
    const char* room_id;
    /** 
     * @brief The ID of the user who published the stream.
     */
    const char* user_id;
    /** 
     * @brief Stream type. See StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
};

/** 
 * @type keytype
 * @brief HTTP/HTTPS  proxy status
 */
enum HttpProxyState {
    /** 
     * @brief HTTP/HTTPS  initialization state
     */
    kHttpInit,
    /** 
     * @brief HTTP/HTTPS  Connection successful
     */
    kHttpConnected,
    /** 
     * @brief HTTP/HTTPS  connection failed
     */
    kHttpError
};

/** 
 * @type keytype
 * @brief SOCKS5  proxy connection status
 */
enum Socks5ProxyState {
    /** 
     * @brief SOCKS5  connection initialization
     */
    kSocks5Init,
    /** 
     * @brief SOCKS5  Connection successful
     */
    kSocks5Connected,
    /** 
     * @brief SOCKS5  connection error
     */
    kSocks5Error,
    /** 
     * @brief TCP  connection failed
     */
    kSocks5TcpConnectFail,
    /** 
     * @brief TCP  connection closed
     */
    kSocks5TcpClose,
    /** 
     * @brief SOCKS  protocol TCP negotiation phase failed
     */
    kSocks5ProtocolTcpFail,
    /** 
     * @brief UDP  connection failed
     */
    kSocks5ProtocolUdpFail,
    /** 
     * @brief Authorization failed
     */
    kSocks5AuthFail,
    /** 
     * @brief Unknown state
     */
    kSocks5Unknown
};

/** 
 * @type keytype
 * @brief  Storage format of locally recorded files
 */
enum RecordingFileType {
    /** 
     * @brief Aac  format file
     */
    kRecordingFileTypeAAC = 0,
    /** 
     * @brief Mp4  format file
     */
    kRecordingFileTypeMP4 = 1,
};

/** 
 * @type keytype
 * @brief  Status of local recording
 */
enum RecordingState {
    /** 
     * @brief Recording exception
     */
    kRecordingStateError = 0,
    /** 
     * @brief Recording in progress
     */
    kRecordingStateProcessing = 1,
    /** 
     * @brief If the recording file is saved successfully, you will not receive the status code until you call `stopFileRecording` to end the recording.
     */
    kRecordingStateSuccess = 2,
};

/** 
 * @type keytype
 * @brief  Error code for local recording
 */
enum RecordingErrorCode {
    /** 
     * @brief Recording normal
     */
    kRecordingErrorCodeOk = 0,
    /** 
     * @brief No file write permissions
     */
    kRecordingErrorCodeNoPermission = -1,
    /** 
     * @brief The current version SDK does not support local recording, please contact technical support
     */
    kRecordingErrorCodeNotSupport = -2,
    /** 
     * @brief Other anomalies
     */
    kRecordingErrorCodeOther = -3,
};

/** 
 * @type keytype
 * @brief  Local recording progress
 */
struct RecordingProgress {
    /** 
     * @brief The cumulative recording time of the current file, in milliseconds
     */
    unsigned long long duration;
    /** 
     * @brief The size of the currently recorded file in bytes
     */
    unsigned long long file_size;
};

/** 
 * @type keytype
 * @brief  Details of local recording
 */
struct RecordingInfo {
    /** 
     * @brief The absolute path of the recorded file, including the file name and file suffix
     */
    const char* file_path;
    /** 
     * @brief For the video encoding type of the recorded file. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType video_codec_type;
    /** 
     * @brief The width of the recorded video, in pixels. Please ignore this field for audio-only recording
     */
    int width;
    /** 
     * @brief The height of the recorded video, the unit: pixels. Please ignore this field for audio-only recording
     */
    int height;
};

/** 
 * @type keytype
 * @brief  Local recording parameter configuration
 */
struct RecordingConfig {
    /** 
     * @brief The absolute path to save the recording file. You need to specify a legal path with read and write permissions.
     */
    const char* dir_path;
    /** 
     * @brief Recording stored file format. See RecordingFileType{@link #RecordingFileType}
     */
    RecordingFileType file_type;
};

/** 
 * @type keytype
 * @brief Define user functions for linux users   <br>
 */
enum UserWorkerType {
    /** 
     * @brief Normal user, no special attributes   <br>
     */
    UserWorkerNormal = 0,
    /** 
     * @brief User supports SIP flow, signaling only sends SIP flow   <br>
     */
    UserWorkerSupportSip = (1 << 0),
    /** 
     * @brief User supports bytevc1 to H264 transcoding of screen streams   <br>
     */
    UserWorkerByteVc1Transcoder = (1 << 1),
    /** 
     * @brief The user needs the signaling server to send a full number of user lists and callback functions   <br>
     */
    UserWorkerNeedUserListAndCb = (1 << 2),
    /** 
     * @brief The user needs to get relevant callbacks for all streams in the room when the room enters multiplayer mode   <br>
     */
    UserWorkerNeedStreamCallBack = (1 << 3),
};

/** 
 * @type keytype
 * @brief A/V synchronization states
 */
enum AVSyncState {
    /** 
     * @brief A/V synchronization begins.
     */
    kAVSyncStateAVStreamSyncBegin = 0,
    /** 
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    kAVSyncStateAudioStreamRemove,
    /** 
     * @brief The publisher stops publishing audio stream during the synchronization, which does not affect the sync relationship.
     */
    kAVSyncStateVdieoStreamRemove,
    /** 
     * @hidden
     * @brief subscriber settings synchronization  <br>
     */
    kAVSyncStateSetAVSyncStreamId,
};

/**
 * @hidden
 * @deprecated
 * @type keytype
 */
enum RtcRoomMode {
    kRtcRoomNormalMode = 0,
    kRtcRoomAudioSelectionMode = 1,
};

/** 
 * @type keytype
 * @brief  Stream type for media stream information synchronization
 */
enum SyncInfoStreamType {
    /** 
     * @brief Audio stream
     */
    kSyncInfoStreamTypeAudio = 0
};

/** 
 * @type keytype
 * @brief  Configuration related to media stream information synchronization
 */
struct StreamSycnInfoConfig {
    /** 
     * @brief Stream properties, mainstream or screen streams. See StreamIndex{@link #StreamIndex}
     */
    StreamIndex stream_index;
    /** 
     * @brief The number of duplicates sent by the message, the value range is  [0,25], it is recommended to set it to [3,5].
     */
    int repeat_count;
    /** 
     * @brief Stream types for media stream information synchronization. See SyncInfoStreamType{@link #SyncInfoStreamType}
     */
    SyncInfoStreamType stream_type;
};

/** 
 * @type keytype
 * @brief Information of the rooms where you want to relay the media stream to
 */
struct ForwardStreamInfo {
    /** 
     * @brief RoomId and UserId are required to generate the Token to forward media streams to the room.<br>
     *        During developing and testing, you can use temporary tokens generated on the console. At the production stage, Tokens are generated by the token generating application deployed on your server.<br>
     *        Forwarding will fail if the token is invalid.
     */
    const char* token;
    /** 
     * @brief ID of the room where the media stream aims to relay to
     */
    const char* room_id;
};

/** 
 * @type keytype
 * @brief Information of the rooms where you want to relay the media stream to
 */
struct ForwardStreamConfiguration {
    /** 
     * @brief Information of the rooms where you want to relay the media stream to
     */
    ForwardStreamInfo* forward_stream_dests = nullptr;
    /** 
     * @brief Number of the rooms where you want to relay the media stream<br>
     *        We recommend that the number is not higher than 4.
     */
    int dest_count = 0;
};

/** 
 * @type keytype
 * @brief The state of the relaying for each room
 */
enum ForwardStreamState {
    /** 
     * @brief Idle
     *        + States of all the rooms turns to idle after you call `stopForwardStreamToRooms`.
     *        + States of the rooms turns to idle that you call `updateForwardStreamToRooms` to remove.
     */
    kForwardStreamStateIdle = 0,
    /** 
     * @brief Start relaying.
     *        + State of the rooms turn to this state after the relaying starts sucessfully by calling `startForwardStreamToRooms`.
     *        + State of the rooms added by calling `updateForwardStreamToRooms` turn to this state after the relaying start sucessfully.
     */
    kForwardStreamStateSuccess = 1,
    /** 
     * @brief Relay fails. Refer to ForwardStreamError{@link #ForwardStreamError} for more information for more information.
     *        Once the relaying fails, state of the room turns to this state after calling `startForwardStreamToRooms` or `updateForwardStreamToRooms`.
     */
    kForwardStreamStateFailure = 2,
};

/** 
 * @type keytype
 * @brief Error codes during the relaying
 */
enum ForwardStreamError {
    /** 
     * @brief Normal
     */
    kForwardStreamErrorOK = 0,
    /** 
     * @brief Invalid argument
     */
    kForwardStreamErrorInvalidArgument = 1201,
    /** 
     * @brief Invalid token
     */
    kForwardStreamErrorInvalidToken = 1202,
    /** 
     * @brief Error returning from server
     */
    kForwardStreamErrorResponse = 1203,
    /** 
     * @brief Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     */
    kForwardStreamErrorRemoteKicked = 1204,
    /** 
     * @brief Server denies.
     */
    kForwardStreamErrorNotSupport = 1205,
};

/** 
 * @type keytype
 * @brief Events during the relaying
 */
enum ForwardStreamEvent {
    /** 
     * @brief Relaying pauses for the reason of network disconnecting.
     */
    kForwardStreamEventDisconnected = 0,
    /** 
     * @brief Relaying recovers from the disconnecting.
     */
    kForwardStreamEventConnected = 1,
    /**  Relaying aborts for the reason of that a User with the same user ID as that of the publisher joins.
     * @brief
     */
    kForwardStreamEventInterrupt = 2,
    /** 
     * @brief Target room list updates after you call `updateForwardStreamToRooms`.
     */
    kForwardStreamEventDstRoomUpdated = 3,
    /** 
     * @brief Wrong API-calling order. For example, call `updateForwardStreamToRooms` before calling `startForwardStreamToRooms`.
     */
    kForwardStreamEventUnExpectAPICall = 4,
};

/** 
 * @type keytype
 * @brief State and error for each room during relaying
 */
struct ForwardStreamStateInfo {
    /** 
     * @brief ID of the room where the media stream aims to relay to
     */
    const char* room_id;
    /** 
     * @brief State of the room during relaying. Refer to ForwardStreamState{@link #ForwardStreamState} for more information.
     */
    ForwardStreamState state;
    /** 
     * @brief Error code from the room during relaying. Refer to ForwardStreamError{@link #ForwardStreamError} for more information.
     */
    ForwardStreamError error;
};

/** 
 * @type keytype
 * @brief Event from each room during relaying
 */
struct ForwardStreamEventInfo {
    /** 
     * @brief ID of the room where the media stream aims to relay to
     *        An Empty string is for all rooms.
     */
    const char* room_id;
    /** 
     * @brief Event from the room during relaying. Refer to ForwardStreamEvent{@link #ForwardStreamEvent} for more information.
     */
    ForwardStreamEvent event;
};

/** 
 * @type keytype
 * @brief Watermark's scaled coordinates and size, relative to the video stream.
 */
struct ByteWatermark {
    /** 
     * @hidden
     */
    const char* url;
    /** 
     * @brief The watermark's horizontal offset from the upper left corner of the video stream to the video stream's width in range of [0,1).
     */
    float x;
    /** 
     * @brief The watermark's vertical offset from the upper left corner of the video stream to the video stream's height in range of [0,1).
     */
    float y;
    /** 
     * @brief The watermark's width to the video stream's width in range of [0,1).
     */
    float width;
    /** 
     * @brief The watermark height to the video stream's height in range of [0,1).
     */
    float height;
};

/** 
 * @type keytype
 * @brief Watermark configurations
 */
struct RTCWatermarkConfig {
    /** 
     * @type keytype
     * @brief Whether the watermark is visible in preview. Its default value is `true`.
     */
    bool visibleInPreview = true;
    /** 
     * @type keytype
     * @brief Watermark's coordinates and size in landscape mode. See ByteWatermark{@link #ByteWatermark}.
     */
    ByteWatermark positionInLandscapeMode;
    /** 
     * @type keytype
     * @brief Watermark's coordinates and size in portrait mode. See ByteWatermark{@link #ByteWatermark}.
     */
    ByteWatermark positionInPortraitMode;
};
/** 
 * @type keytype
 * @brief Cloud Proxy Information
 */
struct CloudProxyInfo {
    /** 
     * @type keytype
     * @brief Cloud proxy IP
     */
    const char* cloud_proxy_ip;
    /** 
     * @type keytype
     * @brief Cloud Proxy Port
     */
    int cloud_proxy_port;
};

/** 
 * @type keytype
 * @brief Configuration of Cloud Proxy
 */
struct CloudProxyConfiguration {
    /** 
     * @brief Information of cloud proxy.<br>
     */
    CloudProxyInfo* cloud_proxies = nullptr;
    /** 
     * @brief Number of cloud proxy.<br>
     */
    int cloud_proxy_count = 0;
};

/** 
 * @type keytype
 * @brief The maximum length of an ID.
 */
const unsigned int MAX_DEVICE_ID_LENGTH = 512;


/** 
 * @type keytype
 * @brief Connection type of the audio device
 */
enum DeviceTransportType {
    /** 
     * @brief Unknown
     */
    kDeviceTransportTypeUnknown = 0,
    /** 
     * @brief Built-in device
     */
    kDeviceTransportTypeBuiltIn = 1,
    /** 
     * @brief Unknown profile via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothUnknownMode = 2,
    /** 
     * @brief Handsfree Profile(HFP) via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothHandsFreeMode = 3,
    /** 
     * @brief Advanced Audio Distribution Profile(A2DP) via a Bluetooth connection
     */
    kDeviceTransportTypeBlueToothStereoMode = 4,
    /** 
     * @brief Speaker of the display or television
     */
    kDeviceTransportTypeDisplayAudio = 5,
    /** 
     * @brief Virtual sound card
     */
    kDeviceTransportTypeVirtual = 6
};


/** 
 * @type keytype
 * @brief Call test result
 */
enum class EchoTestResult {
    /** 
     * @brief The playback of captured audio/video is received, test succeeds.
     */
    kTestSuccess = 0,
    /** 
     * @brief Test is not completed after 60 seconds and has been stopped automatically.
     */
    kTestTimeout,
    /** 
     * @brief Less than 5s between the end of the last test and the start of the next test.
     */
    kTestIntervalShort,
    /** 
     * @brief Audio capture error
     */
    kAudioDeviceError,
    /** 
     * @brief Video capture error
     */
    kVideoDeviceError,
    /** 
     * @brief Audio reception error
     */
    kAudioReceiveError,
    /** 
     * @brief Video reception error
     */
    kVideoReceiveError,
    /** 
     * @brief Unrecoverable internal error
     */
    kInternalError
};

/** 
 * @type keytype
 * @brief Video/audio call test configurations
 */
struct EchoTestConfig {
    /** 
     * @brief View for rendering received video
     */
    void* view;
    /** 
     * @brief Whether to test audio. The device to be tested is the default audio device.  <br>
     *        + true: Yes  <br>
     *            - If you use internal capture, the device microphone will automatically turn on and onLocalAudioPropertiesReport{@link #IRtcEngineEventHandler#onLocalAudioPropertiesReport} will be triggered when the value of audioPropertiesReportInterval is set to greater than 0, from which you can judge the working status of the microphone.  <br>
     *            - If you choose custom capture, you also need to call pushExternalAudioFrame{@link #IRtcEngine#pushExternalAudioFrame} to push the captured audio to the SDK.  <br>
     *        + false: No  <br>
     */
    bool enableAudio;
    /** 
     * @brief Whether to test video. If you are using a desktop PC, the device to be tested is by default the first video device in the list.  <br>
     *        + true: Yes  <br>
     *            - If you use internal capture, the device camera will automatically turn on.  <br>
     *            - If you choose custom capture, you also need to call pushExternalVideoFrame{@link #IRtcEngine#pushExternalVideoFrame} to push the captured video to the SDK.  <br>
     *        + false: No  <br>
     * @notes The video is published with fixed parameters: resolution 640px × 360px, frame rate 15fps.
     */
    bool enableVideo;
    /** 
     * @brief Volume prompt interval in ms, the default value is 100. <br>
     *        + `<= 0`: Turn off prompt <br>
     *        + `(0,100]` Invalid interval value, and will be automatically reset to 100ms. <br>
     *        + `> 100`: the actual value of interval
     */
    int audioPropertiesReportInterval;
    /** 
     * @brief User ID for testing
     */
    const char* uid;
    /** 
     * @brief ID of the room that the tested user will join.  <br>
     */
    const char* roomId;
    /** 
     * @brief Token used for authenticating users when they enter the room.
     */
    const char* token;
};

}  // namespace bytertc
