/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room
*/

#import <CoreMedia/CMTime.h>
#import "ByteRTCDefines.h"
#import "ByteRTCRangeAudio.h"
#import "ByteRTCSpatialAudio.h"

@class RTCRoom;

/** 
 * @type callback
 * @brief  Room event callback interface
 */
@protocol RTCRoomDelegate <NSObject>
@optional

 /** 
  * @type callback
  * @region Multi-room
  * @author shenpengliang
  * @brief Callback on room state changes. You will receive this callback when you join the room, leave the room, or receive room relating warnings and errors.
  * @param roomId  Room ID.
  * @param uid  User ID.
  * @param state Room state code. <br>
  *              + 0: Success. <br>
  *              + !0: Failure. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
  * @param extraInfo Extra information.
  *                 `joinType` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rehoins the room. <br>
  *                 `elapsed` indicates the time interval from calling joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} to successfully joining room, in ms.
  */
- (void)rtcRoom:(RTCRoom *_Nonnull)rtcRoom
    onRoomStateChanged:(NSString *_Nonnull)roomId
             withUid:(nonnull NSString *)uid
           state:(NSInteger)state
           extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @type callback
 * @region Multi-room
 * @author shenpengliang
 * @brief Callback on stream state changes. You will receive this callback when you receive stream relating warnings and errors.
 * @param roomId  Room ID.
 * @param uid  User ID.
 * @param state Room state code. See ByteRTCErrorCode{@link #ByteRTCErrorCode} and ByteRTCWarningCode{@link #ByteRTCWarningCode} for specific indications.
 * @param extraInfo Extra information. Currently unavailable.
 */
- (void)rtcRoom:(RTCRoom *_Nonnull)rtcRoom
   onStreamStateChanged:(NSString *_Nonnull)roomId
            withUid:(nonnull NSString *)uid
          state:(NSInteger)state
          extraInfo:(NSString *_Nonnull)extraInfo;

/** 
 * @hidden
 * @type callback
 * @region Multiple rooms
 * @author shenpengliang
 * @brief Leave the room successfully callback.   <br>
 *        When the user invokes the leaveRoom{@link #RTCRoom#leaveRoom} method, the SDK stops all publish subscription streams and releases all call-related audio & video resources. This callback notifies the user when the SDK completes all resource releases. <br>
 * @param rtcRoom  RTCRoom object. <br>
 * @param stats For the statistics of this call, please refer to the data structure ByteRTCRoomStats{@link #ByteRTCRoomStats}. <br>
 * @notes   <br>
 *        + After the user calls the leaveRoom{@link #RTCRoom#leaveRoom} method to leave the room, if the destroyEngine{@link #destroyEngine} method is called to destroy the RTC engine immediately, this callback event will not be received. <br>
 *        + If the App needs to use the system audio & video device after leaving the room to end the call, it is recommended to initialize the audio & video device after receiving this callback, otherwise the App may fail to initialize the audio & video device due to SDK occupation. <br>
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onLeaveRoomWithStats:(ByteRTCRoomStats *_Nonnull)stats;

 /** 
  * @hidden
  * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
  * @type callback
  * @region Multiple rooms
  * @author shenpengliang
  * @brief Warning callback occurred.   <br>
  *        A warning occurred during the SDK runtime. The SDK usually recovers automatically and warnings can be ignored.
  * @param rtcRoom RTCRoom object.
  * @param warningCode Warning code. See enumeration type ByteRTCWarningCode{@link #ByteRTCWarningCode}.
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomWarning:(ByteRTCWarningCode)warningCode;

/** 
 * @hidden
 * @deprecated since 341.1 by onRoomStateChanged and onStreamStateChanged
 * @type callback
 * @region Multiple rooms
 * @author shenpengliang
 * @brief Error callback occurred.   <br>
 *        An error occurred during the SDK runtime. The SDK usually does not recover automatically, and the app needs to take action.
 * @param rtcRoom  RTCRoom object.
 * @param errorCode  Error code. See enumeration type ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomError:(ByteRTCErrorCode)errorCode;

/** 
 * @type callback
 * @region Multi-Room
 * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync:{@link #RTCRoom#setMultiDeviceAVSync:} is called.
 * @param rtcRoom The ByteRTCRoom instance.
 * @param state A/V synchronization state, see ByteRTCAVSyncState{@link #ByteRTCAVSyncState}.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onAVSyncStateChange:(ByteRTCAVSyncState)state;

/** 
 * @type callback
 * @region Multiple rooms
 * @author liuzhiqiang.avcoder
 * @brief In-room call statistics callback.    <br>
 *        After the user enters the room and starts the call, he receives this callback every 2s.
 * @param rtcRoom  RTCRoom object.
 * @param stats Current RTCRoom statistics, see: ByteRTCRoomStats{@link #ByteRTCRoomStats}
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomStats:(ByteRTCRoomStats *_Nonnull)stats;

/** 
 * @type callback
 * @region Multi-room
 * @author liuzhiqiang.avcoder
 * @brief Local stream data statistics and network quality callback.   <br>
 *        After the local user publishes the flow successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the published flow during this reference period. <br>
 *         Statistics are passed to the user through the callback parameters of the ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} type, including the sent audio & video bit rate, sent frame rate, encoded frame rate, network quality, etc. <br>
 * @param rtcRoom  RTCRoom object. <br>
 * @param stats   Current room local stream data statistics. See: ByteRTCLocalStreamStats{@link #ByteRTCLocalStreamStats} <br>
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onLocalStreamStats:(ByteRTCLocalStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region Multi-room
 * @author liuzhiqiang.avcoder
 * @brief Remote audio/video stream statistics and network quality callbacks for local subscriptions.   <br>
 *        After the local user subscribes to the stream successfully, the SDK will periodically (2s) notify the user through this callback event of the quality statistics of the subscribed stream during this reference period, including: sending audio & video bit rate, sending frame rate, encoded frame rate, network quality, etc.
 * @param rtcRoom  RTCRoom object.
 * @param stats  Current room local stream statistics. See: ByteRTCRemoteStreamStats{@link #ByteRTCRemoteStreamStats}
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRemoteStreamStats:(ByteRTCRemoteStreamStats *_Nonnull)stats;

/** 
 * @type callback
 * @region Multi-room
 * @author shenpengliang
 * @brief Remote visible user joins room, or room invisible user switches to visible callback. <br>
 *        1. When a remote user calls the setUserVisibility:{@link #RTCRoom#setUserVisibility:} method to make itself visible and then join the room, other users in the room will receive the event. <br>
 *        2. When the remote visible user is disconnected and reconnected to the room, other users in the room will receive the event. <br>
 *        3. Invisible in the room When a remote user calls the setUserVisibility:{@link #RTCRoom#setUserVisibility:} method to switch to visible, other users in the room will receive the event. <br>
 *        4. New users will receive a callback notification from live streaming host role users who were in the room before entering the room. <br>
 * @param rtcRoom RTCRoom object. <br>
 * @param userInfo  For user information. See ByteRTCUserInfo{@link #ByteRTCUserInfo}. <br>
 * @param elapsed  Reserved field, meaningless
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserJoined:(ByteRTCUserInfo *_Nonnull)userInfo elapsed:(NSInteger)elapsed;

    /** 
     * @type callback
     * @author shenpengliang
     * @brief This callback is triggered when a remote user is disconnected or turns invisible.
     * @param uid ID of the user who leaves the room, or switches to invisible. <br>
     * @param reason Reason to leave the room: <br>
     *               + 0: The remote client calls leaveRoom{@link #RTCRoom#leaveRoom} to leave the room. <br>
     *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
     *               + 2: The remote client calls setUserVisibility:{@link #RTCRoom#setUserVisibility:} to turn invisible. <br>
     *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
     */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserLeave:(NSString *_Nonnull)uid reason:(ByteRTCUserOfflineReason)reason;
    /** 
     * @type callback
     * @brief You will be informed 30 sec before the expiration via this callback.
     *        Call updateToken:{@link #ByteRTCEngineKit#updateToken:} to renew the Token. If the Token expired, the user would be removed from the room and not be able to continue the call.
     */
- (void)onTokenWillExpire:( RTCRoom *_Nonnull)rtcRoom;

/** 
 * @hidden
 * @type callback
 * @region Multiroom
 * @author shenpengliang
 * @brief When a user in the room calls MuteAllRemoteAudio{@link #MuteAllRemoteAudio},
 *        Changing the state of receiving all remote audio streams, other users in the room receive this callback.
 * @param rtcRoom  RTCRoom object. <br>
 * @param uid  Change the user ID of the receive state
 * @param muteState  Receive state, see: ByteRTCMuteState{@link #ByteRTCMuteState}
 */

- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onMuteAllRemoteAudio:(NSString *_Nonnull)uid muteState:(ByteRTCMuteState)muteState;

/** 
 * @hidden
 * @type callback
 * @region Multiple rooms
 * @brief When the user in the room pauses/resumes receiving all video streams, other users in the room receive this callback. See MuteAllRemoteVideo{@link #MuteAllRemoteVideo}.
 * @param rtcRoom  RTCRoom object. <br>
 * @param uid  Pause/resume the user ID of the received video stream.
 * @param muteState Pause/resume receiving video streams. See ByteRTCMuteState{@link #ByteRTCMuteState}.
 */

- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onMuteAllRemoteVideo:(NSString *_Nonnull)uid withMuteState:(ByteRTCMuteState)muteState;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
  * @type callback
  * @region Multiple rooms
  * @author shenpengliang
  * @brief The following conditions trigger this callback: <br>
  *         + When users in the room post a new audio & video stream, other users in the room will receive this callback notification. <br>
  *         + When the user's original audio and video stream in the room is removed and the audio & video stream is republished, other users in the room will receive this callback notification. <br>
  *         + When the user first joins the room, he receives this callback, including all published streams in the room.
  * @param rtcRoom   RTCRoom object. <br>
  * @param stream  Stream property. See ByteRTCStream{@link #ByteRTCStream}. <br>
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onStreamAdd:(id<ByteRTCStream> _Nonnull)stream;

 /** 
  * @hidden
  * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
  * @type callback
  * @region Multi-room
  * @author shenpengliang
  * @brief When a remote user in the room stops publishing audio & video streams, local users will receive this callback notification.   <br>
  * @param rtcRoom RTCRoom object
  * @param uid User ID of the remote stream source. <br>
  * @param stream  The properties of the stream. See ByteRTCStream{@link #ByteRTCStream}. <br>
  * @param reason  For reasons of remote stream removal. See ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}. <br>
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    didStreamRemoved:(NSString *_Nonnull)uid
              stream:(id<ByteRTCStream> _Nonnull)stream
              reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on new media streams captured by camera/microphone in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes You will receive this callback after a remote user successfully published media streams captured by camera/microphone in the room with publishStream:{@link #RTCRoom#publishStream:}. Then you can choose whether to call subscribeStream:mediaStreamType:{@link #RTCRoom#subscribeStream:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on removal of remote media stream captured by camera/microphone.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @notes After receiving this callback, you can choose whether to call unSubscribeStream:mediaStreamType:{@link #RTCRoom#unSubscribeStream:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserUnPublishStream:(NSString *_Nonnull)userId            type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on new screen sharing media streams from remote users in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who published the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @notes You will receive this callback after a remote user successfully publishes screen sharing streams in the room with publishScreen:{@link #RTCRoom#publishScreen:}. Then you can choose whether to call subscribeScreen:mediaStreamType:{@link #RTCRoom#subscribeScreen:mediaStreamType:} to subscribe to the streams or not.
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserPublishScreen:(NSString *_Nonnull)userId   type:(ByteRTCMediaStreamType)type;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on removal of screen sharing media streams from remote users in the room.
 * @param rtcRoom The rtcRoom instance.
 * @param userId The ID of the remote user who removed the stream.
 * @param type Media stream type. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @param reason The reason for the removal, see ByteRTCStreamRemoveReason{@link #ByteRTCStreamRemoveReason}.
 * @notes After receiving this callback, you can choose whether to call unSubscribeScreen:mediaStreamType:{@link #RTCRoom#unSubscribeScreen:mediaStreamType:} to unsubscribe from the streams or not.
 */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onUserUnPublishScreen:(NSString *_Nonnull)userId type:(ByteRTCMediaStreamType)type
           reason:(ByteRTCStreamRemoveReason)reason;
/** 
 * @type callback
 * @region Room management
 * @author shenpengliang
 * @brief Callback on subscription status of media streams
 * @param rtcRoom The r rtcRoom instance.
 * @param state Subscription status of media streams, see ByteRTCSubscribeState{@link #ByteRTCSubscribeState}.
 * @param userId The ID of the user who published the stream.
 * @param info Configurations of stream subscription, see ByteRTCSubscribeConfig{@link #ByteRTCSubscribeConfig}.
 * @notes Local users will receive this callback:  <br>
 *        + After calling subscribeStream:mediaStreamType:{@link #RTCRoom#subscribeStream:mediaStreamType:}/unSubscribeStream:mediaStreamType:{@link #RTCRoom#unSubscribeStream:mediaStreamType:} to change the subscription status of remote media streams captured by camera/microphone.  <br>
 *        + After calling subscribeScreen:mediaStreamType:{@link #RTCRoom#subscribeScreen:mediaStreamType:}/unSubscribeScreen:mediaStreamType:{@link #RTCRoom#unSubscribeScreen:mediaStreamType:} to change the subscription status of remote screen sharing streams.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onStreamSubscribed:(ByteRTCSubscribeState)state
                userId:(NSString *_Nonnull)userId
       subscribeConfig:(ByteRTCSubscribeConfig *_Nonnull)info;

/** 
 * @hidden
 * @type callback
 * @region multiroom
 * @author shenpengliang
 * @brief Callback the event
 * @param rtcRoom  RTCRoom object when the release stream is successful. <br>
 * @param userId  User ID
 * @param isScreen  Whether the stream is a screen stream
 *
 */

- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onStreamPublishSuccess:(NSString *_Nonnull)userId isScreen:(BOOL)isScreen;

 /** 
  * @type callback
  * @region Multi-room
  * @author hanchenchen.c
  * @brief Receive this callback when you receive a broadcast text message from the room called sendRoomMessage:{@link #ByteRTCEngineKit#sendRoomMessage:}.
  * @param rtcRoom RTCRoom object
  * @param uid Message sender ID.
  * @param message The content of the received text message.
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomMessageReceived:(NSString *_Nonnull)uid
        message:(NSString *_Nonnull)message;

 /** 
  * @type callback
  * @region Multi-room
  * @author hanchenchen.c
  * @brief Receive this callback when you receive a broadcast binary message sent by the room call sendRoomBinaryMessage:{@link #RTCRoom#sendRoomBinaryMessage:}.
  * @param rtcRoom RTCRoom object
  * @param uid Message sender ID.
  * @param message The binary message content received.
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomBinaryMessageReceived:(NSString *_Nonnull)uid
        message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region Multi-room
  * @author hanchenchen.c
  * @brief Receive text messages (P2P) from other users in the room via sendUserMessage:message:{@link #RTCRoom#sendUserMessage:message:}.
  * @param rtcRoom RTCRoom object
  * @param uid The user ID of the sender of the message.
  * @param message The content of the received text message.
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onUserMessageReceived:(NSString *_Nonnull)uid
               message:(NSString *_Nonnull)message;

 /** 
 * @type callback
 * @region Multi-room
 * @author hanchenchen.c
 * @brief Receive a binary message from another user in the room via sendUserBinaryMessage:message:{@link #RTCRoom#sendUserBinaryMessage:message:} Receive this callback.
 * @param rtcRoom RTCRoom object
 * @param uid The user ID of the sender of the message.
 * @param message The binary message content received.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom
    onUserBinaryMessageReceived:(NSString *_Nonnull)uid
               message:(NSData *_Nonnull)message;

 /** 
  * @type callback
  * @region Multi-room
  * @author hanchenchen.c
  * @brief After sending a text or binary message (P2P) to a single user in the room, the message sender will receive a callback with the result of the message.
  * @param rtcRoom RTCRoom object.
  * @param msgid The ID of this message.
  * @param error Message result. See ByteRTCUserMessageSendResult{@link #ByteRTCUserMessageSendResult}
  * @notes   <br>
  *         + You should call sendUserMessage:message:{@link #RTCRoom#sendUserMessage:message:} to send a text message to a single user in the room <br>
  *         + You should call sendUserBinaryMessage:message:{@link #RTCRoom#sendUserBinaryMessage:message:} to send a binary message to a single user in the room
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onUserMessageSendResult:(int64_t)msgid error:(ByteRTCUserMessageSendResult)error;

 /** 
  * @type callback
  * @region Multi-room
  * @author hanchenchen.c
  * @brief After sending a text or binary message to all users in the room, the message sender will receive a callback with the result of the message.
  * @param rtcRoom RTCRoom object.
  * @param msgid The ID of this message.
  * @param error  Message sending results. See ByteRTCRoomMessageSendResult{@link #ByteRTCRoomMessageSendResult}
  * @notes   <br>
  *         + You should call sendRoomMessage:{@link #RTCRoom#sendRoomMessage:} Send a mass text message to the room <br>
  *         + You should call sendRoomBinaryMessage:{@link #RTCRoom#sendRoomBinaryMessage:} Send a mass binary message to the room
  */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onRoomMessageSendResult:(int64_t)msgid error:(ByteRTCRoomMessageSendResult)error;


/** 
 * @type callback
 * @region Video management
 * @author qipengxiang
 * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is invoked to disable/unban the sending of the specified user's video stream in the specified room.
 * @param uid Disabled/unbanned video stream user ID
 * @param banned Video stream sending status <br>
 *         + True: Video stream sending is disabled <br>
 *         + False: Video stream sending is unbanned
 * @notes   <br>
 *         + When the specified user in the room is banned/unbanned video stream sending, all users in the room will receive the callback. <br>
 *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
 *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onVideoStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

/** 
 * @type callback
 * @region Audio event callback
 * @author qipengxiang
 * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is called to disable/unban the sending of the specified user's audio and video stream in the specified room.
 * @param uid Disabled/unbanned audio stream user ID
 * @param banned Audio stream sending status <br>
 *         + True: Audio stream sending is disabled <br>
 *         + False: Audio stream sending is unbanned
 * @notes   <br>
 *         + When the specified user in the room is disabled/unbanned audio stream sending, all users in the room will receive the callback. <br>
 *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
 *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
 *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
 *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback.
 */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onAudioStreamBanned:(NSString *_Nonnull)uid isBanned:(BOOL)banned;

#pragma mark ForwardStream related callback
    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the state and errors during relaying the media stream to each of the rooms
     * @param rtcRoom RTCRoom object
     * @param infos Array of the state and errors of each designated room. Refer to ForwardStreamStateInfo{@link #ForwardStreamStateInfo} for more inforamtion.
     */
- (void)rtcRoom:( RTCRoom *_Nonnull)rtcRoom onForwardStreamStateChanged:(NSArray<ForwardStreamStateInfo *> * _Nonnull)infos;
    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the media stream to each room
     * @param rtcRoom RTCRoom object
     * @param infos Array of the event of each designated room. Refer to ForwardStreamEventInfo{@link #ForwardStreamEventInfo} for more information.
     */
- (void)rtcRoom:( RTCRoom * _Nonnull)rtcRoom onForwardStreamEvent:(NSArray<ForwardStreamEventInfo *> * _Nonnull)infos;
@end

/**
 * @type api
 */
BYTERTC_APPLE_EXPORT @interface RTCRoom : NSObject

@property(nonatomic, weak) id<RTCRoomDelegate> _Nullable delegate;

#pragma mark - Core Methods

/** 
 * @type api
 * @region multi-room
 * @author shenpengliang
 * @brief Leave and destroy the room created by calling createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:}.
 */
- (void)destroy;

/** 
 * @hidden
 * @type api
 * @region multiple rooms
 * @author shenpengliang
 * @brief Get room ID
 */
- (NSString *_Nullable)getRoomId;

/** 
 * @type api
 * @region Multi-room
 * @author shenpengliang
 * @brief By setting RTCRoomDelegate{@link #RTCRoomDelegate}, you can get infromed of events realted to this `RTCRoom` object.
 * @param roomDelegate Refer to RTCRoomDelegate{@link #RTCRoomDelegate}.
 */

- (void)setRtcRoomDelegate:(id<RTCRoomDelegate> _Nullable)roomDelegate;

/** 
 * @type api
 * @region Multiple rooms
 * @author shenpengliang
 * @brief Join the room. <br>
 *         Call createRtcRoom:{@link #ByteRTCEngineKit#createRtcRoom:} After creating a room, call this method to join the room and make audio & video calls with other users in the room. <br>
 * @param token  Dynamic key for authentication and verification of users entering the room. <br>
 *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. <br>
 *         Apps with different AppIDs are not interoperable. <br>
 *         Make sure that the AppID used to generate the Token is the same as the AppID used to create the engine, otherwise it will cause the join room to fail. <br>
 * @param userInfo  User ID. See ByteRTCUserInfo{@link #ByteRTCUserInfo}. <br>
 * @param roomConfig  Room parameter configuration, set the room mode and whether to automatically publish or subscribe to the flow. See ByteRTCRoomConfig{@link #ByteRTCRoomConfig} for the specific configuration mode. <br>
 * @return  Method call result.   <br>
 *         + 0: Success <br>
 *         + -1: Invalid parameter <br>
 *         + -2: Already in the room. After the interface call is successful, as long as the return value of 0 is received and leaveRoom{@link #RTCRoom#leaveRoom} is not called successfully, this return value will be triggered when the room entry interface is called again, regardless of whether the filled room ID and user ID are duplicated. <br>
 *         + -3: Room is empty <br>
 * @notes   <br>
 *         + In the same room with the same AppID, the user ID of each user must be unique. If two users have the same user ID, the user who joined the room later will kick the user who joined the room first out of the room, and the user who joined the room first will receive rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:} callback notification, the error type is duplicate login BRERR_DUPLICATE_LOGIN. <br>
 *         + Local users will receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} callback notification after calling this method to join the room successfully. <br>
 *         + Local users call setUserVisibility:{@link #RTCRoom#setUserVisibility:} to add the room after making itself visible, and remote users will receive rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} callback notification. <br>
 *         + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After successful reconnection, you will receive a callback notification from rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} locally. <br>
 */
- (int)joinRoomByToken:(NSString *_Nullable)token userInfo:(ByteRTCUserInfo *_Nonnull)userInfo roomConfig:(ByteRTCRoomConfig *_Nonnull)roomConfig;

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
 *            - Switch from `false` to `true`: rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}<br>
 *            - Switch from `true` to `false`: rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} <br>
 *        + The invisible user will receive the warning code, `ByteRTCWarningCodeSubscribeStreamForbiden`, when trying to publish media streams.
 */
- (BOOL)setUserVisibility:(BOOL)enable;

/** 
 * @hidden
 * @type api
 * @region  multi-room
 * @author shenpengliang
 * @brief  Get the current user persona.   <br>
 * @return  Current user persona. See ByteRTCUserRoleType{@link #ByteRTCUserRoleType} enumeration type. <br>
 */
- (ByteRTCUserRoleType)clientRole;

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
 *        + When the A/V synchronization state changes, you will receive rtcRoom:onAVSyncStateChange:{@link #RTCRoomDelegate#rtcRoom:onAVSyncStateChange:}.  <br>
 *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
 *        + If you want to change the audio source, call this API again with a new `audioUserId`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
 */
- (BOOL)setMultiDeviceAVSync:(NSString* _Nullable) audioUserId;

/** 
 *  @type api
 *  @region  room management
 *  @author shenpengliang
 *  @brief  Leave the room.   <br>
 *         The user calls this method to leave the room, end the call process, and release all call-related resources. <br>
 *  @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure <br>
 *  @notes   <br>
 *         + After the user leaves the room, the local will receive a callback for onLeaveRoomWithStats:{@link #RTCRoomDelegate#rtcRoom:onLeaveRoomWithStats:}; <br>
 *         + Call setUserVisibility:{@link #RTCRoom#setUserVisibility:} method sets itself to be visible. After the user leaves the room, other users in the room will receive rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} callback notification. <br>
 *         + After calling the joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} method to join the room, you must call this method to leave the room, otherwise you cannot enter the next room. This method can be called regardless of whether it is currently in the room. Repeated calls to this method have no negative impact. <br>
 */
- (int)leaveRoom;


/** 
 * @type api
 * @region Multiple rooms
 * @author shenpengliang
 * @brief Update Token. <br>
 *        When the user invokes the joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} method to join a room,
 *        If an expired token is used, you will fail to join room receive rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onRoomStateChanged:withUid:state:extraInfo:} callback,
 *         Callback error code is ByteRTCErrorCodeInvalidToken in ByteRTCErrorCode{@link #ByteRTCErrorCode}.
 *        At this point, you need to reacquire the token and call this method to update the token. After updating the Token, the SDK will be automatically added to the room. <br>
 * @param token  Updated dynamic key.
 * @return  Method call result.   <br>
 *          + 0: Success. <br>
 *          + < 0: failure. <br>
 * @notes Token  When expiring, if the room has been added successfully, it will not be affected. An expired Token error will notify the user the next time an expired Token is used to join the room, or when the network is disconnected and reconnected to the room due to poor local network conditions.
 */
- (int)renewToken:(NSString *_Nullable)token;
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
 *        + You should call this API in the room. If you want to call it before entering the room, you should set the `remoteVideoConfig` in the `roomConfig ` when calling joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:}.  <br>
 *        + You can call this API anytime before or after subscribing to the target stream. If you have already subscribed to the target stream when calling this API, your settings will take effect when you resubscribe to this stream.  <br>
 *        + SDK will automatically select the stream to be published or subcribed based on the settings of both sides.
 */
- (int) setRemoteVideoConfig:(NSString * _Nonnull) userId remoteVideoConfig:(ByteRTCRemoteVideoConfig *_Nonnull) remoteVideoConfig;

/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Publishes media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure
 * @notes  <br>
 *        + An invisible user cannot publish media streams. Call setUserVisibility:{@link #RTCRoom#setUserVisibility:} to change your visibility in the room.  <br>
 *        + Call publishScreen:{@link #RTCRoom#publishScreen:} to start screen sharing.  <br>
 *        + Call startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *        + After you call this API, the other users in the room will receive rtcRoom:onUserPublishStream:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishStream:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *        + Call unpublishStream:{@link #RTCRoom#unpublishStream:} to stop publishing streams.
 */
- (int)publishStream:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region Room Management
 * @author shenpengliang
 * @brief Stops publishing media streams captured by camera/microphone in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + -1: Failure
 * @notes  <br>
 *         + After calling publishStream:{@link #RTCRoom#publishStream:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:}.
 */
- (int)unpublishStream:(ByteRTCMediaStreamType)type;

/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Publishes local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to publish audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return  API call result:  <br>
 *        + 0: Success <br>
 *        + -1: Failure
 * @notes  <br>
 *         + An invisible user cannot publish media streams. Call setUserVisibility:{@link #RTCRoom#setUserVisibility:} to change your visibility in the room. <br>
 *         + After you called this API, the other users in the room will receive rtcRoom:onUserPublishScreen:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishScreen:type:}. Those who successfully received your streams will receive rtcEngine:onFirstRemoteAudioFrame:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteAudioFrame:}/rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:{@link #ByteRTCEngineDelegate#rtcEngine:onFirstRemoteVideoFrameDecoded:withFrameInfo:} at the same time.  <br>
 *         + Call startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:} to forward the published streams to the other rooms.  <br>
 *         + Call unpublishScreen:{@link #RTCRoom#unpublishScreen:} to stop publishing screen sharing streams.
 */
- (int)publishScreen:(ByteRTCMediaStreamType)type;
/** 
 * @type api
 * @region Screen Sharing
 * @author liyi.000
 * @brief Stops publishing local screen sharing streams in the current room.
 * @param type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See ByteRTCMediaStreamType{@link #ByteRTCMediaStreamType}.
 * @return API call result <br>
 *       + 0: Success <br>
 *       + -1: Failure
 * @notes  <br>
 *         + After calling publishScreen:{@link #RTCRoom#publishScreen:}, call this API to stop publishing streams. <br>
 *         + After calling this API, the other users in the room will receive rtcRoom:onUserUnPublishScreen:type:reason:{@link #RTCRoomDelegate#rtcRoom:onUserUnPublishScreen:type:reason:}.
 */
- (int)unpublishScreen:(ByteRTCMediaStreamType)type;

/** 
 * @hidden
 * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
 * @type api
 * @region Multi-room
 * @author shenpengliang
 * @brief Subscribe to media streams in the room.   <br>
 *        Call this API to subscribe to media streams in the room regardless of subscription mode, either Auto or Manual. <br>
 *        Call this API to update the properties and configurations of the stream you have already subscribed to. <br>
 * @param userId User ID of the publisher of the subscribed media stream <br>
 * @param streamType Mainstream or screen-sharing stream. Refer to  ByteRTCStreamIndex{@link #ByteRTCStreamIndex} for details. <br>
 * @param mediaType Media stream type to be subscribed to. Refer to ByteRTCSubscribeMediaType{@link #ByteRTCSubscribeMediaType} for details. <br>
 * @param videoConfig Subscription configuration of video streams. Refer to ByteRTCSubscribeVideoConfig{@link #ByteRTCSubscribeVideoConfig} for details. <br>
 * @notes  <br>
 *         + Get the media stream information in the room from  rtcRoom:onStreamAdd:{@link #RTCRoomDelegate#rtcRoom:onStreamAdd:} and rtcRoom:didStreamRemoved:stream:reason:{@link #RTCRoomDelegate#rtcRoom:didStreamRemoved:stream:reason:}. <br>
 *         + If the subscription fails, you will receive rtcEngine:onError:{@link #ByteRTCEngineDelegate#rtcEngine:onError:}. Refer to  ByteRTCErrorCode{@link #ByteRTCErrorCode} for the specific reason of the failure.
 *         + You can update the subscription configuration by calling the API even after calling pauseAllSubscribedStream:{@link #RTCRoom#pauseAllSubscribedStream:} to pause  streaming. Call  resumeAllSubscribedStream:{@link #RTCRoom#resumeAllSubscribedStream:} to resume streaming and apply the changes. <br>
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
 *        + You must first get the remote stream information through rtcRoom:onUserPublishStream:type:{@link #RTCRoomDelegate#rtcRoom:onUserPublishStream:type:} before calling this API to subscribe to streams accordingly.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
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
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
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
 *        + You must first get the remote stream information through rtcRoom:onUserPublishScreen:type:{@link #RTCRoomDelegate #rtcRoom:onUserPublishScreen:type:} before calling this API to subscribe to streams accordingly.  <br>
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
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
 *        + After calling this API, you will be informed of the calling result with rtcRoom:onStreamSubscribed:userId:subscribeConfig:{@link #RTCRoomDelegate#rtcRoom:onStreamSubscribed:userId:subscribeConfig:}.  <br>
 *        + Any other exceptions will be included in rtcRoom:onRoomStateChanged:withUid:state:extraInfo:{@link #RTCRoomDelegate#rtcRoom:onStreamStateChanged:withUid:state:extraInfo:}, see ByteRTCErrorCode{@link #ByteRTCErrorCode} for the reasons.
 */
- (void)unSubscribeScreen:(NSString *_Nonnull)userId mediaStreamType:(ByteRTCMediaStreamType)mediaStreamType;

/** 
 * @type api
 * @region Multi-room
 * @author shenpengliang
 * @brief Pause receiving remote media streams.
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @notes  <br>
 *         + Calling this API does not change the capture state and the transmission state of the remote clients. <br>
 *         + Calling this API does not cancel the subscription or change any subscription configuration. <br>
 *         + To resume, call resumeAllSubscribedStream:{@link #RTCRoom#resumeAllSubscribedStream:}.
 */
- (void)pauseAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;

/** 
 * @type api
 * @region Multi-room
 * @author shenpengliang
 * @brief Resume receiving remote media streams
 * @param mediaType Media stream type subscribed to. Refer to ByteRTCPauseResumControlMediaType{@link #ByteRTCPauseResumControlMediaType} for more details.
 * @notes  <br>
 *         + Calling this API does not change the capture state and the transmission state of the remote clients.
 *         + Calling this API does not change any subscription configuration.
 */
- (void)resumeAllSubscribedStream:(ByteRTCPauseResumControlMediaType) mediaType;
 /** 
  * @type api
  * @region Multi-room
  * @author hanchenchen.c
  * @brief Sends a text message (P2P) to the specified user in the room. The
  * @param userId   <br>
  *         Message receives the text message content sent by the user's ID
  * @param message   <br>
  *        . <br>
  *         Message does not exceed 62KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before sending an in-room text message, you must call joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onUserMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} callback to notify the sender of the success or failure of the message. <br>
  *       + If the text message is sent successfully, the user specified by uid will receive an rtcRoom:onUserMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onUserMessageReceived:message:} callback.
  */
- (int64_t)sendUserMessage:(NSString *_Nonnull)userId message:(NSString *_Nonnull)message;

 /** 
  * @type The api
  * @region multiroom
  * @author hanchenchen.c
  * @brief Sends a binary message (P2P) to the specified user in the room.
  * @param uid   <br>
  *        Message Receiving user's ID
  * @param message   <br>
  *        Binary message content sent <br>
  *        Message does not exceed 46KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before sending the in-room binary message, you must call joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onUserMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onUserMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the binary message is sent successfully, the user specified by uid will receive rtcRoom:onUserBinaryMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onUserBinaryMessageReceived:message:} callback.
  */
- (int64_t)sendUserBinaryMessage:(NSString * _Nonnull)uid message:(NSData * _Nonnull)message;

 /** 
  * @type api
  * @region Multi-room
  * @author hanchenchen.c
  * @brief Send text messages to all other users in the room.
  * @param message   <br>
  *        The content of the text message sent. <br>
  *         Message does not exceed 62KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before sending an in-room text message, you must call joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onRoomMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the text message is sent successfully, all remote users in the room will receive rtcRoom:onRoomMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageReceived:message:} callback.
  */
- (int64_t)sendRoomMessage:(NSString *_Nonnull)message;

 /** 
  * @type api
  * @region multiroom
  * @author hanchenchen.c
  * @brief Sends binary messages to all other users in the room.
  * @param message   <br>
  *        The binary broadcast message sent by the user <br>
  *        The message does not exceed 46KB.
  * @return The number of the message sent this time is incremented from 1.
  * @notes   <br>
  *       + Before broadcasting binary messages in the room, you must call joinRoomByToken:userInfo:roomConfig:{@link #RTCRoom#joinRoomByToken:userInfo:roomConfig:} to join the room. <br>
  *       + After calling this function, you will receive an rtcRoom:onRoomMessageSendResult:error:{@link #RTCRoomDelegate#rtcRoom:onRoomMessageSendResult:error:} callback to notify the sender of the success or failure of the message; <br>
  *       + If the binary message is successfully sent, all users in the room will receive rtcRoom:onRoomBinaryMessageReceived:message:{@link #RTCRoomDelegate#rtcRoom:onRoomBinaryMessageReceived:message:} callback.
  */
- (int64_t)sendRoomBinaryMessage:(NSData *  _Nonnull)message;

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
     *        + Call updateForwardStreamToRooms:{@link #RTCRoom#updateForwardStreamToRooms:} to add or remove the designated room(s) after calling this method.
     *        + Call stopForwardStreamToRooms{@link #RTCRoom#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.
     *        + Call pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
- (int)startForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Update information of the rooms where you want to relay the media stream to after calling startForwardStreamToRooms:{@link #RTCRoom#startForwardStreamToRooms:}. <br>
     *        Adding and removing rooms by calling this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:} on the local.
     * @param configurations Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  <br>
     *          0: Success
     *          <0: Failure  <br>
     * @notes <br>
     *        + Users in the room which is added by calling this method will receive rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:}.
     *        + Users in the room which is removed by calling this method will receive rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} and rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:}.
     */
- (int)updateForwardStreamToRooms:(NSArray <ForwardStreamConfiguration *> * _Nullable)configurations;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call to this method to stop relaying media stream to all rooms after calling startForwardStreamToRooms{@link #RTCRoom#startForwardStreamToRooms:}. <br>
     * @notes <br>
     *        + Call this method will trigger rtcRoom:onForwardStreamStateChanged:{@link #RTCRoomDelegate#rtcRoom:onForwardStreamStateChanged:}.
     *        + The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you stop relaying.
     *        + To stop relaying media stream to specific rooms, call updateForwardStreamToRooms:{@link #RTCRoom#updateForwardStreamToRooms:} instead.
     *        + To resume the relaying in a short time, call pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms} instead and then call resumeForwardStreamToAllRooms{@link #RTCRoom#resumeForwardStreamToAllRooms} to recsume after that.
     */
- (void)stopForwardStreamToRooms;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call this method to pause relaying media stream to all rooms after calling startForwardStreamToRooms{@link #RTCRoom#startForwardStreamToRooms:}. <br>
     *        After that, call resumeForwardStreamToAllRooms{@link #RTCRoom#resumeForwardStreamToAllRooms} to resume.
     * @notes The other users in the room will receive callback of rtcRoom:onUserUnPublishStream:type:reason: {@link #RTCRoomDelegate#rtcRoom:onUserUnPublishStream:type:reason:} and rtcRoom:onUserLeave:reason:{@link #RTCRoomDelegate#rtcRoom:onUserLeave:reason:} when you pause relaying.
     */
- (void)pauseForwardStreamToAllRooms;
    /** 
     * @type api
     * @region Multi-room
     * @author wunailiang
     * @brief Call this method to resume relaying to all rooms from the pause by calling pauseForwardStreamToAllRooms{@link #RTCRoom#pauseForwardStreamToAllRooms}.
     * @notes The other users in the room will receive callback of rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} and rtcRoom:onUserJoined:elapsed:{@link #RTCRoomDelegate#rtcRoom:onUserJoined:elapsed:} when you resume relaying.
     */
- (void)resumeForwardStreamToAllRooms;


/** 
 * @type api
 * @region Range Audio
 * @author chuzhongtao
 * @brief Gets range audio instance.
 * @return API call result:  <br>
 *        + ByteRTCRangeAudio: Success. You will get an ByteRTCRangeAudio{@link #ByteRTCRangeAudio} returned from the SDK.  <br>
 *        + NULL: Failure. The current SDK does not offer range audio function.
 * @notes The first time this API is called must be between you create a room and you actually enter the room.
 */
- (ByteRTCRangeAudio *_Nullable)getRangeAudio;

/** 
 * @type api
 * @region Spatial Audio
 * @author majun.lvhiei
 * @brief Gets spatial audio instance.   <br>
 * @return API call result:  <br>
 *        + ISpatialAudio: Success. You will get an ByteRTCSpatialAudio{@link #ByteRTCSpatialAudio} returned from the SDK.  <br>
 *        + NULL: Failure. The current SDK does not offer spatial audio function.
 * @notes   <br>
 *        + The first time this API is called must be between you create a room and you actually enter the room.  <br>
 *        + Only using real dual-channel playback device can you actually enjoy spatial audio effect.  <br>
 *        + Low-end device may have audio stalling issues due to its poor performance, so it is not recommended to enable spatial audio function on such kind of devices. <br>
 *        + SDK currently supports up to 30 users publishing audio with spatial audio enabled at the same time in the same room.
 */
- (ByteRTCSpatialAudio *_Nullable)getSpatialAudio;

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
@end
