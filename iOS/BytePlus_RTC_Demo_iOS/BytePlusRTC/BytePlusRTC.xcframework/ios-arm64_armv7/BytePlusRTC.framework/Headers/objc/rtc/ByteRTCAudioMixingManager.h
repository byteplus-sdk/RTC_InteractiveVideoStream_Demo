/*
 * Copyright (c) 2021 The BytePlusRTC project authors. All Rights Reserved.
 * @brief ByteRTCAudioMixingManager
*/

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

/** 
 * @type api
 * @region Audio Mixing
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCAudioMixingManager :NSObject
/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief  Start mixing audio files. <br>
 *         To mixing multiple audio files at the same time, you can call this method with different mixIDs.
 * @param mixId Mix ID. Used to identify the mixing task. <br>
 *         If this method is repeatedly called with the same ID, the previous mixing task will be stopped and a new task will start. When the previous task is stopped, you will receive `onAudioMixingStateChanged`.
 * @param filePath The path of the mixing audio file. <br>
 *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocal is supported. <br>
 *         Audio file formats supported by different platforms: <br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @param config Mixing configuration <br>
 *         You can set the number of times the file is played, whether the file is played locally or remotely. See ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}.
 * @notes   <br>
 *        + If you have already loaded the file in memory with preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:}, ensure that the mixID is the same.  <br>
 *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
 *        + Call stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop the mixing task. <br>
 *        + The mixing data of this API comes from an audio file, while the mixing data of enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:} comes from the PCM data from memory. The two mixing APIs do not affect each other.
 */
-(void)startAudioMixing:(int)mixId filePath:(NSString * _Nullable)filePath config:(ByteRTCAudioMixingConfig * _Nullable)config;

/** 
 * @type api
 * @region  Mix
 * @author majun.lvhiei
 * @brief  Stop playing audio files and mixes
 * @param mixId   <br>
 *         Mix ID
 * @notes   <br>
 *        + Call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} After the method starts playing audio files and mixes, you can call this method to stop playing audio files and mixes. <br>
 *        + After calling this method to stop playing the audio file, the SDK will notify the local callback that the mixing has been stopped. See `onAudioMixingStateChanged`. <br>
 *        + After calling this method to stop playing the audio file, the audio file will be automatically uninstalled.
 */
-(void)stopAudioMixing:(int)mixId;

/** 
 * @type api
 * @region  Mix
 * @author majun.lvhiei
 * @brief  Pause playing audio files
 * @param mixId   <br>
 *         Mix ID
 * @notes   <br>
 *        + After calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} method to start playing audio files and mixing, you can pause playing audio files by calling this method. <br>
 *        + After calling this method to pause playing audio files, you can call the resumeAudioMixing:{@link #ByteRTCAudioMixingManager#resumeAudioMixing:} method to resume playing and mixing. <br>
 *        + After calling this method to pause playing audio files, the SDK will notify the local callback that the mixing has been suspended. See `onAudioMixingStateChanged`.
 */
-(void)pauseAudioMixing:(int)mixId;

/** 
 * @type api
 * @region  mixing
 * @author majun.lvhiei
 * @brief  Resume playing audio files
 * @param mixId   <br>
 *         Mixing ID
 * @notes   <br>
 *        + After calling pauseAudioMixing:{@link #ByteRTCAudioMixingManager#pauseAudioMixing:} method, you can resume playing and mixing by calling this method. <br>
 *        + After calling this method to resume playing the audio file, the SDK will notify the local callback that the audio file is playing. See `onAudioMixingStateChanged`.
 */
-(void)resumeAudioMixing:(int)mixId;
/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Preload the audio file into memory to minimize the loading cost of playing repeatedly.
 * @param mixId Mix ID. Used to identify the mixing task. <br>
 *        If this method is repeatedly called with the same ID, the previous file will be unloaded and the new file will be loaded. <br>
 *         If you call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} and then call this method with the same ID, the previous mixing task will be stopped, and then the next file will be loaded. <br>
 *         After calling this method to preload A.mp3, if you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play B.mp3 with the same ID, call unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:} to unload A.mp3 first.
 * @param filePath The path of the file to preload.<br>
 *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocal is supported. You can only perload the audio file of length less than 20s. <br>
 *         Audio file formats supported by different platforms: <br>
 *        <table>
 *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
 *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
 *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
 *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
 *        </table>
 * @notes   <br>
 *        + After preload, call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to play the audio file. <br>
 *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
 *        + Unload the preloaded file with unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:}.
 */
-(void)preloadAudioMixing:(int)mixId filePath:(NSString * _Nullable)filePath;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Uninstall the specified audio file
 * @param mixId   <br>
 *        Mix ID
 * @notes Whether the audio file is playing or not, after calling this method to uninstall the file, the SDK will call back to notify that the mix has stopped. See `onAudioMixingStateChanged`.
 */
