/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief Objective-C BytePlusRTC Audio Defines
*/

#import "ByteRTCCommonDefines.h"

/** 
 * @type keytype
 * @brief  Audio scenarios   <br>
 *        After selecting the audio scenario, SDK will automatically select the call/media volume, according to the client-side audio device and status. <br>
 *        If the following audio scenarios cannot meet your business needs, please contact our technical support team for customization.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioScenarioType) {
    /** 
     * @brief (Default) Music scenario   <br>
     *        This scenario is suitable for scenes that require musical expression, such as music live.  <br>
     *         For different audio device and status, the selected volume type is as follows: <br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *            <tr><td>Wired Headset</td><td>Media volume</td><td> Media Volume</td><td>/</td></tr>
     *            <tr><td>Bluetooth Headset</td><td>Media Volume</td><td>Media Volume</td><td>Even if the Bluetooth headset has a microphone, you can only use the build-in microphone for local audio capture.</td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioMusic = 0,
    /** 
     * @brief High-quality communication scenario <br>
     *        This scenario is suitable for scenes that require musical expression, but also want to use the microphone on the bluetooth headphones for audio capturing. <br>
     *        This scenario can provide decent audio performance using the speaker/bluetooth earphones. It can also avoid sudden changes of volume type when switching to bluetooth earphones. <br>
     *        For different audio device and status, the selected volume type is as follows:
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td> Media volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td> Wired headset </td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    ByteRTCAudioScenarioHighqualityCommunication = 1,
    /** 
     * @brief  Call volume scenario <br>
     *         This scenario uses the call volume regardless of the client-side audio device or status.
     *         This scenario is suitable for calls or meetings that require turning on and off the microphone frequently.
     *         Call volume is used the whole time and there will not be sudden changes in volume.
     *         This scenario maximizes the elimination of echoes and has optimal call clarity.
     *         You can use the microphone on the bluetooth earphones for audio capturing.
     *         However, the volume of other audio played using media volume will be lowered, and the audio quality is worse.
     */
    ByteRTCAudioScenarioCommunication = 2,
    /** 
     * @brief Media volume scenario (not recommended)  <br>
     *         This scenario uses the media volume regardless of the client-side audio device or status.
     */
    ByteRTCAudioScenarioMedia = 3,
    /** 
     * @brief Game media scene. Only suitable for game scenes.   <br>
     *        This scenario uses the media volume except when you use the bluetooth earphones.
     *        Echo and howling frequently occurs when you put on speaker and do not have gaming sound cancellation.
     */
    ByteRTCAudioScenarioGameStreaming = 4,
};

/** 
 * @type keytype
 * @brief  Change sound effect type
 */
typedef NS_ENUM(NSInteger, ByteRTCVoiceChangerType) {
    /** 
     * @brief Acoustic, no special effects
     */
    ByteRTCVoiceChangerOriginal = 0,
    /** 
     * @brief Giant
     */
    ByteRTCVoiceChangerGiant = 1,
    /** 
     * @brief Chipmunk
     */
    ByteRTCVoiceChangerChipmunk = 2,
    /** 
     * @brief Little yellow man
     */
    ByteRTCVoiceChangerMinionst = 3,
    /** 
     * @brief Trill
     */
    ByteRTCVoiceChangerVibrato = 4,
    /** 
     * @brief Robot
     */
    ByteRTCVoiceChangerRobot = 5,
};

/** 
 * @type keytype
 * @brief  Reverb effect type
 */
typedef NS_ENUM(NSInteger, ByteRTCVoiceReverbType) {
    /** 
     * @brief Acoustic, no special effects
     */
    ByteRTCVoiceReverbOriginal = 0,
    /** 
     * @brief Echo
     */
    ByteRTCVoiceReverbEcho = 1,
    /** 
     * @brief Concert
     */
    ByteRTCVoiceReverbConcert = 2,
    /** 
     * @brief Ethereal
     */
    ByteRTCVoiceReverbEthereal = 3,
    /**
     * @brief KTV
     */
    ByteRTCVoiceReverbKTV = 4,
    /** 
     * @brief Recording studio
     */
    ByteRTCVoiceReverbStudio = 5,
};

