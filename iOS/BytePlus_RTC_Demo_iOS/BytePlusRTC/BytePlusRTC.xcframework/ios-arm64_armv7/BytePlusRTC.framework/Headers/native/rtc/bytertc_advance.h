/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Advance API
*/

#pragma once

#ifndef BYTE_RTC_ADVANCE_H__
#define BYTE_RTC_ADVANCE_H__

#include "bytertc_engine_interface.h"

#include <stdint.h>
#ifdef __ANDROID__
#include "jni.h"
#endif


#ifdef __GNUC__
#    define attribute_deprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#    define attribute_deprecated __declspec(deprecated)
#else
#    define attribute_deprecated
#endif

namespace bytertc {

/**  
 * @hidden
 * @type
 * @brief RTC Audio Dump node configuration.
 * Be consistent with the AudioSampleType enumeration and AudioSampleConfigure in the bae_audio_sample_interface
 * .
 */
struct RTCAudioSampleConfigure {
    /**
     * @hidden
     */
    bool aec_near_in_enable = false;
    /**
     * @hidden
     */
    bool aec_far_in_enable = false;
    /**
     * @hidden
     */
    bool aec_far_in_ref_enable = false;
    /**
     * @hidden
     */
    bool aec_out_enable = false;
    /**
     * @hidden
     */
    bool agc_out_enable = false;
    /**
     * @hidden
     */
    bool ns_out_enable = false;
    /**
     * @hidden
     */
    bool ainr_out_enable = false;
    /**
     * @hidden
     */
    bool mix_out_enable = false;
    /**
     * @hidden
     */
    bool send2encoder_enable = false;
    /**
     * @hidden
     */
    bool audio_share_in_enable = false;
    /**
     * @hidden
     */
    bool audio_share_win_ref_enable = false;
    /**
     * @hidden
     */
    bool audio_share_out_enable = false;
    /**
     * @hidden
     */
    bool external_audio_in_enable = false;
    /**
     * @hidden
     */
    bool pitchfilter_out_enable = false;
    /**
     * @hidden
     */
    bool decoder_out_enable = false;
    /**
     * @hidden
     */
    void reset() {
        aec_near_in_enable = false;
        aec_far_in_enable = false;
        aec_far_in_ref_enable = false;
        aec_out_enable = false;
        agc_out_enable = false;
        ns_out_enable = false;
        ainr_out_enable = false;
        mix_out_enable = false;
        send2encoder_enable = false;
        audio_share_in_enable = false;
        audio_share_win_ref_enable = false;
        audio_share_out_enable = false;
        external_audio_in_enable = false;
        pitchfilter_out_enable = false;
        decoder_out_enable = false;
    }
    /**
     * @hidden
     */
    void NormalMode() {
        aec_near_in_enable = true;
        aec_far_in_ref_enable = true;
        mix_out_enable = true;
    }
    /**
     * @hidden
     */
    void AllMode() {
        aec_near_in_enable = true;
        aec_far_in_enable = true;
        aec_far_in_ref_enable = true;
        aec_out_enable = true;
        agc_out_enable = true;
        ns_out_enable = true;
        ainr_out_enable = true;
        mix_out_enable = true;
        send2encoder_enable = true;
        audio_share_in_enable = true;
        audio_share_win_ref_enable = true;
        audio_share_out_enable = true;
        external_audio_in_enable = true;
        pitchfilter_out_enable = true;
        decoder_out_enable = true;
    }
};

/**  
 * @hidden
 * @type keytype
 * @brief SDK  server environment.
 */
enum Env {
    /**  
     * @hidden
     * @brief  Online environment.
     */
    kEnvProduct = 0,
    /**  
     * @hidden
     * @brief BOE  environment.
     */
    kEnvBOE,
    /**  
     * @hidden
     * @brief  Test environment.
     */
    kEnvTest
};

attribute_deprecated
/**  
 * @hidden
 * @deprecated
 * @type api
 * @region Engine management
 * @brief Set the environment currently used by the SDK.
 * @param  [in] env The environment parameters used by the SDK are detailed in: Env{@link #Env}.
 * @return
 *        0: Setup succeeded
 *        -1: Setup failed
 * @notes
 *        1. This function is optional function, the default use of official environment;
 *        2. This function must be called before creating the RtcEngine instance createRtcEngine{@link #createRtcEngine}.
 */
BYTERTC_API int setEnv(Env env);

attribute_deprecated
/**  
 * @hidden
 * @deprecated
 * @brief  Set the device ID
 * @param  [in] device_id App to generate a unique device id based on the current software and hardware environment
 */
BYTERTC_API void setDeviceId(const char* device_id);
/**  
 * @hidden
 * @brief  Set the state of the application
 * @param  [in] engine
 *        Engine to notify
 * @param  [in] appState Application state string
 */
BYTERTC_API void setAppState(void* engine, const char* appState);

attribute_deprecated
/**  
 * @hidden
 * @deprecated
 * @type api
 * @region room management
 * @brief Private interface
 * @param  [in] parameters JSON string
 */
BYTERTC_API int setParameters(const char* parameters);

#ifdef __ANDROID__
/** 
 * @hidden(iOS,macOS,Windows,Linux)
 * @type api
 * @region Video Management
 * @brief Is used to set the shared EGLContext for the encoder. The interface needs to pass in an EGLContext of type android.opengl. EGLContext
 * If there are only C++ EGLContext, you need to perform the setHardWareEncodeContext () method setting in a threaded environment bound with EGLContext.
 * Once set, the RTC encoder can share resources with the current EGLContext.
 * If Android uses a pure C++ interface, this method must be set before the engine is created to initialize EGLContext. If there is no shared EGLContext, the parameter can be passed nullptr
 * After the engine is destroyed, clearHardWareEncodeContext () should be called to release resources
 * @param  [in] j_egl_context
 *      Pass in Java EGLContext of the android.opengl. EGLContext type
 * @return
 *      True: set successfully
 *      False: set failed
 */
BYTERTC_API bool setHardWareEncodeContext(jobject j_egl_context);

/**  
 * @hidden(iOS,macOS,Windows,Linux)
 * @type api
 * @region Video Management
 * @brief Is used to set the shared EGLContext for the encoder. The interface needs to perform method settings under the interface bound with EGLContext.
 * Once set, the RTC encoder can share resources with the current EGLContext.
 * If Android uses a pure C++ interface, this method must be set before the engine is created. If there is no threaded environment bound with EGLContext, you can use an interface with the parameter jobject instead
 * After the engine is destroyed, clearHardWareEncodeContext () should be called for resource release
 * @return
 *      True: set successfully
 *      False: set failed
 */
BYTERTC_API bool setHardWareEncodeContext();

/**  
 * @hidden(iOS,macOS,Windows,Linux)
 * @type api
 * @region  video management
 * @brief  Used to clear the shared EGLContext, after the engine is destroyed, if it is determined that it will not be used again  then this interface should be called for resource release of EGLContext
 */
BYTERTC_API void clearHardWareEncodeContext();

/**  
 * @hidden(iOS,macOS,Windows,Linux)
 * @type api
 * @region Engine management
 * @brief Used to set the ApplicationContext for Android to use by Engine,
 * If Android uses a pure C++ interface, this method must be set before the engine is created
 * @param  [in] j_egl_context
 *      Passing in Java android.content. Context type EGLContext
 */
BYTERTC_API void setApplicationContext(jobject j_application_context);
#endif

/**  
 * @hidden
 * @type api
 * @region  video management
 * @type keytype
 * @brief  Hardware acceleration device type
 */
enum HWDeviceType {
    /**  
     * @brief Unknown device type
     */
    kHWDeviceTypeNone,

