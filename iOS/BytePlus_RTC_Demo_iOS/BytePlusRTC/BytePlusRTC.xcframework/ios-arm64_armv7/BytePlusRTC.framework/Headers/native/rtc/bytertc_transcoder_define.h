/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once
#include "bytertc_video_frame.h"
#include "bytertc_audio_frame.h"
#include "bytertc_transcoder_base_interface.h"

#define TRANSCODE_ERR_OK 0
#define TRANSCODE_ERR_BASE 1090
#define TRANSCODE_ERR_INVALID_PARAM 1091
#define TRANSCODE_ERR_INVALID_STATE 1092
#define TRANSCODE_ERR_INVALID_OPERATOR 1093
#define TRANSCODE_ERR_TIMEOUT 1094
#define TRANSCODE_ERR_INVALID_PARAM_BY_SERVER 1095
#define TRANSCODE_ERR_SUB_TIMEOUT_BY_SERVER 1096
#define TRANSCODE_ERR_INVALID_STATE_BY_SERVER 1097
#define TRANSCODE_ERR_AUTHENTICATION_BY_CDN 1098
#define TRANSCODE_ERR_TIMEOUT_BY_SIGNALING 1099
#define TRANSCODE_ERR_PUSH_PUBLIC_STREAM_FAIL 1100
#define TRANSCODE_ERR_MIX_IMAGE_FAIL 1101
#define TRANSCODE_ERR_UNKNOW_ERROR_BY_SERVER 1102
#define TRANSCODE_ERR_MAX 1199

