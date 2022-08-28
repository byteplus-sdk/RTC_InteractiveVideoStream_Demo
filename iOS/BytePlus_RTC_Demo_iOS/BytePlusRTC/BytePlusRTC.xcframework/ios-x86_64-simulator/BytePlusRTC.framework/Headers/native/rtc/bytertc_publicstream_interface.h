//
//  bytertc_publicstream_interface.h
//  BytePlusRTC

#pragma once

#include "bytertc_defines.h"
#include "bytertc_transcoder_base_interface.h"

#define PUBLICSTREAM_OK 0
#define PUBLICSTREAM_BASE 1190
#define PUBLICSTREAM_INVALID_PARAM 1191
#define PUBLICSTREAM_INVALID_STATE 1192
#define PUBLICSTREAM_INTERNAL_ERROR 1193
#define PUBLICSTREAM_PUSH_FAILED 1195
#define PUBLICSTREAM_TIMEOUT 1196

namespace bytertc {
/** 
 * @type keytype
 * @brief Layout mode of the public stream
 */
enum StreamLayoutMode {
    /** 
     * @brief Customer mode
     */ 
    kLayoutCustomerMode = 2
};

/** 
 * @type keytype
 * @brief Error code of the public stream.
 */
enum PublicStreamErrorCode {
    /** 
     * @brief Successfully pushed the public stream.
     */
    kPublicStreamOK = 200,
    /** 
     * @brief The public stream's parameter is invalid.
     */
    kPushPublicStreamInvalidParam = 1191,
    /** 
     * @brief The public stream's status is invalid.
     */
    kPushPublicStreamInvalidStatus = 1192,
    /** 
     * @brief Some internal error occurs in the process of pushing the public stream.
     */
    kPushPublicStreamInternalError = 1193,
    /** 
     * @brief Failed to push the public stream.
     */
    kPushPublicStreamPushFailed = 1195,
    /** 
     * @brief Time-out error for pushing the public stream.
     */
    kPushPublicStreamTimeout = 1196,
};

/** 
 * @type keytype
 * @brief Configurations on how to crop the public stream
 */
typedef struct SourceCrop {
    /** 
     * @brief The normalized horizontal coordinate value of the top left vertex of the cropped image to width of the original image, ranging within [0.0, 1.0).
     */     
    float LocationX = 0.0;
    /** 
     * @brief The normalized vertical coordinate value of the top left vertex of the cropped image to height of the original image, ranging within [0.0, 1.0).
     */
    float LocationY = 0.0;
    /** 
     * @brief The normalized ratio of the width of the cropped image to that of the original image, ranging within [0.0, 1.0).
     */
    float WidthProportion = 0.0;
    /** 
     * @brief The normalized ratio of the height of the cropped image to that of the original image, ranging within [0.0, 1.0).
     */
    float HeightProportion = 0.0;
} SourceCrop;
/** 
 * @type keytype
 * @brief Properties of the public video stream
 */
typedef struct PublicStreamVideoParam {
    /** 
     * @brief Width, unit: px<br>
     *        Valid for even numbers only. Assigning an odd number will lead to a failure of publishing a public stream.
     */
    int32_t width;
    /** 
     * @brief Height, unit: px<br>
     *        Valid for even numbers only. Assigning an odd number will lead to a failure of publishing a public stream.
     */
    int32_t height;
    /** 
     * @brief Frame rate, unit: fps
     */
    int32_t fps;
    /** 
     * @brief Bitrate, unit: kbps<br>
     */
    int32_t bitrate_kpbs;
} PublicStreamVideoParam;
/** 
 * @type keytype
 * @brief Properties of the public audio stream
 */
typedef struct PublicStreamAudioParam {
    /** 
     * @brief Sample rate, including 16k, 32k, 44.1k, and 48k
     */
    int32_t sample_rate;
    /** 
     * @brief Number of audio channels
     */
    int32_t channel_num;
    /** 
     * @brief Bitrate, unit: kbps, including 16 kbps, 32 kbps, and 64 kbps
     */
    int32_t bitrate_kbps;
} PublicStreamAudioParam;
/** 
 * @type keytype
 * @brief Layout configuration of the video stream in the public stream <br>
 *        You can configure each of the video streams for the public stream.
 */
typedef struct PublicStreamLayoutRegion {
    /** 
     * @brief ID of the public stream
     */
    const char* user_id = "";
    /** 
     * @brief ID of the room from which the stream is intended to be sent as a public stream.
     */
    const char* room_id = "";
    /** 
     * @brief Uniform resource identifier(URI) of the background image
     */
    const char* alternate_image_uri = "";
    /** 
     * @brief Left offset of the video against the local client' view, ranging [0.0, 1.0)
     */
    float x;
    /**  
     * @brief Top offset of the video against the local client' view, ranging [0.0, 1.0)
     */
    float y;
    /** 
     * @brief Ratio of the width of the video to that of the client's view, ranging [0.0, 1.0)
     */
    float width;
    /** 
     * @brief Ratio of the height of the video to that of the client's view, ranging [0.0, 1.0)
     */
    float height;
    /** 
     * @brief Transparency, ranging [0，255]
     */
    float alpha;
    /** 
     * @brief Stack's layer order (also known as the z-order) of videos in the public stream. <br>
     *        Ranging [0, 100]. The video appears on the bottom when this value is set to 0.
     */
    int32_t z_order;
    /** 
     * @brief Stream index:<br>
     *        + 0: Main stream which is video or audio stream captured by media device or externally sourced media stream.
     *        + 1: Screen-sharing stream
     */
    int stream_type = 0;
    /** 
     * @brief Media type of the public stream. Refer to TranscoderContentControlType{@link #TranscoderContentControlType} for more details.
     */
    TranscoderContentControlType media_type;
    /** 
     * @brief The fit mode when rendering. Refer to RenderMode{@link #RenderMode} for more details.
     */
    RenderMode render_mode;
    /** 
     * @brief Configurations on how to crop the public stream. Refer to SourceCrop{@link #SourceCrop} for more details.
     */
    SourceCrop source_crop;
} PublicStreamLayoutRegion;
/** 
 * @type keytype
 * @brief Layout configuration of the public stream
 */
struct PublicStreamLayout {
    /** 
     * @brief Layout mode
     */
    int layoutMode;
    /** 
     * @brief interpolation mode
     */
    int interMode;
    /** 
     * @brief Background image
     */
    const char* background_image = nullptr;
    /** 
     * @brief Background color. Such as #FFB6C1
     */
    const char* background_color = nullptr;
    /** 
     * @brief Layout configuration. Refer PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion} to more details.
     */
    PublicStreamLayoutRegion* regions = nullptr;
    /** 
     * @brief Number of the streams in the public stream
     */
    int regions_num = 0;
};
/** 
 * @type keytype
 * @brief Configurations of the public stream
 */
struct PublicStreamConfig {
    /** 
     * @brief ID of the public stream
     */
    const char* stream_id = nullptr;
    /** 
     * @brief Properties of the public video stream. Refer to PublicStreamVideoParam{@link #PublicStreamVideoParam} for more details.
     */
    PublicStreamVideoParam video_config;
    /** 
     * @brief Properties of the public audio stream. Refer to PublicStreamAudioParam{@link #PublicStreamAudioParam} for more details.
     */
    PublicStreamAudioParam audio_config;
    /** 
     * @brief Layout configuration of the public stream. Refer to PublicStreamLayout{@link #PublicStreamLayout} for more details.
     */

