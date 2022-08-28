/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Video Defines
 */

#pragma once

#include "bytertc_common_defines.h"
#include "bytertc_video_frame.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief Rendering mode
 */
enum RenderMode {
    /** 
     * @brief Fill and Crop.  <br>
     *        The video frame is scaled with fixed aspect ratio, and completely fills the canvas. The region of the video exceeding the canvas will be cropped. <br>
     */
    kRenderModeHidden = 1,
    /** 
     * @brief Fit.  <br>
     *        The video frame is scaled with fixed aspect ratio, and is shown completely in the canvas. The region of the canvas not filled with video frame, is filled with `background`.  <br>
     */
    kRenderModeFit = 2,
    /** 
     *  @brief Fill the canvas. <br>
     *         The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    kRenderModeFill = 3,
};

/** 
 * @type keytype
 * @brief Type of the media stream subscribed to
 */
enum SubscribeMediaType {
    /** 
     * @brief Neither audio nor video
     */
    kRTCSubscribeMediaTypeNone = 0,
    /** 
     * @brief Audio only
     */
    kRTCSubscribeMediaTypeAudioOnly,
    /** 
     * @brief Video only
     */
    kRTCSubscribeMediaTypeVideoOnly,
    /** 
     * @brief Video only
     */
    kRTCSubscribeMediaTypeVideoAndAudio
};

/** 
 * @type keytype
 * @brief Pause/resume receiving the remote media stream type.
 */
enum PauseResumeControlMediaType {
    /** 
     * @brief Only control audio, not affect video
     */
    kRTCPauseResumeControlMediaTypeAudio = 0,
    /** 
     * @brief Only control video, not affect audio
     */
    kRTCPauseResumeControlMediaTypeVideo = 1,
    /** 
     * @brief Simultaneous control of audio and video
     */
    kRTCPauseResumeControlMediaTypeVideoAndAudio = 2
};

/** 
 * @type keytype
 * @brief  Time domain hierarchical definition
 */
enum SVCLayer {
    /** 
    * @brief No hierarchy specified (default)
    */
    kSVCLayerDefault = 0,
    /** 
     * @brief T0 layer
     */
    kSVCLayerBase = 1,
    /** 
     * @brief T0 + T1 layer
     */
    kSVCLayerMain = 2,
    /** 
     * @brief T0 + T1 + T2 layer
     */
    kSVCLayerHigh = 3,
};

/** 
 * @type keytype
 * @brief Information of stream switching due to a Fallback
 */
struct RemoteStreamSwitch {
    /** 
     * @brief User ID of the publisher of the subscribed media stream
     */
    const char* uid;
    /** 
     * @brief Whether it is a screen-sharing stream
     */
    bool is_screen;
    /** 
     * @brief The quality index of the subscribed stream before the stream switching
     */
    int before_video_index;
    /** 
     * @brief The quality index of the subscribed stream after the stream switching
     */
    int after_video_index;
    /** 
     * @brief Whether a video stream before the stream switching
     */
    bool before_enable;
    /** 
     * @brief Whether a video stream after the stream switching
     */
    bool after_enable;
    /** 
     * @brief Refer to FallbackOrRecoverReason{@link #FallbackOrRecoverReason} for the reason of the Fallback or reverting from the Fallback of the subscribed stream.
     */
    FallbackOrRecoverReason reason;
};

/** 
 * @type keytype
 * @brief Errors that may occur during pushing streams to CDN.
 */
enum TransCodingError {
    /** 
     * @brief Successfully pushed streams to target CDN.
     */
    kTransCodingErrorOK = 0,
    /** 
     * @brief Parameter error. You should reset stream pushing parameters and try again.
     */
    kTransCodingErrorInvalidArgument = 1,
    /** 
     * @brief Failed to establish a connection with the RTC server. SDK will automatically retry.
     */
    kTransCodingErrorSubscribe = 2,
    /** 
     * @brief There is an error in the process of stream mixing. We suggest you to try again.
     */
    kTransCodingErrorProcessing = 3,
    /** 
     * @brief Pushing the stream failed, you can wait for the server to push again.
     */
    kTransCodingErrorPublish = 4,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Retweet live broadcast contains content.
 */
enum LiveTranscodingContentControl {
    /** 
     * @brief The output of the mixed stream contains audio and video
     */
    kVideoAndAudio = 0,
    /** 
     * @brief The output mix contains only audio
     */
    kAudioOnly,
    /** 
     * @brief The output of the mixed stream contains only video
     */
    kVideoOnly,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Forward the live video encoder format.
 */
enum LiveTranscodingVideoCodec {
    /** 
     * @brief Use H264 encoding format
     */
    kLiveTranscondingH264,
    /** 
     * @brief Custom encoder
     */
    kLiveTranscodingByteVC1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Forward the live audio encoding format.
 */
enum LiveTranscodingAudioCodec {
    /** 
     * @brief Use AAC encoding format
     */
    kLiveTranscodingAAC,
};

/** 
 * @hidden
 * @type keytype
 * @brief AAC  encoding level.
 */
enum LiveTranscodingAudioProfile {
    /** 
     * @brief Encoding level AAC-LC (default)
     */
    kLiveTranscodingAACLC,
    /** 
     * @brief Encoding level AAC-MAIN
     */
    kLiveTranscodingAACMAIN,
    /** 
     * @brief Encoding level HE-AAC v1
     */
    kLiveTranscodingHEV1,
    /** 
     * @brief Encoding level HE-AAC v2
     */
    KLiveTranscodingHEV2,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Forward push video configuration.
 */
struct LiveTranscodingVideoConfig {
    /** 
     * @brief Forwarding live video encoder format. See LiveTranscodingVideoCodec{@link #LiveTranscodingVideoCodec}
     */
    LiveTranscodingVideoCodec codec;
    /** 
     * @brief Confluence video frame rate information
     */
    int fps;
    /** 
     * @brief Video I frame interval.
     */
    int gop;
    /** 
     * @brief Whether to use the low latency feature. The meaning of the value is as follows:   <br>
     *         + True: use the low latency feature <br>
     *         + False: do not use the low latency feature
     */
    bool low_latency;
    /** 
     *  @brief Confluence video bitrate in bps.
     */
    int bitrate;
    /** 
     * @brief Width (pixels)
     */
    int width;
    /** 
     * @brief High (pixels)
     */
    int height;
};

/** 
 * @hidden
 * @type keytype
 * @brief  Forward push audio configuration.
 */
struct LiveTranscodingAudioConfig {
    /** 
     * @brief Forwarding live audio encoder format. See LiveTranscodingAudioCodec{@link #LiveTranscodingAudioCodec}
     */
    LiveTranscodingAudioCodec codec = kLiveTranscodingAAC;
    /** 
     * @brief Confluence audio bitrate in bps.
     */
    int bitrate;
    /** 
     * @brief Audio frame sampling rate in HZ. Currently supported sampling rates are: 8000HZ, 16000HZ, 32000HZ, 44100HZ, 48000HZ.
     */
    int sample_rate;
    /** 
     * @brief Number of sound channels
     */
    int channels;
    /** 
     * @brief AAC  encoding level. See LiveTranscodingAudioProfile{@link #LiveTranscodingAudioProfile}
     */
    LiveTranscodingAudioProfile aac_profile = kLiveTranscodingAACLC;
};

/** 
 * @hidden
 * @type keytype
 * @brief  Layout information for a single video stream in the confluence.
 */
struct LiveTranscodingRegion {
    /** 
     * @brief The user ID of the video stream publishing user. Required.
     */
    const char* uid = nullptr;
    /** 
     * @brief The video stream publishes the user's room ID. Required.
     */
    const char* roomId = nullptr;
    /** 
     * @brief The offset of the user's video layout relative to the left side of the canvas. Relative values in the range [0.0, 1.0].
     */
    double x;
    /** 
     * @brief The offset of the user's video layout relative to the top of the canvas. Relative values in the range [0.0, 1.0].
     */
    double y;
    /** 
     * @brief The ratio of the user's video width relative to the user's original video width. Relative values in the range [0.0, 1.0].
     */
    double w;
    /** 
     * @brief The ratio of the user's video height to the user's original video height. Relative values in the range [0.0, 1.0].
     */
    double h;
    /** 
     * @brief The hierarchy of user video layouts in the canvas. 0 is the bottom layer, the larger the value, the higher the level, the range is [0, 100].
     */
    int zorder;
    /** 
     * @brief Transparency. The range is  [0.0, 1.0].
     */
    double alpha;
    /** 
     * @brief The live broadcast contains content. See LiveTranscodingContentControl{@link #LiveTranscodingContentControl}
     */
    LiveTranscodingContentControl content_control = kVideoAndAudio;
    /** 
     * @brief Rendering mode
     */
    RenderMode render_mode = kRenderModeHidden;
};

/** 
 * @hidden
 * @type keytype
 * @brief  Push flow layout settings.
 */
struct LiveTranscodingLayout {
    /** 
     * @brief SEI  information, length must not exceed 4096 bytes
     */
    const char* app_data = nullptr;
    /** 
     * @brief The background color of the video. The format is a Hex value defined by RGB, such as #FFB6C1 for light pink. Default #000000, black
     */
    const char* background_color = nullptr;
    /** 
     * @brief Push the live broadcast layout information. See LiveTranscodingRegion{@link #LiveTranscodingRegion}
     */
    LiveTranscodingRegion* regions = nullptr;
    /** 
     * @brief Number of confluence
     */
    int regions_num = 0;
};

/** 
 * @hidden
 * @type keytype
 * @brief  Retweet live broadcast configuration information.
 */
struct LiveTranscodingConfig {
    /** 
     * @brief Set the push stream address.
     */
    const char* url = nullptr;
    /** 
     * @brief Retweet video configuration. See LiveTranscodingVideoConfig{@link #LiveTranscodingVideoConfig}
     */
    LiveTranscodingVideoConfig video_config;
    /** 
     * @brief Forward push audio configuration. See LiveTranscodingAudioConfig{@link #LiveTranscodingAudioConfig}
     */
    LiveTranscodingAudioConfig audio_config;
    /** 
     * @brief Push flow layout settings. See LiveTranscodingLayout{@link #LiveTranscodingLayout}
     */
    LiveTranscodingLayout layout;
    /** 
     * @hidden
     * @brief  Set dynamically extended customizable parameters.
     */
    const char* advanced_config = nullptr;
};

/** 
 * @hidden
 * @deprecated since 332.1, use VirtualBackgroundSourceType instead
 * @type keytype
 * @brief  Background mode
 */
enum BackgroundMode {
    /** 
     *@brief No
     */
    kBackgroundModeNone = 0,
    /** 
     *@brief Virtualization
     */
    kBackgroundModeBlur = 1,
    /** 
     *@brief Background 1
     */
    kBackgroundModeA = 2,
    /** 
     *@brief Background 2
     */
    kBackgroundModeB = 3,
};

/** 
 * @hidden
 * @deprecated since 332.1, use enableVirtualBackground instead
 * @type keytype
 * @brief  To split the model
 */
enum DivideMode {
    /** 
     *@brief Self-research
     */
    kDivideModeNone = 0,
    /**
     *@brief effect
     */
    kDivideModeEffect = 1,
};

/** 
 * @type keytype
 * @brief  Flow property.   <br>
 */
struct MediaStreamInfo {
    /** 
     * @brief The user ID that published this stream.
     */
    const char* user_id;
    /** 
     * @brief Whether this stream is a shared screen stream.
     */
    bool is_screen;
    /** 
     * @brief Whether this stream includes a video stream.
     */
    bool has_video;
    /** 
     * @brief Whether the stream includes an audio stream.
     */
    bool has_audio;
    /** 
     * @brief Properties of the video stream.   <br>
     *        When a remote user calls the setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} method to publish multiple configured video streams, this will contain attribute information for all video streams published by the user.
     *        See VideoSolutionDescription{@link #VideoSolutionDescription}.
     */
    VideoSolutionDescription* profiles;
    /** 
     * @brief Number of different configuration streams.   <br>
     *        When a remote user calls the setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} method to publish multiple configured video streams, this contains the number of video streams published by the user.
     */
    int profile_count;