namespace bytertc {
/** 
 * @type keytype
 * @brief Events during pushing streams to CDN
 */
enum StreamMixingEvent {
    /**
     * @hidden
     */
    kStreamMixingBase = 0,
    /** 
     *  Request to start pushing streams to CDN
     */
    kStreamMixingStart = 1,
    /** 
     * ask to push streams to CDN started
     */
    kStreamMixingStartSuccess = 2,
    /** 
     *  Failed to start the task to push streams to CDN
     */
    kStreamMixingStartFailed = 3,
    /** 
     *  Request to update the configuration for the task to push streams to CDN
     */
    kStreamMixingUpdate = 4,
    /** 
     *  Successfully update the configuration for the task to push streams to CDN
     */
    kStreamMixingUpdateSuccess = 5,
    /** 
     *  Failed to update the configuration for the task to push streams to CDN
     */
    kStreamMixingUpdateFailed = 6,
    /** 
     *  Request to stop the task to push streams to CDN
     */
    kStreamMixingStop = 7,
    /** 
     *  The task to push streams to CDN stopped
     */
    kStreamMixingStopSuccess = 8,
    /** 
     *  Failed to stop the task to push streams to CDN
     */
    kStreamMixingStopFailed = 9,
    /** 
     *  Timeout for the request to update the configuration for the task to push streams to CDN.
     */
    kStreamMixingChangeMixType = 10,
    /** 
     *  Got the first frame of the mixed audio stream by client.
     */
    kStreamMixingFirstAudioFrameByClientMix = 11,
    /** 
     *  Got the first frame of the mixed video stream by client.
     */
    kStreamMixingFirstVideoFrameByClientMix = 12,
    /** 
     *  Timeout for the request to update the configuration for the task to push streams to CDN
     */
    kStreamMixingUpdateTimeout = 13,
    /** 
     *  Timeout for the request to start the task to push streams to CDN
     */
    kStreamMixingStartTimeout = 14,
    /** 
     *  Error in the parameters of the request for the task to push streams to CDN
     */
    kStreamMixingRequestParamError = 15,
    /** 
     * @hidden
     *  Mixing image.
     */
    kStreamMixingMixImageEvent = 16,
};
/** 
 * @type errorcode
 * @brief Errors occuring during pushing streams to CDN
 */
enum StreamMixingErrorCode {
    /** 
     * Successfully pushed streams to target CDN.
     */
    kStreamMixingErrorOK = 0,
    /** 
     * Undefined error
     */
    kStreamMixingErrorBase= 1090,
    /** 
     *  Invalid parameters detected by Client SDK.
     */
    kStreamMixingErrorInvalidParam = 1091,
    /** 
     *  Program runs with an error, the state machine is in abnormal condition.
     */
    kStreamMixingErrorInvalidState = 1092,
    /** 
     *  Invalid operation
     */
    kStreamMixingErrorInvalidOperator = 1093,
    /** 
     *  Request timed out. Please check network status and retry.
     */
    kStreamMixingErrorTimeout = 1094,
    /** 
     * ameters detected by the server.
     */
    kStreamMixingErrorInvalidParamByServer = 1095,
    /** 
     *  Your subscription of the stream has expired.
     */
    kStreamMixingErrorSubTimeoutByServer = 1096,
    /** 
     *  Internal server error.
     */
    kStreamMixingErrorInvalidStateByServer = 1097,
    /** 
     *  The server failed to push streams to CDN.
     */
    kStreamMixingErrorAuthenticationByCDN  = 1098,
    /** 
     *  Signaling connection timeout error. Please check network status and retry.
     */
    kStreamMixingErrorTimeoutBySignaling = 1099,
    /** 
     *  Failed to mix image.
     */
    kStreamMixingErrorMixImageFail = 1100,
    /** 
     *  Unknown error from server.
     */
    kStreamMixingErrorUnKnownByServer = 1101,
    /**
     * @hidden
     */
    kStreamMixingErrorMax = 1199,
};

/** 
 * @type keytype
 * @brief Stream mixing type
 */
enum StreamMixingType {
    /** 
     * @brief Server-side stream mixing
     */
    kStreamMixingTypeByServer = 0,
    /** 
     * @brief Intelligent stream mixing
     */
    kStreamMixingTypeByClient = 1,
};


/** 
 * @type keytype
 * @brief Advanced Audio Coding (AAC) profile
 */
enum TranscoderAudioCodecProfile {
    /** 
     * @brief Low-Complexity profile (AAC-LC)
     */
    kByteAACProfileLC = 0,
    /** 
     * @brief HE-AAC profile (AAC LC with SBR)
     */
    kByteAACProfileHEv1 = 1,
    /** 
     * @brief HE-AAC v2 profile (AAC LC with SBR and Parametric Stereo)
     */
    kByteAACProfileHEv2 = 2,
};

/** 
 * @type keytype
 * @brief Video encoding format
 */
enum TranscoderVideoCodecProfile {
    /** 
     * @brief H264 baseline profile
     */
    kByteH264ProfileBaseline = 0,
    /** 
     * @brief H264 main profile
     */
    kByteH264ProfileMain = 1,
    /** 
     * @brief H264 high profile
     */
    kByteH264ProfileHigh = 2,
    /** 
     * @brief Custom baseline profile
     */
    kByteVC1ProfileBaseline = 3,
    /** 
     * @brief Custom main profile
     */
    kByteVC1ProfileMain = 4,
    /** 
     * @brief Custom high profile
     */
    kByteVC1ProfileHigh = 5,
};

/** 
 * @type keytype
 * @brief  Video rendering scale mode
 */
enum TranscoderRenderMode {
    /**
     * @hidden
     * @brief to be removed
     */
    kRenderUnknown = 0,
    /** 
     * @brief Fill and Crop.  <br>
     *        The video frame is scaled with fixed aspect ratio, until it completely fills the canvas. The region of the video exceeding the canvas will be cropped.
     */
    kRenderHidden = 1,
    /** 
     * @brief Fit.  <br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.
     */
    kRenderFit = 2,
    /** 
     * @brief Fill the canvas. <br>
     *        The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    kRenderAdaptive = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Stream mixing region type
 */
enum TranscoderLayoutRegionType {
    /** 
     * @brief The region type is a video stream.
     */
    kLayoutRegionTypeVideoStream = 0,
    /** 
     * @brief The region type is an image.
     */
    kLayoutRegionTypeImage = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Image parameters for stream mixing
 */
typedef struct TranscoderLayoutRegionDataParam{
    /** 
     * @brief Width of the original image in px.
     */
    int image_width;
    /** 
     * @brief Height of the original image in px.
     */
    int image_height;
}TranscoderLayoutRegionDataParam;

/** 
 * @type keytype
 * @brief  Data frame type
 */
enum DataFrameType {
    /** 
     * @brief SEI  video frame
     */
    kDataFrameTypeSei = 0,
};

/**
 * @hidden
 */
typedef size_t status_t;
/**
 * @hidden
 */
class IVideoFrame;
/**
 * @hidden
 */
class IAudioFrame;

/** 
 * @type keytype
 * @brief  Data frame
 */
typedef struct IDataFrame {
    /** 
     * @brief Data frame type. See DataFrameType{@link #DataFrameType}
     */
    DataFrameType frame_type;
    /** 
     * @brief Data frame data
     */
    uint8_t* u8_data;
    /** 
     * @brief Data frame data size
     */
    uint32_t u32_data_size;
    /** 
     * @brief Data frame timestamp in microseconds
     */
    uint64_t u64_ts_us;
} IDataFrame;

/** 
 * @type keytype
 * @brief Layout information for one of the video streams to be mixed.   <br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
typedef struct TranscoderLayoutRegion {
    /** 
     * @brief The user ID of the user who publishes the video stream. Required.
     */
    const char* region_id;
   /** 
     * @brief The room ID of the media stream. <br>
     *        If the media stream is the stream forwarded by startForwardStreamToRooms{@link #IRTCRoom#startForwardStreamToRooms}}, you must set the roomID to the room ID of the target room.
     */
    const char* room_id;
    /** 
     * @brief The normalized horizontal coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0).   <br>
     *        The view's position is determined by the position of its top left end vertex in the coordinate of the canvas. The coordinate is formed  with the top side of the canvas as the x-axis, the left side as the y-axis, and the top left end vertex as the origin point.
     */
    float x;
    /** 
     * @brief The normalized vertical coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0).  <br>
     *        The view's position is determined by the position of its top left end vertex in the coordinate of the canvas. The coordinate is formed  with the top side of the canvas as the x-axis, the left side as the y-axis, and the top left end vertex as the origin point.
     */
    float y;
    /** 
     * @brief The normalized width of the user's view, ranging within (0.0, 1.0].
     */
    float width;
    /** 
     * @brief The normalized height of the user's view, ranging within (0.0, 1.0].
     */
    float height;
    /** 
     * @brief Transparency value, the range is [0,255]
     */
    float alpha;
    /** 
     * @brief The layer on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer.
     */
    int32_t i32_z_order;
    /** 
     * @brief Whether the source user of the stream is a local user:   <br>
     *         + True: Yes <br>
     *         + False: No
     */
    bool local_user;
    /** 
     * @brief Whether the stream comes from screen sharing:   <br>
     *         + True: Yes <br>
     *         + False: No
     */
    bool screen_stream = false;
    /** 
     * @brief The stream mixing content type. The default value is `kHasAudioAndVideo`. See TranscoderContentControlType{@link #TranscoderContentControlType}.
     */
    TranscoderContentControlType content_control;
    /** 
     * @brief The render mode of the video. See TranscoderRenderMode{@link #TranscoderRenderMode}
     */
    TranscoderRenderMode render_mode;
    /** 
     * @hidden
     * @type keytype
     * @brief  Stream mixing region type. See TranscoderLayoutRegionType{@link #TranscoderLayoutRegionType}.
     */
    TranscoderLayoutRegionType type;
    /** 
     * @hidden
     * @type keytype
     * @brief The RGBA data of the mixing image. Put in null when mixing video streams.
     */
    uint8_t* data;
    /** 
     * @hidden
     * @type keytype
     * @brief  Image parameters for stream mixing. See TranscoderLayoutRegionDataParam{@link #TranscoderLayoutRegionDataParam}. Put in null when mixing video streams.
     */
    TranscoderLayoutRegionDataParam data_param;
} TranscoderLayoutRegion;

/** 
 *  @type keytype
 *  @brief Audio transcoding configurations.
 */
typedef struct TranscoderAudioParam {
    /** 
     * @brief The sample rate(kHz). Supported sample rates: 32Khz, 44.1Khz, 48Khz. Defaults to 48Khz.
     */
    int32_t i32_sample_rate;
    /** 
     * @brief The number of channels. Supported channels: 1, 2.  Defaults to 2.
     */
    int32_t i32_channel_num;
    /** 
     * @brief The bitrate(Kbps) in range of [32Kbps, 192Kbps]. Defaults to 64Kbps.
     */
    int32_t i32_bitrate_kbps;
    /** 
     *  @brief AAC profile. See TranscoderAudioCodecProfile{@link #TranscoderAudioCodecProfile}. Defaults to `0`.
     */
    TranscoderAudioCodecProfile audio_codec_profile;
} TranscoderAudioParam;

/** 
 * @type keytype
 * @brief Video configurations in stream mixing
 */
typedef struct TranscoderVideoParam {
    /** 
     * @brief Width in px of the mixed video stream.   <br>
     *        The value must be an even number. Odd number will be directly rejected, causing the stream mixing to fail.
     */
    int32_t i32_width;
    /** 
     * @brief Height in px of the mixed video stream.   <br>
     *        The value must be an even number. Odd number will be directly rejected, causing the stream mixing to fail.
     */
    int32_t i32_height;
    /** 
     * @brief The frame rate. The default value is `15`. The range is `[1, 60]`. If the value is not legal, the SDK uses the default value.
     */
    int32_t i32_fps;
    /** 
     * @brief GOP. The default value is `4`. The range is `[1, 5]`. The unit is second. If the value is not legal, the SDK uses the default value.
     */
    int32_t i32_gop;
    /** 
     * @brief The default value is self-adaptive. The range is `[1, 10000]`. The unit is kbps. If the value is not legal, the SDK uses the default value.
     */
    int32_t i32_bitrate_kbps;
    /** 
     * @brief Video encoding profile. See TranscoderVideoCodecProfile{@link #TranscoderVideoCodecProfile}
     */
    TranscoderVideoCodecProfile video_codec_profile;
    /** 
     * @brief Whether to push streams with low latency:   <br>
     *         + True: Yes <br>
     *         + False: No
     */
    bool lowLatency;
} TranscoderVideoParam;

/** 
 * @type keytype
 * @brief Configurations to be set when pushing media streams to CDN.
 */
class ITranscoderParam : public ITranscoderParamBase {
public:

