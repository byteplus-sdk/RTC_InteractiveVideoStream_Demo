/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Event Handler Lite
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type callback
 * @brief  Audio engine event callback interface
 */
class IRTCAudioEventHandler {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCAudioEventHandler() {}
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
    virtual void onAudioMixingStateChanged(int mix_id, bytertc::AudioMixingState state,
            bytertc::AudioMixingError error) {
        (void)mix_id;
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region Audio Mixing
     * @brief Callback for playback progress of mixed audio files
     * @param [in] mix_id Mixing ID  <br>
     * @param [in] progress The current playback progress (ms) of the mixed audio file
     * @notes After calling setAudioMixingProgressInterval{@link #IAudioMixingManager#setAudioMixingProgressInterval} to set the time interval to a value greater than 0, or calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to set the time interval in AudioMixingConfig{@link #AudioMixingConfig} to a value greater than 0, the SDK will trigger the callback according to the set time interval.
     */
    virtual void onAudioMixingPlayingProgress(int mix_id, int64_t progress) {
        (void)mix_id;
        (void)progress;
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
     * @type callback
     * @region Engine Management
     * @brief Callback on create room failure.
     * @param room_id  Room ID.
     * @param error_code Create room error code. See ErrorCode{@link #ErrorCode} for specific indications.
     */
    virtual void onCreateRoomStateChanged(const char* room_id, int error_code) {
        (void)room_id;
        (void)error_code;
    }

    /** 
     * @hidden (macOS, Windows)
     * @type callback
     * @region Audio event callback
     * @brief Audio playback The event is called back when the device changes.
     * @param  [in] device Changed audio playback device. See AudioRoute{@link #AudioRoute}. <br>
     */
    virtual void onAudioRouteChanged(AudioRoute route) {
        (void)route;
    }

    /** 
     * @type callback
     * @region  engine management
     * @brief SDK  connection state change callback with signaling server. Triggered when the connection state changes.
     * @param  [in] state The current connection status between the SDK and the signaling server. See ConnectionState{@link #ConnectionState}
     */
    virtual void onConnectionStateChanged(bytertc::ConnectionState state) {
        (void)state;
    }

    /** 
     * @type callback
     * @region Engine management
     * @brief SDK Current network connection type change callback. Callbacks the event when the current network connection type of the SDK changes.
     * @param  [in] type <br>
     *        SDK The current network connection type, see: NetworkType{@link #NetworkType}.
     */
    virtual void onNetworkTypeChanged(bytertc::NetworkType type) {
        (void)type;
    }

    /** 
     * @type callback
     * @region Engine management
     * @brief Audio device state callback, returns the state of audio capture and audio playback devices.
     * @param [in] device_id Device ID
     * @param [in] device_type Device type. See RTCAudioDeviceType{@link #RTCAudioDeviceType}.
     * @param [in] device_state Device state. See MediaDeviceState{@link #MediaDeviceState}.
     * @param [in] device_error Device error. See MediaDeviceError{@link #MediaDeviceError}.
     */
    virtual void onAudioDeviceStateChanged(const char* device_id, bytertc::RTCAudioDeviceType device_type,
            bytertc::MediaDeviceState device_state, bytertc::MediaDeviceError device_error) {
        (void)device_id;
        (void)device_type;
        (void)device_state;
        (void)device_error;
    }

    /** 
     * @type callback
     * @region Engine Management
     * @brief Audio device warning callback. The media devices includes audio capture devices and audio rendering devices.
     * @param [in] device_id Device ID
     * @param [in] device_type See RTCAudioDeviceType{@link #RTCAudioDeviceType}
     * @param [in] device_warning See MediaDeviceWarning{@link #MediaDeviceWarning}
     */
    virtual void onAudioDeviceWarning(const char* device_id, bytertc::RTCAudioDeviceType device_type,
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
        (void)stats;
    }

    /** 
     * @type callback
     * @region Proxy callback
     * @brief HTTP Receive the callback when the proxy connection state changes.
     * @param  [in] state The current HTTP proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpProxyState(int state) {
        (void)state;
    }

    /** 
     * @type callback
     * @region Proxy callback
     * @brief HTTPS Receive the callback when the proxy connection state changes.
     * @param   [out] State the current HTTPS proxy connection status. See HttpProxyState{@link #HttpProxyState}
     */
    virtual void onHttpsProxyState(int state) {
        (void)state;
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
    virtual void onSocks5ProxyState(int state, const char* cmd, const char* proxy_address,
            const char* local_address, const char* remote_address) {
        (void)state;
        (void)cmd;
        (void)proxy_address;
        (void)local_address;
        (void)remote_address;
    }

    /** 
     * @type callback
     * @region Local recording
     * @brief Get a callback of the local recording status.   <br>
     *         The callback is triggered by startFileRecording{@link #IRTCAudio#startFileRecording} or stopFileRecording{@link #IRTCAudio#stopFileRecording}.
     * @param  [out] State the recording status. See RecordingState{@link #RecordingState}
     * @param  [out] Error_code recording error code. See RecordingErrorCode{@link #RecordingErrorCode}
     * @param  [out] Info For more information about the recorded file. See RecordingInfo {@link # RecordingInfo}
     */
    virtual void onRecordingStateUpdate(RecordingState state, RecordingErrorCode error_code, RecordingInfo info) {
        (void)state;
        (void)error_code;
        (void)info;
    }

    /** 
     * @type callback
     * @region Local recording
     * @brief Local recording progress callback.   <br>
     *        This callback is triggered by startFileRecording{@link #IRTCAudio#startFileRecording}. When the recording state is normal, the system will prompt the recording progress through this callback every second.
     * @param [out] Process the recording progress. See RecordingProgress{@link #RecordingProgress}
     * @param [out] Info For more information about the recorded file. See RecordingInfo{@link #RecordingInfo}
     */
    virtual void onRecordingProgressUpdate(RecordingProgress process, RecordingInfo info) {
        (void)process;
        (void)info;
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
     *         The time taken from the call to the login{@link #IRTCAudio#login} interface to return the result is <br>
     *         In ms. This callback is received after
     * @notes login{@link #IRTCAudio#login} is called. login{@link #IRTCAudio#login}
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
     * @notes After calling logout{@link #IRTCAudio#logout}, you will receive this callback.
     */
    virtual void onLogout() {}

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Set the return result of the application server parameter
     * @param  [in] error <br>
     *        Set the result <br>
     *         + Return 200, set successfully <br>
     *         + Return other, set failed
     * @notes Receive this callback after calling setServerParams{@link #IRTCAudio#setServerParams}.
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
     * @notes You must first call getPeerOnlineStatus{@link #IRTCAudio#getPeerOnlineStatus} to receive this callback.
     */
    virtual void onGetPeerOnlineStatus(const char* peer_user_id, int status) {
        (void)peer_user_id;
        (void)status;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Receive this callback when you receive a text message from an out-of-room user calling sendUserMessageOutsideRoom{@link #IRTCAudio#sendUserMessageOutsideRoom}
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
     * @brief Receive this callback when you receive a binary message from an out-of-room user calling sendUserBinaryMessageOutsideRoom{@link #IRTCAudio#sendUserBinaryMessageOutsideRoom}
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
     * @notes Receive this callback when a message is sent by calling sendUserMessageOutsideRoom{@link #IRTCAudio#sendUserMessageOutsideRoom} or sendUserBinaryMessageOutsideRoom{@link #IRTCAudio#sendUserBinaryMessageOutsideRoom}.
     */
    virtual void onUserMessageSendResultOutsideRoom(int64_t msgid, int error) {
        (void)msgid;
        (void)error;
    }

    /** 
     * @type callback
     * @region Real-time messaging
     * @brief Callback to send a message to the application server
     * @param  [in] msgid <br>
     *        The ID of this message <br>
     *        All P2P and P2Server messages share a single ID sequence.
     * @param  [in] error <br>
     *         Message sending result <br>
     *         See UserMessageSendResult{@link #UserMessageSendResult}.
     * @notes Receive this callback when a message is sent by calling the sendServerMessage{@link #IRTCAudio#sendServerMessage} or sendServerBinaryMessage{@link #IRTCAudio#sendServerBinaryMessage} interface.
     */
    virtual void onServerMessageSendResult(int64_t msgid, int error, const bytertc::ServerACKMsg& msg) {
        (void)msgid;
        (void)error;
        (void)msg;
    }

     /** 
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRTCAudio#enableAudioPropertiesReport}, you will periodically receive this callback for the information about the subscribed remote audio streams. <br>
      *        The remote audio streams includes the microphone audio and screen audio collected using the RTC SDK internal mechanism/custom mechanism.
      * @param [in] audio_properties_infos See RemoteAudioPropertiesInfo{@link #RemoteAudioPropertiesInfo}.
      * @param [in] audio_properties_info_number The length of `audio_properties_infos`
      * @param [in] total_remote_volume The total volume of all the subscribed remote streams. The range is [0,255]. <br>
      *        + [0,25] Is close to silent; <br>
      *        + [25,75] Is low volume; <br>
      *        + [76,204] Is medium volume; <br>
      *        + [205,255] Is high volume. <br>
      */
    virtual void onRemoteAudioPropertiesReport(const RemoteAudioPropertiesInfo* audio_properties_infos,
            int audio_properties_info_number, int total_remote_volume) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
        (void)total_remote_volume;
    }

     /** 
      * @type callback
      * @region Audio Management
      * @brief After calling enableAudioPropertiesReport{@link #IRTCAudio#enableAudioPropertiesReport}, you will periodically receive this callback for the information about local audio. <br>
      *        Local audio includes the microphone audio and the screen audio captured using RTC SDK internal mechanisms.
      * @param [in] audio_properties_infos See LocalAudioPropertiesInfo{@link #LocalAudioPropertiesInfo}.
      * @param [in] audio_properties_info_number The length of `audio_properties_infos`
      */
    virtual void onLocalAudioPropertiesReport(const LocalAudioPropertiesInfo * audio_properties_infos,
            int audio_properties_info_number) {
        (void)audio_properties_infos;
        (void)audio_properties_info_number;
    }

    /** 
     * @type api
     * @region audio management
     * @brief Audio stream synchronization information callback. You can use this callback to receive audio stream synchronization information sent remotely after the remote user calls sendStreamSyncInfo{@link #IRTCAudio#sendStreamSyncInfo} to send an audio stream synchronization message. <br>
     * @param  [in] stream_key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] stream_type Media stream type. See SyncInfoStreamType{@link #SyncInfoStreamType}.
     * @param  [in] data Message content.
     * @param  [in] length Message length.
     */
    virtual void onStreamSyncInfoReceived(RemoteStreamKey stream_key, SyncInfoStreamType stream_type,
                                         const uint8_t* data, int32_t length) {
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
     * @notes Receives this callback every 2s after the call startNetworkDetection{@link #IRTCAudio#startNetworkDetection} starts probing.
     */
    virtual void onNetworkDetectionResult(NetworkDetectionLinkType type, NetworkQuality quality, int rtt,
            double lost_rate, int bitrate, int jitter) {
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
     *        1. This callback is received once when the stopNetworkDetection{@link #IRTCAudio#stopNetworkDetection} interface is called to stop probing;  <br>
     *        2. Stop detection when the first frame of remote/local audio is received;  <br>
     *        3. Stop detecting when the detection exceeds 3 minutes;  <br>
     *        4. When the probe link is disconnected for a certain period of time, the probe is stopped.
     * @param [in] reason   <br>
     *        See NetworkDetectionStopReason{@link #NetworkDetectionStopReason} for reasons of stopping probing.
     */
    virtual void onNetworkDetectionStopped(NetworkDetectionStopReason reason) {
        (void)reason;
    }


    /** 
     * @type callback
     * @region Audio event callback
     * @brief Users in the room call startAudioCapture{@link #IRTCAudio#startAudioCapture} When audio capture is
     * turned on, other users in the room will receive this callback.
     * @param  [in] user_id Remote user ID to enable audio capture
     */
    virtual void onUserStartAudioCapture(const char* room_id, const char* user_id) {
        (void)room_id;
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief When a user in the room calls stopAudioCapture{@link #IRTCAudio#stopAudioCapture} to turn off audio
     * capture, other users in the room will receive this callback.
     * @param  [in] user_id Remote user ID to turn off audio capture
     */
    virtual void onUserStopAudioCapture(const char* room_id, const char* user_id) {
        (void)room_id;
        (void)user_id;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief Receive the callback when the first audio frame is locally collected
     */

    virtual void onFirstLocalAudioFrame() {}

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
     * @type callback
     * @region Audio event callback
     * @brief When the state of the local audio changes, the callback notifies the current local audio state.
     * @param [in] state The state of the local audio device, see: LocalAudioStreamState{@link #LocalAudioStreamState}
     * @param [in] error Error code when the local audio state changes, see: LocalAudioStreamError{@link
     * #LocalAudioStreamError}
     */
    virtual void onLocalAudioStateChanged(LocalAudioStreamState state, LocalAudioStreamError error) {
        (void)state;
        (void)error;
    }

    /** 
     * @type callback
     * @region Audio event callback
     * @brief When the state of the audio stream from the remote user subscribes to changes, this callback will be
     * received to understand the current state of the remote audio stream.
     * @param [in] key Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}
     * @param [in] state Remote audio stream state. See RemoteAudioState{@link #RemoteAudioState}
     * @param [in] reason For remote audio stream state change. See RemoteAudioStateChangeReason{@link
     * #RemoteAudioStateChangeReason}
     */
    virtual void onRemoteAudioStateChanged(
            const RemoteStreamKey& key, RemoteAudioState state, RemoteAudioStateChangeReason reason) {
        (void)key;
        (void)state;
        (void)reason;
    }

    /** 
     * @type callback
     * @region Room management
     * @brief Audio first frame sending status change callback
     * @param  [in] user Local user information. See RtcUser{@link #RtcUser}
     * @param  [in] state First frame sending status. See FirstFrameSendState{@link #FirstFrameSendState}
     */
    virtual void onAudioFrameSendStateChanged(const char* room_id, const RtcUser& user, FirstFrameSendState state) {
        (void)room_id;
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
    virtual void onAudioFramePlayStateChanged(const char* room_id, const RtcUser& user, FirstFramePlayState state){
        (void)room_id;
        (void)user;
        (void)state;
    }

   /** 
    * @type callback
    * @brief Receives the callback when you call startCloudProxy{@link #IRtcEngine#startCloudProxy} to start cloud proxy, and the SDK connects the proxy server successfully.
    * @param [in] interval The interval in ms between starting cloud proxy and connects the cloud proxy server successfully.
    */
    virtual void onCloudProxyConnected(int interval) {
        (void)interval;
    }
};

}  // namespace bytertc
