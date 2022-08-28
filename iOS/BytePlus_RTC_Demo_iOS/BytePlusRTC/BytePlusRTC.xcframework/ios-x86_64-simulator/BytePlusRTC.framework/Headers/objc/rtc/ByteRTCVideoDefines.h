/*
 * Copyright (c) 2022 The BytePlusRTC project authors. All Rights Reserved.
 * @brief Objective-C BytePlusRTC Video Defines
*/

#import "ByteRTCCommonDefines.h"
#import "ByteRTCAudioDefines.h"
/** 
 * @type keytype
 * @brief Video rendering mode
 */
typedef NS_ENUM(NSUInteger, ByteRTCRenderMode) {
    /** 
     * @brief Fill and Crop.  <br>
     *        The video frame is scaled with fixed aspect ratio, and completely fills the canvas. The region of the video exceeding the canvas will be cropped. <br>
     */
    ByteRTCRenderModeHidden = 1,
    /** 
     * @brief Fit.  <br>
     *        The video frame is scaled with fixed aspect ratio, until it fits just within the canvas. Other part of the canvas is filled with the background color.  <br>
     */
    ByteRTCRenderModeFit = 2,
    /** 
     *  @brief Fill the canvas. <br>
     *         The video frame is scaled to fill the canvas. During the process, the aspect ratio may change.
     */
    ByteRTCRenderModeFill = 3,
};

/** 
 * @type keytype
 * @brief  Stream mixing content type
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderContentControlType) {
    /** 
     * @brief The mixed stream contains audio and video.
     */
    ByteRTCTranscoderContentControlTypeHasAudioAndVideo = 0,
    /** 
     * @brief The mixed stream only contains audio.
     */
    ByteRTCTranscoderContentControlTypeHasAudioOnly = 1,
    /** 
     * @brief The mixed stream only contains video.
     */
    ByteRTCTranscoderContentControlTypeHasVideoOnly = 2,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Stream mixing region type
 */
typedef NS_ENUM(NSUInteger, ByteRTCTranscoderLayoutRegionType) {
    
    /** 
     * @brief The region type is a video stream.
     */
    ByteRTCTranscoderLayoutRegionTypeVideoStream = 0,
    
    /** 
     * @brief The region type is an image.
     */
    ByteRTCTranscoderLayoutRegionTypeImage = 1,
};


/** 
 * @type keytype
 * @brief  Video Stream Type
 *       Currently C++ SDK only supports ByteRTCVideoStreamTypeHigh type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamType) {
    /** 
     * @brief High Resolution Video Streaming
     */
    ByteRTCVideoStreamTypeHigh = 0,
    /** 
     * @brief Low Resolution Video
     */
    ByteRTCVideoStreamTypeLow = 1,
};

/** 
 * @type keytype
 * @brief  Sets the return state of the local video property.
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamState) {
    /** 
     * @brief Set local video properties successfully
    */
    ByteRTCVideoStreamStateSuccess                 = 0,
    /** 
     * @brief Local video attribute parameter is invalid
    */
    ByteRTCVideoStreamStateInvalid                 = -2,
};

/** 
 * @type keytype
 * @brief  Video output direction mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoOutputOrientationMode) {
    /** 
     * @brief Self-adaptation layout
     */
    ByteRTCVideoOutputOrientationModeAdaptative = 0,
    /** 
     * @brief Landscape layout
     */
    ByteRTCVideoOutputOrientationModeFixedLandscape = 1,
    /** 
     * @brief Vertical screen layout
     */
    ByteRTCVideoOutputOrientationModeFixedPortrait = 2,
};

/** 
 * @hidden
 * @type keytype
 * @deprecated since 329.1 use ByteRTCMirrorType instead
 * @brief  Whether to turn on mirror mode
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorMode) {
    /** 
     *  @brief Not open
     */
    ByteRTCMirrorModeOff = 0,
    /** 
     *  @brief Open
     */
    ByteRTCMirrorModeOn = 1,
};

/** 
 * @type keytype
 * @brief  Mirror type
 */
typedef NS_ENUM(NSUInteger, ByteRTCMirrorType) {
    /** 
     * @brief The preview and the published video stream are not mirrored.
     */
    ByteRTCMirrorTypeNone = 0,
    /** 
     * @brief The preview is mirrored. The published video stream is not mirrored.
     */
    ByteRTCMirrorTypeRender = 1,
    /** 
     * @brief The preview and the published video stream are mirrored.
     */
    ByteRTCMirrorTypeRenderAndEncoder = 3,
};

/** 
 * @type keytype
 * @brief Basic beauty effect.
 */
typedef NS_ENUM(NSUInteger, ByteRTCEffectBeautyMode) {
    /** 
     * @brief Brightness.
     */ 
    ByteRTCEffectWhiteMode = 0,
    /** 
     * @brief Smoothness.
     */
    ByteRTCEffectSmoothMode = 1,
    /** 
     * @brief Sharpness.
     */ 
    ByteRTCEffectSharpenMode = 2,
};

/** 
 * @type keytype
 * @brief Information on video frame rotation angle
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoRotation) {
    /** 
     * @brief Video does not rotate
     */
    ByteRTCVideoRotation0 = 0,
    /** 
     * @brief Video rotates 90 degrees clockwise
     */
    ByteRTCVideoRotation90 = 90,
    /** 
     * @brief Video rotates 180 degrees clockwise
     */
    ByteRTCVideoRotation180 = 180,
    /** 
     * @brief Video rotates 270 degrees clockwise
     */
    ByteRTCVideoRotation270 = 270,
};

/** 
 * @type keytype
 * @brief Video content type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoContentType) {
    /** 
     * @brief Normal video
     */
    ByteRTCVideoContentTypeNormalFrame = 0,
    /** 
     * @brief Black frame video
     */
    ByteRTCVideoContentTypeBlackFrame = 1,
};

/** 
 * @type keytype
 * @brief  Video frame scale mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoStreamScaleMode) {
    /** 
     * @brief Auto mode, default to ByteRTCVideoStreamScaleModeFitWithCropping.
     */
    ByteRTCVideoStreamScaleModeAuto            = 0,
    /** 
     * @brief Stretch the video frame until the video frame and the window have the same resolution. The video frame's aspect ratio can be changed as it is automatically stretched to fill the window, but the whole image is visible.
     */
    ByteRTCVideoStreamScaleModeStretch         = 1,
    /** 
     * @brief  Fit the window with cropping   <br>
     *         Scale the video frame uniformly until the window is filled. If the video frame's aspect ratio is different from that of the window, the extra part of the video frame will be cropped. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be greater than or equal to that of the window.
     */
    ByteRTCVideoStreamScaleModeFitWithCropping = 2,
    /** 
     * @brief  Fit the window with filling   <br>
     *         Scale the video frame uniformly until its width or height reaches the boundary of the window. If the video frame's aspect ratio is different from that of the window, the area that is not filled will be black. <br>
     *         After the scaling process is completed, the width or height of the video frame will be consistent with that of the window, and the other dimension will be less than or equal to that of the window.
     */
    ByteRTCVideoStreamScaleModeFitWithFilling  = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Video encoding mode
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCodecMode) {
    /** 
     * @brief Automatic selection
    */
    ByteRTCVideoCodecModeAuto     = 0,
    /** 
     * @brief Hardcoding
    */
    ByteRTCVideoCodecModeHardware = 1,
    /** 
     * @brief Softcoding
    */
    ByteRTCVideoCodecModeSoftware = 2
};

/** 
 * @type keytype
 * @brief Video compression picture type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPictureType) {
    /** 
     * @brief Unknown type
     */
    ByteRTCVideoPictureTypeUnknown = 0,
    /** 
     * @brief I-frames, key frames which are coded without reference to any other frame.
     */
    ByteRTCVideoPictureTypeI = 1,
    /** 
     * @brief P-frames, forward-predicted frames which are coded by a forward predictive coding method.
     */
    ByteRTCVideoPictureTypeP = 2,
    /** 
     * @brief B-frames, bi-directionally predicted frames which are coded by both forward and backward predictive coding method.
     */
    ByteRTCVideoPictureTypeB = 3,
};

/** 
 * @type keytype
 * @brief  Encoder preference
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoEncoderPreference) {
    /** 
     * @brief No preference
     */
    ByteRTCVideoEncoderPreferenceDisabled          = 0,
    /** 
     * @brief Frame rate first
     */
    ByteRTCVideoEncoderPreferenceMaintainFramerate = 1,
    /** 
     * @brief Quality first
     */
    ByteRTCVideoEncoderPreferenceMaintainQuality   = 2,
    /** 
     * @brief Balancing quality and frame rate
     */
    ByteRTCVideoEncoderPreferenceBalance           = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Background mode setting.
 */
typedef NS_ENUM(NSUInteger, ByteRTCBackgroundMode) {
    /** 
     * @brief No
     */
    ByteRTCBackgroundModeNone = 0,
    /** 
     * @brief Virtualization
     */
    ByteRTCBackgroundModeBlur = 1,
    /** 
     * @brief Background 1
     */
    ByteRTCBackgroundModeA = 2,
    /** 
     * @brief Background 2
     */
    ByteRTCBackgroundModeB = 3,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Split model settings.
 */
typedef NS_ENUM(NSUInteger, ByteRTCDivideModel) {
    /** 
     * @brief Self-research
     */
    ByteRTCDivideModelDefault = 0,
    /**
     * @brief effect
     */
    ByteRTCDivideModelEffect = 1,
};

/** 
 * @type keytype
 * @brief Data type
 */
typedef NS_ENUM(NSUInteger, ByteRTCDataFrameType) {
    /** 
     * @brief SEI data
     */
    ByteRTCDataFrameTypeSei = 0,
    /** 
     * @brief Facial recognition data
     */
    ByteRTCDataFrameTypeRoi = 1,
    /** 
     * @brief Other data frame type
     */
    ByteRTCDataFrameTypeOther = 2,
};

/** 
 * @type keytype
 * @brief  Video capture preference
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoCapturePreference) {
   /** 
    * @brief (Default) Video capture preference: auto <br>
    *        SDK determines the best video capture parameters referring to the camera output parameters and the encoder configuration.
    */
    ByteRTCVideoCapturePreferenceAuto = 0,
   /** 
    * @brief Video capture preference: manual <br>
    *        Set the resolution and the frame rate manually.
    */
    ByteRTCVideoCapturePreferenceMannal = 1,
   /** 
    * @brief Video capture preference: encoder configuration
    */
    ByteRTCVideoCapturePreferenceAutoPerformance = 2,
};

