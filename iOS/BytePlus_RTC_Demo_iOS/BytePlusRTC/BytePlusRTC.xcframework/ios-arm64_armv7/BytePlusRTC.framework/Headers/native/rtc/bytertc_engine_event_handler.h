/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Event Handler
*/

#pragma once

#ifndef BYTE_RTC_EVENT_HANDLER_H__
#define BYTE_RTC_EVENT_HANDLER_H__

#include "bytertc_defines.h"

namespace bytertc {

/**  
 * @type callback
 * @brief  Audio & video engine event callback interface.   <br>
 *         When the RTCEngine instance createRtcEngine{@link #createRtcEngine} is created, the callback instance is passed in. <br>
 *         See IRtcEngineEventHandler{@link #IRtcEngineEventHandler}, IRTCRoomEventHandler{@link #IRTCRoomEventHandler}
 */
class IRtcEngineEventHandler {
public:
    /**
     * @hidden
     */
    virtual ~IRtcEngineEventHandler() {
    }
	
	/**  
    * @hidden
    * @type callback
    * @region Game Interface
    * @brief In the game scene, when the sendmode of the room user is modified, the event is called back. There are only three sending modes: mute, send to the team, and send to the world.
    * @param  [in] uid <br>
    *         Remote user id.
    * @param  [in] range_audio_mode <br>
    *         The sending mode of the remote user, see: RangeAudioMode{@link #RangeAudioMode}.
    */
    virtual void onUserAudioSendModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

    /**  
     * @hidden
     * @type callback
     * @region game interface
     *@brief In the game scene, when the recvmode of the room user is modified, the event is called back. There are only three listening modes, namely: mute, listen to the team, and listen to the world.
     *@param  [in] uid <br>
     *        Remote user id.
     *@param  [in] range_audio_mode <br>
     *        Receive mode for remote users, see: RangeAudioMode{@link #RangeAudioMode}.
     */
    virtual void onUserAudioRecvModeChange(const char* uid, int range_audio_mode) {
        (void)uid;
        (void)range_audio_mode;
    }

        /** 
     * @type callback
     * @region Warning code
     * @brief Triggers the callback when an internal warning event occurs
     * @param  [in] warn
     *        Warning identification code, see: WarningCode{@link #WarningCode}
     */
    virtual void onWarning(int warn) {
        (void)warn;
    }

    /** 
     * @type callback
     * @region Error code
     * @brief This callback is triggered when an irreversible error occurs inside the SDK.
     * @param  [in] err Error code. See ErrorCode{@link #ErrorCode}
     */
    virtual void onError(int err) {
        (void)err;
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region Audio Mixing
     * @brief Local music file playback has ended callback.
     *        The callback is triggered when the mix file started by calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} has finished playing.
     */
    virtual void onAudioMixingFinished() {
    }

    /** 
     * @type callback
     * @region  Mix
     * @brief   Callback when audio mix file playback state changes
     * @param  [in] mix_id <br>
     *         Mix ID <br>
     *         Unique ID passed in when using IAudioMixingManager{@link #IAudioMixingManager} related interface.
     * @param  [in] state <br>
     *        Mix status <br>
     *        The mix status can be referred to: AudioMixingState{@link #AudioMixingState}.
     * @param  [in] error
     *         Error code <br>
     *         See AudioMixingError{@link #AudioMixingError}
     * @notes   <br>
     *        + The timing of this callback will be triggered is summarized as follows: <br>
     *        + When the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method is successfully called, a callback with a state value of kAudioMixingStatePlaying will be triggered; otherwise the state will be triggered A callback with a value of kAudioMixingStateFailed. <br>
     *        + When startAudioMixing{@link #IAudioMixingManager#startAudioMixing} is called repeatedly with the same ID, the latter overrides the previous, and this callback notifies the previous mix has stopped with kAudioMixingStateStopped. <br>
     *        + When calling the pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} method to pause playback successfully, a callback with a state value of kAudioMixingStatePaused will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + When the resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} method is called to resume playing successfully, a callback with a state value of kAudioMixingStatePlaying will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + When calling the stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} method to pause playback successfully, a callback with a state value of kAudioMixingStateStopped will be triggered; otherwise, a callback with a state value of kAudioMixingStateFailed will be triggered. <br>
     *        + The end of playback triggers a callback with the state value kAudioMixingStateFinished.
     */
    virtual void onAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state, bytertc::AudioMixingError error) {
    }

