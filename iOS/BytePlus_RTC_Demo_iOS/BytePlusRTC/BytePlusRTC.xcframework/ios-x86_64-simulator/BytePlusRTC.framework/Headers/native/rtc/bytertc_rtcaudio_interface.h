/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief audio engine Interface
 */

#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include "bytertc_audio_frame.h"
#include "bytertc_audio_mixing_manager.h"
#include "byte_rtc_asr_engine_event_handler.h"
#include "bytertc_audio_device_manager.h"

#include "bytertc_audio_room_interface.h"
#include "bytertc_rtcaudio_event_handler.h"

namespace bytertc {
/** 
 * @type api
 * @brief Engine API
 */
class IRTCAudio {
public:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRTCAudio() {}

    /** 
     * @type api
     * @region  engine management
     * @brief  Sets business identity parameters.   <br>
     *         You can distinguish different business scenarios (roles/policies, etc.) through business_id. Business_id customized by the customer, equivalent to a "label",
     *         Can share and refine the functionality of the logical division of the current AppId.
     * @param  [in] business_id <br>
     *         The user's own business_id value. Business_id is equivalent to a sub AppId, you can share and refine the functions of the logical division of AppId
     * , But no authentication is required. Business_id is just a label, and the granularity needs to be customized by the user.
     * @return   <br>
     *         + 0: Success. <br>
     *         + < 0: Failure. See BusinessCheckCode{@link #BusinessCheckCode} for specific reasons. <br>
     *         + -6001: The user is already in the room. <br>
     *         + -6002:
     *  The input is illegal. The legal characters include all lowercase letters, uppercase letters and numbers. In addition, the four independent characters are: English period, dash, underscore and @
     * .
     * @notes   <br>
     *         + Needs to be called before joinRoom{@link #IRTCAudioRoom#joinRoom}, and this method is invalid after joinRoom{@link #IRTCAudioRoom#joinRoom}.
     */
    virtual int setBusinessId(const char* business_id) = 0;
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
     * @region Engine management
     * @brief Set runtime parameters
     * @param  [in] json_string String after json serialization
     * @notes
     */
    virtual void setRuntimeParameters(const char * json_string) = 0;