/** 
 * @type keytype
 * @brief  Video frame type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoFrameType) {
    /** 
     * @brief Video frame type: memory data
     */
    ByteRTCVideoFrameTypeRawMemory = 0,
    /** 
     * @brief Video frame type: CVPixelBuffer
     */
    ByteRTCVideoFrameTypePixelBuffer,
};

/** 
 * @type keytype
 * @brief Video frame format
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoPixelFormat) {
    /** 
     * @brief Unknown format
     */
    ByteRTCVideoPixelFormatUnknown = 0,
    /** 
     * @brief I420
     */
    ByteRTCVideoPixelFormatI420 = 1,
    /** 
     * @brief BGRA
     */
    ByteRTCVideoPixelFormatBGRA = 2,
    /** 
     * @brief NV21
     */
    ByteRTCVideoPixelFormatNV21 = 3,
    /** 
     * @brief RGBA
     */
    ByteRTCVideoPixelFormatRGBA = 4,
    /** 
     * @brief IMC2
     */
    ByteRTCVideoPixelFormatIMC2 = 5,
    /** 
     * @brief ARGB
     */
    ByteRTCVideoPixelFormatARGB = 7,
    /** 
     * @brief NV12
     */
    ByteRTCVideoPixelFormatNV12 = 8,
    /** 
     * @brief Opengl Texture2D
     */
    ByteRTCVideoPixelFormatGLTexture2D = 10,
    /** 
     * @brief Opengl OES
     */
    ByteRTCVideoPixelFormatGLTextureOES = 11,
    /** 
     * @brief CVPixelBuffer
     */
    ByteRTCVideoPixelFormatCVPixelBuffer = 12
};

/** 
 * @type keytype
 * @brief Video frame encoding format
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSinkPixelFormat) {
    /** 
     * @brief Original format
     */
    ByteRTCVideoSinkPixelFormatOriginal = 0,
    /** 
     * @brief YUV I420
     */
    ByteRTCVideoSinkPixelFormatI420 = 1,
    /** 
     * @brief BGRA
     */
    ByteRTCVideoSinkPixelFormatBGRA = 2,
    /** 
     * @brief YUV NV21
     */
    ByteRTCVideoSinkPixelFormatNV12 = 8
};

/** 
 * @type errorcode
 * @brief  Forward the error code of the live broadcast function.
 */
typedef NS_ENUM(NSInteger, ByteRTCTranscodingError) {
    /** 
     * @brief Push flow success.
     */
    ByteRTCTranscodingErrorOK = 0,
    /** 
     * @brief Push flow parameter error. You must update the confluence parameters and try again.
     */
    ByteRTCTranscodingErrorInvalidArgument = 1,
    /** 
     * @brief Failed to establish a connection with the RTC server level. Will automatically reconnect
     */
    ByteRTCTranscodingErrorSubscribe = 2,
    /** 
     * @brief There is an error in the intermediate process of the Confluence service. It is recommended to try again.
     */
    ByteRTCTranscodingErrorProcessing = 3,
    /** 
     * @brief Pushing the stream failed, you can wait for the server level to push the stream again.
     */
    ByteRTCTranscodingErrorPublish = 4,
};

/** 
 * @type keytype
 * @brief Stream mixing type
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingType) {
    /** 
     * @brief Push streams to CDN using RTC server
     */
    ByteRTCStreamMixingTypeByServer = 0,
    /** 
     * @brief Intelligently push streams to CDN
     */
    ByteRTCStreamMixingTypeByClient = 1,
};
/** 
 * @type keytype
 * @brief Events during pushing streams to CDN
 */
typedef NS_ENUM(NSUInteger, ByteRTCStreamMixingEvent) {
    /**
     * @hidden
     */
    ByteRTCStreamMixingEventBase = 0,
    /** 
     *  Request to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStart = 1,
    /** 
     *  the task to push streams to CDN started
     */
    ByteRTCStreamMixingEventStartSuccess = 2,
    /** 
     *  Failed to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStartFailed = 3,
    /** 
     *  Request to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdate = 4,
    /** 
     *  Successfully update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateSuccess = 5,
    /** 
     *  Failed to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateFailed = 6,
    /** 
     *  Request to stop the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStop = 7,
    /** 
     *  the task to push streams to CDN stopped
     */
    ByteRTCStreamMixingEventStopSuccess = 8,
    /** 
     *  Failed to stop the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStopFailed = 9,
    /** 
     *  Timeout for the request to update the configuration for the task to push streams to CDN.
     */
    ByteRTCStreamMixingEventChangeMixType = 10,
    /** 
     *  Got the first frame of the mixed audio stream by client.
     */
    ByteRTCStreamMixingEventFirstAudioFrameByClientMixer = 11,
    /** 
     *  Got the first frame of the mixed video stream by client.
     */
    ByteRTCStreamMixingEventFirstVideoFrameByClientMixer = 12,
    /** 
     *  Timeout for the request to update the configuration for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventUpdateTimeout = 13,
    /** 
     *  Timeout for the request to start the task to push streams to CDN
     */
    ByteRTCStreamMixingEventStartTimeout = 14,
    /** 
     *  Error in the parameters of the request for the task to push streams to CDN
     */
    ByteRTCStreamMixingEventRequestParamError = 15,
    /** 
     * @hidden
     *  Mixing image.
     */
    ByteRTCStreamMixingEventMixImage = 16,
};

/** 
 * @type keytype
 * @brief Type of the media stream subscribed to
 */
typedef NS_ENUM(NSInteger, ByteRTCSubscribeMediaType) {
    /** 
     * @brief Neither audio nor video
     */
    ByteRTCSubscribeMediaTypeNone = 0,
    /** 
     * @brief Audio only
     */
    ByteRTCSubscribeMediaTypeAudioOnly = 1,
    /** 
     * @brief Video only
     */
    ByteRTCSubscribeMediaTypeVideoOnly = 2,
    /** 
     * @brief Both audio and video
     */
    ByteRTCSubscribeMediaTypeAudioAndVideo = 3,
};

/** 
 * @type keytype
 * @brief Pause/resume receiving the remote media stream type.
 */
typedef NS_ENUM(NSInteger, ByteRTCPauseResumControlMediaType) {
    /** 
     * @brief Only control audio, not affect video
     */
    ByteRTCControlMediaTypeAudio = 0,
    /** 
     * @brief Only control video, not affect audio
     */
    ByteRtcControlMediaTypeVideo = 1,
    /** 
     * @brief Simultaneous control of audio and video
     */
    ByteRtcControlMediaTypeAudioAndVideo = 2,
};

/** 
 * @hidden
 * @deprecated
 * @type keytype
 * @brief  Video input type
 */
typedef NS_ENUM(NSInteger, ByteRTCMediaInputType) {
    /** 
     * @brief Custom collection.   <br>
     *         After setting, you can push video frames directly to the SDK.
     */
    ByteRTCMediaInputTypeExternal = 0,
    /** 
     * @brief Internal SDK acquisition. <br>
     *         This setting only switches to internal collection. You need to continue to call startVideoCapture{@link #ByteRTCEngineKit#startVideoCapture} to open internal collection.
     */
    ByteRTCMediaInputTypeInternal = 1
};

/** 
 * @type keytype
 * @brief Video source type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoSourceType) {
    /** 
     * @brief Custom video source
     */
    ByteRTCVideoSourceTypeExternal = 0,
    /** 
     * @brief Internal video capture
     */
    ByteRTCVideoSourceTypeInternal = 1,
    /** 
     * @brief Custom encoded video source.   <br>
     *         Push the encoded video stream with the largest resolution, and the SDK will automatically transcode to generate multiple lower-quality streams for Simulcast.
     */
    ByteRTCVideoSourceTypeEncodedManualSimulcast = 2,
    /** 
     * @brief Custom encoded video source.   <br>
     *         The SDK does not automatically generate multiple streams for Simulcast, you need to generate and push streams of different qualities.
     */
    ByteRTCVideoSourceTypeEncodedAutoSimulcast = 3
};

/** 
 * @type keytype
 * @brief  Video decoding method
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDecoderConfig) {
    /** 
     * @brief Enable SDK internal decoding, only callback the decoded data
     */
    ByteRTCVideoDecoderConfigRaw = 0,
    /** 
     * @brief Turn on custom decoding, only callback the data before decoding
     */
    ByteRTCVideoDecoderConfigEncode = 1,
    /** 
     * @brief Enable SDK internal decoding, and call back the data before and after decoding at the same time
     */
    ByteRTCVideoDecoderConfigBoth = 2
};

/** 
 * @type keytype
 * @brief Virtual background type.
 */
typedef NS_ENUM(NSInteger, ByteRTCVirtualBackgroundSourceType){
    /** 
     * @brief Replace the original video background with the background of a solid color.
     */
    ByteRTCVirtualBackgroundSourceTypeColor = 0,
    /** 
     * @brief Replace the original video background with the custom picture.
     */
    ByteRTCVirtualBackgroundSourceTypeImage = 1
};

/** 
 * @type keytype
 * @brief Camera on a mobile device
 */
typedef NS_ENUM(NSInteger, ByteRTCCameraID) {
    /** 
     * @brief Front-facing camera
     */
    ByteRTCCameraIDFront = 0,
    /** 
     * @brief Back-facing camera
     */
    ByteRTCCameraIDBack = 1,
    /** 
     * @brief External camera
     */
    ByteRTCCameraIDExternal = 2,
    /** 
     * @brief Invalid value
     */
    ByteRTCCameraIDInvalid = 3,
};
/** 
 * @type errorcode
 * @brief Errors occuring during pushing streams to CDN
 */