    /**  
     * @brief Direct3d 11 Video acceleration device
     */
    kHWDeviceTypeD3D11,

    /**  
     * @brief Cuda  hardware acceleration device
     * @notes Cuda  is a hardware acceleration device under the nvidia platform
     */
    kHWDeviceTypeCuda,

    /**  
     * @brief Qsv acceleration device under intel  platform
     */
    kHWDeviceTypeQsv,

    /**  
     * @brief Windows  platform dx hardware acceleration device
     */
    kHWDeviceTypeDxva2,

    /**  
     * @brief Hardware acceleration device mediacodec under Android  platform
     */
    kHWDeviceTypeMediaCodec,

    /**  
     * @brief IOS, MACOS  platform hardware acceleration device VideoToolbox
     */
    kHWDeviceTypeVideoToolbox,
     /**  
     * @hidden
     * @brief Android, linux  platform hardware acceleration device egl context
     */
    kHWDeviceTypeEglContext,

    /**  
     * @hidden
     * @brief Linux, windows  platform hardware acceleration device va context
     */
    kHWDeviceTypeVaapi,
};

/**  
 * @hidden
 * @type keytype
 * @brief  Hardcoding device context
 */
enum HWDeviceContextKey {
    /**
     * @hidden
     * @brief cuda context
     */
    kHWDeviceContextKeyCudaContext,
    /**  
     * @hidden
     * @brief Derict3D11  device
     */
    kHWDeviceContextKeyD3D11Device,
    /**  
     * @hidden
     * @brief Derict3D11  device context
     */
    kHWDeviceContextKeyD3D11DeviceContext,
    /**  
     * @hidden
     * @brief Egl  device context
     */
    kHWDeviceContextKeyEglContext,
    /**  
     * @hidden
     * @brief Vadisplay  device context
     */
    kHWDeviceContextKeyVADisplay,
};

/**  
 * @hidden
 * @type keytype
 * @brief  Hardware acceleration device context
 */
class IHWDeviceContext {
public:
    /**  
     * @brief Get the hardware acceleration device context type
     * @return  Hardware acceleration device type. See HWDeviceType{@link #HWDeviceType}
     */
    virtual HWDeviceType deviceType() const = 0;
    /**  
     * @brief Set property
     * @param  [in] key
     *         Hardware acceleration device context type. See ByteRTCHWDeviceContextKey:{@link #ByteRTCHWDeviceContextKey}
     * @param  [in] value
     *         Pointer to the hardware acceleration device context address
     */
    virtual void setProperty(HWDeviceContextKey key, void* value) = 0;
    /**  
     * @brief Get the property
     * @param  [in] key
     *         Hardware acceleration device context type. See ByteRTCHWDeviceContextKey:{@link #ByteRTCHWDeviceContextKey}
     * @return  Return a pointer to the hardware acceleration device context address
     */
    virtual void* getProperty(HWDeviceContextKey key) = 0;
    /**  
     * @brief Internal context is owned by the instance
     * @return   <br>
     *         + True: hardware device context is owned by the instance object <br>
     *         + False: hardware device context is not owned by the instance object <br>
     */
    virtual bool ownContext() const = 0;
    /**  
     * @brief Sets whether context is owned by the instance object
     * @param   [in] ownContext <br>
     *        + True: context is owned by the instance object <br>
     *        + False: context is not owned by the instance object <br>
     */
    virtual void setOwnContext(bool own_context) = 0;
    /**  
     * @brief Transfer hardware device context,
     * @return  Pointer to hardware device context
     */
    virtual IHWDeviceContext* moveContext() = 0;
    /**  
     * @brief Release instance object
     */
    virtual void release() = 0;
};

/**
 * @hidden
 * @brief create a hardware device context with specified deviceType
 */
BYTERTC_API IHWDeviceContext* createHwDeviceContext(HWDeviceType device_type);

/**  
 * @hidden
 * @brief  Set the device context information of the video source
 * @param  [in] engine
 *        The engine to be set, see: IRtcEngine{@link #IRtcEngine}
 * @param  [in] hw_context
 *        Set the video frame, see: IHWDeviceContext{@link #IHWDeviceContext}
 * @notes Used when hardware encoding is passed in GPU memory
 */
BYTERTC_API void setVideoSourceHWDeviceContext(IRtcEngine* engine, IHWDeviceContext* hw_context);

/**  
 * @type api
 * @region  video management
 * @brief  Create IVideoFrame
 * @param  [in] builder Video frame build instance. See VideoFrameBuilder{@link #VideoFrameBuilder}
 */
BYTERTC_API IVideoFrame* buildVideoFrame(const VideoFrameBuilder& builder);

/**  
 * @type api
 * @region  video management
 * @brief  Send external source video data
 * @param  [in] engine
 *        The engine to be set up. See IRtcEngine{@link #IRtcEngine}
 * @param  [in] frame
 *         Input video frame. See IVideoFrame{@link #IVideoFrame}
 * @notes
 *      1. Support YUV420P, NV12, D3D texture, Cuda memory, OpenGL texture and other formats of video frames.
 *      2. This function runs in the user calling thread
 */
BYTERTC_API bool pushExternalVideoFrame(IRtcEngine* engine, const IVideoFrame* frame);

/**  
 * @hidden
 * @type keytype
 * @region  audio management
 * @brief  Audio encoding type
 */
enum AudioCodecType {
    /**  
     * @brief Unknown encoding type
     */
    kAudioCodecTypeNone = 0,
    /**  
     * @brief Opus  encoding type
     */
    kAudioCodecTypeOpus,
    /**  
     * @brief AAC  encoding type
     */
    kAudioCodecTypeAac,
};

/**
 * @hidden
 */
BYTERTC_API IAudioFrame* buildAudioFrame(const AudioFrameBuilder& builder);

/**  
 * @hidden
 * @type keytype
 * @brief  Audio frame information
 */
class IEncodedAudioFrame {
public:
    /**
     * @hidden
     */
    virtual ~IEncodedAudioFrame() {
    }
    /**
     * @hidden
     */
    virtual AudioCodecType codecType() const = 0;
    /**
     * @hidden
     */
    virtual void setCodecType(AudioCodecType codec_type) = 0;
    /**
     * @hidden
     */
    virtual int sampleRate() const = 0;
    /**
     * @hidden
     */
    virtual void setSampleRate(int sample_rate) = 0;
    /**
     * @hidden
     */
    virtual int channelsNum() const = 0;
    /**
     * @hidden
     */
    virtual void setChannelsNum(int channels_num) = 0;
    /**
     * @hidden
     */
    virtual int64_t timestampUs() const = 0;
    /**
     * @hidden
     */
    virtual void setTimestampUs(int64_t timestamp_us) = 0;
    /**
     * @hidden
     */
    virtual int64_t timestampPts() const = 0;
    /**
     * @hidden
     */
    virtual void setTimestampPts(int64_t timestamp_pts) = 0;
    /**
     * @hidden
     */
    virtual int timebaseNum() const = 0;
    /**
     * @hidden
     */
    virtual void setTimestampNum(int timebase_num) = 0;
    /**
     * @hidden
     */
    virtual int timebaseDen() const = 0;
    /**
     * @hidden
     */
    virtual void setTimestampDen(int timebase_den) = 0;

