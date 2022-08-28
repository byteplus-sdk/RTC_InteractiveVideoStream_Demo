/*
 * Copyright (c) 2021 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Video Processor Interface
*/

#pragma once

#include "bytertc_video_frame.h"

namespace bytertc {

/**  
 * @type api
 * @region  video processing
 */
class IVideoProcessor
{
public:
    /**
     * @hidden
     */
    virtual ~IVideoProcessor() = default;

   /**  
    * @type api
    * @region  video processing
    * @brief  Get RTC SDK acquired video frames obtained, according to the video pre-processor registerLocalVideoProcessor{@link #IRtcEngine#registerLocalVideoProcessor}} set, video pre-processing, the final processed video frames to the RTC SDK for encoding transmission.
    * @param  [in] src_frame Video frames captured by the RTC SDK. See IVideoFrame{@link #IVideoFrame}.
    * @return The video frame after video preprocessing is returned to the RTC SDK for encoding and transmission. See IVideoFrame{@link #IVideoFrame}.
    * @notes  <br>
    *        + Before video preprocessing, you need to call registerLocalVideoProcessor{@link #IRtcEngine#registerLocalVideoProcessor}} to set up the video preprocessor. <br>
    *        + If you need to cancel the video preprocessing, you can set the video preprocessor to nullptr.
    */
    virtual IVideoFrame* processVideoFrame(IVideoFrame* src_frame) = 0;
};

} // namespace bytertc