/** 
 * @type keytype
 * @brief  Sound quality gear
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioProfileType) {
    /** 
     * @brief Default sound quality
     */
    ByteRTCAudioProfileDefault = 0,
    /** 
     * @brief Smooth sound quality.   <br>
     *         Fluent priority, low latency, low power consumption, low traffic consumption, suitable for most game scenarios, such as MMORPG, MOBA, FPS and other game team voice, team voice, national war voice, etc.
     */
    ByteRTCAudioProfileFluent = 1,
    /** 
     * @brief Standard sound quality.   <br>
     *         Suitable for scenes with certain requirements for sound quality, while the delay, power consumption and traffic consumption are relatively moderate, suitable for Werewolf games such as Sirius.
     */
    ByteRTCAudioProfileStandard = 2,
    /** 
     * @brief High-definition sound quality   <br>
     *         Ultra-high sound quality, while the delay, power consumption and traffic consumption are relatively large, suitable for Lianmai PK, online education and other scenes. <br>
     *        Game scenes are not recommended.
     */
    ByteRTCAudioProfileHD = 3,
    /** 
     * @brief Standard quality. Dual-channel audio with a sampling rate of 48 KHz, and the maximum encoding bit rate is 80 Kbps.
     */
    ByteRTCAudioProfileStandardStereo = 4,
    /** 
     * @brief Music quality. Mono-channel audio with a sampling rate of 48 KHz, and the maximum encoding bit rate is 128 Kbps.
     */
    ByteRTCAudioProfileHDMono = 5,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Voice call mode, use this interface to set your own sending mode in team voice
 */
typedef NS_ENUM(NSUInteger, ByteRTCRangeAudioMode) {
    /** 
     * @brief Default mode
     */
    ByteRTCRangeAudioModeUndefined = 0,
    /** 
     * @brief Squad mode
     */
    ByteRTCRangeAudioModeTeam = 1,
    /** 
     * @brief World mode
     */
    ByteRTCRangeAudioModeWorld = 2,
};

/** 
 * @type keytype
 * @brief Type of audio device
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioDeviceType) {
    /** 
     * @brief Unknown device
     */
    ByteRTCAudioDeviceTypeUnknown = -1,
    /** 
     * @brief Screen audio recorder
     */
    ByteRTCAudioDeviceTypeRenderDevice = 0,
    /** 
     * @brief Microphone
     */
    ByteRTCAudioDeviceTypeCaptureDevice = 1,
    /** 
     *@brief Screen audio recorder
     */
    ByteRTCAudioDeviceTypeScreenCaptureDevice = 2
};

/** 
 * @type keytype
 * @brief Audio sample rate in Hz.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSampleRate) {
    /** 
     * @brief Default value.
     */
    ByteRTCAudioSampleRateAuto = -1,
    /** 
     * @brief 8000 Hz
     */
    ByteRTCAudioSampleRate8000 = 8000,
    /** 
     * @brief 16000 Hz
     */
    ByteRTCAudioSampleRate16000 = 16000,
    /** 
     * @brief 32000 Hz
     */
    ByteRTCAudioSampleRate32000 = 32000,
    /** 
     * @brief 44100 Hz
     */
    ByteRTCAudioSampleRate44100 = 44100,
    /** 
     * @brief 48000 Hz
     */
    ByteRTCAudioSampleRate48000 = 48000
};

/** 
 * @type keytype
 * @brief Audio channel
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioChannel) {
    /** 
     * @brief Default value.
     */
    ByteRTCAudioChannelAuto = -1,
    /** 
     * @brief Mono channel
     */
    ByteRTCAudioChannelMono = 1,
    /** 
     * @brief Dual channels
     */
    ByteRTCAudioChannelStereo = 2,
};

/** 
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile
 */
typedef NS_ENUM(NSInteger, ByteRTCAACProfile) {
    /** 
     * @brief Low-Complexity profile (AAC-LC)
     */
    ByteRTCAACProfileLC   = 0,
    /** 
     * @brief HE-AAC profile (AAC LC with SBR)
     */
    ByteRTCAACProfileHEv1 = 1,
    /** 
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo)
     */
    ByteRTCAACProfileHEv2 = 2,
};
/** 
 * @type keytype
 * @brief Audio playback device
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRoute) {
    /** 
     * @brief Unknown device
     */
    ByteRTCAudioRouteUnknown = -1,
    /** 
     * @brief Wired earphones
     */
    ByteRTCAudioRouteHeadset = 1,
    /** 
     * @brief Earpiece. Built-in device for calling
     */
    ByteRTCAudioRouteEarpiece = 2,
    /** 
     * @brief Speaker. Built-in device for hands-free audio playing
     */
    ByteRTCAudioRouteSpeakerphone = 3,
    /** 
     * @brief Bluetooth earphones
     */
    ByteRTCAudioRouteHeadsetBluetooth = 4,
    /** 
     * @brief USB Device
     */
    ByteRTCAudioRouteHeadsetUSB = 5,
};

/** 
 * @type keytype
 * @brief  Audio playback device   <br>
 *        When the audio playback device changes, you will receive the `rtcEngine:onAudioPlaybackDeviceChanged:` callback.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioPlaybackDevice) {
    /** 
     * @brief Wired earphones
     */
    ByteRTCAudioPlaybackDeviceHeadset = 1,
    /** 
     * @brief Earpiece
     */
    ByteRTCAudioPlaybackDeviceEarpiece = 2,
    /** 
     * @brief Speaker
     */
    ByteRTCAudioPlaybackDeviceSpeakerphone = 3,
    /** 
     * @brief Bluetooth earphones
     */
    ByteRTCAudioPlaybackDeviceHeadsetBluetooth = 4,
    /** 
     * @brief USB Device
     */
    ByteRTCAudioPlaybackDeviceHeadsetUSB = 5,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Speech recognition service authentication method, please consult the speech recognition service related classmates for details
 */