typedef NS_ENUM(NSInteger, ByteRtcTranscoderErrorCode) {
    /** 
     *  Successfully pushed streams to target CDN.
     */
    ByteRtcTranscoderErrorCodeOK = 0,
    /** 
     * Undefined error
     */ 
    ByteRtcTranscoderErrorCodeBase = 1090,
    /** 
     *  Invalid parameters detected by client SDK.
     */
    ByteRtcTranscoderErrorCodeInvalidParam = 1091,
    /** 
     *  Program runs with an error, the state machine is in abnormal condition.
     */
    ByteRtcTranscoderErrorCodeInvalidState = 1092,
    /** 
     *  Invalid operation
     */
    ByteRtcTranscoderErrorCodeInvalidOperator = 1093,
    /** 
     *  Request timed out. Please check network status and retry.
     */
    ByteRtcTranscoderErrorCodeTimeOut = 1094,
    /** 
     *  Invalid parameters detected by the server.
     */
    ByteRtcTranscoderErrorCodeInvalidParamByServer = 1095,
    /** 
     *  Your subscription of the stream has expired.
     */
    ByteRtcTranscoderErrorCodeSubTimeoutByServer = 1096,
    /** 
     *  Internal server error.
     */
    ByteRtcTranscoderErrorCodeInvalidStateByServer = 1097,
    /** 
     *  The server failed to push streams to CDN.
     */
    ByteRtcTranscoderErrorCodeAuthenticationByCDN = 1098,
    /** 
     *  Signaling connection timeout error. Please check network status and retry.
     */
    ByteRtcTranscoderErrorCodeTimeoutBySignaling = 1099,
    /** 
     *  Fail to mix image.
     */
    ByteRtcTranscoderErrorCodeMixImageFail = 1100,
    /** 
     *  Unknown error from server.
     */
    ByteRtcTranscoderErrorCodeUnKnownErrorByServer = 1101,
    /**
     * @hidden
     */
    ByteRtcTranscoderErrorCodeMax = 1199,
};

/** 
 * @type keytype
 * @brief Locally recorded media type
 */
typedef NS_ENUM(NSInteger, ByteRTCRecordingType) {
    /** 
     * @brief Audio only
     */
    RecordAudioOnly = 0,
    /** 
     * @brief Video only
     */
    RecordVideoOnly = 1,
    /** 
     * @brief Record audio and video simultaneously
     */
    RecordVideoAndAudio = 2,
};

/** 
 * @type keytype
 * @brief  Screen media type
 */
typedef NS_ENUM(NSInteger, ByteRTCScreenMediaType) {
    /** 
     *@brief only capture video data
     */
    ByteRTCScreenMediaTypeVideoOnly = 0,
    /** 
     *@brief only capture audio data
     */
    ByteRTCScreenMediaTypeAudioOnly = 1,
    /** 
     *@brief capture video && audio data
     */
    ByteRTCScreenMediaTypeVideoAndAudio = 2
};

/** 
 * @type keytype
 * @author liyi.000
 * @brief Type of the screen capture object
 */
typedef NS_ENUM(NSUInteger, ByteRTCScreenCaptureSourceType) {
    /** 
     * @brief Type unknown
     */
    ByteRTCScreenCaptureSourceTypeUnknown = 0,
    /** 
     * @brief Application window
     */
    ByteRTCScreenCaptureSourceTypeWindow = 1,
    /** 
     * @brief Desktop
     */
    ByteRTCScreenCaptureSourceTypeScreen = 2
};
/** 
 * @type keytype
 * @brief Whether to capture the mouse when capturing the screen
 */
typedef NS_ENUM(NSUInteger, ByteRTCMouseCursorCaptureState) {
    /** 
     * @brief Collect mouse information
     */
    ByteRTCMouseCursorCaptureStateOn,
    /** 
     * @brief Do not collect mouse information
     */
    ByteRTCMouseCursorCaptureStateOff,
};
/** 
 * @type keytype
 * @brief  Border highlighting settings for screen sharing
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCHighlightConfig: NSObject
/** 
 * @brief Whether to display a highlighted border. Yes by default.
 */
@property (assign, nonatomic) BOOL enableHighlight;
/** 
 * @brief The color of the border in hexadecimal ARGB: 0xAARRGGBB
 */
@property (assign, nonatomic) uint32_t borderColor;
/** 
 * @brief The width of the border in pixel
 */
@property (assign, nonatomic) int borderWidth;
@end

/** 
 * @type keytype
 * @brief Torch status
 */
typedef NS_ENUM(NSInteger, ByteRTCTorchState) {
    /** 
     * @brief Torch off
     */
    ByteRTCTorchStateOff = 0,
    /** 
     * @brief Torch on
     */
    ByteRTCTorchStateOn = 1,
};

/** 
 * @type keytype
 * @brief  Current audio device type
 */
typedef NS_ENUM(NSInteger, ByteRTCVideoDeviceType) {
    /** 
     * @brief Unknow video device
     */
    ByteRTCVideoDeviceTypeUnknown = -1,
    /** 
     * @brief Video Rendering Device Type
     */
    ByteRTCVideoDeviceTypeRenderDevice = 0,
    /** 
     * @brief Video Acquisition Device Type
     */
    ByteRTCVideoDeviceTypeCaptureDevice = 1,
    /** 
     *@brief Screen Capture Device Type
     */
    ByteRTCVideoDeviceTypeScreenCaptureDevice = 2
};

/** 
 * @type keytype
 * @brief Media stream type
 */
typedef NS_OPTIONS(NSUInteger, ByteRTCMediaStreamType) {
    /** 
     * @brief Controls audio only
     */
    ByteRTCMediaStreamTypeAudio = (1 << 0),
    /** 
     * @brief Controls video only
     */
    ByteRTCMediaStreamTypeVideo = (1 << 1),
    /** 
     * @brief Controls both audio and video
     */
    ByteRTCMediaStreamTypeBoth = ByteRTCMediaStreamTypeAudio | ByteRTCMediaStreamTypeVideo,
};

/** 
 * @type keytype
 * @brief Ratio to the original video frame rate of the publisher
 */
typedef NS_ENUM(NSUInteger, ByteRTCFrameRateRatio) {
    /** 
     * @brief 100%
     */
    ByteRTCFrameRateRatioOrigin = 0,
    /** 
     * @brief 50%
     */
    ByteRTCFrameRateRatioHalf = 1,
    /** 
     * @brief 25%
     */
    ByteRTCFrameRateRatioQuater = 2,
};

/** 
 * @type keytype
 * @brief Video orientation
 */
typedef NS_ENUM(NSUInteger, ByteRTCVideoRotationMode) {
    /** 
     * @brief The orientation of the App
     */
    ByteRTCVideoRotationModeFollowApp = 0,
    /** 
     * @brief Gravity
     */
    ByteRTCVideoRotationModeFollowGSensor = 1,
};

/** 
 * @hidden
 * @type keytype
 * @brief  Expression detection configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectConfig : NSObject
/** 
 * @brief Whether to enable age detection.
 */
@property (assign, nonatomic) BOOL enableAgeDetect;
/** 
 * @brief Whether to enable gender detection.
 */
@property (assign, nonatomic) BOOL enableGenderDetect;
/** 
 * @brief Whether to enable emotion detection.
 */
@property (assign, nonatomic) BOOL enableEmotionDetect;
/** 
 * @brief Whether to enable attractiveness detection.
 */
@property (assign, nonatomic) BOOL enableAttractivenessDetect;
/** 
 * @brief Whether to enable happiness detection.
 */
@property (assign, nonatomic) BOOL enableHappinessDetect;
@end

/** 
 * @hidden
 * @type keytype
 * @brief  Expression detect information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectInfo : NSObject
/** 
* @brief The estimated age in range of (0, 100).
*/
@property (assign, nonatomic) float age;
/** 
* @brief The estimated probability of being a male in range of (0.0, 1.0).
*/
@property (assign, nonatomic) float boyProb;
/** 
* @brief The estimated attractiveness in range of (0, 100).
*/
@property (assign, nonatomic) float attractive;
/** 
* @brief The estimated happy score in range of (0, 100).
*/
@property (assign, nonatomic) float happyScore;
/** 
* @brief The estimated sad score in range of (0, 100).
*/
@property (assign, nonatomic) float sadScore;
/** 
* @brief The estimated angry score in range of (0, 100).
*/
@property (assign, nonatomic) float angryScore;
/** 
* @brief The estimated surprise score in range of (0, 100).
*/
@property (assign, nonatomic) float surpriseScore;
/** 
* @brief The estimated emotional arousal in range of (0, 100).
*/
@property (assign, nonatomic) float arousal;
/** 
* @brief The estimated emotional valence in range of (-100, 100).
*/
@property (assign, nonatomic) float valence;
@end

/** 
 * @hidden
 * @type keytype
 * @brief Expression Detection Result
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCExpressionDetectResult : NSObject
/** 
 * @brief Expression detection result <br>
 *        + 0: Success <br>
 *        + !0: Failure <br>
 */
@property (assign, nonatomic) int detectResult;
/** 
 * @brief The number of detected faces.
 */
@property (assign, nonatomic) int faceCount;

/** 
 * @brief Expression detection information. The length of the array is the same as the number of detected faces. See ByteRTCExpressionDetectInfo{@link #ByteRTCExpressionDetectInfo}.
 */
@property (nonatomic, copy) NSArray<ByteRTCExpressionDetectInfo *> * _Nonnull detectInfo;

@end

/** 
 * @type keytype
 * @brief Rectangle Area
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRectangle : NSObject
/** 
 * @brief The x coordinate of the upper left corner of the rectangular area
 */
@property(assign, nonatomic) int x;
/** 
 * @brief The y coordinate of the upper left corner of the rectangular area
 */
@property(assign, nonatomic) int y;
/** 
 * @brief Rectangle width in px
 */
@property(assign, nonatomic) int width;
/** 
 * @brief Rectangular height in px
 */
@property(assign, nonatomic) int height;
@end
/** 
 * @type keytype
 * @brief Face Detection Result
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFaceDetectionResult : NSObject
/** 
 * @brief Face Detection Result <br>
 *        + 0: Success <br>
 *        + !0: Failure
 */
@property(assign, nonatomic) int detectResult;
/** 
 * @brief Width of the original image (px)
 */
@property(assign, nonatomic) int imageWidth;
/** 
 * @brief Height of the original image (px)
 */
@property(assign, nonatomic) int imageHeight;
/** 
 * @brief The face recognition rectangles. The length of the array is the same as the number of detected faces. See ByteRTCRectangle{@link #ByteRTCRectangle}.
 */
@property(nonatomic, copy) NSArray<ByteRTCRectangle *> * _Nullable faces;

@end
/** 
 * @type keytype
 * @brief Video rendering mode
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCanvas : NSObject
/** 
 * @brief Local view handle
 */
@property(strong, nonatomic) ByteRTCView* _Nullable view;
/** 
 * @brief See ByteRTCRenderMode{@link #ByteRTCRenderMode}
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief room ID
 */
@property(strong, nonatomic) NSString* _Nullable roomId;
/** 
 * @brief User ID
 */