    /** 
     * @type api
     * @region Push to CDN
     * @brief Gets the stream mixing type
     * @return Stream mixing type. See StreamMixingType{@link #StreamMixingType}
     */
    virtual StreamMixingType expectedMixingType() = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Get confluence users ID
     * @return Confluence users ID
     */
    virtual const char* userID() = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Gets the CDN url where the mixed stream is supposed to be pushed
     * @return The CDN url
     */
    virtual const char* uri() = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Get SEI information
     * @return SEI Information
     */
    virtual const char* appData() = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Gets the audio configurations
     * @return Audio configurations. See TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual TranscoderAudioParam audioParam() = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Gets the video configurations
     * @return Video configurations. See TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual TranscoderVideoParam videoParam() = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Gets the video layout information of the mixed stream.
     * @param [in] index The number of the view of which you want to get information
     * @return Layout information. See TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     */
    virtual TranscoderLayoutRegion layoutRegionByIndex(int32_t index) = 0;

    /** 
     * @hidden
     * @type api
     * @region  Forward to live broadcast
     * @brief  Get dynamically extend customizable parameters
     * @return  dynamically extend customizable parameters
     */
    virtual const char* advancedConfig() = 0;
    /** 
     * @hidden
     * @type api
     * @region  Forward to live broadcast
     * @brief  Get Business Transparent Authentication Information
     * @return Business Transparent Authentication Information
     */
    virtual const char* authInfo() = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Sets the expected stream mixing type
     * @param [in] expected_mix_type Stream mixing type. See StreamMixingType{@link #StreamMixingType}
     */
    virtual void setExpectedMixingType(StreamMixingType expected_mix_type) = 0;
    /** 
     * @type api
     * @region Forward to live broadcast
     * @brief Set the merge user ID
     * @param  [in] user_id The ID of the user who initiated the merge
     */
    virtual void setUserID(const char* user_id) = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Sets the CDN url where the mixed stream is supposed to be pushed.
     * @param [in] uri The url to be set.
     */
    virtual void setUri(const char* uri) = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Sets audio configurations
     * @param [in] TranscoderAudioParam Audio configurations. See TranscoderAudioParam{@link #TranscoderAudioParam}
     */
    virtual void setAudioParam(const TranscoderAudioParam&) = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Sets video configurations
     * @param [in] TranscoderVideoParam Video configurations. See TranscoderVideoParam{@link #TranscoderVideoParam}
     */
    virtual void setVideoParam(const TranscoderVideoParam&) = 0;
    /** 
     * @type api
     * @region Push to CDN
     * @brief Sets the layout Configurations
     * @param [in] regions[] Layout Configurations. See TranscoderLayoutRegion{@link #TranscoderLayoutRegion}
     * @param [in] regions_size Amount of views
     * @param [in] bg_color Background color of the mixed stream
     * @param [in] app_data Additional data that you want to import
     */
    virtual void setLayoutParam(
            TranscoderLayoutRegion regions[], int32_t regions_size, const char* bg_color, const char* app_data) = 0;
    /** 
     * @hidden
     * @type api
     * @region  Forward to live broadcast
     * @brief  Set dynamically extend customizable parameters
     * @param  [in] advancedConfig  dynamically extend customizable parameters
     */
    virtual void setAdvancedConfig(const char* advancedConfig) = 0;
    /** 
     * @hidden
     * @type api
     * @region  Forward to live broadcast
     * @brief  Set Business Transparent Authentication Information
     * @param  [in] authInfo  Business Transparent Authentication Information
     */
    virtual void setAuthInfo(const char* authInfo) = 0;

    /** 
     * @type api
     * @region Push to CDN
     * @brief Convert the json format string into the ITranscoderParam structure
     * @param [in] json_str Json format string
     * @return Converted ITranscoderParam structure
     */
    virtual ITranscoderParam* inflatten(const char* json_str) = 0;

    /** 
     * @type api
     * @region Push to CDN
     * @brief Get default transcoding param
     * @return Default ITranscoderParam structure
     */
    virtual ITranscoderParam* defaultTranscoding() = 0;
    /**
     * @hidden
     */
    virtual ~ITranscoderParam() = default;
};

}  // namespace bytertc