typedef NS_ENUM(NSInteger, ByteRTCASRAuthorizationType) {
    /** 
     *  @brief Use token without setting the encrypted form. <br>
     */
    ByteRTCASRAuthorizationTypeToken = 0,
    /** 
     *  @brief With token additional use of signature encryption, this form of encryption requires additional pass secret token. <br>
     */
    ByteRTCASRAuthorizationTypeSignature = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Speech recognition service error code.   <br>
 *         Except for errors caused by network reasons, the speech recognition service will retry itself, other errors will stop the service. At this time, it is recommended to call `startASR:handler:` to restart the speech recognition function.
 */
typedef NS_ENUM(NSInteger, ByteRTCASRErrorCode) {
    /** 
     * @brief The network connection is broken, the service is unavailable, and internal reconnection will be carried out
     */
    ByteRTCASRErrorNetworkInterrupted = -1,
    /** 
     * @brief The user has called `startASR:handler:`. <br>
     *         After starting the speech recognition service, you need to call `stopASR` to stop the speech recognition service before starting the service again.
     */
    ByteRTCASRErrorAlreadyStarted = -2,
    /** 
     * @brief The token required by the speech recognition service is empty
     */
    ByteRTCASRErrorTokenEmpty = -3,
    /** 
     * @brief Signature  The secretKey is empty in authentication mode
     */
    ByteRTCErrorSignatureKeyEmpty = -4,
    /** 
     * @brief User ID is empty
     */
    ByteRTCASRErrorUserIdNull = -5,
    /** 
     * @brief Application ID is empty
     */
    ByteRTCASRErrorAPPIDNull = -6,
    /** 
     * @brief Speech recognition service cluster is empty
     */
    ByteRTCASRErrorClusterNull = -7,
    /** 
     * @brief The speech recognition service connection failed, this version does not have speech recognition function, please contact RTC technical support.
     */
    ByteRTCASRErrorOperationDenied = -8
};

/** 
 * @type keytype
 * @brief Mixing type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingType) {
    /** 
     * @brief Played at the local device only
     */
    ByteRTCAudioMixingTypePlayout = 0,
    /** 
     * @brief Sent to the remote devices only
     */
    ByteRTCAudioMixingTypePublish = 1,
    /** 
     * @brief Played at the local device and sent to the remote devices.
     */
    ByteRTCAudioMixingTypePlayoutAndPublish = 2
};

/** 
 * @type keytype
 * @brief  Mix playback channel type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingDualMonoMode) {
    /** 
     * @brief Consistent with audio files
     */
    ByteRTCAudioMixingDualMonoModeAuto = 0,
    /** 
     * @brief Only the left channel audio in the audio file can be heard
     */
    ByteRTCAudioMixingDualMonoModeL = 1,
    /** 
     * @brief Only the right channel audio in the audio file can be heard
     */
    ByteRTCAudioMixingDualMonoModeR = 2,
    /** 
     * @brief Can hear the left and right audio channels in the audio file at the same time
     */
    ByteRTCAudioMixingDualMonoModeMix = 3
};

/** 
 * @type keytype
 * @brief  Audio mix file playback status.
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingState) {
    /** 
     * @brief Mix loaded
     */
    ByteRTCAudioMixingStatePreloaded = 0,
    /** 
     * @brief Mix is playing
     */
    ByteRTCAudioMixingStatePlaying,
    /** 
     * @brief Mix Pause
     */
    ByteRTCAudioMixingStatePaused,
    /** 
     * @brief Mixing stopped
     */
    ByteRTCAudioMixingStateStopped,
    /** 
     * @brief Mix playback failed
     */
    ByteRTCAudioMixingStateFailed,
    /** 
     * @brief End of mixing
     */
    ByteRTCAudioMixingStateFinished,
    /** 
     * @brief PCM mixing enabled
     */
    ByteRTCAudioMixingStatePCMEnabled,
    /** 
     * @brief PCM mixing disabled
     */
    ByteRTCAudioMixingStatePCMDisabled,
};
/** 
 * @type keytype
 * @brief Error code for audio mixing
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioMixingError) {
    /** 
     * @brief OK
     */
    ByteRTCAudioMixingErrorOk = 0,
    /** 
     * @brief Preload failed. Invalid path or the length exceeds 20s.
     */
    ByteRTCAudioMixingErrorPreloadFailed,
    /** 
     * @brief Mixing failed. Invalid path or fail to open the file.
     */
    ByteRTCAudioMixingErrorStartFailed,
    /** 
     * @brief Invalid mixID
     */
    ByteRTCAudioMixingErrorIdNotFound,
    /** 
     * @brief Invalid position
     */
    ByteRTCAudioMixingErrorSetPositionFailed,
    /** 
     * @brief Invalid volume. The range is [0, 400].
     */
    ByteRTCAudioMixingErrorInValidVolume,
    /** 
     * @brief Another file was preloaded for mixing. Call unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} first.
     */
    ByteRTCAudioMixingErrorLoadConflict,
    /** 
     * @brief Invalid mix type.
     */
    ByteRTCAudioMixingErrorIdTypeNotMatch,
    /** 
     * @brief Invalid pitch value.
     */
    ByteRTCAudioMixingErrorInValidPitch,
    /** 
     * @brief Invalid audio track.
     */
    ByteRTCAudioMixingErrorInValidAudioTrack,
    /** 
     * @brief Mixing starting.
     */
    ByteRTCAudioMixingErrorIsStarting,
    /** 
     * @brief Invalid playback speed
     */
    ByteRTCAudioMixingErrorInValidPlaybackSpeed,
};