@property(strong, nonatomic) NSString* _Nullable uid;
/** 
 * @brief Set the background color of the canvas which is not filled with video frame. The range is `[0x0000000, 0xFFFFFFFF]`. The default is `0x00000000`. The Alpha index is ignored.
 */
@property(assign, nonatomic) NSInteger backgroundColor;
@end

/** 
 * @type keytype
 * @brief Attached data obtained after video decoding
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCFrameExtendedData : NSObject
/** 
 * @brief Data type. See ByteRTCDataFrameType{@link #ByteRTCDataFrameType}.
 */
@property(assign, nonatomic) ByteRTCDataFrameType frameType;
/** 
 * @brief Attached data
 */
@property(strong, nonatomic) NSData * _Nullable extendedData;
/** 
 * @brief Data length
 */
@property(assign, nonatomic) NSInteger extendedDataLen;
@end

NS_ASSUME_NONNULL_BEGIN

/** 
 * @type keytype
 * @brief  Video stream parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoSolution: NSObject
/** 
 * @brief Video resolution
 */
@property(nonatomic, assign) CGSize videoSize;
/** 
 * @brief Video frame rate
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief Maximum bitrate (kbps). You can use `-1` to use the self-adaptive bitrate based on the resolution and framerate.
 */
@property(nonatomic, assign) NSInteger maxKbps;
/** 
 * @brief Video frame scale mode. You can adjust the scale to fit the window. See ByteRTCVideoStreamScaleMode{@link #ByteRTCVideoStreamScaleMode}.
 */
@property(nonatomic, assign) ByteRTCVideoStreamScaleMode mode;

/** 
 * @brief Encoder preference. See ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end

/** 
 * @type keytype
 * @brief  Video acquisition parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCaptureConfig: NSObject
/** 
 * @brief Video capture preference. See ByteRTCVideoCapturePreference{@link #ByteRTCVideoCapturePreference}
 */
@property(nonatomic, assign) ByteRTCVideoCapturePreference preference;

/** 
 * @brief Video capture resolution
 */
@property(nonatomic, assign) CGSize videoSize;
/** 
 * @brief Video capture frame rate in fps.
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief  Flow property.
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCStream <NSObject>
/** 
 * @brief The user ID that published this stream. <br>
 */
@property(nonatomic, copy, readonly) NSString * userId;
/** 
 * @brief Whether this stream is a shared screen stream.   <br>
 */
@property(nonatomic, assign, readonly) BOOL isScreen;
/** 
 * @brief Whether this stream includes a video stream.   <br>
 */
@property(nonatomic, assign, readonly) BOOL hasVideo;
/** 
 * @brief Whether the stream includes an audio stream.   <br>
 */
@property(nonatomic, assign, readonly) BOOL hasAudio;
/** 
 * @brief Resolution information of the video stream.   <br>
 *         When a remote user calls SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} method to publish multiple configured video streams, this will contain attribute information for all video streams published by the user. <br>
 *          See ByteRTCVideoSolution{@link #ByteRTCVideoSolution}. <br>
 */
@property(nonatomic, copy, readonly) NSArray<ByteRTCVideoSolution *> * videoStreamDescriptions;
/** 
 * @brief The maximum resolution of the video stream, the maximum publish resolution that can be supported by the callback publisher when multi-resolution publish subscription is enabled.
 */
@property(nonatomic, retain, readonly) ByteRTCVideoSolution *maxVideoStreamDescription;
@end

/** 
 * @type keytype
 * @brief  Stream Information
 */
@interface ByteRTCStreamEx : NSObject <ByteRTCStream>
/** 
 * @brief User ID
 */
@property(nonatomic, copy, nullable) NSString *userId;
/** 
 * @brief Whether the stream is a shared screen stream.
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief Does the path contain video
 */
@property(nonatomic, assign) BOOL hasVideo;
/** 
 * @brief Does this stream contain audio?
 */
@property(nonatomic, assign) BOOL hasAudio;
/** 
 * @brief For resolution information of the video stream. See ByteRTCVideoSolution{@link #ByteRTCVideoSolution} class.
 *         Users can publish multiple different video resolutions in a stream by calling the SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} method. This parameter is information about all resolutions in the stream.
 */
@property(nonatomic, copy, nullable) NSArray<ByteRTCVideoSolution *> *videoStreamDescriptions;
/** 
 * @brief The maximum resolution of the video stream, the maximum publish resolution that can be supported by the callback publisher when multi-resolution publish subscription is enabled.
 */
@property(nonatomic, retain, nullable) ByteRTCVideoSolution *maxVideoStreamDescription;
@end

/** 
 * @type keytype
 * @brief  The parameter configuration of the subscription flow. Subscription configuration parameters user manually subscribes to all the audio & video streams used.   <br>
 *         When the user turns off the automatic subscription function, when using the manual subscription mode, he subscribes to the audio & video stream by calling the `subscribeStream`, and the incoming parameters are for this data type. <br>
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeConfig: NSObject
/** 
 * @brief Whether it is a screen stream.   <br>
 *         By setting this parameter, the user subscribes to the screen share stream or non-screen share stream published by the remote user. YES is a subscription screen share flow, NO is a subscription non-screen share flow, the default value is YES. <br>
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief Whether to subscribe to videos.   <br>
 *         The user selects whether to subscribe to videos in the remote stream by setting this parameter. YES is a subscription video, NO is a non-subscription video, the default value is YES. <br>
 */
@property(nonatomic, assign) BOOL subscribeVideo;
/** 
 * @brief Whether to subscribe to audio.   <br>
 *         The user selects whether to subscribe to audio in the remote stream by setting this parameter. YES is subscribed audio, NO is not subscribed audio, the default value is YES. <br>
 */
@property(nonatomic, assign) BOOL subscribeAudio;
/** 
 * @brief Subscribed video stream resolution subscript.   <br>
 *         Users can publish multiple videos streams of different resolutions by calling the SetVideoEncoderConfig:{@link #ByteRTCEngineKit#SetVideoEncoderConfig:} method. Therefore, when subscribing to a stream, you need to specify the specific resolution of the subscription. This parameter is used to specify the subscript of the resolution to be subscribed to, and the default value is 0. <br>
 */
@property(nonatomic, assign) NSInteger videoIndex;
/** 
 * @brief Time domain hierarchy of the subscribed video stream, default value is 0.  <br>
 */
@property(nonatomic, assign) NSInteger svcLayer;
/** 
 * @brief The width in px of the subscription, the default value is 0. <br>
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief The height in px of the subscription, the default value is 0.
 */
@property(nonatomic, assign) NSInteger height;
/**
 * @hidden
 */
@property(nonatomic, assign) NSInteger subVideoIndex;
/** 
 * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, values greater than 10 are valid.  <br>
 *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
 *        Only valid if the stream is coded with SVC technique.
 */
@property (nonatomic, assign) NSInteger framerate;


@end

NS_ASSUME_NONNULL_END

/** 
 * @type keytype
 * @brief Video data to be encoded by SDK
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrame : NSObject
/** 
 * @brief Video frame format, see ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}
 */
@property(assign, nonatomic) int format;
/** 
 * @hidden
 * @type api
 * @brief Gets video content type.
 * @return See ByteRTCVideoContentType{@link #ByteRTCVideoContentType}.
 */
@property(assign, nonatomic) ByteRTCVideoContentType contentType;
/** 
 * @brief The timestamp information of the current frame
 */
@property(assign, nonatomic) CMTime time;
/**
 * @hidden
 */
@property(assign, nonatomic) int stride DEPRECATED_MSG_ATTRIBUTE("use strideInPixels instead");
/** 
 * @brief Number of bytes per pixel line
 */
@property(assign, nonatomic) int strideInPixels;
/** 
 * @brief Video frame width
 */
@property(assign, nonatomic) int width;
/** 
 * @brief Video frame height
 */
@property(assign, nonatomic) int height;
/** 
 * @brief Data of CVPixelBufferRef type, valid when format is kPixelFormatCVPixelBuffer
 */
@property(assign, nonatomic) CVPixelBufferRef _Nullable textureBuf;
/** 
 * @brief The first address in video frame memory
 */
@property(strong, nonatomic) NSData * _Nullable dataBuf;
/** 
 * @brief Size (in pixels) of the video frame cropped on the left
 */
@property(assign, nonatomic) int cropLeft;
/** 
 * @brief Size (in pixels) of the video frame cropped on the top
 */
@property(assign, nonatomic) int cropTop;
/** 
 * @brief Size (in pixels) of the video frame cropped on the right
 */
@property(assign, nonatomic) int cropRight;
/** 
 * @brief Size (in pixels) of the video frame cropped on the bottom
 */
@property(assign, nonatomic) int cropBottom;
/** 
 * @brief Video frame rotation angle, the value must be 0,  90, 180, or 270
 */
@property(assign, nonatomic) ByteRTCVideoRotation rotation;
/** 
 * @hidden
 * @brief Video mirroring information
 */
@property(assign, nonatomic) int flip;
/** 
 * @brief the cameraId of the video frame, see ByteRTCCameraID{@link #ByteRTCCameraID}
 */
@property(assign, nonatomic) ByteRTCCameraID cameraId;
/** 
 * @brief Data attached to the video frame, see ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}
 */
@property(strong, nonatomic) ByteRTCFrameExtendedData * _Nullable extendedData;
@end

/** 
 * @type keytype
 * @brief Information about video frames
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCEncodedVideoFrame : NSObject
/** 
 * @brief Video encoding type. See ByteRTCVideoCodecType{@link #ByteRTCVideoCodecType}
 */
@property(assign, nonatomic) ByteRTCVideoCodecType codecType;
/** 
 * @brief Video compression picture type. See ByteRTCVideoPictureType{@link #ByteRTCVideoPictureType}
 */
@property(assign, nonatomic) ByteRTCVideoPictureType pictureType;
/** 
 * @brief Video capture timestamp in microseconds
 */
@property(assign, nonatomic) SInt64 timestampUs;
/** 
 * @brief Video encoding timestamp in microseconds
 */
@property(assign, nonatomic) SInt64 timestampDtsUs;
/** 
 * @brief Video frame width in px
 */
@property(assign, nonatomic) int width;
/** 
 * @brief Video frame height in px
 */
@property(assign, nonatomic) int height;
/** 
 * @brief Video frame rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
/** 
 * @brief The pointer to the video frame
 */
@property(strong, nonatomic) NSData * _Nonnull data;

