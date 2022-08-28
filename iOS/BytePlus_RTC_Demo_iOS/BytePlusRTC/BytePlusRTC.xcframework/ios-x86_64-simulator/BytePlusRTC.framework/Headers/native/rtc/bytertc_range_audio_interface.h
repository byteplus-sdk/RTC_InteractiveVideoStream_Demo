/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief range audio interface
 */

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {
/** 
 * @type keytype
 * @brief The range where local user can hear audio with attenuation effect.
 */
struct ReceiveRange {
    /** 
     * @brief The minimum distance at which the local user can hear the attenuated audio from remote users.  <br>
     *        The value must be ≥ 0, but ≤ max.  <br>
     *        No attenuation effect for audio from distances less than this value you set.
     */
    int min;
    /** 
     * @brief The maximum distance at which the local user can hear audio from remote users.  <br>
     *        The value must be ≥ min, and > 0.  <br>
     *        Audio from distances larger than the value you set cannot be heard.
     */
    int max;
};

/** 
 * @type keytype
 * @brief Range audio stream information
 */
struct RangeAudioInfo {
    /** 
     * @brief ID of remote stream publisher
     */
    const char* user_id;
    /** 
     * @brief Attenuation coefficient of the remote user. The value range is [0,100].  <br>
     *        A value of 0 means that the remote user's audio volume is 0.
     */
    int factor = 0;
};

/** 
 * @type callback
 * @brief Range audio attenuation coefficient observer
 */
class IRangeAudioObserver {
public:
    /** 
     * @type callback
     * @region Range Audio
     * @brief Callback about the current attenuation coefficient of remote users.  <br>
     *        In manual subscription mode, when any user in the room calls updatePosition{@link #IRangeAudio#updatePosition} to update their position or updateReceiveRange{@link #IRangeAudio#updateReceiveRange} to update their audio receiving range, the relative distance between this user and other users in the room will change, and the attenuation coefficient calculated accordingly will change as well, which will be notified to users.  <br>
     *        You can determine whether to subscribe to a remote user's audio stream based on the attenuation coefficient of that user shown in this callback.
     * @param [in] range_audio_info Array containing audio stream information, see RangeAudioInfo{@link #RangeAudioInfo}.
     * @param [in] len Length of the array.
     * @notes You will not receive this callback immediately after updating your location or audio receiving range. SDK calculates the attenuation coefficient every 500 ms, and only trigger this callback if the result of the calculation is different from the previous one, or if the result is the same but more than 3 seconds after the last calculation.
     */
    virtual void onRangeAudioInfo(const RangeAudioInfo* range_audio_info, int len) {}
    /**
     * @hidden
     */
    virtual ~IRangeAudioObserver() {}
};

/** 
 * @type api
 * @brief Range audio instance
 */
class IRangeAudio {
public:
    /** 
     * @type api
     * @region Range Audio
     * @brief Enable/disable the range audio function.  <br>
     *        Range audio means that within a certain range in a same RTC room, the audio volume of the remote user received by the local user will be amplified/attenuated as the remote user moves closer/away. The audio coming from out of the range cannot be heard. See updateReceiveRange{@link #IRangeAudio#updateReceiveRange} to set audio receiving range.
     * @param [in] enable Whether to enable audio range funcion：  <br>
     *        + true: Enable  <br>
     *        + false: Disable（Defaulting setting）
     * @notes You can call this API anytime before or after entering a room. To ensure a smooth switch to the range audio mode after entering the room, you need to call updatePosition{@link #IRangeAudio#updatePosition} before this API to set your own position coordinates, and then enable the range audio function.
     */
    virtual void enableRangeAudio(bool enable) = 0;
    /** 
     * @type api
     * @region Range Audio
     * @brief Updates the audio receiving range for the local user.
     * @param [in] range Audio receiving range, see ReceiveRange{@link #ReceiveRange}.
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @notes If you have previously called registerRangeAudioObserver{@link #IRangeAudio#registerRangeAudioObserver} to set an observer monitoring attenuation coefficient, you will receive onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} when any user in the room calls this API to update the audio receiving range.
     */
    virtual int updateReceiveRange(const ReceiveRange &range) = 0;
    /** 
     * @type api
     * @region Range Audio
     * @brief Updates the coordinate of the local user's position in the rectangular coordinate system in the current room.
     * @param [in] pos 3D coordinate values, the default value is [0, 0, 0], see Position{@link #Position}.
     * @return API call result: <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @notes  <br>
     *        + After calling this API, you should call enableRangeAudio{@link #IRangeAudio#enableRangeAudio} to enable range audio function to actually enjoy the range audio effect.  <br>
     *        + If you have previously called registerRangeAudioObserver{@link #IRangeAudio#registerRangeAudioObserver} to set an observer monitoring attenuation coefficient, you will receive onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} when any user in the room calls this API to update their coordinates.
     */
    virtual int updatePosition(const Position &pos) = 0;
    /** 
     * @type api
     * @region Range Audio
     * @brief Sets the attenuation coefficient observer
     * @param observer Attenuation coefficient observer.
     *        After you call this API, SDK will trigger onRangeAudioInfo{@link #IRangeAudioObserver#onRangeAudioInfo} when it detects that a user in the room updates their location coordinates or audio receiving. See IRangeAudioObserver{@link #IRangeAudioObserver}.
     * @notes You should only call this API in manual subscription mode.
     */
    virtual void registerRangeAudioObserver(IRangeAudioObserver* observer) = 0;
    /**
     * @hidden
     */
    virtual ~IRangeAudio() {}
};
}  // namespace bytertc