/** 
 * @type keytype
 * @brief  Audio input source type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioSourceType) {
    /** 
     * @brief Custom Capture Audio Source
     */
    ByteRTCAudioSourceTypeExternal = 0,
    /** 
     * @brief RTC SDK internal acquisition audio source
     */
    ByteRTCAudioSourceTypeInternal,
};

/** 
 * @type keytype
 * @brief  Audio output type
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioRenderType) {
    /** 
     * @brief Custom render Audio
     */
    ByteRTCAudioRenderTypeExternal = 0,
    /** 
     * @brief RTC SDK internal render audio
     */
    ByteRTCAudioRenderTypeInternal,
};

/** 
 * @type keytype
 * @brief  Enable/disable earphone monitoring
 */
typedef NS_ENUM(NSInteger, ByteRTCEarMonitorMode) {
    /** 
     * @brief Do not turn on the earphone monitoring function
     */
    ByteRTCEarMonitorModeOff = 0,
    /** 
     * @brief Enable earphone monitoring function
     */
    ByteRTCEarMonitorModeOn = 1,
};

/** 
 * @type keytype
 * @brief  Audio data callback method
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameCallbackMethod) {
    /** 
     * @brief The callback of the audio data recorded by local microphone.
     */
    ByteRTCAudioFrameCallbackRecord = 0,
    /** 
     * @brief The callback of the mixed audio data of all remote users subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackPlayback = 1,
    /** 
     * @brief The callback of the mixed audio data including the data recorded by local microphone and that of all remote users subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackMixed = 2,
    /** 
     * @brief The callback of the audio data before mixing of each remote user subscribed by the local user.
     */
    ByteRTCAudioFrameCallbackRemoteUser = 3,
};
/** 
 * @type keytype
 * @brief The type of the audio for the audio processor
 */
typedef NS_ENUM(NSInteger, ByteRTCAudioFrameMethod) {
    /** 
     * Locally captured audio frame
     */
    ByteRTCAudioFrameProcessorRecord = 0,
    /** 
     * The mixed remote audio
     */
    ByteRTCAudioFrameProcessorPlayback = 1,
    /** 
     * The audio streams from remote users
     */
    ByteRTCAudioFrameProcessorRemoteUser = 2,
};

/** 
 * @type keytype
 * @brief User ID of the source of the audio stream, and the corresponding volume.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioVolumeInfo : NSObject
/** 
 * @brief User of the audio stream source ID
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief LinearVolume, range: [0,255]
 */
@property(assign, nonatomic) NSUInteger linearVolume;
/** 
 * @brief NonlinearVolume, range: [-127,0]
 */
@property(assign, nonatomic) NSUInteger nonlinearVolume;
@end

/** 
 * @type keytype
 * @brief Audio parameters format
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFormat : NSObject
/** 
 * @brief Audio sampling rate. See ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}
 */
@property(nonatomic, assign) ByteRTCAudioSampleRate sampleRate;
/** 
 * @brief For audio channels. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}
 */
@property(nonatomic, assign) ByteRTCAudioChannel channel;
@end

/** 
 * @type keytype
 * @brief Audio frame in PCM
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioFrame : NSObject
/** 
 * @brief PCM data
 */
@property(strong, nonatomic) NSData * _Nonnull buffer;
/** 
 * @brief Total sampling number
 */
@property(assign, nonatomic) int samples;
/** 
 * @brief Audio channel. See ByteRTCAudioChannel{@link #ByteRTCAudioChannel}.
 */
@property(assign, nonatomic) ByteRTCAudioChannel channel;
/** 
 * @brief Sample rate. See ByteRTCAudioSampleRate{@link #ByteRTCAudioSampleRate}.
 */
