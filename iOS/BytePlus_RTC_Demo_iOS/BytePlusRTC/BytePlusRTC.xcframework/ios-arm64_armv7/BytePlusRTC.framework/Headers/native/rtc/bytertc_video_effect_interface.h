/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Video Effect Interface
*/

#pragma once

#ifndef BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
#define BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__

#include <stdint.h>
#include "bytertc_defines.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief Virtual background type.
 */
enum VirtualBackgroundSourceType {
    /** 
     * @brief Replace the original video background with the background of a solid color.
     */
    kVirtualBackgroundSourceColor = 0,
    /** 
     * @brief Replace the original video background with the custom picture.
     */
    kVirtualBackgroundSourceImage = 1,
};

/**  
 * @hidden
 * @type keytype
 * @brief  Expression detection configuration
 */
struct VideoEffectExpressionDetectConfig {
  /** 
   * @brief Whether to enable age detection.
   */
  bool detect_age = false;
  /** 
   * @brief Whether to enable gender detection.
   */
  bool detect_gender = false;
  /** 
   * @brief Whether to enable emotion detection.
   */
  bool detect_emotion = false;
  /** 
   * @brief Whether to enable attractiveness detection.
   */
  bool detect_attractiveness = false;
  /** 
   * @brief Whether to enable happiness detection.
   */
  bool detect_happiness = false;
};

/** 
 * @type keytype
 * @brief Virtual background object.
 */
struct VirtualBackgroundSource{
    /** 
     * @brief See VirtualBackgroundSourceType{@link #VirtualBackgroundSourceType}.
     */
    VirtualBackgroundSourceType source_type;
    /** 
     * @brief The color of the solid color background. <br>
     *        The format is 0xAARRGGBB. <br>
     */
    uint32_t source_color = 0xFFFFFFFF;
    /** 
     * @brief The absolute path of the custom picture.
     * @notes   <br>
     *        + Supports formats of jpg, jpeg, and png. <br>
     *        + If the resolution exceeds 1080P, the picture will be scaled proportionally. When the resolutions of the background picture and the video are inconsistent, the picture will be cropped and scaled.
     */
    const char* source_path = nullptr;
};
/** 
 * @type keytype
 * @brief Face Detection Result
 */
struct FaceDetectResult {
    /**
     * @hidden
     */
    static const int max_face_num = 10;
    /** 
     * @brief Face Detection Result <br>
     *        + 0: Success <br>
     *        + !0: Failure  
     */
    int detect_result = 0;
    /** 
     * @brief Number of the detected face
     */
    int face_count = 0;
    /** 
     * @brief The face recognition rectangles. The length of the array is the same as the number of detected faces. See Rectangle{@link #Rectangle}.
     */  
    Rectangle rect[max_face_num];
    /** 
     * @brief Width of the original image (px)
     */   
    int image_width = 0;
    /** 
     * @brief Height of the original image (px)
     */   
    int image_height = 0;
};

/**  
 * @hidden
 * @type keytype
 * @brief  Expression detect information
 */
struct ExpressionDetectInfo {
   /** 
    * @brief The estimated age in range of (0, 100).
    */
    float age = 0;
    /** 
    * @brief The estimated probability of being a male in range of (0.0, 1.0).
    */
    float boy_prob = 0;
    /** 
    * @brief The estimated attractiveness in range of (0, 100).
    */
    float attractive = 0;
    /** 
    * @brief The estimated happy score in range of (0, 100).
    */
    float happy_score = 0;
    /** 
    * @brief The estimated sad score in range of (0, 100).
    */
    float sad_score = 0;
    /** 
    * @brief The estimated angry score in range of (0, 100).
    */
    float angry_score = 0;
    /** 
    * @brief The estimated surprise score in range of (0, 100).
    */
    float surprise_score = 0;
    /** 
    * @brief The estimated emotional arousal in range of (0, 100).
    */
    float arousal = 0;
    /** 
    * @brief The estimated emotional valence in range of (-100, 100).
    */
    float valence = 0;
};

/** 
 * @hidden
 * @type keytype
 * @brief Expression detection result
 */
