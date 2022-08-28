/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room Event Handler Interface
*/

#pragma once

#ifndef BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
#define BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__

#include "bytertc_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief  Audio & video room event callback interface
 */
class IRTCRoomEventHandler {
public:

    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCRoomEventHandler() {
    }

     /** 
     * @type callback
     * @region Multi-room
     * @brief Callback on room state changes. You will receive this callback when you join the room, leave the room, or receive room relating warnings and errors.
     * @param [in] room_id  Room ID.
     * @param [in] uid  User ID.
     * @param [in] state Room state code. <br>
     *              + 0: Success. <br>
     *              + !0: Failure. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param [in] extra_info Extra information.
     *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rehoins the room. <br>
     *                 `elapsed` indicates the time interval from calling joinRoom{@link #IRTCRoom#joinRoom}} to successfully joining room, in ms.
     */
    virtual void onRoomStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }
    
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on stream state changes. You will receive this callback when you receive stream relating warnings and errors.
     * @param [in] room_id  Room ID.
     * @param [in] uid  User ID.
     * @param [in] state Room state code. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param [in] extra_info Extra information. Currently unavailable.
     */
    virtual void onStreamStateChanged(
            const char* room_id, const char* uid, int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** 
      * @type callback
      * @region Room management
      * @brief After leaving the room successfully, receives the callback.   <br>
      *        When the user calls the leaveRoom{@link #IRTCRoom#leaveRoom}, the SDK will stop all publishing subscription streams and release all call-related media resources. After that, the user receives this callback . <br>
      * @param [in] stats Statistics for this call. See RtcRoomStats{@link #RtcRoomStats}. <br>
      * @notes   <br>
      *        + If calling leaveRoom{@link #IRTCRoom#leaveRoom} and then destroyRtcEngine{@link #destroyRtcEngine} immediately after, the user will not receive this callback. <br>
      *        + If the app needs to use the media resources of the device for purposes other than RTC, you should init the resources after receiving this callback. Receiving this callback ensures that the resources are not occupied by RTC SDK.
      */
    virtual void onLeaveRoom(const RtcRoomStats& stats) {
        (void)stats;
    }

    /** 
     * @hidden
     * @deprecated since 341.1 by OnRoomStateChanged and OnStreamStateChanged
     * @type callback
     * @region Room Management
     * @brief SDK Warning callback occurred. When a recoverable error is encountered inside the <br>
     *        SDK, the user is notified via this callback while attempting automatic recovery. This callback event is only used as a notification. <br>
     * @param  [in] warn Code. See WarningCode{@link #WarningCode}. <br>
     */
    virtual void onRoomWarning(int warn) {
        (void)warn;
    }

    /** 
     * @hidden
     * @deprecated since 341.1 by OnRoomStateChanged and OnStreamStateChanged
     * @type callback
     * @region Room management
     * @brief SDK Error callback occurred. <br>
     *        SDK internal encountered an unrecoverable error, will notify the App through this callback, requires the App to operate according to the error code or prompt the user. <br>
     * @param  [in] err Error code. See ErrorCode{@link #ErrorCode}. <br>
     */
    virtual void onRoomError(int err) {
        (void)err;
    }
    /** 
     * @type callback
     * @brief You will be informed 30 sec before the expiration via this callback.
     *        Call updateToken{@link #IRTCRoom#updateToken} to renew the Token. If the Token expired, the user would be removed from the room and not be able to continue the call.
     */
    virtual void onTokenWillExpire() {

    }

    /** 
     * @type callback
     * @region  data statistics
     * @brief  In-room call statistics callback.    <br>
     *        After the user enters the room and starts the call, he receives this callback every 2s.
     * @param  [in] stats Current RtcEngine statistics. See RtcRoomStats{@link #RtcRoomStats}
     */
    virtual void onRoomStats(const RtcRoomStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region Statistics
     * @brief After the published stream is successful, you receive this callback every 2s to understand the network quality information of the published stream during this cycle.
     * @param  [in] stats Current RtcEngine statistics. See LocalStreamStats{@link #LocalStreamStats}
     */
    virtual void onLocalStreamStats(const LocalStreamStats& stats) {
        (void)stats;
    }
    /** 
     * @type callback
     * @region Statistics
     * @brief Receive this callback every 2s to learn the network quality information of the stream published by the subscribed remote user during this cycle.
     * @param  [in] stats Current RtcEngine statistics. See RemoteStreamStats{@link #RemoteStreamStats}
     */
    virtual void onRemoteStreamStats(const RemoteStreamStats& stats) {
        (void)stats;
    }

    /** 
      * @type callback
      * @region Room management
      * @brief You will receive this callback in following cases: <br>
      *        + The remote user calls setUserVisibility{@link #IRTCRoom#setUserVisibility} turns visible and joins your room. <br>
      *        + The remote visible user is disconnected and then reconnected to your room. <br>
      *        + The invisible remote user in your room calls setUserVisibility{@link #IRTCRoom#setUserVisibility} and turns visible. <br>
      *        + You join the room when there are visible users in the room.
      * @param [in] user_info See UserInfo{@link #UserInfo}. <br>
      * @param [in] elapsed Reserved parameter.
      */
    virtual void onUserJoined(const UserInfo& user_info, int elapsed) {
        (void)user_info;
        (void)elapsed;
    }

    /** 
     * @type callback
     * @brief This callback is triggered when a remote user is disconnected or turns invisible.
     * @param uid ID of the user who leaves the room, or switches to invisible. <br>
     * @param reason Reason to leave the room: <br>
     *               + 0: The remote client calls leaveRoom{@link #IRTCRoom#leaveRoom} to leave the room. <br>
     *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
     *               + 2: The remote client calls setUserVisibility{@link #IRTCRoom#setUserVisibility} to turn invisible. <br>
     *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }

    /** 
     * @hidden
     * @type callback
     * @region Media Stream Management
     * @brief When a user in the room calls muteAllRemoteAudio{@link #IRTCRoom#muteAllRemoteAudio},
     *        Changing the state of receiving all remote audio streams, other users in the room receive this callback.
     * @param  [in] user_id Change the user ID of the receiving state
     * @param  [in] mute_state The receiving state, see: MuteState{@link #MuteState}
     */
    virtual void onMuteAllRemoteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /** 
     * @hidden
     * @type callback
     * @region Media Stream Management
     * @brief When the user in the room pauses/resumes receiving all video streams, other users in the room receive this callback. See muteAllRemoteVideo{@link #muteAllRemoteVideo}.
     * @param  [in] uid Pause/resume the user ID of the received video stream.
     * @param   [in] mute Pauses/resumes the state of the received video stream. See MuteState{@link #MuteState}.
     */
    virtual void onMuteAllRemoteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }

    /** 
     * @hidden
     * @deprecated since 336.1, use onUserUnpublishStream and onUserUnpublishScreen instead.
     * @type callback
     * @region Room Management
     * @brief Local users will receive this callback when a remote user in the room stops publishing audio & video streams. Properties of the
     * @param  [in] stream Stream. See MediaStreamInfo{@link #MediaStreamInfo}.
     * @param  [in] reason The reason for the removal of the remote stream. See StreamRemoveReason{@link #StreamRemoveReason}.
     */
    virtual void onStreamRemove(const MediaStreamInfo& stream, StreamRemoveReason reason) {
        (void)stream;
    }


    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream and onUserPublishScreen instead.
     * @type callback
     * @region Room Management
     * @brief When users in the room post a new audio & video stream, other users in the room will receive this callback. Includes streams that are removed and republished.   <br>
     * @param  [in] stream Stream properties. See MediaStreamInfo{@link #MediaStreamInfo}. <br>
     */
    virtual void onStreamAdd(const MediaStreamInfo& stream) {
        (void)stream;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on new media streams captured by camera/microphone in the room.
     * @param [in] uid The ID of the remote user who published the stream.
     * @param [in] type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @notes You will receive this callback after a remote user successfully published media streams captured by camera/microphone in the room with publishStream{@link #IRTCRoom#publishStream}. Then you can choose whether to call subscribeStream{@link #IRTCRoom#subscribeStream} to subscribe to the streams or not.
     */
    virtual void onUserPublishStream(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on removal of remote media stream captured by camera/microphone.
     * @param [in] uid The ID of the remote user who removed the stream.
     * @param [in] type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @param [in] reason The reason for the removal, see StreamRemoveReason{@link #StreamRemoveReason}.
     * @notes After receiving this callback, you can choose whether to call unsubscribeStream{@link #IRTCRoom#unsubscribeStream} to unsubscribe from the streams or not.
     */
    virtual void onUserUnpublishStream(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on new screen sharing media streams from remote users in the room.
     * @param [in] uid The ID of the remote user who published the stream.
     * @param [in] type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @notes You will receive this callback after a remote user successfully published screen sharing streams in the room with publishScreen{@link #IRTCRoom#publishScreen}. Then you can choose whether to call subscribeScreen{@link #IRTCRoom#subscribeScreen} to subscribe to the streams or not.
     */
    virtual void onUserPublishScreen(const char* uid, MediaStreamType type) {
        (void)uid;
        (void)type;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on removal of screen sharing media streams from remote users in the room.
     * @param [in] uid The ID of the remote user who removed the stream.
     * @param [in] type Media stream type. See MediaStreamType{@link #MediaStreamType}.
     * @param [in] reason The reason for the removal, see StreamRemoveReason{@link #StreamRemoveReason}.
     * @notes After receiving this callback, you can choose whether to call unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} to unsubscribe from the streams or not.
     */
    virtual void onUserUnpublishScreen(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
        (void)uid;
        (void)type;
        (void)reason;
    }

    /** 
     * @type callback
     * @region Room management
     * @brief Callback on subscription status of media streams
     * @param [in] state_code Subscription status of media streams, see SubscribeState{@link #SubscribeState}.
     * @param [in] user_id The ID of the user who published the stream.
     * @param [in] info Configurations of stream subscription, see SubscribeConfig{@link #SubscribeConfig}.
     * @notes  <br>
     *        Local users will receive this callback:  <br>
     *        + After calling subscribeStream{@link #IRTCRoom#subscribeStream}}/unsubscribeStream{@link #IRTCRoom#unsubscribeStream}} to change the subscription status of remote media streams captured by camera/microphone.  <br>
     *        + After calling subscribeScreen{@link #IRTCRoom#subscribeScreen}/unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} to change the subscription status of remote screen sharing streams.
     */
    virtual void onStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /** 
     * @hidden
     * @type callback
     * @region Room management
     * @brief Callback the event when the release flow is successful.
     * @param  [in] user_id The user ID of the published stream.
     * @param  [in] is_screen Whether the stream is a screen stream. <br>
     *              + Ture: Screen stream; <br>
     *              + False: Non-screen stream. <br>
     */
    virtual void onStreamPublishSuccess(const char* user_id, bool is_screen) {
        (void)is_screen;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback for broadcast messages in the room.
     * @param  [in] uid <br>
     *         Message sender ID
     * @param  [in] message <br>
     *         Received message content
     * @notes Other users in the same room will receive this callback when they call sendRoomMessage{@link #IRTCRoom#sendRoomMessage} to send a broadcast message.
     */
    virtual void onRoomMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback to a binary broadcast message in the room.
     * @param  [in] uid <br>
     *         Message sender ID
     * @param  [in] size <br>
     *         Binary message length received
     * @param  [in] message <br>
     *        Binary message content received
     * @notes Other users in the same room call sendRoomBinaryMessage{@link #IRTCRoom#sendRoomBinaryMessage} Receive this callback when sending a binary broadcast message.
     */
    virtual void onRoomBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message (P2P) from another user in the room.
     * @param  [in] uid <br>
     *         Message sender ID.
     * @param  [in] message <br>
     *         The content of the received text message.
     * @notes   <br>
     *         + You must call the sendUserMessage{@link #IRTCRoom#sendUserMessage} method before you can receive the callback.
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region Real-time Message Communication
     * @brief A single user receives a callback (P2P) of binary messages from other uid-owned users in the same room.
     * @param  [in] uid <br>
     *         Message sender ID.
     * @param  [in] message <br>
     *         The content of the received binary message.
     * @notes   <br>
     *         + When other users in the same room call sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} to send binary messages to local users, local users will receive the callback.
     */
    virtual void onUserBinaryMessageReceived(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief After sending a text or binary message (P2P) to a single user in the room, the message sender receives a callback with the result of the message.
     * @param  [in] msgid <br>
     *             The ID of this message.
     * @param  [in] error <br>
     *             Text or binary message sending results. See UserMessageSendResult{@link #UserMessageSendResult}
     * @notes   <br>
     *         + You must first call the sendUserMessage{@link #IRTCRoom#sendUserMessage} or sendUserBinaryMessage{@link #IRTCRoom#sendUserBinaryMessage} interface to receive this callback.
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief When the sendRoomMessage{@link #IRTCRoom#sendRoomMessage} function is called to send a message, the sending result of this message (feedback) is called back.
     * @param  [in] msgid <br>
     *         ID of this message
     * @param  [in] error <br>
     *         Message sending result <br>
     *         See RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void onRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /*
     * @hidden
     * @deprecated
     */
    virtual void onRoomModeChanged(RtcRoomMode mode) {
        (void)mode;
    }

#ifndef ByteRTC_AUDIO_ONLY
    /** 
     * @hidden
     * @type callback
     * @region Video management
     * @brief This callback is triggered when subscribing to the remote user
     * @param  [in] user_id The ID of the remote user
     * @param  [in] is_reconnect Whether it is a reconnection
     */
    virtual void onSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /** 
     * @hidden
     * @type callback
     * @region Video management
     * @brief This callback is triggered when the remote user is unsubscribed
     * @param  [in] user_id The ID of the remote user
     * @param  [in] is_reconnect Whether it is a reconnection
     */
    virtual void onUnSubscribe(const char* user_id, bool is_reconnect) {
        (void)user_id;
        (void)is_reconnect;
    }

    /*
     * @hidden
     * @brief callback when the maximum screen share fps is changed
     * @param [in] fps
     *           maximum screen share fps
     */
    virtual void onMaximumScreenShareFpsUpdated(int fps) {
        (void)fps;
    }

    /** 
     * @hidden
     * @brief Callback when the maximum screen shared pixels (resolution) is chang
     * @param  [in] screenPixels
     *        The recommended maximum video width × height value to maintain the frame rate
     *
     */
    virtual void onMaximumScreenSharePixelsUpdated(int screenPixels) {
        (void)screenPixels;
    }

    /** 
     * @hidden
     * @type callback
     * @region video management
     * @brief Spliced view user requests avatar callback
     * @param  [in] uid User ID
     */
    virtual void onNeedAvatar(const char* uid) {
        (void)uid;
    }

    /** 
     * @type callback
     * @region Video management
     * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is invoked to disable/unban the sending of a specified user's video stream in a specified room.
     * @param  [in] uid User ID of the video stream that was disabled/unbanned
     * @param  [in] banned Video stream sending status <br>
     *         + True: Video stream sending was disabled <br>
     *         + False: Video stream sending was unbanned
     * @notes   <br>
     *         + When the specified user in the room is disabled/unbanned Video stream sending, all users in the room will receive the callback .. <br>
     *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
     *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
     *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
     *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback. <br>
     *         + The same room is created again after dissolution, and the state in the room is empty.
     */
    virtual void onVideoStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region Multi-Room
     * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} is called.
     * @param state A/V synchronization state, see AVSyncState{@link #AVSyncState}.
     */
    virtual void onAVSyncStateChange(AVSyncState state) {
        (void)state;
    }

#endif  // ByteRTC_AUDIO_ONLY
    /** 
     * @type callback
     * @region Audio event callback
     * @brief This callback is triggered when the server level MuteUser/UnmuteUser method is called to disable/unban the sending of the specified user's audio and video stream in a specified room.
     * @param  [in] uid Disabled/unbanned audio stream user ID
     * @param  [in] banned Audio stream sending status <br>
     *         + True: audio stream sending is disabled <br>
     *         + False: audio stream sending is unbanned
     * @notes   <br>
     *         + Specified users in the room are prohibited/all users in the room when audio stream sending is unbanned Will receive the callback. <br>
     *         + If the banned user checks out and then enters the room, it will still be banned status, and everyone in the room will receive the callback again. <br>
     *         + If the banned user is disconnected and reconnected to the room, it will still be banned status, and only the person will receive the callback again. <br>
     *         + After the specified user is banned, other users in the room will check out and enter the room again, and will receive the callback again. <br>
     *         + When the number of calls exceeds 5, only blocked/unblocked users will receive the callback. <br>
     *         + The same room is created again after dissolution, and the state in the room is empty.
     */
    virtual void onAudioStreamBanned(const char* uid, bool banned) {
        (void)uid;
        (void)banned;
    }

    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the state and errors during relaying the media stream to each of the rooms
     * @param infos Array of the state and errors of each target room. Refer to ForwardStreamStateInfo{@link #ForwardStreamStateInfo} for more inforamtion.
     * @param info_count The number of the target rooms
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
    }

    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the media stream to each room
     * @param infos Array of the event of each target room. Refer to ForwardStreamEventInfo{@link #ForwardStreamEventInfo} for more information.
     * @param info_count The number of the target rooms
     */
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
    }

    /** 
     * @hidden(Linux)
     * @type callback
     * @brief Report the network quality of the users every 2s after the local user joins the room.
     * @param [in] localQuality Local network quality. Refer to NetworkQualityStats{@link #NetworkQualityStats} for details.
     * @param [in] remoteQualities Network quality of the subscribed users. Refer to NetworkQualityStats{@link #NetworkQualityStats} for details.
     * @param [in] remoteQualityNum Array length of `remoteQualities`
     */
    virtual void onNetworkQuality(const NetworkQualityStats& localQuality, const NetworkQualityStats* remoteQualities, int remoteQualityNum) {
    }
};

} // namespace bytertc

#endif // BYTE_RTC_ROOM_EVENT_HANDLER_INTERFACE_H__