-(void)unloadAudioMixing:(int)mixId;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Adjust the volume of audio mixing, including audio files and PCM data.
 * @param mixId Mixing ID
 * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
 *         + 0: Mute <br>
 *         + 100: Original volume <br>
 *         + 400: Maximum volume (with overflow protection)
 * @param type See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
 */
-(void)setAudioMixingVolume:(int)mixId volume:(int)volume type:(ByteRTCAudioMixingType)type;

/** 
 * @type api
 * @region  mix
 * @author majun.lvhiei
 * @brief  Get audio file duration
 * @param mixId   <br>
 *         Mix ID
 * @return   <br>
 *        + > 0: Success, audio file duration, in milliseconds. <br>
 *        + < 0: Failed
 * @notes  Before calling this method to get the audio file duration, you need to call preloadAudioMixing:filePath:{@link #ByteRTCAudioMixingManager#preloadAudioMixing:filePath:} or startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */
-(int)getAudioMixingDuration:(int)mixId;

/** 
 * @type api
 * @region  mix
 * @author majun.lvhiei
 * @brief  Get audio file playback progress
 * @param mixId   <br>
 *         Mix ID
 * @return   <br>
 *         + > 0: Success, audio file playback progress, in milliseconds. <br>
 *         + < 0: Failed
 * @notes Before calling this method to get the audio file playback progress, you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} first to start playing the audio file.
 */
-(int)getAudioMixingCurrentPosition:(int)mixId;
/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Set the starting playback position of the audio file
 * @param mixId Mixing ID
 * @param position The starting playback position of the audio file in milliseconds.  <br>
 *        You can get the total duration of the audio file with getAudioMixingDuration:{@link #ByteRTCAudioMixingManager#getAudioMixingDuration:}, the value of position set using this method must not be greater than the total duration of the audio file.
 * @notes When mixing online files, calling this API may cause mixing delay.
 */
-(void)setAudioMixingPosition:(int)mixId position:(int)position;

/** 
 * @type api
 * @region  mix
 * @author majun.lvhiei
 * @brief  Set the channel mode of the current audio file
 * @param mixId  Mix ID
 * @param mode  Channel mode. The default channel mode is the same as the source file. See ByteRTCAudioMixingDualMonoMode{@link #ByteRTCAudioMixingDualMonoMode}.
 * @notes  <br>
 *         + Before calling this method to set the channel mode of the audio file, you need to call startAudioMixing:filePath:config:{@link #startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *         + This method is invalid for music played by enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
-(void) setAudioMixingDualMonoMode:(int)mixId mode:(ByteRTCAudioMixingDualMonoMode)mode;

/** 
 * @type api
 * @region Audio Mixing
 * @author wangjunzheng
 * @brief Enables local playback of music files in a different key, mostly used in Karaoke scenarios.  <br>
 *        You can adjust the pitch of locally played music files such as ascending or descending with this method.
 * @param mixId Mixing ID
 * @param pitch The value that is higher or lower than the original pitch of the audio file within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
 *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
 *        Out of the value range, the setting fails and triggers the `onAudioMixingStateChanged` callback, indicating `AUDIO_MIXING_STATE_FAILED` for playback failure with ByteRTCAudioMixingState{@link # ByteRTCAudioMixingState}, and `AUDIO_MIXING_ERROR_ID_TYPE_ INVALID_PITCH` for invalid value setting with ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError}.
 * @notes This method needs to be used after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file and before calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop playing the audio file, otherwise the `onAudioMixingStateChanged` callback will be triggered.
 */
-(void)setAudioMixingPitch:(int)mixId pitch:(int)pitch;

/** 
 * @type api
 * @region Audio Mixing
 * @author dixing
 * @brief Sets the playback speed of the current audio file.
 * @param mixId Audio mixing task ID
 * @param speed Ratio of playback speed to original speed in percentage. The range is [50,200], the default value is 100.  <br>
 *        If the value you set is out of range, the setting fails, and you will receive an `onAudioMixingStateChanged` callback, in which the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStateFailed` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `ByteRTCAudioMixingErrorInValidPlaybackSpeed`.
 * @notes   <br>
 *        + This API can not be used on setting playback speed for PCM audio data.  <br>
 *        + You should call this API after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} and receiving an `onAudioMixingStateChanged` callback indicating that the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStatePlaying` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `AUDIO_MIXING_ERROR_OK`.  <br>
 *        + If you call this API after calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} or unloadAudioMixing:{@link #ByteRTCAudioMixingManager#unloadAudioMixing:}, you will receive an `onAudioMixingStateChanged` callback indicating that the ByteRTCAudioMixingState{@link #ByteRTCAudioMixingState} is `ByteRTCAudioMixingStateFailed` and the ByteRTCAudioMixingError{@link #ByteRTCAudioMixingError} is `ByteRTCAudioMixingErrorIdNotFound`.
 */
-(int)setAudioMixingPlaybackSpeed:(int)mixId speed:(int)speed;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief If you need to call `enableVocalInstrumentBalance` to adjust the volume of the audio file or PCM data used for audio mixing, you must import the original loudness value of the audio file or PCM data via this API.
 * @param mixId Audio mixing ID
 * @param loudness Original loudness of the audio file in lufs. The range is [-70.0, 0.0].  <br>
 *        If the value is set to be less than -70.0lufs, it is automatically adjusted to -70.0lufs. If the value is set to be greater than 0.0lufs, SDK will not equalize the loudness. The default value is 1.0lufs, i.e. No loudness equalization effect.
 * @notes To avoid sudden volume changes during audio file playback, we recommend that you call this API before starting to play the audio file with startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:}.
 */ 