struct ExpressionDetectResult {
    /** 
     * @hidden
     */
    static const int max_face_num = 10;
   /** 
    * @brief Expression detection result <br>
    *        + 0: Success <br>
    *        + !0: Failure <br>
    */
    int detect_result = 0;
   /** 
    * @brief The number of detected faces.
    */
    int face_count = 0;
   /** 
    * @brief Expression detection information. The length of the array is the same as the number of detected faces. See ExpressionDetectInfo{@link #ExpressionDetectInfo}.
    */
    ExpressionDetectInfo detect_info[max_face_num];
};

/** 
 * @type callback
 * @region Video Effect
 * @brief Face detection observer
 */
class IFaceDetectionObserver {
public:
    /** 
     * @type callback
     * @region Video Effect
     * @brief Callback of the result of face detection with Effect SDK. <br>
     *        After calling registerFaceDetectionObserver{@link #IVideoEffect#registerFaceDetectionObserver} and using the Effect SDK integrated in the RTC SDK, you will receive this callback.
     * @param [in] result Face detection result. See FaceDetectResult{@link #FaceDetectResult}.
    */
    virtual void onFaceDetectResult(const FaceDetectResult& result) = 0;
    /** 
     * @hidden
     * @type callback
     * @region Video Effect
     * @brief Callback of the result of face detection with Effect SDK. <br>
     *        After calling registerFaceDetectionObserver{@link #IVideoEffect#registerFaceDetectionObserver} and setVideoEffectExpressionDetect{@link #IVideoEffect#setVideoEffectExpressionDetect}, you will receive this callback. 
     * @param [in] result Expression detection result. See ExpressionDetectResult{@link #ExpressionDetectResult}.
    */
    virtual void onExpressionDetectResult(const ExpressionDetectResult& result) = 0;
    
};

/** 
 * @type api
 * @brief  Video effects interface
 */
