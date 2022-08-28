
/*
 * Copyright 2021 @bytedance
 *  Created on: june 20, 2021
 */

#pragma once

#include "bytertc_defines.h"
#include "bytertc_transcoder_define.h"

namespace bytertc {

/**  
 * @type callback
 * @region Push to CDN
 * @brief Register this observer to receive stream mixing related callbacks from the SDK. 
 */
class ITranscoderObserver {
public:
    /**
     * @hidden
     */
    virtual bool isSupportClientPushStream() {
        return false;
    }
    /**  
     * @type callback
     * @region Push to CDN
     * @brief Used for reporting events during pushing streams to CDN
     * @param [in] event Type Stream mixing status, see StreamMixingEvent{@link #StreamMixingEvent}
     * @param [in] task_id Task ID
     * @param [in] error Errors occuring during the pushing process. See TransCodingError{@link #TransCodingError}
     * @param [in] mix_type Stream mixing and pushing type. See StreamMixingType{@link #StreamMixingType}
     */
    virtual void onStreamMixingEvent(
            StreamMixingEvent event, const char* task_id, StreamMixingErrorCode error, StreamMixingType mix_type) = 0;

    /**  
     * @type callback
     * @region Push to CDN
     * @brief Callback with the video data after stream mixing, running on the video callback thread
     * @param [in] task_id Task ID
     * @param [in] video_frame Video Frame, see IVideoFrame{@link #IVideoFrame}.
     * @notes The interval between callbacks is the same with that between video frames.
     */
    virtual void onStreamMixingVideoFrame(const char* task_id, IVideoFrame* video_frame) = 0;

    /**  
     * @type callback
     * @region Push to CDN
     * @brief Callback with the audio data after stream mixing, running on the audio callback thread
     * @param [in] task_id Task ID.
     * @param [in] audio_frame Audio Frame, see IAudioFrame{@link #IAudioFrame}.
     * @notes You will receive the callback every 10 milliseconds. Each callback carries data collected in the last 10 milliseconds.
     */
    virtual void onStreamMixingAudioFrame(const char* task_id, IAudioFrame* audio_frame) = 0;

    /**  
     * @type callback
     * @region Push to CDN
     * @brief This callback carries SEI data, running on the video callback thread
     * @param [in] task_id Task ID
     * @param [in] data_frame SEI data
     */
    virtual void onStreamMixingDataFrame(const char* task_id, IDataFrame* data_frame) = 0;

    /**  
     * @hidden
     * @brief Destructor
     */
    virtual ~ITranscoderObserver() = default;
};

/**  
 * @hidden
 * @type api
 * @brief Create an instance with stream mixing configurations
 */
BYTERTC_API ITranscoderParam* createTranscoderParam();

} /* namespace bytertc */
