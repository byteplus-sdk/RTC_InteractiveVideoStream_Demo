/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Audio Defines
 */

#pragma once

#include "bytertc_common_defines.h"
#include <string.h>
// use fft size 512 to calculate spectrum, so spectrum size is 512 / 2 + 1 = 257
#define SPECTRUM_SIZE 257

namespace bytertc {

/** 
 * @type keytype
 * @brief Audio sample rate in Hz.
 */
enum AudioSampleRate {
    /** 
     * @brief Default value.
     */
    kAudioSampleRateAuto = -1,
    /** 
     * @brief 8000
     */
    kAudioSampleRate8000 = 8000,
    /** 
     * @brief 16000
     */
    kAudioSampleRate16000 = 16000,
    /** 
     * @brief 32000
     */
    kAudioSampleRate32000 = 32000,
    /** 
     * @brief 44100
     */
    kAudioSampleRate44100 = 44100,
    /** 
     * @brief 48000
     */
    kAudioSampleRate48000 = 48000
};

/** 
 * @type keytype
 * @brief Audio channel
 */
enum AudioChannel {
    /** 
     * @brief Default value.
     */
    kAudioChannelAuto = -1,
    /** 
     * @brief Mono channel
     */
    kAudioChannelMono = 1,
    /** 
     * @brief Dual channels
     */
    kAudioChannelStereo = 2
};

/** 
 * @type keytype
 * @brief Audio format
 */
struct AudioFormat {
    /** 
     * @brief Audio sample rate. See AudioSampleRate{@link #AudioSampleRate}
     */
    AudioSampleRate sample_rate;
    /** 
     * @brief Audio channels. See AudioChannel{@link #AudioChannel}
     */
    AudioChannel channel;
};
/** 
 * @type keytype
 * @brief The type of the audio for the audio processor
 */
enum AudioProcessorMethod{
    /** 
     * @brief Locally captured audio frame
     */
    kAudioFrameProcessorRecord = 0,
    /** 
     * @brief The mixed remote audio
     */
    kAudioFrameProcessorPlayback = 1,
    /** 
     * @brief The audio streams from remote users
     */
    kAudioFrameProcessorRemoteUser = 2,
};
/** 
 * @type keytype
 * @brief Type of audio device
 */
enum RTCAudioDeviceType {
    /** 
     * @brief Unknown device
     */
    kRTCAudioDeviceTypeUnknown = -1,
    /** 
     * @brief Speaker or headphone
     */
    kRTCAudioDeviceTypeRenderDevice = 0,
    /** 
     * @brief Microphone
     */
    kRTCAudioDeviceTypeCaptureDevice = 1,
    /** 
     * @brief Screen capturing audio device
     */
    kRTCAudioDeviceTypeScreenCaptureDevice = 2,
};

/** 
 * @type keytype
 * @brief  Audio route device
 */
enum AudioRoute {
    /** 
     * @brief unknown device
     */
    kAudioRouteUnknown = -1,
    /** 
     * @brief Wired earphones
     */
    kAudioRouteHeadset = 1,
    /** 
     * @brief Earpiece
     */
    kAudioRouteEarpiece = 2,
    /** 
     * @brief Speaker
     */
    kAudioRouteSpeakerphone = 3,
    /** 
     * @brief Bluetooth earphones
     */
    kAudioRouteHeadsetBluetooth = 4,
    /** 
     * @brief USB Device
     */
    kAudioRouteHeadsetUSB = 5
};

/** 
 * @type keytype
 * @brief  Audio playback device
 */
enum AudioPlaybackDevice {
    /** 
     * @brief Wired earphones
     */
    kAudioPlaybackDeviceHeadset = 1,
    /** 
     * @brief Earpiece
     */
    kAudioPlaybackDeviceEarpiece = 2,
    /** 
     * @brief Speaker
     */
    kAudioPlaybackDeviceSpeakerphone = 3,
    /** 
     * @brief Bluetooth earphones
     */
    kAudioPlaybackDeviceHeadsetBluetooth = 4,
    /** 
     * @brief USB Device
     */
    kAudioPlaybackDeviceHeadsetUSB = 5
};

/** 
 * @hidden (macOS, Windows)
 * @type keytype
 * @brief  Audio scene type. <br>
 *        After selecting an audio scene, RTC will automatically collect and play equipment and collect and play status according to the client side audio, applicable to call volume/media volume. <br>
 *         You can set an audio scene by calling setAudioScenario{@link #setAudioScenario}. <br>
 *        If the preset audio scene type cannot meet your business needs, please contact technical support classmate for customization.
 */
enum AudioScenarioType {
    /** 
     * @brief Music scene. Default to this scenario. <br>
     *        This scene is suitable for scenes that require musical expression. Such as live music, etc. <br>
     *         Audio capture playback device and capture playback status, the mapping to the volume type is as follows: <br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td>Media volume</td><td>Call volume</td><td>/</td></tr>
     *            <tr><td>Wired Headset</td><td>Media volume</td><td> Media Volume</td><td>/</td></tr>
     *            <tr><td>Bluetooth Headset</td><td>Media Volume</td><td>Media Volume</td><td>Even if the Bluetooth headset has a microphone, you can only use the build-in microphone for local audio capture.</td></tr>
     *         </table>
     */
    kAudioScenarioTypeMusic = 0,
    /** 
     * @brief High-quality call scenarios. <br>
     *        This scene is suitable for scenes that require musical expression. However, I hope to be able to use the microphone on the Bluetooth headset for audio collection.
     *        This scene can take into account the audio experience when playing/using the Bluetooth headset; and avoid sudden changes in hearing caused by volume type switching when using the Bluetooth headset as much as possible. <br>
     *         Audio capture playback device and capture playback status, the mapping to the volume type is as follows: <br>
     *         <table>
     *            <tr><th></th><th>Mic Off</th><th>Mic On</th><th>Remarks</th><tr>
     *            <tr><td>Build-in microphone and speaker/earpiece</td><td> Media volume </td><td> call volume </td><td>/</td></tr>
     *            <tr><td> Wired headset </td><td> Media volume </td><td> Media Volume </td><td>/</td></tr>
     *            <tr><td> Bluetooth Headset </td><td> Call Volume </td><td> Call Volume </td><td> Ability to use the microphone included in the Bluetooth headset for audio capture. </td></tr>
     *         </table>
     */
    kAudioScenarioTypeHighQualityCommunication = 1,
    /** 
     * @brief Pure call volume scene. <br>
     *         In this scenario, regardless of the client side audio acquisition and playback device and the acquisition and playback status, the call volume is used throughout the process.
     *         Suitable for calls or meeting scenarios that require frequent access. <br>
     *        This scene can maintain a unified audio mode without sudden volume changes;
     *        Eliminate echoes to the greatest extent, so that the call definition is optimal;
     *        When using Bluetooth headsets, you can use the microphone on the Bluetooth headset for audio collection. <br>
     *         However, the volume of other audio played using media volume will be lowered and the sound quality will deteriorate.
     */
    kAudioScenarioTypeCommunication = 2,
    /** 
     * @brief Pure media scene. It is generally not recommended. <br>
     *         In this scenario, regardless of the client side audio acquisition and playback device and the acquisition and playback status, the media volume is used throughout the process.
     */
    kAudioScenarioTypeMedia = 3,
    /** 
     * @brief Game media scene. Only suitable for game scenes.   <br>
     *         In this scenario, the Bluetooth headset uses the call volume, and other devices use the media volume.
     *        Echo and howling are easy to occur when talking outside and there is no game sound cancellation optimization.
     */
    kAudioScenarioTypeGameStreaming = 4,
};

/** 
 * @type keytype
 * @brief  Change sound effect type
 */
enum VoiceChangerType {
    /** 
     * @brief Acoustic, no special effects
     */
    kVoiceChangerTypeOriginal = 0,
    /** 
     * @brief Giant
     */
    kVoiceChangerTypeGiant = 1,
    /** 
     * @brief Chipmunk
     */
    kVoiceChangerTypeChipmunk = 2,
    /** 
     * @brief Little yellow man
     */
    kVoiceChangerTypeMinionst = 3,
    /** 
     * @brief Trill
     */
    kVoiceChangerTypeVibrato = 4,
    /** 
     * @brief Robot
     */
    kVoiceChangerTypeRobot = 5,
};

/** 
 * @type keytype
 * @brief  Reverb effect type
 */
enum VoiceReverbType {
    /** 
     * @brief Acoustic, no special effects
     */
    kVoiceReverbTypeOriginal = 0,
    /** 
     * @brief Echo
     */
    kVoiceReverbTypeEcho = 1,
    /** 
     * @brief Concert
     */
    kVoiceReverbTypeConcert = 2,
    /** 
     * @brief Ethereal
     */
    kVoiceReverbTypeEthereal = 3,
    /**
     * @brief KTV
     */
    kVoiceReverbTypeKTV = 4,
    /** 
     * @brief Recording studio
     */
    kVoiceReverbTypeStudio = 5,
};

/** 
 * @type keytype
 * @brief User ID of the source of the audio stream and the corresponding volume.
 */
struct AudioVolumeInfo {
    /** 
     * @brief Linear volume, the value range is: [0,255], which has a linear relationship with the original volume.
     * The larger the value, the greater the volume. Silence is below 25 (absolutely silent is 0, below 25 there is basically no sound, which can be regarded as silent),
     * low volume is 25~76, medium volume is 76~204, and high volume is above 204
     */
    int linear_volume;
    /** 
     * @brief Non-linear volume, the value range is: [-127, 0], the unit is dB. This volume range is a logarithmic conversion of the original volume,
     * and the resolution is more sensitive at medium and low volume, which is suitable for identification as an Active Speaker (the most active user in the room).
     * The high volume is 0~-20dB, the medium volume is -20~-40dB, and the low volume is -40~-60dB. If it is lower than -60dB, it is silent.
     */
    int nonlinear_volume;
    /** 
     * @brief User of the audio stream source ID
     */
    const char* uid;
};

/** 
 * @type keytype
 * @brief  Audio mix file playback status.
 */
enum AudioMixingState {
    /** 
     * @brief Mix loaded
     */
    kAudioMixingStatePreloaded = 0,
    /** 
     * @brief Mix is playing
     */
    kAudioMixingStatePlaying,
    /** 
     * @brief Mix Pause
     */
    kAudioMixingStatePaused,
    /** 
     * @brief Mixing stopped
     */
    kAudioMixingStateStopped,
    /** 
     * @brief Mix playback failed
     */
    kAudioMixingStateFailed,
    /** 
     * @brief End of mixing
     */
    kAudioMixingStateFinished,
    /** 
     * @brief Prepare PCM Mix
     */
    kAudioMixingStatePCMEnabled,
    /** 
     * @brief End of PCM mix playback
     */
    kAudioMixingStatePCMDisabled,
};
/** 
 * @type keytype
 * @brief Error code for audio mixing
 */
enum AudioMixingError {
    /** 
     * @brief OK
     */
    kAudioMixingErrorOk = 0,
    /** 
     * @brief Preload failed. Invalid path or the length exceeds 20s.
     */
    kAudioMixingErrorPreloadFailed,
    /** 
     * @brief Mixing failed. Invalid path or fail to open the file.
     */
    kAudioMixingErrorStartFailed,
    /** 
     * @brief Invalid mixID
     */
    kAudioMixingErrorIdNotFound,
    /** 
     * @brief Invalid position
     */
    kAudioMixingErrorSetPositionFailed,
    /** 
     * @brief Invalid volume. The range is [0, 400].
     */
    kAudioMixingErrorInValidVolume,
    /** 
     * @brief Another file was preloaded for mixing. Call unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} first.
     */
    kAudioMixingErrorLoadConflict,
    /** 
     * @brief Do not support the mix type.
     */
    kAudioMixingErrorIdTypeNotMatch,
    /** 
     * @brief Invalid pitch value.
     */
    kAudioMixingErrorInValidPitch,
    /** 
     * @brief Invalid audio track.
     */
    kAudioMixingErrorInValidAudioTrack,
    /** 
     * @brief Mixing starting
     */
    kAudioMixingErrorIsStarting,
    /** 
     * @brief Invalid playback speed
     */
    kAudioMixingErrorInValidPlaybackSpeed,
    /** 
     * @hidden
     * @deprecated since 325.1
     * @brief  Mix error code, failed, abandoned
     */
    kAudioMixingErrorCanNotOpen = 701,
};

/** 
 * @type keytype
 * @hidden (Windows)
 * @brief  Whether to turn on the earphone monitoring function
 */
enum EarMonitorMode {
    /** 
     * @brief Not open
     */
    kEarMonitorModeOff = 0,
    /** 
     * @brief Open
     */
    kEarMonitorModeOn = 1,
};

/** 
 * @type keytype
 * @brief  Audio input source type
 */
enum AudioSourceType {
    /** 
     *  Custom Capture Audio Source
     */
    kAudioSourceTypeExternal = 0,
    /** 
     *  RTC SDK internal acquisition audio source
     */
    kAudioSourceTypeInternal,
};

/** 
 * @type keytype
 * @brief  Audio output type
 */
enum AudioRenderType {
    /** 
     *  Custom Render
     */
    kAudioRenderTypeExternal = 0,
    /** 
     *  RTC SDK internal render
     */
    kAudioRenderTypeInternal,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Speech recognition service authentication method, please consult the speech recognition service related classmates for details
 */
enum ASRAuthorizationType {
    /** 
     * @brief Token  authentication
     */
    kASRAuthorizationTypeToken = 0,
    /** 
     * @brief Signature  Authentication
     */
    kASRAuthorizationTypeSignature = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Verification information required to use automatic speech recognition services
 */
struct RTCASRConfig {
    /** 
     * @brief Application ID
     */
    const char* app_id;
    /** 
     * @brief User ID
     */
    const char* user_id;
    /** 
     * @brief For authentication methods. See ASRAuthorizationType{@link #ASRAuthorizationType}
     */
    ASRAuthorizationType authorization_type;
    /** 
     * @brief Access token
     */
    const char* access_token;
    /** 
     * @hidden
     * @brief Private key. Signature  cannot be empty in authentication mode, and it is empty in token authentication mode. See [About Authentication](https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#uh8x72)
     */
    const char* secret_key;
    /** 
     * @brief For scenario information. See Business Clusters (https://bytedance.feishu.cn/docs/doccnMx9153dZEpfLX2I6BkFsMg#aI4WCt)
     */
    const char* cluster;
};

/** 
 * @hidden
 * @type keytype
 * @brief  Speech recognition service error code.   <br>
 *         Except for errors caused by network reasons, the speech recognition service will retry itself, other errors will stop the service. At this time, it is recommended to call `startASR` again to restart the speech recognition function.
 */
enum RTCASRErrorCode {
    /** 
     * @brief The network connection is broken, the service is unavailable, and internal reconnection will be carried out
     */
    kRTCASRErrorNetworkInterrupted = -1,
    /** 
     * @brief Repeatedly call `startASR`. After starting the speech recognition service, you need to call `stopASR` to stop the speech recognition service before you can call `startASR` again to start the service.
     */
    kRTCASRErrorAlreadyStarted = -2,
    /** 
     * @brief The token required by the speech recognition service is empty
     */
    kRTCASRErrorTokenEmpty = -3,
    /** 
     * @brief Signature  secret_key empty in authentication mode
     */
    kRTCErrorSignatureKeyEmpty = -4,
    /** 
     * @brief User ID is empty
     */
    kRTCASRErrorUserIdNull = -5,
    /** 
     * @brief Application ID is empty
     */
    kRTCASRErrorAPPIDNull = -6,
    /** 
     * @brief Speech recognition service cluster is empty
     */
    kRTCASRErrorClusterNull = -7,
    /** 
     * @brief The speech recognition service connection failed, this version does not have speech recognition function, please contact RTC technical support.
     */
    kRTCASRErrorOperationDenied = -8
};

/** 
 * @type keytype
 * @brief Mixing type
 */
enum AudioMixingType {
    /** 
     * @brief Played at the local device only
     */
    kAudioMixingTypePlayout,
    /** 
     * @brief Sent to the remote devices only
     */
    kAudioMixingTypePublish,
    /** 
     * @brief Played at the local device and sent to the remote devices.
     */
    kAudioMixingTypePlayoutAndPublish
};

/** 
 * @type keytype
 * @brief  Mixing configuration
 */
struct AudioMixingConfig {
    /** 
     * @brief For mixing playback types. See AudioMixingType{@link #AudioMixingType}
     */
    AudioMixingType type;
    /** 
     * @brief Mix playback times,
     *        + Play_count < = 0: Infinite loop <br>
     *        + Play_count == 1: Play once (default) <br>
     *        + Play_count > 1: Play play_count times
     */
    int play_count;
     /** 
      * @brief The position of the audio file playback progress bar during audio mixing, the parameter should be an integer, in milliseconds.
      */
     int position;
     /** 
      * @brief Set the time interval (ms) for the audio file playing progress callback. The `onAudioMixingPlayingProgress` callback then will be triggered according to the set value, no callback by default.  <br>
      *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
      *       + If the value is less than or equals to 0, the callback will not be triggered.  <br>
      */
    int64_t callback_on_progress_interval = 0;
};

/** 
 * @type keytype
 * @brief  Mix playback channel type
 */
enum AudioMixingDualMonoMode{
    /** 
     * @brief Consistent with audio files
     */
    kAudioMixingDualMonoModeAuto,
    /** 
     * @brief Only the left channel audio in the audio file can be heard
     */
    kAudioMixingDualMonoModeL,
    /** 
     * @brief Only the right channel audio in the audio file can be heard
     */
    kAudioMixingDualMonoModeR,
    /** 
     * @brief Can hear the left and right audio channels in the audio file at the same time
     */
    kAudioMixingDualMonoModeMix
};

/** 
 * @type keytype
 * @brief Configuration for audio property prompt
 */
struct AudioPropertiesConfig {
    /** 
     * @brief Prompt interval in ms <br>
     *        + `<= 0`: Turn off prompt <br>
     *        + `(0,100]`: Invalid interval value, and will be automatically reset to 100ms. <br>
     *        + `> 100`: the actual value of interval
     */
    int interval;

