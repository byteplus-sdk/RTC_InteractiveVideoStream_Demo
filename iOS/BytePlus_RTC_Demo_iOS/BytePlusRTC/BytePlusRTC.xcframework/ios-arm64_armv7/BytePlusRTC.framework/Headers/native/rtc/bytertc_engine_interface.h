/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Interface
 */

#pragma once

#ifndef BYTE_RTC_INTERFACE_H__
#define BYTE_RTC_INTERFACE_H__

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "bytertc_defines.h"
#include "bytertc_rtcvideo_interface.h"
#include "bytertc_engine_event_handler.h"
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"

namespace bytertc {

class IRTCRoomEventHandler;
/** 
 * @type api
 * @brief Engine API
 *      IRtcEngine uses IRtcEngineering EventHandler to register interface class methods to send callback notifications to applications
 */
class IRtcEngine {
public:

    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRtcEngine() {
    }
    /** 
     * @hidden
     * @deprecated since 326.1, use function joinRoom with RTCRoomConfig parameter instead
     * @type api
     * @region Room management
     * @brief Create/join a room: create a room when the room does not exist; join the room when the room exists.   <br>
     *        Users in the same room can talk to each other. <br>
     *         Repeated calls after entering the room are invalid. The user must call leaveRoom{@link #leaveRoom} to exit the current room before joining the next room. <br>
     *         Local users will receive OnRoomStateChanged{@link #IRTCRoomEventHandler#OnRoomStateChanged} callback notification after calling this method to join the room successfully, and remote users will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} callback notification. <br>
     * @param  [in] token Dynamic key for authenticating the logged-in user. <br>
     *         You need to bring Token to enter the room. When testing, you can use the console to generate temporary tokens. The official launch requires the use of the key SDK to generate and issue tokens at your server level. <br>
     * @param  [in] room_id Added room ID. <br>
     *        The room ID is a non-empty string with a length of less than 128 bytes, and the following character set ranges are supported: <br>
     *            1. 26 capital letters A~ Z. <br>
     *            2. 26 lowercase letters a~ z. <br>
     *            3. 10 numbers 0~ 9. <br>
     *            4. Underline "_", at character "@", minus sign "-". <br>
     * @param  [in] user_info User information. See UserInfo{@link #UserInfo}. <br>
     * @param  [in] profile_type Room mode. <br>
     *        You should choose the right room mode according to your business needs. <br>
     *        You must set the room mode before entering the room, and it cannot be changed after entering the room. <br>
     *         For room patterns. See RoomProfileType{@link #RoomProfileType}. <br>
     * @return   <br>
     *         + 0: Success <br>
     *         + -1: Room_id is empty, failure <br>
     *         + -2: User_info is empty, failure <br>
     * @notes   <br>
     *        + Apps with different App IDs cannot communicate with each other. <br>
     *        + Make sure that the App ID used to generate the Token is the same as the App ID used to create the engine, otherwise it will cause the join room to fail. <br>
     *        + After the user successfully joins the room, the SDK may lose connection to the server in case of poor local network conditions, and the SDK will automatically reconnect at this time. After a successful reconnection, you will receive an OnRoomStateChanged{@link #IRTCRoomEventHandler#OnRoomStateChanged} callback notification locally. <br>
     *        + In the same room with the same App ID, the user ID of each user must be unique. If two users have the same user ID, the user who entered the room later will kick the user who entered the room out of the room, and the user who entered the room will receive the onError{@link #IRtcEngineEventHandler#onError} callback notification. See ErrorCode{@link #ErrorCode} for the error type. <br>
     */
    virtual int joinRoom(
            const char* token, const char* room_id, const UserInfo& user_info, RoomProfileType profile_type) = 0;
    /** 
      * @type api
      * @region Room management
      * @brief Create or join a room: create a room when the room does not exist; join the room when the room exists.   <br>
      *        Users in the same room can talk to each other. <br>
      *         Repeated calls of the API after entering the room are invalid. The user must call leaveRoom{@link #IRTCRoom#leaveRoom} to exit the current room before joining the next room. <br>
      * @param [in] token Dynamic key for authentication of users entering the room. <br>
      *         You must use token to join the room. When debugging, you can use the temporary tokens generated on the console. For official launch, you must generate token on your application server and use the tokens to join the room.<br>
      *         Make sure that the AppID used to generate the token is the same as that used to create the engine, otherwise it will fail to join room. <br>
      * @param [in] room_id  The ID of the room to join. <br>
      *        The string matches the regular expression: `[a-zA-Z0-9_@\-]{1,128}`.
      * @param [in] user_info See UserInfo{@link #UserInfo}. <br>
      * @param [in] room_config  Sets the room mode and whether to automatically publish or subscribe to the stream. See RTCRoomConfig{@link #RTCRoomConfig}. <br>
      * @return   <br>
      *         + 0: Success. <br>
      *         + -1: Failure. There's invalid parameters in RoomID or userInfo.uid. <br>
      *         + -2: Already in the room. When calling the API call， receiving the value of 0 and not calling leaveRoom:{@link #IRTCRoom#leaveRoom},  value `-2` is returned for further API calls, regardless of whether the roomId and the userInfo are duplicated. <br>
      * @notes   <br>
      *        + In the same room with the same App ID, the user ID of each user must be unique. If two users use the same user ID, the former will be kicked out of the room by the latter and receive onError{@link #IRtcEngineEventHandler#onError}.<br>
      *        + You will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}} after joining the room successfully. <br>
      *        + When you call setUserVisibility{@link #IRTCRoom#setUserVisibility} to make yourself visible and join the room, the remote users will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}. <br>
      *        + After joining the room, you may lose connection to the server due to poor network conditions. In this case, the SDK will automatically reconnect. After reconnected, you will receive onRoomStateChanged{@link #IRTCRoomEventHandler#onRoomStateChanged}}. If you are visible in the room, the remote users will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}. <br>
      */
    virtual int joinRoom(const char* token, const char* room_id, const UserInfo& user_info, const RTCRoomConfig& room_config) = 0;

/** 
     * @hidden
     * @deprecated since 327.1, use setCaptureVolume instead
     * @type api
     * @region Audio management
     * @brief Adjust the audio acquisition volume
     * @param  [in] volume Audio acquisition volume, the value range: [0,400] <br>
     *        + 0: Mute <br>
     *        + 100: Original volume <br>
     *        + 400: Up to 4 times the original volume (with overflow protection) <br>
     * @notes  To ensure better call quality, it is recommended to set the volume value to [0,100], this interface is obsolete, please use setCaptureVolume{@link #setCaptureVolume}.
     */
    virtual void setRecordingVolume(const int volume) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Volume management
     * @brief Adjust the audio acquisition volume
     * @param  [in] index Index of the stream, whose volume needs to be adjusted. Refer to StreamIndex{@link #StreamIndex} for more details.
     * @param  [in] volume Ratio of capture volume to original volume. Ranging: [0,400]. Unit: %
     *        + 0: Mute <br>
     *        + 100: Original volume. To ensure the audio quality, we recommend [0, 100].
     *        + 400: Four times the original volume with signal-clipping protection.
     * @notes  Call this API to set the volume of the audio capture before or during the audio capture.
     */
    virtual void setCaptureVolume(StreamIndex index, int volume) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Adjust the playback volume of the mixed remote audios.
     * @param  [in] volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
     *        To ensure the audio quality, we recommend setting the volume within `100`.  <br>
     *        + 0: mute <br>
     *        + 100: original volume <br>
     *        + 400: Four times the original volume with signal-clipping protection.
     * @notes To ensure better call quality, it is recommended to set the volume value to [0,100].
     */
    virtual void setPlaybackVolume(const int volume) = 0;


    /** 
     * @hidden (Windows)
     * @type api
     * @region Audio management
     * @brief Turn on/off the earphone monitor function
     * @param  [in] mode Whether to turn on the earphone monitor function. See EarMonitor Mode {@link #EarMonitor Mode}
     */
    virtual void setEarMonitorMode(EarMonitorMode mode) = 0;

    /** 
     * @hidden (Windows)
     * @type api
     * @region Audio Management
     * @brief Set the volume of the earphone monitor
     * @param  [in] volume The volume of the earphone monitor, the value range: [0,100], the unit:%
     * @notes  <br>
     *         + Before setting the volume of the earphone monitor, you must first call SetEarMonitor Mode {@link #SetEarMonitor Mode} to turn on the earphone monitor function. <br>
     *         + The earphone monitor function is only effective when the internal audio capture function provided by the RTC SDK is used and a wired earphone is connected. <br>
     */
    virtual void setEarMonitorVolume(const int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setScreenAudioStreamIndex instead
     * @type api
     * @region Screen Sharing
     * @brief Turn on the sound card acquisition and merge the audio played by the sound card into the locally collected audio stream. <br>
     *         If you want to transfer the sound played by the sound card to a remote location (such as screen sharing and other scenes), you must turn on the sound card acquisition. In this way, the sound played by the sound card is merged into the locally collected audio stream and sent to the remote end together.
     * @notes   <br>
     *        + After turning on the sound card acquisition, you can set the corresponding volume. See setScreenAudioVolumeBeforeMixing {@link
     *  #setScreenAudioVolumeBeforeMixing} <br>
     *        + If you need to turn off the sound card acquisition. See StopMixScreenAudioToMainStream{@link #StopMixScreenAudioToMainStream}
     */
    virtual void startMixScreenAudioToMainStream() = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setScreenAudioStreamIndex instead
     * @type api
     * @region Screen Sharing
     * @brief Turn off the sound card acquisition, the audio stream played by the sound card is no longer combined into the locally collected audio stream.
     * @notes If you need to turn on the sound card acquisition, please refer to StartMixScreenAudioToMainStream{@link #StartMixScreenAudioToMainStream}
     */
    virtual void stopMixScreenAudioToMainStream() = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setCaptureVolume instead
     * @type api
     * @region screen sharing
     * @brief To adjust the local sound card acquisition volume. <br>
     *        After the local sound card acquisition is turned on, you can use this interface to adjust the acquisition volume.
     *         For information on how to turn on local sound card acquisition, refer to startMixScreenAudioToMainStream{@link #startMixScreenAudioToMainStream}.
     * @param volume The sound card collects the volume, the value range: [0,400] <br>
     *        + 0: mute <br>
     *        + 100: the original volume <br>
     *        + 400: the maximum can be 4 times the original volume (with overflow protection) <br>
     */
    virtual void setScreenAudioVolumeBeforeMixing(int volume) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Start internal audio capture. The default is off.   <br>
     *        Internal audio capture refers to: capturing audio using the built-in module.
     *        The local client will be informed via onAudioDeviceStateChanged{@link #IRtcEngineEventHandler#onAudioDeviceStateChanged} after starting audio capture by calling this API. <br>
     *        The remote clients in the room will be informed of the state change via onUserStartAudioCapture{@link #IRtcEngineEventHandler#onUserStartAudioCapture} after the visible user starts audio capture by calling this API..
     * @notes   <br>
     *        + To enable a microphone without the user's permission will trigger onWarning{@link #IRtcEngineEventHandler#onWarning}. <br>
     *        + Call stopAudioCapture{@link #stopAudioCapture} to stop the internal audio capture. Otherwise, the internal audio capture will sustain until you destroy the engine instance. <br>
     *        + Once you create the engine instance, you can start internal audio capture regardless of the audio publishing state. The audio stream will start publishing only after the audio capture starts. <br>
     *        + To switch from custom to internal audio capture, stop publishing before disabling the custom audio capture module and then call this API to enable the internal audio capture.
     */
    virtual void startAudioCapture() = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Stop internal audio capture. The default is off.   <br>
     *        Internal audio capture refers to: capturing audio using the built-in module.
     *         The local client will be informed via  onAudioDeviceStateChanged{@link #IRtcEngineEventHandler#onAudioDeviceStateChanged}  after stopping audio capture by calling this API.<br>. <br>
     *        The remote clients in the room will be informed of the state change via onUserStopAudioCapture{@link #IRtcEngineEventHandler#onUserStopAudioCapture} after the visible client stops audio capture by calling this API.<br>.
     * @notes   <br>
     *        + Call startAudioCapture{@link #startAudioCapture} to enable the internal audio capture. <br>
     *        + Without calling this API the internal audio capture will sustain until you destroy the engine instance.<br>
     */
    virtual void stopAudioCapture() = 0;

    /** 
     * @hidden (macOS, Windows, Linux)
     * @type api
     * @region  Audio management
     * @brief  Set the audio scene type.   <br>
     *        You can choose the appropriate audio scene type according to the scene where your application is located.
     *        After selecting an audio scenario, RTC automatically applies call volume/media volume based on client side audio routing and publishing subscription status. <br>
     *         Settings can take effect before and after entering the room.
     * @param  [in] scenario Audio scene type,
     *         See AudioScenarioType{@link #AudioScenarioType}
     * @notes   <br>
     *         +
     * Call volume is more suitable for calls, meetings and other scenes that require higher information accuracy. Call volume will activate the system hardware signal processing, making the call sound clearer. At this point, the volume cannot be reduced to
     * 0. <br>
     *         + Media volume is more suitable for entertainment scenes, because its sound will be more expressive. Under the media volume, the minimum volume can be reduced to 0.
     */
    virtual void setAudioScenario(AudioScenarioType scenario) = 0;

    /** 
     * @type api
     * @region Bel Sound Effect Management
     * @brief Set the sound change effect type
     * @param  [in] voice_changer The sound change effect type. See VoiceChangerType{@link #VoiceChangerType}
     * @notes   <br>
     *         + It can be set before and after entering the room. <br>
     *         + Is effective for both internally captured and custom captured audio from the RTC SDK. <br>
     *         + Only valid for mono audio. <br>
     *         + Is only valid in SDKs that include the ability of American sound effects. <br>
     *         + Is mutually exclusive with setVoiceReverbType{@link #setVoiceReverbType}, and the effects set later will override the effects set first. <br>
     */
    virtual int setVoiceChangerType(VoiceChangerType voice_changer) = 0;

    /** 
     * @type api
     * @region Bel Sound Effect Management
     * @brief Set the reverb effect type
     * @param  [in] voice_reverb The reverb effect type. See VoiceReverbType{@link #VoiceReverbType}
     * @notes   <br>
     *         + You can set it before and after entering the room. <br>
     *         + Is effective for both internally captured and custom captured audio from the RTC SDK. <br>
     *         + Only valid for mono audio. <br>
     *         + Is only valid in SDKs that include the ability of American sound effects. <br>
     *         + Is mutually exclusive with setVoiceChangerType{@link #setVoiceChangerType}, and the effects set later will override the effects set first. <br>
     */
    virtual int setVoiceReverbType(VoiceReverbType voice_reverb) = 0;

    /** 
     * @type api
     * @region audio management
     * @brief Sets the sound quality gear. You should choose the appropriate sound quality gear according to the needs of the business scenario.   <br>
     * @param  [in] audio_profile Sound quality gear. See AudioProfileType{@link #AudioProfileType}
     * @notes   <br>
     *         + This method can be called before and after entering the room; <br>
     *         + Support dynamic switching of sound quality gear during a call.
     */
    virtual void setAudioProfile(AudioProfileType audio_profile) = 0;

    /** 
     * @hidden
     * @deprecated since 336.1, use unpublishStream and publishStream instead.
     * @type api
     * @region Media stream management
     * @brief Enable/ Disable the transmission of the local audio stream.   <br>
     *        Remote users in the room will be informed via onUserMuteAudio{@link #IRTCRoomEventHandler#onUserMuteAudio} after the visible user changes the transmission state of the audio streams by calling this API.
     * @param  [in] mute_state An identifier denoting whether the local audio stream is sending. Refer to MuteState{@link #MuteState} for more details.
     * @notes <br>
     *        + Calling this API toggles the transmission state of the local audio streams instead of the capture state.
     *        + You can enable audio transmission regardless of the audio capture state. Enable the transmission before capture, thus the audio stream can be sent once the capture starts.
     */
    virtual void muteLocalAudio(MuteState mute_state) = 0;
    /** 
      * @hidden
      * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
      * @type api
      * @region Custom Audio Capture and Rendering
      * @brief Enables custom audio capture and rendering.
      * @param [in] recording_format See AudioFormat{@link #AudioFormat}
      * @param [in] playback_format See AudioFormat{@link #AudioFormat}
      * @notes   <br>
      *       + You must call this API before joining the room.<br>
      *       + The state of enabling custom audio capture and rendering is still valid after leaving the room, until disableExternalAudioDevice{@link #IRtcEngine#disableExternalAudioDevice} is called to disable custom audio capture and rendering. <br>
      *       + You must enable both custom audio capture and custom audio rendering, or enable both internal audio capture and internal audio rendering. By default, internal audio capture and rendering are used. <br>
      *       + After enabling custom audio capture and rendering, call pushExternalAudioFrame{@link #IRtcEngine#pushExternalAudioFrame} to push custom captured audio frames to the RTC SDK for transmission; and call pullExternalAudioFrame{@link #IRtcEngine#pullExternalAudioFrame} to get remote audio frames. <br>
      *       + If calling the API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. <br>
      *       + To switch to internal capture when custom capture is enabled, you must call disableExternalAudioDevice{@link #IRtcEngine#disableExternalAudioDevice} to disable custom capture, and then call startAudioCapture{@link #IRtcEngine#startAudioCapture} to manually enable internal capture.
      */
    virtual void enableExternalAudioDevice(const AudioFormat &recording_format, const AudioFormat &playback_format) = 0;

     /** 
      * @hidden
      * @deprecated since 340.1, use SetAudioSourceType and SetAudioRenderType instead.
      * @type api
      * @region Custom Audio Capture Rendering
      * @brief Disables custom audio capture and rendering.
      * @notes   <br>
      *       + To switch to internal capture when custom capture is enabled, you must call this API and then call startAudioCapture{@link #IRtcEngine#startAudioCapture}. <br>
      *       + To enable custom audio capture and rendering, call enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice}.
      */
    virtual void disableExternalAudioDevice() = 0;

    /** 
      * @hidden
      * @deprecated since 340.1, use PushExternalAudioFrame with IAudioFrame parameter instead.
      * @type api
      * @region Custom Audio Capture and Rendering
      * @brief Push custom captured audio data to the RTC SDK.
      * @param [in] data PCM data. The audio sampling format must be S16. The data format in the audio buffer must be PCM, and its capacity size should be `audioFrame.samples × audioFrame.channel × 2`.
      * @param [in] samples The samples (number of audio sampling points) of a single push should be `audioFrame.sample Rate/100`. For example, when the sampling rate is set to 48000, data of 480 sampling points should be pushed each time. <br>
      * @return <br>
      *         + 0: Success <br>
      *         + < 0: Failure <br>
      * @notes   <br>
      *        + Before pushing external audio data, you must call enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice} to enable custom audio capture. <br>
      *        + You must push custom captured audio data every 10 milliseconds.<br>
      *        + This API runs in a user-level thread. If other processes are running at the same time, this process will be interrupted. 
      */
    virtual bool pushExternalAudioFrame(int8_t* data, int samples) = 0;

    /** 
     * @hidden
     * @deprecated since 340.1, use PullExternalAudioFrame with IAudioFrame parameter instead.
     * @type api
     * @region  custom audio acquisition rendering
     * @brief  Pull remote audio data. After you enable custom audio capture rendering with enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice}
     * , You can use this method to pull remote audio data.
     * @param [out] Data
     *        Pcm data, the memory size should be samples × playback_format.channel × 2.
     * @param [in] samples
     *         The number of sampling points should be
     * Playback_format.sample _rate/100 set in enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice}. When the sample rate is set to 48000, 480 sample points should be pulled each time
     * @return   Method call result   <br>
     *         + True: Success. <br>
     *         + False: failure <br>
     * @notes   <br>
     *        + Must be pcm data, pull interval is 10ms, audio sampling format is s16.  <br>
     *        + This function runs in the user calling thread and is a synchronous function <br>
     */
    virtual bool pullExternalAudioFrame(int8_t* data, int samples) = 0;

    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief  Switch the audio capture type.
     * @param [in] type Audio input source type. See AudioSourceType{@link #AudioSourceType} <br>
     *            Use internal audio capture by default. The audio capture type and the audio render type may be different from each other.
     * @return   Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @notes   <br>
     *       + You can call this API before or after joining the room.<br>
     *       + If you call this API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. You must call pushExternalAudioFrame{@link #IRtcEngine#pushExternalAudioFrame} to push custom captured audio data to RTC SDK for transmission. <br>
     *       + If you call this API to switch from custom capture to internal capture, you must then call startAudioCapture{@link #IRtcEngine#startAudioCapture} to enable internal capture. <br>
     */
    virtual int setAudioSourceType (AudioSourceType type) = 0;

    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief  Switch the audio render type.
     * @param [in] type Audio output source type. See AudioRenderType{@link #AudioRenderType}. <br>
     *             Use internal audio render by default. The audio capture type and the audio render type may be different from each other.
     * @return   Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @notes   <br>
     *       + You can call this API before or after joining the room. <br>
     *       + After calling this API to enable custom audio rendering, call pullExternalAudioFrame{@link #IRtcEngine#pullExternalAudioFrame} for audio data.
     */
    virtual int setAudioRenderType (AudioRenderType type) = 0;

    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief Push custom captured audio data to the RTC SDK.
     * @param [in] audioFrame. The audio data of 10 ms. See IAudioFrame{@link #IAudioFrame}。
     * @return <br>
     *         + 0: Success <br>
     *         + < 0: Failure <br>
     * @notes   <br>
     *        + Before calling this API, you must call enableExternalAudioDevice{@link #IRtcEngine#enableExternalAudioDevice} to enable custom audio capture. <br>
     *        + You must push custom captured audio data every 10 ms. <br>
     *        + This API runs in the user-level thread. If other processes are running at the same time, this process will be interrupted.
     */
    virtual bool pushExternalAudioFrame(IAudioFrame* audioFrame) = 0;

    /** 
     * @region  custom audio acquisition rendering
     * @brief  Pull remote audio data. You can use the data for audio processing or custom rendering.
     * @param [out] audioFrame The obtained audio data of 10 ms. See IAudioFrame{@link #IAudioFrame}。
     * @return   Method call result:   <br>
     *         + True: Success. <br>
     *         + False: failure <br>
     * @notes   <br>
     *        + Before pulling the audio data, call setAudioRenderType{@link #IRtcEngine#setAudioRenderType} to enable custom rendering. <br>
     *        + Pull the audio data every 10 ms. <br>
     *        + This function runs in the user calling thread and is a synchronous function. <br>
     */
    virtual bool pullExternalAudioFrame(IAudioFrame* audioFrame) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To start playing music files and mixing.
     * @param  [in] file_path <br>
     *         Specifies the absolute path of the local file that needs to be mixed. Supported audio file formats are: mp3, aac, m4a, 3gp, wav.
     * @param  [in] loopback <br>
     *        + True: Only the mixed or replaced audio stream can be heard locally. <br>
     *        + False: Both local and opposite parties can hear the mixed or replaced audio stream
     * @param  [in] replace <br>
     *        + True: Only push the set local audio file, not transfer the audio collected by the microphone. <br>
     *        + False: The audio file content will be mixed with the audio stream collected by the microphone
     * @param  [in] cycle Specify the number of times the audio file is cycled. <br>
     *        + > 0: The number of cycles. <br>
     *        + -1: Infinite loop
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *       + This method specifies that the audio stream captured by the local and microphone is mixed or replaced. Replacement refers to replacing the audio stream captured by the microphone with an audio file. <br>
     *       + This method can choose whether to let the other party hear the locally played audio and specify the number of times to loop it.
     * When this method is called to play the music file and the mix ends, the app receives an onAudioMixingStateChanged{@link #IRtcEngineEventHandler#onAudioMixingStateChanged} callback. <br>
     *       + After you start playing the music file and mixing, you can call the stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} method to stop playing the music file. <br>
     *       + This method mixes external files of data sources, and the supported file formats are: mp3, aac, m4a, 3gp, wav; and setAudioPlayoutMixStream {@link
     *  #setAudioPlayoutMixStream} The data source of the mix is external cache and the audio format is PCM; these two mixing methods can coexist. <br>
     *       + A single room only supports the playback of all music files. After multiple calls to this function, only the last call will take effect. <br>
     *       + Please call this method inside the room.
     */
    virtual int startAudioMixing(const char* file_path, bool loopback, bool replace, int cycle) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Stop playing music files and mixes
     * @notes   <br>
     *       + Call the startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * After the method starts playing music files and mixes, call this method to stop playing music files and mixes. <br>
     *       + Please call this method inside the room.
     */
    virtual void stopAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Pause playing music files
     * @return   <br>
     *         + 0: Success <br>
     *         + < 0: Failure
     * @notes   <br>
     *       + Call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method to start playing music After the file and mixing, you can call this method to pause playing the music file. <br>
     *       + After calling this method to pause playing the music file, you can call the resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} method to resume playing. <br>
     *       + Please call this method inside the room.
     */
    virtual int pauseAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  Resume playing music files
     * @return   <br>
     *        + 0: success <br>
     *        + < 0: failure
     * @notes   <br>
     *       + Call pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} method after pausing playing music files , you can resume playing by calling this method. <br>
     *       + Please call this method in the room
     */
    virtual int resumeAudioMixing() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To adjust the file volume of music files. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
     * @param  [in] volume Music file playback volume range is 0~ 400. <br>
     *        + 0: mute <br>
     *        + 100: original volume <br>
     *        + 400: maximum adjustable volume (with overflow protection)
     * @return   <br>
     *        + 0: success <br>
     *        + < 0: failure
     * @notes   <br>
     *       + Call this method can be adjusted at the same time is local And remote playback volume. adjustAudioMixingPlayoutVolume {@link
     *  #adjustAudioMixingPlayoutVolume} Can be used to adjust the local volume only, and adjustAudioMixingPublishVolume {@link
     *  #adjustAudioMixingPublishVolume} Can be used to adjust the remote volume only. <br>
     *       + The volume adjustment effect of this method on adjustAudioMixingPlayoutVolume{@link #adjustAudioMixingPlayoutVolume} and
     * adjustAudioMixingPublishVolume{@link #adjustAudioMixingPublishVolume} is a product relationship. <br>
     *       + Please call this method inside the room.
     */
    virtual int adjustAudioMixingVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To adjust the local playback volume of music files. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
     * @param  [in] volume Music file playback volume range is 0~ 400. <br>
     *        + 0: mute <br>
     *        + 100: original volume <br>
     *        + 400: maximum adjustable volume (with overflow protection)
     * @return   <br>
     *        + 0: success <br>
     *        + < 0: failure
     * @notes   <br>
     *       + Call this method to adjust the mixed The volume at which the music file is played locally. If you need to adjust the local and remote playback volume at the same time, you can use the
     * adjustAudioMixingVolume{@link #adjustAudioMixingVolume} method. <br>
     *       + Please call this method inside the room.
     */
    virtual int adjustAudioMixingPlayoutVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To adjust the remote playback volume of the music file. In order to ensure better sound quality, it is recommended to set the volume value to [0,100].
     * @param  [in] volume Music file playback volume range is 0~ 400. <br>
     *        + 0: mute <br>
     *        + 100: original volume <br>
     *        + 400: maximum adjustable volume (with overflow protection)
     * @return   <br>
     *        + 0: success <br>
     *        + < 0: failure
     * @notes   <br>
     *       + This method adjusts the music file of the mix in The volume of the remote playback. If you need to adjust the local and remote playback volume at the same time, you can use the
     * adjustAudioMixingVolume{@link #adjustAudioMixingVolume} method. <br>
     *       + Please call this method inside the room.
     */
    virtual int adjustAudioMixingPublishVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mix
     * @brief  Get music file duration
     * @return   <br>
     *        + > 0: Success, music file duration, in milliseconds. <br>
     *        + < 0: Failed
     * @notes  <br>
     *       Please call this method inside the room.
     */
    virtual int getAudioMixingDuration() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  Get the music file playback progress
     * @return   <br>
     *        + > 0: Success, the music file playback progress, in milliseconds. <br>
     *        + < 0: Failed
     * @notes  <br>
     *       Please call this method inside the room.
     */
    virtual int getAudioMixingCurrentPosition() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To set the playback location of the audio file
     * @param  [in] pos
     *         Integer. Progress bar position in milliseconds.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *       This method can set the playback location of the audio file, so that you can play the music file from the specified location according to the actual situation, without playing a music file completely from beginning to end.
     */
    virtual int setAudioMixingPosition(int pos) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Get the file volume of the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness. Make sure the sound_id here is the same as the sound_id set by startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * .
     * @return   <br>
     *        + > 0: Success, file volume, volume range 0~ 400. <br>
     *        + < 0: Failed
     * @notes   <br>
     *       Please call this method inside the room.
     */
    virtual int getEffectVolume(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Adjust the file volume of the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness. Make sure the sound_id here is the same as the sound_id set by startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     * .
     * @param  [in] volume <br>
     *        Music file playback volume range is 0~ 400. Default 100 is the original file volume
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes
     *        + This method adjusts the volume of audio files played locally and remotely. <br>
     *        + Please call this method inside the room.
     */
    virtual int setVolumeOfEffect(int sound_id, int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To start playing the specified sound effect file. In this method, you can set the number of times the sound effect file is played, the volume, and whether the remote user can hear the sound effect.
     * @param  [in] sound_id <br>
     *         Sound ID, application caller maintenance, please ensure uniqueness. If the sound effect has been loaded into memory through preloadEffect{@link #preloadEffect}
     * , Make sure that the sound_id here is the same as the sound_id set by preloadEffect{@link #preloadEffect}.
     * @param  [in] file_path <br>
     *         Specify the audio file name and file path name that need to be mixed. The following audio formats are supported: mp3, aac, m4a, 3gp, wav
     * @param  [in] loopback <br>
     *        + True: Only the sound effect can be heard locally. <br>
     *        + False: The sound effect can be heard by both local and remote users.
     * @param  cycle  Specifies the number of times the audio file is cycled. <br>
     *        + > 0: The number of cycles. <br>
     *        + -1: Infinite loop until it stops after calling stopEffect{@link #stopEffect} or stopAllEffects{@link #stopAllEffects}.
     * @param  [in] volume <br>
     *        The sound file playback volume range is 0~ 400. The default is 100 for the original file volume.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *       + After calling this method to play the sound effect, the application will receive an onAudioMixingStateChanged{@link #IRtcEngineEventHandler#onAudioMixingStateChanged} callback. <br>
     *       + This method can be called many times by passing in the sound_id and
     * File_path of different sound files to realize simultaneous playback of multiple sound files and sound effect superposition. <br>
     *       + You can call the stopEffect{@link #stopEffect} method to stop playing the specified sound effect file. <br>
     *       + Please call this method inside the room.
     */
    virtual int playEffect(int sound_id, const char* file_path, bool loopback, int cycle, int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief  To preload the specified sound effect file.
     * @param  [in] sound_id <br>
     *         Sound ID, application caller maintenance, please ensure uniqueness.
     * @param  [in] file_path <br>
     *         Specify the audio file name and file path name that need to be mixed. The following audio formats are supported: mp3, aac, m4a, 3gp, wav.
     * @return   <br>
     *         + 0: Success <br>
     *         + < 0: Failure
     * @notes   <br>
     *        +
     * Call this method to preload and play the specified sound effect file. The preload operation can be completed before entering the room (all mixing-related interfaces, if not marked, can be called in the room when not entering the room). If the sound file is very long, the loading operation may take a long time. It is recommended that application developers put the preloading operation in a child thread.
     *  <br>
     *        + This method only preloads to play the specified sound effect file, and only calls the startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     *  Method to start playing the specified sound effect file. <br>
     *        + This method preloads the specified sound effect file, which can be unloaded via unloadEffect{@link #unloadEffect}.
     */
    virtual int preloadEffect(int sound_id, const char* file_path) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Uninstall the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *        + Call this method to uninstall the specified sound file. <br>
     *        + If the sound file is not unloaded when the stopEffect{@link #stopEffect} method is called, the SDK will automatically call the method to uninstall the sound file.
     */
    virtual int unloadEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Stop playing the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness. If the sound effect has been loaded into memory through preloadEffect{@link #preloadEffect}
     * , Make sure that the sound_id here is the same as the sound_id set by preloadEffect{@link #preloadEffect}.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *        + Call this method to stop playing the specified sound file. <br>
     *        + unloadEffect{@link #unloadEffect} is actively called inside this method to uninstall the specified sound effect text.
     */
    virtual int stopEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Pause playing the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failed
     * @notes   <br>
     *       Call this method to pause the playback of the specified sound effect file. You can call the resumeEffect{@link #resumeEffect} method to resume playback.
     */
    virtual int pauseEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Resume playback of the specified sound file
     * @param  [in] sound_id <br>
     *        Sound ID, apply caller maintenance, please ensure uniqueness.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes   <br>
     *       + After calling the pauseEffect{@link #pauseEffect} method to pause playing the specified sound effect file, you can resume playing through this method. <br>
     *       + After calling the pauseAllEffects{@link #pauseAllEffects}
     *  Method to pause the playback of all sound effects files, you can also use this method to resume the playback of individual sound effects files.
     */
    virtual int resumeEffect(int sound_id) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Adjust the file volume of all sound files
     * @param  [in] volume <br>
     *        Music file playback volume range is 0~ 400. The default is 100 for the original file volume.
     * @notes   <br>
     *       + This method adjusts the volume of all sound files of the mix to be played locally and remotely. <br>
     *       + Please call this method inside the room.
     */
    virtual void setEffectsVolume(int volume) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Stop playing all sound files
     * @notes   <br>
     *      This method stops playing all sound files.
     */
    virtual void stopAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  To pause the playback of all sound files.
     * @notes   <br>
     *       Call this method to pause the playback of all sound effects files, and you can call the resumeAllEffects{@link #resumeAllEffects} method to resume playback.
     */
    virtual void pauseAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Resume playback of all sound files
     * @notes   <br>
     *      + Call this method to resume playback of all sound files. After pauseAllEffects{@link #pauseAllEffects}
     *  Is called to pause playback of all sound files, this method can be called to resume playback of all sound files. <br>
     *      + After calling the pauseEffect{@link #pauseEffect}
     *  Method to pause the playback of a single specified sound effect file, you can also call this method to resume playback, but the efficiency is too low to recommend this use.
     */
    virtual void resumeAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mix
     * @brief  Uninstall all sound files
     * @notes   <br>
     *       + Call this method to uninstall all sound files. If the sound files were not uninstalled when the engine was destroyed, the SDK will automatically call this method to uninstall all sound files.
     *  <br>
     *       + Call leaveRoom{@link #leaveRoom}
     *  After leaving the room, this method will not be called automatically to uninstall all sound files. If you need to uninstall all sound files after leaving the room, you need the app to call this method actively.
     */
    virtual void unloadAllEffects() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region  mixing
     * @brief  Start/stop external audio stream mixing,  and set the mixing data format
     * @param  [in] enable <br>
     *        + True: Enable external audio stream mixing. <br>
     *        + False: Stop mixing external audio streams.
     * @param  [in] sample_rate <br>
     *         Audio sample rate in HZ. Currently supported sampling rates are: 8000HZ, 16000HZ, 32000HZ, 44100HZ, 48000HZ.
     * @param  [in] channel_num <br>
     *         Number of audio channels. Currently supports single channel (1), dual channel (2)
     * @notes   <br>
     *       + Call this method to set the PCM format of the external audio mix, that is, the
     * Audio_frame audio data format of pushAudioMixingStreamData{@link #pushAudioMixingStreamData}. <br>
     *       + Call the data source external cache of the method mix, and the audio format is PCM; startAudioMixing{@link #IAudioMixingManager#startAudioMixing}
     *  The method mixes the data source external file, and the supported file formats are: mp3, aac, m4a, 3gp, wav. These two mixing methods can coexist. <br>
     *       + Enable is false to stop the external audio stream mixing. Or when the engine is released, the SDK will stop mixing internally. <br>
     *       + The external audio stream mix initiated by this method does not support volume adjustment, pause, pause and resume operations.
     */
    virtual void setAudioPlayoutMixStream(bool enable, int sample_rate, int channel_num) = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Get the SDK current buffered data
     * @return   <br>
     *        + > 0: Success, the number of buffered audio sample points. <br>
     *        + 0: Failure
     * @notes
     *       Call this method to obtain the amount of cached data in real time, and adjust the data push rhythm based on this data to avoid out of memory
     */
    virtual int getAudioMixingStreamCachedFrameNum() = 0;

    /** 
     * @hidden
     * @deprecated since 325.1, use IAudioMixingManager instead
     * @type api
     * @region Audio Mixing
     * @brief Push the audio data of the mix to the SDK
     * @param  [in] audio_frame <br>
     *        PCM audio data, and its format is consistent with setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream}.
     * @param  [in] frame_num <br>
     *         The number of sample points should be the sample_rate/100 set in setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream}.
     *         When the sample rate is set to 48000, 480 sample points should be pushed each time
     * @return
     *        + True: success <br>
     *        + False: failure
     * @notes
     *       + Before calling this method, you must use the setAudioPlayoutMixStream{@link #setAudioPlayoutMixStream} method to set the data format of audio_frame
     * . <br>
     *       + Before calling this method, get the cached data amount through getAudioMixingStreamCachedFrameNum
     * , And adjust the rhythm of the push data to avoid internal cache overflow causing push failure. <br>
     *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 200 milliseconds) on the application side first,
     *  And then push it all at once; after that, the push operation is timed once in 10 milliseconds, and each time The amount of audio data is 10 milliseconds.
     */
    virtual bool pushAudioMixingStreamData(int8_t* audio_frame, int frame_num) = 0;

#ifndef ByteRTC_AUDIO_ONLY

    /** 
     * @hidden (Linux)
     * @type api
     * @region Video management
     * @brief Enable internal video capture immediately. The default is off.   <br>
     *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
     *        The local client will be informed via onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} after starting video capture by calling this API.
     *        The remote clients in the room will be informed of the state change via onUserStartVideoCapture{@link #IRtcEngineEventHandler#onUserStartVideoCapture} after the visible client starts video capture by calling this API.<br>
     * @notes   <br>
     *        + Call stopVideoCapture{@link #IRtcEngine#stopVideoCapture} to stop the internal video capture. Otherwise, the internal video capture will sustain until you destroy the engine instance.<br>
     *        + Once you create the engine instance, you can start internal video capture regardless of the video publishing state. The video stream will start publishing only after the video capture starts. <br>
     *        + To switch from custom to internal video capture, stop publishing before disabling the custom video capture module and then call this API to enable the internal video capture.<br>
     */
    virtual void startVideoCapture() = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Video management
     * @briefDisable internal video capture immediately. The default is off.   <br>
     *        Internal video capture refers to: use the RTC SDK built-in video capture module to capture.<br>
     *        The local client will be informed via onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} after stopping video capture by calling this API.<br>
     *        The remote clients in the room will be informed of the state change via onUserStopVideoCapture{@link #IRtcEngineEventHandler#onUserStopVideoCapture} after the visible client stops video capture by calling this API.<br>
     * @notes   <br>
     *        + Call startVideoCapture{@link #IRtcEngine#startVideoCapture} to enable the internal video capture. <br>
     *        + Without calling this API the internal video capture will sustain until you destroy the engine instance.
     */
    virtual void stopVideoCapture() = 0;

   /** 
    * @hidden(Linux)
    * @type api
    * @region  Video Management
    * @brief  Set the video capture parameters for internal capture of the RTC SDK. <br>
    *         If your project uses the SDK internal capture module, you can specify the video capture parameters including preference, resolution and frame rate through this interface.
    * @param videoCaptureConfig  Video capture parameters. See: VideoCaptureConfig{@link #VideoCaptureConfig}.
    * @return   <br>
    *         + 0: Success; <br>
    *         + < 0: Failure; <br>
    * @notes   <br>
    *  + This interface can be called after the engine is created and takes effect immediately after being called. It is recommended to call this interface before calling startVideoCapture{@link #IRtcEngine#startVideoCapture}.<br>
    *  + It is recommended that different Engines on the same device use the same video capture parameters.<br>
    *  + If you used the internal module to start video capture before calling this interface, the capture parameters default to Auto.
    */
    virtual int setVideoCaptureConfig(const VideoCaptureConfig& videoCaptureConfig) = 0;

    /** 
     * @type api
     * @region Video Management
     * @brief Enables/Disables the mode of publishing multiple video streams with different encoding configuration.
     * @param [in] enabled Whether to enable the mode of publishing multiple video streams:  <br>
     *        + True: Yes  <br>
     *        + False: No(Default setting)
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + <0: Failure
     * @notes <br>
     *        + You can call this API  <br>
     *            - Before entering the room, or  <br>
     *            - After entering the room but before publishing streams.  <br>
     *        + After setting this API to "True", you can call [SetVideoEncoderConfig](#IRtcEngineLite-setvideoencoderconfig-1) to set encoding configuration for each stream.  <br>
     *        + If this function is off, or if this function is on but you don't set the configuration of any stream, only one stream will be sent with a resolution of 640px × 360px and a frame rate of 15fps.
     */
    virtual int enableSimulcastMode(bool enabled) = 0;

    /**
     * {en}
     * @type api
     * @region Video Management
     * @brief <span id="IRtcEngineLite-setvideoencoderconfig-1"></span>
     *        Video publisher call this API to set the parameters of the maximum resolution video stream that is expected to be published, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
     *        You can only set configuration for one stream with this API. If you want to set configuration for multiple streams, Call [SetVideoEncoderConfig](#IRtcEngineLite-setvideoencoderconfig-2).
     * @param [in] max_solution The maximum video encoding parameter. See VideoEncoderConfig{@link #VideoEncoderConfig}.
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure <br>
     * @notes   <br>
     *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode}, SDK will automatically adjust the number of streams published and the parameters of each published stream according to the settings of subscribers. Up to 4 streams will be published, and the resolution you set in this API will be considered as the largest resolution among these 4 streams, see [Publish Multiple Streams](https://www.volcengine.com/docs/6348/70139) for details. Until you enable the mode of publishing multiple streams, SDK will only publish the stream you set.  <br>
     *        + Without calling this API, SDK will only publish one stream for you with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig{@link #IRtcEngine#setScreenVideoEncoderConfig}} for setting parameters for screen sharing video stream.
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig& max_solution) = 0;

    /** 
     * @type api
     * @region Video Management
     * @brief <span id="IRtcEngineLite-setvideoencoderconfig-2"></span>
     *        Video publisher call this API to set the configurations of each stream published, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
     * @param [in] channel_solutions List of configurations for multiple streams. You can set parameters for up to 3 streams, SDK will always take the value of the first 3 streams when parameters for more streams are set.
     *        You should note that the resolution you set is the maximum resolution of each stream, and must be arranged from largest to smallest. See VideoEncoderConfig{@link #VideoEncoderConfig}.
     * @param [in] solution_num Numbers of streams
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure <br>
     * @notes   <br>
     *        + If you call this API after enabling the mode of publishing multiple streams with enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode}, SDK will publish streams as you set, otherwise only the stream with the largest resolution you set will be published.  <br>
     *        + Without calling this API to set parameters for multiple video streams, the SDK only publishes one video stream with a resolution of 640px × 360px and a frame rate of 15fps.  <br>
     *        + After setting parameters for multiple video streams, SDK will automatically match the streams to be published based on the desired subscription parameters set by subscribers, see [Publish Multiple Streams](https://www.volcengine.com/docs/6348/70139) for details.  <br>
     *        + This API is applicable to the video stream captured by the camera, see setScreenVideoEncoderConfig{@link #IRtcEngine#setScreenVideoEncoderConfig}} for setting parameters for screen sharing video stream.
     */
    virtual int setVideoEncoderConfig(const VideoEncoderConfig* channel_solutions, int solution_num) = 0;

    /** 
     * @type api
     * @region Screen Shareing Management
     * @brief Video publisher call this API to set the expected configurations for the screen sharing video stream, including resolution, frame rate, bitrate, scale mode, and fallback strategy in poor network conditions.
     * @param [in] screen_solution You expected configurations for screen sharing video stream. See VideoEncoderConfig{@link #VideoEncoderConfig}.
     * @return  API call result: <br>
     *        + 0: Success <br>
     *        + ! 0: Failure <br>
     * @notes Without calling this API, the default encoding parameters for screen sharing video streams are: resolution 1920px × 1080px, frame rate 15fps.
     */
    virtual int setScreenVideoEncoderConfig(const VideoEncoderConfig& screen_solution) = 0;

    /** 
     * @hidden
     * @deprecated since 336, using SetVideoEncoderConfig instead.
     * @type api
     * @region  Video management
     * @brief  Sets the video encoder configuration of each individual stream for simulcasting, including resolution, frame rate, bitrate, scale mode, fallback strategy under poor network conditions, etc.
     * @param  [in] index Stream type. See StreamIndex{@link #StreamIndex}.
     * @param  [in] solutions    Video parameters of each individual stream for simulcasting. See VideoSolution{@link #VideoSolution}.
     *                           The maximum resolution is 4096px × 4096px. If the resolution exceeds the limit or the video cannot be encoded, the simulcasting will fail.
     * @param  [in] solution_num The length of `solutions`. <br>
     *                           The length of `solutions` is no more than 4. The resolutions must be in descending sort. <br>
     * @return   <br>
     *         + 0: Success <br>
     *         +! 0: Failure <br>
     * @notes   <br>
     *        + When using the internal capture, the resolution and frame rate will be adapted to the maximum resolution and frame rate for encoding. <br>
     *        + The video streams are encoded by default with resolution of 640px × 360px and frame rate of 15fps. <br>
     *        When you call this API, it will take effect immediately, which may cause the camera to restart. <br>
     *        + The screen stream takes the first set of parameters.
     */
    virtual int setVideoEncoderConfig(StreamIndex index, const VideoSolution* solutions, int solution_num) = 0;

    /** 
     * @hidden
     * @deprecated since 329.1, use setVideoEncoderConfig instead
     * @type api
     * @region Video Management
     * @brief Start pushing multiple video streams, and set the video parameters when pushing multiple streams,
     *        Including resolution, Frame rate, bit rate, zoom mode, fallback strategy when the network is poor, etc.
     * @param  [in] solutions The first address of the video parameter array. See VideoSolution{@link #VideoSolution}.
     * @param  [in] solution_num Video parameter array length. <br>
     *                           Up to 3 parameters are supported. When multiple parameters are set, the resolution must be sequentially reduced, arranged from large to small. <br>
     *                           There is no limit to the maximum resolution. However, if the set resolution cannot be encoded, the encoding push stream will fail.
     * @return   <br>
     *         + 0: Success <br>
     *         +! 0: Failure <br>
     * @notes   <br>
     *         + When using internal capture, the resolution and frame rate of video capture will be adapted according to encoding parameters. <br>
     *         + The default video encoding parameters are: resolution 640px × 360px, frame rate 15fps. <br>
     *         + Changing the encoding resolution takes effect immediately, which may cause the camera to restart.
     */
    virtual int setVideoEncoderConfig(const VideoSolution* solutions, int solution_num) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Video Management
     * @brief Sets the view to be used for local video rendering and the rendering mode.  <br>
     * @param [in] index Video stream type. See StreamIndex{@link #StreamIndex}.
     * @param [in] canvas View information and rendering mode. See VideoCanvas{@link #VideoCanvas}.
     * @return  <br>
     *        + 0: Success <br>
     *        + -1: Failure <br>
     * @notes  <br>
     *       + You should bind your stream to a view before joining the room. This setting will remain in effect after you leave the room. <br>
     *       + If you need to unbind the local video stream from the current view, you can call this API and set the videoCanvas to `null`.
     */
    virtual int setLocalVideoCanvas(StreamIndex index, const VideoCanvas& canvas) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @region Video management
     * @brief Update the render mode and background color of local video rendering
     * @param [in] index See StreamIndex{@link #StreamIndex}.
     * @param [in] renderMode See RenderMode{@link #RenderMode}.
     * @param [in] backgroundColor See VideoCanvas{@link #VideoCanvas}.background_color.
     * @notes Calling this API during local video rendering will be effective immediately.
     */
    virtual void updateLocalVideoCanvas(StreamIndex index, const enum RenderMode renderMode, const uint32_t backgroundColor) = 0;

    /** 
     * @type api
     * @hidden(Linux)
     * @region Video Management
     * @brief Set the view and mode for rendering the specific video stream. <br>
     *        If you need to unbind the canvas for the video stream, set the canvas to `Null`.
     * @param  [in] stream_key See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] canvas canvas and rendering mode. See VideoCanvas{@link #VideoCanvas}
     * @return   <br>
     *         + 0: Success <br>
     *         +!0: Failure <br>
     * @notes   <br>
     *        + Set the canvas after receiving onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} or onFirstRemoteVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameDecoded}. The difference between these two callbacks is that if the video recording function is enabled, the video recording service will join the room as a dumb client side, so other client sides will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined} callback. <br>
     *       + When the local user leaves the room, the setting will be invalid. The remote user leaving the room does not affect the setting.
     */
    virtual void setRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const VideoCanvas& canvas) = 0;
    /** 
     * @hidden(Linux)
     * @type api
     * @region Video management
     * @brief Update the render mode and background color of remote video rendering
     * @param [in] stream_key See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param [in] renderMode See RenderMode{@link #RenderMode}.
     * @param [in] backgroundColor See VideoCanvas{@link #VideoCanvas}.background_color.
     * @notes Calling this API during remote video rendering will be effective immediately.
     */
    virtual void updateRemoteStreamVideoCanvas(RemoteStreamKey stream_key, const enum RenderMode renderMode, const uint32_t backgroundColor) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Custom Video Capturing & Rendering
     * @brief Binds the local video stream to a custom renderer.
     * @param [in] index Video stream type. See StreamIndex{@link #StreamIndex}.
     * @param [in] video_sink Custom video renderer. See IVideoSink{@link #IVideoSink}.
     * @param [in] required_format Video frame encoding format that applys to custom rendering. See PixelFormat{@link #PixelFormat}.
     * @notes  <br>
     *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
     *        + Joining or leaving the room will not affect the binding state. <br>
     *        + If you need to unbind the video stream from the custom renderer, you must set video_sink to `null`.  <br>
     *        + You should call this API before joining the room, and after receiving onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured} which reports that the first local video frame has been successfully captured.
     */
    virtual void setLocalVideoSink(
            StreamIndex index, IVideoSink* video_sink, IVideoSink::PixelFormat required_format) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Custom Video Capturing & Rendering
     * @brief Binds the remote video stream to a custom renderer.
     * @param [in] stream_key Remote stream information which specifys the source and type of the video stream to be rendered. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param [in] video_sink Custom video renderer. See IVideoSink{@link #IVideoSink}.
     * @param [in] required_format Encoding format which applys to the custom renderer. See PixelFormat{@link #PixelFormat}.
     * @notes   <br>
     *        + RTC SDK uses its own renderer (internal renderer) for video rendering by default.  <br>
     *        + Joining or leaving the room will not affect the binding state. <br>
     *         + This API can be called before and after entering the room. To call before entering the room, you need to get the remote stream information before joining the room; if you cannot get the remote stream information in advance, you can call the API after joining the room and getting the remote stream information via onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream}.
     *         + If you need to unbind, you must set videoSink to null.
     */
    virtual void setRemoteVideoSink(RemoteStreamKey stream_key, IVideoSink* video_sink,
                                   IVideoSink::PixelFormat required_format) = 0;

    /** 
     * @hidden
     * @deprecated since 336.1, use unpublishStream publishStream instead.
     * @type api
     * @region Video management
     * @brief Enable/ Disable the transmission of the local video stream.  The video stream is not sending by default.<br>
     *        Call this API to start sending local video streams when using either internal capture module or custom video source. <br>
     *         Remote users in the room will be informed via onUserMuteVideo{@link #IRTCRoomEventHandler#onUserMuteVideo} after the visible user changes the transmission state of the video streams by calling this API.
     * @param   [in] muteState An identifier denoting whether the local video stream is sending. Refer to MuteState{@link #MuteState} for more details. <br>
     * @notes  <br>
     *         + Calling this API toggles the transmission state of the local video streams instead of the capture state.
     *         + You can enable video transmission regardless of the video capture state. Enable the transmission before capture, thus the video stream can be sent once the capture starts.
     */
    virtual void muteLocalVideo(MuteState muteState) = 0;

    /** 
     * @hidden
     * @type api
     * @region Audio management
     * @brief Send screen share local audio data
     * @param  [in] pData
     *        Audio data
     * @param  [in] nSamples
     *        Sample number
     * @param  [in] nBytesPerSample
     *        Single sample data length
     * @param  [in] nChannels
     *        Audio channel number
     * @param  [in] sampleRate
     *        Sample rate
     * @return   <br>
     *         + True: success; <br>
     *         + False: failure; <br>
     * @notes   <br>
     *        + Only video frames in YUV420P format are supported for the time being. <br>
     *        + This function runs in the user calling thread. Before destroying the RtcEngine instance, please stop calling this function to push screen shared data <br>
     */
    virtual void pushScreenAudioFrame(const void* pData, const size_t nSamples, const size_t nBytesPerSample,
            const size_t nChannels, const uint32_t sampleRate) = 0;

    /** 
     * @hidden (macOS, Windows, Linux)
     * @type api
     * @region Video management
     * @brief Toggle the front/postcondition camera used for internal video capture  <br>
     *        After calling this interface, onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} callback will be triggered locally.
     * @param   [in] Camera ID, mobile end camera. See CameraID{@link #CameraID}.
     * @return   <br>
     *         + 0: Success <br>
     *         +! 0: Failed <br>
     * @notes   <br>
     *        + Default uses front-facing camera.
     *        + If you are using the camera for video capture, the toggle operation will take effect immediately; if the camera is not activated, the set camera will be turned on when the internal capture is turned on later.
     *        + If you have multiple cameras locally and want to select a specific working camera, you can control it through IVideoDeviceManager{@link #IVideoDeviceManager}. <br>
     */
    virtual int switchCamera(CameraID camera_id) = 0;

    /** 
     * @type api
     * @region Screen sharing
     * @brief Push screen video frame.
     * @param  [in] frame Set the screen video frame, see: IVideoFrame{@link #IVideoFrame}. <br>
     * @return   <br>
     *         + True: success; <br>
     *         + False: failure; <br>
     * @notes   <br>
     *        + Only video frames in YUV420P format are supported for the time being. <br>
     *        + This function runs in the user calling thread. Before destroying the RtcEngine instance, please stop calling this function to push screen shared data <br>
     */
    virtual bool pushScreenFrame(IVideoFrame* frame) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region Screen Sharing
     * @brief This method shares a window or part of the window. The user needs to specify the window id that he wants to share in this method.
     * @param  [in] window_id
     *        Specify the window id to be shared, see: view_t{@link #view_t}
     * @param  [in] region_rect
     *        Specify the position of the shared area relative to the entire window, and share the entire window when the value is 0, see: Rectangle{@link #Rectangle}
     * @param  [in] capture_params
     *        Encoding parameter configuration for screen sharing, see: DesktopCaptureParameters {@link # DesktopCaptureParameters}
     * @return   <br>
     *         + 0: Success; <br>
     *         + -1: Failure; <br>
     * @notes   <br>
     *        + This function and publishScreen{@link #IRTCRoom#publishScreen} are mutually exclusive. When calling stopScreenCapture {@link
     *  #stopScreenCapture}, publishScreen{@link #IRTCRoom#publishScreen} can be used again.  <br>
     *        + This function and stopScreenCapture{@link #stopScreenCapture} are called in pairs. <br>
     *        + After receiving the onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     *          Event, set the remote screen sharing view by calling the setRemoteVideoCanvas{@link #setRemoteVideoCanvas} or setRemoteVideoSink{@link #setRemoteVideoSink}
     *          Function. <br>
     *        + Locally, you can call the setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} or setLocalVideoSink {@link #setLocalVideoSink} Function to set the local screen share view. <br>
     *        + You can also get the original data source by registering the registerVideoFrameObserver{@link #registerVideoFrameObserver} video callback object, listening for the
     * onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} local screen video callback event and the
     * onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} remote screen share video callback event. <br>
     */
    virtual int startScreenCaptureByWindowId(
            view_t window_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region Screen Sharing
     * @brief Share the screen by specifying an area to share a screen or part of the screen. The user needs to specify the screen area that he wants to share in this method.
     * @param  [in] screen_rect
     *         Specify the position of the screen to be shared relative to the virtual screen. The virtual screen refers to the image area composed of all screens. For details, see: Rectangle{@link #Rectangle}
     * @param  [in] region_rect
     *         Specify the position of the area to be shared relative to the screen_rect. For details, see: Rectangle{@link #Rectangle}
     * @param  [in] capture_params
     *         The encoding parameter configuration of screen sharing, see: DesktopCaptureParameters {@Link #DesktopCaptureParameters}
     * @return   <br>
     *         + 0: Success; <br>
     *         + -1: Failure; <br>
     * @notes   <br>
     *        + This function and publishScreen{@link #IRTCRoom#publishScreen} are mutually exclusive to use when calling stopScreenCapture {@link
     *  #stopScreenCapture} Before using publishScreen{@link #IRTCRoom#publishScreen}. <br>
     *        + This function and stopScreenCapture{@link #stopScreenCapture} are called in pairs <br>
     *        + After receiving the onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     *          Event, set the remote screen sharing view by calling the
     * setRemoteVideoCanvas{@link #setRemoteVideoCanvas} or setRemoteVideoSink{@link #setRemoteVideoSink}
     *  Function. <br>
     *        + Locally, you can call the setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} or setLocalVideoSink {@link #setLocalVideoSink} Function to set the local screen share view. <br>
     *        + You can also get the original data source by registering the registerVideoFrameObserver{@link #registerVideoFrameObserver} video callback object, listening for the
     * onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} local screen video callback event and the
     * onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} remote screen share video callback event. <br>
     */
    virtual int startScreenCaptureByScreenRect(const Rectangle& screen_rect, const Rectangle& region_rect,
            const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden (iOS, Android)
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region screen sharing
     * @brief Share the screen through the screen id, share a screen or part of the screen. Users need to specify the screen id they want to share in this method.
     * @param  [in] display_id
     *         Specify the screen id to be shared.
     * @param  [in] region_rect
     *         Specify the location of the area to be shared relative to the entire screen, see: Rectangle{@link #Rectangle}
     * @param  [in] capture_params
     *        The encoding parameter configuration for screen sharing, see: DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return   <br>
     *         + 0: Success; <br>
     *         + -1: Failure; <br>
     * @notes  Share a window or part of the window. You need to specify the window id you want to share in this method.
     */
    virtual int startScreenCaptureByDisplayId(
            unsigned int display_id, const Rectangle& region_rect, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden (macOS, Windows,iOS)
     * @deprecated since 327.1, use startScreenVideoCapture and publishScreen instead
     * @type api
     * @region screen sharing
     * @brief Open screen sharing through the incoming Context.
     * @param  [in] context
     *        Android platform is MediaProjection object, obtained by the business party after applying for system recording permission, not used on the iOS, just pass empty.
     * @param  [in] group_id
     *        IOS platform needs to pass in the group id used by App and Extension, and the Android platform can pass empty.
     * @param  [in] capture_params
     *         Screen sharing encoding parameter configuration, see: DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return   <br>
     *         + 0: success; <br>
     *         + -1: Failure; <br>
     * @notes  Turn on screen sharing, mobile end dedicated interface.
     */
    virtual int startScreenCapture(
            void* context, const char* group_id, const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden (iOS, Android, Linux)
     * @type api
     * @region Screen sharing
     * @brief Update the capture area when capturing screen video streams through the capture module provided by the RTC SDK.
     * @param   [in] region_rect Acquisition area. See Rectangle{@link #Rectangle} <br>
     *                           This parameter describes the acquisition area after calling this interface, and the relative relationship between the 'source_info' setting area in startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}.
     * @notes Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}.
     */
    virtual void updateScreenCaptureRegion(const Rectangle& region_rect) = 0;

    /** 
     * @hidden
     * @deprecated since 327.1, use setVideoEncoderConfig, updateScreenCaptureHighlightConfig,
     *                  updateScreenCaptureFilterConfig, updateScreenCaptureMouseCursor instead
     * @type api
     * @region ScreenShare
     * @brief Update the configuration of the encoding parameters of the screen share.
     * @param  [in] capture_params
     *         Screen share encoding parameter configuration, see: DesktopCaptureParameters{@link #DesktopCaptureParameters}
     * @return   <br>
     *         + 0: success; <br>
     *         + -1: Failure; <br>
     */
    virtual int updateScreenCaptureParameters(const DesktopCaptureParameters& capture_params) = 0;

    /** 
     * @hidden (iOS, Android, Linux)
     * @type api
     * @region  screen sharing
     * @brief  Capture screen video stream for sharing. Screen video stream includes: content displayed on the screen, in the application window, or in the virtual screen. <br>
     *        The content displayed in the virtual screen is only supported on Windows.
     * @param  [in] source_info Screen capture source information. See ScreenCaptureSourceInfo{@link #ScreenCaptureSourceInfo}. <br>
     *                          Call getScreenCaptureSourceList{@link #IRtcEngine#getScreenCaptureSourceList} to get all the screen sources that can be shared.
     * @param  [in] capture_params Screen capture parameters. See ScreenCaptureParameters{@link #ScreenCaptureParameters}.
     * @return   <br>
     *         + 0: Success; <br>
     *         + -1: Failure; <br>
     * @notes   <br>
     *        + This API only starts screen capturing but does not publish the captured video. Call PublishScreen{@link #IRTCRoom#PublishScreen} to publish the captured video. <br>
     *        + To turn off screen video capture, call StopScreenVideoCapture{@link #IRtcEngine#StopScreenVideoCapture}. <br>
     *        + Local users will receive OnVideoDeviceStateChanged{@link #IRtcEngineEventHandler#OnVideoDeviceStateChanged} on the state of screen capturing such as start, pause, resume, and error. <br>
     *        + After successfully calling this API, local users will receive onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured}. <br>
     *        + Before calling this API, you can call SetScreenVideoEncoderConfig{@link #IRtcEngine#SetScreenVideoEncoderConfig} to set the frame rate and encoding resolution of the screen video stream. <br>
     *        + After receiving onFirstLocalVideoFrameCaptured{@link #IRtcEngineEventHandler#onFirstLocalVideoFrameCaptured}, you can set the local screen sharing view by calling SetLocalVideoCanvas{@link #IRtcEngine#SetLocalVideoCanvas} or SetLocalVideoSink {@link #SetLocalVideoSink}. <br>
     *        + You can also register an observer by calling RegisterVideoFrameObserver{@link #RegisterVideoFrameObserver} and receive the captured screen video frame through OnLocalScreenFrame{@link #IVideoFrameObserver#OnLocalScreenFrame}.<br>
     */
    virtual int startScreenVideoCapture(const ScreenCaptureSourceInfo& source_info, const ScreenCaptureParameters& capture_params) = 0;

    /** 
     * @hidden (macOS, Windows, iOS, Linux)
     * @deprecated since 336.1, use startScreenCapture instead
     * @type api
     * @region  Screen sharing
     * @brief  Open screen sharing through the incoming Context.
     * @param  [in] context
     *        Android platform incoming MediaProjection object, obtained by the business party after applying for system recording permission.
     * @return   <br>
     *         + 0: Success; <br>
     *         + -1: Failure; <br>
     * @notes  Enable screen sharing, Android-specific interface.
     */
    virtual int startScreenVideoCapture(void* context) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region screen sharing
     * @brief Stop screen video streaming.
     * @notes   <br>
     *        + To turn on screen video stream capture, calling startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} <br>
     *        + Local users will receive the onVideoDeviceStateChanged{@link #IRtcEngineEventHandler#onVideoDeviceStateChanged} callback. <br>
     *        + Calling this interface does not affect screen video stream publishing. <br>
     */
    virtual void stopScreenVideoCapture() = 0;

    /** 
     * @hidden (iOS, Android, Linux)
     * @type api
     * @region Screen sharing
     * @brief Update border highlighting settings when capturing screen video streams through the capture module provided by the RTC SDK. The default display table box.
     * @param  [in] highlight_config Border highlighting settings. See HighlightConfig{@link #HighlightConfig}
     * @notes  Before calling this interface, you must have turned on internal screen flow collection by calling startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}.
     */
    virtual void updateScreenCaptureHighlightConfig(const HighlightConfig& highlight_config) = 0;

    /** 
     * @hidden (iOS, Android, Linux)
     * @type api
     * @region Screen sharing
     * @brief Update the processing settings for the mouse when capturing screen video streams through the capture module provided by the RTC SDK. Default acquisition mouse.
     * @param  [in] capture_mouse_cursor See MouseCursorCaptureState{@link #MouseCursorCaptureState}
     * @notes  Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}.
     */
    virtual void updateScreenCaptureMouseCursor(MouseCursorCaptureState capture_mouse_cursor) = 0;

    /** 
     * @hidden (iOS, Android, Linux)
     * @type api
     * @region Screen sharing
     * @brief When capturing screen video streams through the capture module provided by the RTC SDK, set the window that needs to be filtered.
     * @param  [in] ScreenFilterConfig Window filtering settings. See ScreenFilterConfig{@link #ScreenFilterConfig} <br>
     * @notes  <br>
     *        + Before calling this interface, internal screen stream capture must have been turned on by calling startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture}. <br>
     *        + This function only works when the screen source category is a screen rather than an application form. See: ScreenCaptureSourceType{@link #ScreenCaptureSourceType}
     */
    virtual void updateScreenCaptureFilterConfig(const ScreenFilterConfig& filter_config) = 0;

    /** 
     * @hidden (Linux)
     * @brief  Get the list of shared objects (application windows and desktops),  after using it, you need to call the corresponding release interface to release
     * @region  screen sharing
     * @notes   <br>
     *        + The enumerated form can be used as an input parameter when opening screen sharing, see: startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} <br>
     *        + This function For PC side use only
     */
    virtual IScreenCaptureSourceList* getScreenCaptureSourceList() = 0;

    /** 
     * @hidden (Linux)
     * @brief  Get the preview thumbnail of the screen-sharing object
     * @region  screen share
     * @param type Type of the screen capture object. Refer to ScreenCaptureSourceType{@link #ScreenCaptureSourceType} for more details.
     * @param source_id ID of the screen-shared object. Refer to view_t{@link #view_t} for more details.
     * @param max_width Maximum width of the preview thumbnail. RTC will scale the thumbnail to fit the given size while maintaining the original aspect ratio. If the aspect ratio of the given size does not match the sharing object, the thumbnail will have blank borders.
     * @param max_height Maximum height of the preview thumbnail. Refer to the note for `max_width`.
     * @return Preview thumbnail of the screen-sharing object Refer to IVideoFrame{@link #IVideoFrame} for more details.
     */
    virtual IVideoFrame* getThumbnail(
            ScreenCaptureSourceType type, view_t source_id, int max_width, int max_height) = 0;

    /** 
     * @hidden(Linux)
     * @brief Get application window preview thumbnail for screen sharing. 
     * @region 屏幕共享
     * @param source_id ID of the screen-sharing object. You can get the ID by calling getScreenCaptureSourceList{@link #getScreenCaptureSourceList}. Refer to view_t{@link #view_t} for more details.
     * @param max_width Maximum width of the App icon. The width is always equal to the height. SDK will set the height and width to the smaller value if the given values are unequal. RTC will return nullptr if you set the value with a number out of the valid range, [32, 256]. The default size is 100 x 100.
     * @param max_height Maximum height of the app icon. Refer to the note for  `max_width`
     * @return Refer to IVideoFrame{@link #IVideoFrame} for more details. You can call this API when the item to be shared is an application. If not, the return value will be nullptr.
     */
    virtual IVideoFrame* getWindowAppIcon(view_t source_id, int max_width = 100, int max_height = 100) = 0;

    /** 
     * @hidden
     * @deprecated since 324.1, use setVideoSourceType instead
     * @type api
     * @region Video Management
     * @brief Set whether custom video capture is enabled
     * @param   [in] enable <br>
     *        + True: On <br>
     *        + False: Off
     * @notes   <br>
     *        + 1. This method can be called before and after entering the room. <br>
     *        + 2. When you have called startVideoCapture{@link #IRtcEngine#startVideoCapture} to turn on internal collection, and then call this method to switch to custom collection, the SDK will automatically turn off internal collection. <br>
     *        + 3. When you call this method to turn on custom collection, to switch to internal collection, you must first call this method to turn off custom collection, and then call StartVideoCapture{@link #IRtcEngine#startVideoCapture} to manually turn on internal collection.
     */
    virtual void setExternalVideoSource(bool enable) = 0;

    /** 
     * @hidden
     * @deprecated since 329.1, use setVideoSourceType instead
     * @type api
     * @region Video management
     * @brief Switch video capture methods (internal capture/custom capture)
     * @param   [in] type Video capture methods. See VideoSourceType{@link #VideoSourceType}
     * @notes   <br>
     *        + Default uses internal capture. Internal capture refers to video capture using the video capture mechanism built into the RTC SDK. <br>
     *        + This method can be called before and after entering the room. <br>
     *        + When you have called startVideoCapture{@link #IRtcEngine#startVideoCapture} to turn on internal collection, and then call this method to switch to custom collection, the SDK will automatically turn off internal collection. <br>
     *        + When you call this method to turn on custom collection, in order to switch to internal collection, you must first call this method to turn off custom collection, and then call startVideoCapture{@link #IRtcEngine#startVideoCapture} to manually turn on internal collection.
     */
    virtual void setVideoSourceType(VideoSourceType type) = 0;

    /** 
     * @type api
     * @region Video management
     * @brief Set the video source of the RTC SDK.
     *        The internal video capture is the default, which refers to capturing video using the built-in module.
     * @param  [in] stream_index Stream index. Refer to StreamIndex{@link #StreamIndex} for more details.
     * @param  [in] type Video source type. Refer to VideoSourceType{@link #VideoSourceType} for more details.
     * @notes   <br>
     *         + You can call this API whether the user is in a room or not. <br>
     *         + Calling this API to switch to the custom video source will stop the enabled internal video capture.
     *         + To switch to internal video capture, call this API to stop custom capture and then call startVideoCapture{@link #IRtcEngine#startVideoCapture} to enable internal video capture.<br>
     *         + To push custom encoded video frames to the SDK, call this API to switch `VideoSourceType` to `VideoSourceTypeEncodedWithAutoSimulcast` or `VideoSourceTypeEncodedWithoutAutoSimulcast`.
     */
    virtual void setVideoSourceType(StreamIndex stream_index, VideoSourceType type) = 0;

    /** 
     * @type api
     * @region  Video Management
     * @brief  Send external source video data
     * @param  [in] frame Set the video frame. See IVideoFrame{@link #IVideoFrame}. <br>
     * @notes   <br>
     *        + Only video frames in YUV420P format are supported for the time being. <br>
     *        + This function runs in the user calling thread <br>
     * @notes  Before pushing external video frames, you must call setVideoSourceType{@link #setVideoSourceType} to turn on external video source capture.
     */
    virtual bool pushExternalVideoFrame(IVideoFrame* frame) = 0;

    /**
     * @hidden
     */
    virtual void setupDynamicLayoutRender(IVideoSink* render) = 0;
#endif

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device, and use speakers by default.   <br>
     *         When the audio playback device changes, you will receive an onAudioPlaybackDeviceChanged {@link
     *  #IRtcEngineLiteEventHandler #onAudioPlaybackDeviceChanged} Callback.
     * @param  [in] device Audio playback device. See AudioPlaybackDevice{@link #AudioPlaybackDevice} <br>
     * @return  Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     * @notes   <br>
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method only supports setting audio & video playback devices as earphones or speakers. When the app connects to a wired or Bluetooth audio playback device, the SDK
     *  Automatically switches to a wired or Bluetooth audio playback device. Active setting as a wired or Bluetooth audio playback device will return Failure. <br>
     *        + 3.
     * If you connect a wired or Bluetooth audio playback device, setting the audio playback device as a speaker or earpiece will successfully call, but it will not immediately switch to the speaker or earpiece. After the wired or Bluetooth audio playback device is removed, it will automatically switch to the earpiece or speaker according to the settings.
     *  <br>
     *        + 4. This method can be called before and during a call. <br>
     */
    virtual int setAudioPlaybackDevice(AudioPlaybackDevice device) = 0;

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device,  When the audio playback device <br>
     *          changes, you will receive an OnAudioRouteChanged {@link
     *  #IRtcEngineLiteEventHandler #OnAudioRouteChanged} Callback.
     * @param  [in] device Audio playback device. See AudioRoute{@link #AudioRoute} <br>
     * @return  Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     * @notes   <br>
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method only called in communication scenario, can manually route to any available device.
     *        + 3. This method can be only called during a call.
     *        + 4. SetAudioRoute to kAudioRouteUnknown must be failed.<br>
     */
    virtual int setAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device, and use speakers by default.   <br>
     *         When the audio playback device changes, you will receive an OnAudioRouteChanged {@link
     *  #IRtcEngineLiteEventHandler #OnAudioRouteChanged} Callback.
     * @param  [in] device Audio playback device. See AudioRoute{@link #AudioRoute} <br>
     * @return  Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     * @notes   <br>
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method only supports setting audio & video playback devices as earphones or speakers. When the
     * app connects to a wired or Bluetooth audio playback device, the SDK Automatically switches to a wired or
     * Bluetooth audio playback device. Active setting as a wired or Bluetooth audio playback device will return
     * Failure. <br>
     *        + 3.
     * If you connect a wired or Bluetooth audio playback device, setting the audio playback device as a speaker or
     * earpiece will successfully call, but it will not immediately switch to the speaker or earpiece. After the wired
     * or Bluetooth audio playback device is removed, it will automatically switch to the earpiece or speaker according
     * to the settings. <br>
     *        + 4. This method can be called before and during a call.
     *        + 5. setDefaultAudioRoute to kAudioRouteDeviceUnknown must be failed.<br>
     */
    virtual int setDefaultAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief get current using audio playback device.   <br>
     *         When the audio playback device changes, you will receive an OnAudioRouteChanged{@link
     * #IRtcEngineLiteEventHandler #OnAudioRouteChanged} Callback.
     * @return  device current using Audio playback device. See AudioRoute{@link #AudioRoute}
     * @notes   <br>
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method can be called before and during a call. <br>
     */
    virtual AudioRoute getAudioRoute() = 0;
    /** 
     * @type api
     * @region Audio & Video Fallback
     * @brief Sets the fallback option for published audio & video streams.   <br>
     *        You can call this API to set whether to automatically lower the resolution you set of the published streams under limited network conditions.
     * @param [in] option Fallback option, see PublishFallbackOption{@link #PublishFallbackOption}.
     * @return  API call result <br>
     *         + 0: Success <br>
     *         + < 0: Failure
     * @notes   <br>
     *         + This API only works after you call enableSimulcastMode{@link #IRtcEngine#enableSimulcastMode} to enable the mode of publishing multiple streams. <br>
     *         + You must call this API before entering the room.  <br>
     *         + After you allow video stream to fallback, your stream subscribers will receive onSimulcastSubscribeFallback{@link #IRtcEngineEventHandler#onSimulcastSubscribeFallback}} when the resolution of your published stream are lowered or restored.  <br>
     *         + You can alternatively set fallback options with distributions from server side, which is of higher priority.
     */
    virtual int setPublishFallbackOption(PublishFallbackOption option) = 0;

    /** 
     * @type api
     * @region Audio & Video Fallback
     * @brief Sets the fallback option for subscribed RTC streams.   <br>
     *        You can call this API to set whether to lower the resolution of currently subscribed stream under limited network conditions.
     * @param [in] option Fallback option, see SubscribeFallbackOption{@link #SubscribeFallbackOption} for more details.
     * @return API call result:  <br>
     *        + 0:  Success  <br>
     *        + < 0: Failure
     *  @notes   <br>
     *         + You must call this API before entering the room.  <br>
     *         + After you enables the fallback, you will receive onSimulcastSubscribeFallback{@link #IRtcEngineEventHandler#onSimulcastSubscribeFallback}} and onRemoteVideoSizeChanged{@link #IRtcEngineEventHandler#onRemoteVideoSizeChanged} when the resolution of your subscribed stream is lowered or restored.  <br>
     *         + You can alternatively set fallback options with distributions from server side, which is of higher priority.
     */
    virtual int setSubscribeFallbackOption(SubscribeFallbackOption option) = 0;

    /** 
     * @type api
     * @region  audio & video fallback
     * @brief  Set user priority
     * @param  [in] user_id Remote user's ID
     * @param  [in] priority Remote user's requirement priority. See enumeration type RemoteUserPriority{@link #RemoteUserPriority}
     * @return 0:  Success. <br>
     *         + < 0: failure <br>
     * @notes   <br>
     *         + 1. This method is used with setSubscribeFallbackOption{@link #setSubscribeFallbackOption}. <br>
     *         + 2. If the subscription flow fallback option is turned on, weak connections or insufficient performance will give priority to ensuring the quality of the flow received by high-priority users. <br>
     *         + 3. This method can be used before and after entering the room, and the priority of the remote user can be modified. <br>
     */
    virtual int setRemoteUserPriority(const char* user_id, RemoteUserPriority priority) = 0;

    /** 
     * @type api
     * @region Engine management
     * @brief  Sets the business ID   <br>
     *         You can use businessId to distinguish different business scenarios. You can customize your businessId to serve as a sub AppId, which can share and refine the function of the AppId, but it does not need authentication.
     * @param  [in] business_id <br>
     *         Your customized businessId
     *         BusinessId is a tag, and you can customize its granularity.
     * @return   <br>
     *         + 0: Success <br>
     *         + < 0: Failure. See BusinessCheckCode{@link #BusinessCheckCode} for specific reasons. <br>
     *         + -6001: The user is already in the room. <br>
     *         + -6002: The input is invalid. Legal characters include all lowercase letters, uppercase letters, numbers, and four other symbols, including '.', '-','_', and '@'.
     * @notes   <br>
     *         + You must call this API before the joinRoom{@link #IRtcEngine#joinRoom} API, otherwise it will be invalid.
     */
    virtual int setBusinessId(const char* business_id) = 0;

    /** 
     * @hidden
     * @deprecated since 332.1, use enableVirtualBackground instead
     * @type api
     * @region Video Effects
     * @brief Turn on the background and set the background mode and split mode
     * @param  [in] mode Background mode. See BackgroundMode{@link #BackgroundMode}. <br>
     * @param  [in] divide_model Segmentation model. See DivideMode{@link #DivideMode}. <br>
     * @return   <br>
     *         + 0: Success <br>
     *         +! 0: Failed <br>
     */
    virtual int replaceBackground(BackgroundMode mode, DivideMode divide_model) = 0;

    /** 
     * @hidden
     * @deprecated since 332.1, use disableVirtualBackground instead
     * @type api
     * @region Video Effects
     * @brief  Close the background
     */
    virtual void disableBackground() = 0;

    /** 
     * @deprecated Since 329.1, use setLocalVideoMirrorType instead
     * @hidden
     * @type api
     * @region Video Management
     * @brief Set whether to turn on mirror mode when front-facing camera capture is used.  <br>
     * @param   [in] mirrorMode Whether to turn on mirror mode
     */
    virtual void setLocalVideoMirrorMode(MirrorMode mirrorMode) = 0;

    /** 
     * @type api
     * @hidden(Windows,MacOS,Linux)
     * @brief Set the orientation of the video capture. By default, the App direction is used as the orientation reference.<br>
     *        During rendering, the receiving client rotates the video in the same way as the sending client did.<br>
     * @param [in] rotationMode Rotation reference can be the orientation of the App or gravity. Refer to VideoRotationMode{@link #VideoRotationMode} for details.
     * @return <br>
     *        + 0: Success
     *        + <0: Failure
     * @notes <br>
 *        + The orientation setting is effective for internal video capture only. That is, the orientation setting is not effective to the custom video source or the screen-sharing stream.
 *        + If the video capture is on, the setting will be effective once you call this API. If the video capture is off, the setting will be effective on when capture starts.
     */
    virtual int setVideoRotationMode(VideoRotationMode rotationMode) = 0;

    /** 
     * @type api
     * @region Video management
     * @brief Sets the mirror mode for the captured video stream.
     * @param  [in] mirrorType Mirror type. See MirrorType{@link #MirrorType}.
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
    virtual void setLocalVideoMirrorType(MirrorType mirrorType) = 0;

    /** 
     * @type api
     * @region Audio & Video Processing
     * @brief Enables/Disables basic beauty effects.
     * @param [in] enable Whether to enable basic beauty effects. <br>
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
     *        + You cannot use the basic beauty effects and the advanced effect features at the same time. Call enableEffect{@link #IVideoEffect#enableEffect} to use advanced effect features. <br>
     *        + You need to integrate Effect SDK before calling this API. Effect SDK V4.3.1+ is recommended. <br>
     *        + Call setBeautyIntensity{@link #IRtcEngine#setBeautyIntensity} to set the beauty effect intensity. If you do not set the intensity, the brightness, smoothness, and sharpness intensity will default to 0.5. <br>
     *        + This API is not applicable to screen capturing. <br>
     */
    virtual int enableEffectBeauty(bool enable) = 0;

    /** 
     * @type api
     * @region Audio & Video Processing
     * @brief Sets the beauty effect intensity.
     * @param [in] beautyMode Basic beauty effect. See EffectBeautyMode{@link #EffectBeautyMode}.
     * @param [in] intensity Beauty effect intensity in range of [0,1], default to 0.5. When you set it to 0, the beauty effect will be turned off.
     * @return  <br>
     *        + 0: Success. <br>
     *        + 1000: The Effect SDK is not integrated. <br>
     *        + 1001: This API is not available for your current RTC SDK. <br>
     *        + <0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://docs.byteplus.com/effects/docs/error-code-table). <br>
     * @notes <br>
     *        + If you call this API before calling enableEffectBeauty{@link #IRtcEngine#enableEffectBeauty}, the default settings of beauty effect intensity will adjust accordingly. <br>
     *        + If you destroy the engine, the beauty effect settings will be invalid. <br>
     */
    virtual int setBeautyIntensity(EffectBeautyMode beautyMode, float intensity) = 0;

    /** 
     * @hidden
     * @type api
     * @region Video Effects
     * @brief  Get video effects interface
     * @return  Video effects interface pointer
     */
    virtual IVideoEffect* getVideoEffectInterface() = 0;

    /** 
     * @hidden
     * @type api
     * @region  video management
     * @brief  Get camera control interface
     * @return  Camera control interface pointer
     */
    virtual ICameraControl* getCameraControl() = 0;

    /** 
     * @type api
     * @region Encryption
     * @brief Set the way to use built-in encryption when transmitting  <br>
     * @param encrypt_type Built-in encryption algorithm. See EncryptType{@link #EncryptType}
     * @param  [in] encrypt_type Encryption type. See EncryptType{@link #EncryptType}
     * @param  [in] key Encryption key, the length is limited to 36 bits, and the excess will be Truncate
     * @param  [in] key_size The length of the parameter key
     * @notes   <br>
     *        + Use this method when using the built-in encryption on transfer; if you need to use custom encryption on transfer. See OnEncryptData {@link #IEncryptHandler#OnEncryptData}. Built-in encryption and custom encryption are mutually exclusive, and the transmission is determined to be encrypted according to the last method called. <br>
     *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. <br>
     */
    virtual void setEncryptInfo(EncryptType encrypt_type, const char* key, int key_size) = 0;

    /** 
     * @type api
     * @region Encryption
     * @brief Set custom encryption   <br>
     *        You need to implement the corresponding encryption/decryption method, refer to EncryptType{@link #EncryptType}. <br>
     * @param  [in] handler Custom encryption handler, you need to implement the handler's encryption and decryption method <br>
     * @notes   <br>
     *        + This method is mutually exclusive with setEncryptInfo{@link #IRtcEngine#setEncryptInfo}, you can only select custom encryption method or default encryption method. The encryption method that takes effect depends on the last method called. <br>
     *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. <br>
     *        + Whether encrypted or decrypted, the length modification of the original data source needs to be controlled between 90% and 120%, i.e. If the input data is 100 bytes, the processed data must be between 90 and 120 bytes. Between bytes, if the encrypted or decrypted result exceeds the length limit, the audio & video frame will be discarded. <br>
     *        + Data encryption/decryption is performed serially, so depending on the implementation, it may affect the final rendering efficiency. Whether to use this method needs to be carefully evaluated by users.
     */
    virtual void setCustomizeEncryptHandler(IEncryptHandler* handler) = 0;

    virtual void enableAudioFrameCallback(AudioFrameCallbackMethod method, AudioFormat format) = 0;

    /** 
     * @type api
     * @region Audio Data Callback
     * @brief Enables audio data callback.
     * @param [in] method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}. <br>
     *               If `method` is set as `kAudioFrameCallbackRecord`, `kAudioFrameCallbackPlayback`, `kAudioFrameCallbackMixed`, `kAudioFrameCallbackRecordScreen`, set `format` to the accurate value listed in the audio parameters format.
     *               If `method` is set as `kAudioFrameCallbackRemoteUser`, set `format` to `auto`.
     * @param [in] format Audio parameters format. See AudioFormat{@link #AudioFormat}.
     * @notes After calling this API and registerAudioFrameObserver{@link #IRtcEngine#registerAudioFrameObserver}, IAudioFrameObserver{@link #IAudioFrameObserver} will receive the corresponding audio data callback. However, these two APIs are independent of each other and the calling order is not restricted. <br>
     */
    virtual void disableAudioFrameCallback(AudioFrameCallbackMethod method) = 0;

    /** 
     * @type api
     * @region Audio Data Callback
     * @brief Disables audio data callback.
     * @param [in] method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}.
     * @notes Call this API after calling enableAudioFrameCallback{@link #IRtcEngine#enableAudioFrameCallback}.
     */
    /** 
     * @type api
     * @region Audio Data Callback
     * @brief Register an audio frame observer.  <br>
     * @param [in] observer Audio data callback observer. See IAudioFrameObserver{@link #IAudioFrameObserver}. Use `null` to cancel the registration.
     * @return  <br>
     *        + 0: Success. <br>
     *        + < 0: Failure. <br>
     * @notes After calling this API and enableAudioFrameCallback{@link #IRtcEngine#enableAudioFrameCallback}, IAudioFrameObserver{@link #IAudioFrameObserver} will receive the corresponding audio data callback.
     */
    virtual void registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;
    /** 
     * @type api
     * @hidden
     * @deprecated since 342, use registerAudioProcessor instead.
     * @region  Audio Processing
     * @brief  Set up a custom audio processor.   <br>
     *        Using this processor, you can call processAudioFrame{@link #IAudioProcessor#processAudioFrame} to customize the audio frames captured by the RTC SDK and use the processed audio frames for RTC audio & video communication. <br>
     *        SDK only holds weak references to the processor, you should guarantee its Life Time.
     * @param  [in] processor Custom audio processor. See IAudioProcessor{@link #IAudioProcessor}. If null is passed in, the audio frames captured by the RTC SDK are not customized.
     * @param  [in] audioFormat Customize the audio parameter format. See AudioFormat{@link #AudioFormat}, the SDK will give the audio frame according to the specified settings.
     * @notes When this interface is repeatedly called, only the last call takes effect. The effects do not stack.
     */
    virtual void registerLocalAudioProcessor(IAudioProcessor* processor, AudioFormat audioFormat) = 0;
   /** 
    * @type api
    * @brief  Register a custom audio preprocessor. <br>
    *         After that, you can call enableAudioProcessor{@link #IRtcEngine#enableAudioProcessor} to process the locally captured or received remote audio streams.
    * @param  [in] processor Custom audio processor. See IAudioFrameProcessor{@link #IAudioFrameProcessor}。<br>
    *        SDK only holds weak references to the processor, you should guarantee its Life Time.
    * @notes When this interface is repeatedly called, only the last call takes effect.
    */
    virtual void registerAudioProcessor(IAudioFrameProcessor* processor) = 0;
   /** 
    * @type api
    * @brief Get the local captured audio frames or received remote audio frames for custom processing.
    * @param  [in] method Audio Frame type. See AudioProcessorMethod{@link #AudioProcessorMethod}. To process multiple types of audio, you can call this API with different methods. <br>
    *        With different values, you will receive corresponding callback: <br>
    *        + For locally captured audio, you will receive onProcessRecordAudioFrame{@link #IAudioFrameProcessor#onProcessRecordAudioFrame} <br>
    *        + For mixed remote audio, you will receive onProcessPlayBackAudioFrame{@link #IAudioFrameProcessor#onProcessPlayBackAudioFrame} <br>
    *        + For audio from remote users, you will receive onProcessRemoteUserAudioFrame{@link #IAudioFrameProcessor#onProcessRemoteUserAudioFrame} <br>
    * @param  [in] format The format of the returned audio frame. See AudioFormat{@link #AudioFormat}.
    * @notes <br>
    *        + Before calling this API, you must call registerAudioProcessor{@link #IRtcEngine#registerAudioProcessor} to register the processor. <br>
    *        + To disable custom audio processing, call disableAudioProcessor{@link #IRtcEngine#disableAudioProcessor}.
    */
    virtual void enableAudioProcessor(AudioProcessorMethod method, AudioFormat format) = 0;
    /** 
    * @type api
    * @brief Disable custom audio processing.
    * @param  [in] method Audio Frame type. See AudioProcessorMethod{@link #AudioProcessorMethod}.
    */
    virtual void disableAudioProcessor(AudioProcessorMethod method) = 0;
    /** 
     * @type api
     * @region Video Data Callback
     * @brief Register a video data callback observer
     * @param [in] observer Video data callback observer, see IVideoFrameObserver{@link #IVideoFrameObserver}. Cancel the registration by setting it to `null`.
     * @notes We recommended you call this API before calling joinRoom{@link #IRtcEngine#joinRoom}.
     */
    virtual void registerVideoFrameObserver(IVideoFrameObserver* observer) = 0;

    /** 
      * @type api
      * @region  Video Processing
      * @brief  Set up a custom video preprocessor. <br>
      *         Using this video preprocessor, you can call processVideoFrame{@link #IVideoProcessor#processVideoFrame} to preprocess the video frames collected by the RTC SDK, and use the processed video frames for RTC audio & video communication.
      * @param  [in] processor Custom video processor. See IVideoProcessor{@link #IVideoProcessor}. If null is passed in, the video frames captured by the RTC SDK are not preprocessed. <br>
      *        SDK only holds weak references to the processor, you should guarantee its Life Time.
      * @param  [in] config Customize the settings applicable to the video pre-processor. See VideoPreprocessorConfig{@link #VideoPreprocessorConfig}. <br>
      *                Currently, the 'required_pixel_format 'in'config' only supports: 'kVideoPixelFormatI420' and'kVideoPixelFormatUnknown ': <br>
      *                + When set to'kVideoPixelFormatUnknown', the RTC SDK gives the format of the video frame for processing by the processor, that is, the format of the acquisition.
      *                 You can get the actual captured video frame format and pixel type by frameType{@link #IVideoFrame#frameType} and pixelFormat{@link #IVideoFrame#pixelFormat}. <br>
      *                + When set to'kVideoPixelFormatI420 ', the RTC SDK converts the captured video frames into the corresponding format for pre-processing. This method call fails when <br>
      *                + Is set to another value.
      * @return  <br>
      *          + 0: Success. <br>
      *          +! 0: failure <br>
      * @notes   <br>
      *         + For Windows platforms, the preprocessed video frame format returned only supports'kVideoPixelFormatI420 '<br>
      *         + For Windows platforms, setting the required_pixel_format in'config' to'kVideoPixelFormatI420 'can bring some performance optimization by avoiding format conversion. <br>
      *         + When this interface is repeatedly called, only the last call takes effect. The effects do not stack.
      */
    virtual int registerLocalVideoProcessor(IVideoProcessor* processor, VideoPreprocessorConfig config) = 0;

    /** 
     * @hidden
     * @deprecated since 326.1, use sendSEIMessage instead
     * @type api
     * @region  video data callback
     * @brief  To register metadata observers to receive or send metadata. The underlying layer implements this function by adding SEI data to the video frame. <br>
     *         After registering an observer, there is no SEI information in the video frame sent, which will trigger onReadyToSendMetadata {@link
     *  #IMetadataObserver #onReadyToSendMetadata} Callback. <br> After registering an observer, the received video frame contains SEI information, which will trigger a receive
     * onMetadataReceived{@link #IMetadataObserver#onMetadataReceived} callback. <br>
     * @param  [in] observer Metadata observer, see: IMetadataObserver{@link #IMetadataObserver}
     * @notes   <br>
     *       + When using video custom capture and rendering, you can directly add and obtain metadata in the video frame. This interface is not recommended.
     *       + This interface supports dynamic unregistration, setting the parameter to nullptr to unregister. <br>
     */
    virtual void registerMetadataObserver(IMetadataObserver* observer) = 0;

    /** 
     * @type api
     * @region Video Management
     * @brief When video communication, SEI data is sent through video frames.This function is called when the streammain stream is an internal source and the camera is turned off. The SDK engine will construct a video black frame to send SEI information
     * @param  [in] stream_index Media stream type. See StreamIndex{@link #StreamIndex}
     * @param  [in] message SEI message. Length not exceeding 4 kB. <br>
     * @param  [in] length SEI message length. <br>
     * @param  [in] repeat_count Number of times the message was sent repeatedly. The value range is [0,30]. <br>
     *                    When this interface is called, SEI data is added to consecutive'repeatCount 'video frames starting with the current video frame.
     * @return  <br>
     *         + > = 0: The number of SEIs to be added to the video frame <br>
     *         + < 0: Send failed
     * @notes  <br>
     *         + You can use this interface to add SEI to the video frame collected internally by the RTC SDK. For video frames obtained by custom acquisition: if the original video frame does not add SEI data, you can call this interface to add SEI information to it for encoding and transmission; if the original video frame has added SEI data, then Call this interface does not take effect. <br>
     *         + If there is no video frame with SEI within 2s after calling this interface (for example, video capture and transmission are not turned on), then SEI data will not be added to the video frame.
     *         + After the message is sent successfully, the remote will receive an onSEIMessageReceived{@link #IRtcEngineEventHandler#onSEIMessageReceived} callback.
     *         + When sending SEI information with video black frames, please call this function at the frequency of 15/repeatcount FPS
     */
    virtual int sendSEIMessage(StreamIndex stream_index, const uint8_t* message, int length, int repeat_count) = 0;

    /** 
     * @hidden
     * @deprecated
     * @type api
     * @region room management
     * @brief Set the engine to automatically publish properties
     * @param  [in] engine
     *       For the engine to be set, see: IRtcEngine{@link #IRtcEngine}
     * @param  [in] auto_publish
     *       Whether to automatically publish streams, the default is true to automatically publish, when setting false, you can use engine- > publish (), engine- > unpublish () to publish and Unpublish local stream
     * @notes
     * Set whether the engine automatically publishes the user's local stream, which must be called before joinChannel. The default engine auto_publish is true. The engine- > publish (),
     * Engine- > unpublish () interfaces should not be called when the auto_publish is true.
     */
    virtual void enableAutoPublish(bool auto_publish) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Video Facility Management
     * @brief Create a video Facility Management instance
     * @return Video Facility Management instance. See IVideoDeviceManager{@link #IVideoDeviceManager}
     * @notes When the IVideoDeviceManager instance is no longer used, call the instance's release{@link #release}
     * Interface to avoid Resource leakage
     */
    virtual IVideoDeviceManager* getVideoDeviceManager() = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region audio management
     * @brief Device audio management interface creation
     * @return Audio Facility Management interface
     */
    virtual IAudioDeviceManager* getAudioDeviceManager() = 0;

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

    /** 
     * @hidden
     * @type api
     * @region audio data callback
     * @brief Register an audio data callback observer.
     * @param  [in] observer Audio data callback observer. See IRemoteAudioFrameObserver{@link #IRemoteAudioFrameObserver}
     * @notes   <br>
     *          Register the callback to receive PCM data from a single remote user.
     */
    virtual void registerRemoteAudioFrameObserver(IRemoteAudioFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region Local recording
     * @brief This method records the audio & video data during the call to a local file.
     * @param  [in] type Stream attribute, specify whether to record mainstream or screen stream. See StreamIndex{@link #StreamIndex}
     * @param  [in] config Local recording parameter configuration. See RecordingConfig{@link #RecordingConfig}
     * @param [in] recording_type Local recording media type. See RecordingType{@link #RecordingType}.
     * @return   <br>
     *         + 0: normal
     *         + -1: Parameter setting exception
     *         + -2: The current version of the SDK does not support this Feature, please contact technical support staff
     * @notes   <br>
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRtcEngineEventHandler#onRecordingStateUpdate} callback. <br>
     *         + If the recording is normal, the system will notify the recording progress through onRecordingProgressUpdate{@link #IRtcEngineEventHandler#onRecordingProgressUpdate}
     *  Callback every second.
     */
    virtual int startFileRecording(StreamIndex type, RecordingConfig config, RecordingType recording_type) = 0;

    /** 
     * @type api
     * @region local recording
     * @brief Stop local recording
     * @param  [in] type Stream attribute, specify to stop mainstream or screen stream recording. See StreamIndex{@link #StreamIndex}
     * @notes   <br>
     *         + Call startFileRecording{@link #IRtcEngine#startFileRecording} After starting local recording, you must call this method to stop recording. <br>
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRtcEngineEventHandler#onRecordingStateUpdate} callback prompting you to record the result.
     */
    virtual void stopFileRecording(StreamIndex type) = 0;
    /** 
     * @type api
     * @hidden(Linux)
     * @brief Enable the audio process mode for external sound card.
     * @param [in] enable <br>
     *        + true: enable <br>
     *        + false: disable (by default)
     * @notes   <br>
     *         + When you use external sound card for audio capture, enable this mode for better audio quality. <br>
     *         + When using the mode, you can only use earphones. If you need to use internal or external speaker, disable this mode.
     */
    virtual void enableExternalSoundCard(bool enable) = 0;

    /** 
     * @type api
     * @region Engine management
     * @brief Set runtime parameters
     * @param  [in] json_string String after json serialization
     * @notes
     */
    virtual void setRuntimeParameters(const char * json_string) = 0;

    /** 
     * @type api
     * @region speech recognition service
     * @brief Enables automatic speech recognition service. This method converts the recognized user's voice into text and calls it back to the user through the onMessage{@link #IRTCASREngineEventHandler#onMessage}
     *  Event.
     * @param  [in] asr_config Check information. See RTCASRConfig{@link #RTCASRConfig}
     * @param  [in] handler Speech recognition service usage status callback. See IRTCASREngineEventHandler{@link #IRTCASREngineEventHandler}
     */
    virtual void startASR(const RTCASRConfig& asr_config, IRTCASREngineEventHandler* handler) = 0;

    /** 
     * @hidden
     * @type api
     * @region  speech recognition service
     * @brief  Turn off speech recognition service
     */
    virtual void stopASR() = 0;
    /** 
     * @type api
     * @region Engine management
     * @brief Report the user feedback to RTC.
     * @param [in] type List of preset problems. See ProblemFeedbackOption{@link #ProblemFeedbackOption}
     * @param [in] count The length of `problemDesc`.
     * @param [in] problemDesc Specific description of other problems other than the preset problem
     * @return  <br>
     *          + 0: Report successfully <br>
     *          + -1: Failed to report, not yet joined the room <br>
     *          + -2: Failed to report, data analysis error <br>
     *          + -3: Failed to report, missing fields <br>
     * @notes If the user is in the room when reporting, the report leads to the room / rooms where the user is currently located;
     *        If the user is not in the room when reporting, the report leads to the previously exited Room.
     */
    virtual int feedback(ProblemFeedbackOption *type, int count, const char* problem_desc) = 0;

    /** 
     * @type api
     * @region  mixing
     * @brief  Mixing management interface creation
     * @return  Mixing management instance. See IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* getAudioMixingManager() = 0;

    /** 
     * @type api
     * @region Real-time messaging
     * @brief Log in to send P2P messages or send messages to a server without joining the RTC room.<br>
     *        To log out, call logout{@link #IRtcEngine#logout}. <br>
     * @param  [in] token <br>
     *        Token is required during login for authentication. <br>
     *        This Token is different from that required by calling joinRoom. You can assign any value even null to `roomId` to generate a login token. During developing and testing, you can use temporary tokens generated on the console. Deploy the token generating application on your server.
     * @param  [in] uid <br>
     *        User ID <br>
     *        User ID is unique within one appid.
     * @return <br>
     *        + `0`: Success<br>
     *        + `-1`: Failure due to invalid parameter<br>
     *        + `-2`: Invalid call. RTC will return this value when you call this API after the user has been logged in to the server. <br>
     * @notes  You will receive onLoginResult{@link #IRtcEngineEventHandler#onLoginResult}} after calling this API and log in successfully. But remote users will not receive notification about that.
     */
    virtual int64_t login(const char* token, const char* uid) = 0;
    /** 
     * @type After api
     * @region  real-time messaging
     * @brief  Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
     * @notes   <br>
     *        + Before calling this interface to log out, you must call login{@link #IRtcEngine#login} to log in. <br>
     *        + After local users call this method to log out, they will receive the result of the onLogout{@link #IRtcEngineEventHandler#onLogout} callback notification, and remote users will not receive the notification.
     */
    virtual void logout() = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Update the Token <br>
     *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
     *         When calling the login{@link #IRtcEngine#login} method to log in, if an expired token is used, the login will fail and you will receive an onLoginResult{@link #IRtcEngineEventHandler#onLoginResult} callback notification with an error code of kLoginErrorCodeInvalidToken. You need to reacquire the token and call this method to update the token.
     * @param  [in] token <br>
     *        Updated dynamic key
     * @notes   <br>
     *        + If the token is invalid and the login fails, call this method. After updating the token, the SDK will automatically log back in, and the user does not need to call the login{@link #IRtcEngine#login} method. <br>
     *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
     */
    virtual void updateLoginToken(const char* token) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     *        Client side calls sendServerMessage{@link #IRtcEngine#sendServerMessage} or sendServerBinaryMessage{@link #IRtcEngine#sendServerBinaryMessage} Before sending a message to the business server, a valid signature and business server address must be set.
     * @brief Set application server parameters   <br>
     * @param  [in] signature <br>
     *        Dynamic signature <br>
     *        The service server uses this signature to authenticate the request.
     * @param  [in] url <br>
     *         The address of the application server
     * @notes   <br>
     *        + The user must call login{@link #IRtcEngine#login} to log in before calling this interface. <br>
     *        + After calling this interface, the SDK will use onServerParamsSetResult{@link #IRtcEngineEventHandler#onServerParamsSetResult} to return the corresponding result.
     */
    virtual void setServerParams(const char* signature, const char* url) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Query the login status of the opposite or local user
     * @param  [in] peer_user_id <br>
     *        User ID to be queried
     * @notes   <br>
     *        + login{@link #IRtcEngine#login} must be called before this interface can be called. <br>
     *        + After calling this interface, the SDK notifies the query result using the onGetPeerOnlineStatus{@link #IRtcEngineEventHandler#onGetPeerOnlineStatus} callback. <br>
     *        + Before sending an out-of-room message, the user can know whether the peer user is logged in through this interface to decide whether to send a message. You can also check your login status through this interface.
     */
    virtual void getPeerOnlineStatus(const char* peer_user_id) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Send a text message (P2P) to a specified user outside the room
     * @param  [in] uid <br>
     *        Message receiving user's ID
     * @param  [in] message <br>
     *        Text message content sent <br>
     *        Message does not exceed 62KB.
     * @param [in] config Message type, see MessageConfig{@link #MessageConfig}.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @notes   <br>
     *        + You must call login{@link #IRtcEngine#login} to complete the login before you can send a message in a foreign text of the room. <br>
     *        + After the user calls this interface to send a text message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageSendResultOutsideRoom} callback to know whether the message was successfully sent. <br>
     *        + If the text message is sent successfully, the user specified by uid receives the message via the onUserMessageReceivedOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageReceivedOutsideRoom} callback.
     */
    virtual int64_t sendUserMessageOutsideRoom(const char* uid, const char* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Send binary messages (P2P) to a specified user outside the room
     * @param  [in] uid <br>
     *        ID of the user receiving the message
     * @param  [in] length <br>
     *        Length of the binary string
     * @param  [in] message <br>
     *        Content of the binary message sent <br>
     *        Message does not exceed 46KB.
     * @param [in] config Message type, see MessageConfig{@link #MessageConfig}.
     * @return   <br>
     *         + > 0: sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created <br>
     *         + -2: Sent failed, uid is empty
     * @notes   <br>
     *        + login{@link #IRtcEngine#login} must be called before sending out-of-room binary messages. <br>
     *        + After the user calls this interface to send a binary message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRtcEngineEventHandler#onUserMessageSendResultOutsideRoom} callback to notify whether the message was sent successfully. <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the message through the onUserBinaryMessageReceivedOutsideRoom{@link #IRtcEngineEventHandler#onUserBinaryMessageReceivedOutsideRoom} callback.
     */
    virtual int64_t sendUserBinaryMessageOutsideRoom(const char* uid, int length, const uint8_t* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief The client side sends a text message to the application server (P2Server)
     * @param  [in] message <br>
     *        The content of the text message sent <br>
     *        The message does not exceed 62KB.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created
     * @notes   <br>
     *        + Before sending a text message to the business server, you must first call login{@link #IRtcEngine#login} to complete the login, and then call setServerParams {@link # IRtcEngineLite #setServerParams} Set up the business server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRtcEngineEventHandler#onServerMessageSendResult} callback to inform the message sender whether the message was sent successfully. <br>
     *        + If the text message is sent successfully, the business server that previously called setServerParams{@link #IRtcEngine#setServerParams} will receive the message.
     */
    virtual int64_t sendServerMessage(const char* message) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Client side sends binary messages to the application server (P2Server)
     * @param  [in] length <br>
     *        Length of binary string
     * @param  [in] message <br>
     *        Binary message content sent <br>
     *        Message does not exceed 46KB.
     * @return   <br>
     *         + > 0: Sent successfully, return the number of the sent message, increment from 1 <br>
     *         + -1: Sent failed, RtcEngine instance not created
     * @notes   <br>
     *        + Before sending a binary message to the business server, you must first call login{@link #IRtcEngine#login} to complete the login, and then call setServerParams{@link #IRtcEngine#setServerParams} Set up the business server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRtcEngineEventHandler#onServerMessageSendResult} callback to inform the message sender that the sending succeeded or failed. <br>
     *        + If the binary message is sent successfully, the business server that previously called setServerParams{@link #IRtcEngine#setServerParams} will receive the message.
     */
    virtual int64_t sendServerBinaryMessage(int length, const uint8_t* message) = 0;

    /** 
     * @type api
     * @region Pre-call network detection
     * @brief Pre-call network detection
     * @param  [in] is_test_uplink Whether to detect uplink bandwidth
     * @param  [in] expected_uplink_bitrate Expected uplink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
     * @param  [in] is_test_downlink Whether to detect downlink bandwidth
     * @param  [in] expected_downlink_biterate Expected downlink bandwidth, unit: kbps<br>Range: {0, [100-10000]}, `0`: Auto, that RTC will set the highest bite rate.
     * @return   <br>
     *         + > 0: Start probe successful <br>
     *         + -1: Start probe failed. Parameter error, both uplink and downlink probes are false, or the expected bandwidth exceeds the range [100,10000] <br>
     *         + -2: Failed to start probing. Push-pull flow has started <br>
     *         + -3: Probe has started <br>
     * @notes   <br>
     *        + After calling this interface, you will receive onNetworkDetectionResult{@link #IRtcEngineEventHandler#onNetworkDetectionResult} callback notifying the probe result; <br>
     *        + If the probe stops, you will receive onNetworkDetectionStopped{@link #IRtcEngineEventHandler#onNetworkDetectionStopped} notify that probing has stopped.
     */
    virtual NetworkDetectionStartReturn startNetworkDetection(bool is_test_uplink, int expected_uplink_bitrate,
                                   bool is_test_downlink, int expected_downlink_biterate) = 0;

    /** 
     * @type api
     * @region Pre-call network probe
     * @brief Stop pre-call network probe
     * @notes   <br>
     *        + After calling this interface, you will receive onNetworkDetectionStopped{@link #IRtcEngineEventHandler#onNetworkDetectionStopped} notifying that the the probing has stopped.
     */
    virtual void stopNetworkDetection() = 0;

    /** 
     * @hidden (Android, iOS)
     * @type api
     * @region Screen sharing
     * @brief Set the screen audio acquisition method (internal acquisition/custom acquisition)
     * @param  [in] source_type Screen audio input source type. See AudioSourceType{@link #AudioSourceType}
     * @notes   <br>
     *       + The default acquisition method is internal to the RTC SDK Collect. <br>
     *       + You should call this method before publishScreen{@link #IRTCRoom#publishScreen}. Otherwise, you will receive an error from onWarning{@link #IRtcEngineEventHandler#onWarning}: 'kWarningCodeSetScreenAudioSourceTypeFailed' <br>
     *       + If it is set to internal collection, you must call startScreenAudioCapture{@link #IRtcEngine#startScreenAudioCapture} to start collection; <br>
     *       + If it is set to custom collection, you must call pushScreenAudioFrame{@link #IRtcEngine#pushScreenAudioFrame} to customize the collected screen audio frame Push to the RTC SDK. <br>
     *       + Whether it is an internal capture or a custom capture, you must call publishScreen{@link #IRTCRoom#publishScreen} to push the captured screen audio to the remote end.
     */
    virtual void setScreenAudioSourceType(AudioSourceType source_type) = 0;

    /** 
     * @type api
     * @region Screen sharing
     * @brief Set the mixing mode of the screen audio stream and the audio stream collected by the microphone when the screen is shared
     * @param  [in] index The mixing mode. See StreamIndex{@link #StreamIndex} <br>
     *         + 'kStreamIndexMain': Mix the audio stream collected by the screen audio stream and the microphone <br>
     *         + 'KStreamIndexScreen ': Divide the screen audio stream and the audio stream collected by the microphone into two audio streams
     * @notes You should call this method before publishScreen{@link #IRTCRoom#publishScreen}. Otherwise, you will receive an error from onWarning{@link #IRtcEngineEventHandler#onWarning} ': kWarningCodeSetScreenAudioStreamIndexFailed'
     */
    virtual void setScreenAudioStreamIndex(StreamIndex index) = 0;

    /** 
     * @hidden (Android, iOS, Linux)
     * @type api
     * @region screen sharing
     * @brief When sharing the screen, start using RTC SDK internal collection method to collect screen audio
     * @notes  <br>
     *         + After collection, you also need to call publishScreen{@link #IRTCRoom#publishScreen} to collect the screen audio Push to the far end. <br>
     *         + To turn off screen audio internal capture, call stopScreenAudioCapture{@link #IRtcEngine#stopScreenAudioCapture}.
     */
    virtual void startScreenAudioCapture() = 0;

   /** 
    * @hidden (Android, iOS, Linux)
    * @type api
    * @region Screen sharing
    * @brief Stop using RTC SDK internal acquisition method to capture screen audio during screen sharing.
    * @notes To start the screen audio internal capture, call startScreenAudioCapture{@link #IRtcEngine#startScreenAudioCapture}.
    */
    virtual void stopScreenAudioCapture() = 0;

    /** 
     * @type api
     * @region Screen Sharing
     * @brief Using a custom capture method, when capturing screen audio during screen sharing, push the audio frame to the RTC SDK for encoding and other processing.
     * @param  [in] frame Audio data frame. See IAudioFrame{@link #IAudioFrame}
     * @return  Method call result   <br>
     *         + 0: Setup succeeded <br>
     *         + < 0: Setup failed <br>
     * @notes   <br>
     *         + Before calling this interface to push custom collected audio data during screen sharing, you must call setScreenAudioSourceType{@link #IRtcEngine#setScreenAudioSourceType} Enable custom capture of screen audio. <br>
     *         + You should call this method every 10 milliseconds to push a custom captured audio frame. A push audio frame should contain frame.sample _rate/100 audio sample points. For example, if the sampling rate is 48000Hz, 480 sampling points should be pushed each time. <br>
     *         + The audio sampling format is S16. The data format in the audio buffer must be PCM data, and its capacity size should be samples × frame.channel × 2. <br>
     *         + This function runs within user-level threads. If other processes are running at the same time, this process will be interrupted. <br>
     *         + After calling this interface to push the custom captured audio frame to the RTC SDK, you must call publishScreen{@link #IRTCRoom#publishScreen} to push the captured screen audio to the remote end. Audio frame information pushed to the RTC SDK is lost before calling publishScreen{@link #IRTCRoom#publishScreen}.
     */
    virtual int pushScreenAudioFrame(IAudioFrame* frame) = 0;


    /** 
     * @hidden
     * @type api
     * @deprecated since 327.1, use stopScreenVideoCapture instead
     * @region Screen sharing
     * @brief Stop screen or window sharing.
     * @notes   <br>
     *        + This function must be called after startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} <br>
     *        + This function cannot be mixed with publishScreen{@link #IRTCRoom#publishScreen}, unpublishScreen{@link #IRTCRoom#unpublishScreen}. <br>
     */
    virtual void stopScreenCapture() = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region  screen sharing
     * @brief  set extension configuration
     * @param groupId  App and extension should belong to the same app group. Group ID needs to be passed in here
     * @notes this function must be called immediately after the sharedenginewithappid function <br>
     *                If it is not called or the call time is late, local users will receive a callback to rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error: {@link #ByteRTCEngineDelegate #rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error:}. <br>
     *                Parameter  device_state value is ByteRTCMediaDeviceStateStopped, device_error value is ByteRTCMediaDeviceErrorNotFindGroupId
     */
    virtual void setExtensionConfig(const char* group_id) = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region  screen sharing
     * @brief send screen sharing extension program message
     * @param message:  Message content sent to extension program
     * @param size : size of message
     * @notes This function must be called after the startScreenCapture function
     */
    virtual void sendScreenCaptureExtensionMessage(const char* message, size_t size) = 0;

    /** 
     * @hidden (macOS,Windows,Android,Linux)
     * @type api
     * @region  screen sharing
     * @brief  start local screen shared data collection
     * @param type screen shared data collection type
     * @param bundleId the bundle ID of the broadcast upload extension passed in, which is used to display the extension preferentially in settings
     * @notes when the extension is started abnormally from the IOS control center, you don't need to call this function <br>
     *       local users will receive a callback to rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error: {@link #ByteRTCEngineDelegate #rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error:}. <br>
     *       Parameter  device_state value is ByteRTCMediaDeviceStateStarted, device_error value is ByteRTCMediaDeviceErrorOK
     */
    virtual void startScreenCapture(ScreenMediaType type, const char* bundle_id) = 0;

    /** 
     * @hidden (macOS, Windows, iOS, Linux)
     * @type api
     * @region  Screen sharing
     * @brief  Start to capture screen audio/video through the incoming Type and Context.
     * @param [in] type
     *        specifying the media type of screen capture，see ScreenMediaType{@link #ScreenMediaType}
     * @param  [in] context
     *        Android platform incoming Intent object, obtained by the business party after applying for system recording permission.
     * @notes  <br>
     *        + After collection, you also need to call publishScreen {@link #IRtcRoom #publishScreen} to collect the screen audio/vieo Push to the far end. <br>
     *        + Enable internal screen audio/video capture, Android-specific interface.
     */
    virtual void startScreenCapture(ScreenMediaType type, void* context) = 0;

    /** 
     * @hidden (macOS,Windows,Linux)
     * @type api
     * @region  screen sharing
     * @brief  update screen acquisition data type
     * @param type screen acquisition data type
     * @notes  this function must be called after the startScreenCapture function.
     *        local users will receive a callback to rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error: {@link #ByteRTCEngineDelegate #rtcEngine: onMediaDeviceStateChanged: deviceType: device_state: device_error:}. <br>
     *        Parameter  device_state value is ByteRTCMediaDeviceStateStarted or ByteRTCMediaDeviceStateStopped, device_error value is ByteRTCMediaDeviceErrorOK
     */
    virtual void updateScreenCapture(ScreenMediaType type) = 0;


     /** 
      * @type api
      * @region Audio Management
      * @brief Enable audio information prompts.   <br>
      * @param config See AudioPropertiesConfig{@link #AudioPropertiesConfig}
      * @notes After enable the prompt, you can:   <br>
      *        + Get the information of the audio stream collected by the local microphone and screen audio stream through onLocalAudioPropertiesReport{@link #IRtcEngineEventHandler#onLocalAudioPropertiesReport}; <br>
      *        + Get the information of the subscribed remote audio streams through onRemoteAudioPropertiesReport{@link #IRtcEngineEventHandler#onRemoteAudioPropertiesReport}.
      */
    virtual void enableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;
    /** 
     * @type api
     * @region Audio Management
     * @brief Enables/disables the loudness equalization function.  <br>
     *        If you call this API with the parameter set to True, the loudness of user's voice will be adjusted to -16lufs. If then you also call setAudioMixingLoudness{@link #IAudioMixingManager#setAudioMixingLoudness} and import the original loudness of the audio data used in audio mixing, the loudness will be adjusted to -20lufs when the audio data starts to play.
     * @param [in] enable Whether to enable loudness equalization funcion:  <br>
     *        + True: Yes <br>
     *        + False: No
     * @notes You must call this API before starting to play the audio file with startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */
    virtual void enableVocalInstrumentBalance(bool enable) = 0;
    /** 
     * @type api
     * @region Audio Management
     * @brief Enables/disables the playback ducking function. This function is usually used in scenarios such as "Watch Videos Together".  <br>
     *        With the function on, if remote voice is detected, the local media volume will be lowered to ensure the clarity of the remote voice. If remote voice disappears, the local media volume restores.
     * @param enable Whether to enable playback ducking:  <br>
     *        + True: Yes  <br>
     *        + False: No
     */
    virtual void enablePlaybackDucking(bool enable) = 0;
    /** 
     * @type api
     * @region Video Data Callback
     * @brief Register a local video frame observer.   <br>
     *        This method applys to both internal capturing and custom capturing.  <br>
     *        After calling this API, SDK triggers onLocalEncodedVideoFrame{@link #ILocalEncodedVideoFrameObserver#onLocalEncodedVideoFrame} whenever a video frame is captured.
     * @param [in] observer Local video frame observer. See ILocalEncodedVideoFrameObserver{@link #ILocalEncodedVideoFrameObserver}. You can cancel the registration by setting it to `nullptr`.
     * @notes You can call this API before or after entering the RTC room. Calling this API before entering the room ensures that video frames are monitored and callbacks are triggered as early as possible.
     */
    virtual void registerLocalEncodedVideoFrameObserver(ILocalEncodedVideoFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region  video management
     * @brief  Video data callback after registering remote encoding.   <br>
     *         After registration, when the SDK detects a remote encoded video frame, it will trigger the onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame} callback
     * @param  [in] observer Remote encoded video data monitor. See IRemoteEncodedVideoFrameObserver{@link #IRemoteEncodedVideoFrameObserver}
     * @notes   <br>
     *        + This method needs to be called before entering the room. <br>
     *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
     */
    virtual void registerRemoteEncodedVideoFrameObserver(IRemoteEncodedVideoFrameObserver* observer) = 0;

    /** 
     * @type api
     * @region Video management
     * @brief Register custom encoded frame push event callback
     * @param  [in] encoder_handler Custom encoded frame callback class. See IExternalVideoEncoderEventHandler{@link #IExternalVideoEncoderEventHandler}
     * @notes   <br>
     *        + This method needs to be called before entering the room. <br>
     *        + The engine needs to be unregistered before it is destroyed. Call this method to set the parameter to nullptr.
     */
    virtual void setExternalVideoEncoderEventHandler(IExternalVideoEncoderEventHandler* encoder_handler) = 0;

    /** 
     * @type api
     * @region  video management
     * @brief  Push custom encoded video stream
     * @param  [in] index The attributes of the encoded stream that need to be pushed. See StreamIndex{@link #StreamIndex}
     * @param  [in] video_index The corresponding encoded stream subscript, starting from 0, if you call setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} to set multiple streams, the number here must be consistent with it
     * @param  [in] video_stream Encoded stream video frame information. See IEncodedVideoFrame{@link #IEncodedVideoFrame}. <br>
     * @notes   <br>
     *         + Currently, only video frames in H264 and ByteVC1 formats are supported, and the video stream protocol must be in an Annex B format. <br>
     *         + This function runs within the user calling thread <br>
     *         + Before pushing a custom encoded video frame, you must call setVideoSourceType{@link #IRtcEngine#setVideoSourceType} to switch the video input source to the custom encoded video source.
     */
    virtual bool pushExternalEncodedVideoFrame(StreamIndex index, int video_index, IEncodedVideoFrame* video_stream) = 0;

    /** 
     * @type api
     * @region Video Management
     * @brief Before subscribing to the remote video stream, set the remote video data decoding method
     * @param  [in] key The remote stream information, that is, which video stream is decoded. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @param  [in] config Video decoding method. See VideoDecoderConfig{@link #VideoDecoderConfig}.
     * @notes   <br>
     *         + This method is suitable for manual subscription mode and is used before subscribing to remote flows. <br>
     *         + When you want to custom decode a remote stream, you need to call registerRemoteEncodedVideoFrameObserver{@link #IRtcEngine#registerRemoteEncodedVideoFrameObserver} to register the remote video stream monitor, and then call the interface to set the decoding method to custom decoding. The monitored video data will be called back through onRemoteEncodedVideoFrame{@link #IRemoteEncodedVideoFrameObserver#onRemoteEncodedVideoFrame}.
     */
    virtual void setVideoDecoderConfig(RemoteStreamKey key, VideoDecoderConfig config) = 0;

    /** 
     * @type api
     * @region Video Management
     * @brief After subscribing to the remote video stream, request the key frame to the remote
     * @param  [in] stream_info The remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     * @notes   <br>
     *         + This method is only suitable for manual subscription mode and is used after successful subscription to the remote flow. <br>
     *         + This method is suitable for calling setVideoDecoderConfig{@link #IRtcEngine#setVideoDecoderConfig} to turn on the custom decoding function, and the custom decoding fails
     */
    virtual void requestRemoteVideoKeyFrame(const RemoteStreamKey& stream_info) = 0;

    /** 
     * @type api
     * @region Audio management
     * @brief Send audio stream synchronization information. The message is sent to the remote end through the audio stream and synchronized with the audio stream. After the interface is successfully called, the remote user will receive a onStreamSyncInfoReceived{@link #IRtcEngineEventHandler#onStreamSyncInfoReceived} callback.
     * @param  [in] data Message content.
     * @param  [in] length Message length. Message length must be [1,16] bytes.
     * @param  [in] config For configuration of media stream information synchronization. See StreamSycnInfoConfig{@link #StreamSycnInfoConfig}.
     * @return   <br>
     *         + > = 0: Message sent successfully. Returns the number of successful sends. <br>
     *         + -1: Message sending failed. Message length greater than 16 bytes. <br>
     *         + -2: Message sending failed. The content of the incoming message is empty. <br>
     *         + -3: Message sending failed. This screen stream was not published when the message was synchronized through the screen stream. <br>
     *         + -4: Message sending failed. This audio stream is not yet published when you synchronize messages with an audio stream captured by a microphone or custom device, as described in ErrorCode{@link #ErrorCode}. <br>
     * @notes When using `kRoomProfileTypeLiveBroadcasting` as room profile, the data will be delivered. For other coom profiles, the data may be lost when the local user is muted.
     */
    virtual int sendStreamSyncInfo(const uint8_t* data, int32_t length, const StreamSycnInfoConfig& config) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Change local voice to a different key, mostly used in Karaoke scenarios.  <br>
     *        You can adjust the pitch of local voice such as ascending or descending with this method.
     * @param [in] pitch The value that is higher or lower than the original local voice within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
     *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
     *        Out of the value range, the setting fails and triggers onWarning{@link #IRtcEngineEventHandler#onWarning} callback, indicating `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` for invalid value setting with WarningCode{@link #WarningCode}.
     */
    virtual void setLocalVoicePitch(int pitch) = 0;

    /** 
     * @type api
     * @region Media stream management
     * @brief Control the playinging status of the local audio stream: play/not play   <br>
     * @param  [in] mute_state Playinging status to identify whether to play the local audio stream, see: MuteState {@link #MuteState}
     * @notes This method only controls the local audio The playinging state of the stream does not affect the local audio play device.
     */
    virtual void muteAudioPlayback(MuteState mute_state) = 0;

    /** 
     * @type api
     * @brief Subscribe the public stream<br>
     *        A user can call this method to subscribe a public stream whenever he/she is has joined the room or not.
     * @param [in] public_streamid ID of the public stream. If the stream has not been published then, the local client will receive the public stream once it starts publishing.
     * @return <br>
     *        + 0: Success. You will also be informed by onPlayPublicStreamResult{@link #IRtcEngineEventHandler#onPlayPublicStreamResult} 回调。<br>
     *        + !0: Failure because of invalid parameter or empty parameters.<br>
     * @notes  <br>
     *        + We recommend to bind a view for the public stream before calling this API to subscribe a public stream. <br>
     *              - Internal renderer: By calling setPublicStreamVideoCanvas{@link #IRtcEngine# setPublicStreamVideoCanvas} or <br>
     *              - Custom renderer: By calling setPublicStreamVideoSink{@link #IRtcEngine#setPublicStreamVideoSink}<br>
     *        + After calling this API, you will be informed once the first frame has been decoded successfully by onFirstPublicStreamVideoFrameDecoded{@link #IRtcEngineEventHandler#onFirstPublicStreamVideoFrameDecoded} and onFirstPublicStreamAudioFrame{@link #IRtcEngineEventHandler#onFirstPublicStreamAudioFrame}.<br>
     *        + If the public stream contains SEI information, you will be informed by onPublicStreamSEIMessageReceived{@link #IRtcEngineEventHandler#onPublicStreamSEIMessageReceived}.<br>
     *        + Call stopPlayPublicStream{@link #IRtcEngine#stopPlayPublicStream} to cancel subscribing the public stream.
     */
    virtual int startPlayPublicStream(const char* public_streamid) = 0;
    /** 
     * @type api
     * @brief Cancel subscribing the public stream.<br>
     *        Call this method to cancel subscribing to the public stream by calling startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream}.
     * @param [in] public_streamid ID of the public stream
     * @return
     *        + 0: Success<br>
     *        + !0: Failure<br>
     */

    virtual int stopPlayPublicStream(const char* public_streamid) = 0;
    /** 
     * @type api
     * @brief Assign a internal render view to the public stream
     * @param [in] public_streamid ID of the public stream
     * @param [in] canvas Internal render view. Refer to VideoCanvas{@link #VideoCanvas} for more details.
     * @return
     *        + 0: Success<br>
     *        + !0: Failure<br>
     */
    virtual int setPublicStreamVideoCanvas(const char* public_streamid, const VideoCanvas& canvas) = 0;
    /** 
     * @type api
     * @brief Assign a custom renderer to the public stream
     * @param [in] public_streamid ID of the public stream
     * @param [in] video_sink Custom renderer. Set to be `null` when you want to release the renderer. Refer to IVideoSink{@link #IVideoSink} for more details.
     * @return
     *        + 0: Success<br>
     *        + !0: Failure<br>
     */
    virtual void setPublicStreamVideoSink(const char* public_streamid, IVideoSink* video_sink,
                                          IVideoSink::PixelFormat format) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region Audio & Video Processing
     * @brief Adds watermark to designated video stream.
     * @param [in] index Targeting stream index of the watermark. See StreamIndex{@link #StreamIndex}.
     * @param [in] image_path File path of the watermark image. You can use the absolute path or the asset path(/assets/xx.png). The path should be less than 512 bytes. <br>
     *        The watermark image should be in PNG or JPG format.
     * @param [in] config Watermark configurations. See RTCWatermarkConfig{@link #RTCWatermarkConfig}.
     * @notes <br>
     *        + Call clearVideoWatermark{@link #IRtcEngine#clearVideoWatermark} to remove the watermark on the designated video stream. <br>
     *        + You can only add one watermark to one video stream. The newly added watermark replaces the previous one. You can call this API multiple times to add watermarks to different streams. <br>
     *        + You can call this API before and after joining room. <br>
     *        + If you mirror the preview, or the preview and the published stream, the watermark will also be mirrored locally, but the published watermark will not be mirrored. <br>
     *        + When you enable simulcast mode, the watermark will be added to all video streams, and it will scale down to smaller encoding configurations accordingly. <br>
     */
    virtual void setVideoWatermark(StreamIndex index, const char * image_path, RTCWatermarkConfig config) = 0;

    /** 
     * @hidden(Linux)
     * @type api
     * @region Audio & Video Processing
     * @brief  Removes video watermark from designated video stream.
     * @param  [in] index Targeting stream index of the watermark. See StreamIndex{@link #StreamIndex}.
     */
    virtual void clearVideoWatermark(StreamIndex index) = 0;

  /** 
     * @hidden
     * @type api
     * @region  multi-room
     * @brief  Leave and destroy the room created by calling createRtcRoom{@link #IRtcEngine#createRtcRoom}.
     */
    virtual void destroy() = 0;
    /** 
     * @hidden
     * @deprecated since 327.1, use setUserVisibility instead
     * @type api
     * @region multiroom
     * @brief To set the user persona. The default role is live streaming host.   <br>
     *        By setting different user personas, you can control the user's behavior in the room: <br>
     *         + Whether audio & video streams can be published; <br>
     *         + Whether the user himself is invisible in the room. <br>
     * @param  [in] role User persona. See UserRoleType{@link #UserRoleType}.
     * @notes   <br>
     *        + Users can call this method to set user persona before and after joining the room. <br>
     *        + In the room, after calling this method to successfully switch roles, other users in the room will receive corresponding callback notifications: <br>
     *            -When Switching from an invisible user to a live streaming host, other users in the room will receive onUserJoined{@link #IRTCRoomEventHandler#onUserJoined}; <br>
     *            -When Switching from a live streaming host to an invisible user, other users in the room will receive the corresponding callback notification The user receives onUserLeave{@link #onUserLeave}.
     */
    virtual void setUserRole(UserRoleType role) = 0;
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
     * @notes  When the Token expired, the user would be removed from the room. And you would get informed of  `ERROR_CODE_EXPIRED_TOKEN` by onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}}. Reacquire a token and call joinRoom{@link #IRTCRoom#joinRoom} with the token to rejoin the room.
     */
    virtual void updateToken(const char* token) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param [in] uid Message Receiving user ID
     * @param [in] message <br>
     *        The broadcast message sent by the user <br>
     *         Message does not exceed 62KB.
     * @param [in] config Message type, see MessageConfig{@link #MessageConfig}.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomMessageReceived{@link #IRTCRoomEventHandler#onRoomMessageReceived} callback.
     */
    virtual int64_t sendUserMessage(const char* uid, const char* message, MessageConfig config) = 0;
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
    virtual int64_t sendUserBinaryMessage(const char* uid, int length, const uint8_t* message, MessageConfig config) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Send broadcast messages to all other users in the room.
     * @param  [in] message <br>
     *        The binary broadcast message sent by the user <br>
     *        The message does not exceed 46KB.
     * @return The number of the message sent this time is incremented from 1.
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} callback.
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
     * @notes   <br>
     *        + Before sending in-room binary messages, you must call joinRoom{@link #IRTCRoom#joinRoom} to join the room. <br>
     *        + After calling this function, you get an onRoomMessageSendResult{@link #IRTCRoomEventHandler#onRoomMessageSendResult} callback. <br>
     *        + Other users in the same room receive an onRoomBinaryMessageReceived{@link #IRTCRoomEventHandler#onRoomBinaryMessageReceived} callback.
     */
    virtual int64_t sendRoomBinaryMessage(int size, const uint8_t* message) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1, use publishStream instead.
     * @type api
     * @region Multi-room
     * @brief Publish media streams in the current room.
     * @notes   <br>
     *        + Call this API to publish media streams in Multi-room mode. In this mode, the Auto-Publish is disabled by default.  <br>
     *        + An invisible user cannot publish media streams. Call setUserVisibility{@link #IRTCRoom#setUserVisibility} to change the visibility of a user.  <br>
     *        + Call publishScreen{@link #IRTCRoom#publishScreen} to start screen sharing.
     *        + Call startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms} to forward the published streams to the other rooms.
     *        + After publishing media streams by calling this API, the other users in the room will be informed via onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd}.
     */
    virtual void publish() = 0;
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
     * @hidden
     * @deprecated since 336.1, use unpublishStream instead.
     * @type api
     * @region Multi-room
     * @brief Stop publishing media streams in the room.
     * @notes   <br>
     *        + In Multi-room mode, call this API to stop publishing media streams after starting by calling publish{@link #IRTCRoom#publish}. <br>
     *        + After stop publishing media streams by calling this API, the other users in the room will be informed via onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove} callback notification.
     */
    virtual void unpublish() = 0;
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
     * @hidden
     * @deprecated since 327.1, use publishScreen without params instead
     * @type api
     * @region multiroom
     * @brief To publish local screen share streams to rooms.
     * @param  [in] parameters
     *        Screenshare stream encoding parameters. See ScreenParameters{@link #ScreenParameters}
     * @notes   <br>
     *        + This method is suitable for users who call the setUserVisibility{@link #IRTCRoom#setUserVisibility} method to make themselves visible. <br>
     *        + After this method is called to publish the local screen sharing flow, the user also needs to periodically call the pushScreenFrame {@link
     *  #IRtcEngineLite #pushScreenFrame} Method by setting a timed task to push the screen data that needs to be sent to the SDK. <br>
     *        + The remote receives the onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}
     * , onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} event. <br>
     *        + This function and the startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} function are mutually exclusive calls, which can be called after the
     * unpublishScreen{@link #unpublishScreen} function is called. <br>
     *        + After receiving the onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered} event, set the remote screen sharing view by calling the setRemoteVideoCanvas{@link #setRemoteVideoCanvas} or setRemoteVideoSink{@link #setRemoteVideoSink} function. <br>
     *        + Locally, you can call the setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} or setLocalVideoSink{@link #IRtcEngine#setLocalVideoSink} function to set the local screen share view. <br>
     *        + You can also get the original data source by registering the registerVideoFrameObserver{@link #registerVideoFrameObserver} video callback object to listen for the onLocalScreenFrame{@link #IVideoFrameObserver#onLocalScreenFrame} local screen video callback event and the onRemoteScreenFrame {@link #IVideoFrameObserver #onRemoteScreenFrame} remote screen share video callback event. <br>
     *        + This method can only be called after joinRoom{@link #IRTCRoom#joinRoom}. <br>
     *         + After calling this API, the other users in the room will receive onUserUnPublishStream{@link #IRtcEngineEventHandler#onUserUnPublishStream}.
     */
    virtual void publishScreen(const ScreenParameters& parameters) = 0;
    /** 
     * @hidden
     * @deprecated since 336.1
     * @type api
     * @region screen share
     * @brief publish local screen share streams to the room.
     * @notes   <br>
     *        + You must join the room before you can call this method. <br>
     *        + In live, game, cloud game room mode, only visible users can call this method. You can set the user's visibility in the room by calling the setUserVisibility{@link #IRTCRoom#setUserVisibility} method. <br>
     *        + This method only affects the publishing status of the screen shared video stream, and does not affect the collection of the screen video stream. You can capture in two ways: <br>
     *               - RTC SDK internal capture: see startScreenVideoCapture{@link #IRtcEngine#startScreenVideoCapture} and startScreenAudioCapture{@link #IRtcEngine#startScreenAudioCapture} <br>
     *               - RTC SDK external capture: you can capture the screen audio & video stream yourself and periodically call pushScreenFrame{@link #IRtcEngine#pushScreenFrame} and pushScreenAudioFrame{@link #IRtcEngine#pushScreenAudioFrame} Push the collected audio & video frames to the RTC SDK for encoding transmission. <br>
     *        + After successful publication, the remote will receive an onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} callback; if you call registerVideoFrameObserver{@link #registerVideoFrameObserver} to register a video frame callback observer, then you will also receive an onRemoteScreenFrame{@link #IVideoFrameObserver#onRemoteScreenFrame} callback.
     *        + Call unpublishScreen{@link #IRTCRoom#unpublishScreen} to cancel publishing.
     */
    virtual void publishScreen() = 0;
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
     * @hidden
     * @deprecated since 336.1
     * @type api
     * @region screen share
     * @brief Stop publishing local screen share streams to the room.
     * @notes The remote receives the onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove} event.
     * @notes   <br>
     *        + This method only affects the publishing status of the screen shared video stream, and does not affect the collection of the screen video stream. <br>
     *        + Call publishScreen{@link #IRTCRoom#publishScreen} to start publishing.
     */
    virtual void unpublishScreen() = 0;
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
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region multiroom
     * @brief To subscribe to the specified room remote audio & video stream.   <br>
     *         Turn off the automatic subscription function. When using the manual subscription mode, the user calls this method to subscribe to the audio & video stream in the room on demand. <br>
     *        This method only takes effect when the automatic subscription function is turned off. Users need to call the enableAutoSubscribe{@link #enableAutoSubscribe}
     *  Method to turn off the automatic subscription function before joining the room to use the manual subscription mode. <br> Users call this method when the automatic subscription function is turned on. The SDK does not subscribe to the audio & video stream, and notifies the user that the subscription failed through a
     * onRoomWarning{@link #onRoomWarning} callback with the callback warning code
     * kWarningCodeSubscribeStreamForbiden{@link #kWarningCodeSubscribeStreamForbiden}. <br> When the subscription stream fails, the SDK
     *  Will call back onRoomError{@link #onRoomError} according to the cause of the failure to notify the user. The specific error can be described by the error code ErrorCode {@link
     *  #ErrorCode}. <br>
     * @param  [in] user_id The user ID of the remote user that specifies the subscription. <br>
     * @param  [in] info Select the subscription configuration. See the data structure SubscribeConfig{@link #SubscribeConfig}. <br>
     * @notes   <br>
     *        + This method only supports subscribing to remote audio & video streams in the current room. If the specified stream does not exist in the current room, the SDK does not subscribe. <br>
     *        + After the user calls the joinRoom{@link #IRTCRoom#joinRoom} method to join the room: 1. When a new audio & video stream is released in the room, you will receive a onStreamAdd{@link #onStreamAdd} callback notification locally; 2. onStreamRemove {@link #onStreamRemove} callback notification is received locally when audio & video streams in the room stop publishing. Through these two callbacks, the user can obtain the audio & video stream information in the current room and call this method to subscribe to the audio & video stream when needed. <br>
     */
    virtual void subscribeStream(const char* user_id, const SubscribeConfig& info) = 0;
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
     *         + Get the media stream information in the room from onStreamAdd{@link #IRTCRoomEventHandler#onStreamAdd} and onStreamRemove{@link #IRTCRoomEventHandler#onStreamRemove}. <br>
     *         + If the subscription fails, you will receive onRoomError{@link #IRTCRoomEventHandler#onRoomError}. Refer to ErrorCode{@link #ErrorCode} for the specific reason of failure.
     *         + You can update the subscription configuration by calling the API even after calling pauseAllSubscribedStream{@link #IRTCRoom#pauseAllSubscribedStream} to pause streaming. Call resumeAllSubscribedStream{@link #IRTCRoom#resumeAllSubscribedStream} to resume streaming and apply the changes. <br>
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
     *        + You must first get the remote stream information through onUserPublishStream{@link #IRTCRoomEventHandler#onUserPublishStream} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
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
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
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
     *        + You must first get the remote stream information through onUserPublishScreen{@link #IRTCRoomEventHandler#onUserPublishScreen} before calling this API to subscribe to streams accordingly.  <br>
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
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
     *        + After calling this API, you will be informed of the calling result with onStreamSubscribed{@link #IRTCRoomEventHandler#onStreamSubscribed}.  <br>
     *        + Any other exceptions will be included in onStreamStateChanged{@link #IRTCRoomEventHandler#onStreamStateChanged}, see ErrorCode{@link #ErrorCode} for the reasons.
     */
    virtual void unsubscribeScreen(const char *user_id,MediaStreamType type) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Stop subscribing to the remote audio & video stream in the specified room.   <br>
     *         Turn off the automatic subscription function. When using the manual subscription mode, the user calls this method to stop subscribing to the subscribed audio & video stream. <br>
     *        This method only takes effect when the automatic subscription function is turned off. Users need to set config to turn off the automatic subscription function when joining the room to use the manual subscription mode. <br>
     * @param  [in] user_id Specifies the ID of the user who stopped subscribing to the remote audio & video stream. <br>
     * @param  [in] is_screen Specifies whether the stopped stream is a screen stream. <br>
     * @notes   <br>
     *        + You can call this method to stop the subscription regardless of whether you subscribe to the specified remote audio & video stream. Stop subscription stream_id invalid or unsubscribed, SDK will not do any processing, no negative impact. <br>
     */
    virtual void unsubscribe(const char* user_id, bool is_screen) = 0;
    /**
     * @hidden
     */
    virtual void enableSubscribeLocalStream(bool enable) = 0;
    /** 
     * @hidden
     * @deprecated Since 323.1, use onUserStartAudioCapture instead
     * @type api
     * @region multiroom
     * @brief To turn on/off volume prompts. Off by default. <br>
     *         When the volume prompt is turned on, you will receive a callback of the volume information of the remote user who collected the volume locally or subscribed at the set time interval.
     *         For specific information about the callback. See onAudioVolumeIndication{@link #IRTCRoomEventHandler#onAudioVolumeIndication}
     * @param  [in] interval The time interval for receiving the volume prxxompt callback: <br>
     *                 + ≤ 0: Disable the volume prompt function. <br>
     *                 + > 0: Enable the volume prompt function and set the time interval for receiving the volume prompt callback. In milliseconds. <br>
     *                 It is recommended to set to greater than or equal to 200 milliseconds; when less than 10 milliseconds, the behavior is undefined.
     */
    virtual void setAudioVolumeIndicationInterval(int interval) = 0;
    /** 
     * @type api
     * @region  multi-room
     * @brief  Adjust the audio playback volume from the remote user
     * @param user_id  The remote user ID of the audio source
     * @param volume  Playback volume, the value range: [0,400] <br>
     *               + 0: mute <br>
     *               + 100: original volume <br>
     *               + 400: Up to 4 times the original volume (with overflow protection) <br>
     */
    virtual void setRemoteAudioPlaybackVolume(const char* user_id, int volume) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
     * @type api
     * @region Multiroom
     * @brief  To set the reception status for all audio streams from the remote. The default is receive.
     * @param  [in] mute_state Reception status. See: MuteState{@link #MuteState}
     * @notes  This method only affects whether the remote audio stream is received locally, and does not affect the collection and transmission function of the remote audio device.
     */
    virtual void muteAllRemoteAudio(MuteState mute_state) = 0;
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
    /** 
     * @hidden
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region multiroom
     * @brief  To set the reception status of the audio stream from the remote specified user. The default is receive.
     * @param  [in] uid Specifies the ID of the remote user
     * @param  [in] mute_state Receiving state. See: MuteState{@link #MuteState}
     * @notes  This method only affects whether the remote audio stream is received locally, and does not affect the collection and transmission function of the remote audio device.
     */
    virtual void muteRemoteAudio(const char* uid, MuteState mute_state) = 0;
#ifndef ByteRTC_AUDIO_ONLY
    /**
     * @hidden
    */
    virtual void updateCloudRending(const char* cloudrenderJsonString) = 0;


    /** 
     * @type api
     * @region Multi-room
     * @brief Synchronizes published audio and video.  <br>
     *        When the same user simultaneously uses separate devices to capture and publish audio and video, there is a possiblity that the streams are out of sync due to the network disparity. In this case, you can call this API on the video publisher side and the SDK will automatically line the video stream up according to the timestamp of the audio stream, ensuring that the audio the receiver hears corresponds to the video the receiver watches.
     * @param [in] audio_user_id The ID of audio publisher. You can stop the current A/V synchronization by setting this parameter to null.
     * @notes  <br>
     *        + You can call this API anytime before or after entering the room.  <br>
     *        + The source user IDs of the audio and video stream to be synchronized must be in the same RTC room.  <br>
     *        + When the A/V synchronization state changes, you will receive onAVSyncStateChange{@link #IRTCRoomEventHandler#onAVSyncStateChange}}.  <br>
     *        + More than one pair of audio and video can be synchronized simultaneously in the same RTC room, but you should note that one single audio source cannot be synchronized with multiple video sources at the same time.  <br>
     *        + If you want to change the audio source, call this API again with a new `audio_user_id`. If you want to change the video source, you need to stop the current synchronization first, then call this API on the new video publisher side.
     */
    virtual void setMultiDeviceAVSync(const char* audio_user_id) = 0;


    /** 
     * @type api
     * @region Multi-room
     * @brief Create a new task of pushing media streams to CDN and sets the relevant configurations.  <br>
     *        When pushing more than one live streams in the same task, SDK will first mix those streams into one single stream and then push it to CDN.
     * @param [in] task_id Task ID. <br>
     *        You may want to push more than one mixed stream to CDN from the same room. When you do that, use different ID for corresponding tasks; if you will start only one task, use an empty string.
     * @param [in] param Configurations to be set when pushing streams to CDN. See ITranscoderParam{@link #ITranscoderParam}.
     * @param [in] observer Register this observer to receive callbacks from the SDK. See ITranscoderObserver{@link #ITranscoderObserver}.
     * @notes   <br>
     *       + After calling this API, you will be informed of the result and errors during the pushing process via the onStreamMixingEvent{@link #ITranscoderObserver#onStreamMixingEvent}} callback.
     *       + Call stopLiveTranscoding{@link #IRtcEngine#stopLiveTranscoding}} to stop pushing streams to CDN.
     */
    virtual void startLiveTranscoding(const char* task_id, ITranscoderParam* param, ITranscoderObserver* observer) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Stops pushing media streams to CDN. <br>
     *        For starting pushing media streams to CDN, see startLiveTranscoding{@link #IRtcEngine#startLiveTranscoding}}.
     * @param [in] task_id Task ID. Specifys which pushing task you want to stop.
     */
    virtual void stopLiveTranscoding(const char* task_id) = 0;
    /** 
     * @type api
     * @region Multi-room
     * @brief Update parameters needed when pushing media streams to CDN.  <br>
     *        After calling startLiveTranscoding{@link #IRtcEngine#startLiveTranscoding}} to enable the function of pushing streams to CDN, you can call this API to update the relevant configurations.
     * @param [in] task_id Task ID. Specifys of which pushing task you want to update the parameters.
     * @param [in] param Configurations that you want to update. See ITranscoderParam{@link #ITranscoderParam}.
     */
    virtual void updateLiveTranscoding(const char* task_id, ITranscoderParam* param) = 0;
    /** 
     * @deprecated  since 336, use setRemoteStreamVideoCanvas instead
     * @hidden
     * @type api
     * @region Multi-room
     * @brief Sets the view to be used for remote video rendering and the rendering mode. <br>
     *        If you need to unbind the remote video stream from the current view, you can set the canvas to `null`.
     * @notes   <br>
     * @param [in] user_id The ID of the remote user who published the video stream.
     * @param [in] index Video stream type. See StreamIndex{@link #StreamIndex}.
     * @param [in] canvas View information and rendering mode. See VideoCanvas{@link #VideoCanvas}.
     * @return  <br>
     *         + 0: Success <br>
     *         +!: Failure <br>
     * @notes  <br>
     *        + You should bind the stream to a view after entering the room. This setting will remain in effect after you leave the room. <br>
     *        + You can get the remote user ID in onFirstRemoteVideoFrameRendered{@link #IRtcEngineEventHandler#onFirstRemoteVideoFrameRendered}.
     */
    virtual void setRemoteVideoCanvas(const char* user_id, StreamIndex index, const VideoCanvas& canvas) = 0;
    /** 
     * @deprecated Since 325.1
     * @hidden
     * @type api
     * @region Multi-room
     * @brief Remove all remote videos.
     */
    virtual void removeAllRemoteVideo() = 0;
    /** 
     * @deprecated Since 325.1
     * @hidden
     * @type api
     * @region Multi-room
     * @brief Remove all remote views shared by the screen.
     */
    virtual void removeAllRemoteScreen() = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use pauseAllSubscribedStream/resumeAllSubscribedStream instead
     * @type api
     * @region Multi-room
     * @brief Set whether to play all remote video streams
     * @param   [in] muteState Reception status to identify whether to receive all remote audio/video streams. See MuteState{@link #MuteState} <br>
     *        + True: stop playing <br>
     *        + False: start playing <br>
     * @notes This method does not affect the remote video capture and transmission status
     */
    virtual void muteAllRemoteVideo(MuteState muteState) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use subscribeUserStream instead
     * @type api
     * @region Multi-room
     * @brief Set whether to play the remote video stream
     * @param  [in] userid The remote user ID of the video source
     * @param   [in] muteState Reception status to identify whether to receive the remote audio/video stream. See MuteState{@link #MuteState} <br>
     *        + True: stop playing <br>
     *        + False: turn on playback <br>
     * @notes  This method does not affect the remote video capture and transmission status
     */
    virtual void muteRemoteVideo(const char* userid, MuteState muteState) = 0;
#endif
    /**
     * @hidden
     */
    virtual void setCustomUserRole(const char* role) = 0;
    /** 
     * @hidden
     * @deprecated since 326.1, use joinRoom instead
     * @type api
     * @region multiroom
     * @brief To set the subscription mode.   <br>
     *        The user calls this method to set the subscription mode for audio & video streams in the room. The default is automatic subscription. <br>
     *        To enable the manual subscription function, it is recommended to complete the setting before calling the joinRoom{@link #IRTCRoom#joinRoom} method to join the room. <br>
     * @param  [in] audio_mode Subscription mode for audio streams. See SubscribeMode{@link #SubscribeMode}. <br>
     * @param  [in] video_mode Subscription mode for video streams. See SubscribeMode{@link #SubscribeMode}. <br>
     */
    virtual void enableAutoSubscribe(SubscribeMode audio_mode, SubscribeMode video_mode) = 0;
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
     * @brief Start publishing a public media stream.<br>
     *        A public stream refers to a media stream that does not belong to any room or any user. Users within the same `appID` can call startPlayPublicStream{@link #IRtcEngine#startPlayPublicStream} to subscribe to the public stream regardless the user has joined which room or has not joined any room.
     * @param public_stream_id ID of the pulbic stream
     * @param param Properties of the public stream. Refer to IPublicStreamParam{@link #IPublicStreamParam} for more details.<br>
     *              A public stream can include a bundle of media streams and appears as the designated layout.
     * @return
     *        + 0: Success. And you will be informed by onPushPublicStreamResult{@link #IRtcEngineEventHandler#onPushPublicStreamResult}. <br>
     *        + !0: Failure because of invalid parameter or empty parameters.<br>
     * @notes
     *        + Call updatePublicStreamParam{@link #IRtcEngine#updatePublicStreamParam} to update the properties of the public stream which is published by the same user. Calling this API with the same stream ID repeatedly by the same user can not update the existing public stream.<br>
     *        + If Users with different userID call this API with the same stream ID, the public stream will be updated with the parameters passed in the latest call.<br>
     *        + To publish multiple public streams, call this API with different stream ID respectively.<br>
     *        + To stop publishing the public stream, call stopPushPublicStream{@link #IRtcEngine#stopPushPublicStream}.
     */
    virtual int startPushPublicStream(const char* public_stream_id, IPublicStreamParam* param) = 0;
    /** 
     * @type api
     * @brief Stop the public stream published by the current user.<br>
     *        Refer to startPushPublicStream{@link #IRtcEngine#startPushPublicStream} for details about starting publishing a public stream.
     * @param public_stream_id ID of the public stream<br>
     *                  The public stream must be published by the current user.
     * @return
     *        + 0: Success<br>
     *        + !0: Failure<br>
     */
    virtual int stopPushPublicStream(const char* public_stream_id) = 0;
    /** 
     * @type api
     * @brief Update the properties of the public stream published by the current user.<br>
     *        Refer to startPushPublicStream{@link #IRtcEngine#startPushPublicStream} for details about starting publishing a public stream.
     * @param public_stream_id ID of the public stream<br>
     * @param param Properties of the public stream. Refer to IPublicStreamParam{@link #IPublicStreamParam} for more details.<br>
     *              The stream to be updated must be published by the current user.
     * @return
     *        + 0: Success<br>
     *        + !0: Failure<br>
     */
    virtual int updatePublicStreamParam(const char* public_stream_id, IPublicStreamParam* param) = 0;

    /** 
     * @type api
     * @region Network Management
     * @brief Starts a call test.  <br>
     *        Before entering the room, you can call this API to test whether your local audio/video equipment as well as the upstream and downstream networks are working correctly.  <br>
     *        Once the test starts, SDK will record your sound or video. If you receive the playback within the delay range you set, the test is considered normal.
     * @param [in] echo_test_config Test configurations, see EchoTestConfig{@link #EchoTestConfig}.
     * @param [in] play_delay_time Delayed audio/video playback time specifying how long you expect to receive the playback after starting the. The range of the value is [2,10] in seconds and the default value is 2.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + -1: Failure, testing in progress  <br>
     *        + -2: Failure, you are in the room  <br>
     *        + -3: Failure, neither video nor audio is captured  <br>
     *        + -4: Failure, Parameter exception  <br>
     *        + -5: Failure, the roomID is already used
     * @notes  <br>
     *        + Once you start the test, you can either call stopEchoTest{@link #IRtcEngine#stopEchoTest} or wait until the test stops automatically after 60s, to start the next test or enter the room.  <br>
     *        + All APIs related to device control and stream control called before this API are invalidated during the test and are restored after the test.  <br>
     *        + All APIs related to device control, stream control, and room entry called during the test do not take effect, and you will receive onWarning{@link #IRtcEngineEventHandler#onWarning} with the warning code `kWarningCodeInEchoTestMode`.
     *        + You will receive the test result from onEchoTestResult{@link #IRtcEngineEventHandler#onEchoTestResult}.
     */
    virtual int startEchoTest(EchoTestConfig echo_test_config, unsigned int play_delay_time) = 0;

    /** 
     * @type api
     * @region Network Management
     * @brief Stop the current call test.  <br>
     *        After calling startEchoTest{@link #IRtcEngine#startEchoTest}, you must call this API to stop the test.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + -1: Failure, no test is in progress
     * @notes After stopping the test with this API, all the system devices and streams are restored to the state they were in before the test.
     */
    virtual int stopEchoTest() = 0;

    /** 
     * @type api
     * @region  cloud proxy
     * @brief  Start cloud proxy
     * @param  [in] configuration cloud proxy informarion list. See CloudProxyConfiguration{@link #CloudProxyConfiguration}.
     * @notes   <br>
     *         + Call this API before joining the room.<br>
     *         + Start pre-call network detection after starting cloud proxy. <br>
     *         + After starting cloud proxy and connects the cloud proxy server successfully, receives onCloudProxyConnected{@link #IRtcEngineEventHandler#onCloudProxyConnected}. <br>
     *         + To stop cloud proxy, call stopCloudProxy{@link #IRtcEngine#stopCloudProxy}.
     */
    virtual void startCloudProxy(const CloudProxyConfiguration& configuration) = 0;
    /** 
     * @type api
     * @region  cloud proxy
     * @brief  Stop cloud proxy
     * @notes To start cloud proxy, call startCloudProxy{@link #IRtcEngine#startCloudProxy}}.
     */
    virtual void stopCloudProxy() = 0;

};

/** 
 * @type api
 * @region Engine Management
 * @brief Create an engine instance.   <br>
 *        This is the very first API that you must call if you want to use all the RTC capabilities.  <br>
 *        If there is no engine instance in current thread, calling this API will create one. If an engine instance has been created, calling this API again will create another instance.
 * @param [in] app_id A unique identifier for each App, randomly generated by the RTC console. Only instances created with the same app_id are able to communicate with each other.
 * @param [in] event_handler Handler sent from SDK to App. See IRtcEngineEventHandler{@link #IRtcEngineEventHandler}.
 * @param [in] parameters Reserved parameter, in JSON string format.
 * @return  <br>
 *        + IRtcEngine：A successfully created engine instance  <br>
 *        + Null：Creation failed
 * @notes   <br>
 *         + If you create multiple engine instances in the same thread, you must destroy each of these instances by calling destroyRtcEngine{@link #destroyRtcEngine}.
 *         + The number of engine instances created on a Linux platform depends on the hardware performance of the system.
 */
BYTERTC_API bytertc::IRtcEngine* createRtcEngine(const char* app_id,
        bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/** 
 * @hidden
 * @region Engine Management
 * @brief Create a game RTCEngine instance.
 * @param  [in] app_id <br>
 *         A unique device identifier for each application. Instances generated by different AppIDs are completely independent for audio & video calls and cannot communicate with each other.
 * @param  [in] event_handler <br>
 *        SDK callback to the Callback object at the application layer. See IRtcEngineEventHandler{@link #IRtcEngineEventHandler}.
 * @param  [in] parameters Preserve the parameters
 * @return  Available IRtcEngine{@link #IRtcEngine} instances.
 * @notes   <br>
 *         + This method creates and initializes an IRtcEngine{@link #IRtcEngine} instance. With IRtcEngine, you must first call the interface for initialization. The <br>
 *         + IRtcEngine{@link #IRtcEngine} instance notifies the application engine runtime event via the specified IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          . All methods defined in IRtcEngineEventHandler{@link #IRtcEngineEventHandler} are optional implementations.
 */
BYTERTC_API bytertc::IRtcEngine* createGameRtcEngine(const char* app_id,
        bytertc::IRtcEngineEventHandler* event_handler, const char* parameters);

/** 
 * @hidden
 * @region Engine management
 * @brief Create RTCEngine instances.
 * @param  [in] app_id <br>
 *         A unique device identifier for each application. Instances generated by different AppIDs are completely independent for audio & video calls and cannot communicate with each other.
 * @param  [in] event_handler <br>
 *        SDK callback to the Callback object at the application layer. See IRtcEngineEventHandler{@link #IRtcEngineEventHandler}.
 * @param  [in] parameters Preserve the parameters
 * @return  Available IRtcEngine{@link #IRtcEngine} instances.
 * @notes   <br>
 *         + This method creates and initializes an IRtcEngine{@link #IRtcEngine} instance. With IRtcEngine, you must first call the interface for initialization. The <br>
 *         + IRtcEngine{@link #IRtcEngine} instance notifies the application engine runtime event via the specified IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          . All methods defined in IRtcEngineEventHandler{@link #IRtcEngineEventHandler} are optional implementations.
 */
BYTERTC_API bytertc::IRtcEngine* createRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);

/** 
 * @hidden
 * @region Engine Management
 * @brief Create a game RTCEngine instance.
 * @param  [in] app_id <br>
 *         A unique device identifier for each application. Instances generated by different AppIDs are completely independent for audio & video calls and cannot communicate with each other.
 * @param  [in] event_handler <br>
 *        SDK callback to the Callback object at the application layer. See IRtcEngineEventHandler{@link #IRtcEngineEventHandler}.
 * @param  [in] parameters Preserve the parameters
 * @return  Available IRtcEngine{@link #IRtcEngine} instances.
 * @notes   <br>
 *         + This method creates and initializes an IRtcEngine{@link #IRtcEngine} instance. With IRtcEngine, you must first call the interface for initialization. The <br>
 *         + IRtcEngine{@link #IRtcEngine} instance notifies the application engine runtime event via the specified IRtcEngineEventHandler{@link #IRtcEngineEventHandler}
 *          . All methods defined in IRtcEngineEventHandler{@link #IRtcEngineEventHandler} are optional implementations.
 */
BYTERTC_API bytertc::IRtcEngine* createGameRtcEngineWithPtr(
        const char* app_id, std::unique_ptr<bytertc::IRtcEngineEventHandler> event_handler,
        const char* parameters);
/** 
 * @type api
 * @region Engine Management
 * @brief Destroy the engine instance created by createRtcEngine{@link #createRtcEngine}, and release all related resources.
 * @param [in] engine The engine instance created by createRtcEngine{@link #createRtcEngine}
 * @notes  <br>
 *         + Call this API after all business scenarios related to the engine instance are destroyed. In a multi-thread scenario, you must not call IRtcEngine{@link #IRtcEngine} related APIs after calling this interface, or the SDK may crash. When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *         + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete. Therefore, do not call this API directly in the callback thread, or wait for the execution of the main thread in the callback and call this API in the main thread at the same time. Otherwise, it will cause a deadlock.
 */    
BYTERTC_API void destroyRtcEngine(bytertc::IRtcEngine* engine);

/** 
 * @hidden
 * @region Engine Management
 * @brief Destroy the game RTCEngine instance created by createGameRtcEngine{@link #createGameRtcEngine} and release all related resources.
 * @param  [in] engine <br>
 *         The instance returned by createGameRtcEngine{@link #createGameRtcEngine}.
 * @notes   <br>
 *         + Make sure that this method is called in the last stage of all business scenarios. <br>
 *         + After this method is called, it will destroy all SDK-related memory and stop any interaction with the media server. <br>
 *         + Any settings made to the SDK after the last createGameRtcEngine{@link #createGameRtcEngine} call,
 *           Will take effect the next time createGameRtcEngine{@link #createGameRtcEngine} is effectively executed. <br>
 *         + This method is a blocking call, which will block the current thread until the SDK completes the exit logic completely. Therefore, care should be taken not to call this method directly in the callback thread, and care should also be taken not to wait for the main thread in the callback method. Execution while calling this method in the main thread, thus causing a deadlock.
 */
BYTERTC_API void destroyGameRtcEngine(bytertc::IRtcEngine* engine);

/** 
 * @type api
 * @region  error code
 * @brief  Get the description of the error code
 * @param  [in] code Needs to get the description of the error code
 * @return  The description of the error code
 * @notes  This interface is a general function and does not need to rely on the engine object when calling.
 */
BYTERTC_API const char* getErrorDescription(int code);

/** 
 * @type api
 * @region  engine management
 * @brief  Get the current SDK version information.
 * @return Current SDK version information.
 */
BYTERTC_API const char* getSDKVersion();

}    // namespace bytertc

#endif  // BYTE_RTC_INTERFACE_H__
