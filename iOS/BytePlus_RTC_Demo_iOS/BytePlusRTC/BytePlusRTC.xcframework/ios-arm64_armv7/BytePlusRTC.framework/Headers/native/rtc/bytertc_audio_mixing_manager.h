/*
 * Copyright (c) 2021 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Audio Mixing Manager
*/

#pragma once

#ifndef BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#define BYTE_RTC_AUDIO_MIXING_MANAGER_H__
#include "bytertc_audio_frame.h"

namespace bytertc {

/** 
 * @type api
 * @brief  Mixing management class
 */
class IAudioMixingManager {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IAudioMixingManager() {
    }
    /** 
     * @type api
     * @region Audio Mixing
     * @brief  Start mixing audio files. <br>
     *         To mixing multiple audio files at the same time, you can call this method with different mixIDs.
     * @param [in] mix_id Mix ID. Used to identify the mixing task. <br>
     *         If this method is repeatedly called with the same ID, the previous mixing task will be stopped and a new task will start. When the previous task is stopped, you will receive `onAudioMixingStateChanged`.
     * @param [in] file_path The path of the mixing audio file. <br>
     *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocal is supported. <br>
     *         Audio file formats supported by different platforms: <br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @param [in] config Mixing configuration <br>
     *         You can set the number of times the file is played, whether the file is played locally or remotely. See AudioMixingConfig{@link #AudioMixingConfig}.
     * @notes   <br>
     *        + If you have already loaded the file in memory with preloadAudioMixing{@link #IAudioMixingManager#preloadAudioMixing}, ensure that the mixID is the same.  <br>
     *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
     *        + Call stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} to stop the mixing task. <br>
     *        + The mixing data of this API comes from an audio file, while the mixing data of enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame} comes from the PCM data from memory. The two mixing APIs do not affect each other.
     */
    virtual void startAudioMixing(int mix_id, const char * file_path, const AudioMixingConfig& config) = 0;