    /** 
     * @brief Whether to enable audio spectrum detection
     */
    bool enable_spectrum = false;

    /** 
     * @brief Whether to enable Voice Activity Detection
     */
    bool enable_vad = false;
};
/** 
 * @type keytype
 * @brief Audio properties   <br>
 */
struct AudioPropertiesInfo {
    /** 
     * @brief linear volume. The value is in linear relation to the original volume. The higher the value, the higher the volume. The range is [0,255]. <br>
     *        - [0, 25]: Silence <br>
     *        - [26, 75]: Low volume <br>
     *        - [76, 204]: Medium volume <br>
     *        - [205, 255]: High volume <br>
     */
    int linear_volume;
    /** 
     * @brief non-linear volume in dB. The value is in proportion to the log value of the original volume. You can use the value to recognize the Active Speaker in the room. The range is [-127, 0]. <br>
     *        - [-127, -60]: Silence <br>
     *        - [-59, -40]: Low volume <br>
     *        - [-39, -20]: Medium volume <br>
     *        - [-19, 0]: High volume <br>
     */
    int nonlinear_volume;
    /** 
     * @brief Spectrum array. The default length is 257.
     */
    float spectrum[SPECTRUM_SIZE] = {0};
    /** 
     * @brief Voice Activity Detection (VAD) result
     *        + 1: Voice activity detected.<br>
     *        + 0: No voice activity detected.<br>
     *        + -1: VAD not activated.<br>
     */
    int vad = -1;
};

/** 
 * @type keytype
 * @brief Remote audio properties
 */
struct RemoteAudioPropertiesInfo {
    /** 
     * @type keytype
     * @brief Remote stream information. See RemoteStreamKey{@link #RemoteStreamKey}.
     */
    RemoteStreamKey stream_key;
    /** 
     * @type keytype
     * @brief See AudioPropertiesInfo{@link #AudioPropertiesInfo}.
     */
    AudioPropertiesInfo audio_properties_info;
};

/** 
 * @type keytype
 * @brief Local audio properties
 */
struct LocalAudioPropertiesInfo {
    /** 
     * @brief See StreamIndex{@link #StreamIndex}.
     */
    StreamIndex stream_index;
    /** 
     * @type keytype
     * @brief See AudioPropertiesInfo{@link #AudioPropertiesInfo}.
     */
    AudioPropertiesInfo audio_properties_info;
};

/** 
 * @type keytype
 * @brief  Sound quality gear
 *         Call `setAudioProfile` to set the sound quality gear
 */
enum AudioProfileType {
    /** 
     * @brief Default sound quality
     *         The sound quality configuration of RoomProfileType{@link #RoomProfileType} set by the server or client side
     */
    kAudioProfileTypeDefault = 0,
    /** 
     * @brief Smooth sound quality.   <br>
     *         Mono, sampling rate of 16kHz, coding rate of 24kbps. <br>
     *         Fluent priority, low latency, low power consumption, low traffic consumption, suitable for most game scenarios, such as MMORPG, MOBA, FPS and other game team voice, team voice, national war voice, etc.
     */
    kAudioProfileTypeFluent = 1,
    /** 
     * @brief Standard sound quality.   <br>
     *         Mono, the sampling rate is 48kHz, the coding rate is 48kbps. <br>
     *         Suitable for scenes with certain requirements for sound quality, while the delay, power consumption and traffic consumption are relatively moderate, suitable for educational scenes and Werewolf games such as Sirius.
     */
    kAudioProfileTypeStandard = 2,
    /** 
     * @brief High-definition sound quality   <br>
     *         Dual channel, sampling rate is 48kHz, coding rate is 128kbps. <br>
     *         Ultra-high sound quality, while the delay, power consumption and flow consumption are relatively large, suitable for music scenes such as Lianmai PK. <br>
     *        Game scenes are not recommended.
     */
    kAudioProfileTypeHD = 3,
    /** 
     * @brief Standard quality. Dual-channel audio with a sampling rate of 48 KHz, and the maximum encoding bit rate is 80 Kbps.
     */
    kAudioProfileTypeStandardStereo = 4,
    /** 
     * @brief Music quality. Mono-channel audio with a sampling rate of 48 KHz, and the maximum encoding bit rate is 128 Kbps.
     */
    kAudioProfileTypeHDMono = 5,
};

/** 
 * @type keytype
 * @brief Coordinate value of the local user's position in the rectangular coordinate system in the RTC room.
 */
struct Position {
    /** 
     * @brief X-coordinate
     */
    int x;
    /** 
     * @brief Y-coordinate
     */
    int y;
    /** 
     * @brief Z-coordinate
     */
    int z;
    /**
     * @hidden
     */
    bool isEqual(const Position& pos) const {
        return x == pos.x && y == pos.y && z == pos.z;
    }
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief Accessibility to volume setting
 */
enum AudioAbilityType {
    /** 
     * @brief Unknown
     */
    kAudioAbilityTypeUnknown = -1,
    /** 
     * @brief The volume setting is accessible.
     */
    kAudioAbilityAble = 0,
    /** 
     * @brief The volume setting is inaccessible.
     */
    kAudioAbilityUnable = 1,
};

/** 
 * @type keytype
 * @brief Audio device information
 */
struct AudioDeviceInfo {
    /** 
     * @brief Device ID
     */
    char device_id[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief Device alias
     */
    char device_name[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief ID of the sound card connected to the audio device. With this variable, you can choose the speaker and microphone connected to the same sound card with ease.
     */
    char device_container_id[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief ID of the device vendor
     */
    int64_t device_vid;
    /** 
     * @brief Product number of the device
     */
    int64_t device_pid;
    /** 
     * @brief Connection type of the device
     */
    DeviceTransportType transport_type;
    /** 
     * @brief Accessibility to the volume setting
     */
    AudioAbilityType volume_settable;
    /** 
     * @brief Whether the device is the default device
     */
    bool is_system_default;
    /**
     * @hidden
     */
    AudioDeviceInfo() {
        memset(device_id, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_name, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_container_id, 0, MAX_DEVICE_ID_LENGTH);
        this->device_vid = 0;
        this->device_pid = 0;
        this->transport_type = DeviceTransportType::kDeviceTransportTypeUnknown;
        this->volume_settable = AudioAbilityType::kAudioAbilityTypeUnknown;
        this->is_system_default = false;
    }
    
    /**
     * @hidden
     */
    AudioDeviceInfo& operator=(const AudioDeviceInfo& src) {
        if (this != &src) {
            strncpy(device_id, src.device_id, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_name, src.device_name, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_container_id, src.device_container_id, MAX_DEVICE_ID_LENGTH - 1);
            device_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_name[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_container_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_vid = src.device_vid;
            device_pid = src.device_pid;
            transport_type = src.transport_type;
            volume_settable = src.volume_settable;
            is_system_default = src.is_system_default;
        }

        return *this;
    }
};


}  // namespace bytertc