    /**
     * @hidden
     */
    virtual void setStreamMemory(const ManagedMemory& memory) = 0;
    /**
     * @hidden
     */
    virtual uint8_t* data() const = 0;
    /**
     * @hidden
     */
    virtual int dataSize() const = 0;
};

/**
 * @hidden
 */
BYTERTC_API IEncodedAudioFrame* createEncodedAudioFrame();

/**
 * @hidden
 */
BYTERTC_API IEncodedVideoFrame* buildEncodedVideoFrame(const EncodedVideoFrameBuilder& builder);

/**  
 * @hidden
 * @type callback
 * @region audio data callback
 * @brief Local audio frame monitor
 */
class ILocalEncodedAudioFrameObserver  {
public:
    /**  
     * @hidden
     * @brief  Destructor
     */
    virtual ~ILocalEncodedAudioFrameObserver() {
    }

    /**  
     * @hidden
     * @type callback
     * @region Audio data callback
     * @brief Call RegisterLocalEncodedAudioFrameObserver{@link #RegisterLocalEncodedAudioFrameObserver}, when the SDK receives local audio frame information, callback the event
     * @param  [in] type Local audio frame type. See StreamIndex{@link #StreamIndex}
     * @param  [in] audio_stream Local audio frame information. See IEncodedAudioFrame{@link #IEncodedAudioFrame}
     */
    virtual void onLocalEncodedAudioFrame(StreamIndex type, const IEncodedAudioFrame& audio_stream) = 0;
};

/**  
 * @hidden
 * @type callback
 * @region audio data callback
 * @brief Remote audio frame monitor
 */
class IRemoteEncodedAudioFrameObserver  {
public:
    /**  
     * @hidden
     * @brief  Destructor
     */
    virtual ~IRemoteEncodedAudioFrameObserver () {
    }