    /** 
     * @type api
     * @region  Mix
     * @brief  Stop playing music files and mixes
     * @param  [in] mix_id <br>
     *         Mix ID
     * @notes   <br>
     *        + After calling the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method to start playing music files and mixes, you can call this method to stop playing music files and mixes. <br>
     *        + After calling this method to stop playing the music file, the SDK notifies the local callback that the mixing has been stopped. See `onAudioMixingStateChanged`. <br>
     *        + After calling this method to stop playing the music file, the music file will be automatically uninstalled.
     */
    virtual void stopAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region  Mix
     * @brief  Pause playing music files and mixes
     * @param  [in] mix_id <br>
     *         Mix ID
     * @notes   <br>
     *        + After calling the startAudioMixing{@link #IAudioMixingManager#startAudioMixing} method to start playing music files and mixes, you can call this method to pause playing music files and mixes. <br>
     *        + After calling this method to pause playing music files and mixing, you can call the resumeAudioMixing{@link #IAudioMixingManager#resumeAudioMixing} method to resume playing and mixing. <br>
     *        + After calling this method to pause playing the music file, the SDK will notify the local callback that the mixing has been suspended. See `onAudioMixingStateChanged`.
     */
    virtual void pauseAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region  mixing
     * @brief  Resume playing music files and mixing
     * @param  [in] mix_id <br>
     *         Mixing ID
     * @notes   <br>
     *        + After calling the pauseAudioMixing{@link #IAudioMixingManager#pauseAudioMixing} method to pause playing music files and mixing, you can resume playing and mixing by calling this method. <br>
     *        + After calling this method to resume playing the music file and mixing, the SDK will notify the local callback that the music file is playing. See `onAudioMixingStateChanged`.
     */
    virtual void resumeAudioMixing(int mix_id) = 0;
    /** 
     * @type api
     * @region Audio Mixing
     * @brief Preload the audio file into memory to minimize the loading cost of playing repeatedly.
     * @param [in] mix_id Mix ID. Used to identify the mixing task. <br>
     *        If this method is repeatedly called with the same ID, the previous file will be unloaded and the new file will be loaded. <br>
     *         If you call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} and then call this method with the same ID, the previous mixing task will be stopped, and then the next file will be loaded. <br>
     *         After calling this method to preload A.mp3, if you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play B.mp3 with the same ID, call unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing} to unload A.mp3 first.
     * @param [in] file_path The path of the file to preload.<br>
     *        You can use the URL of the online file, and the absolute path of the local file. For the URL of the online file, only https protocal is supported. You can only perload the audio file of length less than 20s. <br>
     *         Audio file formats supported by different platforms: <br>
     *        <table>
     *           <tr><th></th><th>mp3</th><th>mp4</th><th>aac</th><th>m4a</th><th>3gp</th><th>wav</th><th>ogg</th><th>ts</th><th>wma</th></tr>
     *           <tr><td>Android</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td></tr>
     *           <tr><td>iOS</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td></td><td></td></tr>
     *           <tr><td>Windows</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td>Y</td><td></td><td>Y</td><td>Y</td></tr>
     *        </table>
     * @notes   <br>
     *        + After preloaded, call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to play the audio file. <br>
     *        + After calling this method, you will receive `onAudioMixingStateChanged` about the current mixing status. <br>
     *        + Unload the preloaded file with unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing}.
     */
    virtual void preloadAudioMixing(int mix_id, const char* file_path) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Uninstall the specified music file
     * @param  [in] mix_id <br>
     *        Mix ID
     * @notes Whether the music file is playing or not, after calling this method to uninstall the file, the SDK will call back to notify that the mix has stopped. See `onAudioMixingStateChanged`.
     */
    virtual void unloadAudioMixing(int mix_id) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Adjust the volume of audio mixing, including audio files and PCM data.
     * @param mix_id Mixing ID
     * @param volume The ratio of the mixing volume to the original volume. The range is `[0, 400]`. The recommended range is `[0, 100]`. <br>
     *         + 0: Mute <br>
     *         + 100: Original volume <br>
     *         + 400: Maximum volume (with overflow protection)
     * @param type See AudioMixingType{@link #AudioMixingType}.
     */
    virtual void setAudioMixingVolume(int mix_id, int volume, AudioMixingType type) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Get the duration of the music file
     * @param  [in] mix_id <br>
     *        Mix ID
     * @return   <br>
     *         + > 0: Success, the duration of the music file, in milliseconds. <br>
     *         + < 0: Failed
     * @notes  Before calling this method to get the length of the music file, you need to call preloadAudioMixing{@link #preloadAudioMixing} or startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */
    virtual int getAudioMixingDuration(int mix_id) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Get the music file playback progress
     * @param  [in] mix_id <br>
     *        Mix ID
     * @return   <br>
     *         + > 0: Success, the music file playback progress, in milliseconds. <br>
     *         + < 0: Failed
     * @notes  Before calling this method to get the progress of music file playback, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing music files.
     */
    virtual int getAudioMixingCurrentPosition(int mix_id) = 0;
    /** 
     * @type api
     * @region Audio Mixing
     * @brief Set the starting position of the audio file for audio mixing
     * @param [in] mix_id Mixing ID
     * @param [in] position The starting position in ms. <br>
     *        You can get the length of the file with getAudioMixingDuration{@link #IAudioMixingManager#getAudioMixingDuration}. The value of the position must be less than the length of the file.
     * @notes When mixing online files, calling this API may cause mixing delay.
     */
    virtual void setAudioMixingPosition(int mix_id, int position) = 0;

    /** 
     * @type api
     * @region  Mix
     * @brief  Set the channel mode of the current audio file
     * @param  [in] mix_id Mix ID
     * @param  [in] mode Channel mode. The default channel mode is the same as the source file. See AudioMixingDualMonoMode{@link #AudioMixingDualMonoMode}.
     * @notes  <br>
     *         + Before calling this method to set the channel mode of the audio file, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *         + This method is invalid for music played by enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual void setAudioMixingDualMonoMode(int mix_id, AudioMixingDualMonoMode mode) = 0;
    
    /** 
     * @type api
     * @region Audio Mixing
     * @brief Enables local playback of music files in a different key, mostly used in Karaoke scenarios.  <br>
     *        You can adjust the pitch of locally played music files such as ascending or descending with this method.
     * @param [in] mix_id Mixing ID
     * @param [in] pitch The value that is higher or lower than the original pitch of the audio file within a range from -12 to 12. The default value is 0, i.e. No adjustment is made.  <br>
     *        The difference in pitch between two adjacent values within the value range is a semitone, with positive values indicating an ascending tone and negative values indicating a descending tone, and the larger the absolute value set, the more the pitch is raised or lowered.  <br>
     *        Out of the value range, the setting fails and triggers the `onAudioMixingStateChanged` callback, indicating `AUDIO_MIXING_STATE_FAILED` for playback failure with AudioMixingState{@link # AudioMixingState}, and `AUDIO_MIXING_ERROR_ID_TYPE_ INVALID_PITCH` for invalid value setting with AudioMixingError{@link #AudioMixingError}.
     * @notes This method needs to be used after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file and before calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} to stop playing the audio file, otherwise the `onAudioMixingStateChanged` callback will be triggered.
     */
    virtual void setAudioMixingPitch(int mix_id, int pitch) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Sets the playback speed of the current audio file.
     * @param [in] mix_id Audio mixing task ID
     * @param [in] speed Ratio of playback speed to original speed in percentage. The range is [50,200], the default value is 100.  <br>
     *        If the value you set is out of range, the setting fails, and you will receive an `onAudioMixingStateChanged` callback, in which the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStateFailed` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorInValidPlaybackSpeed`.
     * @notes   <br>
     *        + This API can not be used on setting playback speed for PCM audio data.  <br>
     *        + You should call this API after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} and receiving an `onAudioMixingStateChanged` callback indicating that the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStatePlaying` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorOk`.  <br>
     *        + If you call this API after calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing} or unloadAudioMixing{@link #IAudioMixingManager#unloadAudioMixing}, you will receive an `onAudioMixingStateChanged` callback indicating that the AudioMixingState{@link #AudioMixingState} is `kAudioMixingStateFailed` and the AudioMixingError{@link #AudioMixingError} is `kAudioMixingErrorIdNotFound`.
     */
    virtual int setAudioMixingPlaybackSpeed(int mix_id, int speed) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Set the interval of audio file playback progress callbacks during audio mixing
     * @param [in] mix_id Mixing ID  <br>
     *        You can set the interval for multiple IDs by calling this method multiple times and passing in different IDs.
     * @param [in] interval The time interval (ms) of the audio file playback progress callback in milliseconds.  <br>
     *       + The value of interval is a multiple of 10 greater than 0. When the value set is not divisible by 10, the default is rounded up by 10. For example, if the value is set to 52ms, it will be automatically adjusted to 60ms, then the SDK will trigger `onAudioMixingPlayingProgress` callback at the set interval.  <br>
     *       + If the value is less than or equals to 0, the callback will not be triggered.  <br>
     * @notes This method needs to be used after calling startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file, and before calling stopAudioMixing{@link #IAudioMixingManager#stopAudioMixing}} to stop playing the audio file, otherwise an error callback `onAudioMixingStateChanged` will be triggered.  <br>
     *        If you want to set the interval of playback progress callbacks before the music file starts playing, you need to call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to set the interval in AudioMixingConfig{@link #AudioMixingConfig}, and you can update the callback interval through this method after the audio file starts playing.
     */
    virtual void setAudioMixingProgressInterval(int mix_id, int64_t interval) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief If you need to call `enableVocalInstrumentBalance` to adjust the volume of the audio file or PCM data used for audio mixing, you must import the original loudness value of the audio file or PCM data via this API.
     * @param [in] mixId Audio mixing ID
     * @param [in] loudness Original loudness of the audio file in lufs. The range is [-70.0, 0.0].  <br>
     *        If the value is set to be less than -70.0lufs, it is automatically adjusted to -70.0lufs. If the value is set to be greater than 0.0lufs, SDK will not equalize the loudness. The default value is 1.0lufs, i.e. No loudness equalization effect.
     * @notes To avoid sudden volume changes during audio file playback, we recommend that you call this API before starting to play the audio file with startAudioMixing{@link #IAudioMixingManager#startAudioMixing}.
     */ 
    virtual void setAudioMixingLoudness(int mix_id, float loudness) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Start PCM mixing. <br>
     *        To mix multiple PCM audio data, call this API multiple times with different mix_ids.
     * @param [in] mix_id Mixing ID. Used to identify the mixing. Ensure it is unique. <br>
     *        If this API is called repeatedly with the same mix_id, the previous mixing will stop, and the next mixing will start, and you will receive `onAudioMixingStateChanged` notification that the previous mixing has stopped.
     * @param [in] type Mixing type <br>
     *        Whether the PCM data is mixed locally and sent to the remotes. See AudioMixingType{@link #AudioMixingType}.
     * @notes   <br>
     *        + After this API, you must call pushAudioMixingFrame{@link #pushAudioMixingFrame} to start mixing. <br>
     *        + To end PCM mixing, use disableAudioMixingFrame{@link #IAudioMixingManager#disableAudioMixingFrame}.
     */
    virtual void enableAudioMixingFrame(int mix_id, AudioMixingType type) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief End PCM mixing.
     * @param mix_id Mixing ID.
     */
    virtual void disableAudioMixingFrame(int mix_id) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Push PCM audio frame data for mixing
     * @param mix_id Mixing ID.
     * @param audioFrame See IAudioFrame{@link #IAudioFrame}.
     * @return   <br>
     *        + 0: Success <br>
     *        + < 0: Failure
     * @notes
     *       + Before calling this method, you must start the external audio stream mixing through enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}. <br>
     *       + Use reference suggestions: For the first time to push data, please cache certain data (such as 100 milliseconds) on the application side, and then push it at once; after that, the push operation is timed to be once in 10 milliseconds, and the amount of audio data each time is 10 milliseconds. To pause PCM mixing, pause pushing PCM data.
     */
    virtual int pushAudioMixingFrame(int mix_id, IAudioFrame* audio_frame) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Get the track index of the current audio file
     * @param [in] mix_id Mixding ID
     * @return  <br>
     *        + >=0: Succeeded, the SDK will return the track index of the current audio file.  <br> <br>
     *        + < 0: Failed
     * @notes  <br>
     *       + Before using this method, you should call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *       + This method is invalid for music played using enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual int getAudioTrackCount(int mix_id) = 0;

    /** 
     * @type api
     * @region Audio Mixing
     * @brief Specify the playback track of the current audio file
     * @param [in] mix_id Mixing ID
     * @param [in] audio_track_index The specified playback track.  <br>
     *        The set parameter value needs to be less than or equal to the return value of getAudioTrackCount{@link #IAudioMixingManager#getAudioTrackCount}.
     * @notes  <br>
     *       + Before using this method, you should call startAudioMixing{@link #IAudioMixingManager#startAudioMixing} to start playing the audio file. <br>
     *       + This method is invalid for music played using enableAudioMixingFrame{@link #IAudioMixingManager#enableAudioMixingFrame}.
     */
    virtual void selectAudioTrack(int mix_id, int audio_track_index) = 0;

    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IAudioMixingManager() {
    }
};

}  // namespace bytertc

#endif // BYTE_RTC_AUDIO_MIXING_MANAGER_H__
