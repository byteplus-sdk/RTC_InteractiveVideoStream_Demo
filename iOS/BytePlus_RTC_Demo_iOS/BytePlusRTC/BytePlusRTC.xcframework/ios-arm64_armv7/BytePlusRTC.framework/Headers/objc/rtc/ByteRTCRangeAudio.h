/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief range audio interface
 */

#pragma once

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

/** 
 * @type keytype
 * @brief The range where local user can hear audio with attenuation effect.
 */
BYTERTC_APPLE_EXPORT @interface ReceiveRange : NSObject
/** 
 * @brief The minimum distance at which the local user can hear the attenuated audio from remote users.  <br>
 *        The value must be ≥ 0, but ≤ max.  <br>
 *        No attenuation effect for audio from distances less than this value you set.
 */
@property(nonatomic, assign) int min;
/** 
 * @brief The maximum distance at which the local user can hear audio from remote users.  <br>
 *        The value must be ≥ min, and > 0.  <br>
 *        Audio from distances larger than the value you set cannot be heard.
 */
@property(nonatomic, assign) int max;
@end

/** 
 * @type keytype
 * @brief Range audio stream information
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRangeAudioInfo : NSObject
/** 
 * @brief ID of remote stream publisher
 */
@property(copy, nonatomic) NSString * _Nonnull userId;
/** 
 * @brief Attenuation coefficient of the remote user. The value range is [0,100].  <br>
 *        A value of 0 means that the remote user's audio volume is 0.
 */
@property(nonatomic, assign) int factor;

@end

/** 
 * @type callback
 * @brief Range audio attenuation coefficient observer
 */
BYTERTC_APPLE_EXPORT @protocol ByteRTCRangeAudioObserver <NSObject>
/** 
 * @type callback
 * @region Range Audio
 * @author chuzhongtao
 * @brief Callback about the current attenuation coefficient of remote users.  <br>
 *        In manual subscription mode, when any user in the room calls updatePosition:{@link #ByteRTCRangeAudio#updatePosition:} to update their position or updateReceiveRange:{@link #ByteRTCRangeAudio#updateReceiveRange:} to update their audio receiving range, the relative distance between this user and other users in the room will change, and the attenuation coefficient calculated accordingly will change as well, which will be notified to users.  <br>
 *        You can determine whether to subscribe to a remote user's audio stream based on the attenuation coefficient of that user shown in this callback.
 * @param rangeAudioInfo Array containing audio stream information, see ByteRTCRangeAudioInfo{@link #ByteRTCRangeAudioInfo}.
 * @notes You will not receive this callback immediately after updating your location or audio receiving range. SDK calculates the attenuation coefficient every 500 ms, and only trigger this callback if the result of the calculation is different from the previous one, or if the result is the same but more than 3 seconds after the last calculation.
 */
- (void)onRangeAudioInfo:(NSArray<ByteRTCRangeAudioInfo *> * _Nonnull)rangeAudioInfo;

@end

/** 
 * @type api
 * @author chuzhongtao
 * @brief Range audio instance
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCRangeAudio :NSObject
/** 
 * @type api
 * @region Range Audio
 * @author chuzhongtao
 * @brief Enable/disable the range audio function.  <br>
 *        Range audio means that within a certain range in a same RTC room, the audio volume of the remote user received by the local user will be amplified/attenuated as the remote user moves closer/away. The audio coming from out of the range cannot be heard. See updateReceiveRange:{@link #ByteRTCRangeAudio#updateReceiveRange:} to set audio receiving range.
 * @param enable Whether to enable audio range funcion：  <br>
 *        + true: Enable  <br>
 *        + false: Disable（Defaulting setting）
 * @notes You can call this API anytime before or after entering a room. To ensure a smooth switch to the range audio mode after entering the room, you need to call updatePosition:{@link #ByteRTCRangeAudio#updatePosition:} before this API to set your own position coordinates, and then enable the range audio function.
 */
- (void)enableRangeAudio:(BOOL)enable;
/** 
 * @type api
 * @region Range Audio
 * @author chuzhongtao
 * @brief Updates the audio receiving range for the local user.
 * @param range Audio receiving range, see ReceiveRange{@link #ReceiveRange}.
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @notes If you have previously called registerRangeAudioObserver:{@link #ByteRTCRangeAudio#registerRangeAudioObserver:} to set an observer monitoring attenuation coefficient, you will receive onRangeAudioInfo:{@link #ByteRTCRangeAudioObserver#onRangeAudioInfo:} when any user in the room calls this API to update the audio receiving range.
 */
- (int)updateReceiveRange:(ReceiveRange* _Nonnull) range;
/** 
 * @type api
 * @region Range Audio
 * @author chuzhongtao
 * @brief Updates the coordinate of the local user's position in the rectangular coordinate system in the current room.
 * @param pos 3D coordinate values, the default value is [0, 0, 0], see Position{@link #Position}.
 * @return API call result: <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @notes  <br>
 *        + After calling this API, you should call enableRangeAudio:{@link #ByteRTCRangeAudio#enableRangeAudio:} to enable range audio function to actually enjoy the range audio effect.  <br>
 *        + If you have previously called registerRangeAudioObserver:{@link #ByteRTCRangeAudio#registerRangeAudioObserver:} to set an observer monitoring attenuation coefficient, you will receive onRangeAudioInfo:{@link #ByteRTCRangeAudioObserver#onRangeAudioInfo:} when any user in the room calls this API to update their coordinates.
 */
- (int)updatePosition:(Position* _Nonnull) pos;
/** 
 * @type api
 * @region Range Audio
 * @author chuzhongtao
 * @brief Sets the attenuation coefficient observer
 * @param observer Attenuation coefficient observer.
 *        After you call this API, SDK will trigger onRangeAudioInfo:{@link #ByteRTCRangeAudioObserver#onRangeAudioInfo:} when it detects that a user in the room updates their location coordinates or audio receiving. See ByteRTCRangeAudioObserver{@link #ByteRTCRangeAudioObserver}.
 * @notes You should only call this API in manual subscription mode.
 */
- (void)registerRangeAudioObserver:(_Nullable id<ByteRTCRangeAudioObserver>) observer;

@end
