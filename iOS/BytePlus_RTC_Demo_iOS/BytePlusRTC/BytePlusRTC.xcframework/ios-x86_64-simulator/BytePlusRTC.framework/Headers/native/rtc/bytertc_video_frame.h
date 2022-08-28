/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Video Frame
 */

#pragma once

#ifndef BYTE_RTC_VIDEO_FRAME_H__
#define BYTE_RTC_VIDEO_FRAME_H__

#include <stdint.h>
#include <stddef.h>
#include <memory>
#include "bytertc_common_defines.h"
#ifdef BYTERTC_ANDROID
#include <jni.h>
#endif

namespace bytertc {

/** 
 * @type keytype
 * @brief Video compression picture type
 */
enum VideoPictureType {
    /** 
     * @brief Unknown type
     */
    kVideoPictureTypeUnknown = 0,
    /** 
     * @brief I-frames, key frames which are coded without reference to any other frame.
     */
    kVideoPictureTypeI,
    /** 
     * @brief P-frames, forward-predicted frames which are coded by a forward predictive coding method.
     */
    kVideoPictureTypeP,
    /** 
     * @brief  B-frames, bi-directionally predicted frames which are coded by both forward and backward predictive coding method.
     */
    kVideoPictureTypeB
};

/** 
 * @type keytype
 * @brief Video frame rotation angle
 */
enum VideoRotation {
    /** 
     * @brief Video does not rotate
    */
    kVideoRotation0 = 0,
    /** 
     * @brief Video rotate 90 degrees clockwise
    */
    kVideoRotation90 = 90,
    /** 
     * @brief Video rotate 180 degrees clockwise
    */
    kVideoRotation180 = 180,
    /** 
     * @brief Video rotate 270 degrees clockwise
    */
    kVideoRotation270 = 270
};

/** 
 * @type keytype
 * @brief  Video frame scale mode
 */
enum VideoStreamScaleMode {
    /** 
     * @brief Auto mode, default to FitWithCropping.
     */
    kVideoStreamScaleModeAuto = 0,
    /** 
     * @brief Stretch the video frame until the video frame and the window have the same resolution. The video frame's aspect ratio can be changed as it is automatically stretched to fill the window, but the whole image is visible.
     */
    kVideoStreamScaleModeStretch = 1,
    /** 
     * @brief  Fit the window with cropping <br>
     *         Scale the video frame uniformly until the window is filled. If the video frame's aspect ratio is different from that of the window, the extra part of the video frame will be cropped. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be greater than or equal to that of the window.
     */
    kVideoStreamScaleModeFitWithCropping = 2,
    /** 
     * @brief  Fit the window with filling <br>
     *         Scale the video frame uniformly until its width or height reaches the boundary of the window. If the video frame's aspect ratio is different from that of the window, the area that is not filled will be black. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be less than or equal to that of the window.
     */
    kVideoStreamScaleModeFitWithFilling = 3,
};


/** 
 * @type keytype
 * @brief  Video encoding mode
 */
enum VideoCodecMode {
    /** 
     * @brief Automatic selection
     */
    kCodecModeAuto = 0,
    /** 
     * @brief Hardcoding
     */
    kCodecModeHardware,
    /** 
     * @brief Softcoding
     */
    kCodecModeSoftware,
};

/** 
 * @type keytype
 * @brief  Encoder preference
 */
enum VideoEncodePreference {
    /** 
     * @brief No preference
     */
    kVideoEncodePreferenceDisabled = 0,
    /** 
     * @brief Frame rate first
     */
    kVideoEncodePreferenceFramerate,
    /** 
     * @brief Quality first
     */
    kVideoEncodePreferenceQuality,
    /** 
     * @brief Balancing quality and frame rate
     */
    kVideoEncodePreferenceBalance,
};

/** 
 * @type keytype
 * @brief  camera.
 */
enum CameraID {
    /** 
     *@brief Front-facing camera for mobile, build-in camera for PC
     */
    kCameraIDFront = 0,
    /** 
     *@brief Postconditioning camera for mobile, PC is undefined for camera 1
     */
    kCameraIDBack = 1,
    /** 
     *@brief External camera
     */
    kCameraIDExternal = 2,
    /** 
     *@brief Invalid value
     */
    kCameraIDInvalid = 3
};


#define SEND_KBPS_AUTO_CALCULATE -1
#define SEND_KBPS_DISABLE_VIDEO_SEND 0

/** 
 * @type keytype
 * @brief  Video stream parameters
 */
struct VideoSolution {
    /** 
     * @brief Width (pixels)
     */
    int width;
    /** 
     * @brief Height (pixels)
     */
    int height;
    /** 
     * @brief Video frame rate
     */
    int fps;
    /** 
     * @brief Maximum bitrate (kbps) <br>
     *        Estimated value is recommended.
     */
    int max_send_kbps = SEND_KBPS_AUTO_CALCULATE;
    /** 
     * @brief Video frame scale mode. You can adjust the scale to fit the window. See VideoStreamScaleMode{@link #VideoStreamScaleMode}
     */
    VideoStreamScaleMode scale_mode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
    /** 
     * @brief ncoder preference. See VideoEncodePreference{@link #VideoEncodePreference}.
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};
/** 
 * @type keytype
 * @brief Video frame configuration
 */
struct VideoEncoderConfig {
    /** 
     * @brief Width of the video frame in px
     */
    int width;
    /** 
     * @brief Height of the video frame in px
     */
    int height;
    /** 
     * @brief Video frame rate in fps
     */
    int frameRate;
    /** 
     * @brief Maximum bit rate in kbps. Optional for internal capturing while mandatory for custom capturing.  <br>
     *        The default value is -1 in internal capturing mode, SDK will automatically calculate the applicable bit rate based on the input resolution and frame rate.  <br>
     *        No stream will be encoded and published if you set this parameter to 0.
     */
    int maxBitrate = SEND_KBPS_AUTO_CALCULATE;
    /** 
     * @brief Video frame scale mode. The mode of how the video adapts the view. See VideoStreamScaleMode {@link #VideoStreamScaleMode}.
     */
    VideoStreamScaleMode scaleMode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
    /** 
     * @brief Encoding policy preference, see VideoEncodePreference {@link #VideoEncodePreference}.
     */
    VideoEncodePreference encoderPreference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};

/** 
 * @type keytype
 * @brief  Video attribute
 */
struct VideoSolutionDescription {
    /** 
     * @brief Width (pixels)
     */
    int width;
    /** 
     * @brief High (pixels)
     */
    int height;
    /** 
     * @brief Video frame rate
     */
    int fps;
    /** 
     * @brief Maximum transmission rate (kilobits per second)
     */
    int max_send_kbps;
    /** 
     * @brief Zoom mode. See VideoStreamScaleMode{@link #VideoStreamScaleMode}
     */
    VideoStreamScaleMode scale_mode = VideoStreamScaleMode::kVideoStreamScaleModeAuto;
    /** 
     * @brief The encoding type of the video. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_name = VideoCodecType::kVideoCodecTypeUnknown;
    /** 
     * @brief The encoding mode of the video. See VideoCodecMode{@link #VideoCodecMode}
     */
    VideoCodecMode codec_mode = VideoCodecMode::kCodecModeAuto;
    /** 
     * @brief Video coding quality preference strategy. See VideoEncodePreference{@link #VideoEncodePreference}
     */
    VideoEncodePreference encode_preference = VideoEncodePreference::kVideoEncodePreferenceFramerate;
};


/** 
 * @hidden
 * @type keytype
 * @region  video management
 */
typedef VideoSolutionDescription VideoProfile;

/** 
 * @type keytype
 * @brief Encoding format for video frame color
 */
enum VideoPixelFormat {
    /** 
     * @brief Unknown format
     */
    kVideoPixelFormatUnknown = 0,
    /** 
     * @brief YUV I420
     */
    kVideoPixelFormatI420,
    /** 
     * @brief YUV NV12
     */
    kVideoPixelFormatNV12,
    /** 
     * @brief YUV NV21
     */
    kVideoPixelFormatNV21,
    /** 
     * @brief RGB 24bit
     */
    kVideoPixelFormatRGB24,
    /** 
     * @brief RGBA
     */
    kVideoPixelFormatRGBA,
    /** 
     * @brief ARGB
     */
    kVideoPixelFormatARGB,
    /** 
     * @brief BGRA
     */
    kVideoPixelFormatBGRA,
    /** 
     * @brief Texture2D
     */
    kVideoPixelFormatTexture2D = 0x0DE1,
    /** 
     * @brief TextureOES
     */
    kVideoPixelFormatTextureOES = 0x8D65,
};

/** 
 * @hidden
 * @type keytype
 * @brief Video content type
 */
enum VideoContentType {
    /** 
     * @brief Normal video
     */
    kVideoContentTypeNormalFrame = 0,
    /** 
     * @brief Black frame video
     */
    kVideoContentTypeBlackFrame,
};

/** 
 * @type keytype
 * @region  video management
 * @brief  Video YUV format color space
 */
enum ColorSpace {
    /** 
     * Unknown color space, default kColorSpaceYCbCrBT601LimitedRange color space
     */
    kColorSpaceUnknown = 0,
    /** 
     * @brief BT.601 Digital Coding Standard, Color Space [16-235]
     */
    kColorSpaceYCbCrBT601LimitedRange,
    /** 
     *  @brief BT.601 Digital Coding Standard, Color Space [0-255]
     */
    kColorSpaceYCbCrBT601FullRange,
    /** 
     * @brief BT.7091 Digital Coding Standard, Color Space [16-235]
     */
    kColorSpaceYCbCrBT709LimitedRange,
    /** 
     * @brief BT.7091 Digital Coding Standard, Color Space [0-255]
     */
    kColorSpaceYCbCrBT709FullRange,
};

/** 
 * @type keytype
 * @brief Video frame format
 */
enum VideoFrameType {
    /** 
     * @brief Original format, stored as memory
     */
    kVideoFrameTypeRawMemory,
    /** 
     * @brief CVPixelBufferRef which applys to iOS and macOS
     */
    kVideoFrameTypeCVPixelBuffer,
    /** 
     * @brief Open gl texture
     */
    kVideoFrameTypeGLTexture,
    /** 
     * @brief Cuda
     */
    kVideoFrameTypeCuda,
    /** 
     * @brief Direct3d 11
     */
    kVideoFrameTypeD3D11,
    /** 
     * @brief Direct3d 9
     */
    kVideoFrameTypeD3D9,
    /** 
     * @brief VideoFrame used in Java
     */
    kVideoFrameTypeJavaFrame,
    /** 
     * @brief Vaapi
     */
    kVideoFrameTypeVAAPI,
};

/** 
 * @type keytype
 * @brief  Custom Memory Release
 */
struct ManagedMemory {
    /** 
     * @hidden
     * @brief  Memory data data type, the default is cpu memory. See VideoFrameType:{@link #VideoFrameType}
     * @notes  This field is not used, will be deleted later, currently only cpu memory
     */
    VideoFrameType type = kVideoFrameTypeRawMemory;
    /** 
     * @brief Memory data address
     */
    uint8_t* data = nullptr;
    /** 
     * @brief Size of memory space
     */
    int size = 0;
    /** 
     * @brief User-defined data
     */
    void* user_opaque = nullptr;
    /** 
     * @brief Custom memory free method pointer, if the pointer is not empty, the method will be called to free memory space. The parameters passed in by the
     *         Function are data, size, user_opaque 3 fields in this structure.
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
};

/** 
 * @type keytype
 * @region Video Management
 * @brief Video frame construction object
 */
typedef struct VideoFrameBuilder {
#define ByteRTCNumDataPointers 4
    /** 
     * @hidden
     * @brief Memory data type, the default value is cpu memory. See VideoFrameType{@link #VideoFrameType}
     */
    VideoFrameType frame_type = kVideoFrameTypeRawMemory;
    /** 
     * @hidden
     * @brief Video frame pixel format. See VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat pixel_fmt = kVideoPixelFormatUnknown;
    /** 
     * @hidden
     * @brief Video frame color space, see ColorSpace{@link #ColorSpace}
     */
    ColorSpace color_space = kColorSpaceUnknown;
    /** 
     * @brief Array of video frame data plane pointer
     */
    uint8_t* data[ByteRTCNumDataPointers] = { 0 };
    /** 
     * @brief Line length of video frame data plane
     */
    int linesize[ByteRTCNumDataPointers] = { 0 };
    /** 
     * @brief SEI data address
     */
    uint8_t* extra_data = nullptr;
    /** 
     * @brief SEI data size
     */
    int extra_data_size = 0;
    /** 
     * @brief Address of supplementary data
     */
    uint8_t* supplementary_info = nullptr;
    /** 
     * @brief Size of supplementary data
     */
    int supplementary_info_size = 0;
    /** 
     * @brief Video frame memory space size
     */
    int size = 0;
    /** 
     * @brief Video frame width
     */
    int width = 0;
    /** 
     * @brief Video frame height
     */
    int height = 0;
    /** 
     * @brief Video rotation angle, see VideoRotation{@link #VideoRotation}
     */
    VideoRotation rotation = kVideoRotation0;
    /** 
     * @hidden
     * @brief Mirror parameter
     */
    bool flip = false;
    /** 
     * @brief Hardware acceleration buffer pointer
     */
    void* hwaccel_buffer = nullptr;
    /** 
     * @brief Private data pointer
     */
    void* user_opaque = nullptr;
    /** 
     * @brief Video frame timestamp
     */
    int64_t timestamp_us = 0;
    /** 
     * @brief Hardware accelerate context(AKA Opengl Context, Vulkan Context)
     */
    void* hwaccel_context = nullptr;
#ifdef __ANDROID__
    /** 
     * @brief Hardware accelerate context's java object(Only for Android, AKA Opengl Context)
     */
    jobject android_hwaccel_context = nullptr;
#endif
    /** 
     * @brief Texture matrix (only for texture type frame)
     */
    float tex_matrix[16] = { };
    /** 
     * @brief Texture ID (only for texture type frame)
     */
    uint32_t texture_id = 0;

    /** 
     * @brief User-defined pointer used for release the memory space, if the pointer is not empty.
     */
    int (*memory_deleter)(struct VideoFrameBuilder* builder) = nullptr;
} VideoFrameBuilder;

/** 
 * @type keytype
 * @brief Sets the video frame
 */
class IVideoFrame {
public:
    /** 
     * @brief Gets video frame type, see VideoFrameType{@link #VideoFrameType}
     */
    virtual VideoFrameType frameType() const = 0;
    /** 
     * @brief Gets video frame format, see VideoPixelFormat{@link #VideoPixelFormat}
     */
    virtual VideoPixelFormat pixelFormat() const = 0;
    /** 
     * @hidden
     * @type api
     * @brief Gets video content type.
     * @return See VideoContentType{@link #VideoContentType}.
     */
    virtual VideoContentType videoContentType() const = 0;