-(void)setAudioMixingLoudness:(int)mixId loudness:(float)loudness;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Set the interval of audio file playback progress callbacks during audio mixing
 * @param mixId Mixing ID  <br>
 *        You can set the interval for multiple IDs by calling this method multiple times and passing in different IDs.
 * @param interval The time interval (ms) of the audio file playback progress callback in milliseconds.  <br>
 *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
 *       + If the value is less than or equals to 0, the callback will not be triggered.  <br>
 * @notes This method needs to be used after calling startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file, and before calling stopAudioMixing:{@link #ByteRTCAudioMixingManager#stopAudioMixing:} to stop playing the audio file, otherwise an error callback `onAudioMixingStateChanged` will be triggered.  <br>
 *        If you want to set the interval of playback progress callbacks before the music file starts playing, you need to call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to set the interval in ByteRTCAudioMixingConfig{@link #ByteRTCAudioMixingConfig}, and you can update the callback interval through this method after the audio file starts playing.
 */
-(void) setAudioMixingProgressInterval:(int)mixId interval:(int64_t) interval;

 /** 
  * @type api
  * @region Audio Mixing
  * @author majun.lvhiei
  * @brief Start PCM mixing. <br>
  *        To mix multiple PCM audio data, call this API multiple times with different ids.
  * @param mixId Mixing ID. Used to identify the mixing. Ensure it is unique. <br>
  *        If this API is called repeatedly with the same ID, the previous mixing will stop, and the next mixing will start, and you will receive `onAudioMixingStateChanged` notification that the previous mixing has stopped.
  * @param type Mixing type <br>
  *        Whether the PCM data is mixed locally and sent to the remotes. See ByteRTCAudioMixingType{@link #ByteRTCAudioMixingType}.
  * @notes   <br>
  *        + After this API, you must call pushAudioMixingFrame:audioFrame:{@link #pushAudioMixingFrame:audioFrame:} to start mixing. <br>
  *        + To end PCM mixing, use disableAudioMixingFrame:{@link #disableAudioMixingFrame:}.
  */
-(void)enableAudioMixingFrame:(int)mixId type:(ByteRTCAudioMixingType)type;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief End PCM mixing.
 * @param mixId Mixing ID.
 */
-(void)disableAudioMixingFrame:(int)mixId;

/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Push PCM audio frame data for mixing
 * @param mixId Mixing ID.
 * @param audioFrame See ByteRTCAudioFrame{@link #ByteRTCAudioFrame}.
 * @return   <br>
 *        + 0: Success <br>
 *        + < 0: Failure
 * @notes
 *       + Before calling this method, you must start the external audio stream mixing through enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}. <br>
 *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 200 milliseconds) on the application side, and then push it all at once; after that, the push operation is timed once in 10 milliseconds, and the amount of audio data each time is 10 milliseconds. To pause PCM mixing, pause pushing PCM data.
 */
-(int)pushAudioMixingFrame:(int)mixId audioFrame:(ByteRTCAudioFrame* _Nullable)audioFrame;
/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief  Get the track index of the current audio file
 * @param  mixId Mixding ID
 * @return   <br>
 *        + >=0: Succeeded, the SDK will return the track index of the current audio file.  <br> <br>
 *        + < 0: Failed
 * @notes  <br>
 *       + Before using this method, you should call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *       + This method is invalid for music played using enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
-(int)getAudioTrackCount:(int)mixId;
/** 
 * @type api
 * @region Audio Mixing
 * @author majun.lvhiei
 * @brief Specify the playback track of the current audio file
 * @param mixId Mixing ID
 * @param audioTrackIndex The specified playback track.  <br>
 *        The set parameter value needs to be less than or equal to the return value of getAudioTrackCount:{@link #ByteRTCAudioMixingManager#getAudioTrackCount:}.
 * @notes  <br>
 *       + Before using this method, you should call startAudioMixing:filePath:config:{@link #ByteRTCAudioMixingManager#startAudioMixing:filePath:config:} to start playing the audio file. <br>
 *       + This method is invalid for music played using enableAudioMixingFrame:type:{@link #ByteRTCAudioMixingManager#enableAudioMixingFrame:type:}.
 */
-(void)selectAudioTrack:(int)mixId audioTrackIndex:(int)audioTrackIndex;
@end