class IVideoEffect {
public:
    /** 
     * @hidden
     * @type api
     * @region Video Effects
     * @brief  Sets the video effects resource finder path and initializes video effects.
     * @param [in] finder ResourceFinder path
     * @param [in] deleter ResourceDeleter path
     * @return  <br>
     *      + 0: Success <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.   <br> <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int setAlgoModelResourceFinder(uintptr_t finder, uintptr_t deleter) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief  Video effects license check
     * @param androidContext   <br>
     *        Android Context object pointer (jobject type). The nullptr
     * @param jnienv Android <br>
     *        JNIEnv pointer is passed to platforms other than Android. Incoming nullptr
     * @param licensePath  Absolute path of license file from platforms other than Android
     * @return   <br>
     *       + 0: call succeeded <br>
     *       + 1000: not integrated cvsdk <br>
     *       + 1001: cv function is not supported in this RTC version <br>
     *       + < 0: Failure Please refer to [error codes](https://www.volcengine.com/docs/5889/61813).
     * @notes  Before you start using video effects, you must first call this method for license verification
     */
    virtual int checkLicense(void* androidContext, void* jnienv, const char* licensePath) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @hidden (iOS, Android)
     * @brief Get authorization messages from the Effect SDK to obtain online licenses.
     * @param  [in] ppmsg Authorization message string address
     * @param  [in] len Authorization message string length
     * @return   <br>
     *       + 0: call succeeded <br>
     *      + 1000: The Effect SDK is not integrated. <br>
     *       + 1001: CV function is not supported in this RTC version <br>
     *       + < 0: Failure. For specific error codes, please refer to the [error codes](https://www.volcengine.com/docs/5889/61813).
     * @notes  <br>
     *         + You must obtain an online license for the Effect SDK before using the CV functions. <br>
     *          After obtaining authorization messages through this interface, you must refer to [Online Authorization Instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99798/). <br>
     *           Implement the business logic of obtaining online licenses by yourself. After obtaining the license, you must call checkLicense{@link #checkLicense} to confirm that the license is valid. Then you can use the CV function. <br>
     *         + After obtaining the authorization message, call freeAuthMessage{@link #freeAuthMessage} to free memory.
     */
    virtual int getAuthMessage(char ** ppmsg, int * len) = 0;
    /** 
     * @type api
     * @region Video Effects
     * @hidden  (iOS, Android)
     * @brief After using the authorization message string, free the memory.
     * @param  [in] pmsg The authorization message string returned by getAuthMessage.
     * @return   <br>
     *       + 0: Call succeeded <br>
     *      + 1000: The Effect SDK is not integrated. <br>
     *      + 1001: This API is not available for your Effect SDK.  <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int freeAuthMessage(char * pmsg) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief  Turn on and off video effects
     * @param [in] enabled  Whether to turn on effects, true: on, false: off
     * @return   <br>
     *      + 0: Succeed <br>
     *      + 1000: Effect SDK is not integrated  <br>
     *      + 1001: CV functionality is not supported in the current RTC version  <br>
     *      + <0: Other errors, see [error codes](https://www.volcengine.com/docs/5889/61813)
     * @notes  Call CheckLicense{@link #checkLicense} and setAlgoModelPath {@link Call this method after #setAlgoModelPath}
     */
    virtual int enableEffect(bool enabled) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief  Set the video effects algorithm model path
     * @param [in] modelPath  Model path
     */
    virtual void setAlgoModelPath(const char* modelPath) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region Video Effects
     * @brief  Sets the configuration for video effects expression detection.
     * @param [in] expressionDetectConfig Expression detection configuration. See VideoEffectExpressionDetectConfig{@link #VideoEffectExpressionDetectConfig}.
     * @return  <br>
     *      + 0: Success <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.   <br> <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int setVideoEffectExpressionDetect(const VideoEffectExpressionDetectConfig& expressionDetectConfig) = 0;
    
    /** 
     * @type api
     * @region Video Effects
     * @brief Set video effects material package.
     * @param [in] effectNodePaths Array of effect material package paths. <br>
     *        To remove the current video effect, set it to null.
     * @param  [in] nodeNum <br>
     *         Number of special effects material packages
     * @return   <br>
     *       + 0: call success <br>
     *       + 1000: The Effect SDK is not integrated. <br>
     *       + 1001: This API is not available for your Effect SDK.   <br> <br>
     *       + < 0: Failure. For specific error codes, please refer to the [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int setEffectNodes(const char** effectNodePaths, int nodeNum) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region Video Effects
     * @brief  Appends video effects material package.
     * @param [in] effectNodePaths Array of effect material package paths. 
     * @param [in] nodeNum  Number of special effects material packages.
     * @return  <br>
     *      + 0: Success <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.   <br> <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     * @notes  This API adds new video effect to the video effect you set with setEffectNodes{@link #IVideoEffect#setEffectNodes}.
     */
    virtual int appendEffectNodes(const char** effectNodePaths, int nodeNum) = 0;
    
    /** 
     * @hidden
     * @type api
     * @region Video Effects
     * @brief  Removes the designated video effects material package.
     * @param [in] effectNodePaths Array of effect material package paths. 
     * @param [in] nodeNum  Number of special effects material packages.
     * @return  <br>
     *      + 0: Success <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.   <br> <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     * @notes Removes the designated video effects in setEffectNodes{@link #IVideoEffect#setEffectNodes} or appendEffectNodes{@link #IVideoEffect#appendEffectNodes}.
     */
    virtual int removeEffectNodes(const char** effectNodePaths, int nodeNum) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief  Set the effect intensity
     * @param  [in] nodePath <br>
     *         Special effects material package path
     * @param  [in] nodeKey <br>
     *         The name of the material key to be set, please refer to [Material key correspondence instructions](http://ailab-cv-sdk.bytedance.com/docs/2036/99769/) for the value.
     * @param  [in] nodeValue <br>
     *         The intensity value that needs to be set, the value range [0,1], and the setting is invalid when it exceeds the range.
     * @return   <br>
     *       + 0: Call succeeded <br>
     *       + 1000: The Effect SDK is not integrated.  <br>
     *       + 1001: This API is not available for your Effect SDK.  <br>
     *       + < 0: Failure. For specific error codes, please refer to the [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int updateNode(const char* nodePath, const char* nodeKey, float nodeValue) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief Set the color filter
     * @param  [in] resPath <br>
     *        Filter effects package absolute path.
     * @return   <br>
     *       + 0: Call succeeded <br>
     *      + 1000: The Effect SDK is not integrated. <br>
     *      + 1001: This API is not available for your Effect SDK.  <br>
     *      + <0: Other errors. See [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int setColorFilter(const char* resPath) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief Set the intensity of the color filter enabled
     * @param  [in] intensity <br>
     *        Filter intensity. The value range [0,1] is set to be invalid when the range is exceeded.
     * @return   <br>
     *       + 0: Call succeeded <br>
     *      + 1000: The Effect SDK is not integrated.  <br>
     *      + 1001: This API is not available for your Effect SDK.  <br>
     *       + < 0: Failure. For specific error codes, please refer to the [error codes](https://www.volcengine.com/docs/5889/61813).
     */
    virtual int setColorFilterIntensity(float intensity) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief Initialize the virtual background function.
     * @param [in] androidContext Pointer of Android Context object (jobject type). For platforms other than Android, use nullptr.
     * @param [in] jnienv Pointer of Android JNIEnv. For platforms other than Android, use nullptr.
     * @param [in] licensePath Absolute path to CV license file
     * @param [in] modelPath Absolute path to model parameter file
     * @return   <br>
     *         + 0: Call succeeded. <br>
     *         + 1000: The Effect SDK is not integrated. <br>
     *         + 1001: This API is not available for your Effect SDK. <br>
     *         + > 40000: Failure. Effect SDK authorization error, please refer to [error codes](https://www.volcengine.com/docs/5889/61813) for specific error codes. <br>
     *         + < 0: Failure. Effect SDK internal error, specific error code please refer to [error codes](https://www.volcengine.com/docs/5889/61813). <br>
     */
    virtual int initVirtualBackground(void* androidContext, void* jnienv, const char* licensePath,const char* modelPath) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief Turn on the virtual background function.
     * @param  [in] source Virtual background object. See VirtualBackgroundSource{@link #VirtualBackgroundSource}.
     * @return   <br>
     *         + 0: Success. <br>
     *         + < 0: Failure. Effect SDK internal error. For specific error code, see [error codes](https://www.volcengine.com/docs/5889/61813). <br>
     *         + -1: Failure. Virtual background function not successfully initialized. See initVirtualBackground{@link #IVideoEffect#initVirtualBackground}. <br>
     *         + -4: Failure. Failed to open the custom background picture. <br>
     *         + -37: Failure. Failed to decode the custom background picture. <br>
     *         + -38: Failure. The format of the custom background picture not supported. Formats jpg, jpeg, and png are supported. <br>
     * @notes   <br>
     *        + Before calling this api, call initVirtualBackground{@link #IVideoEffect#initVirtualBackground}. <br>
     *        + The virtual background supports the video stream collected by the camera, including SDK default mechanism and custom mechanism. Screen video stream does not supported the virtual backgrounds function. <br>
     */
    virtual int enableVirtualBackground(const VirtualBackgroundSource& source) = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief Turn off the virtual background function.
     * @return   <br>
     *         + 0: success <br>
     *         + < 0: Failure. Please refer to [error codes](https://www.volcengine.com/docs/5889/61813) for specific error codes. <br>
     * @notes After calling enableVirtualBackground{@link #enableVirtualBackground} to enable the virtual background function, you can call this interface to turn it off.
     */
    virtual int disableVirtualBackground() = 0;

    /** 
     * @type api
     * @region Video Effects
     * @brief  Register the observer for the result of face detection. <br>
     *        With this observer, you will receive onFaceDetectResult{@link #IFaceDetectionObserver#onFaceDetectResult}} periodically. 
     * @param [in] observer See IFaceDetectionObserver{@link #IFaceDetectionObserver}.
     * @param [in] interval_ms Time interval in ms. The actual time interval of receiving callbacks is between `interval` and `interval + the time slot of a captured video frame`.
     * @return <br>
     *       + 0: Success <br>
     *       + <0: Failure <br>
     */
    virtual int registerFaceDetectionObserver(IFaceDetectionObserver * observer, int interval_ms) = 0;
};

}  // namespace bytertc

#endif // BYTE_RTC_VIDEO_EFFECT_INTERFACE_H__
