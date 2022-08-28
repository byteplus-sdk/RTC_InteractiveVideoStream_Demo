/*
 * Copyright 2020 @bytedance
 *
 *  Created on: Dec 16, 2021
 */
#pragma once

#include <stdint.h>

namespace bytertc {
/**  
 * @type keytype
 * @brief  Camera fill light status
 */
enum TorchState{

    /**  
     * @brief Camera fill light off
     */
    kTorchStateOff=0,
    /**  
     * @brief Camera fill light on
     */
    kTorchStateOn=1,
};

/**  
 * @hidden(macOS, Windows)
 * @type api
 * @region video management
 * @brief camera control interface
 * @notes must have been called StartVideoCapture{@link #IRtcEngine#StartVideoCapture} to use this interface when using the SDK internal capture module for video capture.
 */
class ICameraControl {
public:
    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region  video management
     * @brief  set the zoom factor of the currently used camera (front/postcondition)
     * @param zoom_val  zoom factor. The value range is [1, < Maximum Zoom Multiplier >]. <br>
     *                  The maximum zoom factor can be obtained by calling getCameraZoomMaxRatio{@link #getCameraZoomMaxRatio}.
     * @return   <br>
     *         + 0: Success. <br>
     *         + < 0: Failed.
     * @notes  <br>
     *         + You must have called StartVideoCapture {@link #IRtcEngine#StartVideoCapture} for video capture using the SDK internal capture module to set the camera zoom factor. <br>
     *         + The setting result fails after calling StopVideoCapture{@link #IRtcEngine#StopVideoCapture} to turn off internal collection.
     */
    virtual int setCameraZoomRatio(float zoom_val) = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region Video Management
     * @brief Get the maximum zoom multiple of the currently used camera (front/postcondition)
     * @return Maximum zoom multiple
     * @notes You must have called StartVideoCapture {@link #IRtcEngine#StartVideoCapture} When using the SDK internal capture module for video capture, the camera maximum zoom multiple can be detected.
     */
    virtual float getCameraZoomMaxRatio() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region Video Management
     * @brief Detect whether the currently used camera (front/postcondition) supports zoom (digital/optical zoom).
     * @return   <br>
     *         + true: Support <br>
     *         + false: Not supported
     * @notes  You must have called StartVideoCapture{@link #IRtcEngine#StartVideoCapture} for video capture using the SDK internal capture module to detect camera zoom capability.
     */
    virtual bool isCameraZoomSupported() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region  video management
     * @brief  detect the currently used camera (front/postcondition), whether flash is supported.
     * @return   <br>
     *         + true: Support <br>
     *         + false: Not supported
     * @notes  You must have called StartVideoCapture{@link #IRtcEngine#StartVideoCapture} for video capture using the SDK internal capture module to detect flash capability.
     */
    virtual bool isCameraTorchSupported() = 0;

    /**  
     * @hidden(macOS, Windows)
     * @type api
     * @region video management
     * @brief turn on/off the flash of the currently used camera (front/postcondition)
     * @param torch_state turn on/off. See TorchState{@link #TorchState}.
     * @return   <br>
     *         + 0: Success.
     *         + < 0: Failed.
     * @notes  <br>
     *         + You must have called StartVideoCapture{@link #IRtcEngine#StartVideoCapture} for video capture using the SDK internal capture module to set the flash. <br>
     *         + The setting result fails after calling StopVideoCapture{@link #IRtcEngine#StopVideoCapture} to turn off internal collection.
     */
    virtual int setCameraTorch(TorchState torch_state) = 0;

    virtual bool isCameraFocusPositionSupported() = 0;
    
    virtual int setCameraFocusPosition(float x, float y) = 0;
    
    virtual bool isCameraExposurePositionSupported() = 0;
    
    virtual int setCameraExposurePosition(float x, float y) = 0;
    
    virtual int setCameraExposureCompensation(float val) = 0;
};

}  // namespace bytertc