@end
/** 
 * @hidden
 * @type keytype
 * @brief  Image parameters for stream mixing
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscoderLayoutRegionDataParam : NSObject
/** 
 * @brief Width of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageWidth;
/** 
 * @brief Height of the original image in px.
 */
@property (assign, nonatomic) NSInteger imageHeight;
@end

/** 
 * @type keytype
 * @brief Layout information for one of the video streams to be mixed.   <br>
 *        After starting to push streams to CDN and mixing multiple video streams, you can set the layout information for each of them.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingRegion : NSObject
/** 
 * @brief The user ID of the user who publishes the video stream. Required.
 */
@property(copy, nonatomic) NSString * _Nonnull uid;
/** 
 * @brief The room ID of the media stream. <br>
 *        If the media stream is the stream forwarded by startForwardStreamToRooms:{@link #ByteRTCEngineKit#startForwardStreamToRooms:}, you must set the roomID to the room ID of the target room. <br>
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief The normalized horizontal coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0).  <br>
 *        The view's position is determined by the position of its top left end vertex in the coordinate of the canvas. The coordinate is formed  with the top side of the canvas as the x-axis, the left side as the y-axis, and the top left end vertex as the origin point.
 */
@property(assign, nonatomic) CGFloat x;
/** 
 * @brief The normalized vertical coordinate value of the top left end vertex of the user's view, ranging within [0.0, 1.0).  <br>
 *        The view's position is determined by the position of its top left end vertex in the coordinate of the canvas. The coordinate is formed  with the top side of the canvas as the x-axis, the left side as the y-axis, and the top left end vertex as the origin point.
 */
@property(assign, nonatomic) CGFloat y;
/** 
 * @brief The normalized width of the user's view, ranging within (0.0, 1.0].
 */
@property(assign, nonatomic) CGFloat width;
/** 
 * @brief The normalized height of the user's view, ranging within (0.0, 1.0].
 */
@property(assign, nonatomic) CGFloat height;
/** 
 * @brief The layter on which the video is rendered. The range is [0, 100]. 0 for the bottom layer, and 100 for the top layer.
 */
@property(assign, nonatomic) NSInteger zOrder;
/** 
 *  @brief Whether the source user of the stream is a local user.
 */
 @property(assign, nonatomic) BOOL localUser;
/** 
 *  @brief Whether the stream comes from screen sharing, the default value is No.
 */
 @property(assign, nonatomic) BOOL screenStream;
/** 
 * @brief The opacity in range of [0.0, 1.0]. The lower value, the more transparent.
 */
@property(assign, nonatomic) CGFloat alpha;
/** 
 * @brief The stream mixing content type. The default value is `ByteRTCTranscoderContentControlTypeHasAudioAndVideo`. See ByteRTCTranscoderContentControlType{@link #ByteRTCTranscoderContentControlType}.
 */
@property (assign, nonatomic) ByteRTCTranscoderContentControlType contentControl;

/** 
 * @brief Video rendering mode. See ByteRTCRenderMode{@link #ByteRTCRenderMode} for data types. <br>
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @hidden
 * @brief Stream mixing region type. See ByteRTCTranscoderLayoutRegionType{@link #ByteRTCTranscoderLayoutRegionType}.
 */
@property (assign, nonatomic) ByteRTCTranscoderLayoutRegionType type;
/** 
 * @hidden
 * @brief   The RGBA data of the mixing image. Put in null when mixing video streams.
 */
@property (strong, nonatomic) NSData * _Nullable data;
/** 
 * @hidden
 * @type keytype
 * @brief  Image parameters for stream mixing. See ByteRTCTranscoderLayoutRegionDataParam{@link #ByteRTCTranscoderLayoutRegionDataParam}. Put in null when mixing video streams.
 */
@property (strong, nonatomic) ByteRTCTranscoderLayoutRegionDataParam * _Nullable dataParam;
@end

/** 
 * @type keytype
 * @brief The overall video layout of the mixed stream.   <br>
 *        After starting to push streams to CDN, you can set the layout of each video stream, the background information of the mixed stream, etc.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoCompositingLayout : NSObject
/** 
 * @brief Background color of the canvas,in RGB hex value. For example, #FFB6C1 represents light pink. The default value is #000000 (black).
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief List of user's video layout information. The specific layout of each stream is detailed in ByteRTCVideoCompositingRegion{@link #ByteRTCVideoCompositingRegion}.
 */
@property(copy, nonatomic) NSArray<ByteRTCVideoCompositingRegion *> * _Nonnull regions;
/** 
 * @brief Data passed through from the App.
 */
@property(copy, nonatomic) NSString *_Nonnull appData;
@end

/** 
 * @type keytype
 * @brief Video transcoding related configurations.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingVideoConfig : NSObject
/** 
 * @brief The video codec. The default value is `0`. <br>
 *        + Specify `0` to use H.264; <br>
 *        + Specify `1` to use byteVC1. You must specify the bitrate of ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig}.
 */