    /**  
     * @hidden
     * @type callback
     * @region Audio data callback
     * @brief Call RegisterRemoteEncodedAudioFrameObserver{@link #RegisterRemoteEncodedAudioFrameObserver}, when the SDK receives the remote audio frame information, callback the event
     * @param  [in] stream_id The ID of the received remote audio stream
     * @param  [in] audio_stream The remote audio frame information. See IEncodedAudioFrame{@link #IEncodedAudioFrame}
     * @param  [in] stream_info Information about the received remote audio stream. See RemoteStreamKey{@link #RemoteStreamKey}
     */
    virtual void onRemoteEncodedAudioFrame(
            const char* stream_id, const IEncodedAudioFrame& audio_stream, const RemoteStreamKey& stream_info) = 0;
};


/**  
 * @hidden
 * @type api
 * @region Audio data callback
 * @brief Register the remote audio frame monitor.   <br>
 *         After calling this method, every time the SDK detects a remote audio frame, it will call back the audio frame information to the user through OnRemoteEncodedAudioFrame{@link #OnRemoteEncodedAudioFrame}
 * @param  [in] engine The engine to be set up. See IRtcEngine{@link #IRtcEngine}
 * @param  [in] observer Remote AudioFrame Monitor. See IRemoteEncodedAudioFrameObserver{@link #IRemoteEncodedAudioFrameObserver}
 * @notes   <br>
 *        + This method is recommended to be called before entering the room. <br>
 *        + Setting the parameter to nullptr cancels registration.
 */
BYTERTC_API void registerRemoteEncodedAudioFrameObserver(IRtcEngine* engine, IRemoteEncodedAudioFrameObserver* observer);

/**  
 * @hidden
 * @type api
 * @region Audio data callback
 * @brief Register a local audio frame monitor.   <br>
 *         After calling this method, every time the SDK detects a local audio frame, it will call back the audio frame information to the user through OnLocalEncodedAudioFrame{@link #OnLocalEncodedAudioFrame}
 * @param  [in] engine The engine to be set up. See IRtcEngine{@link #IRtcEngine}
 * @param  [in] observer Local AudioFrame Monitor. See ILocalEncodedAudioFrameObserver{@link #ILocalEncodedAudioFrameObserver}
 * @notes   <br>
 *        + This method is recommended to be called before entering the room. <br>
 *        + Setting the parameter to nullptr cancels registration.
 */
BYTERTC_API void registerLocalEncodedAudioFrameObserver(IRtcEngine* engine, ILocalEncodedAudioFrameObserver* observer);


/**
 * @hidden
 */
BYTERTC_API bool pushExternalEncodedAudioFrame(IRtcEngine* engine, const IEncodedAudioFrame* audio_stream);

/**
 * @hidden
 * @type api
 */
struct MediaIoOption {
    /**
     * @hidden
     */
    bool enable_audio_encoding = true;
    /**
     * @hidden
     */
    bool enable_video_encoding = true;
    /**
     * @hidden
     */
    bool enable_audio_decoding = true;
    /**
     * @hidden
     */
    bool enable_video_decoding = true;
};

/**
 * @hidden
 * @type api
 */
BYTERTC_API void setupEngineMediaIo(IRtcEngine* engine, const MediaIoOption& option);

/**  
 * @type keytype
 * @region  video data callback
 * @brief Metadata  maximum data size
 */
const int MAX_METADATA_LENGTH = 1024;


/**  
 * @hidden
 * @type callback
 * @brief  Audio device event callback
 */
class IAudioDeviceEventHandler {
public:
    /**  
     * @hidden
     * @type callback
     * @brief  Get microphone volume
     * @param  [in] volume
     *        Volume size
     */
    virtual void onRecordingAudioVolumeIndication(int volume) = 0;