@property(assign, nonatomic) ByteRTCAudioSampleRate sampleRate;
@end

/** 
 *  @type callback
 *  @brief Audio data callback observer
 */
@protocol ByteRTCAudioFrameObserver <NSObject>
/** 
 * @type callback
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Returns audio data recorded by microphone
 * @param audioFrame Audio data recorded by microphone, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Returns the mixed audio data of all subscribed remote users
 * @param audioFrame Mixed audio data, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onPlaybackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Returns the audio data of one remote user.
 * @param streamKey Remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}.
 * @param audioFrame Audio data. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @notes This callback works on the playback thread. Don't do anything time-consuming in this callback, or it may affect the entire audio playback chain.
 */
- (void)onRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                    audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/** 
 * @type callback
 * @region Audio Data Callback
 * @author wangjunzheng
 * @brief Returns mixed audio data including both data recorded by the local microphone and data from all subscribed remote users
 * @param audioFrame Mixed audio data, see ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
 */
- (void)onMixedAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end
 /** 
 * @type keytype
 * @hidden 
 * @deprecated since 342, use ByteRTCAudioFrameProcessor instead.
 * @author majun.lvhiei
 * @region  audio processing
 * @brief  Custom audio processor
 */
@protocol ByteRTCAudioProcessor <NSObject>
/** 
 * @type callback
 * @hidden 
 * @deprecated since 342, use ByteRTCAudioFrameProcessor instead.
 * @region Audio processing
 * @author majun.lvhiei
 * @brief Get the audio frames collected by the RTC SDK, and perform custom processing, and finally give the processed audio frames to the RTC SDK for encoding and transmission. The audio frames collected by the
 * @param audioFrame RTC SDK can be customized to directly modify the data in the audio buffer. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @return   <br>
 *        0: Unprocessed <br>
 *         > 0: Processing succeeded <br>
 *         < 0: Processing failed
 * @notes Before audio custom processing, you need to call `registerLocalAudioProcessor` to set the audio custom processor.
 */
- (int)processAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;

@end
/** 
 * @type callback
 * @author majun.lvhiei
 * @brief  Custom audio processor
 */