    /** 
     * @type callback
     * @region Audio Mixing
     * @brief Callback for playback progress of mixed audio files
     * @param [in] mix_id Mixing ID  <br>
     * @param [in] progress The current playback progress (ms) of the mixed audio file
     * @notes After calling setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} to set the time interval to a value greater than 0, or calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to set the time interval in AudioMixingConfig{@link #AudioMixingConfig} to a value greater than 0, the SDK will trigger the callback according to the set time interval.
     */
    virtual void onAudioMixingPlayingProgress(int mix_id, int64_t progress){
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type callback
     * @region Audio Mixing
     * @brief Local sound file playback has ended callback.
     *        When the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method is called to start playing the specified audio file, the application will receive the callback after the audio file has finished playing.
     * @param  [in] sound_id
     *         Sound ID, application caller maintenance, please ensure uniqueness.
     */
    virtual void onAudioEffectFinished(int sound_id) {
    }

    /** 
     * @type callback
     * @region  engine management
     * @brief  Terminal monitoring log callback. The callback is triggered when a terminal monitoring event is generated.
     * @param  [in] log_type <br>
     *         Event type. The current type is fixed to "live_webrtc_monitor_log".
     * @param  [in] log_content <br>
     *         Terminal monitoring log content.
     */
    virtual void onLogReport(const char* log_type, const char* log_content) {
        (void)log_type;
        (void)log_content;
    }

    /** 
     * @hidden (macOS, Windows)
     * @type callback
     * @region Audio event callback
     * @brief Audio playback The event is called back when the device changes.
     * @param  [in] device Changed audio playback device. See AudioPlaybackDevice{@link #AudioPlaybackDevice}. <br>
     */
    virtual void onAudioPlaybackDeviceChanged(AudioPlaybackDevice device) {
        (void)device;
    };

    /** 
     * @hidden (macOS, Windows)
     * @type callback
     * @region Audio event callback
     * @brief Audio playback The event is called back when the device changes.
     * @param  [in] device Changed audio playback device. See AudioRoute{@link #AudioRoute}. <br>
     */
    virtual void onAudioRouteChanged(AudioRoute route) {
        (void)route;
    };

    /** 
     * @type callback
     * @region  engine management
     * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
     * @param  [in] state The current connection status between the SDK and the signaling server. See ConnectionState{@link #ConnectionState}
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
    }

    /** 
     * @type callback
     * @region Engine management
     * @brief SDK Current network connection type change callback. Callbacks the event when the current network connection type of the SDK changes.
     * @param  [in] type <br>
     *        SDK The current network connection type, see: NetworkType{@link #NetworkType}.
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
    }

    /** 
     * @type callback
     * @region  audio & video fallback
     * @brief publish performance fallback is not turned on locally. When insufficient device performance is detected, this callback is received. <br>
     *        Locally turn on the release performance fallback. When the release performance fallback/recovery is caused due to device performance/network reasons, this callback is received.
     * @param  [in] mode Indicates whether the release fallback function is turned on locally. See PerformanceAlarmMode{@link #PerformanceAlarmMode} <br>
     *                   + When the publisher does not turn on the release performance fallback, the mode value is kPerformanceAlarmModeNormal. <br>
     *                   + When the publisher turns on the release performance fallback, the mode value is kPerformance AlarmModeSimulcast.
     * @param  [in] room_id <br>
     *                       + When the release performance fallback is not turned on, the room_id is empty <br>
     *                       + When the release performance fallback is turned on, the room_id is the room ID affected by the alarm.
     * @param  [in] reason For the alarm. See PerformanceAlarmReason{@link #PerformanceAlarmReason}
     * @param  [in] data Performance rollback related data. See SourceWantedData{@link #SourceWantedData}.
     */
    virtual void onPerformanceAlarms(bytertc::PerformanceAlarmMode mode, const char* room_id,
            bytertc::PerformanceAlarmReason reason, const bytertc::SourceWantedData& data) {
        (void)mode;
        (void)room_id;
        (void)reason;
        (void)data;
    }

    /** 
     * @hidden
     * @deprecated since 337, using OnAudioDeviceStateChanged and OnVideoDeviceStateChanged instead.
     * @type callback
     * @region  engine management
     * @brief  Callback of media-device state.  <br>
     *         Media devices includes the following three: audio capture devices, audio playback devices, and video capture devices.
     * @param  [in] device_id Device ID
     * @param [in] device_type Device type. Refer to MediaDeviceType{@link #MediaDeviceType} for more details.
     * @param  [in] device_state Device state. Refer to MediaDeviceState{@link #MediaDeviceState} for more details.
     * @param  [in] device_error Device error. Refer to MediaDeviceError{@link #MediaDeviceError} for more details.
     */
    virtual void onMediaDeviceStateChanged(const char* device_id,
                                           bytertc::MediaDeviceType device_type,
                                           bytertc::MediaDeviceState device_state,
                                           bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    virtual void onAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    virtual void onVideoDeviceStateChanged(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    /** 
     * @hidden
     * @deprecated since 337, using OnAudioDeviceWarning and OnVideoDeviceWarning instead.
     * @type callback
     * @region Engine Management
     * @brief Media device warning callback. The media devices includes: audio capture devices, audio rendering devices, and video capture devices.
     * @param [in] device_id Device ID
     * @param [in] device_type Device type. See MediaDeviceType{@link #MediaDeviceType}
     * @param [in] device_warning Device error type. See MediaDeviceWarning{@link #MediaDeviceWarning}
     */
    virtual void onMediaDeviceWarning(const char* device_id, bytertc::MediaDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning){
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }

    virtual void onAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }

    virtual void onVideoDeviceWarning(const char* device_id, bytertc::RTCVideoDeviceType device_type,
            bytertc::MediaDeviceWarning device_warning) {
        (void)device_id;
        (void)device_type;
        (void)device_warning;
    }

    /** 
     * @type callback
     * @region  engine management
     * @brief  Periodically (2s) issue callbacks to report the current cpu and memory usage
     * @param  [in] stats Return the structure containing the current system state information. See SysStats{@link #SysStats}
     */
    virtual void onSysStats(const bytertc::SysStats& stats) {
    }

    /** 
     * @type callback
     * @region Proxy callback
     * @brief HTTP Receive the callback when the proxy connection state changes.
     * @param  [in] state The current HTTP proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
        virtual void onHttpProxyState(int state) {
    }

    /** 
     * @type callback
     * @region Proxy callback
     * @brief HTTPS Receive the callback when the proxy connection state changes.
     * @param   [out] State the current HTTPS proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
    }

    /** 
     * @type callback
     * @region Proxy callback
     * @brief Socks5 Receive the callback when the proxy state changes.
     * @param  [out] State SOCKS5 proxy connection status. See Socks5ProxyState{@link #Socks5ProxyState}
     * @param  [out] Cmd every step of the proxy connection operating command
     * @param  [out] Proxy_address proxy address information
     * @param  [out] Local_address the local address used by the current connection
     * @param  [out] Remote_address the remote connection address
     */
    virtual void onSocks5ProxyState(int state,
        const char* cmd,
        const char* proxy_address,
        const char* local_address,
        const char* remote_address) {
    }

    /** 
     * @type callback
     * @region Local recording
     * @brief Get a callback of the local recording status.   <br>
     *         The callback is triggered by startFileRecording{@link #IRtcEngine#startFileRecording} or stopFileRecording{@link #IRtcEngine#stopFileRecording}.
     * @param  [out] Type the stream properties of the recorded stream. See StreamIndex{@link #StreamIndex}
     * @param  [out] State the recording status. See RecordingState{@link #RecordingState}
     * @param  [out] Error_code recording error code. See RecordingErrorCode{@link #RecordingErrorCode}
     * @param  [out] Info For more information about the recorded file. See RecordingInfo {@link # RecordingInfo}
     */
    virtual void onRecordingStateUpdate(
            StreamIndex type, RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region Local recording
     * @brief Local recording progress callback.   <br>
     *        This callback is triggered by startFileRecording{@link #IRtcEngine#startFileRecording}. When the recording state is normal, the system will prompt the recording progress through this callback every second.
     * @param [out] Type the stream properties of the recorded stream. See StreamIndex{@link #StreamIndex}
     * @param [out] Process the recording progress. See RecordingProgress{@link #RecordingProgress}
     * @param [out] Info For more information about the recorded file. See RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingProgressUpdate(StreamIndex type, RecordingProgress process, RecordingInfo info) {
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief login result callback
     * @param  [in] uid <br>
     *        login user ID
     * @param  [in] error_code <br>
     *        login result <br>
     *        See LoginErrorCode{@link #LoginErrorCode}.
     * @param  [in] elapsed <br>
     *         The time taken from the call to the login{@link #IRtcEngine#login} interface to return the result is <br>
     *         In ms. This callback is received after
     * @notes login{@link #IRtcEngine#login} is called. login{@link #IRtcEngine#login}
     */
    virtual void onLoginResult(const char* uid, int error_code, int elapsed) {
        (void)uid;
        (void)error_code;
        (void)elapsed;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief logout result callback
     * @notes After calling logout{@link #IRtcEngine#logout}, you will receive this callback.
     */
    virtual void onLogout() {
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Set the return result of the application server parameter
     * @param  [in] error <br>
     *        Set the result <br>
     *         + Return 200, set successfully <br>
     *         + Return other, set failed
     * @notes Receive this callback after calling setServerParams{@link #IRtcEngine#setServerParams}.
     */
    virtual void onServerParamsSetResult(int error) {
        (void)error;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief The return result of querying the login status of the peer or local user
     * @param  [in] peer_user_id <br>
     *        The user ID that needs to be queried
     * @param  [in] status <br>
     *        The user login status of the query <br>
     *        See USER_ONLINE_STATUS{@link #USER_ONLINE_STATUS}.
     * @notes You must first call getPeerOnlineStatus{@link #IRtcEngine#getPeerOnlineStatus} to receive this callback.
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message from an out-of-room user calling sendUserMessageOutsideRoom{@link #IRtcEngine#sendUserMessageOutsideRoom}
     * @param  [in] uid <br>
     *        Message sender ID
     * @param  [in] message <br>
     *        Received text message content
     */
    virtual void onUserMessageReceivedOutsideRoom(const char* uid, const char* message) {
        (void)uid;
        (void)message;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a binary message from an out-of-room user calling sendUserBinaryMessageOutsideRoom{@link #IRtcEngine#sendUserBinaryMessageOutsideRoom}
     * @param  [in] uid <br>
     *        Message sender ID
     * @param  [in] size <br>
     *        Binary message length
     * @param  [in] message <br>
     *         Binary message content received
     */
    virtual void onUserBinaryMessageReceivedOutsideRoom(const char* uid, int size, const uint8_t* message) {
        (void)uid;
        (void)size;
        (void)message;
    }
    /** 
     * @type callback
     * @region Real-time messaging
     * @brief A callback that sends a message to a specified user outside the room
     * @param  [in] msgid <br>
     *        The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param  [in] error <br>
     *         Message sending result <br>
     *         See UserMessageSendResult{@link #UserMessageSendResult}.
     * @notes Receive this callback when a message is sent by calling sendUserMessageOutsideRoom{@link #IRtcEngine#sendUserMessageOutsideRoom} or sendUserBinaryMessageOutsideRoom{@link #IRtcEngine#sendUserBinaryMessageOutsideRoom}.
     */
    virtual void onUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Callback to send a message to the application server
     * @param [in] msgid The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param [in] error Message Sending Results. See UserMessageSendResult{@link #UserMessageSendResult}.
     * @param message The message returned in ACK when the application server receives HTTP request.
     * @notes Receive this callback when you call sendServerMessage{@link #IRtcEngine#sendServerMessage} or sendServerBinaryMessage{@link #IRtcEngine#sendServerBinaryMessage}} to send a message to your application server.
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

    /** 
     * @type callback
     * @region Video management
     * @brief Receive this callback when you receive a video frame with a SEI message sent via sendSEIMessage{@link #IRtcEngine#sendSEIMessage}
     * @param  [in] stream_key Contains the user name, room name and media stream of the SEI sender. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param  [in] message The content of the SEI message received
     * @param  [in] length Length of received SEI message
    */
    virtual void onSEIMessageReceived(RemoteStreamKey stream_key, const uint8_t* message, int length){
        (void)stream_key;
        (void)message;
        (void)length;
    }

    /** 
     * @hidden
     * @type callback
     * @region Message
     * @brief Callback about publishing status of the black frame video stream .  <br>
     *        In a voice call scenario, when the local user calls sendSEIMessage{@link #IRtcEngine#sendSEIMessage} to send SEI data with a black frame, the sending status of the stream is notified to the remote user through this callback.  <br>
     *        You can tell from this callback that the video frame carrying SEI data is a black frame and thus not render that video frame.
     * @param key Information about stream from the remote user, see RemoteStreamKey{@link #RemoteStreamKey}.
     * @param type State of the black frame video stream, see SEIStreamEventType{@link #SEIStreamEventType}.
     */
    virtual void onSEIStreamUpdate(const RemoteStreamKey& key, SEIStreamEventType type) {
        (void)key;
        (void)type;
    }

     /** 
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport}, you will periodically receive this callback for the information about the subscribed remote audio streams. <br>
      *        The remote audio streams includes the microphone audio and screen audio collected using the RTC SDK internal mechanism/custom mechanism.
      * @param [in] audio_properties_infos See RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}.
      * @param [in] audio_properties_info_number The length of `audio_properties_infos`
      * @param [in] total_remote_volume The total volume of all the subscribed remote streams. The range is [0,255]. <br>
      *        + [0,25] Is close to silent; <br>
      *        + [25,75] Is low volume; <br>
      *        + [76,204] Is medium volume; <br>
      *        + [205,255] Is high volume. <br>
      */
    virtual void onRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos, int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /** 
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport}, you will periodically receive this callback for the information about local audio. <br>
      *        Local audio includes the microphone audio and the screen audio captured using RTC SDK internal mechanisms.
      * @param [in] audio_properties_infos See LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo}.
      * @param [in] audio_properties_info_number The length of `audio_properties_infos`
      */
    virtual void onLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos, int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }
    /** 
     * @type callback
     * @region Audio Device Management
     * @brief Notification on the playing volume during the test for the local audio devices
     * @param [in] volume playing volume during the test for the local audio devices in milliseconds. We recommend to set it to 200 ms.The range is [0,255]. 
     * @notes Start an audio-device test by calling startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} or startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest} will register this callback for regular notification on playing volume. You can set the time interval between each callback by passing a proper value when calling the API above. 
     */
    virtual void onAudioPlaybackDeviceTestVolume(int volume) {
        (void)volume;
    }
    /** 
     * @type callback
     * @region Audio Management
     * @brief After calling enableAudioPropertiesReport{@link #IRtcEngine#enableAudioPropertiesReport}, you will periodically receive this callback for the active speaker information. <br>
     * @param room_id  Room ID.
     * @param uid The user ID of the active speaker.
     */
    virtual void onActiveSpeaker(const char* room_id, const char* uid) {
        (void)room_id;
        (void)uid;
    }

    /** 
     * @type api
     * @region audio management
     * @brief Audio stream synchronization information callback. You can use this callback to receive audio stream synchronization information sent remotely after the remote user calls sendStreamSyncInfo{@link #IRtcEngine#sendStreamSyncInfo} to send an audio stream synchronization message. <br>
     * @param  [in] stream_key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] stream_type Media stream type. See SyncInfoStreamType{@link #SyncInfoStreamType}.
     * @param  [in] data Message content.
     * @param  [in] length Message length.
     */
    virtual void onStreamSyncInfoReceived(RemoteStreamKey stream_key, SyncInfoStreamType stream_type,
                                         const uint8_t* data,
                                         int32_t length) {
        (void)stream_key;
        (void)stream_type;
        (void)data;
        (void)length;
    }

    /** 
     * @type callback
     * @region Pre-call network detection
     * @brief Pre-call network detection result
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
     * @notes Receives this callback every 2s after the call startNetworkDetection{@link #IRtcEngine#startNetworkDetection} starts probing.
     */
    virtual void onNetworkDetectionResult(NetworkDetectionLinkType type, NetworkQuality quality, int rtt, double lost_rate,
                                      int bitrate, int jitter){
        (void)type;
        (void)quality;
        (void)rtt;
        (void)lost_rate;
        (void)bitrate;
        (void)jitter;
    }

    /** 
     * @type callback
     * @region Pre-call network probing
     * @brief Pre-call network probing ends <be>
     *        The following will stop detection and receive this primary callback:  <br>
     *        1. This callback is received once when the stopNetworkDetection{@link #IRtcEngine#stopNetworkDetection} interface is called to stop probing;  <br>
     *        2. Stop detection when the first frame of remote/local audio is received;  <br>
     *        3. Stop detecting when the detection exceeds 3 minutes;  <br>
     *        4. When the probe link is disconnected for a certain period of time, the probe is stopped.
     * @param [in] reason   <br>
     *        See NetworkDetectionStopReason{@link #NetworkDetectionStopReason} for reasons of stopping probing.
     */
    virtual void onNetworkDetectionStopped(NetworkDetectionStopReason reason){
        (void)reason;
    }
    /** 
     * @type callback
     * @brief Callback of the result of subscribing to the public stream<br>
     *        You will be informed of the result of subscribing to the public stream by this callback after calling startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream}.
     * @param [in] public_stream_id 
     * @param [in] errorCode Code for the result of publishing the public stream<br>
     *        `200`: Success
     */
    virtual void onPlayPublicStreamResult(const char* public_stream_id, int errorCode) {
        (void)public_stream_id;
        (void)errorCode;
    }
    /** 
     * @type callback
     * @brief Callback of the SEI carried by the public video stream<br>
     *        You will receive SEI by this callback if the public stream published by calling startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} carrying SEI.
     * @param [in] public_stream_id ID of the public stream
     * @param [in] message SEI(supplemental enhancement information) carried by the public video stream
     * @param [in] message_length Length of the SEI
     * @notes <br>
     *       You will receive SEI from all the video frames if the SEI do not have conflicts.<br>
     *       However, if SEI from video frames have conflicts, you will receive only one of them.
     */
    virtual void onPublicStreamSEIMessageReceived(const char* public_stream_id, const uint8_t* message, int message_length) {
        (void)public_stream_id;
        (void)message;
        (void)message_length;
    }
    /** 
     * @type callback
     * @brief Callback of successfully decoding of the first video frame of the public stream<br>
     *        Refer to startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} for details about subsribing to a public stream.
     * @param [in] public_stream_id ID of the public stream
     * @param [in] info Information of the video stream. Refer to VideoFrameInfo{@link #VideoFrameInfo} for more details.
     */
    virtual void onFirstPublicStreamVideoFrameDecoded(const char* public_stream_id, const VideoFrameInfo& info) {
        (void)public_stream_id;
    }
    /** 
     * @type callback
     * @brief Callback of successfully decoding of the first audio frame of the public stream<br>
     *        Refer to startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} for details about subsribing to a public stream.
     * @param [in] public_stream_id ID of the public stream
     */
    virtual void onFirstPublicStreamAudioFrame(const char* public_stream_id) {
        (void)public_stream_id;
    }
    
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

    virtual void onTokenWillExpire() {

    }

    /** 
     * @hidden
     * @deprecated Since 329.1, use onLocalAudioPropertiesReport/onRemoteAudioPropertiesReport instead
     * @type callback
     * @region audio event callback
     * @brief Prompt all users in the room to send a callback for volume.
     * @param  [in] speakers The ID and volume of the local user and the remote user subscribed to.
     *                       See: AudioVolumeInfo{@link #AudioVolumeInfo}.
     * @param  [in] speaker_number Length of speakers array.
     * @param  [in] total_remote_volume The sum of all audio volumes contained in speakers, the value range is: [0,255]
     * @notes
     *         + For local users: As long as local audio collection is performed, the callback will contain the volume information of the local audio stream. <br>
     *         + For remote users: The local must subscribe to the audio stream of a remote user before the callback contains the volume information of the audio stream it sent.
     */
    virtual void onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speaker_number, int total_remote_volume) {
        (void)speakers;
        (void)speaker_number;
        (void)total_remote_volume;
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
      * @region Room management
      * @brief Receives this callback when the following occurs: <br>
      *        + When the remote visible user calls leaveRoom{@link #IRTCRoom#leaveRoom} to leave the room; <br>
      *        + When the remote visible user calls setUserVisibility{@link #IRTCRoom#setUserVisibility} to switch to invisibility. <br>
      *        + The remote visible user is disconnected. <br>
      * @param [in] uid The ID of the user who leaves the room, or switches to invisible. <br>
      * @param [in] See UserOfflineReason{@link #UserOfflineReason}.
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
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region Media Stream Management
     * @brief Transmission state change of an audio stream in the room triggers this callback. Refer to muteLocalAudio{@link #IRtcEngine#muteLocalAudio} for more details.
     * @param  [in] user_id The user who changes his/her transmission state of the audio streams
     * @param  [in] mute_state Transmission state of the audio streams. Refer to MuteState{@link #MuteState} for more details.
     */
    virtual void onUserMuteAudio(const char* user_id, MuteState mute_state) {
        (void)user_id;
        (void)mute_state;
    }


    /** 
     * @hidden
     * @deprecated since 323.1, use onUserStartAudioCapture instead
     * @type callback
     * @region Audio event callback
     * @brief When the remote user turns on/off audio device capture, others in the room will receive this callback.
     *        The callback is triggered by the remote user calling the startAudioCapture{@link #IRtcEngine#startAudioCapture} method.
     * @param  [in] uid Remote user ID
     * @param  [in] enabled Whether the user has audio device capture <br>
     *        + True: the user has audio device capture <br>
     *        + False: the user has audio device capture closed <br>
     *        + This interface is deprecated, please use onUserStartAudioCapture{@link #IRTCRoomEventHandler#onUserStartAudioCapture} And onUserStopAudioCapture{@link #IRTCRoomEventHandler#onUserStopAudioCapture} <br>
     */
    virtual void onUserEnableLocalAudio(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief The remote clients in the room will be informed of the state change via this callback after the visible user starts audio capture by calling startAudioCapture{@link #IRtcEngine#startAudioCapture}.
     * @param  [in] user_id The user who starts the internal audio capture
     */
    virtual void onUserStartAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief The remote clients in the room will be informed of the state change via this callback after the visible user stops audio capture by calling stopAudioCapture{@link #IRtcEngine#stopAudioCapture}.
     * @param  [in] user_id The user who stops the internal audio capture
     */
    virtual void onUserStopAudioCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief Receive the callback when the first audio frame is locally collected
     * @param  [in] index Audio stream properties. See StreamIndex{@link #StreamIndex}
     */
    virtual void onFirstLocalAudioFrame(StreamIndex index) {
        (void)index;
    }


    /** 
     * @type callback
     * @region Audio event callback
     * @brief Receives the callback when the first frame from a remote audio stream is received.
     * @param  [in] key Remote audio stream information. See RemoteStreamKey{@link #RemoteStreamKey}
     * @notes The callback is received when the user has just received each audio stream in the room.
     */
    virtual void onFirstRemoteAudioFrame(const RemoteStreamKey& key) {
        (void)key;
    }


    /** 
     * @hidden
     * @deprecated since 336.1, use onUserUnPublishStream and onUserUnPublishScreen instead.
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
    virtual void onUserUnPublishStream(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
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
    virtual void onUserUnPublishScreen(const char* uid, MediaStreamType type,StreamRemoveReason reason) {
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
     * @notes Local users will receive this callback:  <br>
     *        + After calling subscribeStream{@link #IRTCRoom#subscribeStream}/unsubscribeStream{@link #IRTCRoom#unsubscribeStream} to change the subscription status of remote media streams captured by camera/microphone.  <br>
     *        + After calling subscribeScreen{@link #IRTCRoom#subscribeScreen}/unsubscribeScreen{@link #IRTCRoom#unsubscribeScreen} to change the subscription status of remote screen sharing streams.
     */
    virtual void onStreamSubscribed(SubscribeState state_code, const char* user_id, const SubscribeConfig& info) {
        (void)state_code;
        (void)user_id;
        (void)info;
    }

    /** 
     * @type callback
     * @region  audio & video rollback
     * @brief Once the Fallback option is set, Fallback or reverting from a Fallback of a media stream will trigger this callback.
     * @param  [in] event Information of stream switching. Refer to RemoteStreamSwitch{@link #RemoteStreamSwitch} for more details.
     * @notes Call setSubscribeFallbackOption{@link #IRtcEngine#setSubscribeFallbackOption} or configure Fallback options on the server side to register this callback.
     */
    virtual void onSimulcastSubscribeFallback(const RemoteStreamSwitch& event) {
        (void)event;
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
     * @type callback
     * @region Video Management
     * @brief RTC SDK receives this callback when the first video frame or screen video frame capture is completed locally.
     * @param [in] index Stream property. See StreamIndex{@link #StreamIndex}.
     * @param [in] info Video information. See VideoFrameInfo{@link #VideoFrameInfo}.
     * @notes For captured local video frames, you can call setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} or setLocalVideoSink{@link #IRtcEngine#setLocalVideoSink} to render locally.
     */
    virtual void onFirstLocalVideoFrameCaptured(StreamIndex index, VideoFrameInfo info) {
        (void)index;
        (void)info;
    }


    /** 
     * @type callback
     * @region video management
     * @brief Receive this callback when the local video size or rotation configuration changes.
     * @param [in] index See StreamIndex{@link #StreamIndex}。
     * @param [in] info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onLocalVideoSizeChanged(StreamIndex index, const VideoFrameInfo& info) {
        (void)index;
        (void)info;
    }


    /** 
     * @type callback
     * @region Video Management
     * @brief Users in the room who subscribe to this video stream receive this callback when the remote video size or rotation configuration changes.
     * @param  [in] key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onRemoteVideoSizeChanged(RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }


    /** 
     * @type callback
     * @region Video Management
     * @brief  Receive this callback after the first frame of remote video stream is locally rendered by SDK.
     * @param  [in] key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] info Video frame information. See VideoFrameInfo{@link #VideoFrameInfo}.
     */
    virtual void onFirstRemoteVideoFrameRendered(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }

    /** 
     * @type callback
     * @region Video Management
     * @brief Receive this callback after the first frame of remote video stream is received and decoded by SDK.
     * @param  [in] key Remote stream information. See RemoteStreamKey {@link #RemoteStreamKey}.
     * @param  [in] info Video frame information. See VideoFrameInfo {@link #VideoFrameInfo}.
     */
    virtual void onFirstRemoteVideoFrameDecoded(const RemoteStreamKey key, const VideoFrameInfo& info) {
        (void)key;
        (void)info;
    }

    /** 
     * @hidden
     * @deprecated since 336.1, use onUserPublishStream, onUserPublishScreen, onUserUnPublishStream and onUserUnPublishScreen instead.
     * @type callback
     * @region Media Stream Management
     * @brief Transmission state change of an video stream in the room triggers this callback. Refer to muteLocalVideo{@link #IRtcEngine#muteLocalVideo}.
     * @param  [in] uid The user who changes his/her transmission state of the video streams
     * @param  [in] mute Transmission state of the video streams. Refer to MuteState{@link #MuteState} for more details.
     */
    virtual void onUserMuteVideo(const char* uid, MuteState mute) {
        (void)uid;
        (void)mute;
    }

    /** 
     * @hidden
     * @deprecated since 325.1, use onUserStartVideoCapture instead
     * @type callback
     * @region Video management
     * @brief This event is called back when the remote user turns on/off local video capture. When the remote user calls EnableLocalVideo, other users will trigger this callback.
     * @param [in] uid User ID, which prompts which user's video stream. Whether the local video feature is enabled. <br>
     * @param [in] enabled Whether to enable local video function.  <br>
     *       + True: This user has enabled the local video function. When enabled, other users can receive the user's video stream. <br>
     *       + false: This user has turned off the video function. After closing, the user can still receive video streams from other users, but other users cannot receive video streams from the user. <br>
     * @notes There are other users who have enabled/disabled the local video feature
     *       + This API is deprecate, please use onUserStartVideoCapture{@link #IRtcEngineEventHandler#onUserStartVideoCapture} and onUserStopVideoCapture{@link #IRtcEngineEventHandler#onUserStopVideoCapture} instead. <br>
     */
    virtual void onUserEnableLocalVideo(const char* uid, bool enabled) {
        (void)uid;
        (void)enabled;
    }

    /** 
     * @type callback
     * @region Video event callback
     * @brief UThe remote clients in the room will be informed of the state change via this callback after the visible user starts video capture by calling startVideoCapture{@link #IRtcEngine#startVideoCapture}.
     * @param  [in] user_id The user who starts the internal video capture
     */
    virtual void onUserStartVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Video event callback
     * @brief The remote clients in the room will be informed of the state change via  this callback after the visible user stops video capture by calling stopVideoCapture{@link #IRtcEngine#stopVideoCapture}.
     * @param  [in] user_id The user who stops the internal video capture
     */
    virtual void onUserStopVideoCapture(const char* user_id) {
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief When the state of the local audio changes, the callback notifies the current local audio state.
     * @param  [in] state The state of the local audio device, see: LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param  [in] error Error code when the local audio state changes, see: LocalAudioStreamError{@link #LocalAudioStreamError}
     */
    virtual void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error) {
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief When the state of the audio stream from the remote user subscribes to changes, this callback will be received to understand the current state of the remote audio stream.
     * @param  [in] key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param  [in] state Remote audio stream state. See RemoteAudioState{@link #RemoteAudioState}
     * @param  [in] reason For remote audio stream state change. See RemoteAudioStateChangeReason{@link #RemoteAudioStateChangeReason}
     */
    virtual void onRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /** 
     * @type callback
     * @region video management [in]
     * @brief Receive this event when the state of the local video stream changes.
     * @param [in] index Index audio/video properties. See StreamIndex{@link #StreamIndex}
     * @param [in] state Local video stream status. See LocalVideoStreamState{@link #LocalVideoStreamState}
     * @param [in] error Error code when local video status changes. See LocalVideoStreamError{@link #LocalVideoStreamError}
     */
    virtual void onLocalVideoStateChanged(StreamIndex index, LocalVideoStreamState state, LocalVideoStreamError error) {
        (void)index;
        (void)state;
        (void)error;
    }


    /** 
     * @type callback
     * @region Video Management
     * @brief When the state of a remote video stream changes, users in the room who subscribe to this stream receive the event.
     * @param  [in] key Information about the remote video stream, room, user ID, stream attributes, etc. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] state The remote video stream status. See RemoteVideoState{@link #RemoteVideoState}.
     * @param  [in] reason For the remote video stream state change. See RemoteVideoStateChangeReason{@link #RemoteVideoStateChangeReason}.
     */
    virtual void onRemoteVideoStateChanged(
            RemoteStreamKey key, RemoteVideoState state, RemoteVideoStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }


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

    /** 
     * @type callback
     * @region Room management
     * @brief Audio first frame sending status change callback
     * @param  [in] user Local user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region Room management
     * @brief Video first frame sending status change callback
     * @param  [in] user Local user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region room management
     * @brief Screen sharing streaming video first frame sending status change callback
     * @param  [in] user Local user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onScreenVideoFrameSendStateChanged(const RtcUser& user, FirstFrameSendState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region  room management
     * @brief  Audio first frame playback state change callback
     * @param  [in] user Remote user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame playback status. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onAudioFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region  room management
     * @brief  Video first frame playback state change callback
     * @param  [in] user Remote user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame playback state. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
    }

    /** 
     * @type callback
     * @region room management
     * @brief Screen sharing streaming video first frame playback state change callback
     * @param  [in] user Remote user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame playback state. See FirstFramePlayState{@link #FirstFramePlayState}
     */
    virtual void onScreenVideoFramePlayStateChanged(const RtcUser& user, FirstFramePlayState state) {
        (void)user;
        (void)state;
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

    /** 
     * @type callback
     * @brief Callback of the result of publishing the public stream<br>
     *        You will be informed of the result of publishing the public stream by this callback after calling startPushPublicStream{@link #IRtcEngine#startPushPublicStream}. 
     * @param [in] public_streamid ID of the public stream
     * @param [in] errorCode Code for the result of publishing the public stream<br>
     *        `200`: Success
     */
    virtual void onPushPublicStreamResult(const char* public_streamid, int errorCode) {
        (void)public_streamid;
        (void)errorCode;
    }
    /** 
     * @type callback
     * @region Network Management
     * @brief Callback about the call test result.
     * @param [in] result Test result, see EchoTestResult{@link #EchoTestResult}.
     * @notes The timing when this callback will be triggered is as follows:  <br>
     *        + A device-related error occured during the test；  <br>
     *        + After a successful test；  <br>
     *        + After stopping the test, provided that the audio/video playback was not received during the test due to non-device reasons.
     */
    virtual void onEchoTestResult(EchoTestResult result) {
        (void)result;
    };
    
    /** 
     * @type callback
     * @region Multi-Room
     * @brief Stream publisher will receive this callback when the A/V synchronization state changes after setMultiDeviceAVSync{@link #IRTCRoom#setMultiDeviceAVSync} is called.
     * @param state A/V synchronization state, see AVSyncState{@link #AVSyncState}.
     */
    virtual void onAVSyncStateChange(AVSyncState state) {
        (void)state;
    }
    /** 
     * @type callback
     * @brief Receives the callback when you call startCloudProxy{@link #IRtcEngine#startCloudProxy}} to start cloud proxy, and the SDK connects the proxy server successfully.
     * @param [in] interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
     */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }


};

} // namespace bytertc

#endif // BYTE_RTC_EVENT_HANDLER_H__