@property(copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief The width (px) of the mixed video stream. The value ranges in [2, 1920], and must be an even number. The default value is 640.
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief The height (px) of the mixed video stream. The value ranges in [2, 1080], and must be an even number. The default value is 480.
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief The frame rate. The default value is `15`. The range is `[1, 60]`. If the value is not legal, the SDK uses the default value.
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief GOP. The default value is `4`. The range is `[1, 5]`. The unit is second. If the value is not legal, the SDK uses the default value.
 */
@property(assign, nonatomic) NSInteger gop;
/** 
 * @brief Bitrate of the mixed video stream. The default value is self-adaptive. The range is `[1, 10000]`. The unit is kbps. If the value is not legal, the SDK uses the default value.
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief Whether to push streams with low latency.
 */
@property(assign, nonatomic) BOOL lowLatency;
@end

/** 
 * @type keytype
 * @brief Audio transcoding configurations.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCTranscodingAudioConfig : NSObject
/** 
 * @brief The audio codec. Only `AAC` is available currently.
 */
@property(copy, nonatomic) NSString * _Nonnull codec;
/** 
 * @brief The sample rate(kHz). Supported sample rates: 32Khz, 44.1Khz, 48Khz. Defaults to 48Khz.
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief The number of channels. Supported channels: 1, 2.  Defaults to 2.
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief The bitrate(Kbps) in range of [32Kbps, 192Kbps]. Defaults to 64Kbps.
 */
@property(assign, nonatomic) NSInteger kBitRate;
/** 
 * @brief AAC profile. See ByteRTCAACProfile{@link #ByteRTCAACProfile}. Defaults to `0`.
 */
@property(assign, nonatomic) ByteRTCAACProfile profile;
/**
 * @hidden
 */
+ (NSString* _Nonnull) toStringWithProfile:(ByteRTCAACProfile) aacProfile;
@end

/** 
 * @type keytype
 * @brief Configurations to be set when pushing media streams to CDN.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCLiveTranscoding : NSObject
/** 
 * @brief Stream mixing type. See ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}.
 */
@property(assign, nonatomic) ByteRTCStreamMixingType expectedMixingType;
/** 
 * @brief The overall video layout of the mixed stream.    <br>
 *        After starting to push streams to CDN, you can set the layout of each video stream, the background information of the mixed stream, etc. See ByteRTCVideoCompositingLayout{@link #ByteRTCVideoCompositingLayout} for details.
 */
@property(strong, nonatomic) ByteRTCVideoCompositingLayout * _Nonnull layout;
/** 
 * @brief Video transcoding related configurations. See ByteRTCTranscodingVideoConfig{@link #ByteRTCTranscodingVideoConfig}.
 */
@property(strong, nonatomic) ByteRTCTranscodingVideoConfig * _Nonnull video;
/** 
 * @brief Audio transcoding related configurations. See ByteRTCTranscodingAudioConfig{@link #ByteRTCTranscodingAudioConfig} for data types.
 */
@property(strong, nonatomic) ByteRTCTranscodingAudioConfig * _Nonnull audio;
/** 
 * @hidden
 * @brief Custom parameter
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable advancedConfig;
/** 
 * @brief Authentication information passed through from the App
 */
@property(strong, nonatomic) NSMutableDictionary *  _Nullable authInfo;
/** 
 * @brief The CDN url where the mixed stream is supposed to be pushed
 */
@property(copy, nonatomic) NSString * _Nullable url;
/** 
 * @brief The room ID of the user who publishes the video stream, need set.
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief The user ID of the user who publishes the video stream
 */
@property(copy, nonatomic) NSString * _Nullable userId;
/** 
 * @brief Gets the default configurations for pushing streams to CDN.
 * @return Configurations for pushing streams to CDN. See ByteRTCLiveTranscoding{@link #ByteRTCLiveTranscoding}.
 */
+ (instancetype _Nonnull)defaultTranscoding;
@end

/** 
 * @type keytype
 * @brief  Video subscription configuration information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSubscribeVideoConfig : NSObject
/** 
 * @brief Subscribed video stream resolution subscript.   <br>
 *        Quality level of the video stream subscribed to. <br>
 *        In Simulcast mode, use a number to specify the expected quality of the video stream to be subscribed to.  In Simulcast mode, a video has a diversity of encoded qualities that ranking from 0 to 3. Call enableSimulcastMode:{@link #ByteRTCEngineKit#enableSimulcastMode:} to enable Simulcast mode on the publisher's clients.  <br>
 *         Ranging from -1 to 3<br>
 *         0 (Default): The best quality <br>
 *         -1: Use the previous settings. <br>
 */
@property(assign, nonatomic) NSInteger videoIndex;
/** 
 * @brief Remote user priority. See ByteRTCRemoteUserPriority{@link #ByteRTCRemoteUserPriority}, the default value is 0.
 */
@property(assign, nonatomic) NSInteger priority;
@end

/** 
 * @type keytype
 * @brief  Performance fallback related data
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceWantedData : NSObject
/** 
 * @brief Recommended video input width
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief Recommended video input high
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief Recommended video input frame rate
 */
@property(nonatomic, assign) NSInteger frameRate;
@end

/** 
 * @type keytype
 * @brief Information of stream switching due to a Fallback
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteStreamSwitchEvent : NSObject
/** 
 * @brief User ID of the publisher of the subscribed media stream
 */
@property(nonatomic, copy) NSString * _Nonnull uid;
/** 
 * @brief Whether it is a screen-sharing stream
 */
@property(nonatomic, assign) BOOL isScreen;
/** 
 * @brief The quality index of the subscribed stream before the stream switching
 */
@property(nonatomic, assign) NSInteger beforeVideoIndex;
/** 
 * @brief The quality index of the subscribed stream after the stream switching
 */
@property(nonatomic, assign) NSInteger afterVideoIndex;
/** 
 * @brief Whether a video stream before the stream switching
 */
@property(nonatomic, assign) BOOL beforeVideoEnabled;
/** 
 * @brief Whether a video stream after the stream switching
 */
@property(nonatomic, assign) BOOL afterVideoEnabled;
/** 
 * @brief Refer to ByteRTCFallbackOrRecoverReason{@link #ByteRTCFallbackOrRecoverReason} for the reason of the Fallback or reverting from the Fallback of the subscribed stream.
 */
@property(nonatomic, assign) ByteRTCFallbackOrRecoverReason reason;
@end

/** 
 * @hidden
 * @deprecated Please use ByteVideoSinkDelegate
 * @type callback
 * @brief Custom video rendering
 */
DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate")
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkProtocol <NSObject>
@required
/** 
 * @hidden
 * @type callback
 * @brief Initialize the renderer
 * @return   <br>
 *          + YES: Custom renderer initialization completed <br>
 *          + NO: Custom renderer initialization failed, do not continue to run <br>
 * @notes Initialize the renderer when this method will be called back
 */
- (BOOL)shouldInitialize DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");;

/** 
 * @hidden
 * @type callback
 * @brief Start the renderer
 * @notes This method will be called back when the rendering function is turned on
 */
- (void)shouldStart DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief Stop the renderer
 * @notes This method will be called back when the rendering function is stopped
 */
- (void)shouldStop DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief Release the renderer
 * @notes This method will be called back when the renderer is about to be abandoned
 */
- (void)shouldDispose DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief  Gets the PixelFormat format
 * @return Buffer  type, {@link #ByteRTCVideoSinkPixelFormat}
 * @notes  Tells SDK the format of PixelFormat through the return value of this method
 */
- (ByteRTCVideoPixelFormat)pixelFormat DEPRECATED_MSG_ATTRIBUTE("Please use ByteRTCVideoSinkDelegate");

/** 
 * @hidden
 * @type callback
 * @brief Output video PixelBuffer
 * @param pixelBuffer Video PixelBuffer
 * @param rotation Video rotation angle, {@link #ByteRTCVideoRotation}
 * @param cameraId Video camera id, {@link #ByteRTCCameraID}
 * @param extendedData Video frame additional data, additional data obtained after video decoding
 * @notes Get video PixelBuffer through this method
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 cameraId:(ByteRTCCameraID) cameraId
             extendedData:(NSData * _Nullable)extendedData DEPRECATED_MSG_ATTRIBUTE("Please use ByteVideoSinkDelegate");

/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @type keytype
 * @brief Custom video renderer
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoSinkDelegate <NSObject>
@required
/** 
 * @type api
 * @brief Outputs video PixelBuffer
 * @param pixelBuffer Video PixelBuffer
 * @param rotation Video rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}
 * * @param contentType Video content type. See ByteRTCVideoContentType{@link #ByteRTCVideoContentType}
 * @param extendedData Additional data obtained after video is decoded.
 */
- (void)renderPixelBuffer:(CVPixelBufferRef _Nonnull)pixelBuffer
                 rotation:(ByteRTCVideoRotation)rotation
                 contentType:(ByteRTCVideoContentType)contentType
             extendedData:(NSData * _Nullable)extendedData;
/**
 * @hidden
 */
- (int)getRenderElapse;
@end

/** 
 * @hidden
 * @type callback
 * @brief  Consumption interface for external rendering data
 */
@protocol ByteRTCVideoFrameConsumerObserver <NSObject>
/** 
 * @brief Output yuv420 data
 * @param ocFrame  Data Buffer
 * @param width  Video width
 * @param rotation  Video rotation angle
 * @param timestamp  Timestamp
 */
- (void)consumeYUV420Buffer:(CVPixelBufferRef _Nullable)ocFrame
    width:(NSInteger)width rotation:(NSInteger)rotation timestamp:(long)timestamp;
/** 
 * @brief Output RGBA data
 * @param pixelBuffer Data Buffer
 * @param width Video width
 * @param rotation Video rotation angle
 * @param timestamp Timestamp
 */
- (void)consumeRGBABuffer:(CVPixelBufferRef _Nullable)ocFrame width:(NSInteger)width
    rotation:(NSInteger)rotation timestamp:(long)timestamp;
@end

/** 
 * @type callback
 * @region  Video Management
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoFrameObserver <NSObject>
/** 
 * @brief Callback of video frame data for local screen stream
 * @param frame Local screen video frame data, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame;
/** 
 * @brief Callback of video frame data for local video stream
 * @param frame Video frame data for local video stream, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 */
- (void)onLocalVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame;

/** 
 * @brief Video frame data callback for the remote screen stream
 * @param frame Video frame data for the remote screen, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid Remote screen sharing user ID
 * @param room Room id for the corresponding stream
 */
- (void)onRemoteScreenFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;
/** 
 * @brief Callback of video frame data of remote video stream
 * @param frame Video frame data of remote video stream, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @param uid Remote screen sharing user ID
 * @param room Room id of corresponding stream
 */
- (void)onRemoteVideoFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid
    room:(NSString * _Nullable)room;

/**
 * @hidden
 */
- (void)OnMergeFrame:(ByteRTCVideoFrame * _Nonnull)frame user:(NSString * _Nullable)uid room:(NSString * _Nullable)room;

@end

/** 
 * @type keytype
 * @brief  Video processing configuration parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoPreprocessorConfig : NSObject
/** 
 * @brief For the pixel format of the video frame. See ByteRTCVideoPixelFormat{@link #ByteRTCVideoPixelFormat}.
 */
@property(nonatomic, assign) ByteRTCVideoPixelFormat required_pixel_format;

@end

/** 
  * @type callback
  * @region  video processing
  */
BYTERTC_APPLE_EXPORT @protocol ByteRTCVideoProcessorDelegate <NSObject>

/** 
 * @type api
 * @region  video processing
 * @author zhushufan.ref
 * @brief  Get RTC SDK acquired video frames, according to registerLocalVideoProcessor:withConfig:{@link #ByteRTCEngineKit#registerLocalVideoProcessor:withConfig:} set the video preprocessor, video preprocessing, and finally the processed video frames to the RTC SDK for encoding transmission.
 * @param src_frame RTC SDK captured video frames, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @return  After video preprocessing video frames, returned to the RTC SDK for encoding and transmission, reference: ByteRTCVideoFrame{@link #ByteRTCVideoFrame}
 * @notes  If you need to cancel the video preprocessing, you can set the video preprocessor to nullptr.
 */
- (ByteRTCVideoFrame* _Nullable) processVideoFrame:(ByteRTCVideoFrame* _Nonnull)src_frame;

@end
/** 
 * @type keytype
 * @region  video management
 * @brief  Screen capture setting parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureParam : NSObject
/** 
 * @brief Screen capture width
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief Screen capture height
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief Screen capture frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief Screen capture bitrate rate in kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
/** 
 * @brief Screen capture area.
 */
@property(nonatomic, assign) CGRect regionRect;
/** 
 * @brief Whether to capture the mouse
 */
@property(nonatomic, assign) ByteRTCMouseCursorCaptureState mouseCursorCaptureState;
/** 
 * @brief The list of excluded windows.
 */
@property (strong, nonatomic) NSArray<NSNumber *> * _Nullable excludedWindowList;
/** 
 * @brief The border highlighting settings of the acquisition area. See ByteRTCHighlightConfig{@link #ByteRTCHighlightConfig}.
 */
@property (strong, nonatomic) ByteRTCHighlightConfig * _Nonnull highlightConfig;
@end
/** 
 * @type keytype
 * @author liyi.000
 * @brief Screen capture object information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenCaptureSourceInfo : NSObject
/** 
 * @brief The type of the sharing screen. See ByteRTCScreenCaptureSourceType{@link #ByteRTCScreenCaptureSourceType}.
 */
@property (assign, nonatomic) ByteRTCScreenCaptureSourceType sourceType;
/** 
 * @brief ID of the sharing object
 */
@property (assign, nonatomic) intptr_t sourceId;
/** 
 * @brief Name of the sharing screen
 */
@property (copy, nonatomic) NSString * _Nullable sourceName;
@end

/** 
 * @type keytype
 * @region  video management
 * @brief  Screen capture setting parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCScreenParam : NSObject
/** 
 * @brief Encoded frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief Encoding rate, when less than 0, the SDK will be based on the high and wide self-adaptation rate, in kbps
 */
@property(nonatomic, assign) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief Virtual background object
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVirtualBackgroundSource: NSObject
/** 
 * @brief See ByteRTCVirtualBackgroundSourceType{@link #ByteRTCVirtualBackgroundSourceType} 。
 */
@property(nonatomic, assign) ByteRTCVirtualBackgroundSourceType sourceType;
/** 
 * @brief The color of the solid color background. <br>
 *        The format is 0xAARRGGBB. <br>
 */
@property int sourceColor;
/** 
 * @brief The absolute path of the custom picture.
 * @notes   <br>
 *        + Supports formats of jpg, jpeg, and png. <br>
 *        + If the resolution exceeds 1080P, the picture will be scaled proportionally. When the resolutions of the background picture and the video are inconsistent, the picture will be cropped and scaled.  <br>
 *        + If you use a png image uploaded in the project as the background，but have png compression enabled, you need to change the file type of the required png image to "Data" in the file view on the right side of xcode, to prevent this png file from being compressed, otherwise it will cause the image decoding to fail.
 */
@property(nonatomic) NSString* _Nullable sourcePath;
@end

/** 
 * @type callback
 * @region Video Data Callback
 * @brief Local video frame observer
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCLocalEncodedVideoFrameObserver<NSObject>
 @optional
/** 
 * @type callback
 * @region Video Data Callback
 * @brief After calling registerLocalEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerLocalEncodedVideoFrameObserver:}, SDK will trigger this callback when it receives local video frames.
 * @param streamIndex Type of the local video frame. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}.
 * @param frame Information about the local video frame. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}.
 */
- (void)onLocalEncodedVideoFrame:(ByteRTCStreamIndex) streamIndex
    Frame:(ByteRTCEncodedVideoFrame * _Null_unspecified)frame;
@end

#pragma mark - ByteRTCEngineExternalVideoEncoderEventHandler

/** 
 * @type callback
 * @brief  Custom coded frame callback class
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCExternalVideoEncoderEventHandler<NSObject>
@required
/** 
 * @type callback
 * @region Video management
 * @author wangzhanqiang
 * @brief Prompt custom encoded frames to start pushing callbacks.   <br>
 *         After receiving this callback, you can call pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:{@link #ByteRTCEngineKit#pushExternalEncodedVideoFrame:withVideoIndex:withEncodedVideoFrame:} Push custom encoded video frames to the SDK
 * @param streamIndex  Properties of the encoded stream that can be pushed. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStart:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region Video management
 * @author wangzhanqiang
 * @brief When receiving the callback, you need to stop pushing custom encoded video frames to the SDK
 * @param streamIndex The properties of the encoded stream that need to stop pushing. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 */
- (void)onStop:(ByteRTCStreamIndex)streamIndex;
@required
/** 
 * @type callback
 * @region Video management
 * @author wangzhanqiang
 * @brief When the frame rate or bit rate of a custom encoded stream changes, the callback is triggered
 * @param streamIndex The properties of the changed encoded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex Corresponding to the subscript of the encoded stream
 * @param fps Changed frame rate, unit: fps
 * @param bitRateKps Changed bit rate, unit: kbps
 */
- (void)onRateUpdate:(ByteRTCStreamIndex)streamIndex
      withVideoIndex:(NSInteger)videoIndex
             withFps:(NSInteger)fps
         withBitRate:(NSInteger)bitRateKps;
@required
/** 
 * @type callback
 * @region Video management
 * @author wangzhanqiang
 * @brief This callback is used to inform the stream publisher that a keyframe needs to be regenerated.
 * @param streamIndex Properties of the remote encoded stream. See ByteRTCStreamIndex{@link #ByteRTCStreamIndex}
 * @param videoIndex The subscript of the corresponding encoded stream
 */
- (void)onRequestKeyFrame:(ByteRTCStreamIndex)streamIndex
           withVideoIndex:(NSInteger)videoIndex;
@end

#pragma mark - ByteRTCEngineRemoteEncodedVideoFrameObserver

/** 
 * @type callback
 * @region  video management
 * @brief  Remote encoded video data monitor
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCRemoteEncodedVideoFrameObserver<NSObject>
@required
/** 
 * @type callback
 * @region Video data callback
 * @author wangzhanqiang
 * @brief Call registerRemoteEncodedVideoFrameObserver:{@link #ByteRTCEngineKit#registerRemoteEncodedVideoFrameObserver:} After the SDK detects the remote encoded video data, the callback is triggered
 * @param streamKey Received remote stream information. See ByteRTCRemoteStreamKey{@link #ByteRTCRemoteStreamKey}
 * @param videoFrame Received remote video frame information. See ByteRTCEncodedVideoFrame{@link #ByteRTCEncodedVideoFrame}
 */
- (void)onRemoteEncodedVideoFrame:(ByteRTCRemoteStreamKey * _Nonnull)streamKey
                   withEncodedVideoFrame:(ByteRTCEncodedVideoFrame* _Nonnull)videoFrame;
@end

/** 
 * @type keytype
 * @brief  Video frame basic information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoFrameInfo : NSObject
/** 
 * @brief Width of video frame (pixels)
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief Height of video frame (pixels)
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief Video frame clockwise rotation angle. See ByteRTCVideoRotation{@link #ByteRTCVideoRotation}.
 */
@property(nonatomic, assign) ByteRTCVideoRotation rotation;
@end

#pragma mark - LiveTranscodingDelegate

/** 
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK.   <br>
 */
@protocol LiveTranscodingDelegate <NSObject>
/** 
 * @type callback
 * @region Push to CDN
 * @brief Whether your App has the ability to push streams to CDN:   <br>
 *        + True: Yes  <br>
 *        + False: No (default value)
 * @notes  <br>
 *          + If you need to use the function of intelligently pushing streams to CDN, you should ensure that your App contains librtmp and has the ability to push streams out. If so, set the callback to True.
 */
 - (BOOL)isSupportClientPushStream;
/** 
 * @type callback
 * @region Push to CDN
 * @brief Used for reporting events during pushing streams to CDN
 * @param event Stream mixing and pushing status, see ByteRTCStreamMixingEvent{@link #ByteRTCStreamMixingEvent}.
 * @param taskId Task ID.
 * @param Code Errors occuring during the pushing process. See ByteRtcTranscoderErrorCode{@link #ByteRtcTranscoderErrorCode} and ByteRTCTranscodingError{@link #ByteRTCTranscodingError}.
 * @param mixType Stream mixing and pushing type. See ByteRTCStreamMixingType{@link #ByteRTCStreamMixingType}.
 */
 - (void)onStreamMixingEvent:(ByteRTCStreamMixingEvent)event
                  taskId:(NSString *_Nonnull)taskId
                      error:(ByteRtcTranscoderErrorCode)Code
                    mixType:(ByteRTCStreamMixingType)mixType;

@optional
/** 
 * @type callback
 * @region Push to CDN
 * @brief Callback with audio data in PCM after intelligent stream mixing.
 * @param audioFrame Audio data frame in PCM. See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @param taskId Task ID.
 * @notes You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10 milliseconds.
 */
- (void)onMixingAudioFrame:(ByteRTCAudioFrame *_Nonnull)audioFrame taskId:(NSString *_Nonnull)taskId;

/** 
 * @type callback
 * @region Push to CDN
 * @brief Callback with video data in YUV after intelligent stream mixing.
 * @param videoFrame Video data frame in YUV, see ByteRTCVideoFrame{@link #ByteRTCVideoFrame}.
 * @param taskId Task ID.
 * @notes The interval between callbacks is the same with that between video frames.
 */
- (void)onMixingVideoFrame:(ByteRTCVideoFrame *_Nonnull)videoFrame taskId:(NSString *_Nonnull)taskId;
/** 
 * @type callback
 * @region Push to CDN
 * @brief This callback carries SEI data
 * @param dataFrame SEI Data. See ByteRTCFrameExtendedData{@link #ByteRTCFrameExtendedData}
 * @param taskId Task ID.
 */
- (void)onMixingDataFrame:(ByteRTCFrameExtendedData *_Nonnull)dataFrame taskId:(NSString *_Nonnull)taskId;

@end

/** 
 * @type callback
 * @region Video Effect
 * @author wangjunlin.3182
 * @brief Face detection observer
 */
@protocol ByteRTCFaceDetectionObserver <NSObject>
/** 
 * @type callback
 * @region Video Effect
 * @author wangjunlin.3182
 * @brief Callback of the result of face detection with Effect SDK. <br>
 *        After calling registerFaceDetectionObserver:withInterval:{@link #ByteRTCEngineKit#registerFaceDetectionObserver:withInterval:} and using the Effect SDK integrated in the RTC SDK, you will receive this callback.
 * @param result Face detection result. See ByteRTCFaceDetectionResult{@link #ByteRTCFaceDetectionResult}.
*/
- (void)onFaceDetectionResult:(ByteRTCFaceDetectionResult * _Nonnull)result;
/** 
 * @hidden
 * @type callback
 * @region Video Effect
 * @author liqi.ritchie
 * @brief Callback of the result of face detection with Effect SDK. <br>
 *        After calling registerFaceDetectionObserver:withInterval:{@link #ByteRTCEngineKit#registerFaceDetectionObserver:withInterval:} and setVideoEffectExpressionDetect:{@link #ByteRTCEngineKit#setVideoEffectExpressionDetect:}, you will receive this callback.
 * @param result Expression detection result. See ExpressionDetectResult{@link #ExpressionDetectResult}.
*/
- (void)onExpressionDetectResult:(ByteRTCExpressionDetectResult * _Nonnull)result;
@end

#pragma mark - ByteRTCEngineMediaMetadataObserver

/** 
 * @hidden
 * @deprecated since 326.1, use sendSEIMessage instead
 * @type callback
 * @brief Configure and obtain additional data interfaces when using internal source video capture
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCMediaMetadataObserver <NSObject>
@required
/** 
 * @type callback
 * @region Video data callback
 * @author wangjunlin.3182
 * @brief When the SDK is ready to send a video frame, the interface will be called back to determine whether metadata
 * @param timestamp The timestamp of the metadata video frame to be added, in microseconds
 * @return The data to be sent cannot exceed the size 1024bytes
 * @notes   <br>
 *        + Returning null means that no metadata needs to be added <br>
 *        + Long-term logical processing cannot be done in the callback to avoid affecting the video card <br>
 */
- (NSData *_Nullable)videoFrameMediaMetaDataAtTime:(NSTimeInterval)timestamp;

@optional
/** 
 * @type callback
 * @region Video data callback
 * @author wangjunlin.3182
 * @brief When the video frame received by the SDK contains medatada, the interface will be called back
 * @param uid The user ID to which the current frame belongs
 * @param extendedData Metadata
 * @param timestamp The timestamp containing the metadata video frame is in microseconds
 * @notes Long-term logical processing cannot be done in the callback to avoid affecting the video card
 */
- (void)receiveVideoFrameFromUID:(NSString * _Nonnull)uid
    withExtendedData:(NSData* _Nullable)extendedData atTimestamp:(NSTimeInterval)timestamp;
@end
/** 
 * @type keytype
 * @brief  Video parameters
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoEncoderConfig: NSObject
/** 
 * @brief Width of the video frame in px
 */
@property(nonatomic, assign) NSInteger width;
/** 
 * @brief Height of the video frame in px
 */
@property(nonatomic, assign) NSInteger height;
/** 
 * @brief Video frame rate in fps
 */
@property(nonatomic, assign) NSInteger frameRate;
/** 
 * @brief Maximum bit rate in kbps. Optional for internal capturing while mandatory for custom capturing.  <br>
 *        The default value is -1 in internal capturing mode, SDK will automatically calculate the applicable bit rate based on the input resolution and frame rate.  <br>
 *        No stream will be encoded and published if you set this parameter to 0.
 */
@property(nonatomic, assign) NSInteger maxBitrate;
/** 
 * @brief Video frame scale mode. The mode of how the video adapts the view, see ByteRTCVideoStreamScaleMode {@link #ByteRTCVideoStreamScaleMode}
 */
@property(nonatomic, assign) ByteRTCVideoStreamScaleMode scaleMode;
/** 
 * @brief Video encoding policy preference, see ByteRTCVideoEncoderPreference{@link #ByteRTCVideoEncoderPreference}
 */
@property(nonatomic, assign) ByteRTCVideoEncoderPreference encoderPreference;
@end
/** 
 * @type keytype
 * @brief Information on remote video frame
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRemoteVideoConfig : NSObject
/** 
 * @brief Expected maximum frame rate of the subscribed stream in px. The default value is 0, values greater than 10 are valid.  <br>
 *        If the frame rate of the stream published is lower than the value you set, or if your subscribed stream falls back under limited network conditions, the frame rate you set will drop accordingly.  <br>
 *        Only valid if the stream is coded with SVC technique.
 */
@property (nonatomic, assign) int framerate;
/** 
 * @brief Width of the video frame in px
 */
@property(nonatomic, assign) int  width;
/** 
 * @brief Height of the video frame in px
 */
@property(nonatomic, assign) int   height;
@end
/** 
 * @type keytype
 * @author shenpengliang
 * @brief  Room configuration
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRoomConfig : NSObject
/** 
 * @brief Room profile. See ByteRTCRoomProfile{@link #ByteRTCRoomProfile}. The default is `ByteRTCRoomProfileCommunication`. The setting cannot be changed after joining the room.
 */
@property(nonatomic) ByteRTCRoomProfile profile;
/** 
* @brief Whether to publish media streams automatically. The default is automatic publishing.  <br>
*        If you call setUserVisibility:{@link #ByteRTCEngineKit#setUserVisibility:} to set your own visibility to false, you will not publish media streams regardless of the value of `isAutoPublish`.
*/
@property(assign, nonatomic) BOOL isAutoPublish;
/** 
 * @brief Whether to automatically subscribe to the audio stream. The default is automatic subscription.
 */
@property(assign, nonatomic) BOOL isAutoSubscribeAudio;
/** 
  * @brief Whether to automatically subscribe to the main video stream. The default is automatic subscription.   <br>
  *        Screen streams are always automatically subscribed and are not affected by this parameter.
  */
@property(assign, nonatomic) BOOL isAutoSubscribeVideo;
/** 
 * @brief Expected configuration of remote video stream, see ByteRTCRemoteVideoConfig{@link #ByteRTCRemoteVideoConfig}.
 */
@property(nonatomic, strong) ByteRTCRemoteVideoConfig * _Nonnull remoteVideoConfig;
@end
/** 
 * @type keytype
 * @brief Crop configuration of the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSourceCropInfo : NSObject
/** 
 * @brief The normalized scale of the upper-left corner of the cropped video frame relative to the overall frame before cropping, in the range [0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationX;
/** 
 * @brief The normalized scale of the upper-left corner of the cropped video frame relative to the overall frame before cropping, in the range [0.0, 1.0)
 */
@property(assign, nonatomic) CGFloat LocationY;
/** 
 * @brief The normalized ratio of the width of the video frame obtained after cropping to the overall frame before cropping, in the range (0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat WidthProportion;
/** 
 * @brief The normalized ratio of the height of the obtained video frame after cropping to the overall frame before cropping, in the range (0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat HeightProportion;
@end
/** 
 * @type keytype
 * @brief Layout of each stream to be mixed into the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamRegion : NSObject
/** 
 * @brief User ID
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/** 
 * @brief Room ID
 */
@property(copy, nonatomic) NSString * _Nonnull roomId;
/** 
 * @brief Address of the background picture
 */
@property(copy, nonatomic) NSString * _Nonnull alternateImage;
/** 
 * @brief Offset of the user video layout relative to the left side of the canvas, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat x;
/** 
 * @brief Offset of the user video layout relative to the top of the canvas, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat y;
/** 
 * @brief The ratio of the user video width relative to the user's original video width, relative value. Range [0.0 - 1.0]
 */
@property(assign, nonatomic) CGFloat width;
/** 
 * @brief The ratio of the user video height relative to the user's original video height, relative value. Range [0.0 - 1.0].
 */
@property(assign, nonatomic) CGFloat height;
/** 
 * @brief The level of the user video layout in the canvas, 0 is the bottom level, the larger the value the higher the level. Range [0 - 100]
 */
@property(assign, nonatomic) NSInteger zOrder;
/** 
 * @brief Transparency, the range is [0.0, 1.0]
 */
@property(assign, nonatomic) CGFloat alpha;
/** 
 * @brief Push stream content control. Default value is 0.<br>
 *      0: The output mix contains audio and video<br>
 *      1: Audio only<br>
 *      2: Video only
 */
@property(assign, nonatomic) NSInteger mediaType;
/** 
 * @brief Media type of pushes stream<br>
 *        0：Media stream captured by camera/microphone<br>
 *        1: Screen sharing media stream
 */
@property(assign, nonatomic) NSInteger streamType;
/** 
 * @brief Video rendering mode
 */
@property(assign, nonatomic) ByteRTCRenderMode renderMode;
/** 
 * @brief Video cropping information
 */
@property(strong, nonatomic) ByteRTCSourceCropInfo * _Nonnull sourceCrop;
@end

/** 
 * @type keytype
 * @brief Layout of streams mixed in the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamLayout : NSObject
/** 
 * @brief Layout mode, currently only user-defined mode is supported, the value is 2
 */
@property(assign, nonatomic) NSInteger layoutMode;
/** 
 * @brief interpolation mode. 0: insert the previous frame. !0: other insert a blank frame.
 */
@property(assign, nonatomic) NSInteger interpolationMode;
/** 
 * @brief Background color
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundColor;
/** 
 * @brief Address of the background picture
 */
@property(copy, nonatomic) NSString *_Nonnull backgroundImage;
/** 
 * @brief User layout information list
 */
@property(copy, nonatomic) NSArray<ByteRTCPublicStreamRegion *> * _Nonnull regions;
@end

/** 
 * @type keytype
 * @brief Properties of the public video stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamVideoConfig : NSObject
/** 
 * @brief Width in px
 */
@property(assign, nonatomic) NSInteger width;
/** 
 * @brief Height in px
 */
@property(assign, nonatomic) NSInteger height;
/** 
 * @brief Frame rate in fps
 */
@property(assign, nonatomic) NSInteger fps;
/** 
 * @brief Bit rate in kbps
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief Configuration of the public audio stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreamAudioConfig : NSObject
/** 
 * @brief Audio sample rate: 16k, 32k, 44.1k, 48k
 */
@property(assign, nonatomic) NSInteger sampleRate;
/** 
 * @brief Number of sound channel
 */
@property(assign, nonatomic) NSInteger channels;
/** 
 * @brief Audio bitrate in kbps: 16kbsp, 32kbps, 64kbps
 */
@property(assign, nonatomic) NSInteger bitrate;
@end

/** 
 * @type keytype
 * @brief  Watermark's scaled coordinates and size, relative to the video stream.
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoByteWatermark: NSObject
/** 
 * @brief The watermark's horizontal offset from the upper left corner of the video stream to the video stream's width in range of [0,1).
 */
@property(assign, nonatomic) float x;
/** 
 * @brief The watermark's vertical offset from the upper left corner of the video stream to the video stream's height in range of [0,1).
 */
@property(assign, nonatomic) float y;
/** 
 * @brief The watermark's width to the video stream's width in range of [0,1).
 */
@property(assign, nonatomic) float width;
/** 
 * @brief The watermark height to the video stream's height in range of [0,1).
 */
@property(assign, nonatomic) float height;
@end

/** 
 * @type keytype
 * @brief  Watermark configurations
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoWatermarkConfig: NSObject
/** 
 * @brief Whether the watermark is visible in preview. Its default value is `true`.
 */
@property(nonatomic, assign) BOOL visibleInPreview;
/** 
 * @brief Watermark's coordinates and size in landscape mode. See ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}.
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInLandscapeMode;
/** 
 * @brief Watermark's coordinates and size in portrait mode. See ByteRTCVideoByteWatermark{@link #ByteRTCVideoByteWatermark}.
 */
@property(strong, nonatomic) ByteRTCVideoByteWatermark * _Nonnull positionInPortraitMode;
@end

/** 
 * @type keytype
 * @brief Properties of the public stream
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCPublicStreaming : NSObject
/** 
 * @brief Layout mode of the public stream. Refer to ByteRTCPublicStreamLayout{@link #ByteRTCPublicStreamLayout} for more details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamLayout * _Nonnull layout;
/** 
 * @brief Properties of the public video stream. Refer to ByteRTCPublicStreamVideoConfig{@link #ByteRTCPublicStreamVideoConfig} for more details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamVideoConfig * _Nonnull video;
/** 
 * @brief Properties of the public audio stream. Refer to ByteRTCPublicStreamAudioConfig{@link #ByteRTCPublicStreamAudioConfig} for more details.
 */
@property(strong, nonatomic) ByteRTCPublicStreamAudioConfig * _Nonnull audio;
/** 
 * @brief room ID of the public streamer
 */
@property(copy, nonatomic) NSString * _Nullable roomId;
/** 
 * @brief Get the default public stream mixing configuration
 */
+ (instancetype _Nonnull)defaultPublicStreaming;
@end
/** 
 * @type api
 * @hidden(iOS)
 * @region Video Device Management
 * @brief Mainly used to enumerate and set up video capture devices
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCVideoDeviceManager : NSObject
/** 
 * @type api
 * @hidden(iOS)
 * @region  Video Device Management
 * @author zhangzhenyu.samuel
 * @brief  Get the list of video capture devices.
 * @return ByteRTCDeviceCollection{@link #ByteRTCDeviceCollection}
 */
- (ByteRTCDeviceCollection * _Nonnull)enumerateVideoCaptureDevices;
/** 
 * @type api
 * @hidden(iOS)
 * @region Video Device Management
 * @author zhangzhenyu.samuel
 * @brief Get the currently-using video capture device
 * @param  deviceID video device ID
 * @return   <br>
 *         + 0: Success. <br>
 *         +! 0: failure <br>
 */
- (int)getVideoCaptureDevice:(NSString * _Nonnull * _Nonnull) deviceID;
/** 
 * @type api
 * @hidden(iOS)
 * @region  Video Device Management
 * @author zhangzhenyu.samuel
 * @brief  Set the current video capture device
 * @param  deviceID Video device ID. Get all video devices by calling  which can be obtained through enumerateVideoCaptureDevices{@link #ByteRTCVideoDeviceManager#enumerateVideoCaptureDevices}
 * @return   <br>
 *         + 0: Success. <br>
 *         +! 0: failure <br>
 */
- (int)setVideoCaptureDevice:(NSString* _Nonnull)deviceID;
@end
