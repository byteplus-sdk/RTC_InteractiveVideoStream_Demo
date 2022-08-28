/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Room Interface
 */

#pragma once

#ifndef BYTE_RTC_ROOM_INTERFACE_H__
#define BYTE_RTC_ROOM_INTERFACE_H__

#include "bytertc_video_effect_interface.h"  // NOLINT
#include "bytertc_defines.h"
#include "bytertc_room_event_handler.h"
#include "bytertc_transcoder_interface.h"
#include "bytertc_publicstream_interface.h"
#include "bytertc_range_audio_interface.h"
#include "bytertc_spatial_audio_interface.h"

namespace bytertc {

/** 
 * @type api
 * @brief  Room interface
 */
class IRTCRoom {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCRoom() {
    }

    /** 
     * @type api
     * @region  multi-room
     * @brief  Leave and destroy the room created by calling createRtcRoom{@link #IRtcEngine#createRtcRoom}}.
     */
    virtual void destroy() = 0;

    /** 
     * @type api
     * @region Multi-room
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
     *            - Switch from `false` to `true`: onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}<br>
     *            - Switch from `true` to `false`: onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} <br>
     *        + The invisible user will receive the warning code, `kWarningCodePublishStreamForbiden`, when trying to publish media streams.
     */
    virtual void setUserVisibility(bool enable) = 0;



    /** 
     * @type api
     * @region multiroom
     * @brief By Setting `IRTCRoomEventHandler` you can get informed of the room-related events realted to this `IRtcRoom` instance.
     * @param  [in] room_event_handler Refer to IRTCRoomEventHandler{@link #IRTCRoomEventHandler}.
     */
    virtual void setRTCRoomEventHandler(IRTCRoomEventHandler* room_event_handler) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Create/join a room: create a room when the room does not exist; when the room exists, users who have not joined the room can join the room.   <br>
     *        Users in the same room can talk to each other. <br>
     *         Repeated calls after entering the room are invalid. The user must call leaveRoom{@link #IRTCRoom#leaveRoom} to exit the current room before joining the next room. <br>
     * @param  [in] token Dynamic key for authenticating the logged-in user. <br>
     *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. <br>
     *        + Apps with different App IDs cannot communicate with each other. <br>
     *        + Make sure that the App ID used to generate the Token is the same as the App ID used to create the engine, otherwise it will cause the join room to fail. <br>
     * @param  [in] room_id Added room ID. <br>
     *        The room ID is a non-empty string with a length of less than 128 bytes, and the following character set ranges are supported: <br>
     *            1. 26 capital letters A~ Z. <br>
     *            2. 26 lowercase letters a~ z. <br>
     *            3. 10 numbers 0~ 9. <br>
     *            4. Underline "_", at character "@", minus sign "-". <br>
     * @param  [in] user_info User information. See UserInfo{@link #UserInfo}. <br>
     * @param  [in] room_config Room parameter configuration, set the room mode and whether to automatically publish or subscribe to the flow. See RTCRoomConfig{@link #RTCRoomConfig} for the specific configuration mode. <br>
     * @return   <br>
     *         + 0: Success <br>
     *         + -1: Room_id/user_info.uid contains invalid parameters. <br>
     *         + -2: Already in the room. After the interface call is successful, as long as the return value of 0 is received and leaveRoom:{@link #IRTCRoom#leaveRoom} is not called successfully, this return value is triggered when the room entry interface is called again, regardless of whether the filled room ID and user ID are duplicated. <br>
     * @notes   <br>
     *        + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who entered the room later will kick the user who entered the room out of the room, and the user who entered the room will receive the onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}} callback notification. For the error type. See kErrorCodeDuplicateLogin in ErrorCode{@link #ErrorCode}. <br>
     *        + Local users will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}} callback notification after calling this method to join the room successfully. <br>
     *        + Local users call setUserVisibility{@link #IRTCRoom#setUserVisibility} to make themselves visible and then join the room, and remote users will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}. <br>
     *        + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After a successful reconnection, you will receive a local onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}} callback notification. <br>
     */
    virtual int joinRoom(const char* token, const UserInfo& user_info, const RTCRoomConfig& config) = 0;