    /**  
     * @hidden
     * @type callback
     * @brief  Get Loopback volume
     * @param  [in] volume
     *        Volume size
     */
    virtual void onLoopbackAudioVolumeIndication(int volume) = 0;
};

/**
 * @hidden
 * @type callback
 */
class IAudioDeviceManagerEx : public IAudioDeviceManager {
public:
    /**  
     * @hidden
     * @region  Audio Facility Management
     * @brief  Constructor
     */
    IAudioDeviceManagerEx() = default;

    /**  
     * @hidden
     * @type api
     * @region Audio Facility Management
     * @brief Destruct the current object and free memory
     * @notes This function should be called when the structure is not needed to free resources related to audio operations
     */
    virtual void release() = 0;

    /**  
     * @hidden
     * @type api
     * @region Audio Facility Management
     * @brief Switch audio to the speaker or earpiece, the default playback device is the speaker
     * @param  [in] enable <br>
     *        + True: switch to the speaker <br>
     *        + False: switch to the earpiece <br>
     * @notes This method is only valid on mobile devices
     */
    virtual void setEnableSpeakerphone(bool enable) = 0;

protected:
    /**  
     * @hidden
     * @brief  Destructor
     */
    virtual ~IAudioDeviceManagerEx() = default;
};

/**  
 * @hidden
 * @type api
 * @brief Audio Facility Management interface is created, this interface does not depend on the engine, and is mainly used for audio Facility Management without an engine
 * @param  [in] handler
 *       Audio device event callback
 * @return Audio Facility Management interface
 */
BYTERTC_API IAudioDeviceManagerEx* createAudioDeviceManager(IAudioDeviceEventHandler* handler);

}  // namespace bytertc

#endif  // BYTE_RTC_ADVANCE_H__