@protocol ByteRTCAudioFrameProcessor <NSObject>
/**  
* @type callback
* @author majun.lvhiei
* @brief Returns the address of the locally captured audio frame for custom processing.
* @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @notes <br>
*        + After custom processing, SDK will encode the processed audio frames and transmit to the remote user. If you enabled ear monitoring, the ear-monitoring audio will be processed.<br>
*        + After calling enableAudioProcessor:audioFormat:{@link #RTCVideo#enableAudioProcessor:audioFormat:} with locally captured audio frame specified, you will receive this callback.
*/
- (int)onProcessRecordAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**  
* @type callback
* @author majun.lvhiei
* @brief Returns the address of the locally captured audio frame for custom processing.
* @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @notes After calling enableAudioProcessor:audioFormat:{@link #RTCVideo#enableAudioProcessor:audioFormat:} with mixed remote audio, you will receive this callback.
*/
- (int)onProcessPlayBackAudioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
/**  
* @type callback
* @author majun.lvhiei
* @brief Returns the address of the locally captured audio frame for custom processing.
* @param stream_info Information of the audio stream. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
* @param audioFrame The address of the audio frame. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}
* @notes After calling enableAudioProcessor:audioFormat:{@link #RTCVideo#enableAudioProcessor:audioFormat:}, with audio streams of the remote users, you will receive this callback.
*/
- (int)onProcessRemoteUserAudioFrame:(ByteRTCRemoteStreamKey * _Nonnull)stream_info  audioFrame:(ByteRTCAudioFrame * _Nonnull)audioFrame;
@end

#pragma mark - AudioDeviceManager

/** 
 * @hidden
 * @type callback
 * @region audio management
 * @author dixing
 * @brief Audio device event callback
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCAudioDeviceEventHandler<NSObject>
/** 
 * @hidden
 * @type callback
 * @region audio management
 * @author dixing
 * @brief Get microphone volume
 * @param volume Volume size
 */
- (void)onRecordingAudioVolumeIndication:(int)volume;
@end
/** 
 * @type api
 * @hidden(iOS)
 * @brief Audio Device Management
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioDeviceManager : NSObject
/**
 * @hidden
 * @type api
 * @author dixing
 */
- (instancetype _Nonnull )initDeviceManager:(id<ByteRTCAudioDeviceEventHandler> _Nonnull)handler;
/** 
 * @type api
 * @hidden(iOS)
 * @region  Audio device management
 * @author dixing
 * @brief  Gets the list of the audio playback devices. When receiving rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} for audio playback device change, you can call this API to get the latest list of audio playback devices.
 * @return  The list of all audio playback devices. See ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}.
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioPlaybackDevices;
/** 
 * @type api
 * @hidden(iOS)
 * @region  Audio Device Management
 * @author dixing
 * @brief  Get the list of audio capture devices. When receiving rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:{@link #ByteRTCEngineDelegate#rtcEngine:onAudioDeviceStateChanged:device_type:device_state:device_error:} for audio capture device change, you can call this API to get the latest list of audio capture devices.
 * @return The list of audio capture devices.. See ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}.
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateAudioCaptureDevices;
/** 
 * @type api
 * @region Audio Facility Management
 * @author liuxiaowu
 * @brief Set the audio capture device to follow the OS default setting or not.
 * @param followed
 *        + true: follow the os default setting. You can not call setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} at the same time.
 *        + false: do not follow the os default setting. You can call setAudioCaptureDevice:{@link #ByteRTCAudioDeviceManager#setAudioCaptureDevice:} to set the audio capture device.
 */
- (void)followSystemCaptureDevice:(BOOL)followed;
/** 
 * @type api
 * @region Audio Facility Management
 * @author liuxiaowu
 * @brief Set the audio playback device to follow the OS default setting or not.
 * @param followed <br>
 *        + true: follow the os default setting. You can not call setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} at the same time.
 *        + false: do not follow the os default setting. You can call setAudioPlaybackDevice:{@link #ByteRTCAudioDeviceManager#setAudioPlaybackDevice:} to set the audio playback device.
 */
- (void)followSystemPlaybackDevice:(BOOL)followed;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio device management
 * @author dixing
 * @brief Sets the audio playback device.
 * @param  deviceID Device ID. You can get the ID by calling
 * EnumerateAudioPlaybackDevices{@link #EnumerateAudioPlaybackDevices}.
 * @return    <br>
 *         + 0: Success <br>
 *         + < 0: Failure <br>
 * @notes After you call followSystemPlaybackDevice:{@link #ByteRTCAudioDeviceManager#followSystemPlaybackDevice:} to set the audio playback device to follow the system setting, you cannot call this API to set the audio playback device.
 */
- (int)setAudioPlaybackDevice:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Gets the current audio playback device.
 * @param  deviceID audio playback device ID
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int)getAudioPlaybackDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Set the audio capture devices.
 * @param  deviceID Audio capture device ID. You can get the device list by calling enumerateAudioCaptureDevices{@link #ByteRTCAudioDeviceManager#EnumerateAudioCaptureDevices}.
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 * @notes After you call followSystemCaptureDevice:{@link #ByteRTCAudioDeviceManager#followSystemCaptureDevice:} to set the audio playback device to follow the system setting, you cannot call this API to set the audio capture device.
 */
- (int)setAudioCaptureDevice:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Gets the current audio capture device.
 * @param  deviceID audio capture device ID.
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int)getAudioCaptureDevice:(NSString *_Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Set the mute state of the current audio capture device. It's not mute by default.
 * @param  mute <br>
 *        + True: mute <br>
 *        + False: non-mute <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) setAudioCaptureDeviceMute:(bool)mute;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Gets information about the mute state of the current audio capture device.
 * @param  Mute <br>
 *        + True: mute <br>
 *        + False: non-mute <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) getAudioCaptureDeviceMute:(bool * _Nonnull)mute;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Set the mute state of the current audio playback device. It's not mute by default.
 * @param  mute <br>
 *        + True: mute <br>
 *        + False: non-mute <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) setAudioPlaybackDeviceMute:(bool)mute;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Gets the mute state of the current audio playback device.
 * @param  mute <br>
 *        + True: mute <br>
 *        + False: non-mute <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) getAudioPlaybackDeviceMute:(bool * _Nonnull)mute;
/** 
 * @type api
 * @hidden(iOS)
 * @region  Audio Device Management
 * @author dixing
 * @brief Set the current audio capture device volume
 * @param  volume Audio capture device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) setAudioCaptureDeviceVolume:(unsigned int)volume;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Get the current audio capture device volume
 * @param  volume Audio capture device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) getAudioCaptureDeviceVolume:(unsigned int * _Nonnull)volume;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Sets the current audio playback device volume
 * @param  volume Audio playback device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) setAudioPlaybackDeviceVolume:(unsigned int)volume;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Get the current audio playback device volume
 * @param  volume Audio playback device volume. The range is [0,255]. <br>
 *        + [0,25]: nearly silent; <br>
 *        + [25,75]: low volume; <br>
 *        + [76,204]: medium volume; <br>
 *        + [205,255]: high volume. <br>
 * @return   Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 */
