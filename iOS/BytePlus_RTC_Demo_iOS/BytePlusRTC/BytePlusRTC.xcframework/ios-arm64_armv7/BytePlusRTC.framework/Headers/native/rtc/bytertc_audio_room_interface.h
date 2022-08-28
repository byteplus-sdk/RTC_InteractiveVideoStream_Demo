/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room Interface
 */

#pragma once

#include "bytertc_audio_defines.h"
#include "bytertc_audio_room_event_handler.h"
#include "bytertc_range_audio_interface.h"
#include "bytertc_spatial_audio_interface.h"

namespace bytertc {

/** 
 * @type api
 * @brief  Room interface
 */
class IRTCAudioRoom {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCAudioRoom() {
    }

    /** 
     * @type api
     * @region  multi-room
     * @brief  Destroy the room, the interface implementation will first perform the check-out operation, and then release the room processing callback pointer
     */
    virtual void destroy() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Create/join a room: create a room when the room does not exist; when the room exists, users who have not joined the room can join the room.   <br>
     *        Users in the same room can talk to each other. <br>
     *         Repeated calls after entering the room are invalid. The user must call `leaveRoom` to exit the current room before joining the next room. <br>
     * @param  [in] token Dynamic key for authenticating the logged-in user. <br>
     *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. <br>
     *        + Apps with different App IDs cannot communicate with each other. <br>
     *        + Make sure that the App ID used to generate the Token is the same as the App ID used to create the engine, otherwise it will cause the join room to fail. <br>
     * @param  [in] user_info User information. See UserInfo{@link #UserInfo}. <br>
     * @param  [in] room_config Room parameter configuration, set the room mode and whether to automatically publish or subscribe to the flow. See AudioRoomConfig{@link #AudioRoomConfig} for the specific configuration mode. <br>
     * @return   <br>
     *         + 0: Success <br>
     *         + -1: Room_id/user_info.uid contains invalid parameters. <br>
     *         + -2: Already in the room. After the interface call is successful, as long as the return value of 0 is received and `leaveRoom` is not called successfully, this return value is triggered when the room entry interface is called again, regardless of whether the filled room ID and user ID are duplicated. <br>
     * @notes   <br>
     *        + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who entered the room later will kick the user who entered the room out of the room, and the user who entered the room will receive the OnError{@link #IRTCAudioEventHandler#OnError} callback notification. For the error type. See kErrorCodeDuplicateLogin in ErrorCode{@link #ErrorCode}. <br>
     *        + Local users will receive onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} callback notification after calling this method to join the room successfully. <br>
     *        + Local users call setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} to make themselves visible and then join the room, and remote users will receive onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined}. <br>
     *        + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After a successful reconnection, you will receive a local onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged} callback notification. <br>
     */
    virtual int joinRoom(const char* token, const UserInfo& user_info, const AudioRoomConfig& room_config) = 0;

    /** 
     * @type api
     * @region Multiple rooms
     * @brief Leave the room.   <br>
     *        The user calls this method to leave the room, end the call process, and release all call-related resources. <br>
     *         After joining the room, you must call this method to end the call, otherwise you cannot start the next call. This method can be called regardless of whether it is currently in the room. Repeated calls to this method have no negative impact. <br>
     * @notes   <br>
     *        + This method is an asynchronous operation and does not really exit the room when the call returns. After you actually exit the room, you will receive a callback notification from onLeaveRoom{@link #IRTCAudioRoomEventHandler#onLeaveRoom} locally. <br>
     *        + After the visible user leaves the room, other users in the room will receive an onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} callback notification. <br>
     *        + If the engine is destroyed immediately after this method is called, the SDK will not be able to trigger the onLeaveRoom{@link #IRTCAudioRoomEventHandler#onLeaveRoom} callback. <br>
     *        + After calling the joinRoom{@link #IRTCAudioRoom#joinRoom} method to join the room, you must call this method to leave the room, otherwise you cannot enter the next room. This method can be called regardless of whether it is currently in the room. Repeated calls to this method have no negative impact. <br>
     */
    virtual void leaveRoom() = 0;