    PublicStreamLayout layout;
};
/** 
 * @type keytype
 * @brief Properties of the public stream
 */
class IPublicStreamParam : public ITranscoderParamBase {
public:
    /** 
     * @type api
     * @brief Set the layout mode of the public stream. Only `kLayoutCustomerMode` is available for the moment.
     * @return Layout mode of the public stream. Refer to StreamLayoutMode{@link #StreamLayoutMode} for more details.
     */
    virtual StreamLayoutMode layoutMode() = 0;
    /** 
     * @type api
     * @brief Get the interpolation mode of the public stream.
     * @return Enable video frame interpolation.<br>
     *         `0`: Intermediate with the last frame
     *         `1`: Intermediate with the background image or blank frames
     */
    virtual int interpolationMode() = 0;
    /** 
     * @type api
     * @brief Get the uniform resource identifier(URI) of the background image
     * @return The URI of the background image
     */
    virtual const char* backgroundImageUri() = 0;
    /** 
     * @type api
     * @brief Get the properties of the public audio stream
     * @return Properties of the public audio stream. Refer to PublicStreamAudioParam{@link #PublicStreamAudioParam} for more details.
     */
    virtual PublicStreamAudioParam audioParam() = 0;
    /** 
     * @type api
     * @brief Get the properties of the public video stream
     * @return Properties of the public video stream. Refer to PublicStreamVideoParam{@link #PublicStreamVideoParam} for more details.
     */
    virtual PublicStreamVideoParam videoParam() = 0;
    /** 
     * @type api
     * @brief Get the layout configurations of the video stream to be added
     * @param [in] index Stream index
     * @return Layout of the region in the public stream. Refer to PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion} for more details.
     */
    virtual PublicStreamLayoutRegion layoutRegionByIndex(int32_t index) = 0;
    /** 
     * @type api
     * @brief Set the interpolation mode
     * @param [in] mode  Interpolation mode<br>
     *         `0`: Intermediate with the last frame
     *         `1`: Intermediate with the background image or blank frames
     */
    virtual void setInterpolationMode(int mode) = 0;
    /** 
     * @type api
     * @brief Set the uniform resource identifier(URI) of the background image
     * @param [in] uri URI of the background image 
     */
    virtual void setBackgroundImageUri(const char* uri) = 0;
    /** 
     * @type api
     * @brief Set audio properties of the public stream
     * @param [in] PublicStreamAudioParam Audio properties of the public stream. Refer to PublicStreamAudioParam{@link #PublicStreamAudioParam} for more details.
     */
    virtual void setAudioParam(const PublicStreamAudioParam&) = 0;
    /** 
     * @type api
     * @brief Set video properties of the public stream
     * @param [in] PublicStreamVideoParam Audio properties of the public stream. Refer to PublicStreamVideoParam{@link #PublicStreamVideoParam} for more details.
     */
    virtual void setVideoParam(const PublicStreamVideoParam&) = 0;
    /** 
     * @type api
     * @brief Set the layout of the public stream
     * @param [in] regions[] A array including layout configurations of each video stream. Refer to PublicStreamLayoutRegion{@link #PublicStreamLayoutRegion} for more details.
     * @param [in] regions_size Number of the streams included in the public stream
     * @param [in] bg_color Background color of the public stream
     * @param [in] mode Layout Mode of the public stream. Refer StreamLayoutMode{@link #StreamLayoutMode} to for more details.
     */
    virtual void setLayoutParam(
                PublicStreamLayoutRegion regions[], int32_t regions_size, const char* bg_color,
                StreamLayoutMode mode) = 0;
    /** 
     * @type api
     * @brief Transvert the json strings into ITranscoderParam struct
     * @param [in] json_str json string
     * @return ITranscoderParam struct
     */
    virtual IPublicStreamParam* inflatten(const char* json_str) = 0;
    /** 
     * @type api
     * @brief Validate the parameters passed in
     * @param [in] json_str String written in json syntax
     * @return <br>
     *         `true`: All the parameters are valid.<br>
     *         `false`: Invalid parameters.
     */
    virtual bool checkParameter(const char* json_str) = 0;
    /**
     * @hidden
     */
    virtual ~IPublicStreamParam() = default;
};

/** 
 * @hidden
 * @type api
 * @brief Create a instance of public stream parameters
 */
BYTERTC_API IPublicStreamParam* createPublicStreamParam();
} /* namespace bytertc */