    /** 
     * @brief Properties of the maximum video stream.   <br>
     *            since version 336
     *        When a remote user calls the setVideoEncoderConfig {@link #IRtcEngineLite #setVideoEncoderConfig} method to publish multiple configured video streams, this will contain the maximum attribute information . user with new subscribe call can require any stream does not exceed this resolution.
     *        The final stream received, influenced by the others in room, server would diliver the closest to the resolution requested by the user。
     *
     */
    VideoSolutionDescription max_profile;
};

/** 
 * @type keytype
 * @brief  Video subscription configuration information
 */
struct SubscribeVideoConfig {
    /** 
     * @brief Subscribed video stream resolution subscript.   <br>
     *        In Simulcast mode, use a number to specify the expected quality of the video stream to be subscribed to.  In Simulcast mode, a video has a diversity of encoded qualities that ranking from 0 to 3. Call setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} to enable Simulcast mode on the publisher's clients.  <br>
     *         Ranging from -1 to 3<br>
     *         0 (Default): The best quality <br>
     *         -1: Use the previous settings. <br>
     */
    int video_index = 0;
    /** 
     * @brief Remote user priority. The default value is 0. Refer to RemoteUserPriority{@link #RemoteUserPriority} for more details.
     */
    int priority = 0;
    /** 
     * @hidden
     * @brief  Constructor
     */
    SubscribeVideoConfig() : video_index(0), priority(0) {
    }
    /**
     * @hidden
     */
    bool operator==(const SubscribeVideoConfig& config) const {
        bool result = video_index == config.video_index && priority == config.priority;
        return result;
    }
    /**
     * @hidden
     */
    bool operator!=(const SubscribeVideoConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

/** 
 * @type keytype
 * @brief  Configuration information for manual subscription flows.   <br>
 */
struct SubscribeConfig {
    /** 
     * @brief Whether it is a screen stream (default is no).   <br>
     */
    bool is_screen = false;
    /** 
     * @brief Whether to subscribe to videos.   <br>
     */
    bool sub_video;
    /** 
     * @brief Whether to subscribe to audio.   <br>
     */
    bool sub_audio;
    /** 
     * @brief Subscribed video stream resolution subscript.   <br>
     *        Users can publish multiple videos of different resolutions in a stream by calling the setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig} method. Therefore, when subscribing to a stream, you need to specify the specific resolution of the subscription. This parameter is used to specify the subscript of the resolution to be subscribed to, and the default value is 0. <br>
     */
    int video_index;
    /** 
     * @brief For the remote user's requirement priority. See RemoteUserPriority{@link #RemoteUserPriority}, the default value is 0. <br>
     *         When the subscription flow fallback option function is turned on (see setSubscribeFallbackOption{@link #IRtcEngine#setSubscribeFallbackOption} method for details), weak connections or insufficient performance will give priority to ensuring the quality of the received high-priority user's flow. <br>
     */
    int priority = 0;
    /** 
     * @brief The time domain hierarchy of the remote user. See SVCLayer{@link #SVCLayer}, the default value is 0. <br>
     *         This only works if the stream supports the SVC feature. <br>
     */
    int svc_layer = 0;
    /** 
     * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, values greater than 10 are valid.  <br>
     *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
     *        Only valid if the stream is coded with SVC technique.
     */
    int framerate = 0;
    /** 
     * @brief The user specifies the width(px) of the most appropriate stream corresponding to the UI by specifying
     */
    int sub_width = 0;
    /** 
     * @brief The user specifies the height(px) of the most appropriate stream corresponding to the UI by specifying
     */
    int sub_height = 0;
    /**
     * @hidden
     */
    int sub_video_index = -1;

public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    SubscribeConfig() : is_screen(false), sub_video(true), sub_audio(true), video_index(0), priority(0) {
    }

    /** 
     * @hidden
     * @brief  Constructor
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex)
            : is_screen(is_screen), sub_video(subvideo), sub_audio(subaudio), video_index(videoindex) {
    }

    /** 
     * @hidden
     * @brief  Constructor
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex, int priority)
            : is_screen(is_screen),
              sub_video(subvideo),
              sub_audio(subaudio),
              video_index(videoindex),
              priority(priority) {
    }

    /** 
     * @hidden
     * @brief  constructor
     */
    SubscribeConfig(bool is_screen, bool subvideo, bool subaudio, int videoindex,
     int priority,int svc_layer,int width,int height)
            : is_screen(is_screen),
              sub_video(subvideo),
              sub_audio(subaudio),
              video_index(videoindex),
              priority(priority),
              svc_layer(svc_layer),
              sub_width(width),
              sub_height(height) {
    }
    /**
     * @hidden
     */
    bool operator==(const SubscribeConfig& config) const {
        // sub_width * sub_height valid
        bool common_result = is_screen == config.is_screen && sub_video == config.sub_video
                                          && sub_audio == config.sub_audio && priority == config.priority
                                          && svc_layer == config.svc_layer && framerate == config.framerate;
        bool result;
        if(sub_width * sub_height > 0 && config.sub_width * config.sub_height > 0) {
          result = common_result && sub_width == config.sub_width && sub_height == config.sub_height ;
        }  else if((sub_width * sub_height == 0) && (config.sub_width * config.sub_height == 0) ) {
          result = common_result && video_index == config.video_index;
        } else {
          result = false;
        }
        return result;
    }

    /**
     * @hidden
     */
    bool operator!=(const SubscribeConfig& config) const {
        bool result = (*this == config);
        return !result;
    }
};

/** 
 * @type keytype
 * @brief Remote video type
 *      Currently C++ sdk only supports kVideoStreamTypeHigh type
 */
enum VideoStreamType {
    /** 
     * @brief High Resolution Video Streaming
     */
    kVideoStreamTypeHigh = 0,
    /** 
     * @brief Low Resolution Video
     */
    kVideoStreamTypeLow = 1,
};

/** 
 * @type keytype
 * @brief Video rendering mode <br>
 *        Use setLocalVideoCanvas{@link #IRtcEngine#setLocalVideoCanvas} to bind the video stream to the canvas.
 */
struct VideoCanvas {
    /** 
     * @brief Local view handle
     */
    void* view;
    /** 
     * @brief Video rendering mode. See RenderMode{@link #RenderMode}
     */
    int render_mode;
    /** 
     * @brief Set the background color of the canvas which is not filled with video frame. The range is `[0x0000000, 0xFFFFFFFF]`. The default is `0x00000000`. The Alpha index is ignored.
     */
    uint32_t background_color;
    /** 
     * @hidden
     * @brief Constructor
     */
    VideoCanvas() : view(NULL), render_mode(kRenderModeHidden), background_color(0) {
    }
    /** 
     * @hidden
     * @brief Constructor
     */
    VideoCanvas(void* v, int m, uint32_t c) : view(v), render_mode(m), background_color(c) {
    }
};

/** 
 * @type keytype
 * @brief Windows window id, Windows platform down to Windows window handle
 */
typedef void* view_t;

/** 
 * @type keytype
 * @brief  Rectangle area of the screen
 */
struct Rectangle {
    /** 
     * @brief The x coordinate of the upper left corner of the rectangular area
     */
    int x = 0;
    /** 
     * @brief The y coordinate of the upper left corner of the rectangular area
     */
    int y = 0;
    /** 
     * @brief Rectangle width
     */
    int width = 0;
    /** 
     * @brief Rectangular height
     */
    int height = 0;
};

/** 
 * @type keytype
 * @brief  Border highlighting settings for screen sharing
 */
struct HighlightConfig {
    /** 
     * @brief Whether to display a highlighted border. Yes by default.
     */
    bool enable_highlight = true;
    /** 
     * @brief The color of the border in hexadecimal ARGB: 0xAARRGGBB
     */
    uint32_t border_color = 0xFF29CCA3;
    /** 
     * @brief The width of the border in pixel
     */
    int border_width = 4;
};

/** 
 * @type keytype
 * @brief  Excludes the specified window when grabbing the screen, no form is excluded by default
 */
struct ScreenFilterConfig {
    /** 
     * @brief Exclude the list of windows when grabbing the screen. This parameter only takes effect when the screen is captured.
     */
    view_t* excluded_window_list = nullptr;
    /** 
     * @brief Exclude the number of windows.
     */
    int excluded_window_num = 0;
};

/** 
 * @type keytype
 * @region Screen sharing
 * @brief Whether to collect mouse information when collecting screen video stream internally
 */
enum MouseCursorCaptureState {
    /** 
     * @brief Collect mouse information
     */
    kMouseCursorCaptureStateOn,
    /** 
     * @brief Do not collect mouse information
     */
    kMouseCursorCaptureStateOff,
};

/** 
 * @hidden
 * @deprecated
 * @type keytype
 * @brief  Screen sharing parameter
 */
struct ScreenParameters {
    /** 
     * @brief Encoded frame rate in fps
     */
    int frame_rate = 15;
    /** 
     * @brief Encoding rate, when less than 0, the SDK will be based on the high and wide self-adaptation rate, in kbps
     */
    int kbitrate = -1;
};

/** 
 * @type keytype
 * @region Screen sharing
 * @brief Content hints of the internally captured screen video stream.
 */
enum ContentHint {
    /** 
     * @brief Detailed content. Recommended when you capture documents, images, etc.
     */
    kContentHintDetails = 0,
    /** 
     * @brief  Animation content. Recommended when you capture videos, games, etc.
     */
    kContentHintMotion,
};

/** 
 * @type keytype
 * @brief  Screen internal capture parameters
 */
struct ScreenCaptureParameters {
    /** 
     * @brief Content hint. See ContentHint{@link #ContentHint}.
     */
    ContentHint content_hint = kContentHintDetails;
    /** 
     * @brief Collection area. See Rectangle{@link #Rectangle}.
     */
    Rectangle region_rect;
    /** 
     * @brief To collect mouse status. See MouseCursorCaptureState{@link #MouseCursorCaptureState}.
     */
    MouseCursorCaptureState capture_mouse_cursor;
    /** 
     * @brief Screen filtering settings. See ScreenFilterConfig{@link #ScreenFilterConfig}.
     */
    ScreenFilterConfig filter_config;
    /** 
     * @brief For the border highlighting settings of the acquisition area. See HighlightConfig{@link #HighlightConfig}.
     */
    HighlightConfig highlight_config;
};

/** 
 * @type keytype
 * @brief  Encoding parameter configuration for screen sharing
 */
struct DesktopCaptureParameters {
    /** 
     * @brief Screen capture code maximum width
     */
    int max_width = 1920;
    /** 
     * @brief Screen capture coding maximum height
     */
    int max_height = 1080;
    /** 
     * @brief Screen capture coded frame rate,  unit fps
     */
    int frame_rate = 15;
    /** 
     * @brief Screen acquisition code rate, -1 is the automatic code rate, SDK will select the appropriate code rate according to the width and height information, unit kbps
     */
    int bitrate = -1;
    /** 
     * @brief Whether to capture the mouse cursor
     */
    bool capture_mouse_cursor = true;
    /** 
     * @brief Exclude the list of windows when grabbing the screen. This parameter only takes effect when the screen is captured.
     */
    view_t* excluded_window_list = nullptr;
    /** 
     * @brief The number of windows excluded when grabbing the screen.
     */
    int excluded_window_num = 0;
    /** 
     * @brief Configuration of highlighted borders
     */
    HighlightConfig highlight_config;
};

/** 
 * @type keytype
 * @brief Custom video renderer
 */
class IVideoSink {
public:
/** 
 * @type keytype
 * @brief Video frame encoding format
 */
enum PixelFormat {
    /** 
     * @brief YUV I420 format
     */
    kI420 = VideoPixelFormat::kVideoPixelFormatI420,
    /** 
     * @brief Original format
     */
    kOriginal = VideoPixelFormat::kVideoPixelFormatUnknown,
};
    /** 
     * @type callback
     * @brief Video frame callback
     * @param [out] VideoFrame Video frame structure. See IVideoFrame{@link #IVideoFrame}.
     * @return Temporarily unavailable
     */
    virtual bool onFrame(IVideoFrame* videoFrame) = 0;
    /** 
     * @hidden
     * @type callback
     * @region Room Management
     * @brief Gets the time taken in custom rendering.
     * @notes Gets the time taken in custom rendering and report. You need to calculate the average rendering time by yourself.
     */
    virtual int getRenderElapse() = 0;
    /** 
     * @type callback
     * @brief Releases the renderer.
     * @notes Used to notify the user that the renderer is about to be deprecated. Resources can be released upon receipt of this notification.
     */
    virtual void release() {
    }
    /** 
     * @hidden
     * @brief Destructor
     */
    virtual ~IVideoSink() = default;
};

/** 
 * @hidden
 * @type keytype
 * @deprecated since 329.1, use MirrorType instead
 * @brief  Whether to turn on mirror mode
 */
enum MirrorMode {
    /** 
     * @brief Not open
     */
    kMirrorModeOff = 0,
    /** 
     * @brief Open
     */
    kMirrorModeOn = 1,
};

/** 
 * @type keytype
 * @brief  Mirror type
 */
enum MirrorType {
    /** 
     * @brief The preview and the published video stream are not mirrored.
     */
    kMirrorTypeNone = 0,
    /** 
     * @brief The preview is mirrored. The published video stream is not mirrored.
     */
    kMirrorTypeRender = 1,
    /** 
     * @brief The preview and the published video stream are mirrored.
     */
    kMirrorTypeRenderAndEncoder = 3,
};

/** 
 * @type keytype
 * @brief  Low light adjusted type
 */
enum AdjustedMode {
    /** 
     * @brief Turn off low light adaptation
     */
    kAdjustedModeDisabled = 0,
    /** 
     * @brief Turn on low light adaptation
     */
    kAdjustedModeEnabled = 1,
};

/** 
 * @type keytype
 * @brief Video source type
 */
enum VideoSourceType {
    /** 
     * @brief Custom video source
     */
    VideoSourceTypeExternal = 0,
    /** 
     * @brief Internal video capture
     */
    VideoSourceTypeInternal = 1,
    /** 
     * @brief Custom encoded video source.   <br>
     *        Push the encoded video stream with the largest resolution, and the SDK will automatically transcode to generate multiple lower-quality streams for Simulcast.
     */
    VideoSourceTypeEncodedWithAutoSimulcast = 2,
    /** 
     * @brief Custom encoded video source.   <br>
     *         The SDK does not automatically generate multiple streams for Simulcast, you need to generate and push streams of different qualities.
     */
    VideoSourceTypeEncodedWithoutAutoSimulcast = 3,
};

/** 
 * @type keytype
 * @brief  Video frame information
 */
struct VideoFrameInfo {
    /** 
     * @brief Width (pixels)
     */
    int width = 0;
    /** 
     * @brief High (pixels)
     */
    int height = 0;
    /** 
     * @brief Video frame clockwise rotation angle. See VideoRotation{@link #VideoRotation}.
     */
    VideoRotation rotation = VideoRotation::kVideoRotation0;
};

/** 
 * @type keytype
 * @brief  Video preprocessing configuration parameters. <br>
 */
struct VideoPreprocessorConfig {
    /** 
     * @brief Video frame pixel format. See VideoPixelFormat{@link #VideoPixelFormat}
     */
    VideoPixelFormat required_pixel_format = kVideoPixelFormatUnknown;
};

/** 
 * @type keytype
 * @brief  Custom coded stream information
 */
struct VideoRateInfo {
    /** 
     * @brief Frame rate, units fps
     */
    int fps;
    /** 
     * @brief Bit rate, unit kbps
     */
    int bitrate_kbps;
};

/** 
 * @type keytype
 * @brief  Video decoding method
 */
enum VideoDecoderConfig {
    /** 
     * @brief Enable SDK internal decoding, only callback the decoded data
     */
    kVideoDecoderConfigRaw,
    /** 
     * @brief Turn on custom decoding, only callback the data before decoding
     */
    kVideoDecoderConfigEncode,
    /** 
     * @brief Enable SDK internal decoding, and call back the data before and after decoding at the same time
     */
    kVideoDecoderConfigBoth,
};

/** 
 * @hidden(Linux)
 * @type keytype
 * @brief  Video capture configuration parameters. <br>
 */
struct VideoCaptureConfig {
   /** 
    * @type keytype
    * @brief Video capture preference
    */
    enum CapturePreference {
       /** 
        * @brief (Default) Video capture preference: auto <br>
        *        SDK determines the best video capture parameters referring to the camera output parameters and the encoder configuration.
        */
        KAuto = 0,
       /** 
        * @brief Video capture preference: manual <br>
        *        Set the resolution and the frame rate manually.
        */
        KManual = 1,
       /** 
        * @brief Video capture preference: encoder configuration <br>
        *        The capture parameters are the same with the parameters set in setVideoEncoderConfig{@link #IRtcEngine#setVideoEncoderConfig}.
        */
        KAutoPerformance = 2,
    };
   /** 
    * @brief Video capture preference
    */
    CapturePreference capturePreference = CapturePreference::KAuto;

    /** 
     * @brief The width of video capture resolution in px.
     */
    int width = 0;
    /** 
     * @brief The height of video capture resolution in px.
     */
    int height = 0;
    /** 
     * @brief Video capture frame rate in fps.
    */
    int frameRate = 0;
};

/** 
 * @type keytype
 * @brief Locally recorded media type
 */
enum RecordingType {
    /** 
     * @brief Audio only
     */
    kRecordAudioOnly = 0,
    /** 
     * @brief Video only
     */
    kRecordVideoOnly = 1,
    /** 
     * @brief Record audio and video simultaneously
     */
    kRecordVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief  Current audio device type
 */
enum RTCVideoDeviceType {
    /** 
     * @brief Unknown device type
     */
    kRTCVideoDeviceTypeUnknown = -1,
    /** 
     * @brief Audio Rendering Device Type
     */
    kRTCVideoDeviceTypeRenderDevice = 0,
    /** 
     * @brief Audio Acquisition Device Type
     */
    kRTCVideoDeviceTypeCaptureDevice = 1,
    /** 
     * @brief Screen Streaming Audio Devices
     */
    kRTCVideoDeviceTypeScreenCaptureDevice = 2,
};

/** 
 * @hidden(Windows, MacOS, Linux)
 * @type keytype
 * @brief Video orientation
 */
enum VideoRotationMode {
    /** 
     * @brief The orientation of the App
     */
    kVideoRotationModeFollowApp = 0,
    /** 
     * @brief Gravity
     */
    kVideoRotationModeFollowGSensor = 1,
};

/** 
 * @type keytype
 * @brief Media stream type
 */
enum MediaStreamType {
    /** 
     * @brief Controls audio only
     */
    kMediaStreamTypeAudio = 1 << 0,
    /** 
     * @brief Controls video only
     */
    kMediaStreamTypeVideo = 1 << 1,
    /** 
     * @brief Controls both audio and video
     */
    kMediaStreamTypeBoth = kMediaStreamTypeAudio | kMediaStreamTypeVideo
};
/** 
 * @type keytype
 * @brief Ratio to the original video frame rate of the publisher
 */
enum FrameRateRatio {
  /** 
   * @brief 100%
   */
  kFrameRateRatioOriginal = 0,
  /** 
   * @brief 50%
   */
  kFrameRateRatioHalf = 1,
  /** 
   * @brief 25%
   */
  kFrameRateRatioQuarter = 2,
};
/** 
 * @type keytype
 * @brief Information on remote video frame
 */
struct RemoteVideoConfig {
    /** 
     * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, values greater than 10 are valid.  <br>
     *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
     *        Only valid if the stream is coded with SVC technique.
     */
    int framerate = 0;
    /** 
     * @brief Width of the video frame in px
     */
    int resolution_width = 0;
    /** 
     * @brief Height of the video frame in px
     */
    int resolution_height = 0;
};
/** 
 * @type keytype
 * @brief Room configuration
 */
struct RTCRoomConfig {
    /** 
      * @brief Room profile. See RoomProfileType{@link #RoomProfileType}. The default is `kRoomProfileTypeCommunication`. The setting cannot be changed after joining the room.
      */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
    * @brief Whether to publish media streams automatically. The default is automatic publishing.  <br>
    *        If you call setUserVisibility{@link #IRTCRoom#setUserVisibility} to set your own visibility to false, you will not publish media streams regardless of the value of `is_auto_publish`.
    */
    bool is_auto_publish = true;
    /** 
      * @brief Whether to automatically subscribe to the audio stream. The default is automatic subscription.
      */
    bool is_auto_subscribe_audio = true;
    /** 
     * @brief Whether to automatically subscribe to the main video stream. The default is automatic subscription.   <br>
     *        Screen streams are always automatically subscribed and are not affected by this parameter.
     */
    bool is_auto_subscribe_video = true;
    /** 
     * @brief Expected configuration of remote video stream, see RemoteVideoConfig{@link #RemoteVideoConfig}.
     */
    RemoteVideoConfig remote_video_config;
};
/** 
 * @type keytype
 * @brief  Multi-room parameter configuration
 */
struct MultiRoomConfig {
    /** 
     * @brief Room mode. See RoomProfileType{@link #RoomProfileType}, the default is normal audio & video call mode, which cannot be changed after entering the room.
     */
    RoomProfileType room_profile_type = kRoomProfileTypeCommunication;
    /** 
     * @brief Whether to automatically subscribe to the audio stream, the default is automatic subscription
     */
    bool is_auto_subscribe_audio = true;
    /** 
     * @brief Whether to automatically subscribe to the video stream, the default is automatic subscription
     */
    bool is_auto_subscribe_video = true;
    /** 
     * @brief Expected configuration of remote video stream, see RemoteVideoConfig{@link #RemoteVideoConfig}.
     */
    RemoteVideoConfig remote_video_config;
};

/** 
 * @type keytype
 * @brief  The media type for screen capture
 */
enum ScreenMediaType {
    /** 
     * @brief Capture video only
     */
    kScreenMediaTypeVideoOnly = 0,
    /** 
     * @brief Capture audio only
     */
    kScreenMediaTypeAudioOnly = 1,
    /** 
     * @brief Capture Audio and video simultaneously.
     */
    kScreenMediaTypeVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief Basic beauty effect.
 */
enum EffectBeautyMode {
    /** 
     * @brief Brightness.
     */ 
    kEffectBeautyWhite = 0,
    /** 
     * @brief Smoothness.
     */
    kEffectBeautySmooth = 1,
    /** 
     * @brief Sharpness.
     */ 
    kEffectBeautySharpen = 2,
};

/** 
 * @type keytype
 * @brief Video device information
 */
struct VideoDeviceInfo {
    /** 
     * @brief Device ID
     */
    char device_id[MAX_DEVICE_ID_LENGTH];
    /** 
     * @brief Device alias
     */
    char device_name[MAX_DEVICE_ID_LENGTH];
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
     * @hidden
     */
    VideoDeviceInfo() {
        memset(device_id, 0, MAX_DEVICE_ID_LENGTH);
        memset(device_name, 0, MAX_DEVICE_ID_LENGTH);
        this->device_vid = 0;
        this->device_pid = 0;
        this->transport_type = DeviceTransportType::kDeviceTransportTypeUnknown;
    };
    
    /**
     * @hidden
     */
    VideoDeviceInfo& operator=(const VideoDeviceInfo& src) {
        if (this != &src) {
            strncpy(device_id, src.device_id, MAX_DEVICE_ID_LENGTH - 1);
            strncpy(device_name, src.device_name, MAX_DEVICE_ID_LENGTH - 1);
            device_id[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_name[MAX_DEVICE_ID_LENGTH - 1] = '\0';
            device_vid = src.device_vid;
            device_pid = src.device_pid;
            transport_type = src.transport_type;
        }
        
        return *this;
    }
};

}  // namespace bytertc