    /** 
     * @type api
     * @region Multiple rooms
     * @brief Create and get a IRTCAudioRoom{@link #IRTCAudioRoom} object <br>
     * @param  [in] room_id A non-empty string with a maximum length of 128 bytes that identifies the room ID of the calling room. Supported character set ranges are: <br>
     *        + 26 uppercase letters A~ Z <br>
     *        + 26 lowercase letters a~ z <br>
     *        + 10 digits 0~ 9 <br>
     *        + Underscore "_", at character "@", Minus "-" <br>
     *        In multi-room mode, after calling the create room interface, do not call the same roomID to create a room, otherwise it will cause the creation of a room to fail. <br>
     * @notes   <br>
     *        + Users can call this method multiple times to create multiple IRTCAudioRoom{@link #IRTCAudioRoom} objects, and then call the joinRoom{@link #IRTCAudioRoom#joinRoom} method of each IRTCRoom object separately to achieve simultaneous joining of multiple rooms; <br>
     *        + After joining multiple rooms, users can subscribe to the audio & video streams of each room at the same time, but currently only support Publish all audio & video streams in one room at the same time. <br>
     */
    virtual IRTCAudioRoom* createRTCRoom(const char* room_id) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Enable internal audio capture. The default is off.   <br>
     *         This method is called before entering the room, and local users will receive a callback to onAudioDeviceStateChanged{@link #IRTCAudioEventHandler#onAudioDeviceStateChanged} . <br>
     *         Call this method after entering the room, and other users in the room will receive a callback for onUserStartAudioCapture{@link #IRTCAudioRoomEventHandler#onUserStartAudioCapture}.
     * @notes   <br>
     *        + If the microphone permission of the current device is not obtained, the onWarning{@link #IRTCAudioEventHandler#onWarning} callback will be triggered after calling this method. <br>
     *        + Call stopAudioCapture{@link #stopAudioCapture} to turn off the audio capture device, otherwise, the SDK will only automatically turn off the device when the engine is destroyed. <br>
     *        + Whether you publish audio data or not, you can call this method to turn on audio collection, and you can only publish audio after calling. <br>
     *        + When you have not entered the room and have used custom acquisition, turning off custom acquisition will not automatically turn on internal acquisition. You need to call this method to manually turn on internal collection.
     */
    virtual void startAudioCapture() = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Turn off internal audio capture. The default is off.   <br>
     *         This method is called before entering the room, and local users will receive a callback to onAudioDeviceStateChanged{@link #IRTCAudioEventHandler#onAudioDeviceStateChanged} . <br>
     *        After calling this method after entering the room, other users in the room will receive a callback for onUserStopAudioCapture{@link #IRTCAudioRoomEventHandler#onUserStopAudioCapture}.
     * @notes   <br>
     *        + Call startAudioCapture{@link #startAudioCapture} to turn on the audio capture device. <br>
     *        + If this method has not been called to shut down after the device is turned on, the SDK will automatically shut down the audio capture device when the engine is destroyed. <br>
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
     * @region audio management
     * @brief Sets the sound quality gear. You should choose the appropriate sound quality gear according to the needs of the business scenario.   <br>
     * @param  [in] audio_profile Sound quality gear. See AudioProfileType{@link #AudioProfileType}
     * @notes   <br>
     *         + This method can be called before and after entering the room; <br>
     *         + Support dynamic switching of sound quality gear during a call.
     */
    virtual void setAudioProfile(AudioProfileType audio_profile) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Volume management
     * @brief Adjust the audio acquisition volume
     * @param  [in] volume The ratio of the collected volume value to the original volume, the range is [0,400], in%, Comes with overflow protection.
     * @notes  <br>
     *         + This interface can be used for volume adjustment whether it is to capture audio streams from the microphone or the screen audio stream; whether it is an internal collection of the RTC SDK or a custom collection.
     *         + You can use this interface to set the acquisition volume before and after turning on audio acquisition.
     */
    virtual void setCaptureVolume(int volume) = 0;

    /** 
     * @hidden (Linux)
     * @type api
     * @region Audio management
     * @brief Adjust the volume after mixing by all remote users that play locally
     * @param  [in] volume Ratio(%) of playback volume to original volume, in the range [0, 400], with overflow protection.  <br>
     *        To ensure the audio quality, we recommend setting the volume within `100`.  <br>
     *        + 0: Mute <br>
     *        + 100: Original volume <br>
     *        + 400: Up to 4 times the original volume (with overflow protection) <br>
     * @notes To ensure better call quality, it is recommended to set the volume value to [0,100].
     */
    virtual void setPlaybackVolume(int volume) = 0;

    /** 
      * @type api
      * @region Audio Management
      * @brief Enable audio information prompts.   <br>
      * @param config See AudioPropertiesConfig{@link #AudioPropertiesConfig}
      * @notes After enable the prompt, you can:   <br>
      *        + Get the information of the audio stream collected by the local microphone and screen audio stream through onLocalAudioPropertiesReport{@link #IRTCAudioEventHandler#onLocalAudioPropertiesReport}; <br>
      *        + Get the information of the subscribed remote audio streams through onRemoteAudioPropertiesReport{@link #IRTCAudioEventHandler#onRemoteAudioPropertiesReport}.
      */
    virtual void enableAudioPropertiesReport(const AudioPropertiesConfig& config) = 0;

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
    virtual void setEarMonitorVolume(int volume) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Change local voice to a different key, mostly used in Karaoke scenarios.  <br>
     *        You can adjust the pitch of local voice such as ascending or descending with this method.
     * @param [in] pitch The value that is higher or lower than the original local voice within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
     *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
     *        Out of the value range, the setting fails and triggers onWarning{@link #IRTCAudioEventHandler#onWarning} callback, indicating `WARNING_CODE_SET_SCREEN_STREAM_INVALID_VOICE_PITCH` for invalid value setting with WarningCode{@link #WarningCode}.
     */
    virtual void setLocalVoicePitch(int pitch) = 0;

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device, and use speakers by default.   <br>
     *         When the audio playback device changes, you will receive an onAudioRouteChanged {@link
     *  #IRTCAudioEventHandler #onAudioRouteChanged} Callback.
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
     *        + 5. SetAudioRoute to kAudioRouteUnknown must be failed. <br>
     */
    virtual int setAudioRoute(AudioRoute route) = 0;

    /** 
     * @hidden (macOS, Windows)
     * @type api
     * @region Audio Facility Management
     * @brief get current using audio playback device.   <br>
     *         When the audio playback device changes, you will receive an onAudioRouteChanged{@link
     * #IRTCAudioEventHandler #onAudioRouteChanged} Callback.
     * @return  device current using Audio playback device. See AudioRoute{@link #AudioRoute}
     * @notes   <br>
     *        + 1. This interface is only available for mobile devices. <br>
     *        + 2. This method can be called before and during a call. <br>
     */
    virtual AudioRoute getAudioRoute() = 0;

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

    virtual void setRemoteAudioPlaybackVolume(const char* room_id, const char* user_id, int volume) = 0;

    /** 
     * @type api
     * @region Audio management
     * @brief Send audio stream synchronization information. The message is sent to the remote end through the audio stream and synchronized with the audio stream. After the interface is successfully called, the remote user will receive a OnStreamSyncInfoReceived{@link #IRTCAudioEventHandler#OnStreamSyncInfoReceived} callback.
     * @param  [in] data Message content.
     * @param  [in] length Message length. Message length must be [1,16] bytes.
     * @return   <br>
     *         + > = 0: Message sent successfully. Returns the number of successful sends. <br>
     *         + -1: Message sending failed. Message length greater than 16 bytes. <br>
     *         + -2: Message sending failed. The content of the incoming message is empty. <br>
     *         + -3: Message sending failed. This screen stream was not published when the message was synchronized through the screen stream. <br>
     *         + -4: Message sending failed. This audio stream is not yet published when you synchronize messages with an audio stream captured by a microphone or custom device, as described in ErrorCode{@link #ErrorCode}. <br>
     * @notes When using `kRoomProfileTypeLiveBroadcasting` as room profile, the data will be delivered. For other coom profiles, the data may be lost when the local user is muted.
     */
    virtual int sendStreamSyncInfo(const uint8_t* data, int32_t length, int repeat_count) = 0;

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
     * @region Media stream management
     * @brief Control the playinging status of the local audio stream: play/not play   <br>
     * @param  [in] mute_state playinging status to identify whether to play the local audio stream, see: MuteState {@link #MuteState}
     * @notes This method only controls the local audio The playinging state of the stream does not affect the local audio play device.
     */
    virtual void muteAudioPlayback(MuteState mute_state) = 0;
    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief  Switch the audio capture type.
     * @param type Audio input source type. See AudioSourceType{@link #AudioSourceType} <br>
     *            Use internal audio capture by default. The audio capture type and the audio render type may be different from each other.
     * @return   Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @notes   <br>
     *       + You can call this API before or after joining the room.<br>
     *       + If you call this API to switch from internal audio capture to custom capture, the internal audio capture is automatically disabled. You must call pushExternalAudioFrame{@link #IRTCAudio#pushExternalAudioFrame} to push custom captured audio data to RTC SDK for transmission. <br>
     *       + If you call this API to switch from custom capture to internal capture, you must then call startAudioCapture{@link #IRTCAudio#startAudioCapture} to enable internal capture. <br>
     */
    virtual int setAudioSourceType(AudioSourceType type) = 0;
    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief  Switch the audio render type.
     * @param type Audio output source type. See AudioRenderType{@link #AudioRenderType}. <br>
     *             Use internal audio render by default. The audio capture type and the audio render type may be different from each other.
     * @return   Method call result:   <br>
     *         + >0: Success. <br>
     *         + -1: Failure.
     * @notes   <br>
     *       + You can call this API before or after joining the room. <br>
     *       + After calling this API to enable custom audio rendering, call pullExternalAudioFrame{@link #IRTCAudio#pullExternalAudioFrame} for audio data.
     */
    virtual int setAudioRenderType(AudioRenderType type) = 0;
    /** 
     * @type api
     * @region Custom Audio Capture and Rendering
     * @brief Push custom captured audio data to the RTC SDK.
     * @param [in] audioFrame. The audio data of 10 ms. See IAudioFrame{@link #IAudioFrame}。
     * @return <br>
     *         + 0: Success <br>
     *         + < 0: Failure <br>
     * @notes   <br>
     *        + Before calling this API, you must call setAudioSourceType{@link #IRTCAudio#setAudioSourceType} to enable custom audio capture. <br>
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
     *        + Before pulling the audio data, call setAudioRenderType{@link #IRTCAudio#setAudioRenderType} to enable custom rendering. <br>
     *        + Pull the audio data every 10 ms. <br>
     *        + This function runs in the user calling thread and is a synchronous function. <br>
     */
    virtual bool pullExternalAudioFrame(IAudioFrame* audioFrame) = 0;

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
     * @region Audio Data Callback
     * @brief Enables audio data callback.
     * @param [in] method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}. <br>
     *               If `method` is set as `kAudioFrameCallbackRecord`, `kAudioFrameCallbackPlayback`, `kAudioFrameCallbackMixed`, `kAudioFrameCallbackRecordScreen`, set `format` to the accurate value listed in the audio parameters format.
     *               If `method` is set as `kAudioFrameCallbackRemoteUser`, set `format` to `auto`.
     * @param [in] format Audio parameters format. See AudioFormat{@link #AudioFormat}.
     * @notes After calling this API and registerAudioFrameObserver{@link #IRTCAudio#registerAudioFrameObserver}, IAudioFrameObserver{@link #IAudioFrameObserver} will receive the corresponding audio data callback. However, these two APIs are independent of each other and the calling order is not restricted. <br>
     */
    virtual void enableAudioFrameCallback(AudioFrameCallbackMethod method, AudioFormat format) = 0;

    /** 
     * @type api
     * @region Audio Data Callback
     * @brief Disables audio data callback.
     * @param [in] method Audio data callback method. See AudioFrameCallbackMethod{@link #AudioFrameCallbackMethod}.
     * @notes Call this API after calling enableAudioFrameCallback{@link #IRTCAudio#enableAudioFrameCallback}.
     */
    virtual void disableAudioFrameCallback(AudioFrameCallbackMethod method) = 0;

    /** 
     * @type api
     * @region Audio Data Callback
     * @brief Register an audio frame observer.  <br>
     * @param [in] observer Audio data callback observer. See IAudioFrameObserver{@link #IAudioFrameObserver}. Use `null` to cancel the registration.
     * @return  <br>
     *        + 0: Success. <br>
     *        + < 0: Failure. <br>
     * @notes After calling this API and enableAudioFrameCallback{@link #IRTCAudio#enableAudioFrameCallback}, IAudioFrameObserver{@link #IAudioFrameObserver} will receive the corresponding audio data callback.
     */
    virtual void registerAudioFrameObserver(IAudioFrameObserver* observer) = 0;

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
    *         After that, you can call enableAudioProcessor{@link #IRTCVideo#enableAudioProcessor} to process the locally captured or received remote audio streams.
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
    *        + Before calling this API, you must call registerAudioProcessor{@link #IRTCVideo#registerAudioProcessor} to register the processor. <br>
    *        + To disable custom audio processing, call disableAudioProcessor{@link #IRTCVideo#disableAudioProcessor}.
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
     * @region  mixing
     * @brief  Mixing management interface creation
     * @return  Mixing management instance. See IAudioMixingManager{@link #IAudioMixingManager}
     */
    virtual IAudioMixingManager* getAudioMixingManager() = 0;

    /** 
     * @hidden
     * @type api
     * @region speech recognition service
     * @brief Enables automatic speech recognition service. This method converts the recognized user's voice into text and calls it back to the user through the OnMessage{@link #IRTCASREngineEventHandler#OnMessage}
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
     * @region Local recording
     * @brief This method records the audio & video data during the call to a local file.
     * @param  [in] config Local recording parameter configuration. See RecordingConfig{@link #RecordingConfig}
     * @return   <br>
     *         + 0: normal
     *         + -1: Parameter setting exception
     *         + -2: The current version of the SDK does not support this Feature, please contact technical support staff
     * @notes   <br>
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRTCAudioEventHandler#onRecordingStateUpdate} callback. <br>
     *         + If the recording is normal, the system will notify the recording progress through onRecordingProgressUpdate{@link #IRTCAudioEventHandler#onRecordingProgressUpdate}
     *  Callback every second.
     */
    virtual int startFileRecording(RecordingConfig config) = 0;

    /** 
     * @type api
     * @region local recording
     * @brief Stop local recording
     * @notes   <br>
     *         + Call startFileRecording{@link #IRTCAudio#startFileRecording} After starting local recording, you must call this method to stop recording. <br>
     *         + After calling this method, you will receive an onRecordingStateUpdate{@link #IRTCAudioEventHandler#onRecordingStateUpdate} callback prompting you to record the result.
     */
    virtual void stopFileRecording() = 0;

    /** 
     * @type api
     * @region Encryption
     * @brief Set the way to use built-in encryption when transmitting  <br>
     * @param encrypt_type Built-in encryption algorithm. See EncryptType{@link #EncryptType}
     * @param  [in] encrypt_type Encryption type. See EncryptType{@link #EncryptType}
     * @param  [in] key Encryption key, the length is limited to 36 bits, and the excess will be Truncate
     * @param  [in] key_size The length of the parameter key
     * @notes   <br>
     *        + Use this method when using the built-in encryption on transfer; if you need to use custom encryption on transfer. See OnEncryptData{@link #IEncryptHandler#OnEncryptData}. Built-in encryption and custom encryption are mutually exclusive, and the transmission is determined to be encrypted according to the last method called. <br>
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
     *        + This method is mutually exclusive with setEncryptInfo{@link #setEncryptInfo},
     *          You can only select custom encryption method or default encryption method. The encryption method that takes effect depends on the last method called. <br>
     *        + This method must be called before entering the room, and can be called repeatedly, taking the last called parameter as the effective parameter. <br>
     *        + Whether encrypted or decrypted, the length modification of the original data source needs to be controlled between 90% and 120%, i.e. If the input data is 100
     *  Bytes, the processed data must be between 90 and 120 bytes. Between bytes, if the encrypted or decrypted result exceeds the length limit, the audio & video frame will be discarded. <br>
     *        +
     *  Data encryption/decryption is performed serially, so depending on the implementation, it may affect the final rendering efficiency. Whether to use this method needs to be carefully evaluated by users.
     *  <br>
     */
    virtual void setCustomizeEncryptHandler(IEncryptHandler* handler) = 0;

    /** 
     * @type api
     * @region Real-time messaging
     * @brief Log in to send P2P messages or send messages to a server without joining the RTC room.<br>
     *        To log out, call logout{@link #IRTCAudio#logout}. <br>
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
     * @notes  You will receive onLoginResult{@link #IRTCAudioEventHandler#onLoginResult} after calling this API and log in successfully. But remote users will not receive notification about that.
     */
    virtual void login(const char* token, const char* uid) = 0;
    /** 
     * @type After api
     * @region  real-time messaging
     * @brief  Calls this interface to log out, it is impossible to call methods related to out-of-room messages and end-to-server messages or receive related callbacks.
     * @notes   <br>
     *        + Before calling this interface to log out, you must call login{@link #IRTCAudio#login} to log in. <br>
     *        + After local users call this method to log out, they will receive the result of the onLogout{@link #IRTCAudioEventHandler#onLogout} callback notification, and remote users will not receive the notification.
     */
    virtual void logout() = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Update the Token <br>
     *        Token used by the user to log in has a certain valid period. When the Token expires, you need to call this method to update the login Token information. <br>
     *         When calling the login{@link #IRTCAudio#login} method to log in, if an expired token is used, the login will fail and you will receive an onLoginResult{@link #IRTCAudioEventHandler#onLoginResult} callback notification with an error code of kLoginErrorCodeInvalidToken. You need to reacquire the token and call this method to update the token.
     * @param  [in] token <br>
     *        Updated dynamic key
     * @notes   <br>
     *        + If the token is invalid and the login fails, call this method. After updating the token, the SDK will automatically log back in, and the user does not need to call the login{@link #IRTCAudio#login} method. <br>
     *        + Token expires, if you have successfully logged in, it will not be affected. An expired Token error will be notified to the user the next time you log in with an expired Token, or when you log in again due to a disconnection due to poor local network conditions.
     */
    virtual void updateLoginToken(const char* token) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Set application server parameters   <br>
     *        Client side calls sendServerMessage{@link #IRTCAudio#sendServerMessage} or sendServerBinaryMessage{@link #IRTCAudio#sendServerBinaryMessage} Before sending a message to the application server, a valid signature and application server address must be set.
     * @param  [in] signature <br>
     *        Dynamic signature <br>
     *        The service server uses this signature to authenticate the request.
     * @param  [in] url <br>
     *         The address of the application server
     * @notes   <br>
     *        + The user must call login{@link #IRTCAudio#login} to log in before calling this interface. <br>
     *        + After calling this interface, the SDK will use onServerParamsSetResult{@link #IRTCAudioEventHandler#onServerParamsSetResult} to return the corresponding result.
     */
    virtual void setServerParams(const char* signature, const char* url) = 0;
    /** 
     * @type api
     * @region Real-time messaging
     * @brief Query the login status of the opposite or local user
     * @param  [in] peer_user_id <br>
     *        User ID to be queried
     * @notes   <br>
     *        + login{@link #IRTCAudio#login} must be called before this interface can be called. <br>
     *        + After calling this interface, the SDK notifies the query result using the onGetPeerOnlineStatus{@link #IRTCAudioEventHandler#onGetPeerOnlineStatus} callback. <br>
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
     *        + You must call login{@link #IRTCAudio#login} to complete the login before you can send a message in a foreign text of the room. <br>
     *        + After the user calls this interface to send a text message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageSendResultOutsideRoom} callback to know whether the message was successfully sent. <br>
     *        + If the text message is sent successfully, the user specified by uid receives the message via the onUserMessageReceivedOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageReceivedOutsideRoom} callback.
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
     *        + You must call login{@link #IRTCAudio#login} before sending out-of-room binary messages. <br>
     *        + After the user calls this interface to send a binary message, he will receive an onUserMessageSendResultOutsideRoom{@link #IRTCAudioEventHandler#onUserMessageSendResultOutsideRoom} callback to notify whether the message was sent successfully. <br>
     *        + If the binary message is sent successfully, the user specified by uid will receive the message through the onUserBinaryMessageReceivedOutsideRoom{@link #IRTCAudioEventHandler#onUserBinaryMessageReceivedOutsideRoom} callback.
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
     *        + Before sending a text message to the application server, you must first call login{@link #IRTCAudio#login} to complete the login, and then call setServerParams{@link #IRTCAudio#setServerParams} Set up the application server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTCAudioEventHandler#onServerMessageSendResult} callback to inform the message sender whether the message was sent successfully. <br>
     *        + If the text message is sent successfully, the application server that previously called setServerParams{@link #IRTCAudio#setServerParams} will receive the message.
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
     *        + Before sending a binary message to the application server, you must first call login{@link #IRTCAudio#login} to complete the login, and then call setServerParams{@link #IRTCAudio#setServerParams} Set up the application server. <br>
     *        + After calling this interface, you will receive an onServerMessageSendResult{@link #IRTCAudioEventHandler#onServerMessageSendResult} callback to inform the message sender that the sending succeeded or failed. <br>
     *        + If the binary message is sent successfully, the application server that previously called setServerParams{@link #IRTCAudio#setServerParams} will receive the message.
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
     *        + After calling this interface, you will receive onNetworkDetectionResult{@link #IRTCAudioEventHandler#onNetworkDetectionResult} callback notifying the probe result; <br>
     *        + If the probe stops, you will receive onNetworkDetectionStopped{@link #IRTCAudioEventHandler#onNetworkDetectionStopped} notify that probing has stopped.
     */
    virtual NetworkDetectionStartReturn startNetworkDetection(bool is_test_uplink, int expected_uplink_bitrate,
                                   bool is_test_downlink, int expected_downlink_biterate) = 0;

    /** 
     * @type api
     * @region Pre-call network probe
     * @brief Stop pre-call network probe
     * @notes   <br>
     *        + After calling this interface, you will receive onNetworkDetectionStopped{@link #IRTCAudioEventHandler#onNetworkDetectionStopped} notifying that the the probing has stopped.
     */
    virtual void stopNetworkDetection() = 0;

    /** 
     * @type api
     * @region  cloud proxy
     * @brief  Start cloud proxy
     * @param  [in] configuration cloud proxy informarion list. See CloudProxyConfiguration{@link #CloudProxyConfiguration}.
     * @notes   <br>
     *         + Call this API before joining the room.<br>
     *         + Start pre-call network detection after starting cloud proxy. <br>
     *         + After starting cloud proxy and connects the cloud proxy server successfully, receives onCloudProxyConnected{@link #IRTCAudioEventHandler#onCloudProxyConnected}. <br>
     *         + To stop cloud proxy, call stopCloudProxy{@link #IRTCAudio#stopCloudProxy}.
     */
    virtual void startCloudProxy(const CloudProxyConfiguration& configuration) = 0;

    /** 
     * @type api
     * @region  cloud proxy
     * @brief  Stop cloud proxy
     * @notes To start cloud proxy, call startCloudProxy{@link #IRTCAudio#startCloudProxy}.
     */
    virtual void stopCloudProxy() = 0;
};

/** 
 * @type api
 * @region Engine Management
 * @brief Create RTCEngine instances. <br>
 *         If no engine instance is created in the current thread, you must use this method first to use the various audio & video capabilities provided by RTC. <br>
 *        If an engine instance has been created in the current thread, another independent engine instance is created when this method is called again.
 * @param  [in] app_id <br>
 *         A unique device identifier for each application. Only instances generated using the same app_id can be used for audio & video communication.
 * @param  [in] event_handler <br>
 *        SDK callback to the application layer Callback object. See IRTCAudioEventHandler{@link #IRTCAudioEventHandler}.
 * @param  [in] parameters This engine instance parameter is used to override the default parameters. JSON string format.
 * @return Available IRTCAudio{@link #IRTCAudio} instances.
 * @notes   <br>
 *         + If you create multiple engine instances in the same thread, these instances must be destroyed by calling destroyRTCAudio{@link #destroyRTCAudio} separately.
 *         + The number of engine instances created on Linux platform depends on the hardware performance of the system.
 */
BYTERTC_API IRTCAudio* createRTCAudio(const char* app_id,
        IRTCAudioEventHandler* event_handler, const char* parameters);

/** 
 * @type api
 * @region Engine Administration
 * @brief Destroys the RTCEngine instance created by createRTCAudio{@link #createRTCAudio} and releases all related resources.
 * @param  [in] engine <br>
 *        createRTCAudio{@link #createRTCAudio}, the instance returned.
 * @notes  <br>
 *         + Call this API after all business scenarios related to the engine instance are destroyed. In a multi-thread scenario, you must not call IRTCAudio{@link #IRTCAudio} related APIs after calling this interface, or the SDK may crash. <br>
 *         + When the API is called, RTC SDK destroys all memory associated with the engine instance and stops any interaction with the media server.  <br>
 *         + Calling this API will start the SDK exit logic. The engine thread is held until the exit logic is complete. The engine thread is retained until the exit logic is complete.  <br>
 *           Therefore, do not call this API directly in the callback thread, or wait for the execution of the main thread in the callback and call this API in the main thread at the same time. Otherwise, it will cause a deadlock.
 */
BYTERTC_API void destroyRTCAudio(IRTCAudio* engine);

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

}  // namespace bytertc