    /** 
      * @type api
      * @region  room management
      * @brief  Leave RTC room.   <br>
      *        The user calls this method to leave the RTC room, end the call process, and release all call-related resources. <br>
      *        It is an asynchronous operation, and the call returns without actually exiting the room. When actually exiting the room, you will receive onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom}. <br>
      * @return   <br>
      *         + 0: Success <br>
      *         + < 0: Failure <br>
      * @notes   <br>
      *        + When visible users leave the room, others in the room will receive onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}. <br>
      *        + If the engine is destroyed immediately after this method is called, you will not receive onLeaveRoom{@link #IRTCRoomEventHandler#onLeaveRoom}. <br>
      *        + After calling joinRoom{@link #IRTCRoom#joinRoom} to join the room, you must call this API to end the call, otherwise you cannot start the next call. You can call this API in or out of the room. Repeated calls cause no negative effect. <br>
      */
    virtual void leaveRoom() = 0;

    /** 
     * @type api
     * @brief Update Token. <br>
     *        A Token used to join rooms has an expiration time. You will be informed 30 sec before the expiration of the token by onTokenWillExpire{@link #IRTCRoomEventHandler#onTokenWillExpire}. Call this API to renew the Token. Or the user will be removed from the room as the Token expires. <br>
     *         If you called joinRoom{@link #IRTCRoom#joinRoom} to join a room or reconnected into a room with an invalid Token, it would fail. You would get informed by onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}}. The error code is the `ERROR_CODE_INVALID_TOKEN` in ErrorCode{@link #ErrorCode}. Reacquire a token and call this API to renew the token. <br>
     * @param token  Valid token.  <br>
     *        If the Token is invalid, SDK will emit `ERROR_CODE_UPDATE_TOKEN_WITH_INVALID_TOKEN` defined in an ErrorCode{@link #ErrorCode}.
     * @return  <br>
     *          + 0: Success. <br>
     *          + < 0: Failure <br>
     * @notes  When the Token expired, the user would be removed from the room. And you would get informed of  `ERROR_CODE_EXPIRED_TOKEN` by onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}. Reacquire a token and call joinRoom{@link #IRTCRoom#joinRoom}} with the token to rejoin the room.
     */
    virtual void updateToken(const char* token) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Send a text message (P2P) to the specified user in the room
     * @param  [in] uid <br>
     *        Message Receives the user's ID
     * @param  [in] message <br>
     *        Text message content sent. <br>
     *         Message does not exceed 62KB.
     * @param [in] config Message type, see MessageConfig{@link #MessageConfig}.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending an in-room text message, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} callback to notify the message sender that the sending was successful or failed; <br>
     *        + If the text message is sent successfully, the user specified by uid will receive onUserMessageReceived{@link #IRTCRoomEventHandler#onUserMessageReceived} callback.
     */
    virtual int64_t sendUserMessage(const char* uid, const char* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /** 
     * @type api
     * @region multi-room
     * @brief Sends a binary message (P2P) to the specified user in the room
     * @param  [in] uid <br>
     *        The ID of the message receiving user
     * @param  [in] length <br>
     *        The length of the binary string.
     * @param  [in] message <br>
     *         The content of the binary message. The message does not exceed 46KB.
     *         The number of the message sent this time is incremented from
     * @param [in] config Message type, see MessageConfig{@link #MessageConfig}.
     * @return 1.  <br>
     * @notes   + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you will receive an onUserMessageSendResult{@link #IRTCRoomEventHandler#onUserMessageSendResult} callback to notify the sender of the success or failure of the message; <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the onUserBinaryMessageReceived{@link #IRTCRoomEventHandler#onUserBinaryMessageReceived} callback.
     */
    virtual int64_t sendUserBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config = kMessageConfigReliableOrdered) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] message <br>
     *        The broadcast message sent by the user <br>
     *        Message does not exceed 62KB.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} callback.
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
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} callback.
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Publishes media streams captured by camera/microphone in the current room.
     * @param [in] type Media stream type, used for specifying whether to publish audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *        + Streams are not published automatically in multi-room mode by default, you need to call this API to publish streams manually.  <br>
     *        + An invisible user cannot publish media streams. Call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change your visibility in the room.  <br>
     *        + Call publishScreen{@link #IRTCRoom#publishScreen} to start screen sharing.  <br>
     *        + Call startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} to forward the published streams to the other rooms.  <br>
     *        + After you call this API, the other users in the room will receive onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}. Those who successfully received your streams will receive onFirstRemoteAudioFrame{@link #IRtcEngineEventHandler#onFirstRemoteAudioFrame}/onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} at the same time.  <br>
     *        + Call unpublishStream{@link #IRTCRoom#unpublishStream} to stop publishing streams.
     */
    virtual void publishStream(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Stops publishing media streams captured by camera/microphone in the current room.
     * @param [in] type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *         + After calling publishStream{@link #IRtcEngine#publishStream}, call this API to stop publishing streams. <br>
     *         + After calling this API, the other users in the room will receive onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}.
     */
    virtual void unpublishStream(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Screen Sharing
     * @brief Publishes local screen sharing streams in the current room.
     * @param [in] type Media stream type, used for specifying whether to publish audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *         + An invisible user cannot publish media streams. Call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change your visibility in the room. <br>
     *         + After you called this API, the other users in the room will receive onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}. Those who successfully received your streams will receive onFirstRemoteAudioFrame{@link #IRtcEngineEventHandler#onFirstRemoteAudioFrame}/onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded} at the same time.  <br>
     *         + Call startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} to forward the published streams to the other rooms.  <br>
     *         + Call unpublishScreen{@link #IRTCRoom#unpublishScreen} to stop publishing screen sharing streams.
     */
    virtual void publishScreen(MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Screen Sharing
     * @brief Stops publishing local screen sharing streams in the current room.
     * @param [in] type Media stream type, used for specifying whether to stop publishing audio stream or video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *         + After calling publishScreen{@link #IRTCRoom#publishScreen}, call this API to stop publishing streams. <br>
     *         + After calling this API, the other users in the room will receive onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen}.
     */
    virtual void unpublishScreen(MediaStreamType type) = 0;

    /** 
     * @hidden
     * @deprecated since 336.1, use subscribeStream, unsubscribeStream, subscribeScreen and unsubscribeScreen instead.
     * @type api
     * @region Multi-room
     * @brief Subscribe to media streams in the room.   <br>
     *        Call this API to subscribe to media streams in the room regardless of subscription mode, either Auto or Manual. <br>
     *        Call this API to update the properties and configurations of the stream you have already subscribed to. <br>
     * @param  [in] user_id User ID of the publisher of the subscribed media stream <br>
     * @param  [in] stream_type Mainstream or screen-sharing stream. Refer to StreamIndex{@link #StreamIndex} for details.
     * @param  [in] media_type Media stream type to be subscribed to. Refer to  SubscribeMediaType{@link #SubscribeMediaType} for details. <br>
     * @param  [in] video_config Subscription configuration of video streams. Refer to SubscribeVideoConfig{@link #SubscribeVideoConfig} for details. <br>
     * @notes   <br>
     *         + Get the media stream information in the room from OnStreamAdd{@link #IRTCRoomEventHandler#OnStreamAdd} and OnStreamRemove{@link #IRTCRoomEventHandler#OnStreamRemove}. <br>
     *         + If the subscription fails, you will receive onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}. Refer to ErrorCode{@link #ErrorCode} for the specific reason of failure.
     *         + You can update the subscription configuration by calling the API even after calling PauseAllSubscribedStream{@link #IRTCRoom#PauseAllSubscribedStream} to pause streaming. Call ResumeAllSubscribedStream{@link #IRTCRoom#ResumeAllSubscribedStream} to resume streaming and apply the changes. <br>
     */
    virtual void subscribeUserStream(const char* user_id, StreamIndex stream_type, SubscribeMediaType media_type, const SubscribeVideoConfig& video_config) = 0;
    /** 
     * @type api
     * @region Video Management
     * @brief Sets your expected configuration of the remote video stream that you want to subscribe to or have subscribed to.
     * @param [in] user_id The ID of the target stream publisher
     * @param [in] remote_video_config Your expected configuration, see RemoteVideoConfig{@link #RemoteVideoConfig}.
     * @notes <br>
     *        + This API only works after the publisher calls enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} to enable publishing multiple video streams, in which case the subscriber will receive the stream from the publisher that is closest to the set configuration;  otherwise the subscriber will only receive one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + If you don't call this API after the publisher enables the function of publishing multiple streams, you will receive by default the video stream with the largest resolution set by the publisher.  <br>
     *        + You should call this API in the room. If you want to call it before entering the room, you should set the `remote_video_config` in the `room_config` when calling joinRoom{@link #IRTCRoom#joinRoom}.  <br>
     *        + You can call this API anytime before or after subscribing to the target stream. If you have already subscribed to the target stream when calling this API, your settings will take effect when you resubscribe to this stream.  <br>
     *        + SDK will automatically select the stream to be published or subscribed based on the settings of both sides.
     */
    virtual void setRemoteVideoConfig(const char *user_id,const RemoteVideoConfig &remote_video_config) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Subscribes to specific remote media streams captured by camera/microphone.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param [in] user_id The ID of the remote user who published the target audio/video stream.
     * @param [in] type Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *        + You must first get the remote stream information through onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void subscribeStream(const char *user_id,MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Unsubscribes from specific remote media streams captured by camera/microphone.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param [in] user_id The ID of the remote user who published the target audio/video stream.
     * @param [in] type Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void unsubscribeStream(const char *user_id,MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Subscribes to specific screen sharing media stream.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param [in] user_id The ID of the remote user who published the target screen audio/video stream.
     * @param [in] type Media stream type, used for specifying whether to subscribe to the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *        + You must first get the remote stream information through onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void subscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /** 
     * @type api
     * @region Room Management
     * @brief Unsubscribes from specific screen sharing media stream.  <br>
     *        You can call this API in both automatic subscription mode and manual subscription mode.
     * @param [in] user_id The ID of the remote user who published the target screen audio/video stream.
     * @param [in] type Media stream type, used for specifying whether to unsubscribe from the audio stream or the video stream. See MediaStreamType{@link #MediaStreamType}.
     * @notes  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void unsubscribeScreen(const char *user_id,MediaStreamType type) = 0;

    /**
     * @hidden
     */
    virtual void enableSubscribeLocalStream(bool enable) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Pause receiving remote media streams.
     * @param  [in] media_type Media stream type subscribed to. Refer to PauseResumeControlMediaType{@link #PauseResumeControlMediaType}.
     * @notes   <br>
     *         + Calling this API does not change the capture state and the transmission state of the remote clients. <br>
     *         + Calling this API does not cancel the subscription or change any subscription configuration. <br>
     *         + To resume, call resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream}.
     */
    virtual void pauseAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;

    /** 
     * @type api
     * @region  multi-room
     * @brief  Media stream type subscribed to. Refer to
     * @param  [in] media_type Media stream type subscribed to. Refer to PauseResumeControlMediaType{@link #PauseResumeControlMediaType}
     * @notes  <br>
     *         + Calling this API does not change the capture state and the transmission state of the remote clients.
     *         + Calling this API does not change any subscription configuration.
     */
    virtual void resumeAllSubscribedStream(PauseResumeControlMediaType media_type) = 0;


#ifndef ByteRTC_AUDIO_ONLY

    /** 
     * @type api
     * @region Multi-room
     * @brief Synchronizes published audio and video.  <br>
     *        When the same user simultaneously uses separate devices to capture and publish audio and video, there is a possiblity that the streams are out of sync due to the network disparity. In this case, you can call this API on the video publisher side and the SDK will automatically line the video stream up according to the timestamp of the audio stream, ensuring that the audio the receiver hears corresponds to the video the receiver watches.
     * @param [in] audio_user_id The ID of audio publisher. You can stop the current A/V synchronization by setting this parameter to null.
     * @notes  <br>
     *        + You can call this API anytime before or after entering the room.  <br>
     *        + The source user IDs of the audio and video stream to be synchronized must be in the same RTC room.  <br>
     *        + When the A/V synchronization state changes, you will receive onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange}.  <br>
     *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
     *        + If you want to change the audio source, call this API again with a new `audio_user_id`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
     */
    virtual void setMultiDeviceAVSync(const char* audio_user_id) = 0;

    /**
     * @hidden
    */
    virtual void updateCloudRending(const char* cloudrenderJsonString) = 0;

#endif

    /**
     * @hidden
     */
    virtual void setCustomUserRole(const char* role) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Start relaying media stream across rooms. <br>
     *        After a user joins a room, you can call this method to publish the media stream to multiple rooms that applies to scenarios such as anOnline talent contest and so on.
     * @param [in] configuration Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more inforamtion.
     * @return  <br>
     *        0: Success
     *        <0: Failure  <br>
     * @notes <br>
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged}.
     *        + After calling this method, listen the events from each room during the relaying by registering onForwardStreamEvent{@link #IRTCRoomEventHandler#onForwardStreamEvent}.
     *        + Once the relaying begins, the other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}.
     *        + Call updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} to add or remove the target room(s) after calling this method.
     *        + Call stopForwardStreamToRooms{@link #IRTCRoom#stopForwardStreamToRooms} to stop relaying to all rooms after calling this method.
     *        + Call pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} to pause relaying to all rooms after calling this method.
     */
    virtual int startForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Update information of the rooms where you want to relay the media stream to after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. <br>
     *        Adding and removing rooms by calling this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged} on the local.
     * @param [in] configuration Information of the rooms where you want to relay the media stream to. Refer to ForwardStreamConfiguration{@link #ForwardStreamConfiguration} for more information.
     * @return  <br>
     *          0: Success
     *          <0: Failure  <br>
     * @notes <br>
     *        + Users in the room which is added by calling this method will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen}.
     *        + Users in the room which is removed by calling this method will receive onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}/onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} and onUserLeave{@link #IRTCRoomEventHandler#onUserLeave}.
     */
    virtual int updateForwardStreamToRooms(const ForwardStreamConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call to this method to stop relaying media stream to all rooms after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. <br>
     * @notes <br>
     *        + Call this method will trigger onForwardStreamStateChanged{@link #IRTCRoomEventHandler#onForwardStreamStateChanged}.
     *        + The other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} when you stop relaying.
     *        + To stop relaying media stream to specific rooms, call updateForwardStreamToRooms{@link #IRTCRoom#updateForwardStreamToRooms} instead.
     *        + To resume the relaying in a short time, call pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms} instead and then call resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} to recsume after that.
     */
    virtual void stopForwardStreamToRooms() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call this method to pause relaying media stream to all rooms after calling startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}. <br>
     *        After that, call resumeForwardStreamToAllRooms{@link #IRTCRoom#resumeForwardStreamToAllRooms} to resume.
     * @notes The other users in the room will receive callback of onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}/onUserUnPublishScreen{@link #IRtcEngineEventHandler#onUserUnPublishScreen} and onUserLeave{@link #IRTCRoomEventHandler#onUserLeave} when you pause relaying.
     */
    virtual void pauseForwardStreamToAllRooms() = 0;

    /** 
     * @type api
     * @region Multi-room
     * @brief Call this method to resume relaying to all rooms from the pause by calling pauseForwardStreamToAllRooms{@link #IRTCRoom#pauseForwardStreamToAllRooms}.
     * @notes The other users in the room will receive callback of onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} and onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}/onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} when you resume relaying.
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

} // namespace bytertc

#endif // BYTE_RTC_ROOM_INTERFACE_H__