    /** 
     * @type api
     * @brief Update Token. <br>
     *        A Token used to join rooms has an expiration time. You will be informed 30 sec before the expiration of the token by OnTokenWillExpire{@link #RTCEngine#onTokenWillExpire}. Call this API to renew the Token. Or the user will be removed from the room as the Token expires. <br>
     *         If you called joinRoom{@link #IRTCAudioRoom#joinRoom} to join a room or reconnected into a room with an invalid Token, it would fail. You would get informed by onRoomStateChanged{@link #IRTCAudioRoomEventHandler#onRoomStateChanged}. The error code is the `ERROR_CODE_INVALID_TOKEN` in ErrorCode{@link #ErrorCode}. Reacquire a token and call this API to renew the token. <br>
     * @param token  Valid token.  <br>
     *        If the Token is invalid, SDK will emit `ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN` defined in an ErrorCode{@link #ErrorCode}.
     * @return  <br>
     *          + 0: Success. <br>
     *          + < 0: Failure <br>
     * @notes  When the Token expired, the user would be removed from the room. And you would get informed of  `ERROR_CODE_EXPIRED_TOKEN` by OnError{@link #IRTCAudioRoomEventHandler#onError}. Reacquire a token and call joinRoom{@link #IRTCAudioRoom#joinRoom} with the token to rejoin the room.
     */
    virtual void updateToken(const char* token) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Set user visibility. The default is visible.   <br>
     *        By setting user visibility, you can control the user's behavior in the room: <br>
     *         + Whether audio & video streams can be published; <br>
     *         + Whether the user himself is invisible in the room.
     * @param  [in] enable Sets whether the user is visible to other users in the room: <br>
     *         + True: can be perceived by other users in the room, and can publish and subscribe to audio & video streams in the room; <br>
     *         + False: cannot be perceived by other users in the room, and can only subscribe to audio & video streams in the room.
     * @notes   <br>
     *         + This method can be called before and after joining the room. <br>
     *         + When this method is called in the room, other users in the room will receive corresponding callback notifications: <br>
     *            -When Switching from false to true, other users in the room will receive onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} callback notifications; <br>
     *            -When Switching from true to false, other users in the room will receive onUserLeave {@ Link #IRTCRoomEventHandler #onUserLeave} callback notification. <br>
     *         + If you call this method to set the visibility to false, the attempt to publish the stream will receive an OnWarning{@link #IRTCAudioEventHandler#OnWarning} warning. See the kWarningCodePublishStreamForbiden warning code in WarningCode{@link #WarningCode} for specific reasons.
     */
    virtual void setUserVisibility(bool enable) = 0;

    /** 
     * @type api
     * @region multiroom
     * @brief Set the event handle of the IRTCAudioRoom{@link #IRTCAudioRoom} object.
     *         You can listen for callback events for the room corresponding to this IRTCAudioRoom{@link #IRTCAudioRoom} object by setting the event handle.
     * @param  [in] room_event_handler Callback processor. See IRTCAudioRoomEventHandler{@link #IRTCAudioRoomEventHandler}.
     */
    virtual void setRTCRoomEventHandler(IRTCAudioRoomEventHandler* room_event_handler) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Send a text message (P2P) to the specified user in the room
     * @param  [in] user_id <br>
     *        Message Receives the user's ID
     * @param  [in] message <br>
     *        Text message content sent. <br>
     *         Message does not exceed 62KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending an in-room text message, you must call joinRoom{@link #IRTCAudioRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCAudioRoomEventHandler#onUserMessageSendResult} callback to notify the message sender that the sending was successful or failed; <br>
     *        + If the text message is sent successfully, the user specified by user_id will receive onUserMessageReceived{@link #IRTCAudioRoomEventHandler#onUserMessageReceived} callback.
     */
    virtual int64_t sendUserMessage(const char* user_id, const char* message) = 0;

    /** 
     * @type api
     * @region multi-room
     * @brief Sends a binary message (P2P) to the specified user in the room
     * @param  [in] user_id <br>
     *        The ID of the message receiving user
     * @param  [in] length <br>
     *        The length of the binary string.
     * @param  [in] message <br>
     *         The content of the binary message. The message does not exceed 46KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   + Before sending in-room binary messages, you must call joinRoom{@link #IRTCAudioRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCAudioRoomEventHandler#onUserMessageSendResult} callback to notify the sender of the success or failure of the message; <br>
     *        + If the binary message is sent successfully, the user specified by user_id will receive the onUserBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#onUserBinaryMessageReceived} callback.
     */
    virtual int64_t sendUserBinaryMessage(const char* user_id, int length, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] message <br>
     *        The broadcast message sent by the user <br>
     *        Message does not exceed 62KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCAudioRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomMessageReceived{@link #IRTCAudioRoomEventHandler#onRoomMessageReceived} callback.
     */
    virtual int64_t sendRoomMessage(const char* message) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] size <br>
     *        The length of the binary message sent
     * @param  [in] message <br>
     *        The binary broadcast message sent by the user <br>
     *        The message does not exceed 46KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCAudioRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCAudioRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTCAudioRoomEventHandler#onRoomBinaryMessageReceived} callback.
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Publishes audio streams captured by camera/microphone in the current room.
     * @notes  <br>
     *        + Streams are not published automatically in multi-room mode by default, you need to call this API to publish streams manually.  <br>
     *        + An invisible user cannot publish audio stream. Call setUserVisibility{@link #IRTCAudioRoom#setUserVisibility} to change your visibility in the room.  <br>
     *        + Call startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms} to forward the published streams to the other rooms.  <br>
     *        + After you call this API, the other users in the room will receive onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}. Those who successfully received your stream will receive OnFirstRemoteAudioFrame{@link #IRTCAudioRoomEventHandler#OnFirstRemoteAudioFrame} at the same time.  <br>
     *        + Call unpublishStream{@link #IRTCAudioRoom#unpublishStream} to stop publishing streams.
     */
    virtual void publishStream() = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Stops publishing audio streams captured by microphone in the current room.
     * @notes  <br>
     *         + After calling publishStream{@link #IRTCAudioRoom#publishStream}, call this API to stop publishing streams. <br>
     *         + After calling this API, the other users in the room will receive onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream}.
     */
    virtual void unpublishStream() = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Subscribes to specific remote audio streams captured by microphone.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param [in] user_id The ID of the remote user who published the target audio stream.
     * @notes  <br>
     *        + You must first get the remote stream information through OnUserPublishStream{@link #IRTCAudioRoomEventHandler#OnUserPublishStream} before calling this API to subscribe to streams accordingly.  <br>
     *        + Any other exceptions will be included in OnStreamStateChanged{@link #IRTCAudioRoomEventHandler#OnStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void subscribeStream(const char* user_id) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Unsubscribes from specific remote audio streams captured by microphone.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param userId The ID of the remote user who published the target audio stream.
     * @notes  <br>
     *        + Any other exceptions will be included in OnStreamStateChanged{@link #IRTCAudioRoomEventHandler#OnStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void unsubscribeStream(const char* user_id) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Suspends receiving audio streams from a remote location.
     * @notes   <br>
     *         + This method only pauses the reception of the remote stream and does not affect the collection and transmission of the remote stream; <br>
     *         + This method does not change the user's subscription status and the attributes of the subscription stream. <br>
     *         + To resume receiving remote streams, call resumeAllSubscribedStream{@link #IRTCAudioRoom#resumeAllSubscribedStream}.
     */
    virtual void pauseAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region  multi-room
     * @brief  Resume receiving audios from the remote end
     * @notes  <br>
     *         + This method only resumes receiving of remote streams, and does not affect the collection and sending of remote streams; <br>
     *         + This method does not change the user's subscription status And properties of the subscription stream.
     */
    virtual void resumeAllSubscribedStream() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Start relaying audio stream across rooms. <br>
     *        After a user joins a room, you can call this method to publish the audio stream to multiple rooms that applies to scenarios such as anOnline talent contest and so on.
     * @param [in] configuration Information of the rooms where you want to relay the audio stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more inforamtion.
     * @return  <br>
     *        0: Success
     *        <0: Failure  <br>
     * @notes <br>
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged}.
     *        + After calling this method, listen the events from each room during the relaying by registering onForwardStreamEvent{@link #IRTCAudioRoomEventHandler#onForwardStreamEvent}.
     *        + Once the relaying begins, the other users in the room will receive callback of onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream} .
     *        + Call updateForwardStreamToRooms{@link #IRTCAudioRoom#updateForwardStreamToRooms} to add or remove the target room(s) after calling this method.
     *        + Call stopForwardStreamToRooms{@link #IRTCAudioRoom#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.
     *        + Call pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Update information of the rooms where you want to relay the audio stream to after calling startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms}. <br>
     *        Adding and removing rooms by calling this method will trigger onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged} on the local.
     * @param [in] configuration Information of the rooms where you want to relay the audio stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  <br>
     *          0: Success
     *          <0: Failure  <br>
     * @notes <br>
     *        + Users in the room which is added by calling this method will receive onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream} .
     *        + Users in the room which is removed by calling this method will receive onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream}  and onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave}.
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call to this method to stop relaying audio stream to all rooms after calling startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms}. <br>
     * @notes <br>
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCAudioRoomEventHandler#onForwardStreamStateChanged}.
     *        + The other users in the room will receive callback of onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}  when you stop relaying.
     *        + To stop relaying audio stream to specific rooms, call updateForwardStreamToRooms{@link #IRTCAudioRoom#updateForwardStreamToRooms} instead.
     *        + To resume the relaying in a short time, call pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms} instead and then call resumeForwardStreamToAllRooms{@link #IRTCAudioRoom#resumeForwardStreamToAllRooms} to recsume after that.
     */
    virtual void stopForwardStreamToRooms() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call this method to pause relaying audio stream to all rooms after calling startForwardStreamToRooms{@link #IRTCAudioRoom#startForwardStreamToRooms}. <br>
     *        After that, call resumeForwardStreamToAllRooms{@link #IRTCAudioRoom#resumeForwardStreamToAllRooms} to resume.
     * @notes The other users in the room will receive callback of onUserUnPublishStream{@link #IRTCAudioRoomEventHandler#onUserUnPublishStream} and onUserLeave{@link #IRTCAudioRoomEventHandler#onUserLeave} when you pause relaying.
     */
    virtual void pauseForwardStreamToAllRooms() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call this method to resume relaying to all rooms from the pause by calling pauseForwardStreamToAllRooms{@link #IRTCAudioRoom#pauseForwardStreamToAllRooms}.
     * @notes The other users in the room will receive callback of onUserJoined{@link #IRTCAudioRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCAudioRoomEventHandler#onUserPublishStream}  when you resume relaying.
     */
    virtual void resumeForwardStreamToAllRooms() = 0;
    /** 
     * @type api
     * @region Range Audio
     * @brief Gets range audio instance.
     * @return API call result:  <br>
     *        + IRangeAudio: Success. You will get an IRangeAudio{@link #IRangeAudio} returned from the SDK.  <br>
     *        + nullptr: Failure. The current SDK does not offer range audio function.
     * @notes The first time this API is called must be between you create a room and you actually enter the room.
     */
    virtual IRangeAudio* getRangeAudio() = 0;
    
    /** 
     * @type api
     * @region Spatial Audio
     * @brief Gets spatial audio instance.   <br>
     * @return API call result:  <br>
     *        + ISpatialAudio: Success. You will get an ISpatialAudio{@link #ISpatialAudio} returned from the SDK.  <br>
     *        + nullptr: Failure. The current SDK does not offer spatial audio function.
     * @notes   <br>
     *        + The first time this API is called must be between you create a room and you actually enter the room.  <br>
     *        + Only using real dual-channel playback device can you actually enjoy spatial audio effect.  <br>
     *        + Low-end device may have audio stalling issues due to its poor performance, so it is not recommended to enable spatial audio function on such kind of devices. <br>
     *        + SDK currently supports up to 30 users publishing audio with spatial audio enabled at the same time in the same room.
     */
    virtual ISpatialAudio* getSpatialAudio() = 0;
};

}  // namespace bytertc
