/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room Event Handler Interface
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief  Audio & video room event callback interface
 */
class IRTCAudioRoomEventHandler {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCAudioRoomEventHandler() {}

    /** 
     * @type callback
     * @region Room management
     * @brief Callback on room state changes. You will receive this callback when you join the room, leave the room, or receive room relating warnings and errors.
     * @param [in] room_id  Room ID.
     * @param [in] uid  User ID.
     * @param [in] state Room state code. <br>
     *              + 0: Success. <br>
     *              + !0: Failure. See ErrorCode{@link #ErrorCode} and WarningCode{@link #WarningCode} for specific indications.
     * @param [in] extra_info Extra information.
     *                 `join_type` indicates the type of room the user joins. `0` means the user joins the room for the first time, and `1` means the user rehoins the room. <br>
     *                 `elapsed` indicates the time interval from calling JoinRoom{@link #IRTCAudioRoom#JoinRoom} to successfully joining room, in ms.
     */
    virtual void onRoomStateChanged(const char* room_id, const char* uid,
            int state, const char* extra_info) {
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
    virtual void onStreamStateChanged(const char* room_id, const char* uid,
            int state, const char* extra_info) {
        (void)room_id;
        (void)state;
        (void)extra_info;
    }

    /** 
     * @type callback
     * @region Room management
     * @brief Leave the room callback.   <br>
     *        After the user calls the leaveRoom{@link #IRTCAudioRoom#leaveRoom} method, the SDK stops all publishing subscription streams and notifies the user to leave the room successfully through this callback after releasing all audio & video resources related to the call. <br>
     * @param  [in] stats For statistics on this call. See RtcRoomStats{@link #RtcRoomStats}. <br>
     * @notes   <br>
     *        + After the user calls the leaveRoom{@link #IRTCAudioRoom#leaveRoom} method to leave the room, if the DestroyRTCAudio{@link #DestroyRTCAudio} method is called to destroy the RTC engine immediately, this callback event will not be received. <br>
     *        + After leaving the room, if the App needs to use the system audio & video device, it is recommended to receive this callback before initializing the audio & video device, otherwise the initialization may fail due to the SDK occupying the audio & video device. <br>
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
     *        Call updateToken{@link #IRTCAudioRoom#updateToken} to renew the Token. If the Token expired, the user would be removed from the room and not be able to continue the call.
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
     * @brief Remote visible users join the room, or invisible users in the room switch to visible callbacks. <br>
     *        1. When a remote user calls the setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} method to make itself visible and then join the room, other users in the room will receive the event. <br>
     *        2. When the remote visible user is disconnected and reconnected to the room, other users in the room will receive the event. <br>
     *        3. Invisible in the room When a remote user calls the setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} method to switch to visible, other users in the room will receive the event. <br>
     *        4. New users entering the room will receive a callback notification from visible users who were already in the room before entering the room. <br>
     * @param  [in] user_info User information. See UserInfo{@link #UserInfo} <br>
     * @param  [in] elapsed This parameter is meaningless
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
     *               + 0: The remote client calls leaveRoom{@link #IRTCAudioRoom#leaveRoom} to leave the room. <br>
     *               + 1: The remote client is disconnected because of poor network connection or expired Token. <br>
     *               + 2: The remote client calls setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} to turn invisible.<br> 
     *               + 3: The remote user has been removed from the room by the administrator via a OpenAPI call.
     */
    virtual void onUserLeave(const char* uid, UserOfflineReason reason) {
        (void)uid;
        (void)reason;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on new audio stream added in the room.
     * @param [in] uid The ID of the remote user who published the stream.
     * @notes You will receive this callback after a remote user successfully published audio streams in the room with publishStream{@link #IRTCAudioRoom#publishStream}. Then you can choose whether to call SubscribeStream{@link #IRTCAudioRoom#SubscribeStream} to subscribe to the stream or not.
     */
    virtual void onUserPublishStream(const char* uid) {
        (void)uid;
    }
    /** 
     * @type callback
     * @region Room management
     * @brief Callback on removal of remote audio stream.
     * @param [in] uid The ID of the remote user who removed the stream.
     * @param [in] reason The reason for the removal, see StreamRemoveReason{@link #StreamRemoveReason}.
     * @notes After receiving this callback, you can choose whether to call unsubscribeStream{@link #IRTCAudioRoom#unsubscribeStream} to unsubscribe from the streams or not.
     */
    virtual void onUserUnPublishStream(const char* uid, StreamRemoveReason reason) {
        (void)uid;
        (void)reason;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receives a callback for broadcast messages in the room.
     * @param  [in] uid <br>
     *         Message sender ID
     * @param  [in] message <br>
     *         Received message content
     * @notes Other users in the same room will receive this callback when they call sendRoomMessage{@link #IRTCAudioRoom#sendRoomMessage} to send a broadcast message.
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
     * @notes Other users in the same room call sendRoomBinaryMessage{@link #IRTCAudioRoom#sendRoomBinaryMessage} Receive this callback when sending a binary broadcast message.
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
     *         + You must call the sendUserMessage{@link #IRTCAudioRoom#sendUserMessage} method before you can receive the callback.
     */
    virtual void onUserMessageReceived(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }

    /** 
     * @type callback
     * @region Real-time Message Communication
     * @brief A single user receives a callback (P2P) of binary messages from other uid-owned users in the same room.
     * @param [in] uid <br>
     *         Message sender ID.
     * @param [in] message <br>
     *         The content of the received binary message.
     * @notes   <br>
     *         + When other users in the same room call sendUserBinaryMessage{@link #IRTCAudioRoom#sendUserBinaryMessage} to send binary messages to local users, local users will receive the callback.
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
     * @param [in] msgid <br>
     *             The ID of this message.
     * @param [in] error <br>
     *             Text or binary message sending results. See UserMessageSendResult{@link #UserMessageSendResult}
     * @notes   <br>
     *         + You must first call the sendUserMessage{@link #IRTCAudioRoom#sendUserMessage} or sendUserBinaryMessage{@link #IRTCAudioRoom#sendUserBinaryMessage} interface to receive this callback.
     */
    virtual void onUserMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief When the sendRoomMessage{@link #IRTCAudioRoom#sendRoomMessage} function is called to send a message, the sending result of this message (feedback) is called back.
     * @param [in] msgid <br>
     *         ID of this message
     * @param [in] error <br>
     *         Message sending result <br>
     *         See RoomMessageSendResult{@link #RoomMessageSendResult}
     */
    virtual void onRoomMessageSendResult(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

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
     * @brief Callback returning the state and errors during relaying the audio stream to each of the rooms
     * @param [in] infos Array of the state and errors of each target room. Refer to ForwardStreamStateInfo{@link #ForwardStreamStateInfo} for more inforamtion.
     * @param [in] info_count The number of the target rooms
     */
    virtual void onForwardStreamStateChanged(ForwardStreamStateInfo* infos, int info_count) {
        (void)infos;
        (void)info_count;
    }

    /** 
     * @type callback
     * @region Multi-room
     * @brief Callback returning the events during relaying the audio stream to each room
     * @param [in] infos Array of the event of each target room. Refer to ForwardStreamEventInfo{@link #ForwardStreamEventInfo} for more information.
     * @param [in] info_count The number of the target rooms
     */
    virtual void onForwardStreamEvent(ForwardStreamEventInfo* infos, int info_count) {
        (void)infos;
        (void)info_count;
    }
};

}  // namespace bytertc

