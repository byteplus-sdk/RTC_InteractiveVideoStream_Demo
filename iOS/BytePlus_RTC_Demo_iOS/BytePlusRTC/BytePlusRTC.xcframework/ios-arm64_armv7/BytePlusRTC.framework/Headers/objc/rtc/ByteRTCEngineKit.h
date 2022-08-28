/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC
*/

#import <CoreMedia/CMTime.h>
#import "ByteRTCDefines.h"
#import "ByteRTCHttpClientProtocol.h"
#import "ByteRTCAudioMixingManager.h"

@class ByteRTCEngineKit;
@class RTCRoom;
/**
 * @type api
 */
@protocol ByteRTCHttpClientProtocol;

#pragma mark - ByteRTCEngineDelegate
/** 
 * @type callback
 * @brief ByteRTCEngineDelegate protocol contains the callback method provided by the SDK, which reports some run-time events to the application through a proxy
 */
@protocol ByteRTCEngineDelegate <NSObject>
@optional

#pragma mark - Core Delegate Methods
// @name  core event callback

/** 
 * @type callback
 * @region Warning code
 * @brief Warning callback occurred.   <br>
 *        A warning occurred during the SDK runtime. The SDK usually recovers automatically and warnings can be ignored.
 * @param engine ByteRTCEngineKit object.
 * @param Code Warning code. See ByteRTCWarningCode{@link #ByteRTCWarningCode}.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onWarning:(ByteRTCWarningCode)Code;

/** 
 * @type callback
 * @region Error code
 * @brief Error callback occurred. This callback is triggered when a network or media-related error occurs during the <br>
 *        SDK runtime and cannot be automatically recovered.
 * @param engine ByteRTCEngineKit object. <br>
 * @param errorCode  BigInt. See ByteRTCErrorCode{@link #ByteRTCErrorCode}. <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onError:(ByteRTCErrorCode)errorCode;

/** 
 * @type callback
 * @region Multi-Room
 * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync:{@link #ByteRTCEngineKit#setMultiDeviceAVSync:} is called.
 * @param engine The ByteRTCEngineKit instance.
 * @param state A/V synchronization state, see ByteRTCAVSyncState{@link #ByteRTCAVSyncState}.
 */