    /** 
     * @brief Gets video frame timestamp in microseconds
     */
    virtual int64_t timestampUs() const = 0;
    /** 
     * @brief Gets video frame width in px
     */
    virtual int width() const = 0;
    /** 
     * @brief Gets video frame height in px
     */
    virtual int height() const = 0;
    /** 
     * @brief Gets the video frame rotation angle, see VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /** 
     * @deprecated
     * @hidden
     * @brief Gets mirror information
     * @return Is there a need to mirror the video:  <br>
     *        + True: Yes  <br>
     *        + False: No
     */
    virtual bool flip() const = 0;
    /** 
     * @brief Gets video frame color space, see ColorSpace{@link #ColorSpace}
     */
    virtual ColorSpace colorSpace() const = 0;
    /** 
     * @brief Video frame color plane number
     * @notes YUV formats are categorized into planar format and packed format.  <br>
     *        In a planar format, the Y, U, and V components are stored separately as three planes, while in a packed format, the Y, U, and V components are stored in a single array.
     */
    virtual int numberOfPlanes() const = 0;
    /** 
     * @brief Gets plane data pointer
     * @param [in] plane_index Plane data index
     */
    virtual uint8_t* getPlaneData(int plane_index) = 0;
    /** 
     * @brief Gets the length of the data line in the plane
     * @param [in] plane_index Plane data index
     */
    virtual int getPlaneStride(int plane_index) = 0;
    /** 
     * @brief Gets extended data pointer
     * @param [in] size Size of extended data in bytes
     */
    virtual uint8_t* getExtraDataInfo(int& size) const = 0;  // NOLINT
    /** 
     * @brief Gets supplementary data pointer
     * @param [in] size Size of supplementary data in bytes
     */
    virtual uint8_t* getSupplementaryInfo(int& size) const = 0;  // NOLINT
    /** 
     * @brief Gets local buffer pointer
     */
    virtual void* getHwaccelBuffer() = 0;
    /** 
     * @brief Get hardware accelerate context(AKA Opengl Context, Vulkan Context)
     */
    virtual void* getHwaccelContext() = 0;
#ifdef __ANDROID__
    /** 
     * @brief Get hardware accelerate context's java object(Only for Android, AKA Opengl Context)
     * @return return JavaLocalRef, need delete manually by use DeleteLocalRef(env, jobject)
     */
    virtual jobject getAndroidHwaccelContext() = 0;
#endif
    /** 
     * @brief Get Texture matrix (only for texture type frame)
     */
    virtual void getTexMatrix(float matrix[16]) = 0;
    /** 
     * @brief Get Texture ID (only for texture type frame)
     */
    virtual uint32_t getTextureId() = 0;
    /** 
     * @brief Makes shallow copies of video frame and return pointer
     */
    virtual IVideoFrame* shallowCopy() = 0;
    /** 
     * @brief Releases video frame
     */
    virtual void release() = 0;
    /** 
     * @brief Converts video frames to i420 format
     */
    virtual void toI420() = 0;
    /** 
     * @brief Get cameraId of the frame, see CameraID{@link #CameraID}
     */
    virtual CameraID getCameraId() const = 0;
/**
 * @hidden
 */
protected:
    /** 
     * @brief Destructor
     */
    virtual ~IVideoFrame() = default;
};

/** 
 * @type keytype
 * @region  video management
 * @brief  Video frame parameters
 */
typedef struct EncodedVideoFrameBuilder {
    /** 
     * @brief Video frame encoding format. See VideoCodecType{@link #VideoCodecType}
     */
    VideoCodecType codec_type = kVideoCodecTypeUnknown;
    /** 
     * @brief Video frame encoding type. See VideoPictureType{@link #VideoPictureType}
     */
    VideoPictureType picture_type = kVideoPictureTypeUnknown;
    /** 
     * @brief Video frame rotation angle. See VideoRotation{@link #VideoRotation}
     */
    VideoRotation rotation = kVideoRotation0;
    /** 
     * @brief Video frame data pointer
     * @notes IEncodedVideoFrame  takes ownership of the data
     */
    uint8_t* data = nullptr;
    /** 
     * @brief Video frame data size
     */
    int size = 0;
    /** 
     * @brief Video frame width in px
     */
    int width = 0;
    /** 
     * @brief Video frame height in px
     */
    int height = 0;
    /** 
     * @brief Video capture timestamp in microseconds
     */
    int64_t timestamp_us = 0;
    /** 
     * @brief Video encoding timestamp in microseconds
     */
    int64_t timestamp_dts_us = 0;
    /** 
     * @brief The user-defined video frame releases the callback function pointer. If the pointer is not empty, the method will be called to free memory space
     */
    int (*memory_deleter)(uint8_t* data, int size, void* user_opaque) = nullptr;
} EncodedVideoFrameBuilder;
/** 
 * @type keytype
 * @brief Information about video frames
 */
class IEncodedVideoFrame {
public:
    /** 
     * @type api
     * @brief Gets the video encoding type
     * @return Video encoding type. See VideoCodecType{@link #VideoCodecType}
     */
    virtual VideoCodecType codecType() const = 0;
    /** 
     * @type api
     * @brief Gets video capture timestamp
     * @return Video capture timestamp in microseconds
     */
    virtual int64_t timestampUs() const = 0;
    /** 
     * @type api
     * @brief Gets video encoding timestamp
     * @return Video encoding timestamp in microseconds
     */
    virtual int64_t timestampDtsUs() const = 0;
    /** 
     * @type api
     * @brief Get videos frame width
     * @return Video frame width in px
     */
    virtual int width() const = 0;
    /** 
     * @type api
     * @brief Gets video frame height
     * @return Video frame height in px
     */
    virtual int height() const = 0;
    /** 
     * @type api
     * @brief Gets video compression picture type.
     * @return Video compression picture type.See VideoPictureType{@link #VideoPictureType}
     */
    virtual VideoPictureType pictureType() const = 0;
    /** 
     * @type api
     * @brief Gets video frame rotation angle
     * @return Video frame rotation angle. See VideoRotation{@link #VideoRotation}
     */
    virtual VideoRotation rotation() const = 0;
    /** 
     * @type api
     * @brief Get the pointer to the video frame
     * @return The pointer to the video frame
     */
    virtual uint8_t* data() const = 0;
    /** 
     * @type api
     * @brief Gets video frame data size
     * @return Video frame data size
     */
    virtual int dataSize() const = 0;
    /** 
     * @type api
     * @brief Makes shallow copies of video frame and return pointer
     */
    virtual IEncodedVideoFrame* shallowCopy() const = 0;
    /** 
     * @type api
     * @brief Releases video frame
     */
    virtual void release() = 0;
    /** 
     * @type api
     * @brief Create video frames according to the parameters and return the pointer
     * @param [in] builder Video frame parameters. See EncodedVideoFrameBuilder{@link #EncodedVideoFrameBuilder}
     * @return IEncodedVideoFrame Created video frame pointer
     */
    static IEncodedVideoFrame* buildEncodedVideoFrame(const EncodedVideoFrameBuilder& builder);
    /**
     * @hidden
     */
protected:
    /** 
     * @hidden
     * @brief Destructor
     */
    virtual ~IEncodedVideoFrame() = default;
};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_FRAME_H__