- (int) getAudioPlaybackDeviceVolume:(unsigned int * _Nonnull)volume;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Start the audio playback device test.   <br>
 *        This method tests whether the playback device works properly. The SDK plays the specified audio file. If the tester can hear the sound, the playback device can work normally.
 * @param  testAudioFilePath The absolute path of the audio file. The path string uses UTF-8 encoding format and supports the following audio formats: mp3, aac, m4a, 3gp, wav.
 * @param  interval playback device test volume callback interval
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 * @notes   <br>
 *        + This method must be called before joining the room and cannot be applied at the same time as other audio device testing functions. <br>
 *        + Call StopAudioPlaybackDeviceTest{@link #ByteRTCAudioDeviceManager#StopAudioPlaybackDeviceTest} to stop the test. <br>
 */
- (int)startPlaybackDeviceTest:(NSString *_Nonnull)testAudioFilePath interval:(int)interval;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Stop audio playback device testing.
 * @return  Method call result   <br>
 *         + 0: Success. <br>
 *         + < 0: failure <br>
 * @notes  After calling StartAudioPlaybackDeviceTest{@link #ByteRTCAudioDeviceManager#StartAudioPlaybackDeviceTest}, call this method to stop the test.
 */
- (int)stopPlaybackDeviceTest;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Try to initialize the audio playback device for device test.
 * @param deviceID device ID
 * @return Device status error code: <br>
 *         + 0: Status normal.  <br>
 *         + -1: Test not excuted. <br>
 *         + -2: Init failed due to lack of permission. <br>
 *         + -3: The device does not exist. No device or device removed. <br>
 *         + -4: The audio format is not supported. <br>
 *         + -5: Error for other reasons
 * @notes  <br>
 *        + Call this API before joining the room; <br>
 *        + You may still fail to enable the device even you passed the test. Occupation by other application or shortage of CPU / memory may cause the failure.
 */
- (int)initAudioPlaybackDeviceForTest:(NSString * _Nonnull)deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Try to initialize the audio capture device for device test.
 * @param deviceID device ID
 * @return Device status error code: <br>
 *         + 0: Status normal.  <br>
 *         + -1: Test not excuted. <br>
 *         + -2: Init failed due to lack of permission. <br>
 *         + -3: The device does not exist. No device or device removed. <br>
 *         + -4: The audio format is not supported. <br>
 *         + -5: Error for other reasons
 * @notes  <br>
 *        + Call this API before joining the room; <br>
 *        + You may still fail to enable the device even you passed the test. Occupation by other application or shortage of CPU / memory may cause the failure.
 */
- (int)initAudioCaptureDeviceForTest:(NSString * _Nonnull)deviceID;
/**  
 * @type api
 * @hidden(macOS)
 * @region Audio Device Management
 * @author dixing
 * @brief Switch audio playback device to the speaker or the earpiece. The default playback device is the speaker.
 * @param  enable <br>
 *        + True: switch to the speaker <br>
 *        + False: switch to the earpiece <br>
 * @notes This method is only valid on mobile devices.
 */
- (void)setEnableSpeakerphone:(bool)enable;
@end

/** 
 * @hidden
 * @type keytype
 * @brief  Verification information required to use automatic speech recognition services
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCASRConfig : NSObject
/** 
 *  @brief Application ID
 */
@property(copy, nonatomic) NSString *_Nonnull appId;
/** 
 *  @brief User ID
 */
@property(copy, nonatomic) NSString *_Nonnull userId;
/** 
 *  @brief Access token
 */
@property(copy, nonatomic) NSString *_Nonnull accessToken;
/** 
 * @hidden
 *  @brief Private key. Signature  cannot be empty in authentication mode, and it is empty in token authentication mode. See [About Authentication](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#uh8x72)
 */
@property(copy, nonatomic) NSString *_Nonnull secretKey;
/** 
 *  @brief For scenario information. See Business Clusters (https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#aI4WCt)
 */
@property(copy, nonatomic) NSString *_Nonnull cluster;
/** 
 *  @brief Authentication mode. See ByteRTCASRAuthorizationType{@link #ByteRTCASRAuthorizationType}
 */
@property(assign, nonatomic) ByteRTCASRAuthorizationType authorizationType;

@end

#pragma mark - ByteASREventHandler

/** 
 * @hidden
 * @type keytype
 * @brief  Speech recognition service usage status callback
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCASREngineEventHandler<NSObject>
@required
/** 
 * @hidden
 * @type callback
 * @brief  Speech recognition service starts successful callback
 */
- (void)onSuccess;
@required
/** 
 * @hidden
 * @type callback
 * @brief The voice-to-text callback is successful, and the callback returns the full amount of messages after recognition.
 * @param message Text message obtained after the recognition is completed
 * @notes If the network connection is interrupted during the recognition process, the callback information after reconnection contains only the text message recognized after reconnection, and no longer contains the message recognized after the last connection.
 */
- (void)onMessage:(NSString *_Nonnull)message;
@required
/** 
 * @hidden
 * @type callback
 * @brief This callback is triggered when an error event occurs within the speech recognition service.
 * @param errorCode Error code <br>
 *         + < 0: Parameter error or API call order error. See ByteRTCASRErrorCode{@link #ByteRTCASRErrorCode}; <br>
 *         + > 0: See [speech recognition service error code](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#VPknqs)
 * @param errorMessage Error reason description
 */
- (void)onError:(NSInteger)errorCode withErrorMessage:(NSString *_Nonnull)errorMessage;
@end

/** 
 * @type keytype
 * @brief  Mixing configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingConfig : NSObject
/** 
 * @brief Mix playback type. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}
 */
@property(assign, nonatomic) ByteRTCAudioMixingType type;
/** 
 * @brief Mix playback times
 *        + Play_count < = 0: Infinite loop <br>
 *        + Play_count == 1: Play once (default) <br>
 *        + Play_count > 1: Play play_count times
 */
@property(assign, nonatomic) NSInteger playCount;
/** 
 * @brief The position of the audio file playback progress bar during audio mixing, the parameter should be an integer, in milliseconds.
 */
@property(assign, nonatomic) NSInteger position;
/** 
 * @brief Set the time interval (ms) for the audio file playing progress callback. The `rtcEngine:onAudioMixingPlayingProgress:progress:` callback then will be triggered according to the set value, no callback by default.  <br>
 *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms.  <br>
 *       + If the value is less than or equals to 0, the callback will not be triggered.  <br>
 */
@property(assign, nonatomic) NSInteger callbackOnProgressInterval;

@end

/** 
 * @type keytype
 * @brief  Configuration related to audio attribute information prompt   <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesConfig : NSObject
/** 
 * @brief Prompt interval in ms <br>
 *        + `<= 0`: Turn off prompt <br>
 *        + `(0,100]`: Invalid interval value, and will be automatically reset to 100ms. <br>
 *        + `> 100`: the actual value of interval
 */
@property(assign, nonatomic) NSInteger interval;
/** 
 * @brief Whether to enable audio spectrum detection
 */
@property(assign, nonatomic) BOOL enable_spectrum;
/** 
 * @brief Whether to enable Voice Activity Detection
 */
@property(assign, nonatomic) BOOL enable_vad;
@end
/** 
 * @type keytype
 * @brief Audio properties   <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioPropertiesInfo : NSObject
/** 
 * @brief linear volume. The value is in linear relation to the original volume. The higher the value, the higher the volume. The range is [0,255]. <br>
 *        - [0, 25]: Silence <br>
 *        - [26, 75]: Low volume <br>
 *        - [76, 204]: Medium volume <br>
 *        - [205, 255]: High volume <br>
 */
@property(assign, nonatomic) NSInteger linearVolume;
/** 
 * @brief non-linear volume in dB. The value is in proportion to the log value of the original volume. You can use the value to recognize the Active Speaker in the room. The range is [-127, 0]. <br>
 *        - [-127, -60]: Silence <br>
 *        - [-59, -40]: Low volume <br>
 *        - [-39, -20]: Medium volume <br>
 *        - [-19, 0]: High volume <br>
 */
@property(assign, nonatomic) NSInteger nonlinearVolume;
/** 
 * @brief Voice Activity Detection (VAD) result
 *        + 1: Voice activity detected.<br>
 *        + 0: No voice activity detected.<br>
 *        + -1: VAD not activated.<br>
 */
@property(assign, nonatomic) NSInteger vad;
/** 
 * @brief Spectrum array. The default length is 257.
 */
@property(copy, nonatomic) NSArray<NSNumber*> * _Nonnull spectrum;
@end

/** 
 * @type keytype
 * @brief Local audio properties
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLocalAudioPropertiesInfo : NSObject

/** 
 * @brief See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
@property(assign, nonatomic) ByteRTCStreamIndex streamIndex;
/** 
 * @type keytype
 * @brief See ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;

@end

/** 
 * @type keytype
 * @brief Remote audio properties
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteAudioPropertiesInfo : NSObject
/** 
 * @type keytype
 * @brief See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 */
@property(strong, nonatomic) ByteRTCRemoteStreamKey *_Nonnull streamKey;
/** 
 * @type keytype
 * @brief See ByteRTCAudioPropertiesInfo{@link #ByteRTCAudioPropertiesInfo}
 */
@property(strong, nonatomic) ByteRTCAudioPropertiesInfo *_Nonnull audioPropertiesInfo;

@end

/** 
 * @type keytype
 * @brief Coordinate value of the local user's position in the rectangular coordinate system in the RTC room.
 */
BYTERTC_APPLE_EXPORT @interface Position : NSObject
/** 
 * @brief X-coordinate
 */
@property(nonatomic, assign) int x;
/** 
 * @brief Y-coordinate
 */
@property(nonatomic, assign) int y;
/** 
 * @brief Z-coordinate
 */
@property(nonatomic, assign) int z;

@end