-(void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAVSyncStateChange:(ByteRTCAVSyncState)state;

/** 
 * @type callback
 * @region  engine management
 * @author hanchenchen.c
 * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
 * @param engine ByteRTCEngineKit object
 * @param state The current connection status between the SDK and the signaling server. See ByteRTCConnectionState{@link #ByteRTCConnectionState}
 */
- (void) rtcEngine:(ByteRTCEngineKit * _Nonnull)engine connectionChangedToState:(ByteRTCConnectionState) state;

/** 
 * @type callback
 * @region  engine management
 * @author hanchenchen.c
 * @brief SDK  current network connection type change callback.
 * @param engine ByteRTCEngineKit object
 * @param type SDK The current network connection type. See ByteRTCNetworkType{@link #ByteRTCNetworkType}
 */
- (void) rtcEngine:(ByteRTCEngineKit * _Nonnull)engine networkTypeChangedToType:(ByteRTCNetworkType) type;

/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on room state changes. You will receive this callback when you join the room, leave the room, or receive room relating warnings and errors.
 * @param roomId  Room ID.
 * @param uid  User ID.
 * @param state Room state code. <br>
 *              + 0: Success. <br>
 *              + !0: Failure. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
 * @param extraInfo Extra information.
 *                 `joinType` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rehoins the room. <br>
 *                 `elapsed` indicates the time interval from calling joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to successfully joining room, in ms.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on stream state changes. You will receive this callback when you receive stream relating warnings and errors.
 * @param roomId  Room ID.
 * @param uid  User ID.
 * @param state Room state code. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
 * @param extraInfo Extra information. Currently unavailable.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onStreamStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;


/** 
  * @type callback
  * @region Room management
  * @author shenpengliang
  * @brief After leaving the room successfully, receives the callback.   <br>
  *        When the user calls the leaveRoom{@link #ByteRTCEngineKit#leaveRoom}, the SDK will stop all publishing subscription streams and release all call-related media resources. After that, the user receives this callback . <br>
  * @param engine  RTCRoom instance  <br>
  * @param stats  Statistics for this call. See ByteRTCRoomStats{@link #ByteRTCRoomStats}. <br>
  * @notes   <br>
  *        + If calling leaveRoom{@link #ByteRTCEngineKit#leaveRoom} and then destroyEngine{@link #ByteRTCEngineKit#destroyEngine} immediately after, the user will not receive this callback. <br>
  *        + If the app needs to use the media resources of the device for purposes other than RTC, you should init the resources after receiving this callback. Receiving this callback ensures that the resources are not occupied by RTC SDK.
  */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

/** 
  * @type callback
  * @region Room management
  * @author shenpengliang
  * @brief You will receive this callback in following cases: <br>
  *        + The remote user calls setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} turns visible and joins your room. <br>
  *        + The remote visible user is disconnected and then reconnected to your room. <br>
  *        + The invisible remote user in your room calls setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} and turns visible. <br>
  *        + You join the room when there are visible users in the room.
  * @param engine ByteRTCEngineKit instance <br>
  * @param userInfo See ByteRTCUserInfo{@link #ByteRTCUserInfo}. <br>
  * @param elapsed Reserved parameter.
  */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onUserJoined:(nonnull ByteRTCUserInfo *)userInfo elapsed:(NSInteger)elapsed;

    /** 
     * @type callback
     * @author shenpengliang
     * @brief This callback is triggered when a remote user is disconnected or turns invisible.
     * @param uid ID of the user who leaves the room, or switches to invisible. <br>
     * @param reason Reason to leave the room: <br>
     *               + 0: The remote client calls leaveRoom{@link #ByteRTCEngineKit#leaveRoom} to leave the room. <br>
     *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
     *               + 2: The remote client calls setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to turn invisible.<br>
     *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
     */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;

/** 
 * @hidden
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback the event when the release flow is successful.
 * @param engine ByteRTCEngineKit object. <br>
 * @param userId  Publish the user ID of the stream. <br>
 * @param isScreen Whether the successful stream is a screen stream
 *         + Ture: screen stream; <br>
 *         + False: non-screen stream. <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

#pragma mark - Core Audio Delegate Methods
// @name core audio event callback

/** 
 * @hidden
 * @type callback
 * @region Media Stream Management
 * @author shenpengliang
 * @brief When a user in the room calls muteAllRemoteAudio:{@link #muteAllRemoteAudio:},
 *        Changes the state of receiving all remote audio streams, other users in the room receive this callback.
 * @param engine ByteRTCEngineKit object
 * @param uid Change the user ID of the receive state
 * @param muteState Receive state. See ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMuteAllRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMuteAllRemoteVideo:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region Media Stream Management
 * @author shenpengliang
 * @brief Transmission state change of an audio stream in the room triggers this callback. Refer to muteLocalAudio:{@link #ByteRTCEngineKit#muteLocalAudio:} for more details.
 * @param engine ByteRTCEngineKit instance
 * @param uid The user who changes his/her transmission state of the audio streams
 * @param muteState Transmission state of the audio streams. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @deprecated since 323.1, use onUserStartAudioCapture instead
 * @type callback
 * @region audio event callback
 * @author dixing
 * @brief Remote user on/off audio device capture callback
 *         Prompts that a remote user has turned on/off audio device capture. The callback is triggered by the remote user's call to the startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} method
 * @param engine ByteRTCEngineering Kit object
 * @param enabled YES: This user turned on audio Device capture; NO: This user turned off audio device capture
 * @param uid Remote user ID
 *        + This interface is deprecated, please use rtcEngine:onUserStartAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartAudioCapture:} and rtcEngine:onUserStopAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopAudioCapture:} <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didLocalAudioEnabled:(BOOL)enabled byUid:(NSString * _Nonnull)uid;
    /** 
     * @type callback
     * @brief You will be informed 30 sec before the expiration via this callback.
     *        Call updateToken:{@link #ByteRTCEngineKit#updateToken:} to renew the Token. If the Token expired, the user would be removed from the room and not be able to continue the call.
     */
- (void)onTokenWillExpire:(ByteRTCEngineKit * _Nonnull)engine;
/** 
 * @type callback
 * @region Audio event callback
 * @author dixing
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts audio capture by calling startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture}.
 * @param engine ByteRTCEngineKit instance
 * @param userId The user who starts the internal audio capture
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartAudioCapture:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region Audio event callback
 * @author dixing
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user stops audio capture by calling stopAudioCapture{@link #ByteRTCEngineKit#stopAudioCapture}.
 * @param engine ByteRTCEngineKit instance
 * @param userId The user who stops the internal audio capture
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStopAudioCapture:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region Audio event callback
 * @author wangjunzheng
 * @brief Report the event when the first frame of audio of the remote stream is received
 * @param engine ByteRTCEngineKit object
 * @param key Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @notes The callback will be received when the user has just received each audio stream in the room.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/** 
 * @hidden
 * @deprecated Since 329.1, use onLocalAudioPropertiesReport/onRemoteAudioPropertiesReport instead
 * @type callback
 * @region audio event callback
 * @author wangjunzheng
 * @brief To prompt the volume information collected locally and the volume information of the remote user subscribed in the room. <br>
 *        This callback is not turned on by default. You can open it by calling setAudioVolumeIndicationInterval:{@link #setAudioVolumeIndicationInterval:}. <br>
 * @param engine ByteRTCEngineKit object
 * @param speakers  ID and volume of the local user and subscribed remote user.
 *                       See ByteRTCAudioVolumeInfo{@link #ByteRTCAudioVolumeInfo}. The sum of all audio volumes contained in
 * @param totalRemoteVolume Speakers, the value range is [0,255].
 * @notes  <br>
 *         + For local users: As long as the local audio collection is performed, the callback will contain the volume information of the local audio stream. <br>
 *         + For remote users: The local must subscribe to the audio stream of a remote user before the callback contains the volume information of the audio stream it sent.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioVolumeIndication:(NSArray<ByteRTCAudioVolumeInfo *> * _Nonnull)speakers totalRemoteVolume:(NSInteger)totalRemoteVolume;

 /** 
  * @type callback
  * @region Audio Management
  * @author wangjunzheng
  * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCEngineKit#enableAudioPropertiesReport:}, you will periodically receive this callback for the information about local audio. <br>
  *        Local audio includes the microphone audio and the screen audio captured using RTC SDK internal mechanisms.
  * @param engine ByteRTCEngineKit object
  * @param audioPropertiesInfos See ByteRTCLocalAudioPropertiesInfo{@link #ByteRTCLocalAudioPropertiesInfo}.
  */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onLocalAudioPropertiesReport:(NSArray<ByteRTCLocalAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos;

/** 
 * @hidden(iOS)
 * @type callback
 * @region Audio Device Management
 * @brief Notification on the playing volume during the test for the local audio devices
 * @param volume playing volume during the test for the local audio devices in milliseconds. We recommend to set it to 200 ms.The range is [0,255]. 
 * @notes Start an audio-device test by calling startAudioPlaybackDeviceTest{@link #startAudioPlaybackDeviceTest} or startAudioDeviceRecordTest{@link #startAudioDeviceRecordTest} will register this callback for regular notification on playing volume. You can set the time interval between each callback by passing a proper value when calling the API above. 
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioPlaybackDeviceTestVolume:(int)volume;

 /** 
  * @type callback
  * @region Audio Management
  * @author wangjunzheng
  * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCEngineKit#enableAudioPropertiesReport:}, you will periodically receive this callback for the information about the subscribed remote audio streams. <br>
  *        The remote audio streams includes the microphone audio and screen audio collected using the RTC SDK internal mechanism/custom mechanism.
  * @param engine ByteRTCEngineKit object
  * @param audioPropertiesInfos See ByteRTCRemoteAudioPropertiesInfo{@link #ByteRTCRemoteAudioPropertiesInfo}.
  * @param totalRemoteVolume The total volume of all the subscribed remote streams. The range is [0,255]. <br>
  *        + [0,25] Is close to silent; <br>
  *        + [25,75] Is low volume; <br>
  *        + [76,204] Is medium volume; <br>
  *        + [205,255] Is high volume. <br>
  */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRemoteAudioPropertiesReport:(NSArray<ByteRTCRemoteAudioPropertiesInfo *> * _Nonnull)audioPropertiesInfos totalRemoteVolume:(NSInteger)totalRemoteVolume;

/** 
 * @type callback
 * @region Audio Management
 * @author zhangcaining
 * @brief After calling enableAudioPropertiesReport:{@link #ByteRTCEngineKit#enableAudioPropertiesReport:}, you will periodically receive this callback for the active speaker information. <br>
 * @param roomId  Room ID.
 * @param uid The user ID of the active speaker.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onActiveSpeaker:(NSString * _Nonnull)roomId uid:(NSString *_Nonnull)uid;

#pragma mark - Core Video Delegate Methods
// @name core video event callback

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region Video management
 * @author shenpengliang
 * @param engine ByteRTCEngineKit instance
 * @brief Transmission state change of an video stream in the room triggers this callback. Refer to muteLocalVideo:{@link #ByteRTCEngineKit#muteLocalVideo:}.
 * @param uid The user who changes his/her transmission state of the video streams
 * @param muteState Transmission state of the video streams. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMuteVideo:(NSString * _Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

/** 
 * @type callback
 * @region Video management
 * @author zhushufan.ref
 * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts video capture by startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture}.
 * @param engine ByteRTCEngineKit instance
 * @param userId The user who starts the internal video capture
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStartVideoCapture:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region Video management
 * @author zhushufan.ref
 * @brief The remote clients in the room will be informed of the state change via  this callback after the visible user stops video capture by calling stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture}.
 * @param engine ByteRTCEngineKit instance
 * @param userId The user who stops the internal video capture
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserStopVideoCapture:(NSString *_Nonnull)userId;

/** 
 * @type callback
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Receive this callback when the first locally captured video/screen share screen is rendered in the local view.
 * @param engine ByteRTCEngineKit object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstLocalVideoFrameCaptured:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/** 
 * @type callback
 * @region Video Management
 * @author zhushufan.ref
 * @brief Receive this callback after the first frame of remote video stream is locally rendered by SDK.
 * @param engine ByteRTCEngineKit object
 * @param streamKey  Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo  Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteVideoFrameRendered:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/** 
 * @type callback
 * @region Video Management
 * @author zhushufan.ref
 * @brief Receive this callback after the first frame of remote video stream is received and decoded by SDK.
 * @param engine ByteRTCEngineKit object
 * @param streamKey  Remote stream information, see ByteRTCRemoteStreamKey {@link #ByteRTCRemoteStreamKey}
 * @param frameInfo  Video frame information, see ByteRTCVideoFrameInfo {@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstRemoteVideoFrameDecoded:(ByteRTCRemoteStreamKey * _Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/** 
 * @type callback
 * @region Video Management
 * @author zhushufan.ref
 * @brief Users in the room who subscribe to this video stream receive this callback when the remote video size or rotation information changes.
 * @param engine ByteRTCEngineKit object
 * @param streamKey Stream property. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param frameInfo Video frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteVideoSizeChanged:(ByteRTCRemoteStreamKey *_Nonnull)streamKey withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @type callback
 * @region video management
 * @author zhushufan.ref
 * @brief Receive this callback when local video size or rotation information changes.
 * @param engine  ByteRTCEngineKit object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param frameInfo Frame information. See ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLocalVideoSizeChanged:(ByteRTCStreamIndex)streamIndex withFrameInfo:(ByteRTCVideoFrameInfo *_Nonnull)frameInfo;

/** 
 * @type callback
 * @region Video management
 * @author zhushufan.ref
 * @brief Remote video stream state change callback.
 * @param engine ByteRTCEngineKit object, reference: ByteRTCEngineKit{@link #ByteRTCEngineKit}
 * @param uid The user ID of the remote user whose video stream state has changed
 * @param state The changed remote video stream state. See type ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine remoteVideoStateChangedOfUid:(NSString * _Nonnull)uid state:(ByteRTCRemoteVideoState)state;

/** 
 * @hidden
 * @deprecated since 337, using onAudioDeviceStateChanged and onVideoDeviceStateChanged instead
 * @type callback
 * @region Engine management
 * @author zhangzhenyu.samuel
 * @brief Media device state callback, returns the state of four media devices: audio capture, audio playback, video capture, and screen capture.
 * @param engine ByteRTCEngineKit instance
 * @param device_id Device ID
 * @param device_type Device type. See ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}.
 * @param device_state Device state. See ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}.
 * @param device_error Device error. See ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMediaDeviceStateChanged:(NSString*_Nonnull)device_id
        device_type:(ByteRTCMediaDeviceType)device_type
        device_state:(ByteRTCMediaDeviceState)device_state
        device_error:(ByteRTCMediaDeviceError)device_error
    __attribute((deprecated("Will be removed in new version")));
/** 
 * @type callback
 * @region Engine management
 * @author zhangzhenyu.samuel
 * @brief Audio device state callback, returns the state of audio capture and audio playback devices.
 * @param engine ByteRTCEngineKit instance
 * @param device_id Device ID
 * @param device_type Device type. See ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}.
 * @param device_state Device state. See ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}.
 * @param device_error Device error. See ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioDeviceStateChanged:(NSString*_Nonnull)device_id
      device_type:(ByteRTCAudioDeviceType)device_type
     device_state:(ByteRTCMediaDeviceState)device_state
     device_error:(ByteRTCMediaDeviceError)device_error;
/** 
 * @type callback
 * @region Engine management
 * @author zhangzhenyu.samuel
 * @brief Video device state callback, returns the state of camera capture and screen capture devices.
 * @param engine ByteRTCEngineKit instance
 * @param device_id Device ID
 * @param device_type Device type. See ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}.
 * @param device_state Device state. See ByteRTCMediaDeviceState{@link #ByteRTCMediaDeviceState}.
 * @param device_error Device error. See ByteRTCMediaDeviceError{@link #ByteRTCMediaDeviceError}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onVideoDeviceStateChanged:(NSString*_Nonnull)device_id
      device_type:(ByteRTCVideoDeviceType)device_type
     device_state:(ByteRTCMediaDeviceState)device_state
     device_error:(ByteRTCMediaDeviceError)device_error;

/** 
 * @hidden
 * @deprecated since 337, using onAudioDeviceWarning and onVideoDeviceWarning instead
 * @type callback
 * @region Engine Management
 * @author dixing
 * @brief Media device warning callback. The media devices includes: audio capture devices, audio rendering devices, and video capture devices.
 * @param engine ByteRTCEngineKit object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCMediaDeviceType{@link #ByteRTCMediaDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onMediaDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCMediaDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning
    __attribute((deprecated("Will be removed in new version")));
/** 
 * @type callback
 * @region Engine Management
 * @author dixing
 * @brief Audio device warning callback. The audio devices includes audio capture devices and audio rendering devices.
 * @param engine ByteRTCEngineKit object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCAudioDeviceType{@link #ByteRTCAudioDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCAudioDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;
/** 
 * @type callback
 * @region Engine Management
 * @author dixing
 * @brief Video device warning callback. The video devices includes video capture devices.
 * @param engine ByteRTCEngineKit object
 * @param deviceId Device ID
 * @param deviceType See ByteRTCVideoDeviceType{@link #ByteRTCVideoDeviceType}
 * @param deviceWarning See ByteRTCMediaDeviceWarning{@link #ByteRTCMediaDeviceWarning}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onVideoDeviceWarning:(NSString*_Nonnull)deviceId
    deviceType:(ByteRTCVideoDeviceType)deviceType
    deviceWarning:(ByteRTCMediaDeviceWarning)deviceWarning;

/** 
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Receive this callback when the sending state of the first audio frame changes.
 * @param engine ByteRTCEngineKit object
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Receive this callback when the video first frame sending state changes
 * @param engine ByteRTCEngineKit object
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Screen Sharing Stream Video Receive this callback
 * @param engine ByteRTCEngineKit object when the first frame sending state changes. <br>
 * @param user Local user information. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame sending status. See ByteRTCFirstFrameSendState{@link #ByteRTCFirstFrameSendState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onScreenVideoFrameSendStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFrameSendState)state;

/** 
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Receive this callback when the audio first frame playback state changes
 * @param engine ByteRTCEngineering Kit object. <br>
 * @param user User information from the audio stream. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback status. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Receive this callback when the video first frame playback state changes
 * @param user User information from the video stream source. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback state. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

/** 
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Screen Sharing Stream Video Receive this callback
 * @param engine ByteRTCEngineKit object when the first frame playback state changes. <br>
 * @param user Screen sharing user information from the stream source. See ByteRTCUser{@link #ByteRTCUser}
 * @param state First frame playback status. See ByteRTCFirstFramePlayState{@link #ByteRTCFirstFramePlayState}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onScreenVideoFramePlayStateChanged:(ByteRTCUser *_Nonnull)user state:(ByteRTCFirstFramePlayState)state;

#pragma mark - Media Stream Delegate Methods
// @name media data event callback

/** 
 *  @type callback
 *  @region Audio event callback
 *  @author wangjunzheng
 *  @brief Receive the callback when the first audio frame is locally collected.
 *  @param engine ByteRTCEngineKit object
 *  @param streamIndex  Audio stream properties. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstLocalAudioFrame:(ByteRTCStreamIndex) streamIndex;

/** 
 * @hidden
 * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief This callback is triggered by the following conditions: <br>
 *         + When a user in the room publishes a new audio & video stream, other users in the room will receive this callback notification. <br>
 *         + When the user's original audio and video stream in the room is removed and the audio & video stream is republished, other users in the room will receive this callback notification. <br>
 *         + When the user first joins the room, he receives this callback, including all published streams in the room.
 * @param engine ByteRTCEngineKit object. Properties of the <br>
 * @param stream  Stream. See ByteRTCStream{@link #ByteRTCStream} data type. <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onStreamAdd:(id <ByteRTCStream> _Nonnull)stream;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on new media streams captured by camera/microphone in the room.
 * @param engine The engine instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes You will receive this callback after a remote user successfully published media streams captured by camera/microphone in the room with publishStream:{@link #ByteRTCEngineKit#publishStream:}. Then you can choose whether to call subscribeStream:mediaStreamType:{@link #ByteRTCEngineKit#subscribeStream:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserPublishStream:(NSString *_Nonnull)userId
             type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on removal of remote media stream captured by camera/microphone.
 * @param engine The engine instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @notes After receiving this callback, you can choose whether to call unSubscribeStream:mediaStreamType:{@link #ByteRTCEngineKit#unSubscribeStream:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserUnPublishStream:(NSString *_Nonnull)userId
             type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on new screen sharing media streams from remote users in the room.
 * @param engine The engine instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes You will receive this callback after a remote user successfully publishes screen sharing streams in the room with publishScreen:{@link #ByteRTCEngineKit#publishScreen:}. Then you can choose whether to call subscribeScreen:mediaStreamType:{@link #ByteRTCEngineKit#subscribeScreen:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserPublishScreen:(NSString *_Nonnull)userId
             type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on removal of screen sharing media streams from remote users in the room.
 * @param engine The engine instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @notes After receiving this callback, you can choose whether to call unSubscribeScreen:mediaStreamType:{@link #ByteRTCEngineKit#unSubscribeScreen:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserUnPublishScreen:(NSString *_Nonnull)userId
             type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on subscription status of media streams
 * @param engine The engine instance
 * @param state Subscription status of media streams, see ByteRTCSubscribeState{@link #ByteRTCSubscribeState}.
 * @param userId The ID of the user who published the stream.
 * @param info Configurations of stream subscription, see ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}.
 * @notes <br>
 *        Local users will receive this callback:  <br>
 *        + After calling subscribeStream:mediaStreamType:{@link #ByteRTCEngineKit#subscribeStream:mediaStreamType:}/unSubscribeStream:mediaStreamType:{@link #ByteRTCEngineKit#unSubscribeStream:mediaStreamType:} to change the subscription status of remote media streams captured by camera/microphone.  <br>
 *        + After calling subscribeScreen:mediaStreamType:{@link #ByteRTCEngineKit#subscribeScreen:mediaStreamType:}/unSubscribeScreen:mediaStreamType:{@link #ByteRTCEngineKit#unSubscribeScreen:mediaStreamType:} to change the subscription status of remote screen sharing streams.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/** 
 * @hidden
 * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
 * @type callback
 * @region Room Management
 * @author shenpengliang
 * @brief Local users will receive this callback notification when a remote user in the room stops publishing audio & video streams.   <br>
 * @param engine ByteRTCEngineKit object. <br>
 * @param uid  The user ID of the remote stream source. <br>
 * @param stream  The properties of the stream. See ByteRTCStream{@link #ByteRTCStream}. <br>
 * @param reason  For reasons of remote stream removal. See ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}. <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;

/** 
 *  @hidden
 *  @type callback
 *  @region Audio management
 *  @author wangjunzheng
 *  @brief In the game scene, the event is called back when the audio sending mode of the remote user in the room changes. There are only three sending modes: mute, send to the team, and send to the world.
 *  @param engine  ByteRTCEngineKit object
 *  @param uid   Remote user ID
 *  @param mode   Remote user's audio sending mode
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didUserAudioSendModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;

/** 
 *  @hidden
 *  @type callback
 *  @region Audio management
 *  @author wangjunzheng
 *  @brief In the game scene, the event is called back when the audio listening mode of the remote user in the room changes. There are only three listening modes, namely: mute, listening team, and listening world.
 *  @param engine  ByteRTCEngineKit object
 *  @param  uid   Remote user ID
 *  @param  mode   Audio listening mode of remote user
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine didUserAudioRecvModeChange:(NSString* _Nonnull )uid mode:(ByteRTCRangeAudioMode)mode;

/** 
 * @type callback
 * @region Video management
 * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is invoked to disable/unban the sending of a specified user's video stream in a specified room.
 * @param uid Disabled/unbanned video stream user ID
 * @param banned Video stream sending status <br>
 *         + True: Video stream sending is disabled <br>
 *         + False: Video stream sending is unbanned
 * @notes   <br>
 *         + When the specified user in the room is banned/unbanned video stream sending, all users in the room will receive the callback. <br>
 *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
 *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback. <br>
 *         + The same room is created again after dissolution, and the state in the room is empty.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onVideoStreamBanned:(NSString* _Nonnull)uid isBanned:(BOOL)banned;
/** 
 * @type callback
 * @region Audio event callback
 * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is called to disable/unban the sending of the specified user's audio and video stream in a specified room.
 * @param uid Disabled/unbanned audio stream user ID
 * @param banned Audio stream sending status <br>
 *         + True: Audio stream sending is disabled <br>
 *         + False: Audio stream sending is unbanned
 * @notes   <br>
 *         + When the specified user in the room is disabled/unbanned audio stream sending, all users in the room will receive the callback. <br>
 *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
 *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback. <br>
 *         + The same room is created again after dissolution, and the state in the room is empty.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioStreamBanned:(NSString* _Nonnull)uid isBanned:(BOOL)banned;

#pragma mark - Media Device Delegate Methods
// @name media device event callback
/** 
 * @hidden
 * @deprecated since 338.1, use onAudioRouteChanged instead
 *  @type callback
 *  @region Audio event callback
 *  @author dixing
 *  @brief You will receive this callback when the audio playback device changes.
 *  @param engine ByteRTCEngineKit instance.
 *  @param device New audio playback device. See ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}
 *  @notes For the settings of audio playback device and audio routing, see setAudioPlaybackDevice:{@link #ByteRTCEngineKit#setAudioPlaybackDevice:}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onAudioPlaybackDeviceChanged:(ByteRTCAudioPlaybackDevice)device;
/** 
 * @hidden(Mac)
 * @type callback
 * @region Audio event callback
 * @author dixing
 * @brief RTC notifies the audio route changes via this callback.
 * @param device Current audio playback device. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute} for more information.
 * @notes Either of the following action will lead to audio route switching. <br>
 * + Connecting/Disconnecting an audio device
 * + Designating the other audio device by calling setAudioRoute:{@link #ByteRTCEngineKit#setAudioRoute:}. 
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onAudioRouteChanged:(ByteRTCAudioRoute)device;

#pragma mark custom message Delegate Methods
// @name send message callback

/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a broadcast text message from the room called sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:}.
 * @param engine  The current RTCEngine instance.
 * @param uid  Message sender ID.
 * @param message The content of the received text message.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/** 
 * @type callback
 * @region Live Messaging Communication
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a broadcast binary message sent from the room by calling sendRoomBinaryMessage:{@link #ByteRTCEngineKit#sendRoomBinaryMessage:}.
 * @param engine  The current RTCEngine instance.
 * @param uid  Message sender ID.
 * @param message The binary message content received.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/** 
 * @type callback
 * @region Video management
 * @author wangjunlin.3182
 * @brief Receive this callback when you receive a video frame with a SEI message by calling sendSEIMessage:andMessage:andRepeatCount:{@link #ByteRTCEngineKit#sendSEIMessage:andMessage:andRepeatCount:}.
 * @param engine Current RTCEngine instance
 * @param remoteStreamKey Contains the user name, room name and media stream of the SEI sender. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param message Received SEI message content
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onSEIMessageReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey andMessage:(NSData* _Nonnull)message;

/** 
 * @hidden
 * @type callback
 * @region Message
 * @brief Callback about publishing status of the black frame video stream .  <br>
 *        In a voice call scenario, when the local user calls sendSEIMessage:andMessage:andRepeatCount:{@link #ByteRTCEngineKit#sendSEIMessage:andMessage:andRepeatCount:} to send SEI data with a black frame, the sending status of the stream is notified to the remote user through this callback.  <br>
 *        You can tell from this callback that the video frame carrying SEI data is a black frame and thus not render that video frame.
 * @param engine Current RTCEngine instance
 * @param remoteStreamKey Information about stream from the remote user, see RemoteStreamKey{@link #RemoteStreamKey}.
 * @param eventType State of the black frame video stream, see ByteSEIStreamEventType{@link #ByteSEIStreamEventType}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onSEIStreamUpdate:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey eventType:(ByteSEIStreamEventType)eventType;

/** 
 * @type api
 * @region audio management
 * @author wangjunzheng
 * @brief Audio stream synchronization information callback. You can use this callback to receive audio stream synchronization information sent remotely after the remote user calls sendStreamSyncInfo:config:{@link #ByteRTCEngineKit#sendStreamSyncInfo:config:} to send an audio stream synchronization message. <br>
 * @param engine  Current RTCEngine instance.
 * @param remoteStreamKey  For remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param streamType  Media stream type. See ByteRTCSyncInfoStreamType{@link #ByteRTCSyncInfoStreamType}.
 * @param data Message content.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onStreamSyncInfoReceived:(ByteRTCRemoteStreamKey* _Nonnull)remoteStreamKey streamType:(ByteRTCSyncInfoStreamType)streamType data:(NSData* _Nonnull)data;

#pragma mark - Statistics Delegate Methods
// @name data statistics callback

/** 
 * @type callback
 * @region Data statistics
 * @author liuzhiqiang.avcoder
 * @brief In-room call statistics callback.    <br>
 *        After the user enters the room and starts the call, he receives this callback every 2s.
 * @param engine ByteRTCEngineKit object
 * @param stats Current RtcEngine statistics. See ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/** 
 * @type callback
 * @region Data statistics
 * @author liuzhiqiang.avcoder
 * @brief Report the current device CPU and memory usage, which is triggered every 2s.
 * @param engine ByteRTCEngineKit object
 * @param stats Cpu and memory usage information. See ByteRTCSysStats{@link #ByteRTCSysStats} data type
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine reportSysStats:(const ByteRTCSysStats * _Nonnull)stats;

/** 
 * @type callback
 * @region Data statistics
 * @author liuzhiqiang.avcoder
 * @brief Local stream data statistics and network quality callbacks.   <br>
 *        After the local user publishes the flow successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the published flow during this reference period. <br>
 *         Statistics are passed to the user through the callback parameters of the ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} type, including the sent audio & video bit rate, sent frame rate, encoded frame rate, network quality, etc. <br>
 * @param engine ByteRTCEngineKit object. <br>
 * @param stats  Publish audio/video stream quality and local network quality statistics. See ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} data type. <br>
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onLocalStreamStats:(const ByteRTCLocalStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region  data statistics
 * @author liuzhiqiang.avcoder
 * @brief  Remote audio/video stream data statistics and network quality callbacks for local subscriptions.   <br>
 *        After the local user subscribes to the stream successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the subscribed stream during this reference period, including: sending audio & video bit rate, sending frame rate, encoded frame rate, network quality, etc.
 * @param engine ByteRTCEngineKit object
 * @param stats Current RtcEngine statistics. See ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onRemoteStreamStats:(const ByteRTCRemoteStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region Audio event callback
 * @author wangjunzheng
 * @brief Receive this callback when the state of the local audio stream changes.
 * @param engine ByteRTCEngineKit object
 * @param state The current state of the local audio device. See ByteRTCLocalAudioStreamState{@link #ByteRTCLocalAudioStreamState}
 * @param error Error code when the state of the local audio stream changes. See ByteRTCLocalAudioStreamError{@link #ByteRTCLocalAudioStreamError}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onLocalAudioStateChanged:(ByteRTCLocalAudioStreamState)state
                     error:(ByteRTCLocalAudioStreamError)error;

/** 
 *  @type callback
 *  @region Audio event callback
 *  @author wangjunzheng
 *  @brief Receive this callback when the state of the remote audio stream subscribed to changes.
 *  @param engine ByteRTCEngineKit object
 *  @param key Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 *  @param state The current state of the remote audio stream. See ByteRTCRemoteAudioState{@link #ByteRTCRemoteAudioState}
 *  @param reason The reason for the change in the state of the remote audio stream. See ByteRTCRemoteAudioStateChangeReason{@link #ByteRTCRemoteAudioStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onRemoteAudioStateChanged:(ByteRTCRemoteStreamKey * _Nonnull)key
                      state:(ByteRTCRemoteAudioState)state
                      reason:(ByteRTCRemoteAudioStateChangeReason)reason;

/** 
 * @type callback
 * @region Video management
 * @author shenpengliang
 * @brief Receive this event when the state of the local video stream changes.
 * @param engine ByteRTCEngineKit object
 * @param streamIndex Stream property. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state Current state of local video stream. See ByteRTCLocalVideoStreamState{@link #ByteRTCLocalVideoStreamState}
 * @param error Error code when local video state changes. See ByteRTCLocalVideoStreamError{@link #ByteRTCLocalVideoStreamError}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onLocalVideoStateChanged:(ByteRTCStreamIndex)streamIndex
             withStreamState:(ByteRTCLocalVideoStreamState)state
             withStreamError:(ByteRTCLocalVideoStreamError)error;

/** 
 * @type callback
 * @region Video management
 * @author shenpengliang
 * @brief When the state of the remote video stream changes, users in the room who subscribe to this stream will receive the event.
 * @param engine ByteRTCEngineKit object
 * @param streamKey Remote video stream information, room, user ID, stream attributes, etc.. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param state The current state of the remote video stream. See ByteRTCRemoteVideoState{@link #ByteRTCRemoteVideoState}
 * @param reason The reason for the change in the state of the remote video stream. See ByteRTCRemoteVideoStateChangeReason{@link #ByteRTCRemoteVideoStateChangeReason}
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onRemoteVideoStateChanged:(ByteRTCRemoteStreamKey*_Nonnull)streamKey
               withVideoState:(ByteRTCRemoteVideoState)state
withVideoStateReason:(ByteRTCRemoteVideoStateChangeReason)reason;

#pragma mark - Message Delegate Methods

/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a text message (P2P) from another user in the room via sendUserMessage:message:config:{@link #ByteRTCEngineKit#sendUserMessage:message:config}.
 * @param engine  The current RTCEngine instance.
 * @param uid  The user ID of the sender of the message.
 * @param message The content of the received text message.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageReceived:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;

/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a binary message from another user in the room via sendUserBinaryMessage:message:config:{@link #ByteRTCEngineKit#sendUserBinaryMessage:message:config:}.
 * @param engine  The current RTCEngine instance.
 * @param uid  The user ID of the sender of the message.
 * @param message The binary message content received.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserBinaryMessageReceived:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief After sending a text or binary message (P2P) to a single user in the room, the message sender will receive a callback with the result of the message.
 * @param engine ByteRTCEngineKit object
 * @param msgid  The ID of this message.
 * @param error Message result. See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
 * @notes   <br>
 *         + You should call sendUserMessage:message:config:{@link #ByteRTCEngineKit#sendUserMessage:message:config} Send a text message to a single user in the room <br>
 *         + You should call sendUserBinaryMessage:message:config:{@link #ByteRTCEngineKit#sendUserBinaryMessage:message:config:} Send a binary message to a single user in the room
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

 /** 
  * @type callback
  * @region Real-time messaging
  * @author hanchenchen.c
  * @brief After sending a text or binary message to all users in the room, the message sender will receive a callback with the result of the message.
  * @param engine ByteRTCEngineKit object
  * @param msgid  The ID of this message.
  * @param error  Message sending results. See ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes   <br>
  *         + You should call sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:} Send a mass text message to the room <br>
  *         + You should call sendRoomBinaryMessage:{@link #ByteRTCEngineKit#sendRoomBinaryMessage:} Send a mass binary message to the room
  */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;

#pragma mark - Rtm
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Login result callback
 * @param engine ByteRTCEngineKit object
 * @param uid   <br>
 *        Login user ID
 * @param errorCode   <br>
 *        Login result <br>
 *        See ByteRTCLoginErrorCode{@link #ByteRTCLoginErrorCode}.
 * @param elapsed   <br>
 *        The time it takes from calling the login:uid:{@link #ByteRTCEngineKit#login:uid:} interface to return the result. <br>
 *         Is in ms.
 * @notes Receive this callback after calling login:uid:{@link #ByteRTCEngineKit#login:uid:}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onLoginResult:(NSString * _Nonnull)uid errorCode:(ByteRTCLoginErrorCode)errorCode elapsed:(NSInteger)elapsed;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Logout result callback
 * @param engine ByteRTCEngineKit object
 * @notes After calling logout{@link #ByteRTCEngineKit#logout}, you will receive this callback.
 */
- (void)rtcEngineOnLogout:(ByteRTCEngineKit * _Nonnull)engine;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Set the return result of the application server parameter
 * @param engine ByteRTCEngineKit object
 * @param errorCode  <br>
 *        Set the result <br>
 *         + Return 200, set successfully <br>
 *         + Return other, set failed
 * @notes Receive this callback after calling setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onServerParamsSetResult:(NSInteger)errorCode;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Returns the result of querying the login status of the peer or local user
 * @param engine ByteRTCEngineKit object
 * @param peerUserId   <br>
 *        User ID to query
 * @param status   <br>
 *        User login status of the query <br>
 *        See ByteRTCUserOnlineStatus{@link #ByteRTCUserOnlineStatus}.
 * @notes You must first call getPeerOnlineStatus:{@link #ByteRTCEngineKit#getPeerOnlineStatus:} to receive this callback.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onGetPeerOnlineStatus:(NSString * _Nonnull)peerUserId status:(ByteRTCUserOnlineStatus)status;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a text message from an out-of-room user calling sendUserMessageOutsideRoom:message:config:{@link #ByteRTCEngineKit#sendUserMessageOutsideRoom:message:config:}
 * @param engine ByteRTCEngineKit object
 * @param uid   <br>
 *        Message sender ID
 * @param message   <br>
 *        Received text message content
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receive this callback when you receive a binary message from an out-of-room user call sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCEngineKit#sendUserBinaryMessageOutsideRoom:message:config:}.
 * @param engine ByteRTCEngineKit object
 * @param  uid   <br>
 *          Message sender ID
 * @param  message   <br>
 *          Binary message content received
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserBinaryMessageReceivedOutsideRoom:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;
/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief A callback that sends a message to a specified user outside the room
 * @param engine ByteRTCEngineKit object
 * @param msgid   <br>
 *        The ID of this message <br>
 *        All P2P and P2Server messages share a single ID sequence.
 * @param error   <br>
 *         Message sending result <br>
 *         See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @notes Receive this callback when you send a message by calling sendUserMessageOutsideRoom:message:config:{@link #ByteRTCEngineKit#sendUserMessageOutsideRoom:message:config:} or sendUserBinaryMessageOutsideRoom:message:config:{@link #ByteRTCEngineKit#sendUserBinaryMessageOutsideRoom:message:config:}.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onUserMessageSendResultOutsideRoom:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

/** 
 * @type callback
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Receives the callback after sending the message to the application server successfully.
 * @param engine ByteRTCEngineKit object
 * @param msgid The ID of this message <br>
 *        All P2P and P2Server messages share a single ID sequence.
 * @param error Message Sending Results. See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}.
 * @param message The message returned in ACK when the application server receives HTTP request.
 * @notes Receive this callback when you call sendServerMessage:{@link #ByteRTCEngineKit#sendServerMessage:} or sendServerBinaryMessage:{@link #ByteRTCEngineKit#sendServerBinaryMessage:} to send a message to your application server.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onServerMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error message:(NSData * _Nonnull)message;

#pragma mark - Network Probe Methods
/** 
 * @type callback
 * @region Pre-call network detection
 * @author hanchenchen.c
 * @brief Pre-call network detection result
 * @param engine ByteRTCEngineKit object
 * @param type   <br>
 *        Uplink/downlink type <br>
 * @param quality   <br>
 *        Probe the quality of the network <br>
 * @param rtt   <br>
 *        Probe the rtt <br> of the network
 * @param lost_rate   <br>
 *        Probe the quality of the network Packet loss rate <br>
 * @param bitrate   <br>
 *        Probes the bandwidth of the network (kbps) <br>
 * @param jitter   <br>
 *        Probes the jitter of the network <br>
 * @notes Receives this callback every 2s after the call startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:{@link #ByteRTCEngineKit#startNetworkDetection:uplinkBandwidth:downlink:downlinkBandwidth:} interface starts probing.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onNetworkDetectionResult:(ByteRTCNetworkDetectionLinkType)type quality:(ByteRTCNetworkQuality)quality rtt:(int)rtt lostRate:(double)lost_rate bitrate:(int)bitrate jitter:(int)jitter;

/** 
 * @type callback
 * @region Pre-call network probing
 * @author hanchenchen.c
 * @brief Pre-call network probing ends <be>
 *        The following will stop detection and receive this primary callback:  <br>
 *        1. This callback is received once when the stopNetworkDetection{@link #ByteRTCEngineKit#stopNetworkDetection} interface is called to stop probing;  <br>
 *        2. Stop detection when the first frame of remote/local audio is received;  <br>
 *        3. Stop detecting when the detection exceeds 3 minutes;  <br>
 *        4. When the probe link is disconnected for a certain period of time, the probe is stopped.
 * @param engine ByteRTCEngineKit object
 * @param err_code   <br>
 *        See ByteRTCNetworkDetectionStopReason{@link #ByteRTCNetworkDetectionStopReason} for reasons of stopping probing.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onNetworkDetectionStopped:(ByteRTCNetworkDetectionStopReason)err_code;

#pragma mark - Subscribe Delegate Methods

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
     didSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

/**
 * @hidden
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
   didUnSubscribe:(NSString * _Nonnull)uid isReconnect:(BOOL)isReconnect;

#pragma mark - Log Delegate Methods
// @name log related callbacks

/** 
 * @hidden
 * @type callback
 * @region Engine management
 * @author chenweiming.push
 * @brief SDK Internal log callbacks. <br>
 *        SDK internal runtime will call back the log to the business side to facilitate troubleshooting.
 * @param engine   <br>
 *        ByteRTCEngineKit object.
 * @param dict   <br>
 *        Log content.
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine log:(NSDictionary* _Nonnull)dict
    __attribute((deprecated("Will be removed in new version")));

#pragma mark Audio Mix Delegate Methods
// @name audio mix callback

/** 
 * @hidden
 * @deprecated Since 325.1, use ByteRTCAudioMixingManager instead
 * @type callback
 * @region  mix
 * @author majun.lvhiei
 * @brief  Music file mix end callback. With this callback, the SDK notifies the application layer of the end of the music file mix.
 * @param engine Current RTC SDK object
 */
- (void)rtcEngineLocalAudioMixingDidFinish:(ByteRTCEngineKit *_Nonnull)engine;

/** 
 * @hidden
 * @deprecated Since 325.1, use ByteRTCAudioMixingManager instead
 * @type callback
 * @region  mix
 * @author majun.lvhiei
 * @brief  Sound file mix end callback. The SDK uses this callback to notify the application layer sound effect file that the mixing ends
 * @param engine  The current RTC SDK object
 * @param soundId  Sound effect ID
 */
- (void)rtcEngineDidAudioEffectFinish:(ByteRTCEngineKit *_Nonnull)engine soundId:(NSInteger)soundId;

/** 
 * @type callback
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Callback when audio mix file playback state changes
 * @param engine Current RTC SDK engine object
 * @param mixId   <br>
 *        Mix ID <br>
 *        Unique ID passed in when using ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager} related interface.
 * @param state   <br>
 *        Mix status <br>
 *        The mix status can be referred to: ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState}.
 * @param error   <br>
 *         Error code <br>
 *         See ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}.
 * @notes   <br>
 *        + The timing of this callback will be triggered is summarized as follows: <br>
 *        + When startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} method is successfully called, the callback with the state value ByteRTCAudioMixingStatePlaying will be triggered; otherwise, the callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} is repeatedly called with the same ID, the latter overrides the previous one, and this callback notifies the previous mix has stopped with ByteRTCAudioMixingStateStopped. <br>
 *        + When the pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} method pauses playback successfully, a callback with the state value ByteRTCAudioMixingStatePaused will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When calling the resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} method to resume playback successfully, a callback with the state value ByteRTCAudioMixingStatePlaying will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + When the stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} method stops playing successfully, a callback with the state value ByteRTCAudioMixingStateStopped will be triggered; otherwise, a callback with the state value ByteRTCAudioMixingStateFailed will be triggered. <br>
 *        + The end of playback triggers a callback with the state value ByteRTCAudioMixingStateFinished.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
   onAudioMixingStateChanged:(NSInteger)mixId state:(ByteRTCAudioMixingState)state error:(ByteRTCAudioMixingError)error;

/** 
 * @type callback
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Callback for playback progress of mixed audio files
 * @param engine Current RTC SDK object
 * @param mixId Mixing ID  <br>
 * @param progress The current playback progress (ms) of the mixed audio file
 * @notes After calling setAudioMixingProgressInterval:interval:{@link #ByteRTCAudioMixingManager#setAudioMixingProgressInterval:interval:} to set the time interval to a value greater than 0, or calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to set the time interval in ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig} to a value greater than 0, the SDK will trigger the callback according to the set time interval.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine
    onAudioMixingPlayingProgress:(NSInteger)mixId progress:(int64_t) progress;

#pragma mark transcoding Delegate Methods
// @name retweet live status callback

#pragma mark Performance Delegate Methods
// @name performance related callbacks

/** 
 * @type callback
 * @region  audio & video fallback
 * @author panjian.fishing
 * @brief Publish performance fallback is not turned on locally. When insufficient device performance is detected, this callback is received.   <br>
 *        Locally turn on the release performance fallback. When the release performance fallback/recovery is caused due to device performance/network reasons, this callback is received. <br>
 * @param mode  Indicates whether the release fallback function is turned on locally. See ByteRTCPerformanceAlarmMode{@link #ByteRTCPerformanceAlarmMode} <br>
 *              + When the publisher does not turn on the release performance fallback, the mode value is ByteRTCPerformanceAlarmModeNormal. <br>
 *              + When the publisher turns on the release performance fallback, the mode value is ByteRTCPerformanceAlarmModeSimulcast.
 * @param roomId   <br>
 *                 + When the release performance fallback is not turned on, the roomId is empty <br>
 *                 + When the release performance fallback is turned on, the roomId is the room ID affected by the alarm.
 * @param reason For alarm reasons. See ByteRTCPerformanceAlarmReason{@link #ByteRTCPerformanceAlarmReason}
 * @param data Performance fallback related data. See ByteRTCSourceWantedData{@link #ByteRTCSourceWantedData}.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onPerformanceAlarmsWithMode:(ByteRTCPerformanceAlarmMode)mode
                         roomId:(NSString *_Nonnull)roomId
                         reason:(ByteRTCPerformanceAlarmReason)reason
               sourceWantedData:(ByteRTCSourceWantedData *_Nonnull)data;

/** 
 * @type callback
 * @region  audio & video rollback
 * @author panjian.fishing
 * @brief Once the Fallback option is set, Fallback or reverting from a Fallback of a media stream will trigger this callback.
 * @param engine Current RTCEngine instance
 * @param event Information of stream switching. Refer to ByteRTCRemoteStreamSwitchEvent{@link #ByteRTCRemoteStreamSwitchEvent} for more details.
 * @notes Call setSubscribeFallbackOption:{@link #ByteRTCEngineKit#setSubscribeFallbackOption:} or configure Fallback options on the server side to register this callback.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine OnSimulcastSubscribeFallback:(ByteRTCRemoteStreamSwitchEvent *_Nonnull)event;

#pragma mark Proxy Delegate Methods
// @name Socks5 and HTTP proxy callbacks

/** 
 * @type callback
 * @region Network proxy
 * @brief HTTP Receive the callback when the proxy connection state changes.
 * @param engine ByteRTCEngineKit object
 * @param state Current HTTP proxy connection status
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onHttpProxyState:(NSInteger)state;

/** 
 * @type callback
 * @region Network proxy
 * @brief HTTPS Receive the callback when the proxy connection state changes.
 * @param engine ByteRTCEngineKit object
 * @param state Current HTTPS proxy connection status
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onHttpsProxyState:(NSInteger)state;

/** 
 * @type callback
 * @region Network proxy
 * @brief SOCKS5 Receive the callback when the proxy state changes.
 * @param engine ByteRTCEngineKit object
 * @param state SOCKS5 proxy connection status
 * @param cmd Every step of the proxy connection operating command
 * @param proxy_address Proxy address information
 * @param local_address Local address used by the current connection
 * @param remote_address Remote connection address
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
    onSocks5ProxyState:(NSInteger)state
                   cmd:(NSString *_Nonnull)cmd
         proxy_address:(NSString *_Nonnull)proxy_address
         local_address:(NSString *_Nonnull)local_address
        remote_address:(NSString *_Nonnull)remote_address;

#pragma mark FileRecording related callback
/** 
 * @type callback
 * @region  local recording
 * @brief  Get local recording status callback.   <br>
 *         The callback is triggered by either startFileRecording:withRecordingConfig:type:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:type:} or stopFileRecording:{@link #ByteRTCEngineKit#stopFileRecording:}.
 * @param engine ByteRTCEngineKit object
 * @param type Stream properties of the recorded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param state Recording status. See ByteRTCRecordingState{@link #ByteRTCRecordingState}
 * @param error_code Recording error code. See ByteRTCRecordingErrorCode{@link #ByteRTCRecordingErrorCode}
 * @param recording_info Recording file details. See ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine
        onRecordingStateUpdate:(ByteRTCStreamIndex)type
                         state:(ByteRTCRecordingState)state
                    error_code:(ByteRTCRecordingErrorCode)error_code
                recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;

/** 
 * @type callback
 * @region  local recording
 * @brief  Local recording progress callback.   <br>
 *        This callback is triggered by startFileRecording:withRecordingConfig:type:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:type:}. When the recording state is normal, the system will prompt the recording progress through this callback every second.
 * @param engine ByteRTCEngineKit object
 * @param type Stream properties of the recorded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param process Recording progress. See ByteRTCRecordingProgress{@link #ByteRTCRecordingProgress}
 * @param recording_info Details of the recorded file. See ByteRTCRecordingInfo{@link #ByteRTCRecordingInfo}
 */
- (void)rtcEngine:(ByteRTCEngineKit* _Nonnull)engine
        onRecordingProgressUpdate:(ByteRTCStreamIndex)type
                          process:(ByteRTCRecordingProgress* _Nonnull)process
                   recording_info:(ByteRTCRecordingInfo* _Nonnull)recording_info;

#pragma mark ForwardStream related callback
    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the state and errors during relaying the media stream to each of the rooms
     * @param engine ByteRTCEngineKit object
     * @param infos Array of the state and errors of each designated room. Refer to ForwardStreamStateInfo{@link #ForwardStreamStateInfo} for more inforamtion.
     */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the media stream to each room
     * @param engine ByteRTCEngineKit object
     * @param infos Array of the event of each designated room. Refer to ForwardStreamEventInfo{@link #ForwardStreamEventInfo} for more information.
     */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;
/** 
 * @type callback
 * @brief Periodical report of network quality
 * @param engine ByteRTCEngineKit object
 * @param localQuality Local network quality. Refer to ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats}.
 * @param remoteQualities Network quality of the subscribed users. Refer to ByteRTCNetworkQualityStats{@link #ByteRTCNetworkQualityStats} for details.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onNetworkQuality:(ByteRTCNetworkQualityStats *_Nonnull)localQuality remoteQualities:(NSArray<ByteRTCNetworkQualityStats*> *_Nonnull)remoteQualities;

/** 
 * @type callback
 * @brief Callback of the result of publishing the public stream<br>
 *        You will be informed of the result of publishing the public stream by this callback after calling startPushPublicStream:withLayout:{@link #ByteRTCEngineKit#startPushPublicStream:withLayout:}.
 * @param engine engine instance
 * @param publicStreamId ID of the public stream
 * @param errorCode Result and status code of publishing the public stream. Refer to ByteRTCTranscodingError{@link #ByteRTCTranscodingError} for more details.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
onPushPublicStreamResult:(NSString *_Nonnull)publicStreamId
        errorCode:(int)errorCode;

/** 
 * @type callback
 * @brief Callback of the result of subscribing to the public stream<br>
 *        You will be informed of the result of subscribing to the public stream by this callback after calling startPushPublicStream:withLayout:{@link #ByteRTCEngineKit#startPushPublicStream:withLayout:}.
 * @param engine engine instance
 * @param publicStreamId ID of the public stream
 * @param errorCode Result and status code of subscribing to the public stream. Refer to ByteRTCTranscodingError{@link #ByteRTCTranscodingError} for more details.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine
onPlayPublicStreamResult:(NSString *_Nonnull)publicStreamId
        errorCode:(int)errorCode;

/** 
 * @type callback
 * @brief Callback of the SEI carried by the public video stream<br>
 *        You will receive SEI by this callback if the public stream published by calling startPlayPublicStream:{@link #ByteRTCEngineKit#startPlayPublicStream:} carrying SEI.
 * @param engine ByteRTCEngineKit instance
 * @param publicStreamId ID of the public stream
 * @param message SEI(supplemental enhancement information) carried by the public video stream
 * @notes  <br>
 *       You will receive SEI from all the video frames if the SEI do not have conflicts.<br>
 *       However, if SEI from video frames have conflicts, you will receive only one of them.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onPublicStreamSEIMessageReceived:(NSString* _Nonnull)publicStreamId andMessage:(NSData* _Nonnull)message;

/** 
 * @type callback
 * @brief Callback of successfully decoding of the first video frame of the public stream<br>
 *        Refer to startPlayPublicStream:{@link #ByteRTCEngineKit#startPlayPublicStream:} for details about subsribing to a public stream.
 * @param engine ByteRTCEngineKit instance
 * @param publicStreamId ID of the public stream
 * @param frameInfo Information of the video stream. Refer to ByteRTCVideoFrameInfo{@link #ByteRTCVideoFrameInfo} for more details.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstPublicStreamVideoFrameDecoded:(NSString * _Nonnull)publicStreamId withFrameInfo:(ByteRTCVideoFrameInfo * _Nonnull)frameInfo;

/** 
 * @type callback
 * @brief Callback of successfully decoding of the first audio frame of the public stream<br>
 *        Refer to startPlayPublicStream:{@link #ByteRTCEngineKit#startPlayPublicStream:} for details about subsribing to a public stream.
 * @param engine ByteRTCEngineKit instance
 * @param publicStreamId ID of the public stream
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onFirstPublicStreamAudioFrame:(NSString * _Nonnull)publicStreamId;
/** 
 * @type callback
 * @brief Receives the callback when you call startCloudProxy:{@link #ByteRTCEngineKit#startCloudProxy:} to start cloud proxy, and the SDK connects the proxy server successfully.
 * @param interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
 */
- (void)rtcEngine:(ByteRTCEngineKit * _Nonnull)engine onCloudProxyConnected:(NSInteger)interval;
/** 
 * @type callback
 * @region Network Management
 * @author qipengxiang
 * @brief Callback about the call test result.
 * @param result Test result, see ByteRTCEchoTestResult{@link #ByteRTCEchoTestResult}.
 * @notes The timing when this callback will be triggered is as follows:  <br>
 *        + A device-related error occured during the test；  <br>
 *        + After a successful test；  <br>
 *        + After stopping the test, provided that the audio/video playback was not received during the test due to non-device reasons.
 */
- (void)rtcEngine:(ByteRTCEngineKit *_Nonnull)engine onEchoTestResult:(ByteRTCEchoTestResult)result;
@end

#pragma mark - ByteRTCEngineKit
/** 
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief SDK  callback to the application layer delegate object. See ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEngineKit : NSObject
/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCEngineDelegate> _Nullable delegate;

/**
 * @hidden
 */
@property (nonatomic, weak) id<ByteRTCMonitorDelegate> _Nullable monitorDelegate
    __deprecated_msg("Will be removed in new version");

#pragma mark Core Methods
// @name core method

/** 
 * @hidden
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief  Create RTCEngine instance. <br>
 *        This method should be used as the first step in the normal SDK process to use the other capabilities of the SDK by creating an RTCEngine instance.
 * @param appId   <br>
 *        A unique device identifier for each application, randomly generated by the VRTC console. Instances generated by different AppIDs are completely independent of each other for audio & video calls in VRTC.
 * @param delegate   <br>
 *        SDK callback to the delegate of the application layer. See ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @return Available ByteRTCEngineKit{@link #ByteRTCEngineKit} instances.
 * @notes   <br>
 *         + This method initializes an RTCEngine singleton on the first call. Unless the destroy{@link #ByteRTCEngineKit#destroy} method is called, all subsequent calls return the same internal instance. <br>
 *         + Calling this method several times in a row will not create a different ByteRTCEngineKit{@link #ByteRTCEngineKit}. This method should be used in pairs with destroy{@link #ByteRTCEngineKit#destroy}. <br>
 *         + You must use the same App ID before you can talk between Apps. <br>
 *         + After calling destroy{@link #ByteRTCEngineKit#destroy}, the ByteRTCEngineKit{@link #ByteRTCEngineKit} instance will be destroyed, and calling the initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} method again will create a brand-new ByteRTCEngineKit{@link #ByteRTCEngineKit} instance.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                                      __deprecated_msg("Will be removed in new version");
/** 
 * @hidden
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief  Create RTCEngine instance. <br>
 *        This method should be used as the first step in the normal SDK process to use the other capabilities of the SDK by creating an RTCEngine instance.
 * @param appId   <br>
 *        A unique device identifier for each application, randomly generated by the VRTC console. Instances generated by different AppIDs are completely independent of each other for audio & video calls in VRTC.
 * @param delegate   <br>
 *        SDK callback to the application-level delegate. See ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param monitorDelegate   <br>
 *        Callback delegate for monitoring information. See ByteRTCMonitor Delegate {@link #ByteRTCMonitor Delegate}
 * @return Available ByteRTCEngineKit{@link #ByteRTCEngineKit} instances.
 * @notes   <br>
 *         + This method initializes an RTCEngine singleton on the first call. Unless the destroy{@link #ByteRTCEngineKit#destroy} method is called, all subsequent calls return the same internal instance. <br>
 *         + Calling this method several times in a row will not create a different ByteRTCEngineKit{@link #ByteRTCEngineKit}. This method should be used in pairs with destroy{@link #ByteRTCEngineKit#destroy}.  <br>
 *         + You must use the same App ID before you can talk between Apps. <br>
 *         + After calling destroy{@link #ByteRTCEngineKit#destroy}, the ByteRTCEngineKit{@link #ByteRTCEngineKit} instance will be destroyed, and calling the initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} method again will create a brand-new ByteRTCEngineKit{@link #ByteRTCEngineKit} instance.
 */
+ (instancetype _Nonnull)sharedEngineWithAppId:(NSString * _Nonnull)appId
                                      delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                               monitorDelegate:(id<ByteRTCMonitorDelegate> _Nullable)monitorDelegate
                               __deprecated_msg("Will be removed in new version");

/** 
 * @hidden
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief Creates an engine instance if no engine instance is created, or get the engine instance if one already exists.
 * @return See ByteRTCEngineKit{@link #ByteRTCEngineKit} object.
 * @notes  <br>
 *      + Call initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} to initialize the engine.  <br>
 *      + Nil is returned if initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} or if the method is called after destroy{@link #ByteRTCEngineKit#destroy} is called.
 */
+ (ByteRTCEngineKit * _Nullable) sharedInstance;

/** 
 * @type api
 * @region Engine Management
 * @author chenweiming.push
 * @brief Create an engine instance.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current thread, calling this API will create one. If an engine instance has been created, calling this API again will create another instance.
 * @param appId A unique identifier for each App, randomly generated by the RTC console. Engine instances created with different AppIds cannot communicate with each other.
 * @param delegate Delegate sent from SDK to App. See ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param parameters Reserved parameter, in JSON string format
 * @return A ByteRTCEngineKit{@link #ByteRTCEngineKit} instance
 * @notes We kindly recommend that you create no more than 2 engine instances on mobile devices.
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
                  parameters:(NSDictionary* _Nullable)parameters;

/** 
 * @hidden
 * @type api
 * @region Engine management
 * @author chenweiming.push
 * @brief Create engine objects. This method should be the first step in the normal SDK process. By creating an engine instance, use the other capabilities of the SDK
 * @param appId The unique device identifier of each application is randomly generated by the VRTC console. Instances generated by different AppIDs make audio & video calls in VRTC
 *               Completely independent and cannot communicate with each other.
 * @param delegate SDK callback to the application layer delegate. See ByteRTCEngineDelegate{@link #ByteRTCEngineDelegate}
 * @param parameters  Reserved parameters
 * @param monitorDelegate   <br>
 *        Callback delegate for monitoring information. See ByteRTCMonitor Delegate {@link #ByteRTCMonitor Delegate}
 * @return Available ByteRTCEngineKit{@link #ByteRTCEngineKit} instances
 * @notes
 *      1. Calling this method several times in a row creates a different ByteRTCEngineKit{@link #ByteRTCEngineKit}
 *      2. You must use the same App ID to make calls between Apps
 */
- (id _Nonnull)initWithAppId:(NSString * _Nonnull)appId
                    delegate:(id<ByteRTCEngineDelegate> _Nullable)delegate
             monitorDelegate:(id<ByteRTCMonitorDelegate> _Nullable)monitorDelegate
                  parameters:(NSDictionary* _Nullable)parameters
                  __deprecated_msg("Will be removed in new version");

/** 
 * @type api
 * @region Engine Management
 * @author chenweiming.push
 * @brief Destroy the engine instance.  <br>
 *        If the current engine instance is created by initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}, then the behavior of this API is consistent with destroy{@link #ByteRTCEngineKit#destroy}.
 * @notes
 *       + Call this API after all business scenarios related to the engine instance are destroyed.  <br>
 *       + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *       + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or wait for the execution of the main thread in the callback and call this API in the main thread at the same time. Otherwise, it will cause a deadlock.
 *       + You can enable ARC for Objective-C, to automatically trigger the destruction logic when the dealloc method is called.
 */
- (void)destroyEngine;

/** 
 * @type api
 * @region Engine Administration
 * @author chenweiming.push
 * @brief Destroys the engine instance created by initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} and releases all related resources.
 * @notes   <br>
 *         + Make sure that this method is called in the last stage of all business scenarios. <br>
 *         + After this method is called, it will destroy all SDK-related memory and stop any interaction with the media server. <br>
 *         + Any settings made to the SDK after the last initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} call,
 *           Will take effect the next time initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} is effectively executed. <br>
 *         + This method is a blocking call, which will block the current thread until the SDK completes the exit logic completely. Therefore, care should be taken not to call this method directly in the callback thread, and care should also be taken not to wait for the execution of the main thread in the callback method while calling this method in the main thread, thus causing deadlock.
 */
+ (void)destroy;

/** 
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief  Gets the current version number of the SDK.
 * @return SDK  The current version number.
 */
+ (NSString * _Nonnull)getSdkVersion;

/** 
 * @hidden
 * @deprecated
 * @type api
 * @region engine management
 * @author chenweiming.push
 * @brief Set the string parameters in the JSON format and configure the RTC engine parameters.
 * @param parameters   <br>
 *        JSON format string parameters.
 * @return   <br>
 *         + 0: Success. <br>
 *         + < 0: Failed.
 * @notes   <br>
 *         + Needs to be called before the engine is initialized.
 */
+ (int)setParameters:(NSString* _Nullable)parameters
    __deprecated_msg("Will be removed in new version");

/** 
 * @hidden
 * @deprecated since 326.1, use setUserVisiblity instead
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief To set the user persona.   <br>
 *        By setting different user personas, you can control the user's behavior in the room: <br>
 *         + Whether audio & video streams can be published; <br>
 *         + Whether the user himself is invisible in the room. <br>
 * @param role  User persona. See ByteRTCUserRoleType{@link #ByteRTCUserRoleType}. <br>
 * @return  Method call result.   <br>
 *          + YES: Success. <br>
 *          + NO: failure <br>
 * @notes   <br>
 *         + Users can call this method to set user persona before and after joining the room. <br>
 *         + In the room, after calling this method to successfully switch roles, other users in the room will receive corresponding callback notifications: <br>
 *            -When Switching from an invisible user to a live streaming host, other users in the room will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}; <br>
 *            -When Switching from a live streaming host to an invisible user , other users in the room will receive rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:}.
 */
- (BOOL)setUserRole:(ByteRTCUserRoleType)role
    __deprecated_msg("Will be removed in new version");
/** 
 * @type api
 * @region Multi-room
 * @author liuzhiqiang
 * @brief Set the visibility of the user in the room. Visible by default.   <br>
 * @param enable  Visibility of the user in the room: <br>
 *         + True: The user can publish media streams. And the other users in the room get informed of the behaviors of the user, such as Joining room, starting video capture, and Leaving room.<br>
 *         + False: The user cannot publish media streams. And the other users in the room do not get informed of the behaviors of the user, such as joining, starting video capture, or leaving.<br>
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: Failure <br>
 * @notes   <br>
 *        + You can call this API whether the user is in a room or not. <br>
 *        + When you call this API, the other users in the room will be informed via the related callback: <br>
 *            - Switch from `false` to `true`: rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}<br>
 *            - Switch from `true` to `false`: rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} <br>
 *        + The invisible user will receive the warning code, `ByteRTCWarningCodeSubscribeStreamForbiden`, when trying to publish media streams.
 */
- (BOOL)setUserVisibility:(BOOL)enable;

/** 
 * @type api
 * @region Multi-room
 * @author wangzhanqiang
 * @brief Synchronizes published audio and video.  <br>
 *        When the same user simultaneously uses separate devices to capture and publish audio and video, there is a possiblity that the streams are out of sync due to the network disparity. In this case, you can call this API on the video publisher side and the SDK will automatically line the video stream up according to the timestamp of the audio stream, ensuring that the audio the receiver hears corresponds to the video the receiver watches.
 * @param audioUserId The ID of audio publisher. You can stop the current A/V synchronization by setting this parameter to null.
 * @return API call result:  <br>
 *        + True: Success  <br>
 *        + False: Failure
 * @notes  <br>
 *        + You can call this API anytime before or after entering the room.  <br>
 *        + The source user IDs of the audio and video stream to be synchronized must be in the same RTC room.  <br>
 *        + When the A/V synchronization state changes, you will receive rtcEngine:onAVSyncStateChange:{@link #ByteRTCEngineDelegate#rtcEngine:onAVSyncStateChange:}.  <br>
 *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
 *        + If you want to change the audio source, call this API again with a new `audioUserId`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
 */
- (BOOL)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;


/** 
 * @hidden
 * @deprecated since 336.1, use publishStream instead.
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief Publish media streams in the current room.
 * @notes  <br>
 *        + Call this API to publish media streams in Multi-room mode. In this mode, the Auto-Publish is disabled by default.  <br>
 *        + An invisible user cannot publish media streams. Call setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to change the visibility of a user.  <br>
 *        + Call publishScreen{@link #RTCEngine#publishScreen} to start screen sharing.
 *        + Call startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:} to forward the published streams to the other rooms.
 *        + After publishing media streams by calling this API, the other users in the room will be informed via rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:}.
 */
- (BOOL)publish;
/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Publishes media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + True: Success  <br>
 *        + False: Failure
 * @notes  <br>
 *        + An invisible user cannot publish media streams. Call setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to change your visibility in the room.  <br>
 *        + Call publishScreen:{@link #ByteRTCEngineKit#publishScreen:} to start screen sharing.  <br>
 *        + Call startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *        + After you call this API, the other users in the room will receive rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *        + Call unpublishStream:{@link #ByteRTCEngineKit#unpublishStream:} to stop publishing streams.
 */
- (BOOL)publishStream:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 336.1, use unpublishStream instead.
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief Stop publishing media streams in the room.
 * @notes   <br>
 *         + In Multi-room mode, call this API to stop publishing media streams after starting by calling publish{@link #ByteRTCEngineKit#publish}. <br>
 *         + After stop publishing media streams by calling this API, the other users in the room will be informed via  rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}.
 */
- (BOOL)unpublish;
/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Stops publishing media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + True: Success  <br>
 *        + False: Failure
 * @notes  <br>
 *         + After calling publishStream:{@link #ByteRTCEngineKit#publishStream:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcEngine:onUserUnPublishStream:type:reason: {@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}
 */
- (BOOL)unpublishStream:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @type api
 * @deprecated since 329.1, no use
 * @region room management
 * @author shenpengliang
 * @brief  Get the current user persona.   <br>
 * @return  Current user persona. See ByteRTCUserRoleType{@link #ByteRTCUserRoleType} enumeration type. <br>
 */
- (ByteRTCUserRoleType)clientRole DEPRECATED_MSG_ATTRIBUTE("no useful");

/** 
 * @hidden
 * @type api
 * @deprecated since 326.1, use joinRoom with RoomConfig instead
 * @region Room Management
 * @author shenpengliang
 * @brief Create/join a room: Create a room when the room does not exist; join the room when the room exists.   <br>
 *        Users in the same room can talk to each other. <br>
 *         User calls sharedEngineWithAppId:delegate:{@link #ByteRTCEngineKit#sharedEngineWithAppId:delegate:} After creating the RTC engine, you need to call this method to join the room implementation to make audio & video calls with other users. <br>
 *        If the user calls this method to join the room, subsequent repeated calls to this method will fail. The user must call leaveRoom{@link #ByteRTCEngineKit#leaveRoom} to exit the current room before joining the next room. <br>
 *         Local users will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} callback notification after calling this method to join the room successfully, and remote users will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} callback notification. <br>
 * @param token  Dynamic key for authenticating the logged-in user. <br>
 *          You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. <br>
 * @param roomId  The room ID added. <br>
 *        The room ID is a non-empty string with a length of less than 128 bytes, and the following character set ranges are supported: <br>
 *             1. 26 capital letters A~ Z. <br>
 *             2. 26 lowercase letters a~ z. <br>
 *             3. 10 numbers 0~ 9. <br>
 *             4. Underline "_", at character "@", minus sign "-". <br>
 * @param roomProfile  Room mode. <br>
 *        You should choose the right room mode according to your business needs. <br>
 *        You must set the room mode before entering the room, and it cannot be changed after entering the room. <br>
 *         For room mode. See ByteRTCRoomProfile{@link #ByteRTCRoomProfile}.
 * @param userInfo  For user information. See ByteRTCUserInfo{@link #ByteRTCUserInfo}. <br>
 * @return  Method call result.   <br>
 *          + 0: Success <br>
 *          + -1: RoomId is empty, failure <br>
 *          + -2: UserId is empty, failure <br>
 * @notes   <br>
 *         + Apps with different App IDs cannot communicate with each other. <br>
 *         + Make sure that the App ID used to generate the Token is the same as the App ID used to create the engine, otherwise it will cause the join room to fail. <br>
 *         + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After successful reconnection, rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} callback notification is received locally. <br>
 *         + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who joined the room later will kick the user who joined the room first out of the room, and the user who joined the room first will receive rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} callback notification, the error type is duplicate login BRERR_DUPLICATE_LOGIN. <br>
 */
- (int)joinRoomByKey:(NSString *_Nullable)token
              roomId:(NSString *_Nonnull)roomId
         roomProfile:(ByteRTCRoomProfile)roomProfile
            userInfo:(ByteRTCUserInfo *_Nonnull)userInfo DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomByKey with roomConfig");
/** 
  * @type api
  * @region Room management
  * @author shenpengliang
  * @brief Create or join a room: create a room when the room does not exist; join the room when the room exists.   <br>
  *        Users in the same room can talk to each other. <br>
  *         Repeated calls of the API after entering the room are invalid. The user must call leaveRoom{@link #ByteRTCEngineKit#leaveRoom} to exit the current room before joining the next room. <br>
  * @param token Dynamic key for authentication of users entering the room. <br>
  *         You must use token to join the room. When debugging, you can use the temporary tokens generated on the console. For official launch, you must generate token on your application server and use the tokens to join the room.<br>
  *         Make sure that the AppID used to generate the token is the same as that used to create the engine, otherwise it will fail to join room. <br>
  * @param roomId  The ID of the room to join. <br>
  *        The string matches the regular expression: `[a-zA-Z0-9_@\-]{1,128}`.
  * @param userInfo See ByteRTCUserInfo{@link #ByteRTCUserInfo}. <br>
  * @param rtcRoomConfig  Sets the room mode and whether to automatically publish or subscribe to the stream. See ByteRTCRoomConfig{@link #ByteRTCRoomConfig}. <br>
  * @return   <br>
  *         + 0: Success. <br>
  *         + -1: Failure. There's invalid parameters in RoomID or userInfo.uid. <br>
  *         + -2: Already in the room. When calling the API call， receiving the value of 0 and not calling leaveRoom{@link #ByteRTCEngineKit#leaveRoom},  value `-2` is returned for further API calls, regardless of whether the roomId and the userInfo are duplicated. <br>
  *         + -3: Failure. Engine not exists. Please create RTC engine first.
  * @notes   <br>
  *        + In the same room with the same App ID, the user ID of each user must be unique. If two users use the same user ID, the former will be kicked out of the room by the latter and receive rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:}.<br>
  *        + You will receive rtcEngine:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomStateChanged:withUid:state:extraInfo:} after joining the room successfully. <br>
  *        + When you call setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to make yourself visible and join the room, the remote users will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}. <br>
  *        + After joining the room, you may lose connection to the server due to poor network conditions. In this case, the SDK will automatically reconnect. After reconnected, you will receive rtcEngine:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomStateChanged:withUid:state:extraInfo:}. If you are visible in the room, the remote users will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}. <br>
  */
- (int)joinRoomByKey:(NSString *_Nullable)token
              roomId:(NSString *_Nonnull)roomId
            userInfo:(ByteRTCUserInfo *_Nonnull)userInfo
       rtcRoomConfig:(ByteRTCRoomConfig *_Nonnull)rtcRoomConfig;


/** 
 *  @hidden
 *  @type api
 *  @deprecated since 328.1, use leaveRoom without block instead
 *  @region Room management
 *  @author shenpengliang
 *  @brief Leave the room.   <br>
 *         The user calls this method to leave the room, end the call process, and release all call-related resources. <br>
 *          After calling the joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} method to join the room, you must call this method to leave the room, otherwise you cannot enter the next room. This method can be called regardless of whether it is currently in the room. Repeated calls to this method have no negative impact. <br>
 *         This method is an asynchronous operation, and the call returns without actually exiting the room. After you actually exit the room, the SDK executes the Block block that was passed in when this method was called. <br>
 *  @param leaveRoomBlock  Block executed after leaving the room. The input parameters of Block are statistics between joining the room and leaving the room. See ByteRTCRoomStats{@link #ByteRTCRoomStats}. <br>
 *  @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 *  @notes   <br>
 *         + After the visible user leaves the room, other users in the room will receive rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:} callback notification. <br>
 *         + If the engine is destroyed immediately after calling this method, the SDK will not be able to execute the Block block passed in as an argument. <br>
 */
- (int)leaveRoom:(void (^_Nullable)(ByteRTCRoomStats *_Nonnull stat))leaveRoomBlock
DEPRECATED_MSG_ATTRIBUTE("Please use leaveRoom");


/** 
  * @type api
  * @region  room management
  * @author shenpengliang
  * @brief  Leave RTC room.   <br>
  *        The user calls this method to leave the RTC room, end the call process, and release all call-related resources. <br>
  *        It is an asynchronous operation, and the call returns without actually exiting the room. When actually exiting the room, you will receive rtcEngine:onLeaveRoomWithStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLeaveRoomWithStats:}. <br>
  * @return   <br>
  *         + 0: Success <br>
  *         + < 0: Failure <br>
  * @notes   <br>
  *        + When visible users leave the room, others in the room will receive rtcEngine:onUserLeave:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserLeave:reason:}. <br>
  *        + If the engine is destroyed immediately after this method is called, you will not receive rtcEngine:onLeaveRoomWithStats:{@link #ByteRTCEngineDelegate#rtcEngine:onLeaveRoomWithStats:}. <br>
  *        + After calling joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join the room, you must call this API to end the call, otherwise you cannot start the next call. You can call this API in or out of the room. Repeated calls cause no negative effect. <br>
  */
- (int)leaveRoom;

/** 
* @type api
* @author shenpengliang
* @brief Update Token. <br>
*        A Token used to join rooms has an expiration time. You will be informed 30 sec before the expiration of the token by onTokenWillExpire:{@link #ByteRTCEngineDelegate#onTokenWillExpire:}. Call this API to renew the Token. Or the user will be removed from the room as the Token expires. <br>
*         If you called joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join a room or reconnected into a room with an invalid Token, it would fail. You would get informed by rtcEngine:onRoomStateChanged:withUid:state:extraInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomStateChanged:withUid:state:extraInfo:}. The error code is the `ERROR_CODE_INVALID_TOKEN` in ByteRTCErrorCode{@link #ByteRTCErrorCode}. Reacquire a token and call this API to renew the token. <br>
* @param token  Valid token.  <br>
*        If the Token is invalid, SDK will emit `ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN` defined in ByteRTCErrorCode{@link #ByteRTCErrorCode}.
* @return  <br>
*          + 0: Success. <br>
*          + < 0: Failure <br>
* @notes  When the Token expired, the user would be removed from the room. And you would get informed of  `ERROR_CODE_EXPIRED_TOKEN` by rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:}. Reacquire a token and call joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} with the token to rejoin the room.
*/
- (int)updateToken:(NSString *_Nonnull)token;

/** 
 * @type api
 * @region  engine management
 * @author chenweiming.push
 * @brief  Get the description text of various error codes and warning codes in the SDK.
 * @param code   <br>
 *        The value obtained by rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} and rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} callbacks,
 *        For details, please refer to ByteRTCWarningCode{@link #ByteRTCWarningCode} and ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 * @return  Description text.
 */
+ (NSString * _Nonnull)getErrorDescription:(NSInteger)code;

#pragma mark Core Audio Methods
// @name audio core method

/** 
 * @type api
 * @region Audio management
 * @author dixing
 * @brief Start internal audio capture. The default is off.   <br>
 *        Internal audio capture refers to: capturing audio using the built-in module.
 *         The local client will be informed via rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} after starting audio capture by calling this API.
 *         The remote clients in the room will be informed of the state change via rtcEngine:onUserStartAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartAudioCapture:} after the visible user starts audio capture by calling this API.
 * @notes   <br>
 *        + To enable a microphone without the user's permission will trigger rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:}.  <br>
 *        + Call stopAudioCapture{@link #ByteRTCEngineKit#stopAudioCapture} to stop the internal audio capture. Otherwise, the internal audio capture will sustain until you destroy the engine instance. <br>
 *        + Once you create the engine instance, you can start internal audio capture regardless of the audio publishing state. The audio stream will start publishing only after the audio capture starts. <br>
 *        + To switch from custom to internal audio capture, stop publishing before disabling the custom audio capture module by calling disableExternalAudioDevice{@link #ByteRTCEngineKitdisableExternalAudioDevice} and then call this API to enable the internal audio capture.<br>
 */
- (void)startAudioCapture;

 /** 
  * @type api
  * @region audio management
  * @author dixing
  * @brief Stop internal audio capture. The default is off.   <br>
  *        Internal audio capture refers to: capturing audio using the built-in module.
  *        The local client will be informed via rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} after stopping audio capture by calling this API.<br>
  *         The remote clients in the room will be informed of the state change via rtcEngine:onUserStopAudioCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopAudioCapture:} after the visible client stops audio capture by calling this API.<br>
  * @notes   <br>
  *        + Call startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} to enable the internal audio capture. <br>
  *        + Without calling this API the internal audio capture will sustain until you destroy the engine instance.<br>
  */
- (void)stopAudioCapture;

/** 
 * @type api
 * @region Audio management
 * @author dixing
 * @brief Sets the audio scenarios.   <br>
 *        You can choose the appropriate audio scenario according to your application. <br>
 *        After selecting the audio scenario, SDK will automatically select the call/media volume, according to the client-side audio device and status. <br>
 *        You can call this API before or after joining room.
 * @param audioScenario  Audio scenarios. See ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}.
 * @notes   <br>
 *         + Call volume is more suitable for calls, meetings and other scenarios that demand information accuracy. Call volume will activate the system hardware signal processor, making the sound clearer. The volume cannot be reduced to 0. <br>
 *         + Media volume is more suitable for entertainment scenarios, which require musical expression. The volume can be reduced to 0.
 */
- (void)setAudioScenario:(ByteRTCAudioScenarioType)audioScenario;

/** 
 * @type api
 * @region audio management
 * @author dixing
 * @brief Sets the sound quality gear. You should choose the appropriate sound quality gear according to the needs of the business scenario.   <br>
 * @param audioProfile  Sound quality gear. See ByteRTCAudioProfileType{@link #ByteRTCAudioProfileType}
 * @notes   <br>
 *         + This method can be called before and after entering the room; <br>
 *         + Support dynamic switching of sound quality gear during a call.
 */
- (void)setAudioProfile:(ByteRTCAudioProfileType)audioProfile;

/** 
 * @type api
 * @region American Voice Effect Management
 * @author luomingkang
 * @brief Set the sound change effect type
 * @param voiceChanger The sound change effect type. See ByteRTCVoiceChangerType{@link #ByteRTCVoiceChangerType}
 * @notes   <br>
 *         + Can be set before and after entering the room. <br>
 *         + Is effective for both internally captured and custom captured audio from the RTC SDK. <br>
 *         + Only valid for mono audio. <br>
 *         + Is only valid in SDKs that include the ability of American sound effects. <br>
 *         + Is mutually exclusive with setVoiceReverbType:{@link #setVoiceReverbType:}, and the effects set later will override the effects set first. <br>
 */
- (void)setVoiceChangerType:(ByteRTCVoiceChangerType)voiceChanger;

/** 
 * @type api
 * @region Bel Sound Effect Management
 * @author luomingkang
 * @brief Set the reverb effect type
 * @param voiceReverb Reverb effect type. See ByteRTCVoiceReverbType{@link #ByteRTCVoiceReverbType}
 * @notes   <br>
 *         + Can be set before and after entering the room. <br>
 *         + Is effective for both internally captured and custom captured audio from the RTC SDK. <br>
 *         + Only valid for mono audio. <br>
 *         + Is only valid in SDKs that include the ability of American sound effects. <br>
 *         + Is mutually exclusive with setVoiceChangerType:{@link #setVoiceChangerType:}, and the effects set later will override the effects set first. <br>
 */
- (void)setVoiceReverbType:(ByteRTCVoiceReverbType)voiceReverb;

/** 
 * @hidden
 * @deprecated since 336.1, use unpublishStream and publishStream instead.
 * @type api
 * @region Media Stream Management
 * @author shenpengliang
 * @brief Enable/ Disable the transmission of the local audio stream.   <br>
 *        Remote users in the room will be informed via rtcEngine:onUserMuteAudio:muteState:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMuteAudio:muteState:} after the visible user changes the transmission state of the audio streams by calling this API.
 * @param muteState An identifier denoting whether the local audio stream is sending. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details.
 * @notes <br>
 *        + Calling this API toggles the transmission state of the local audio streams instead of the capture state.
 *        + You can enable audio transmission regardless of the audio capture state. Enable the transmission before capture, thus the audio stream can be sent once the capture starts.
 */
- (void)muteLocalAudio:(ByteRTCMuteState)muteState;


/** 
 * @hidden
 * @deprecated since 326.1, use SubscribeUserStream instead
 * @type api
 * @region Media Stream Management
 * @author shenpengliang
 * @brief  To set the reception status of the audio stream from the specified remote user. The default is receive.
 * @param uid  Specify the ID
 * @param muteState  Reception status of the remote user to identify whether the remote audio stream is received. See ByteRTCMuteState{@link #ByteRTCMuteState}
 */
- (void)muteRemoteAudio:(NSString * _Nonnull)uid muteState:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region Media Stream Management
 * @author shenpengliang
 * @brief To set the reception status for all audio streams from the remote. The default is receive.
 * @param muteState Receive status to identify whether the remote audio stream is received. For details. See ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes This method only affects whether the remote audio stream is received locally, and does not affect the collection and transmission function of the remote audio device.
 */
- (void)muteAllRemoteAudio:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Pause receiving remote media streams.
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @notes   <br>
 *         + Calling this API does not change the capture state and the transmission state of the remote clients. <br>
 *         + Calling this API does not cancel the subscription or change any subscription configuration. <br>
 *         + To resume, call resumeAllSubscribedStream:{@link #ByteRTCEngineKit#resumeAllSubscribedStream:}.
 */
- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Resume receiving remote media streams
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @notes  <br>
 *         + Calling this API does not change the capture state and the transmission state of the remote clients.
 *         + Calling this API does not change any subscription configuration.
 */
- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @hidden
 * @deprecated Since 325.1, use enableAudioPropertiesReport instead
 * @type api
 * @region audio management
 * @author wangjunzheng
 * @brief To turn on/off volume prompts. Off by default. <br>
 *         When the volume prompt is turned on, you will receive a callback of the volume information of the remote user who collected the volume locally or subscribed at the set time interval.
 *         For specific information about the callback. See rtcEngine:onAudioVolumeIndication:totalRemoteVolume:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioVolumeIndication:totalRemoteVolume:}.
 * @param interval The time interval between receiving the volume prompt callback <br>
 *                 + ≤ 0: Disable the volume prompt function. <br>
 *                 + > 0: Enable the volume prompt function and set the time interval for receiving the volume prompt callback. In milliseconds. <br>
 *                 It is recommended to set to greater than or equal to 200 milliseconds; when less than 10 milliseconds, the behavior is undefined.
 */
- (void)setAudioVolumeIndicationInterval:(NSInteger)interval;

/** 
 * @hidden
 * @deprecated since 323.1, use setCaptureVolume instead
 * @type api
 * @region Audio Management
 * @author wangjunzheng
 * @brief Adjust the audio acquisition volume.
 * @param volume Audio acquisition volume, value range: [0,400] <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: maximum can be 4 times the original volume (with overflow protection) <br>
 * @notes To ensure better call quality, it is recommended to set the volume value Is [0,100].
 */
- (void)setRecordingVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use setCaptureVolume");

/** 
 * @type api
 * @region Audio Management
 * @author wangjunzheng
 * @brief Adjust the audio acquisition volume
 * @param index Index of the stream, whose volume needs to be adjusted. Refer to ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for more details.
 * @param volume Ratio of capture volume to original volume. Ranging: [0,400]. Unit: %
 *        + 0: Mute <br>
 *        + 100: Original volume. To ensure the audio quality, we recommend [0, 100].
 *        + 400: Four times the original volume with signal-clipping protection.
 * @notes  Call this API to set the volume of the audio capture before or during the audio capture.
 */
- (void)setCaptureVolume:(ByteRTCStreamIndex)index volume:(int)volume;

/** 
 * @type api
 * @region audio management
 * @author dixing
 * @brief Adjust the playback volume of the mixed remote audios.
 * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
 *        To ensure the audio quality, we recommend setting the volume within `100`.  <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: Four times the original volume with signal-clipping protection.
 */
- (void)setPlaybackVolume:(NSInteger)volume;

/** 
 * @type api
 * @region Audio management
 * @author wangjunzheng
 * @brief Enable audio information prompts.   <br>
 * @param config See ByteRTCAudioPropertiesConfig{@link #ByteRTCAudioPropertiesConfig}.
 * @notes  <br>
 *        With the prompt on, you can:  <br>
 *       + Get the information of the audio stream captured by the local microphone and screen audio stream through rtcEngine:onLocalAudioPropertiesReport:{@link #ByteRTCEngineDelegate#rtcEngine:onLocalAudioPropertiesReport:}.  <br>
 *       + Get the information of the subscribed remote audio streams through rtcEngine:onRemoteAudioPropertiesReport:totalRemoteVolume:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteAudioPropertiesReport: totalRemoteVolume:}.
 */
- (void)enableAudioPropertiesReport:(ByteRTCAudioPropertiesConfig* _Nonnull)config;

/** 
 * @type api
 * @region Audio management
 * @author dixing
 * @brief Turn on/off the earphone monitor function
 * @param mode Whether to turn on the earphone monitor function. See ByteRTCEarMonitorMode{@link #ByteRTCEarMonitorMode}
 * @notes  <br>
 *         + You must use the earphone monitor function when using the internal audio capture function provided by the RTC SDK. <br>
 *         + The earphone monitoring function is only effective when a wired earphone is connected. <br>
 *         + Limited by iOS platform, RTC only supports software earphone monitoring.
 */
- (void)setEarMonitorMode:(ByteRTCEarMonitorMode)mode;

/** 
 * @type api
 * @region Audio Management
 * @author dixing
 * @brief Set the volume of the earphone monitor
 * @param volume The volume of the earphone monitor, the value range: [0,100], the unit:%
 * @notes  <br>
 *         + Before setting the volume of the earphone monitor, you must first call setEarMonitorMode:{@link #setEarMonitorMode:} to turn on the earphone monitor function. <br>
 *         + The earphone monitor function is only effective when the internal audio capture function provided by the RTC SDK is used and a wired earphone is connected. <br>
 */
- (void)setEarMonitorVolume:(NSInteger)volume;

/** 
 * @type api
 * @region Audio Mixing
 * @author wangjunzheng
 * @brief Change local voice to a different key, mostly used in Karaoke scenarios.  <br>
 *        You can adjust the pitch of local voice such as ascending or descending with this method.
 * @param pitch The value that is higher or lower than the original local voice within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
 *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
 *        Out of the value range, the setting fails and triggers rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} callback, indicating `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` for invalid value setting with ByteRTCWarningCode{@link #ByteRTCWarningCode}.
 */
- (void)setLocalVoicePitch:(NSInteger)pitch;
/** 
 * @type api
 * @region Audio Management
 * @author majun.lvhiei
 * @brief Enables/disables the loudness equalization function.  <br>
 *        If you call this API with the parameter set to True, the loudness of user's voice will be adjusted to -16lufs. If then you also call setAudioMixingLoudness:loudness:{@link #ByteRTCAudioMixingManager#setAudioMixingLoudness:loudness:} and import the original loudness of the audio data used in audio mixing, the loudness will be adjusted to -20lufs when the audio data starts to play.
 * @param enable Whether to enable loudness equalization funcion:  <br>
 *        + True: Yes <br>
 *        + False: No
 * @notes You must call this API before starting to play the audio file with startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */
- (void)enableVocalInstrumentBalance:(BOOL)enable;
/** 
 * @type api
 * @region Audio Management
 * @author majun.lvhiei
 * @brief Enables/disables the playback ducking function. This function is usually used in scenarios such as "Watch Videos Together".  <br>
 *        With the function on, if remote voice is detected, the local media volume will be lowered to ensure the clarity of the remote voice. If remote voice disappears, the local media volume restores.
 * @param enable Whether to enable playback ducking:  <br>
 *        + True: Yes  <br>
 *        + False: No
 */
- (void)enablePlaybackDucking:(BOOL)enable;
#pragma mark Core Video Methods
// @name video core method

/** 
 * @type api
 * @region Custom Video Capturing & Rendering
 * @author sunhang.io
 * @brief Binds the local video stream to a custom renderer.
 * @param index Video stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param requiredFormat Video frame encoding format that applys to custom rendering. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}.
 * @notes  <br>
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
 *        + Joining or leaving the room will not affect the binding state. <br>
 *        + If you need to unbind the video stream from the custom render, you must set videoSink to `null`.  <br>
 *        + You should call this API before joining the room, and after receiving rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:} which reports that the first local video frame has been successfully captured.
 */
- (void)setLocalVideoSink:(ByteRTCStreamIndex)index
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;

/** 
 * @type api
 * @region Custom Video Capturing & Rendering
 * @author sunhang.io
 * @brief Binds the remote video stream to a custom renderer.
 * @param streamKey Remote stream information which specifys the source and type of the video stream to be rendered. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoSink Custom video renderer. See ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}.
 * @param requiredFormat Encoding format that applys to the custom renderer. See ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat}.
 * @notes  <br>
 *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
 *        + Joining or leaving the room will not affect the binding state. <br>
 *        + This API can be called before and after entering the room. To call before entering the room, you need to get the remote stream information before joining the room; if you cannot get the remote stream information in advance, you can call the API after joining the room and getting the remote stream information via rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:}.
 *        + If you need to unbind the remote stream from the renderer, you must set videoSink to null.
 */
- (void)setRemoteVideoSink:(ByteRTCRemoteStreamKey* _Nonnull)streamKey
                withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
         withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;

/** 
 * @hidden
 * @deprecated since 325.1, use setLocalVideoSink instead
 * @type api
 * @region  to customize video capture rendering
 * @author sunhang.io
 * @brief  To set the local video external renderer.
 * @param videoRenderer External renderer, specifically ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
DEPRECATED_MSG_ATTRIBUTE("Please use setLocalVideoSink");

/** 
 * @hidden
 * @deprecated since 325.1, use setLocalVideoSink instead
 * @type api
 * @region  to customize video capture rendering f
 * @author sunhang.io
 * @brief  To set the local video external renderer.
 * @param videoRenderer  External renderer, specifically referring to ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate}
 * @param roomId  Room ID
 * @param userId  User ID
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)setLocalVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                   forRoomId:(NSString * _Nonnull)roomId
                   forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setLocalVideoSink");

/** 
 * @hidden
 * @deprecated since 325.1, use setRemoteVideoSink instead
 * @type api
 * @region to customize video capture rendering
 * @author sunhang.io
 * @brief To set the external renderer for the video stream from the specified remote user. <br>
 *         Set videoRenderer to null if you need to unbind the remote video stream and the external renderer.
 * @param videoRenderer External video renderer. See ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param roomId Room ID
 * @param userId Remote user ID
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forRoomId:(NSString * _Nonnull)roomId
                    forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setRemoteVideoSink");

/** 
 * @hidden
 * @deprecated since 325.1, use setRemoteVideoSink instead
 * @type api
 * @region to customize video capture rendering
 * @author sunhang.io
 * @brief To set the external renderer for the video stream from the specified remote user.
 * @param videoRenderer External video renderer. See ByteRTCVideoSinkProtocol{@link #ByteRTCVideoSinkProtocol}
 * @param userId Remote user ID
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)setRemoteVideoRenderer:(id<ByteRTCVideoSinkProtocol> _Nullable)videoRenderer
                    forUserId:(NSString * _Nonnull)userId
DEPRECATED_MSG_ATTRIBUTE("Please use setRemoteVideoSink");

/** 
 * @hidden
 * @deprecated since 329.1, use setVideoEncoderConfig instead
 * @type api
 * @hidden
 * @region Video Management
 * @author panjian.fishing
 * @brief Start pushing multiple video streams and set the video parameters when pushing multiple streams,
 *        Including resolution, frame rate, bit rate, zoom mode, fallback strategy when the network is poor, etc.
 * @param videoSolutions  The first address of the video parameter array. See ByteRTCVideoSolution{@link #ByteRTCVideoSolution}. <br>
 *                        Up to 3 parameters are supported. When multiple parameters are set, the resolution must be sequentially reduced, arranged from large to small. <br>
 *                        There is no limit to the maximum resolution. However, if the set resolution cannot be encoded, the encoding push stream will fail.
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 * @notes  <br>
 *         + When using internal capture, the resolution and frame rate of video capture will be adapted according to encoding parameters. <br>
 *         + The default video encoding parameters are: resolution 640px × 360px, frame rate 15fps. <br>
 *         + Changing the encoding resolution takes effect immediately, which may cause the camera to restart.
 */
- (int)setVideoEncoderConfig:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;


/** 
 * @hidden
 * @deprecated since 336, using setRemoteVideoConfig:remoteVideoConfig: instead
 * @type api
 * @region Video management
 * @author wangzhanqiang
 * @brief  Sets the video encoder configuration of each individual stream for simulcasting, including resolution, frame rate, bitrate, scale mode, fallback strategy under poor network conditions, etc.
 * @param  Stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param videoSolutions Video parameters of each individual stream for simulcasting. See ByteRTCVideoSolution{@link #ByteRTCVideoSolution}. <br>
 *                        The length of `videoSolutions` is no more than 4. The resolutions must be in descending sort. <br>
 *                        The maximum resolution is 4096px × 4096px. If the resolution exceeds the limit or the video cannot be encoded, the simulcasting will fail.
 * @return   <br>
 *         + 0: Success <br>
 *         +! 0: Failure <br>
 * @notes   <br>
 *        + When using the internal capture, the resolution and frame rate will be adapted to the maximum resolution and frame rate for encoding. <br>
 *        + The video streams are encoded by default with resolution of 640px × 360px and frame rate of 15fps. <br>
 *        + When you call this API, it will take effect immediately, which may cause the camera to restart. <br>
 *        + The screen stream takes the first set of parameters.
 */
- (int)setVideoEncoderConfig:(ByteRTCStreamIndex)streamIndex config:(NSArray <ByteRTCVideoSolution *> * _Nullable)videoSolutions;
/** 
 * @type api
 * @region Video Management
 * @author zhaomingliang
 * @brief Enables/Disables the mode of publishing multiple video streams with different encoding configuration.
 * @param enabled Whether to enable the mode of publishing multiple video streams:  <br>
 *        + True: Yes  <br>
 *        + False: No(Default setting)
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + <0: Failure
 * @notes <br>
 *        + You should call this API  <br>
 *            - before entering the room, or  <br>
 *            - after entering the room but before publishing streams  <br>
 *        + After setting this API to "True", you can call SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} to set encoding configuration for each stream.  <br>
 *        + If this function is off, or if this function is on but you don't set the configuraion of any stream, only one stream will be sent with a resolution of 640px × 360px and a frame rate of 15fps.
 */
- (int) enableSimulcastMode:(BOOL) enabled;
/** 
 * @type api
 * @region Video Management
 * @author zhaomingliang
 * @brief Sets your expected configuration of the remote video stream that you want to subscribe to or have subscribed to.
 * @param userId The ID of the target stream publisher
 * @param remoteVideoConfig Your expected configuration, see ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}.
 * @notes <br>
 *        + This API only works after the publisher calls enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} to enable publishing multiple video streams, in which case the subscriber will receive the stream from the publisher that is closest to the set configuration;  otherwise the subscriber will only receive one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + If you don't call this API after the publisher enables the function of publishing multiple streams, you will receive by default the video stream with the largest resolution set by the publisher.  <br>
 *        + You should call this API in the room. If you want to call it before entering the room, you should set the `remoteVideoConfig` in the `rtcRoomConfig` when calling joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}.  <br>
 *        + You can call this API anytime before or after subscribing to the target stream. If you have already subscribed to the target stream when calling this API, your settings will take effect when you resubscribe to this stream.  <br>
 *        + SDK will automatically select the stream to be published or subcribed based on the settings of both sides.
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;

/**
 * {en}
 * @type api
 * @region Video Management
 * @author zhaomingliang
 * @brief Video publisher call this API to set the parameters of the maximum resolution video stream that is expected to be published, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
 *        You can only set configuration for one stream with this API. If you want to set configuration for multiple streams, Call SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:}.
 * @param max_solution The maximum video encoding parameter. See ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}.
 * @return  API call result: <br>
 *        + 0: Success <br>
 *        + ! 0: Failure <br>
 * @notes  <br>
 *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:}, SDK will automatically adjust the number of streams published and the parameters of each published stream according to the settings of subscribers. Up to 4 streams will be published, and the resolution you set in this API will be considered as the largest resolution among these 4 streams.  <br>
 *        + Without calling this API, SDK will only publish one stream for you with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + This API is applicable to the video stream captured by the camera, see SetScreenVideoEncoderConfig:{@link #ByteRTCEngineKit#SetScreenVideoEncoderConfig:} for setting parameters for screen sharing video stream.
 */
- (int)SetMaxVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) max_solution;
/** 
 * @type api
 * @region Video Management
 * @author zhaomingliang
 * @brief Video publisher call this API to set the configurations of each stream published, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
 * @param channel_solutions List of configurations for multiple streams. You can set parameters for up to 3 streams, SDK will always take the value of the first 3 streams when parameters for more streams are set.
 *        You should note that the resolution you set is the maximum resolution of each stream, and must be arranged from largest to smallest. See ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}.
 * @return  API call result: <br>
 *        + 0: Success <br>
 *        + ! 0: Failure <br>
 * @notes  <br>
 *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:}, SDK will publish streams as you set, otherwise only the stream with the largest resolution you set will be published.  <br>
 *        + Without calling this API to set parameters for multiple video streams, the SDK only publishes one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
 *        + After setting parameters for multiple video streams, SDK will automatically match the streams to be published based on the desired subscription parameters set by subscribers.  <br>
 *        + This API is applicable to the video stream captured by the camera, see SetScreenVideoEncoderConfig:{@link #ByteRTCEngineKit#SetScreenVideoEncoderConfig:} for setting parameters for screen sharing video stream.
 */
-(int)SetVideoEncoderConfig:(NSArray <ByteRTCVideoEncoderConfig *> * _Nullable) channel_solutions;
/** 
 * @type api
 * @region Screen Shareing Management
 * @author zhaomingliang
 * @brief Video publisher call this API to set the expected configurations for the screen sharing video stream, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
 * @param screen_solution You expected configurations for screen sharing video stream. See ByteRTCVideoEncoderConfig{@link #ByteRTCVideoEncoderConfig}.
 * @return  API call result: <br>
 *        + 0: Success <br>
 *        + ! 0: Failure <br>
 * @notes Without calling this API, the default encoding parameters for screen sharing video streams are: resolution 1920px × 1080px, frame rate 15fps.
 */
-(int)SetScreenVideoEncoderConfig:(ByteRTCVideoEncoderConfig * _Nullable) screen_solution;

/** 
 * @type api
 * @region  Video Management
 * @author wangcheng.leo
 * @brief  Set the video capture parameters for internal capture of the RTC SDK. <br>
 *         If your project uses the SDK internal capture module, you can specify the video capture parameters including preference, resolution and frame rate through this interface.
 * @param captureConfig  Video capture parameters. See: ByteRTCVideoCaptureConfig{@link #ByteRTCVideoCaptureConfig}.
 * @return   <br>
 *         + 0: Success; <br>
 *         + < 0: Failure; <br>
 * @notes   <br>
 *  + This interface can be called after the engine is created and takes effect immediately after being called. It is recommended to call this method before startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture}.
 *  + It is recommended that different Engines on the same device use the same video capture parameters.
 *  + If you use the internal module to start video capture before calling this interface, the capture parameters default to Auto.
 */
- (int)setVideoCaptureConfig:(ByteRTCVideoCaptureConfig * _Nullable)captureConfig;

/** 
 * @type api
 * @region Video Management
 * @author sunhang.io
 * @brief Sets the view to be used for local video rendering and the rendering mode.  <br>
 * @param streamIndex Video stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param canvas View information and rendering mode. See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.
 * @return   <br>
 *         + 0: Success <br>
 *         + -1: Failure <br>
 * @notes  <br>
 *       + You should bind your stream to a view before joining the room. This setting will remain in effect after you leave the room. <br>
 *       + If you need to unbind the local video stream from the current view, you can call this API and set the videoCanvas to `null`.
 */
- (int)setLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;

/** 
 * @type api
 * @region  video management
 * @author wangfujun.911
 * @brief Update the render mode and background color of local video rendering.
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param renderMode See ByteRTCRenderMode{@link #ByteRTCRenderMode}.
 * @param backgroundColor See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor.
 * @return   <br>
 *         + 0: Success <br>
 *         + -1: Failure. VideoCanvas is null. <br>
 * @notes Calling this API during local video rendering will be effective immediately.
 */
- (int)updateLocalVideoCanvas:(ByteRTCStreamIndex)streamIndex
                withRenderMode:(ByteRTCRenderMode)renderMode
          withBackgroundColor:(NSUInteger)backgroundColor;

/** 
 * @type api
 * @region Custom Video Capturing & Rendering
 * @author sunhang.io
 * @brief Sets the view and rendering mode to use when rendering a video stream from a specified remote user uid. <br>
 *         If you need to unbind the video view, set canvas to empty.
 * @param uid  Remote user ID of the video source
 * @param streamIndex  Video stream properties. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param canvas  View information and rendering mode. See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 * @notes   <br>
 *        + Call this API after receiving rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:} or rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:}.
 *         The difference between these two callbacks is that if the video recording function is enabled, the video recording service will join the room as a dumb client side, so the other users will receive rtcEngine:onUserJoined:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onUserJoined:elapsed:}, rather than rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:}. <br>
 *       + When the local user leaves the room, the setting will be invalid. The remote user leaving the room does not affect the setting.
 */
- (int)setRemoteVideoCanvas:(NSString * _Nonnull)uid
                  withIndex:(ByteRTCStreamIndex)streamIndex
             withCanvas:(ByteRTCVideoCanvas * _Nullable)canvas;
/** 
 * @type api
 * @region Video management
 * @author wangfujun.911
 * @brief Update the render mode and background color of remote video rendering
 * @param roomid room ID
 * @param uid User ID
 * @param streamIndex See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param renderMode See RByteRTCRenderMode{@link #ByteRTCRenderMode}.
 * @param backgroundColor See ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas}.backgroundColor，
 * @notes Calling this API during remote video rendering will be effective immediately.
 */
- (int)updateRemoteStreamVideoCanvas:(NSString * _Nonnull)roomid
                withUserId:(NSString * _Nonnull)uid
                withIndex:(ByteRTCStreamIndex)streamIndex
                withRenderMode:(ByteRTCRenderMode)renderMode
                withBackgroundColor:(NSUInteger)backgroundColor;
 /** 
  * @type api
  * @region Video Management
  * @author zhangzhenyu.samuel
  * @brief Enable internal video capture immediately. The default setting is off.   <br>
  *        Internal video capture refers to: capturing video using the built-in module.
  *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after starting video capture by calling this API.
  *        The remote clients in the room will be informed of the state change via rtcEngine:onUserStartVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStartVideoCapture:} after the visible client starts video capture by calling this API.<br>
  * @notes   <br>
  *        + Call stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} to stop the internal video capture. Otherwise, the internal video capture will sustain until you destroy the engine instance.<br>
  *        + Once you create the engine instance, you can start internal video capture regardless of the video publishing state. The video stream will start publishing only after the video capture starts. <br>
  *        + To switch from custom to internal video capture, stop publishing before disabling the custom video capture module and then call this API to enable the internal video capture.<br>
  *        + Call switchCamera:{@link #ByteRTCEngineKit#switchCamera:} to switch the camera used by the internal video capture module.<br>
  *        + Since the upgrade in v3.37.0, to start capture by calling this API, you need to request the capture permission in your App.
  */
- (void)startVideoCapture;

 /** 
  * @type api
  * @region Video Management
  * @author zhangzhenyu.samuel
  * @brief Disable internal video capture immediately. The default is off.  <br>
  *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
  *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after stopping video capture by calling this API.<br>
  *        The remote clients in the room will be informed of the state change via rtcEngine:onUserStopVideoCapture:{@link #ByteRTCEngineDelegate#rtcEngine:onUserStopVideoCapture:} after the visible client stops video capture by calling this API.<br>
  * @notes   <br>
  *        + A call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to enable the internal video capture. <br>
  *        + Without calling this API the internal video capture will sustain until you destroy the engine instance.
  */
- (void)stopVideoCapture;

/** 
 * @hidden
 * @deprecated since 336.1, use unpublishStream and publishStream instead.
 * @type api
 * @region  video management
 * @author zhushufan.ref
 * @brief Enable/ Disable the transmission of the local video stream.  The video stream is not sending by default.<br>
 *        Call this API to start sending local video streams when using either internal capture module or custom video source. <br>
 *         Remote users in the room will be informed via rtcEngine:onUserMuteVideo:withMuteState:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMuteVideo:withMuteState:} after the visible user changes the transmission state of the video streams by calling this API.
 * @param mute_state An identifier denoting whether the local video stream is sending. Refer to ByteRTCMuteState{@link #ByteRTCMuteState} for more details. <br>
 * @notes  <br>
 *         + Calling this API toggles the transmission state of the local video streams instead of the capture state.
 *         + You can enable video transmission regardless of the video capture state. Enable the transmission before capture, thus the video stream can be sent once the capture starts.
 */
- (void)muteLocalVideo:(ByteRTCMuteState)mute_state;

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region Media Stream Management
 * @author shenpengliang
 * @brief Set whether to play the remote video stream
 * @param uid The remote user ID of the video source
 * @param muteState Playback status to identify whether to play the remote video stream. See ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)muteRemoteVideo:(NSString * _Nonnull)uid
                        withMuteState:(ByteRTCMuteState)muteState DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
 * @type api
 * @region Media Stream Management
 * @author shenpengliang
 * @brief Set whether to play all remote video streams
 * @param muteState Play status to identify whether to play remote video streams. See ByteRTCMuteState{@link #ByteRTCMuteState}
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)muteAllRemoteVideo:(ByteRTCMuteState)muteState
DEPRECATED_MSG_ATTRIBUTE("Please use pauseAllSubscribedStream or resumeAllSubscribedStream");

/** 
 * @hidden
 * @deprecated Since 329.1, use setLocalVideoMirrorType instead
 * @type api
 * @region Video Management
 * @author wangjunlin.3182
 * @brief Set whether to turn on mirror mode when front-facing camera capture is used. The default is off.  <br>
 * @param mode Whether to turn on mirror mode. See ByteRTCMirrorMode{@link #ByteRTCMirrorMode}
 * @return   <br>
 *          + 0: Success <br>
 *          + < 0: Failure <br>
 */
- (int)setLocalVideoMirrorMode:(ByteRTCMirrorMode) mode;

/** 
 * @type api
 * @region Video management
 * @author wangjunlin.3182
 * @brief  Sets the mirror mode for the captured video stream.
 * @param mirrorType Mirror type. See ByteRTCMirrorType{@link #ByteRTCMirrorType}.
 * @notes  <br>
 *         + Switching video streams does not affect the settings of the mirror type. <br>
 *         + This API is not applicable to screen-sharing streams. <br>
 *         + Before you call this API, the initial states of each video stream are as follows: <br>
 *         <table>
 *            <tr><th></th><th>Front-facing camera</th><th>Back-facing camera</th><th>Custom capturing</th><th>Built-in camera</th></tr>
 *            <tr><td>Mobile device</td><td>The preview is mirrored. The published video stream is not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>The preview and the published video stream are not mirrored.</td><td>/</td></tr>
 *            <tr><td>PC</td><td>/</td><td>/</td><td>The preview and the published video stream are not mirrored.</td><td>The preview is mirrored. The published video stream is not mirrored.</td></tr>
 *         </table>
 */
- (int)setLocalVideoMirrorType:(ByteRTCMirrorType) mirrorType;

/** 
 * @type api
 * @brief Set the orientation of the video capture. By default, the App direction is used as the orientation reference.<br>
 *        During rendering, the receiving client rotates the video in the same way as the sending client did.<br>
 * @param rotationMode Rotation reference can be the orientation of the App or gravity. Refer to ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode} for details.
 * @return <br>
 *        + 0: Success
 *        + <0: Failure
 * @notes <br>
 *        + The orientation setting is effective for internal video capture only. That is, the orientation setting is not effective to the custom video source or the screen-sharing stream.
 *        + If the video capture is on, the setting will be effective once you call this API. If the video capture is off, the setting will be effective on when capture starts.
 */
- (int)setVideoRotationMode:(ByteRTCVideoRotationMode) rotationMode;

/** 
 * @type api
 * @region Audio & Video Processing
 * @author wangjunlin.3182
 * @brief Enables/Disables basic beauty effects.
 * @param enable Whether to enable basic beauty effects. <br>
 *        + true: Enables basic beauty effects. <br>
 *        + false: (Default) Disables basic beauty effects. <br>
 * @return  <br>
 *        + 0: Success. <br>
 *        + 1000: The Effect SDK is not integrated. <br>
 *        + 1001: This API is not available for your current RTC SDK. <br>
 *        + 1002: This API is not available for your current Effect SDK. You can upgrade your Effect SDK to V4.3.1+. <br>
 *        + 1003: Contact our technical support team for further instructions. <br>
 *        + 1004: Downloading related resources. The beauty effects will take effect after downloading. <br>
 *        + <0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://docs.byteplus.com/effects/docs/error-code-table). <br>
 * @notes <br>
 *        + You cannot use the basic beauty effects and the advanced effect features at the same time. Call enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:} to use advanced effect features. <br>
 *        + You need to integrate Effect SDK before calling this API. Effect SDK V4.3.1+ is recommended. <br>
 *        + Call setBeautyIntensity:withIntensity:{@link #ByteRTCEngineKit#setBeautyIntensity:withIntensity:} to set the beauty effect intensity. If you do not set the intensity, the brightness, smoothness, and sharpness intensity will default to 0.5. <br>
 *        + This API is not applicable to screen capturing. <br>
 */
- (int)enableEffectBeauty:(BOOL)enable;

/** 
 * @type api
 * @region Audio & Video Processing
 * @author wangjunlin.3182
 * @brief Sets the beauty effect intensity.
 * @param beautyMode Basic beauty effect. See ByteRTCEffectBeautyMode{@link #ByteRTCEffectBeautyMode}.
 * @param intensity Beauty effect intensity in range of [0,1], default to 0.5. When you set it to 0, the beauty effect will be turned off.
 * @return  <br>
 *        + 0: Success. <br>
 *        + 1000: The Effect SDK is not integrated. <br>
 *        + 1001: This API is not available for your current RTC SDK. <br>
 *        + <0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://docs.byteplus.com/effects/docs/error-code-table). <br>
 * @notes <br>
 *        + If you call this API before calling enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:}, the default settings of beauty effect intensity will adjust accordingly. <br>
 *        + If you destroy the engine, the beauty effect settings will be invalid. <br>
 */
- (int)setBeautyIntensity:(ByteRTCEffectBeautyMode) beautyMode
            withIntensity:(float)intensity;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Switch to the front-facing/back-facing camera used in the internal video capture  <br>
 *        The local client will be informed via rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} after calling this API.
 * @param cameraId Camera ID. Refer to ByteRTCCameraID{@link #ByteRTCCameraID} for more details.
 * @return   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 * @notes  <br>
 *         + Front-facing camera is the default camera.
 *         + If the internal video capturing is on, the switch is effective once you call this API. If the internal video capturing is off, the setting will be effective when capture starts.
 */
- (int)switchCamera:(ByteRTCCameraID) cameraId;

/** 
 * @hidden
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Video image segmentation, replace background
 * @param mode  Background mode, used to set prefabricated background, whether to blur, etc. See ByteRTCBackgroundMode{@link #ByteRTCBackgroundMode}
 * @param divideModel  To choose which segmentation model to use. See ByteRTCDivideModel{@link #ByteRTCDivideModel}
 * @return   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int)replaceBackground:(ByteRTCBackgroundMode)mode
          withDivideModel:(ByteRTCDivideModel)divideModel;
/** 
 * @type api
 * @hidden(iOS)
 * @region Video Effects
 * @brief Get authorization messages from the Effect SDK for the online license.
 * @param ppmsg Authorization message string address
 * @return   <br>
 *       + 0: call succeeded <br>
 *       + 1000: The Effect SDK is not integrated. <br>
 *       + 1001: CV function is not supported in this RTC version <br>
 *       + < 0: Failure. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes  <br>
 *         + You must get an online license for the Effect SDK before using the CV functions. <br>
 *           After getting authorization messages with this API, implement the code of getting the online license with [Online Authorization Instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99798/). Then call checkVideoEffectLicense{@link #ByteRTCEngineKit#checkVideoEffectLicense} to validate the license. After that, you can use the CV function. <br>
 */
- (int)getAuthMessage:(NSString *_Nullable*_Nullable)ppmsg;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Video effects license check
 * @param licenseFile  Absolute path of license file
 * @return   <br>
     *      + 0: Success <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.   <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes EnableVideoEffect:{@link #enableVideoEffect:} Before you start using video effects, you need to call this method for license verification
 */
- (int)checkVideoEffectLicense:(NSString * _Nonnull)licenseFile;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Create/destroy video effects engine
 * @param enabled   <br>
 *         Whether to create video effects engine <br>
 *        + True: create <br>
 *        + False: destroy
 * @return   <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes   <br>
 *        + This method must be called after calling checkVideoEffectLicense:{@link #checkVideoEffectLicense:} and setVideoEffectAlgoModelPath:{@link #setVideoEffectAlgoModelPath:}. <br>
 *        + This method does not directly turn on/off video effects. After calling this method, you must call setVideoEffectNodes:{@link #setVideoEffectNodes:} to turn on video effects. <br>
 *        + In a common scenario, the special effects engine will be destroyed with the destruction of the RTC engine. When you have high performance requirements, you can call false in this method to destroy the special effects engine separately when the special effects related functions are not used.
 */
- (int)enableVideoEffect:(BOOL)enabled;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Set the video effects algorithm model path
 * @param modelPath   <br>
 *         Model path
 */
- (void)setVideoEffectAlgoModelPath:(NSString * _Nonnull)modelPath;

/** 
 * @hidden
 * @type api
 * @region Video Effects
 * @author liqi.ritchie
 * @brief  Sets the video effects resource finder path and initializes video effects.
 * @param finder ResourceFinder path
 * @param deteter ResourceDeleter path
 * @return  <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 */
- (int)setVideoEffectAlgoModelResourceFinder:(void *_Nonnull)finder deleter:(void *_Nonnull)deteter;

/** 
 * @hidden
 * @type api
 * @region Video Effects
 * @author liqi.ritchie
 * @brief  Sets the configuration for video effects expression detection.
 * @param config Expression detection configuration. See ByteRTCExpressionDetectConfig{@link #ByteRTCExpressionDetectConfig}.
 * @return  <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 */
- (int)setVideoEffectExpressionDetect:(ByteRTCExpressionDetectConfig *_Nonnull)config;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief Set video effects material package.
* @param effectNodePaths Array of effect material package paths. <br>
*        To remove the current video effect, set it to null.
 * @return   <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes Before calling this method, you must first call enableVideoEffect:{@link #ByteRTCEngineKit#enableVideoEffect:}.
 */
- (int) setVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/** 
 * @hidden
 * @type api
 * @region Video Effects
 * @author liqi.ritchie
 * @brief  Appends video effects material package.
 * @param effectNodePaths Array of effect material package paths.
 * @return  <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes  This API adds new video effect to the video effect you set with setVideoEffectNodes:{@link #ByteRTCEngineKit#setVideoEffectNodes:}.
 */
- (int) appendVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/** 
 * @hidden
 * @type api
 * @region Video Effects
 * @author liqi.ritchie
 * @brief  Removes the designated video effects material package.
 * @param effectNodes Array of effect material package paths.
 * @return  <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes Removes the designated video effects in setVideoEffectNodes:{@link #ByteRTCEngineKit#setVideoEffectNodes:} or appendVideoEffectNodes:{@link #ByteRTCEngineKit#appendVideoEffectNodes:}.
 */
- (int) removeVideoEffectNodes:(NSArray <NSString *> *_Nonnull)effectNodePaths;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Set effect intensity
 * @param nodePath  Effect material package path.
 * @param nodeKey  The name of the material key to be set. See [Material key correspondence instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/).
 * @param nodeValue  The intensity value to be set. The value range is [0,1], and the setting beyond this range is invalid.
 * @return   <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 * @notes This interface is only applicable to special effects resources that contain the above three parameters at the same time. For special effects that do not have strength parameters, such as most stickers, this interface call is invalid.
 */
- (int) updateVideoEffectNode:(NSString * _Nonnull)nodePath nodeKey:(NSString * _Nonnull)nodeKey  nodeValue:(float) nodeValue;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief  Set color filter
 * @param resPath   <br>
 *         Filter effect package absolute path
 * @return   <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 */
- (int) setVideoEffectColorFilter:(NSString * _Nonnull)resPath;

/** 
 * @type api
 * @region Video Effects
 * @author zhushufan.ref
 * @brief Set the color filter intensity
 * @param intensity Filter intensity that is enabled. The value range [0,1] is invalid when the range is exceeded
 * @return   <br>
 *      + 0: Success <br>
 *      + 1000: The Effect SDK is not integrated.  <br>
 *      + 1001: This API is not available for your Effect SDK.   <br>
 *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
 */
- (int) setVideoEffectColorFilterIntensity:(float) intensity;
 /** 
  * @type api
  * @region Video Effects
  * @author wangjunlin.3182
  * @brief Initialize the virtual background function.
  * @param licensePath Absolute path to CV license file
  * @param modelPath Absolute path to model parameter file
  * @return   <br>
  *         + 0: Call succeeded. <br>
  *         + 1000: The Effect SDK is not integrated.  <br>
  *         + 1001: This API is not available for your Effect SDK.   <br>
  *         + > 40000: Failure. Effect SDK authorization error, please refer to [error codes](https://www.volcengine.com/docs/5889/61813) for specific error codes. <br>
  *         + < 0: Failure. Effect SDK internal error, specific error code please refer to [error codes](https://www.volcengine.com/docs/5889/61813). <br>
  */
- (int) initVirtualBackground:(NSString* _Nonnull)licensePath withModel:(NSString* _Nonnull)modelPath;
 /** 
  * @type api
  * @region Video Effects
  * @author wangjunlin.3182
  * @brief Turn on the virtual background function.
  * @param source Virtual background object. See ByteRTCVirtualBackgroundSource{@link #ByteRTCVirtualBackgroundSource}.
  * @return   <br>
  *         + 0: Success. <br>
  *         + < 0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://www.volcengine.com/docs/5889/61813). <br>
  *         + -1: Failure. Virtual background function not successfully initialized. See initVirtualBackground:withModel:{@link #ByteRTCEngineKit#initVirtualBackground:withModel:}. <br>
  *         + -4: Failure. Failed to open the custom background picture. <br>
  *         + -37: Failure. Failed to decode the custom background picture. <br>
  *         + -38: Failure. The format of the custom background picture not supported. Formats jpg, jpeg, and png are supported. <br>
  * @notes   <br>
  *        + Before calling this api, call initVirtualBackground:withModel:{@link #ByteRTCEngineKit#initVirtualBackground:withModel:}. <br>
  *        + The virtual background supports the video stream collected by the camera, including SDK default mechanism and custom mechanism. Screen video stream does not supported the virtual backgrounds function. <br>
  */
- (int) enableVirtualBackground:(ByteRTCVirtualBackgroundSource* _Nonnull)source;
 /** 
  * @type api
  * @region Video Effects
  * @author wangjunlin.3182
  * @brief Turn off the virtual background function.
  * @return   <br>
  *         + 0: success <br>
  *         + < 0: Failure. Please refer to [error codes](https://www.volcengine.com/docs/5889/61813) for specific error codes. <br>
  * @notes After calling enableVirtualBackground:{@link #ByteRTCEngineKit#enableVirtualBackground:} to enable the virtual background function, you can call this   API to turn it off.
  */
- (int) disableVirtualBackground;



#pragma mark - ICameraControl

/** 
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief  Set camera zoom parameters
 * @param zoom_val   <br>
 *          Camera zoom parameters. 1.0 means scaling to the original image, the maximum value that can be set is obtained through the getCameraZoomMaxRatio{@link #getCameraZoomMaxRatio} method <br>
 * @return   <br>
 *       + 0: Success <br>
 *       + -1: Failure <br>
 */
- (int) setCameraZoomRatio: (float) zoom_val;

/** 
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief  Get the maximum zoom parameters that can be set by the camera
 * @return  The maximum zoom parameters that can be set  <br>
 */
- (float) getCameraZoomMaxRatio;

/** 
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief  Detect whether the camera supports scaling
 * @return   <br>
 *       + True: supports scaling <br>
 *       + False: does not support scaling <br>
 */
- (bool) isCameraZoomSupported;

/** 
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief  Detect whether the camera supports fill light
 * @return   <br>
 *       + True: support fill light <br>
 *       + False: not support fill light <br>
 */
- (bool) isCameraTorchSupported;

/** 
 * @hidden(macOS)
 * @type api
 * @region  video management
 * @brief  Set the fill light status
 * @param torch_state   <br>
 *          Fill light status. See ByteRTCTorchState{@link #ByteRTCTorchState} <br>
 * @return   <br>
 *       + 0: Success <br>
 *       + -1: Failure <br>
 */
- (int) setCameraTorch: (ByteRTCTorchState)torch_state;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Checks if manual focus is available for the currently used camera.
 * @return  <br>
 *        + true: Available. <br>
 *        + false: Unavailable.
 * @notes You must call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to start SDK internal video capturing before calling this API.
 */
- (bool)isCameraFocusPositionSupported;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Sets the manual focus position for the currently used camera.
 * @param position The position of the focus point. Setting the upper-left corner of the canvas as the origin, the `x` in `position` means the x-coordinate of the focus point in range of [0, 1], and the `y` in `position` means the y-coordinate of the focus point in range of [0, 1].
 * @return  <br>
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @notes <br>
 *        + You must call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + When you set the focus point at the center of the canvas, the focus point setting will be canceled.  <br>
 *        + The camera focus point setting will be invalid after calling stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraFocusPosition:(CGPoint)position;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Checks if manual exposure setting is available for the currently used camera.
 * @return  <br>
 *        + true: Available. <br>
 *        + false: Unavailable.
 * @notes You must call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to start SDK internal video capturing before calling this API.
 */
- (bool)isCameraExposurePositionSupported;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Sets the manual exposure position for the currently used camera.
 * @param position The position of the exposure point. Setting the upper-left corner of the canvas as the origin, the `x` in `position` means the x-coordinate of the exposure point in range of [0, 1], and the `y` in `position` means the y-coordinate of the exposure point in range of [0, 1].
 * @return  <br>
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @notes <br>
 *        + You must call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + When you set the exposure point at the center of the canvas, the exposure point setting will be canceled.  <br>
 *        + The camera exposure point setting will be invalid after calling stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraExposurePosition:(CGPoint)position;

/** 
 * @type api
 * @region Video Management
 * @author zhangzhenyu.samuel
 * @brief Sets the exposure compensation for the currently used camera.
 * @param val Exposure compensation in range of [-1, 1]. Default to 0, which means no exposure compensation.
 * @return  <br>
 *        + 0: Success. <br>
 *        + < 0: Failure.
 * @notes <br>
 *        + You must call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to start SDK internal video capturing, and use SDK internal rendering before calling this API. <br>
 *        + The camera exposure compensation setting will be invalid after calling stopVideoCapture{@link #ByteRTCEngineKit#stopVideoCapture} to stop internal capturing.
 */
- (int)setCameraExposureCompensation:(float)val;

/** 
 * @type api
 * @region Video Effects
 * @author wangjunlin.3182
 * @brief  Register the observer for the result of face detection. <br>
 *        With this observer, you will receive onFaceDetectionResult:{@link #ByteRTCFaceDetectionObserver#onFaceDetectionResult:} periodically.
 * @param faceDetectionObserver See ByteRTCFaceDetectionObserver{@link #ByteRTCFaceDetectionObserver}.
 * @param interval Time interval in ms. The actual time interval of receiving callbacks is between `interval` and `interval + the time slot of a captured video frame`.
 * @return <br>
 *       + 0: Success <br>
 *       + <0: Failure <br>
 */
- (int) registerFaceDetectionObserver:(_Nullable id<ByteRTCFaceDetectionObserver>)faceDetectionObserver
                  withInterval:(NSInteger)interval;

#pragma mark - MediaMetadataData InnerVideoSource
/** 
 * @hidden
 * @deprecated since 326.1 Use sendSEIMessage instead
 * @type api
 * @region video data callback
 * @author wangjunlin.3182
 * @brief Register metadata observers to receive or send metadata. The underlying layer implements this function by adding SEI data to the video frame. <br>
 *         After registering an observer, the video frame sent does not have SEI information, which will trigger a videoFrameMediaMetaDataAtTime:{@link #videoFrameMediaMetaDataAtTime:} callback. <br>
 *         After registering an observer, the received video frame contains SEI information, which will trigger a receive receiveVideoFrameFromUID:withExtendedData:atTimestamp:{@link #receiveVideoFrameFromUID:withExtendedData:atTimestamp:} callback. <br>
 * @param metadataObserver Metadata observer, see: ByteRTCMediaMetadataObserver{@link #ByteRTCMediaMetadataObserver}
 * @return   <br>
 *          + YES: Set successfully <br>
 *          + NO: Set failed <br>
 * @notes   <br>
 *       + When using video custom capture and rendering, you can directly add and obtain metadata in the video frame. This interface is not recommended.
 *       + This interface supports dynamic unregistration, setting the parameter to nullptr to unregister. <br>
 */
- (BOOL)setMediaMetadataObserver:(_Nullable id<ByteRTCMediaMetadataObserver>) metadataObserver;

/** 
 * @type api
 * @region Video Management
 * @author wangjunlin.3182
 * @brief When video communication, SEI data is sent through video frames.This function is called when the streammain stream is an internal source and the camera is turned off. The SDK engine will construct a video black frame to send SEI information
 * @param streamIndex  Media stream type. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param message SEI message. Length not exceeding 4 kB.
 * @param repeatCount  Number of message sending repetitions. The value range is [0,30]. <br>
 *                    When this interface is called, SEI data is added to consecutive'repeatCount 'video frames starting with the current video frame.
 * @return  <br>
 *         + > = 0: The number of SEIs to be added to the video frame <br>
 *         + < 0: Send failed
 * @notes  <br>
 *         + You can use this interface to add SEI to the video frame collected internally by the RTC SDK. For video frames obtained by custom acquisition: if the original video frame does not add SEI data, then you can call this interface to add SEI information to it for encoding and transmission; if the original video frame has added SEI data, then Call this interface does not take effect <br>
 *         + If there is no video frame with SEI within 2s after calling this interface (for example, video acquisition and transmission are not turned on) ), then, SEI data will not be added to the video frame. <br>
 *         + After the message is sent successfully, the remote will receive a callback from rtcEngine:onSEIMessageReceived:andMessage:{@link #ByteRTCEngineDelegate#rtcEngine:onSEIMessageReceived:andMessage:}.
 *         + When sending SEI information with video black frames, please call this function at the frequency of 15/repeatcount FPS
 */
- (int)sendSEIMessage:(ByteRTCStreamIndex)streamIndex andMessage:(NSData* _Nonnull)message andRepeatCount:(int)repeatCount;

#pragma mark - VideoFrameObserver InnerVideoSource

/** 
 * @hidden
 * @type api
 * @region Video Data Callback
 * @author sunhang.io
 * @brief Register/Unregister Video Data Callback Observer
 * @param frameObserver Video Data Callback Observer Object, see: ByteRTCVideoFrameObserver{@link #ByteRTCVideoFrameObserver}. <br>
 *         Set the parameter to nullptr to cancel registration.
 * @return   <br>
 *         + YES: Setup succeeded <br>
 *         + NO: Setup failed
 * @notes This method can be called at any time, it is recommended before joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}.
 */
- (BOOL)setVideoFrameObserver:(_Nullable id<ByteRTCVideoFrameObserver>) frameObserver;

/** 
 * @type api
 * @region  Video Processing
 * @author zhushufan.ref
 * @brief  Set up a custom video preprocessor. <br>
 *         Using this video preprocessor, you can call processVideoFrame:{@link #ByteRTCVideoProcessorDelegate#processVideoFrame:} to preprocess the video frames captured by the RTC SDK and use the processed video frames for RTC audio & video communication.
 * @param processor Custom video processor. See ByteRTCVideoProcessorDelegate{@link #ByteRTCVideoProcessorDelegate}. If null is passed in, the video frames captured by the RTC SDK are not preprocessed. <br>
 *        SDK only holds weak references to the processor, you should guarantee its Life Time. <br>
 *         When designing the'processor ', the video frame data should be obtained from the'textureBuf' field of ByteRTCVideoFrame{@link #ByteRTCVideoFrame}; <br>
 *         The video frame data returned after processing should be in the format of'ByteRTCVideoPixelFormat 'in ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}, and must be stored in the'textureBuf' field that returns the frame data.
 * @param config Customize the settings applicable to the video preprocessor. See ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig}. <br>
 *                Currently, the 'required_pixel_format 'in'config' only supports: 'ByteRTCVideoPixelFormatI420' and'ByteRTCVideoPixelFormatUnknown ': <br>
 *                + When set to'UNKnow', the RTC SDK gives the format of the video frame for processing by the processor, that is, the format of the acquisition. <br>
 *                + When set to'ByteRTCVideoPixelFormatI420 ', the RTC SDK will convert the captured video into the corresponding format for pre-processing. This method call fails when <br>
 *                + Is set to another value.
 * @return  <br>
 *          + 0: Success. <br>
 *          +! 0: failure <br>
 * @notes   <br>
 *         + When this interface is called repeatedly, only the last call takes effect. The effects do not stack. <br>
 *         + For iOS platforms, setting the required_pixel_format in ByteRTCVideoPreprocessorConfig{@link #ByteRTCVideoPreprocessorConfig} to'kVideoPixelFormatUnknown 'brings some performance optimization by avoiding format conversion.
 */
- (int)registerLocalVideoProcessor:(_Nullable id<ByteRTCVideoProcessorDelegate>) processor
                  withConfig:(ByteRTCVideoPreprocessorConfig* _Nullable)config;

#pragma mark - LocalEncodedVideoFrameObserver
/** 
 * @type api
 * @region Video Data Callback
 * @author wangzhanqiang
 * @brief Register a local video frame observer.   <br>
 *        This method applys to both internal capturing and custom capturing.  <br>
 *        After calling this API, SDK triggers onLocalEncodedVideoFrame:Frame:{@link #ByteRTCLocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame:Frame:} whenever a video frame is captured.
 * @param frameObserver Local video frame observer. See ByteRTCLocalEncodedVideoFrameObserver{@link #ByteRTCLocalEncodedVideoFrameObserver}. You can cancel the registration by setting it to `nullptr`.
 * @notes You can call this API before or after entering the RTC room. Calling this API before entering the room ensures that video frames are monitored and callbacks are triggered as early as possible.
 */
- (void)registerLocalEncodedVideoFrameObserver:(_Nullable id<ByteRTCLocalEncodedVideoFrameObserver>) frameObserver;

#pragma mark Subscribe Controller Methods
// @name custom subscription method

/** 
 * @hidden
 * @deprecated since 326.1, use joinRoom with MultiRoomConfig instead
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief Set the subscription mode of audio & video streams in the room (automatic/manual). Automatic subscription by default.   <br>
 *        To enable the manual subscription function, it is recommended to complete the setting before calling the joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} method to join the room. <br>
 * @param audioMode  Subscription mode for audio streams. See ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}. <br>
 * @param videoMode  Subscription mode for video streams. See ByteRTCSubscribeMode{@link #ByteRTCSubscribeMode}. The <br>
 * @return  Method executes the result.   <br>
 *          + YES: Success. <br>
 *          + NO: failure. <br>
 * @notes SDK  provides two subscription modes: <br>
 *          1. Automatic subscription mode. When the automatic subscription function is turned on, the SDK automatically helps users subscribe to audio & video streams published by all other users in the room; <br>
 *          2. Manual subscription mode. When the automatic subscription feature is turned off, users manually subscribe to audio & video streams posted by other users by calling the subscribeStream:subscribeConfig:{@link #subscribeStream:subscribeConfig:} method as needed. <br>
 */
- (BOOL)enableAutoSubscribe:(ByteRTCSubscribeMode)audioMode videoMode:(ByteRTCSubscribeMode)videoMode
DEPRECATED_MSG_ATTRIBUTE("Please use joinRoomBykey with roomConfig");

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief Subscribe to the specified room remote audio & video stream.   <br>
 *         Turn off the automatic subscription function. When using the manual subscription mode, call this method to subscribe to the audio & video stream in the room on demand. <br>
 *         To turn off the automatic subscription function, when starting the manual subscription mode, you must call enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:} before joining the room. <br>
 * @param userId  Publishes the user ID of the remote audio & video stream. <br>
 * @param info  Select the subscription configuration. See ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}. <br>
 * @notes  <br>
 *         + When the subscription flow fails, it will be called back by rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:}. For specific errors, please refer to the error code ByteRTCErrorCode{@link #ByteRTCErrorCode} <br>
 *         + If the specified stream does not exist in the current room, the SDK will not subscribe. <br>
 *         + After the user joins the room, he can get the audio & video stream information in the room according to the relevant callbacks and manually subscribe:
 *            -when The user just joined the room, he will receive rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:} callback to understand the audio & video stream information that has been published in the current room; <br>
 *            -when There is a new audio in the room & When a video stream publishes/stops publishing, you will receive a callback from rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:} and
 *              rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}
 */
- (void)subscribeStream:(NSString *_Nonnull)userId subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

/** 
 * @hidden
 * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
 * @type api
 * @region room management
 * @author shenpengliang
 * @brief Subscribe to media streams in the room.   <br>
 *        Call this API to subscribe to media streams in the room regardless of subscription mode, either Auto or Manual. <br>
 *        Call this API to update the properties and configurations of the stream you have already subscribed to. <br>
 * @param userId User ID of the publisher of the subscribed media stream <br>
 * @param streamType Mainstream or screen-sharing stream. Refer to ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for details. <br>
 * @param mediaType  Media stream type to be subscribed to. Refer to ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType} for details. <br>
 * @param videoConfig Subscription configuration of video streams. Refer to ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig} for details. <br>
 * @notes  <br>
 *         + Get the media stream information in the room from rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:} and rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}. <br>
 *         + If the subscription fails, you will receive rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:}. Refer to ByteRTCErrorCode{@link #ByteRTCErrorCode} for the specific reason of the failure.
 *         + You can update the subscription configuration by calling the API even after calling pauseAllSubscribedStream:{@link #ByteRTCEngineKit#pauseAllSubscribedStream:} to pause streaming. Call resumeAllSubscribedStream:{@link #ByteRTCEngineKit#resumeAllSubscribedStream:} to resume streaming and apply the changes. <br>
 */
- (void)subscribeUserStream:(NSString *_Nonnull)userId streamType:(ByteRTCStreamIndex)streamType mediaType:(ByteRTCSubscribeMediaType)mediaType videoConfig:(ByteRTCSubscribeVideoConfig *_Nonnull)videoConfig;
/** 
 * @type api
 * @region Room Management
 * @author liuzhiqiang
 * @brief Subscribes to specific remote media streams captured by camera/microphone.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId The ID of the remote user who published the target audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *        + You must first get the remote stream information through rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:} before calling this API to subscribe to streams accordingly.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcEngine:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (void)subscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region Room Management
 * @author liuzhiqiang
 * @brief Unsubscribes from specific remote media streams captured by camera/microphone.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId The ID of the remote user who published the target audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *        + After calling this API, you will be informed of the calling result with rtcEngine:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region Room Management
 * @author liuzhiqiang
 * @brief Subscribes to specific screen sharing media stream.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId The ID of the remote user who published the target screen audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *        + You must first get the remote stream information through rtcEngine:onUserPublishScreen:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishScreen:type:} before calling this API to subscribe to streams accordingly.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcEngine:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (void)subscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;
/** 
 * @type api
 * @region Room Management
 * @author liuzhiqiang
 * @brief Unsubscribes from specific screen sharing media stream.  <br>
 *        You can call this API in both automatic subscription mode and manual subscription mode.
 * @param userId The ID of the remote user who published the target screen audio/video stream.
 * @param mediaStreamType Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *        + After calling this API, you will be informed of the calling result with rtcEngine:onStreamSubscribed:userId:subscribeConfig:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (void)unSubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/** 
 * @hidden
 * @deprecated since 326.1, use subscribeUserStream instead
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Stop subscribing to the specified room remote audio & video stream.   <br>
 *         Turn off the automatic subscription function. When using the manual subscription mode, call this method to stop the audio & video stream in the subscription room. <br>
 *         To turn off the automatic subscription function, when starting the manual subscription mode, you must call enableAutoSubscribe:videoMode:{@link #enableAutoSubscribe:videoMode:} before joining the room. <br>
 * @param userId  Publishes the user ID of the remote audio & video stream. <br>
 * @param isScreen  Whether the stream subscribed to is a screen share stream. <br>
 * @notes You can call this method to stop the subscription regardless of whether you subscribe to the specified remote audio & video stream. When the userId that stops subscribing is invalid or unsubscribed, the SDK will not do any processing and there is no negative impact. <br>
 */
- (void)unSubscribeStream:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen
DEPRECATED_MSG_ATTRIBUTE("Please use subscribeUserStream");

#pragma mark Audio Routing Controller
// @name audio playback route
/** 
 * @hidden
 * @deprecated since 338.1, use setAudioRoute instead
 * @type api
 * @region Audio management
 * @author dixing
 * @brief  Sets the speaker or the earpiece as the audio playback device. The audio playback device defaults to the speaker.  <br>
 *         When the audio playback device changes, you will receive the rtcEngine:onAudioPlaybackDeviceChanged:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioPlaybackDeviceChanged:} callback. <br>
 * @param audioPlaybackDevice  Audio playback device (speaker or earpiece). See ByteRTCAudioPlaybackDevice{@link #ByteRTCAudioPlaybackDevice}. <br>
 * @return   <br>
 *         + 0: Success <br>
 *         + < 0: failure <br>
 * @notes   <br>
 *        + This API is applicable for mobile devices such as mobile phones. <br>
 *        + The earpiece and the speaker are mobile devices' built-in audio playback devices. The earpiece is usually used for calling and the speaker is usually used for playing out loud. <br>
 *        + After connecting to a wired or bluetooth audio playback device, the audio route will switch to them. For the selected volume type in different audio scenarios, see ByteRTCAudioScenarioType{@link #ByteRTCAudioScenarioType}. <br>
 *        + You can call this API before or after joining room.
 */
- (int)setAudioPlaybackDevice:(ByteRTCAudioPlaybackDevice)audioPlaybackDevice;
/** 
 * @hidden(Mac)
 * @type api
 * @region Audio management
 * @author liuxiaowu
 * @brief Designate the device as the current audio playback device. The default device is set via setDefaultAudioRoute:{@link #ByteRTCEngineKit#setDefaultAudioRoute:}. <br>
 *         When the audio playback route changes, you will get notified via rtcEngine:onAudioRouteChanged:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioRouteChanged:}.
 * @param audioRoute Audio route. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute} for more details. You cannot choose `ByteRTCAudioRouteUnknown`. <br>
 *        You cannot choose `ByteRTCAudioRouteEarpiece` except in the communication audio mode.<br>
 *        You can choose `ByteRTCAudioRouteHeadsetBluetooth` or `ByteRTCAudioRouteHeadsetUSB` except in the communication audio mode.
 * @return <br>
 *         + 0: Success <br>
 *         + < 0: Failure <br>
 * @notes <br>
 *      + The audio route automatically switches to the wired or Bluetooth audio playback device once it is connected. <br>
 *      + Disconnecting the current audio device will have the audio route switched to the previous device. If all the peripheral devices are removed, the audio route will switch to the default route audio. <br>
 *      + For the volume type in different audio scenarios, refer to ByteRTCAudioScenarioType{@link#ByteRTCAudioScenarioType}.
 */
- (int)setAudioRoute:(ByteRTCAudioRoute)audioRoute;
/**
 * {en}
 * @hidden(Mac)
 * @type api
 * @region Audio Facility Management
 * @author liuxiaowu
 * @brief Set the speaker or earpiece as the default audio playback device.   <br>
 * @param audioRoute Audio playback device. Refer to ByteRTCAudioRoute{@link #ByteRTCAudioRoute} <br>
 * @return <br>
 *         + 0: Success. The setting takes effect immediately. However, the audio route will not switch to the default device until all the audio peripheral devices are disconnected. <br>
 *         + < 0: failure. It fails when the device designated is neither a speaker nor an earpiece.
 * @notes You can call this API whether the user is in or outside a room.
 */
- (int)setDefaultAudioRoute:(ByteRTCAudioRoute)audioRoute;
/** 
 * @type api
 * @region Audio management
 * @author dixing
 * @brief Get the information of currently-using playback route.
 * @return See ByteRTCAudioRoute{@link #ByteRTCAudioRoute}.
 * @notes To set the audio playback route, see setAudioRoute:{@link #ByteRTCEngineKit#setAudioRoute:}.
 */
- (ByteRTCAudioRoute)getAudioRoute;
/** 
 * @type api
 * @author liuxiaowu
 * @brief Enable the audio process mode for external sound card.
 * @param enable <br>
 *        + true: enable <br>
 *        + false: disable (by default)
 * @notes   <br>
 *         + When you use external sound card for audio capture, enable this mode for better audio quality. <br>
 *         + When using the mode, you can only use earphones. If you need to use internal or external speaker, disable this mode.
 */
- (void)enableExternalSoundCard:(bool)enable;

#pragma mark Combined to Push

/** 
 * @type api
 * @region Push to CDN
 * @author wanghaoxu
 * @brief Create a new task of pushing media streams to CDN and sets the relevant configurations.  <br>
 *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
 * @param task_id Task ID. <br>
 *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
 * @param transcoding Configurations to be set when pushing streams to CDN. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}
 * @param observer Register this observer to receive callbacks from the SDK. See LiveTranscodingDelegate{@link #LiveTranscodingDelegate}.
 * @notes  <br>
 *        + After calling this API, you will be informed of the result and errors during the pushing process via the onStreamMixingEvent:taskId:error:mixType:{@link #LiveTranscodingDelegate#onStreamMixingEvent:taskId:error:mixType:} callback.  <br>
 *        + Call stopLiveTranscoding:{@link #ByteRTCEngineKit#stopLiveTranscoding:} to stop pushing streams to CDN.
 */
- (int)startLiveTranscoding:(NSString * _Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nullable)transcoding observer:(id<LiveTranscodingDelegate> _Nullable)observer;

/** 
 * @type api
 * @region Push to CDN
 * @brief Stops pushing media streams to CDN.
 * @param task_id Task ID. Specifys which pushing task you want to stop.
 * @return API call result: <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 */
- (int)stopLiveTranscoding:(NSString *_Nonnull)task_id;

/** 
 * @type api
 * @region Multi-room
 * @author shenpengliang
 * @brief Update parameters needed when pushing media streams to CDN.  <br>
 *        After enabling the function of pushing streams to CDN, you can call this API to update the relevant configurations.
 * @param task_id Task ID. Specifys of which pushing task you want to update the parameters.
 * @param Transcoding Configurations that you want to update. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}.
 * @return  API call result.   <br>
 *          + 0: Success <br>
 *          + < 0: failure
 */
- (int)updateLiveTranscoding:(NSString *_Nonnull)task_id transcoding:(ByteRTCLiveTranscoding *_Nonnull)transcoding;

/** 
 * @type api
 * @region Cloud Rendering
 * @author wuxinyu.mrx
 * @brief Enable cloud rendering according to the incoming layout information.  <br>
 * @param rendingInfo  Rendering function related, parameters. <br>
 * @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)enableCloudRending:(NSString *_Nonnull)rendingInfo;

/** 
 * @type api
 * @region Cloud Render
 * @author wuxinyu.mrx
 * @brief Update the cloud rendering with the layout information passed in.  <br>
 * @param rendingInfo  Rendering function related, parameters. <br>
 * @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)updateCloudRending:(NSString *_Nonnull)rendingInfo;

/** 
 * @type api
 * @region  cloud rendering
 * @author wuxinyu.mrx
 * @brief  Stop cloud rendering.  <br>
 * @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 */
- (int)disableCloudRending;

#pragma mark public streaming
/** 
 * @type api
 * @brief Start publishing a public media stream.<br>
 *        A public stream refers to a media stream that does not belong to any room or any user. Users within the same `appID` can call startPlayPublicStream:{@link #ByteRTCEngineKit#startPlayPublicStream:} to subscribe to the public stream regardless the user has joined which room or has not joined any room.
 * @param publicStreamId ID of the public stream<br>
 * @param publicStreamParam Properties of the public stream. Refer to ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} for more details.<br>
 *              A public stream can include a bundle of media streams and appears as the designated layout.
 * @return
 *        + 0: Success. And you will be informed by rtcEngine:onPushPublicStreamResult:errorCode:{@link #ByteRTCEngineDelegate#rtcEngine:onPushPublicStreamResult:errorCode:}. <br>
 *        + !0: Failure because of invalid parameter or empty parameters.<br>
 * @notes
 *        + Call updatePublicStreamParam:withLayout:{@link #ByteRTCEngineKit#updatePublicStreamParam:withLayout:} to update the properties of the public stream which is published by the same user. Calling this API with the same stream ID repeatedly by the same user can not update the existing public stream.<br>
 *        + If Users with different userID call this API with the same stream ID, the public stream will be updated with the parameters passed in the latest call.<br>
 *        + To publish multiple public streams, call this API with different stream ID respectively.<br>
 *        + To stop publishing the public stream, call stopPushPublicStream:{@link #ByteRTCEngineKit#stopPushPublicStream:}.
 */
- (int)startPushPublicStream:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStreamParam;

/** 
 * @type api
 * @brief Stop the public stream published by the current user.<br>
 *        Refer to startPushPublicStream:withLayout:{@link #ByteRTCEngineKit#startPushPublicStream:withLayout:} for details about starting publishing a public stream.
 * @param publicStreamId ID of the public stream<br>
 *                  The public stream must be published by the current user.
 * @return
 *        + 0: Success<br>
 *        + !0: Failure<br>
 */
- (int)stopPushPublicStream:(NSString * _Nonnull)publicStreamId;

/** 
 * @type api
 * @brief Update the properties of the public stream published by the current user.<br>
 *        Refer to startPushPublicStream:withLayout:{@link #ByteRTCEngineKit#startPushPublicStream:withLayout:} for details about starting publishing a public stream.
 * @param publicStreamId ID of the public stream<br>
 *              The stream to be updated must be published by the current user.
 * @param publicStreamParam Properties of the public stream. Refer to ByteRTCPublicStreaming{@link #ByteRTCPublicStreaming} for more details.current user.
 * @return <br>
 *        + 0: Success<br>
 *        + !0: Failure<br>
 */
- (int)updatePublicStreamParam:(NSString * _Nonnull)publicStreamId withLayout:(ByteRTCPublicStreaming *_Nullable)publicStreamParam;

/** 
 * @type api
 * @brief Subscribe the public stream<br>
 *        A user can call this method to subscribe a public stream whether he/she has joined the room or not.
 * @param publicStreamId ID of the public stream. If the stream has not been published then, the local client will receive the public stream once it starts publishing.
 * @return <br>
 *        + 0: Success. You will also be informed by rtcEngine:onPlayPublicStreamResult:errorCode:{@link #ByteRTCEngineDelegate#rtcEngine:onPlayPublicStreamResult:errorCode:}.  <br>
 *        + !0: Failure because of invalid parameter or empty parameters.<br>
 * @notes  <br>
 *        + We recommend to bind a view for the public stream before calling this API to subscribe a public stream. <br>
 *              - Internal renderer: By calling setPublicStreamVideoCanvas:withCanvas:{@link #ByteRTCEngineKit#setPublicStreamVideoCanvas:withCanvas:}<br>
 *              - Custom renderer: By calling setPublicStreamVideoSink:withSink:withPixelFormat:{@link #ByteRTCEngineKit#setPublicStreamVideoSink:withSink:withPixelFormat:}<br>
 *        + After calling this API, you will be informed once the first frame has been decoded successfully by rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstPublicStreamVideoFrameDecoded:withFrameInfo:} and rtcEngine:onFirstPublicStreamAudioFrameDecoded:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstPublicStreamAduioFrameDecoded:}.<br>
 *        + If the public stream contains SEI information, you will be informed by rtcEngine:onPublicStreamSEIMessageReceived:andMessage:{@link #ByteRTCEngineDelegate#rtcEngine:onPublicStreamSEIMessageReceived:andMessage:}.<br>
 *        + Call stopPlayPublicStream:{@link #ByteRTCEngineKit#stopPlayPublicStream:} to cancel subscribing the public stream.
     */
- (int)startPlayPublicStream:(NSString * _Nonnull)publicStreamId;

/** 
 * @type api
 * @brief Cancel subscribing the public stream.<br>
 *        Call this method to cancel subscribing to the public stream by calling startPlayPublicStream:{@link #ByteRTCEngineKit#startPlayPublicStream:}.
 * @param publicStreamId ID of the public stream
 * @return
 *        + 0: Success<br>
 *        + !0: Failure<br>
 */
- (int)stopPlayPublicStream:(NSString * _Nonnull)publicStreamId;

/** 
 * @type api
 * @brief Assign a internal render view to the public stream
 * @param publicStreamId ID of the public stream
 * @param videoCanvas Internal render view. Set to be a blank view if you want to unbind. Refer to ByteRTCVideoCanvas{@link #ByteRTCVideoCanvas} for more details.
 * @return
 *        + 0: Success<br>
 *        + !0: Failure<br>
 */
- (int)setPublicStreamVideoCanvas:(NSString *_Nonnull)publicStreamId withCanvas:(ByteRTCVideoCanvas * _Nullable)videoCanvas;

/** 
 * @type api
 * @brief Assign a custom renderer to the public stream
 * @param publicStreamId ID of the public stream
 * @param videoSink Custom renderer. Set to be `null` when you want to release the renderer. Refer to ByteRTCVideoSinkDelegate{@link #ByteRTCVideoSinkDelegate} for more details.
 * @param requiredFormat Format of the video frames required by the external video renderer. Refer to  ByteRTCVideoSinkPixelFormat{@link #ByteRTCVideoSinkPixelFormat} for more details.
 * @return
 *        + 0: Success<br>
 *        + !0: Failure<br>
 */
- (int)setPublicStreamVideoSink:(NSString *_Nonnull)publicStreamId
                       withSink:(id<ByteRTCVideoSinkDelegate> _Nullable)videoSink
                withPixelFormat:(ByteRTCVideoSinkPixelFormat)requiredFormat;
/** 
 * @type api
 * @region Network Management
 * @author qipengxiang
 * @brief Starts a call test.  <br>
 *        Before entering the room, you can call this API to test whether your local audio/video equipment as well as the upstream and downstream networks are working correctly.  <br>
 *        Once the test starts, SDK will record your sound or video. If you receive the playback within the delay range you set, the test is considered normal.
 * @param echoConfig Test configurations, see ByteRTCEchoTestConfig{@link #ByteRTCEchoTestConfig}.
 * @param delayTime Delayed audio/video playback time specifying how long you expect to receive the playback after starting the. The range of the value is [2,10] in seconds and the default value is 2.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure, testing in progress  <br>
 *        + -2: Failure, you are in the room  <br>
 *        + -3: Failure, neither video nor audio is captured  <br>
 *        + -4: Failure, Parameter exception  <br>
 *        + -5: Failure, the roomID is already used
 * @notes  <br>
 *        + Once you start the test, you can either call stopEchoTest{@link #ByteRTCEngineKit#stopEchoTest} or wait until the test stops automatically after 60s, to start the next test or enter the room.  <br>
 *        + All APIs related to device control and stream control called before this API are invalidated during the test and are restored after the test.  <br>
 *        + All APIs related to device control, stream control, and room entry called during the test do not take effect, and you will receive rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} with the warning code `ByteRTCWarningCodeInEchoTestMode`.
 *        + You will receive the test result from rtcEngine:onEchoTestResult:{@link #ByteRTCEngineDelegate#rtcEngine:onEchoTestResult:}.
 */
- (int)startEchoTest:(ByteRTCEchoTestConfig* _Nullable)echoConfig playDelay:(NSInteger)delayTime;
/** 
 * @type api
 * @region Network Management
 * @author qipengxiang
 * @brief Stop the current call test.  <br>
 *        After calling startEchoTest:playDelay:{@link #ByteRTCEngineKit#startEchoTest:playDelay:}, you must call this API to stop the test.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure, no test is in progress
 * @notes After stopping the test with this API, all the system devices and streams are restored to the state they were in before the test.
 */
- (int)stopEchoTest;

#pragma mark External Video Data
// @name custom video capture

/** 
 * @hidden
 * @deprecated  Use setVideoSourceType instead
 * @type api
 * @region  video management
 * @author zhushufan.ref
 * @brief  To configure video capture sources.
 * @param type  For video input types. See ByteRTCMediaInputType{@link #ByteRTCMediaInputType}.
 * @notes   <br>
 *        + 1. This method can be called before and after entering the room. <br>
 *        + 2. The SDK will automatically turn off the internal collection when you have called startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to turn on the internal collection and then call this method to switch to custom collection. <br>
 *        + 3. If you want to switch to internal collection after you have turned on custom collection, you must first call this method to specify that internal collection is used, and then call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to manually turn on internal collection.
 */
- (void)setVideoInputType:(ByteRTCMediaInputType)type;

/** 
 * @hidden
 * @deprecated since 329.1, user setVideoSourceType instead
 * @type api
 * @region Video management
 * @author zhushufan.ref
 * @brief Switch video capture methods (internal capture/custom capture)
 * @param type Video capture methods. See ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType}
 * @notes   <br>
 *        + Use internal capture by default. Internal capture refers to video capture using the video capture mechanism built into the RTC SDK. <br>
 *        + This method can be called before and after entering the room. <br>
 *        + The SDK will automatically turn off the internal collection when you have called startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to turn on the internal collection, and then call this method to switch to custom collection. <br>
 *        + When you call this method to turn on custom collection, to switch to internal collection, you must first call this method to turn off custom collection, and then call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to manually turn on internal collection.
 */
- (void)setVideoSourceType:(ByteRTCVideoSourceType)type;

/** 
 * @type api
 * @region Custom video capture rendering
 * @author zhangzhenyu.samuel
 * @brief Push external video frames.
 * @param frame The video frame contains the video data to be encoded by the SDK
 * @param pts CMTime
 * @return   <br>
 *          + YES Push Successfully <br>
 *          + NO Push Failure <br>
 * @notes Before pushing an external video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} to turn on external video source capture.
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts;

/** 
 * @type api
 * @region Customize video capture rendering
 * @author zhangzhenyu.samuel
 * @brief Push external video frames.
 * @param frame The video frame contains the video data to be encoded by the SDK
 * @param pts CMTime
 * @param rotation Current video angle, see ByteRTCVideoRotationMode{@link #ByteRTCVideoRotationMode}.
 * @return   <br>
 *          + YES push success <br>
 *          + NO push failure <br>
 * @notes Before pushing an external video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} to turn on external video source capture.
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(ByteRTCVideoRotation)rotation;

/** 
 * @type api
 * @region  custom video capture rendering
 * @author zhangzhenyu.samuel
 * @brief  Push external video frames.
 * @param frame The video frame contains the video data to be encoded by the SDK
 * @param pts CMTime
 * @param rotation The current video angle
 * @param extendedData Extended data of the current frame, if not, it will be empty
 * @param supplementoryInfo Additional information, such as the location of the face, etc.
 * @return   <br>
 *          + YES Push success <br>
 *          + NO Push failure <br>
 * @notes  Before pushing an external video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} to turn on external video source capture.
 */
- (BOOL)pushExternalVideoFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts
                                                             rotation:(ByteRTCVideoRotation)rotation
                                                         extendedData:(NSData* _Nullable)extendedData
                                                    supplementaryInfo:(NSData* _Nullable)supplementoryInfo;


/** 
 * @type api
 * @region Custom video capture rendering
 * @author zhangzhenyu.samuel
 * @brief Push external video frames, encapsulated with ByteRTCVideoFrame.
 * @param frame This video frame contains video data to be encoded by the SDK. Refer to ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return   <br>
 *          + YES Push Successfully <br>
 *          + NO Push Failure <br>
 * @notes Before pushing an external video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} Turn on external video source capture.
 */
- (BOOL)pushExternalByteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

#pragma mark External Audio Data
// @name custom audio capture and rendering
/** 
  * @hidden
  * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
  * @type api
  * @region Custom Audio Capture and Rendering
  * @author dixing
  * @brief Enables custom audio capture and rendering.
  * @param recordingFormat See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
  * @param playbackFormat See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}
  * @notes   <br>
  *       + You must call this API before joining the room.<br>
  *       + The state of enabling custom audio capture and rendering is still valid after leaving the room, until disableExternalAudioDevice{@link #ByteRTCEngineKit#disableExternalAudioDevice} is called to disable custom audio capture and rendering. <br>
  *       + You must enable both custom audio capture and custom audio rendering, or enable both internal audio capture and internal audio rendering. By default, internal audio capture and rendering are used. <br>
  *       + After enabling custom audio capture and rendering, call pushExternalAudioFrame:{@link #ByteRTCEngineKit#pushExternalAudioFrame:} to push custom captured audio frames to the RTC SDK for transmission; and call pullExternalAudioFrame:{@link #ByteRTCEngineKit#pullExternalAudioFrame:} to get remote audio frames. <br>
  *       + If calling the API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. <br>
  *       + To switch to internal capture when custom capture is enabled, you must call disableExternalAudioDevice{@link #ByteRTCEngineKit#disableExternalAudioDevice} to disable custom capture, and then call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to manually enable internal capture.
  */
- (void)enableExternalAudioDevice:(ByteRTCAudioFormat * _Nonnull) recordingFormat playbackFormat:(ByteRTCAudioFormat * _Nonnull) playbackFormat;
 /** 
 * @hidden
 * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
 * @type api
 * @region Custom Audio Capture Rendering
 * @author dixing
 * @brief Disables custom audio capture and rendering.
 * @notes   <br>
 *       + To switch to internal capture when custom capture is enabled, you must call this API and then call startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture}. <br>
 *       + To enable custom audio capture and rendering, call enableExternalAudioDevice:playbackFormat:{@link #enableExternalAudioDevice:playbackFormat:}.
 */
- (void)disableExternalAudioDevice;
/** 
 * @type api
 * @region Custom Audio Capture and Rendering
 * @author gaoguangyuan
 * @brief  Switch the audio capture type.
 * @param type Audio input source type. See ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType} <br>
 *            Use internal audio capture by default. The audio capture type and the audio render type may be different from each other.
 * @return   Method call result:   <br>
 *         + >0: Success. <br>
 *         + -1: Failure.
 * @notes   <br>
 *       + You can call this API before or after joining the room.<br>
 *       + If you call this API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. You must call pushExternalAudioFrame:{@link #ByteRTCEngineKit#pushExternalAudioFrame:} to push custom captured audio data to RTC SDK for transmission. <br>
 *       + If you call this API to switch from custom capture to internal capture, you must then call startAudioCapture{@link #ByteRTCEngineKit#startAudioCapture} to enable internal capture.
 */
- (int)setAudioSourceType:(ByteRTCAudioSourceType) type;
/** 
 * @type api
 * @region Custom Audio Capture and Rendering
 * @author gaoguangyuan
 * @brief  Switch the audio render type.
 * @param type Audio output source type. See ByteRTCAudioRenderType{@link #ByteRTCAudioRenderType}. <br>
 *             Use internal audio render by default. The audio capture type and the audio render type may be different from each other.
 * @return   Method call result:   <br>
 *         + >0: Success. <br>
 *         + -1: Failure.
 * @notes   <br>
 *       + You can call this API before or after joining the room. <br>
 *       + After calling this API to enable custom audio rendering, call pullExternalAudioFrame:{@link #ByteRTCEngineKit#pullExternalAudioFrame:} for audio data.
 */
- (int)setAudioRenderType:(ByteRTCAudioRenderType) type;

 /** 
  * @deprecated Since 325.1, use ByteRTCAudioMixingManager instead
  * @hidden
  * @type api
  * @region  mixing
  * @author majun.lvhiei
  * @brief  Start/stop external audio stream mixing,  and set the mixing data format
  * @param enable   <br>
  *        + YES: Enable external audio stream mixing. <br>
  *        + NO: Stop external audio stream mixing.
  * @param sampleRate   <br>
  *        Audio sample rate in HZ. Currently supported sampling rates are: 8000HZ, 16000HZ, 32000HZ, 44100HZ, 48000HZ.
  * @param channelNum   <br>
  *         Number of audio channels. Currently supports single channel (1), dual channel (2)
  * @return   <br>
  *       + YES: success <br>
  *       + NO: failure
  * @notes   <br>
  *       + Call this method to set the PCM format of external audio mixes, namely pushAudioMixingStreamData:frameNum:{@link #pushAudioMixingStreamData:frameNum:} audioFrame audio data format. <br>
  *       + Call the data source external cache of the method mix, and the audio format is PCM; startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} The method mixes the data source external files, and the supported file formats are: mp3, aac, m4a, 3gp, wav. These two mixing methods can coexist. <br>
  *       + Stop external audio stream mixing when enabled to NO. Or when the engine is released, the SDK will stop mixing internally. <br>
  *       + The external audio stream mix initiated by this method does not support volume adjustment, pause, pause and resume operations.
  */
- (BOOL)setAudioPlayoutMixStream:(BOOL) enable
                    sampleRate:(int) sampleRate
                    channelNum:(int) channelNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @deprecated Since 325.1, use ByteRTCAudioMixingManager instead
 * @hidden
 * @type api
 * @region Audio Mixing
 * @author wangjunzheng
 * @brief To get the SDK currently buffered data
 * @return   <br>
 *        + > 0: Success, the number of audio sample points buffered. <br>
 *        + 0: Failure
 * @notes
 *       Call this method to obtain the amount of cached data in real time, and adjust the data push rhythm based on this data to avoid out of memory
 */

- (int)getAudioMixingStreamCachedFrameNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

 /** 
  * @deprecated Since 325.1, use ByteRTCAudioMixingManager instead
  * @hidden
  * @type api
  * @region  mix
  * @author majun.lvhiei
  * @brief  Push the audio data of the mix to the SDK
  * @param audioFrame   <br>
  *        PCM audio data, and its format is consistent with setAudioPlayoutMixStream.
  * @param frameNum   <br>
  *         Sample points. If the audio sampling rate is 48000HZ, the amount of data per second for a single channel is 48000 sampling points, the number of sampling points corresponding to the audio data of 10 milliseconds is 480 sampling points.
  * @return   <br>
  *        + YES: Success <br>
  *        + NO: Failure
  * @notes
  *       + Before calling this method, you must set the data format of the audioFrame through the setAudioPlayoutMixStream method. <br>
  *       + Before calling this method, get the cached amount of data through getAudioMixingStreamCachedFrameNum, and adjust the rhythm of the push data to avoid internal slow overflow causing push failure. <br>
  *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 200 milliseconds) on the application side, and then push it all at once; after that, the push operation is timed once in 10 milliseconds, and the amount of audio data each time is 10 milliseconds.
  */
- (BOOL)pushAudioMixingStreamData:(void* _Nonnull)audioFrame
                         frameNum:(int)frameNum
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @type api
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Enables audio data callback.
 * @param method Audio data callback method. See ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}. <br>
 *               If `method` is set as `0`, `1`, or `2`, set `format` to the accurate value listed in the audio parameters format.
 *               If `method` is set as `3`, set `format` to `auto`.
 * @param format Audio parameters format. See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}.
 * @notes After calling this API and setAudioFrameObserver:{@link #ByteRTCEngineKit#setAudioFrameObserver:}, ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} will receive the corresponding audio data callback. However, these two APIs are independent of each other and the calling order is not restricted. <br>
 */
- (void)enableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method format:(ByteRTCAudioFormat* _Nullable)format;

/** 
 * @type api
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Disables audio data callback.
 * @param method Audio data callback method. See ByteRTCAudioFrameCallbackMethod{@link #ByteRTCAudioFrameCallbackMethod}.
 * @notes Call this API after calling enableAudioFrameCallback:format:{@link #ByteRTCEngineKit#enableAudioFrameCallback:format:}.
 */
- (void)disableAudioFrameCallback:(ByteRTCAudioFrameCallbackMethod) method;

/** 
 * @type api
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Register an audio frame observer.  <br>
 * @param audioFrameObserver Audio data callback observer. See ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver}. Use `null` to cancel the registration.
 * @return  <br>
 *        + 0: Success. <br>
 *        + < 0: Failure. <br>
 * @notes After calling this API and enableAudioFrameCallback:format:{@link #ByteRTCEngineKit#enableAudioFrameCallback:format:}, ByteRTCAudioFrameObserver{@link #ByteRTCAudioFrameObserver} will receive the corresponding audio data callback.
 */
- (BOOL)setAudioFrameObserver:(_Nullable id<ByteRTCAudioFrameObserver>) audioFrameObserver;
/** 
 * @type api
 * @hidden
 * @deprecated since 342, use registerAudioProcessor instead.
 * @region  Audio Processing
 * @author majun.lvhiei
 * @brief  Set up a custom audio processor.   <br>
 *        Using this processor, you can call processAudioFrame:{@link #ByteRTCAudioProcessor#processAudioFrame:} to customize the audio frames captured by the RTC SDK and use the processed audio frames for RTC audio & video communication. <br>
 *        SDK only holds weak references to the processor, you should guarantee its Life Time.
 * @param audioProcessor Custom audio processor. See ByteRTCAudioProcessor{@link #ByteRTCAudioProcessor}. If null is passed in, the audio frames captured by the RTC SDK are not customized.
 * @param format Customize the audio parameter format. See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}, the SDK will give the audio frame according to the specified setting.
 * @return  Method call result   <br>
 *         + YES: Success. <br>
 *         + NO: failure
 * @notes When this interface is called repeatedly, only the last call takes effect. The effects do not stack.
 */
- (BOOL)registerLocalAudioProcessor:(_Nullable id<ByteRTCAudioProcessor>) audioProcessor
                             format:(ByteRTCAudioFormat* _Nullable)format;
/** 
* @type api
* @author majun.lvhiei
* @brief  Register a custom audio preprocessor. <br>
*         After that, you can call enableAudioProcessor:audioFormat:{@link #ByteRTCEngineKit#enableAudioProcessor:audioFormat:} to process the locally captured or received remote audio streams.
* @param processor Custom audio processor. See ByteRTCAudioFrameProcessor{@link #ByteRTCAudioFrameProcessor}。<br>
*        SDK only holds weak references to the processor, you should guarantee its Life Time.
* @notes When this interface is repeatedly called, only the last call takes effect.
*/
- (BOOL)registerAudioProcessor:(_Nullable id<ByteRTCAudioFrameProcessor>)processor;
/** 
* @type api
* @author majun.lvhiei
* @brief Get the local captured audio frames or received remote audio frames for custom processing.
* @param  method Audio Frame type. See ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}. To process multiple types of audio, you can call this API with different methods. <br>
*        With different values, you will receive corresponding callback: <br>
*        + For locally captured audio, you will receive onProcessRecordAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRecordAudioFrame:}  <br>
*        + For mixed remote audio, you will receive onProcessPlayBackAudioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessPlayBackAudioFrame:} <br>
*        + For audio from remote users, you will receive onProcessRemoteUserAudioFrame:audioFrame:{@link #ByteRTCAudioFrameProcessor#onProcessRemoteUserAudioFrame:audioFrame:} <br>
* @param  format The format of the returned audio frame. See ByteRTCAudioFormat{@link #ByteRTCAudioFormat}.
* @notes <br>
*        + Before calling this API, you must call registerAudioProcessor:{@link #ByteRTCEngineKit#registerAudioProcessor:} to register the processor. <br>
*        + To disable custom audio processing, call disableAudioProcessor:{@link #ByteRTCEngineKit#disableAudioProcessor:}.
*/
- (void)enableAudioProcessor:(ByteRTCAudioFrameMethod)method
                 audioFormat:(ByteRTCAudioFormat *_Nullable)format;
/** 
* @type api
* @author majun.lvhiei
* @brief Disable custom audio processing.
* @param method Audio Frame type. See ByteRTCAudioFrameMethod{@link #ByteRTCAudioFrameMethod}.
*/
- (void)disableAudioProcessor:(ByteRTCAudioFrameMethod)method;
/** 
  * @type api
  * @region Custom Audio Capture and Rendering
  * @author dixing
  * @brief Push custom captured audio data to the RTC SDK.
  * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
  * @return <br>
  *         + 0: Success <br>
  *         + < 0: Failure <br>
  * @notes   <br>
  *        + Before pushing external audio data, you must call setAudioSourceType:{@link #ByteRTCEngineKit#setAudioSourceType:} to enable custom audio capture. <br>
  *        + You must push custom captured audio data every 10 milliseconds. The samples (number of audio sampling points) of a single push should be `audioFrame.sample Rate/100`. For example, when the sampling rate is set to 48000, data of 480 sampling points should be pushed each time. <br>
  *        + The sampleRate and channel set in this API must be consistent with that in setAudioSourceType:{@link #ByteRTCEngineKit#setAudioSourceType:}. <br>
  *        + Audio sampling format must be S16. The data format in the audio buffer must be PCM, and its capacity size should be `audioFrame.samples × audioFrame.channel × 2`. <br>
  *        + This API runs in a user-level thread. If other processes are running at the same time, this process will be interrupted. <br>
  */
- (int)pushExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

/** 
  * @type api
  * @region Custom audio capture and rendering
  * @author dixing
  * @brief Pulls audio data for custom rendering.
  * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
  * @return <br>
  *           + 0: Success <br>
  *           + < 0: Failure <br>
  * @notes   <br>
  *        + Before pulling custom audio data, you must call setAudioRenderType:{@link #ByteRTCEngineKit#setAudioRenderType:} to enable custom audio capture and rendering. <br>
  *        + You should pull audio data every 10 milliseconds. Samples (number of audio sampling points) should be `audioFrame.sample Rate/100`. For example, if the sampling rate is set to 48000, 480 sampling points is pulled each time. <br>
  *        + The sampleRate and channel of the audio data pulled by this API are consistent with that set in setAudioRenderType:{@link #ByteRTCEngineKit#setAudioRenderType:}, regardless of the parameters set for the remote audio capture. <br>
  *        + The audio sampling format is S16. The data format in the audio buffer is PCM, and its capacity size is `audioFrame.samples × audioFrame.channel × 2`. <br>
  *        + This API runs in a user-level thread. If other processes are running at the same time, this process will be interrupted.
  */
- (int)pullExternalAudioFrame:(ByteRTCAudioFrame * _Nonnull) audioFrame;

#pragma mark Message Related

/** 
 * @type api
 * @region real-time messaging
 * @author hanchenchen.c
 * @brief Sends text messages to all other users in the room.
 * @param message   <br>
 *        The content of the text message sent <br>
 *        The message does not exceed 62KB.
 * @return The number of the message sent this time is incremented from 1.
 * @notes   <br>
 *       + Before broadcasting a text message in the room, you must call joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join the room. <br>
 *       + After calling this function, you will receive an rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:} callback to inform the message sender that the sending succeeded or failed; <br>
 *       + If the text message is sent successfully, all remote users in the room will receive rtcEngine:onRoomMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageReceived:message:} callback.
 */
- (int)sendRoomMessage:(NSString *  _Nonnull)message;

/** 
 * @type api
 * @region real-time messaging
 * @author hanchenchen.c
 * @brief Sends binary messages to all other users in the room.
 * @param message   <br>
 *        The binary broadcast message sent by the user <br>
 *        The message does not exceed 46KB.
 * @return The number of the message sent this time is incremented from 1.
 * @notes   <br>
 *       + Before broadcasting binary messages in the room, you must call joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join the room. <br>
 *       + After calling this function, you will receive an rtcEngine:onRoomMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
 *       + If the binary message is sent successfully, all users in the room will receive rtcEngine:onRoomBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onRoomBinaryMessageReceived:message:} callback.
 */
- (int)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

#pragma mark Game Audio Related
/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Set the working mode of the engine, the default is general mode. Called before entering the room.
 * @param mode Mode selection, general mode or game voice mode. See RtcMode{@link #RtcMode}.
 * @return  Method call result   <br>
 *          + 0: call succeeded <br>
 *          + < 0: Failure <br>
 */
- (int)setRtcMode:(ByteRTCMode)mode;

/** 
 * @hidden
 * @type api
 * @region The game interface
 * @author shazhou
 * @brief Sends audio to the team or the world, which is called after creating the RtcEngine instance.
 * @param mode Select the mode, send to the team or send to the world. See RangeAudioMode{@link #RangeAudioMode}.
 * @return  Method call result   <br>
 *          + 0: call succeeded <br>
 *          + < 0: Failure <br>
 */
- (int)setAudioSendMode:(ByteRTCRangeAudioMode)mode;

/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Listen to squad or world audio, called after creating the RtcEngine instance.
 * @param mode Select the mode to listen to team or world audio. See RangeAudioMode{@link #RangeAudioMode}.
 * @return  Method call result   <br>
 *          + 0: call succeeded <br>
 *          + < 0: Failure <br>
 */
- (int)setAudioRecvMode:(ByteRTCRangeAudioMode)mode;

/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Settings teamId, must be called before joining the room, does not support modification after setting. If teamId is not set and is in game voice mode, joining the room fails. If teamId is not set and is in general mode, this method is invalid.
 * @param teamId  Team ID.
 * @return  Method call result   <br>
 *          + 0: call succeeded <br>
 *          + < 0: Failure <br>
 */
- (int)setTeamId:(NSString* _Nonnull)teamId;

/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Set your own audible range and use
 * @param minRange
 *         Minimum starting decay distance in game voice, that is, beyond this distance, the volume starts to decay as the distance increases
 * @param maxRange
 *         Maximum decay distance, that is, beyond this distance, the sound cannot be heard
 * @return Method call result   <br>
 *         + 0: call successfully <br>
 *         + < 0: The volume does not decay when the call fails <br>
 * @notes   <br>
 *        + (0, MinRange). <br>
 *        + (minRange, MaxRange), increase attenuation by distance <br>
 *        + Greater than maxRange, no sound can be heard <br>
 */
- (int)updateAudioRecvRange:(int)minRange
    maxRange:(int)maxRange;

/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Update your location to use in game voice. In game voice, the character has its own three-dimensional coordinates, and the volume can be dynamically adjusted according to the distance
 * @param x: X axis coordinates
 * @param y: Y axis coordinates
 * @param z: Z axis coordinates
 * @return  Method call result   <br>
 *         + 0: call succeeded <br>
 *         + < 0: Failure <br>
 * @notes  Only open area voice enableRangeAudio {@Link #enableRangeAudio:}, non-teammate users will only adjust the volume when sending and receiving the world
 */
- (int)updateSelfPosition:(int)x
                        y:(int)y
                        z:(int)z;

/** 
 * @hidden
 * @type api
 * @region game interface
 * @author shazhou
 * @brief Game voice scene, whether to turn on regional voice, the default turn on regional voice
 * @param enable
 *         1.true means on
 *         2.false means off
 * @return  Method call result   <br>
 *         + 0: call success <br>
 *         + < 0: Failure <br>\ < -- Plhd--0/>
 * If regional voice is turned on, the voice between non-teammates in the transceiver world mode will decay according to the distance between users, and it will not be heard if it exceeds the listening range. If regional voice is turned off, the voice between non-teammates in the transceiver world mode Will not decay with distance
 */
- (int)enableRangeAudio:(BOOL) enable;

/** 
 * @type api
 * @region Engine management
 * @author chenweiming.push
 * @brief  Sets the business ID   <br>
 *        You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
 * @param businessId   <br>
 *        Your customized businessId
 *        BusinessId is a tag, and you can customize its granularity.
 * @return   <br>
 *         + 0: Success <br>
 *         + < 0: Failure <br>
 *         + -6001: The user is already in the room. <br>
 *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
 * @notes   <br>
 *         + You must call this API before the joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} API, otherwise it will be invalid.
 */
- (int)setBusinessId:(NSString* _Nullable)businessId;
/** 
 * @type api
 * @region Engine management
 * @author chenweiming.push
 * @brief The call ends and the user feedback problem is reported to RTC <br>
 * @param types The list of preset problems. See ByteRTCProblemOption{@link #ByteRTCProblemOption} <br>
 * @param desc Specific description of other problems other than the preset problem <br>
 * @return  <br>
 *          + 0: Report successfully <br>
 *          + -1: Failed to report, haven't joined the room yet <br>
 *          + -2: Failed to report, data analysis error <br>
 *          + -3: Failed to report, missing fields <br>
 * @notes If the user is in the room when reporting, the report leads to the room / rooms where the user is currently located;
 *        If the user is not in the room when reporting, the report leads to the previously exited Room.
 */
- (int)feedback:(NSArray<ByteRTCProblemOption *> * _Nullable)types desc:(NSString* _Nullable)desc;

#pragma mark Monitor Related
// @name monitoring related api

/** 
 * @hidden
 * @deprecated
 * @type api
 * @region engine management
 * @author chenweiming.push
 * @brief Set device ID. <br>
 *        When monitoring, you can find relevant information according to the set deviceID. Must be called before initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}.
 * @param deviceID   <br>
 *         Device ID.
 */
+ (void)setDeviceId:(NSString* _Nonnull) deviceID
    __deprecated_msg("Will be removed in new version");

/** 
 * @hidden
 * @deprecated
 * @type api
 * @region Engine management
 * @author chenweiming.push
 * @brief Settings The server environment currently used by the SDK.
 * @param env   <br>
 *        The server environment parameters used by the SDK are detailed in: Env{@link #Env}.
 * @return   <br>
 *         + 0: Success. <br>
 *         + < 0: Failed. <br>
 *         + -1: The engine has been created.
 * @notes   <br>
 *         + This function is optional and uses official environment by default. <br>
 *         + This function must be called before creating the RtcEngine instance initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}.
 */
+ (int)setEnv:(ByteRTCEnv)env
    __deprecated_msg("Will be removed in new version");

/** 
 * @hidden
 * @type api
 * @region Engine management
 * @author weirongbin
 * @brief Set a custom HttpClient implementation. Provided to the SDK for network requests.
 * @param client   <br>
 *        Custom HttpClient.
 * @notes   <br>
 *         + The SDK supports the use of custom HttpClient, which requires the implementation of the ByteRTCHttpClientProtocol{@link #ByteRTCHttpClientProtocol} protocol. <br>
 *         + Must be set before creating the RtcEngine instance initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}. <br>
 *         + If not set, the HttpClient implemented internally in the SDK is used by default.
 */
+ (void)setHttpClient:(id<ByteRTCHttpClientProtocol> _Nonnull)client;

/** 
 * @hidden
 * @type api
 * @region engine management
 * @author chenweiming.push
 * @brief Get a custom HttpClient implementation. Implementation of
 * @return HttpClient .
 */
+ (id<ByteRTCHttpClientProtocol> _Nonnull)getHttpClient;

/** 
 * @hidden
 * @type api
 * @region Engine management
 * @author weirongbin
 * @brief Whether a custom HttpClient has been set.
 * @return   <br>
 *         + True: set.
 *         + False: not set.
 */
+ (bool)isHttpClientSet;

#pragma mark message related

/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Sends text messages (P2P) to specified users in the room.
 * @param uid   <br>
 *        Message Receives the user's ID
 * @param message   <br>
 *        Text message content sent. <br>
 *         Message does not exceed 62KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return The number of the message sent this time is incremented from 1.
 * @notes   <br>
 *       + Before sending an in-room text message, you must call joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join the room. <br>
 *       + After calling this function, you will receive an rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:} callback to notify the sender of the success or failure of the message. <br>
 *       + If the text message is sent successfully, the user specified by uid will receive rtcEngine:onUserMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageReceived:message:} callback.
 */
- (int64_t)sendUserMessage:(NSString * _Nonnull)uid message:(NSString * _Nonnull)message config:(ByteRTCMessageConfig)config;

/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Sends binary messages (P2P) to specified users in the room.
 * @param uid   <br>
 *        Message Receiving user's ID
 * @param message   <br>
 *        Binary message content sent <br>
 *        Message does not exceed 46KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return The number of the message sent this time is incremented from 1.
 * @notes   <br>
 *       + Before sending the in-room binary message, you must call joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:} to join the room. <br>
 *       + After calling this function, you will receive an rtcEngine:onUserMessageSendResult:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResult:error:} callback to notify the message sender that the sending succeeded or failed; <br>
 *       + If the binary message is sent successfully, the user specified by uid will receive rtcEngine:onUserBinaryMessageReceived:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserBinaryMessageReceived:message:} callback.
 */
- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message config:(ByteRTCMessageConfig)config;

#pragma mark Others
// @name other settings

/** 
 * @type api
 * @region  audio management
 * @author majun.lvhiei
 * @brief  Adjusts the audio playback volume from the specified remote user, the default is 100.
 * @param uid Remote user ID of the audio source
 * @param volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
 *        To ensure the audio quality, we recommend setting the volume within `100`.  <br>
 *               + 0: mute <br>
 *               + 100: original volume <br>
 *               + 400: Maximum can be 4 times the original volume (with overflow protection) <br>
 */
- (void)setRemoteAudioPlaybackVolume:(NSString* _Nonnull)uid volume:(int)volume;

#pragma mark audio mix related
/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Get music file duration
 * @return   <br>
 *        + > 0: Success, music file duration, in milliseconds. <br>
 *        + < 0: Failed
 * @notes  <br>
 *       Please call this method inside the room.
 */
- (int)getAudioMixingDuration
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Get the music file playback progress
 * @return   <br>
 *        + > 0: Success, the music file playback progress, in milliseconds. <br>
 *        + < 0: Failed
 * @notes  <br>
 *       Please call this method inside the room.
 */
- (int)getAudioMixingCurrentPosition
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");


/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Stop playing music files and mixing
 * @return   <br>
 *        + 0: success
 *        + < 0: failure
 * @notes   <br>
 *       + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} method to start playing music files and mixing, call this method to stop playing the music file and mixing. <br>
 *       + Please call this method inside the room.
 */
- (int)stopAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Pause playing music files
 * @return   <br>
 *         + 0: Success <br>
 *         + < 0: Failure
 * @notes   <br>
 *       + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the music file and mixing, you can call this method to pause playing the music file. <br>
 *       + After calling this method to pause playing the music file, you can call the resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} method to resume playing. <br>
 *       + Please call this method inside the room.
 */
- (int)pauseAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Resume playing music files
 * @return   <br>
 *        + 0: success <br>
 *        + < 0: failure
 * @notes   <br>
 *       + Call pauseAudioMixing{@link #pauseAudioMixing} method to pause playing music files After that, you can resume playing by calling this method. <br>
 *       + Please call this method in the room
 */
- (int)resumeAudioMixing
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mix
 * @author majun.lvhiei
 * @brief  To adjust the file volume of music files. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
 * @param volume Music file playback volume range is 0~ 400. <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: maximum adjustable volume (with overflow protection)
 * @return   <br>
 *        + 0: success <br>
 *        + < 0: failure
 * @notes   <br>
 *       + Call this method can be adjusted at the same time is local And remote playback volume. Adjusting the local volume only can use adjustAudioMixingPlayoutVolume:{@link #adjustAudioMixingPlayoutVolume:}, and adjusting the remote volume only can use adjustAudioMixingPublishVolume:{@link #adjustAudioMixingPublishVolume:}. <br>
 *       + The volume adjustment effect of this method on adjustAudioMixingPlayoutVolume:{@link #adjustAudioMixingPlayoutVolume:} and adjustAudioMixingPublishVolume:{@link #adjustAudioMixingPublishVolume:} is a product relationship <br>
 *       + Please call this method in the room.
 */
- (int)adjustAudioMixingVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  To start playing music files and mixing.
 * @param  filePath   <br>
 *         Specifies the absolute path of the local file that needs to be mixed. Supported audio file formats are: mp3, aac, m4a, 3gp, wav.
 * @param  loopback   <br>
 *        YES: Only the mixed or replaced audio stream can be heard locally. <br>
 *        NO: Both the local and the other party can hear the mixed or replaced audio stream
 * @param  replace   <br>
 *        YES: Only push the set local audio file, not transfer the audio collected by the microphone. <br>
 *        NO: The audio file content will be mixed with the audio stream collected by the microphone.
 * @param cycle  Specifies the number of times the audio file is cycled. <br>
 *        + > 0: The number of cycles. <br>
 *        + -1: Infinite loop
 * @return
 *        + 0: Success
 *        + < 0: Failure
 * @notes  <br>
 *       + This method specifies that the audio stream collected by the local and microphone is mixed or replaced. Replacement refers to replacing the audio stream captured by the microphone with an audio file. <br>
 *       + This method can choose whether to let the other party hear the locally played audio and specify the number of times to loop it. After calling this method to play the music file and the mixing ends, the application will receive a callback from rtcEngineLocalAudioMixingDidFinish:{@link #ByteRTCEngineDelegate#rtcEngineLocalAudioMixingDidFinish:}. <br>
 *       + After you start playing the music file and mixing, you can call the stopAudioMixing{@link #stopAudioMixing} method to stop playing the music file. <br>
 *       + This method mixes external files from data sources, and the supported file formats are: mp3, aac, m4a, 3gp, wav; and setAudioPlayoutMixStream mixes data sources are externally cached and the audio format is PCM; these two mixing methods can coexist. <br>
 *       + A single room only supports the playback of all music files. After multiple calls to this function, only the last call will take effect. <br>
 *       + Please call this method inside the room.
 */
- (int)startAudioMixing:(NSString *  _Nonnull)filePath
               loopback:(BOOL)loopback
                replace:(BOOL)replace
                  cycle:(NSInteger)cycle
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  To set the playback location of the audio file
 * @param pos
 *         Integer. Progress bar position in milliseconds.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *       This method can set the playback location of the audio file, so that you can play the music file from the specified location according to the actual situation, without playing a music file completely from beginning to end.
 */
- (int)setAudioMixingPosition:(NSInteger)pos
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  To adjust the local playback volume of music files. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
 * @param volume Music file playback volume range is 0~ 400. <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: maximum adjustable volume (with overflow protection)
 * @return   <br>
 *        + 0: success <br>
 *        + < 0: failure
 * @notes   <br>
 *       + Call this method to adjust the mixed The volume at which the music file is played locally. If you need to adjust the volume of both local and remote playback, you can use the adjustAudioMixingVolume:{@link #adjustAudioMixingVolume:} method. <br>
 *       + Please call this method inside the room.
 */
- (int)adjustAudioMixingPlayoutVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  To adjust the remote playback volume of the music file. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
 * @param volume Music file playback volume range is 0~ 400. <br>
 *        + 0: mute <br>
 *        + 100: original volume <br>
 *        + 400: maximum adjustable volume (with overflow protection)
 * @return   <br>
 *        + 0: success <br>
 *        + < 0: failure
 * @notes   <br>
 *       + This method adjusts the music file of the mix in The volume of the remote playback. If you need to adjust the local and remote playback volume at the same time, you can use the adjustAudioMixingVolume:{@link #adjustAudioMixingVolume} method. <br>
 *       + Please call this method inside the room.
 */
- (int)adjustAudioMixingPublishVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Adjust the file volume of the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness. Make sure the soundId here is the same as the soundId set by playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:}.
 * @param volume   <br>
 *        Music file playback volume range is 0~ 400. Default 100 is the original file volume
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes
 *        + This method adjusts the volume of audio files played locally and remotely. <br>
 *        + Please call this method inside the room.
 */
- (int)setVolumeOfEffect:(NSInteger)soundId
              withVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Get the file volume of the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness. Make sure the soundId here is the same as the soundId set by playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:}.
 * @return   <br>
 *        + > 0: Success, file volume, volume range 0~ 400. <br>
 *        + < 0: Failed
 * @notes   <br>
 *       Please call this method inside the room.
 */
- (int)getEffectVolume:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  To start playing the specified sound effect file. In this method, you can set the number of times the sound effect file is played, the volume, and whether the remote user can hear the sound effect.
 * @param soundId   <br>
 *         Sound ID, application caller maintenance, please ensure uniqueness. If the sound effect has been loaded into memory through preloadEffect:filePath:{@link #preloadEffect:filePath:}, make sure that the soundId here is the same as the soundId set by preloadEffect:filePath:{@link #preloadEffect:filePath:}.
 * @param filePath   <br>
 *         Specify the audio file name and file path name that need to be mixed. The following audio formats are supported: mp3, aac, m4a, 3gp, wav
 * @param loopback   <br>
 *         + YES: Only the sound effect can be heard locally; <br>
 *         + NO: Both local and remote users can hear the sound effect
 * @param  cycle  Specify the number of times the audio file is played in a loop. <br>
  *        + > 0: The number of cycles. <br>
 *         + -1: Infinite loop until it stops after calling stopEffect:{@link #stopEffect:} or stopAllEffects{@link #stopAllEffects}.
 * @param volume   <br>
 *        The sound file playback volume range is 0~ 400. The default is 100 for the original file volume.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *       + After calling this method to play the sound effect, the application will receive rtcEngineLocalAudioMixingDidFinish:{@link #ByteRTCEngineDelegate#rtcEngineLocalAudioMixingDidFinish:} callback.
 *       + This method can be called many times, and the soundId and filePath of different sound effects files can be passed in to realize the simultaneous playing of multiple sound effects files and the superposition of sound effects.
 *       + You can stop playing the specified sound effect file through the stopEffect:{@link #stopEffect:} method.
 *       + Please call this method inside the room.
 */
- (int)playEffect:(NSInteger)soundId
         filePath:(NSString * _Nullable)filePath
         loopback:(BOOL)loopback
            cycle:(NSInteger)cycle
       withVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Preload the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness.
 * @param filePath   <br>
 *         Specify the audio file name and file path name that need to be mixed. The following audio formats are supported: mp3, aac, m4a, 3gp, wav.
 * @return   <br>
 *         + 0: Success <br>
 *         + < 0: Failure
 * @notes   <br>
 *        + Call this method to preload and play the specified sound effect file. The preload operation can be completed before entering the room (all mixing-related interfaces, if not marked, can be called in the room when not entering the room). If the sound file is very long, the loading operation may take a long time. It is recommended that application developers put the preloading operation in a child thread.
 *        + This method only preloads to play the specified sound effect file, and only through playEffect:filePath:loopback:cycle:withVolume:{@link #playEffect:filePath:loopback:cycle:withVolume:} starts playing the specified sound effect file.
 *        + This method preloads the specified sound effect file, which can be unloaded via unloadEffect:{@link #unloadEffect:}.
 */
- (int)preloadEffect:(NSInteger)soundId filePath:(NSString * _Nullable)filePath
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Uninstall the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *        + This method unloads the specified sound file.
 *        + If the sound file is not unloaded when the stopEffect:{@link #stopEffect:} method is called, the SDK will automatically call the method to uninstall the sound file.
 */
- (int)unloadEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Pause playing the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *        Call this method to pause playing the specified sound effect file. You can call the resumeEffect:{@link #resumeEffect:} method to resume playing.
 */
- (int)pauseEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Resume playing the specified sound effect file
 * @param soundId   <br>
 *         Sound effect ID, apply caller maintenance, please ensure uniqueness.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes
 *       + After calling the pauseEffect:{@link #pauseEffect:} method to pause playing the specified sound effect file, it can be used to resume playing. <br>
 *       + After calling the pauseAllEffects{@link #pauseAllEffects} method to pause the playback of all sound effects files, you can also use this method to resume the playback of individual sound effects files.
 */
- (int)resumeEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Stop playing the specified sound file
 * @param soundId   <br>
 *        Sound ID, apply caller maintenance, please ensure uniqueness. If the sound effect has been loaded into memory through preloadEffect:filePath:{@link #preloadEffect:filePath:}, make sure that the soundId here is the same as the soundId set by preloadEffect:filePath:{@link #preloadEffect:filePath:}.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *        + Call this method to stop playing the specified sound file. <br>
 *        + This method will actively call unloadEffect:{@link #unloadEffect:} to uninstall the specified sound effect text.
 */
- (int)stopEffect:(NSInteger)soundId
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Adjust the file volume of all sound files
 * @param volume   <br>
 *        Music file playback volume range is 0~ 400. The default is 100 for the original file volume.
 * @return   <br>
 *        + 0: Success
 *        + < 0: Failure
 * @notes   <br>
 *        + This method adjusts the volume of all sound files of the mix to be played locally and remotely. <br>
 *        + Please call this method inside the room.
 */
- (int)setEffectsVolume:(NSInteger)volume
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Uninstall all sound files
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *        + Call this method to uninstall all sound files. If the sound files were not uninstalled when the engine was destroyed, the SDK will automatically call this method to uninstall all sound files. <br>
 *        + Calling leaveRoom{@link #ByteRTCEngineKit#leaveRoom} will not automatically call this method to uninstall all sound files after leaving the room. If you need to uninstall all sound files after leaving the room, you need the app to call this method actively.
 */
- (int)unloadAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");


/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Pause the playback of all sound effects files
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *      This method pauses the playback of all sound effects files, you can call resumeAllEffects {@link The #resumeAllEffects} method resumes playback.
 */
- (int)pauseAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

/** 
 * @hidden
 * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Resume playback of all sound files
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes   <br>
 *        + Call this method to resume playback of all sound files. After pauseAllEffects{@link #pauseAllEffects} is called to pause playback of all sound files, this method can be called to resume playback of all sound files. <br>
 *        + After calling the pauseEffect:{@link #pauseEffect:} method to pause the playback of a single specified sound effect file, you can also call this method to resume playback, but the efficiency is too low to recommend this use.
 */
- (int)resumeAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

 /** 
  * @hidden
  * @deprecated since 325.1, use ByteRTCAudioMixingManager instead
  * @type api
  * @region Audio Mixing
  * @author majun.lvhiei
  * @brief Stop playing all sound files
  * @return   <br>
  *        + 0: Success <br>
  *        + < 0: Failure
  * @notes   <br>
  *      This method stops playing all sound files.
  */
- (int)stopAllEffects
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCAudioMixingManager");

#pragma mark Fallback Related
/** 
 * @type api
 * @region Audio & Video Fallback
 * @author panjian.fishing
 * @brief Sets the fallback option for published audio & video streams.   <br>
 *        You can call this API to set whether to automatically lower the resolution you set of the published streams under limited network conditions.
 * @param option Fallback option, see ByteRTCPublishFallbackOption{@link #ByteRTCPublishFallbackOption}.
 * @return  API call result <br>
 *         + 0: Success <br>
 *         + < 0: Failure
 * @notes  <br>
 *         + This API only works after you call enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} to enable the mode of publishing multiple streams. <br>
 *         + You must call this API before entering the room.  <br>
 *         + After you allow video stream to fallback, your stream subscribers will receive rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCEngineDelegate#rtcEngine:OnSimulcastSubscribeFallback:} when the resolution of your published stream are lowered or restored.  <br>
 *         + You can alternatively set fallback options with distrubutions from server side, which is of higher priority.
 */
- (int)setPublishFallbackOption:(ByteRTCPublishFallbackOption)option;
/** 
 * @type api
 * @region Audio & Video Fallback
 * @author panjian.fishing
 * @brief Sets the fallback option for subscribed RTC streams.   <br>
 *        You can call this API to set whether to lower the resolution of currently subscribed stream under limited network conditions.
 * @param option Fallback option, see ByteRTCSubscribeFallbackOption{@link #ByteRTCSubscribeFallbackOption} for more details.
 * @return API call result:  <br>
 *        + 0:  Success  <br>
 *        + < 0: Failure
 *  @notes  <br>
 *         + You must call this API before enterting the room.  <br>
 *         + After you enables the fallback, you will receive rtcEngine:OnSimulcastSubscribeFallback:{@link #ByteRTCEngineDelegate#rtcEngine:OnSimulcastSubscribeFallback:} and rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onRemoteVideoSizeChanged:withFrameInfo:} when the resolution of your subscribed stream is lowered or restored.  <br>
 *         + You can alternatively set fallback options with distrubutions from server side, which is of higher priority.
 */
- (int)setSubscribeFallbackOption:(ByteRTCSubscribeFallbackOption)option;

/** 
 * @type api
 * @region  audio & video fallback
 * @author panjian.fishing
 * @brief Set user priority
 * @param priority Priority of remote user. See enumeration type ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}
 * @param uid ID of remote user
 * @return  + 0: Success. <br>
 *          + < 0: failure <br>
 * @notes   <br>
 *         + This method is used with setSubscribeFallbackOption:{@link #setSubscribeFallbackOption:}. <br>
 *         + If the subscription flow fallback option is turned on, weak connections or insufficient performance will give priority to ensuring the quality of the flow received by high-priority users. <br>
 *         + This method can be used before and after entering the room, and the priority of the remote user can be modified.
 */
- (int)setRemoteUserPriority:(ByteRTCRemoteUserPriority)priority
                         uid:(NSString *_Nonnull)uid;

#pragma mark AES Related

/** 
 * @type api
 * @region Encryption
 * @author wangjunlin.3182
 * @brief Set the way to use built-in encryption when transmitting  <br>
 * @param encrypt_type Built-in encryption algorithm. See ByteRTCEncryptType{@link #ByteRTCEncryptType}
 * @param key Encryption key, the length is limited to 36 bits, and the excess will be truncated
 * @notes   <br>
 *        + Use this method when using built-in encryption when transmitting; if you need to use transmission See ByteRTCEncryptRawData:{@link #ByteRTCEncryptHandler#ByteRTCEncryptRawData:}.
 *         Built-in encryption and custom encryption mutex, determine the scheme of transmission encryption according to the last called method. <br>
 *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. <br>
 */
- (void)setEncryptType:(ByteRTCEncryptType)encrypt_type key:(NSString * _Nonnull)key;

/** 
 * @type api
 * @region  encryption
 * @author wangjunlin.3182
 * @brief Set up custom encryption and decryption methods
 *        You need to implement the corresponding encryption and decryption methods. For details, refer to ByteRTCEncryptHandler{@link #ByteRTCEncryptHandler} <br>
 * @param handler   <br>
 *        Custom encryption handler, which needs to implement the encryption and decryption method <br>
 * @notes
 *        + The method and setEncryptType:key:{@link #setEncryptType:key:} are mutually exclusive relationships,
 *          That is, according to the call order, the last call method takes effect Version <br>
 *        + This method must be called before calling joinRoomByKey:roomId:userInfo:rtcRoomConfig:{@link #ByteRTCEngineKit#joinRoomByKey:roomId:userInfo:rtcRoomConfig:}
 * , Which can be called repeatedly, taking the last called parameter as the effective parameter <br>
 *        + Whether encrypted or decrypted, the length modification of the original data source needs to be controlled between 90% -120%, that is, if the input data is 100 bytes, The processed data must be between
 *         90 and 120 bytes. If the encryption or decryption result exceeds the length limit, the audio & video frame will be discarded <br>
 *        + Data encryption/decryption is performed serially, so depending on the implementation The method may affect the final rendering efficiency. Whether to use this method needs to be carefully evaluated by the user <br>
 */
- (void)setCustomizeEncryptHandler:(id<ByteRTCEncryptHandler> _Nullable)handler;



#pragma mark - ScreenCapture
/** 
 * @hidden
 * @deprecated since 327.1, use startScreenSharingWithPreferredExtension instead
 * @type api
 * @region screen sharing
 * @author liyi.000
 * @brief Configure external screen capture
 * @param enable YES: on;
 *               NO: not on;
 * @param rect Acquisition area
 * @param param Acquisition parameters ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}
 * @return 0 : success;
 *        -1: Failure;\ < --plhd- -1/>
 * 1. Screen acquisition is divided into internal acquisition and external acquisition. This method belongs to external acquisition.
 *        Internal acquisition: the SDK performs screen acquisition and all subsequent processes
 *        External acquisition: the user is responsible for collecting screen data frames and providing them to the SDK through the interface
 *        2. After this method is called to publish the local screen share stream, the user also needs to periodically call the pushScreenCaptureFrame:time:rotation:{@link #pushScreenCaptureFrame:time:rotation:} method by setting a timed task to push the screen data that needs to be sent to the SDK.
 *        3. The rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameRendered:withFrameInfo:} and rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:} events are received on the remote after calling this interface.
 */
- (int)setScreenCapture:(BOOL)enable Rect:(CGRect)rect screenCaptureParam:(ByteRTCScreenCaptureParam * _Nonnull)param;

/** 
 * @hidden
 * @deprecated since 336.1
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief  Publish local screen sharing.
 * @notes   <br>
 *        + Only visible users can call this API. You can set the user's visibility by calling setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:}. <br>
 *        + This API only starts the publishing but not the capturing. <br>
 *        + After the screen stream is published, the remote user will receive rtcEngine:onUserPublishStream:type:{@link #ByteRTCEngineDelegate #rtcEngine:onUserPublishStream:type:}. <br>
 *         + If you started capturing audio before calling this API, the remote side will receive the rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:} callback.
 *        + If you started capturing video before calling this API, the remote side will receive the rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} callback.
 *        + To stop publishing, call unpublishScreen{@link #ByteRTCEngineKit#unpublishScreen}.
 */
- (void)publishScreen;
/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Publishes local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *         + An invisible user cannot publish media streams. Call setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to change your visibility in the room. <br>
 *         + After you called this API, the other users in the room will receive rtcEngine:onUserPublishScreen:type:{@link #ByteRTCEngineDelegate#rtcEngine:onUserPublishScreen:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *         + Call startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *         + Call unpublishScreen:{@link #ByteRTCEngineKit#unpublishScreen:} to stop publishing screen sharing streams.
 */
- (void)publishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 336.1
 * @type api
 * @region Screen sharing
 * @author liyi.000
 * @brief Unpublish screen stream
 * @notes   <br>
 *        + This method only affects the publishing status of screen sharing video streams, and does not affect the capture of screen video streams. <br>
 *        + After the call succeeds, the remote receives a callback to rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}. <br>
 *        + Call publishScreen:{@link #ByteRTCEngineKit#publishScreen:} to start publishing.
 */
- (void)unpublishScreen;
/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Stops publishing local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes  <br>
 *         + After calling publishScreen:{@link #ByteRTCEngineKit#publishScreen:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcEngine:onUserUnPublishScreen:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishScreen:type:reason:}.
 */
- (void)unpublishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @type api
 * @region  screen sharing
 * @author liyi.000
 * @brief  Push external screen acquisition frame
 * @param frame  The video frame contains the video data to be encoded by the SDK
 * @param pts  Timestamp of each frame, the rotation angle of the unit ms
 * @param rotation  Frame contains: 0, 90, 180, 270
 * @notes  Screen acquisition is divided into internal acquisition and external acquisition, this method belongs to external acquisition.
 */
- (void)pushScreenCaptureFrame:(CVPixelBufferRef _Nonnull )frame time:(CMTime)pts rotation:(int)rotation;

/** 
 * @type api
 * @region  Screen Sharing
 * @author wangzhanqiang
 * @brief  Set Extension configuration. It should be set before capturing screen internally.
 * @param groupId  Your app and Extension should belong to the same App Group. You need to put in their Group ID here.
 * @notes You must call this API immediately after calling initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:}. You only need to call this API once in the life cycle of the engine instance. <br>
 */
- (void)setExtensionConfig:(NSString *_Nullable)groupId;
/** 
 * @type api
 * @hidden(macOS)
 * @region  Screen Sharing
 * @author wangzhanqiang
 * @brief  Start capturing the screen audio and/or video stream with the RTC SDK internal module.
 * @param type Media type. See ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}.
 * @param bundleId The bundle ID of the Extension, which is used to only display your Extension in your app.
 * @notes <br>
 *      + If you start the Extension from the iOS control center, this API do not need to be called. <br>
 *      + After the streams are captured, you need to call publishScreen:{@link #ByteRTCEngineKit#publishScreen:} to push the streams to the remote end. <br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} when the capturing is started. <br>
 */
- (void)startScreenCapture:(ByteRTCScreenMediaType) type bundleId:(NSString *_Nullable)bundleId;

/** 
 * @type api
 * @region  Screen Sharing
 * @author wangzhanqiang
 * @brief  Updates the media type of the internal screen capture.
 * @param type Media type. See ByteRTCScreenMediaType{@link #ByteRTCScreenMediaType}.
 * @notes <br>
 *      + Call this API after calling startScreenCapture:bundleId:{@link #ByteRTCEngineKit#startScreenCapture:bundleId:}. <br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} or rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}. <br>
 */
- (void)updateScreenCapture:(ByteRTCScreenMediaType) type;

/** 
 * @type api
 * @region  Screen Sharing
 * @author wangzhanqiang
 * @brief  Stop internal screen capture.
 * @notes <br>
 *      + Calling this API changes the capturing status without affecting the publishing status. To start the internal screen capture, call startScreenCapture:bundleId:{@link #ByteRTCEngineKit#startScreenCapture:bundleId:} again.<br>
 *      + You will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} and rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:}. <br>
 */
- (void)stopScreenCapture;

/** 
 * @type api
 * @region  Screen Sharing
 * @author wangzhanqiabg
 * @brief Send message to screen capture Extension
 * @param messsage  Message sent to the Extension
 * @notes Call this API after calling startScreenCapture:bundleId:{@link #ByteRTCEngineKit#startScreenCapture:bundleId:}.
 */
- (void)sendScreenCaptureExtensionMessage:(NSData *_Nonnull) messsage;

/** 
 * @type api
 * @brief Set runtime parameters
 * @param parameters Reserved parameters
 */
- (void)setRuntimeParameters:(NSDictionary * _Nullable)parameters;
/** 
 * @type api
 * @hidden(iOS)
 * @region  screen sharing
 * @author liyi.000
 * @brief  Get the list of shared objects (application windows and screens).
 * @return The list of shared objects. See ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}。<br>
 *         The enumerated value can be used for startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCEngineKit#startScreenCaptureSourceInfo:captureParameters:}.
 * @notes Only valid for PC and macOS.
 */
- (NSArray<ByteRTCScreenCaptureSourceInfo *> *_Nonnull)getScreenCaptureSourceList;
/** 
 * @type api
 * @hidden(iOS)
 * @region  screen sharing
 * @author liyi.000
 * @brief  Capture screen video stream for sharing. Screen video stream includes: content displayed on the screen, or content in the application window.
 * @param  sourceInfo Screen capture source information. See ByteRTCScreenCaptureSourceInfo{@link #ByteRTCScreenCaptureSourceInfo}. <br>
 *                    Call GetScreenCaptureSourceList{@link #ByteRTCEngineKit#GetScreenCaptureSourceList} to get all the screen sources that can be shared.
 * @param  captureParameters Screen capture parameters. See ByteRTCScreenCaptureParam{@link #ByteRTCScreenCaptureParam}.
 * @return   <br>
 *         + 0: Success; <br>
 *         + -1: Failure; <br>
 * @notes   <br>
 *        + This API only starts screen capturing but does not publish the captured video. Call publishScreen:{@link #RTCRoom#publishScreen:} to publish the captured video. <br>
 *        + To turn off screen video capture, call stopScreenCapture{@link #ByteRTCEngineKit#stopScreenCapture}. <br>
 *        + Local users will receive rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onVideoDeviceStateChanged:device_type:device_state:device_error:} on the state of screen capturing such as start, pause, resume, and error. <br>
 *        + After successfully calling this API, local users will receive rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:}. <br>
 *        + Before calling this API, you can call SetScreenVideoEncoderConfig:{@link #ByteRTCEngineKit#SetScreenVideoEncoderConfig:} to set the frame rate and encoding resolution of the screen video stream. <br>
 *        + After receiving rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstLocalVideoFrameCaptured:withFrameInfo:}, you can set the local screen sharing view by calling setLocalVideoCanvas:withCanvas:{@link #ByteRTCEngineKit#setLocalVideoCanvas:withCanvas:} or setLocalVideoSink:withSink:withPixelFormat:{@link #ByteRTCEngineKit#setLocalVideoSink:withSink:withPixelFormat:}. <br>
 *        + You can also register an observer by calling registerVideoFrameObserver:{@link #ByteRTCEngineKit#registerVideoFrameObserver:} and receive the captured screen video frame through onLocalScreenFrame:{@link #ByteRTCVideoFrameObserver#onLocalScreenFrame:}.<br>
 */
- (int)startScreenCaptureSourceInfo:(ByteRTCScreenCaptureSourceInfo *_Nonnull)sourceInfo captureParameters:(ByteRTCScreenCaptureParam *_Nonnull)captureParameters;
/** 
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @author liyi.000
 * @brief Update the capture area when capturing screen video streams through the internal capture module .
 * @param  regionRect The relative capture area to the area set by startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCEngineKit#startScreenCaptureSourceInfo:captureParameters:}.
 * @notes Before calling this API, you must call startScreenCaptureSourceInfo:captureParameters:{@link #ByteRTCEngineKit#startScreenCaptureSourceInfo:captureParameters:} to start internal screen stream capture.
 */
- (void)updateScreenCaptureRegion:(CGRect)regionRect;
/** 
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @author liyi.000
 * @brief Update border highlighting settings when capturing screen video streams through the internal capture module. The border is shown by default.
 * @param config Border highlighting settings. See ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}.
 * @notes  Before calling this API, you must have turned on internal screen capture by calling StartScreenVideoCapture{@link #StartScreenVideoCapture}.
 */
- (void)updateScreenCaptureHighlightConfig:(ByteRTCHighlightConfig *_Nonnull)config;
/** 
 * @hidden(iOS)
 * @type api
 * @region Screen sharing
 * @author liyi.000
 * @brief Update the processing settings for the mouse when capturing screen video streams through the capture module provided by the RTC SDK. The mouse is shown by default.
 * @param mouseCursorCaptureState See ByteRTCMouseCursorCaptureState{@link #ByteRTCMouseCursorCaptureState}.
 * @notes  Before calling this API, you must have turned on internal screen capture by calling StartScreenVideoCapture{@link #StartScreenVideoCapture}.
 */
- (void)UpdateScreenCaptureMouseCursor:(ByteRTCMouseCursorCaptureState)mouseCursorCaptureState;
/** 
 * @type api
 * @hidden(iOS)
 * @region Screen sharing
 * @author liyi.000
 * @brief When capturing screen video streams through the capture module provided by the RTC SDK, set the windows to be filtered out.
 * @param excludedWindowList The windows to be filtered out.
 * @notes  <br>
 *        + BBefore calling this API, you must have turned on internal screen capture by calling StartScreenVideoCapture{@link #StartScreenVideoCapture}. <br>
 *        + This function only works when the screen source is a screen rather than an application window. See: ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.
 */
- (void)UpdateScreenCaptureFilterConfig:(NSArray<NSNumber *> * _Nullable) excludedWindowList;;
/** 
 * @type api
 * @hidden(iOS)
 * @region  screen share
 * @brief  Get the thumbnail of the screen
 * @param sourceType Type of the screen capture object. See ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.
 * @param sourceId ID of the screen-shared object.
 * @param maxWidth Maximum width
 * @param maxHeight Maximum height
 * @return The thumbnail of the sharing object. <br>
 *         The thumbnail is of the same width-height ratio of the object. The size of the trumbnail is no larger than the specified size.
 */
- (ByteRTCImage *_Nonnull)getScreenCaptureSourceThumbnail:(ByteRTCScreenCaptureSourceType)sourceType sourceId:(intptr_t)sourceId maxWidth:(int)maxWidth maxHeight:(int)maxHeight;
/** 
 * @hidden
 * @type api
 */
+ (ByteRTCAudioDeviceManager *_Null_unspecified)createAudioDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/** 
 * @type api
 * @hidden(iOS)
 * @region audio management
 * @author dixing
 * @brief Get ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 * @return ByteRTCAudioDeviceManager{@link #ByteRTCAudioDeviceManager}
 */
- (ByteRTCAudioDeviceManager *_Null_unspecified)getAudioDeviceManager;
/** 
 * @type api
 * @hidden(iOS)
 * @region Video Device Management
 * @author zhangzhenyu.samuel
 * @brief Get ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 * @return ByteRTCVideoDeviceManager{@link #ByteRTCVideoDeviceManager}
 */
- (ByteRTCVideoDeviceManager * _Null_unspecified)getVideoDeviceManager;

#pragma mark - ASR
/** 
 * @hidden
 * @type api
 * @region speech recognition service
 * @author wangjunzheng
 * @brief Enables automatic speech recognition service. This method converts the recognized user's voice into text and calls it back to the user via the onMessage:{@link #ByteRTCASREngineEventHandler#onMessage:} event.
 * @param handler The speech recognition service uses a status callback. See ByteRTCASREngineEventHandler{@link #ByteRTCASREngineEventHandler}
 * @param asrConfig Check information. See ByteRTCASRConfig{@link #ByteRTCASRConfig}
 */
- (void)startASR:(ByteRTCASRConfig *_Nonnull)asrConfig handler:(id<ByteRTCASREngineEventHandler> _Nonnull)handler ;
/** 
 * @hidden
 * @type api
 * @region  speech recognition service
 * @author wangjunzheng
 * @brief  Turn off speech recognition service
 */
- (void)stopASR;

#pragma mark - FileRecording
/** 
 * @type api
 * @region Local recording
 * @author wunailiang
 * @brief This method records the audio & video data during the call to a local file.
 * @param streamIndex Stream property, specify whether to record mainstream or screen stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param recordingConfig Local recording parameter configuration. See ByteRTCRecordingConfig{@link #ByteRTCRecordingConfig}
 * @return    <br>
 *         + 0: normal
 *         + -1: Parameter setting exception
 *         + -2: The current version of the SDK does not support this feature, please contact technical support
 * @notes   <br>
 *         + After calling this method, you will receive rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} callback. <br>
 *         + If the recording is normal, the system will notify the recording progress through rtcEngine:onRecordingProgressUpdate:process:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingProgressUpdate:process:recording_info:} callback every second.
 */
- (int)startFileRecording:(ByteRTCStreamIndex)streamIndex
      withRecordingConfig:(ByteRTCRecordingConfig* _Nonnull)recordingConfig type:(ByteRTCRecordingType)recordingType;

/** 
 * @type api
 * @region Local recording
 * @author wunailiang
 * @brief Stop local recording
 * @param streamIndex Stream property, specify to stop mainstream or screen stream recording. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @notes   <br>
 *         + After calling startFileRecording:withRecordingConfig:type:{@link #ByteRTCEngineKit#startFileRecording:withRecordingConfig:type:} to start local recording, you must call this method to stop recording. <br>
 *         + After calling this method, you will receive rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:{@link #ByteRTCEngineDelegate#rtcEngine:onRecordingStateUpdate:state:error_code:recording_info:} callback prompting you to record the result.
 */
- (void)stopFileRecording:(ByteRTCStreamIndex)streamIndex;

/** 
  * @type api
  * @region  mixing
  * @author majun.lvhiei
  * @brief  Mixing management interface creation
  * @return  Mixing management instance. See ByteRTCAudioMixingManager{@link #ByteRTCAudioMixingManager}
  */
- (ByteRTCAudioMixingManager *_Nullable)getAudioMixingManager;

#pragma mark - Rtm
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Log in to send P2P messages or send messages to a server without joining the RTC room.<br>
 *        To log out, call logout{@link #ByteRTCEngineKit#logout}.
 * @param token   <br>
 *        Token is required during login for authentication. <br>
 *        This Token is different from that required by calling joinRoom. You can assign any value even null to `roomId` to generate a login token. During developing and testing, you can use temporary tokens generated on the console. Deploy the token generating application on your server.
 * @param uid   <br>
 *        User ID <br>
 *        User ID is unique within one appid.
 * @return <br>
 *        + `0`: Success<br>
 *        + `-1`: Failure due to invalid parameter<br>
 *        + `-2`: Invalid call. RTC will return this value when you call this API after the user has been logged in to the server. <br>
 *        + `-3`: Failure due to an empty Engine instance. Create an Engine instance by calling initWithAppId:delegate:parameters:{@link #ByteRTCEngineKit#initWithAppId:delegate:parameters:} before calling this API.
 * @notes  You will receive rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} after calling this API and log in successfully. But remote users will not receive notification about that.
 */
- (int64_t)login:(NSString * _Nonnull)token uid:(NSString * _Nonnull)uid;
/** 
 * @type After api
 * @region  real-time messaging
 * @author hanchenchen.c
 * @brief  Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
 * @notes   <br>
 *        + Before calling this interface to log out, login:uid:{@link #ByteRTCEngineKit#login:uid:} Login <br>
 *        + After local users call this method to log out, they will receive rtcEngineOnLogout:{@link #ByteRTCEngineDelegate#rtcEngineOnLogout:} callback notification results, and remote users will not receive notifications.
 */
- (void)logout;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Update the Token <br>
 *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
 *         When calling the login:uid:{@link #ByteRTCEngineKit#login:uid:} method to log in, if an expired token is used, the login will fail and will receive rtcEngine:onLoginResult:errorCode:elapsed:{@link #ByteRTCEngineDelegate#rtcEngine:onLoginResult:errorCode:elapsed:} callback notification with the error code ByteRTCLoginErrorCodeInvalidToken. You need to reacquire the token and call this method to update the token.
 * @param token   <br>
 *        Updated dynamic key <br>
 * @notes   <br>
 *        + If the token is invalid and the login fails, call this method to update the token, and the SDK will automatically log in again. The user does not need to call the login:uid:{@link #ByteRTCEngineKit#login:uid:} method. <br>
 *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
 */
- (void)updateLoginToken:(NSString * _Nonnull)token;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Set application server parameters   <br>
 *        Client side calls sendServerMessage:{@link #ByteRTCEngineKit#sendServerMessage:} or sendServerBinaryMessage:{@link #ByteRTCEngineKit#sendServerBinaryMessage:} Before sending a message to the application server, you must set a valid signature and application server address.
 * @param signature   <br>
 *        Dynamic Signature <br>
 *        The service server uses this signature to authenticate the request. <br>
 * @param url   <br>
 *         Address of the application server
 * @notes   <br>
 *        + The user must call login:uid:{@link #ByteRTCEngineKit#login:uid:} before logging in to call this interface. <br>
 *        + After calling this interface, the SDK will use rtcEngine:onServerParamsSetResult:{@link #ByteRTCEngineDelegate#rtcEngine:onServerParamsSetResult:} to return the corresponding result.
 */
- (void)setServerParams:(NSString * _Nonnull)signature url:(NSString * _Nonnull)url;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Query the login status of the opposite or local user
 * @param peerUserId   <br>
 *        User ID to query
 * @notes   <br>
 *        + You must call login:uid:{@link #ByteRTCEngineKit#login:uid:} After logging in, you can call this interface. <br>
 *        + After calling this interface, the SDK will use rtcEngine:onGetPeerOnlineStatus:status:{@link #ByteRTCEngineDelegate#rtcEngine:onGetPeerOnlineStatus:status:} callback to notify the query result. <br>
 *        + Before sending an out-of-room message, the user can know whether the peer user is logged in through this interface to decide whether to send a message. You can also check your login status through this interface.
 */
- (void)getPeerOnlineStatus:(NSString * _Nonnull)peerUserId;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Send a text message (P2P) to a specified user outside the room
 * @param userId   <br>
 *        Message Receives the user's ID
 * @param messageStr   <br>
 *        Text message content sent <br>
 *        Message does not exceed 62KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return   <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, RtcEngine instance not created <br>
 *         + -2: Sent failed, userId is empty
 * @notes   <br>
 *        + Before sending an out-of-room text message, you should call login:uid:{@link #ByteRTCEngineKit#login:uid:} to complete login. <br>
 *        + After the user calls this interface to send a text message, he will receive an rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} callback to know whether the message was sent successfully; <br>
 *        + If the text message is sent successfully, the user specified by the userId will receive the message through rtcEngine:onUserMessageReceivedOutsideRoom:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageReceivedOutsideRoom:message:} callback.
 */
- (int64_t)sendUserMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSString * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Send binary messages (P2P) to the specified user outside the room
 * @param userId   <br>
 *        Message receiving user's ID
 * @param messageStr   <br>
 *        Binary message content sent <br>
 *        Message does not exceed 46KB.
 * @param config Message type, see ByteRTCMessageConfig{@link #ByteRTCMessageConfig}.
 * @return   <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, RtcEngine instance not created <br>
 *         + -2: Sent failed, userId is empty
 * @notes   <br>
 *        + Before sending out-of-room binary messages, you must call login:uid:{@link #ByteRTCEngineKit#login:uid:} to complete login. <br>
 *        + After the user calls this interface to send a binary message, he will receive an rtcEngine:onUserMessageSendResultOutsideRoom:error:{@link #ByteRTCEngineDelegate#rtcEngine:onUserMessageSendResultOutsideRoom:error:} callback to notify whether the message was sent successfully; <br>
 *        + If the binary message is sent successfully, the user specified by the userId will use rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:{@link #ByteRTCEngineDelegate#rtcEngine:onUserBinaryMessageReceivedOutsideRoom:message:} callback Receive the message.
 */
- (int64_t)sendUserBinaryMessageOutsideRoom:(NSString * _Nonnull)userId message:(NSData * _Nonnull)messageStr config:(ByteRTCMessageConfig)config;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Client side sends a text message to the application server (P2Server)
 * @param messageStr   <br>
 *        The content of the text message sent <br>
 *        The message does not exceed 62KB.
 * @return   <br>
 *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Sent failed, RtcEngine instance not created
 * @notes   <br>
 *        + Before sending a text message to the application server, you must first call login:uid:{@link #ByteRTCEngineKit#login:uid:} to complete the login, and then call setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} Set up the application server. <br>
 *        + After calling this interface, you will receive an rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCEngineDelegate#rtcEngine:onServerMessageSendResult:error:message:} callback to inform the message sender whether the message was sent successfully. <br>
 *        + If the text message is sent successfully, the application server that previously called setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} will receive the message.
 */
- (int64_t)sendServerMessage:(NSString * _Nonnull)messageStr;
/** 
 * @type api
 * @region Real-time messaging
 * @author hanchenchen.c
 * @brief Client side sends binary messages to the application server (P2Server)
 * @param messageStr   <br>
 *        Binary message content sent <br>
 *        Message does not exceed 46KB.
 * @return   <br>
 *         + > 0: Send successfully, return the number of the sent message, increment from 1 <br>
 *         + -1: Send failed, RtcEngine instance not created
 * @notes   <br>
 *        + Before sending a binary message to the application server, call login:uid:{@link #ByteRTCEngineKit#login:uid:} to complete the login, then call setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} Set up the application server. <br>
 *        + After calling this interface, you will receive an rtcEngine:onServerMessageSendResult:error:message:{@link #ByteRTCEngineDelegate#rtcEngine:onServerMessageSendResult:error:message:} callback to inform the message sender that the sending succeeded or failed; <br>
 *        + If the binary message is sent successfully, the application server that previously called setServerParams:url:{@link #ByteRTCEngineKit#setServerParams:url:} will receive the message.
 */
- (int64_t)sendServerBinaryMessage:(NSData * _Nonnull)messageStr;

/** 
 * @type api
 * @region Pre-call network detection
 * @author hanchenchen.c
 * @brief Pre-call network detection
 * @param is_test_uplink   Whether to detect uplink bandwidth
 * @param expected_uplink_bitrate   Expected uplink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
 * @param is_test_downlink  Whether to detect downlink bandwidth
 * @param expected_downlink_bitrate   Expected downlink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
 * @return   <br>
 *         + > 0: probe started successfully <br>
 *         + -1: Probe started failed. Parameter error, both uplink and downlink probes are false, or the expected bandwidth exceeds the range [100,10000] <br>
 *         + -2: Failed to start probing. Push-pull flow has started <br>
     *         + -3: Probe has started <br>
 * @notes   <br>
 *        + After calling this interface, you will receive rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkDetectionResult:quality:rtt:lostRate:bitrate:jitter:} Callback to notify the probe result; <br>
 *        + If the probe stops, you will receive rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkDetectionStopped:} Notify probe to stop.
 */
- (ByteRTCNetworkDetectionStartReturn)startNetworkDetection:(bool)is_test_uplink uplinkBandwidth:(int)expected_uplink_bitrate downlink:(bool)is_test_downlink downlinkBandwidth:(int)expected_downlink_bitrate;

/** 
 * @type api
 * @region Pre-call network probe
 * @author hanchenchen.c
 * @brief Stop pre-call network probe
 * @notes   <br>
 *        + After calling this interface, you will receive an rtcEngine:onNetworkDetectionStopped:{@link #ByteRTCEngineDelegate#rtcEngine:onNetworkDetectionStopped:} notification to stop the probe.
 */
- (void)stopNetworkDetection;

#pragma mark  ScreenAudio

/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Sets the screen audio source type. (internal capture/custom capture)
 * @param sourceType Screen audio source type. See ByteRTCAudioSourceType{@link #ByteRTCAudioSourceType}.
 * @notes   <br>
 *       + The default screen audio source type is RTC SDK internal capture. <br>
 *       + You should call this API before calling publishScreen:{@link #ByteRTCEngineKit#publishScreen:}. Otherwise, you will receive rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:} with 'ByteRTCWarningSetScreenAudioSourceTypeFailed'. <br>
 *       + When using internal capture, you need to call startScreenCapture:bundleId:{@link #ByteRTCEngineKit#startScreenCapture:bundleId:} to start capturing.
 *       + When using custom capture, you need to call pushScreenAudioFrame:{@link #ByteRTCEngineKit#pushScreenAudioFrame:} to push the audio stream to the RTC SDK. <br>
 *       + Whether you use internal capture or custom capture, you must call publishScreen:{@link #ByteRTCEngineKit#publishScreen:} to publish the captured screen audio stream.
 */
- (void) setScreenAudioSourceType:(ByteRTCAudioSourceType)sourceType;

/** 
 * @type api
 * @region Screen sharing
 * @author liyi.000
 * @brief Set the mix mode of the screen audio stream and the audio stream collected by the microphone when the screen is shared
 * @param index Mix mode. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex} <br>
 *         + 'ByteRTCStreamIndexMain': Mix the audio stream collected by the screen audio stream and the microphone <br>
 *         + 'ByteRTCStreamIndexScreen': Divide the screen audio stream and the audio stream collected by the microphone into two audio streams
 * @notes You should call this method before publishScreen:{@link #ByteRTCEngineKit#publishScreen:}. Otherwise, you will receive 'ByteRTCWarningSetScreenAudioStreamIndexFailed' from rtcEngine:onWarning:{@link #ByteRTCEngineDelegate#rtcEngine:onWarning:}
 */
- (void) setScreenAudioStreamIndex:(ByteRTCStreamIndex) index;

/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Using a custom capture method, when capturing screen audio during screen sharing, push the audio frame to the RTC SDK for encoding and other processing.
 * @param audioFrame Audio data frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 * @return Method call result   <br>
 *         + 0: Setup succeeded <br>
 *         + < 0: Setup failed <br>
 * @notes   <br>
 *         + ScresetenAudioSourceType must be called before calling this interface to push custom captured audio data during screen sharing: { @Link #setScreenAudioSourceType:} Enable custom capture of screen audio. <br>
 *         + You should call this method every 10 milliseconds to push a custom captured audio frame. A push audio frame should contain frame.sample _rate/100 audio sample points. For example, if the sampling rate is 48000Hz, 480 sampling points should be pushed each time. <br>
 *         + The audio sampling format is S16. The data format in the audio buffer must be PCM data, and its capacity size should be samples × frame.channel × 2. <br>
 *         + This function runs within user-level threads. If other processes are running at the same time, this process will be interrupted. <br>
 *         + After calling this interface to push the custom captured audio frame to the RTC SDK, you must call publishScreen:{@link #ByteRTCEngineKit#publishScreen:} to push the captured screen audio to the remote end. Audio frame information pushed to the RTC SDK is lost before calling publishScreen:{@link #ByteRTCEngineKit#publishScreen:}.
 */
- (int) pushScreenAudioFrame:(ByteRTCAudioFrame* _Nonnull)audioFrame;

#pragma mark EncodedVideo
/** 
 * @type api
 * @region Video Management
 * @author wangzhanqiang
 * @brief Set the video source input to the RTC SDK.
 *        The internal video capture is the default, which refers to capturing video using the built-in module.
 * @param type Video source type. Refer to ByteRTCVideoSourceType{@link #ByteRTCVideoSourceType} for more details.
 * @param streamIndex Stream index. Refer to ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for more details.
 * @notes   <br>
 *         + You can call this API whether the user is in a room or not. <br>
 *         + Calling this API to switch to the custom video source will stop the enabled internal video capture.
 *         + To switch to internal video capture, call this API to stop custom capture and then call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to enable internal video capture.
 *         + To push custom encoded video frames to the SDK, call this API to switch `ByteRTCVideoSourceType` to `ByteRTCVideoSourceTypeEncodedManualSimulcast` or `ByteRTCVideoSourceTypeEncodedAutoSimulcast`.

 */
- (void)setVideoSourceType:(ByteRTCVideoSourceType)type WithStreamIndex:(ByteRTCStreamIndex)streamIndex;

/** 
 * @type api
 * @region Video management
 * @author wangzhanqiang
 * @brief Register custom encoded frame push event callback
 * @param handler Custom encoded frame callback class. See ByteRTCExternalVideoEncoderEventHandler{@link #ByteRTCExternalVideoEncoderEventHandler}
 * @notes   <br>
 *        + This method needs to be called before entering the room. <br>
 *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
 */
- (void)setExternalVideoEncoderEventHandler:(id<ByteRTCExternalVideoEncoderEventHandler> _Nullable)handler;

/** 
 * @type api
 * @region Video management
 * @author wangzhanqiang
 * @brief Push custom encoded video stream
 * @param streamIndex The properties of the encoded stream that need to be pushed. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex The corresponding encoded stream subscript, starting from 0, if you call SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} The number of multiple streams must be consistent here
 * @param videoFrame Encoding For streaming video frame information. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}. <br>
 * @notes   <br>
 *         + Currently, only video frames in H264 and ByteVC1 formats are supported, and the video stream protocol must be in an Annex B format. <br>
 *         + This function runs within the user calling thread <br>
 *         + Before pushing a custom encoded video frame, you must call setVideoSourceType:WithStreamIndex:{@link #ByteRTCEngineKit#setVideoSourceType:WithStreamIndex:} to switch the video input source to the custom encoded video source.
 */
- (BOOL)pushExternalEncodedVideoFrame:(ByteRTCStreamIndex)streamIndex
                       withVideoIndex:(NSInteger)videoIndex
                withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;

/** 
 * @type api
 * @region Video Management
 * @author wangzhanqiang
 * @brief Before subscribing to the remote video stream, set the remote video data decoding method
 * @param key The remote stream information specifies which video stream to decode. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param config  Video decoding method. See ByteRTCVideoDecoderConfig{@link #ByteRTCVideoDecoderConfig}.
 * @notes   <br>
 *         + This method is suitable for manual subscription mode and is used before subscribing to remote flows. <br>
 *         + When you want to custom decode a remote stream, you need to call registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerRemoteEncodedVideoFrameObserver:} Register the remote video stream monitor, and then call the interface to set the decoding method to custom decoding. The monitored video data is called back through onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:}.
 */
- (void)setVideoDecoderConfig:(ByteRTCRemoteStreamKey * _Nonnull)key
       withVideoDecoderConfig:(ByteRTCVideoDecoderConfig)config;

/** 
 * @type api
 * @region Video Management
 * @author wangzhanqiang
 * @brief After subscribing to the remote video stream, request the keyframe
 * @param key Remote stream information to the remote. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @notes   <br>
 *         + This method is only suitable for manual subscription mode and is used after successful subscription to the remote flow. <br>
 *         + This method is suitable for calling setVideoDecoderConfig:withVideoDecoderConfig:{@link #ByteRTCEngineKit#setVideoDecoderConfig:withVideoDecoderConfig:} After the custom decoding function is turned on, and the custom decoding fails
 */
- (void)requestRemoteVideoKeyFrame:(ByteRTCRemoteStreamKey * _Nonnull)key;

/** 
 * @type api
 * @region  video management
 * @author wangzhanqiang
 * @brief  Video data callback after registering remote encoding.   <br>
 *         After registration, when the SDK detects a remote encoded video frame, onRemoteEncodedVideoFrame:withEncodedVideoFrame:{@link #ByteRTCRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame:withEncodedVideoFrame:} callback
 * @param observer Remote encoded video data monitor. See ByteRTCRemoteEncodedVideoFrameObserver{@link #ByteRTCRemoteEncodedVideoFrameObserver}
 * @notes   <br>
 *        + This method needs to be called before entering the room. <br>
 *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
 */
- (void)registerRemoteEncodedVideoFrameObserver:(id<ByteRTCRemoteEncodedVideoFrameObserver> _Nullable)observer;

#pragma mark StreamSyncInfo
/** 
 * @type api
 * @region Audio management
 * @author wangjunzheng
 * @brief Send audio stream synchronization information. The message is sent to the remote end through the audio stream and synchronized with the audio stream. After the interface is successfully called, the remote user will receive rtcEngine:onStreamSyncInfoReceived:streamType:data:{@link #ByteRTCEngineDelegate#rtcEngine:onStreamSyncInfoReceived:streamType:data:}.
 * @param data Message content.
 * @param config  For configuration of media stream information synchronization. See ByteRTCStreamSycnInfoConfig{@link #ByteRTCStreamSycnInfoConfig}.
 * @return   <br>
 *         + > = 0: Message sent successfully. Returns the number of successful sends. <br>
 *         + -1: Message sending failed. Message length greater than 16 bytes. <br>
 *         + -2: Message sending failed. The content of the incoming message is empty. <br>
 *         + -3: Message sending failed. This screen stream was not published when the message was synchronized through the screen stream. <br>
 *         + -4: Message sending failed. This audio stream is not yet published when you synchronize messages with an audio stream captured by a microphone or custom device, as described in the error code ByteRTCErrorCode{@link #ByteRTCErrorCode}. <br>
 * @notes When using `ByteRTCRoomProfileLiveBroadcasting` as room profile, the data will be delivered. For other coom profiles, the data may be lost when the local user is muted.
 */
- (int)sendStreamSyncInfo:(NSData* _Nonnull)data config:(ByteRTCStreamSycnInfoConfig * _Nonnull)config;

#pragma mark ForwardStream
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Start relaying media stream across rooms. <br>
     *        After a user joins a room, you can call this method to publish the media stream to multiple rooms that applies to scenarios such as an online talent contest and so on.
     * @param configurations Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more inforamtion.
     * @return  <br>
     *        0: Success
     *        <0: Failure  <br>
     * @notes <br>
     *        + Call this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:}.
     *        + After calling this method, listen the events from each room during the relaying by registering rtcRoom:onForwardStreamEvent:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamEvent:}.
     *        + Once the relaying begins, the other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}.
     *        + Call updateForwardStreamToRooms:{@link #ByteRTCEngineKit#updateForwardStreamToRooms:} to add or remove the designated room(s) after calling this method.
     *        + Call stopForwardStreamToRooms{@link #ByteRTCEngineKit#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.
     *        + Call pauseForwardStreamToAllRooms{@link #ByteRTCEngineKit#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
- (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Update information of the rooms where you want to relay the media stream to after calling startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:}. <br>
     *        Adding and removing rooms by calling this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} on the local.
     * @param configurations Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  <br>
     *          0: Success
     *          <0: Failure  <br>
     * @notes <br>
     *        + Users in the room which is added by calling this method will receive rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}.
     *        + Users in the room which is removed by calling this method will receive rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}} and rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:}.
     */
- (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call to this method to stop relaying media stream to all rooms after calling startForwardStreamToRooms{@link #ByteRTCEngineKit#startForwardStreamToRooms:}. <br>
     * @notes <br>
     *        + Call this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:}.
     *        + The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you stop relaying.
     *        + To stop relaying media stream to specific rooms, call updateForwardStreamToRooms:{@link #ByteRTCEngineKit#updateForwardStreamToRooms:} instead.
     *        + To resume the relaying in a short time, call pauseForwardStreamToAllRooms{@link #ByteRTCEngineKit#pauseForwardStreamToAllRooms} instead and then call resumeForwardStreamToAllRooms{@link #ByteRTCEngineKit#resumeForwardStreamToAllRooms} to recsume after that.
     */
- (void)stopForwardStreamToRooms;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call this method to pause relaying media stream to all rooms after calling startForwardStreamToRooms{@link #ByteRTCEngineKit#startForwardStreamToRooms:}. <br>
     *        After that, call resumeForwardStreamToAllRooms{@link #ByteRTCEngineKit#resumeForwardStreamToAllRooms} to resume.
     * @notes The other users in the room will receive callback of rtcEngine:onUserUnPublishStream:type:reason:{@link #ByteRTCEngineDelegate#rtcEngine:onUserUnPublishStream:type:reason:}} and rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} when you pause relaying.
     */
- (void)pauseForwardStreamToAllRooms;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call this method to resume relaying to all rooms from the pause by calling pauseForwardStreamToAllRooms{@link #ByteRTCEngineKit#pauseForwardStreamToAllRooms}.
     * @notes The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you resume relaying.
     */
- (void)resumeForwardStreamToAllRooms;

/** 
 * @type api
 * @region Media stream management
 * @author yangpan
 * @brief Control the playinging status of the local audio stream: play/not play   <br>
 * @param muteState Playinging status to identify whether to play the local audio stream, see: ByteRTCMuteState{@link #ByteRTCMuteState}
 * @notes This method only controls the local audio The playinging state of the stream does not affect the local audio play device.
 */
- (void)muteAudioPlayback:(ByteRTCMuteState)muteState;


/** 
 * @type api
 * @region  Audio & Video Processing
 * @author yanjing
 * @brief Adds watermark to designated video stream.
 * @param streamIndex Targeting stream index of the watermark. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param imagePath File path of the watermark image. You can use the absolute path or the asset path(/assets/xx.png). The path should be less than 512 bytes. <br>
 *        The watermark image should be in PNG or JPG format.
 * @param rtcWatermarkConfig Watermark configurations. See ByteRTCVideoWatermarkConfig{@link #ByteRTCVideoWatermarkConfig}.
 * @notes <br>
 *        + Call ClearVideoWatermark{@link #ByteRTCEngineKit#ClearVideoWatermark:} to remove the watermark on the designated video stream. <br>
 *        + You can only add one watermark to one video stream. The newly added watermark replaces the previous one. You can call this API multiple times to add watermarks to different streams. <br>
 *        + You can call this API before and after joining room. <br>
 *        + If you mirror the preview, or the preview and the published stream, the watermark will also be mirrored locally, but the published watermark will not be mirrored. <br>
 *        + When you enable simulcast mode, the watermark will be added to all video streams, and it will scale down to smaller encoding configurations accordingly. <br>
 */
- (void)SetVideoWatermark:(ByteRTCStreamIndex)streamIndex
            WithImagePath:(NSString * _Nullable)imagePath
   WithRTCWatermarkConfig:(ByteRTCVideoWatermarkConfig* _Nonnull)rtcWatermarkConfig;

/** 
 * @type api
 * @region  Audio & Video Processing
 * @author yanjing
 * @brief  Removes video watermark from designated video stream.
 * @param streamIndex Targeting stream index of the watermark. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 */
- (void)ClearVideoWatermark:(ByteRTCStreamIndex)streamIndex;
/** 
 * @type api
 * @region  cloud proxy
 * @author daining.nemo
 * @brief  Start cloud proxy
 * @param  cloudProxiesInfo cloud proxy informarion list. See ByteRTCCloudProxyInfo{@link #ByteRTCCloudProxyInfo}.
 * @notes   <br>
 *         + Call this API before joining the room.<br>
 *         + Start pre-call network detection after starting cloud proxy. <br>
 *         + After starting cloud proxy and connects the cloud proxy server successfully, receives rtcEngine:onCloudProxyConnected:{@link #ByteRTCEngineDelegate#rtcEngine:onCloudProxyConnected:}. <br>
 *         + To stop cloud proxy, call stopCloudProxy{@link #ByteRTCEngineKit#stopCloudProxy}.
 */
- (void)startCloudProxy:(NSArray <ByteRTCCloudProxyInfo *> * _Nullable)cloudProxiesInfo;
/** 
 * @type api
 * @region  cloud proxy
 * @author daining.nemo
 * @brief  Stop cloud proxy
 * @notes To start cloud proxy, call startCloudProxy:{@link #ByteRTCEngineKit#startCloudProxy:}.
 */
- (void)stopCloudProxy;
@end
