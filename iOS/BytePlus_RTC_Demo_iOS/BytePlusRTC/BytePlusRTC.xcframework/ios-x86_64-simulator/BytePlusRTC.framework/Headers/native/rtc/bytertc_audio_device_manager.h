/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Audio Device Manager
*/

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {

/** 
 * @type api
 * @region  engine management
 * @brief  Audio & video equipment related information
 */
class IDeviceCollection {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IDeviceCollection() {
    }
    /** 
     * @type api
     * @region engine management
     * @brief Get the number of audio & video devices in the current system
     * @return Number of audio & video devices
     */
    virtual int getCount() = 0;
    /** 
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param  [in] index Device index number, starting from 0, note that it must be less than the return value of getCount{@link #IAudioDeviceCollection#getCount}.
     * @param  [out] device_name device name
     * @param  [out] device_id device ID
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region  engine management
     * @brief  Releases the resources occupied by the current IDeviceCollection{@link #IAudioDeviceCollection} object.
     * @notes This method should be called to release related resources when you do not need to return a list of audio & video device related information.
     */
    virtual void release() = 0;
/**
 * @hidden
 */
protected:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IDeviceCollection() {
    }
};

/** 
 * @type api
 * @region  engine management
 * @brief  Audio equipment related information
 */
class IAudioDeviceCollection : public IDeviceCollection {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IAudioDeviceCollection() {};
    /** 
     * @type api
     * @region engine management
     * @brief Get the number of audio & video devices in the current system
     * @return Number of audio devices
     */
    virtual int getCount() override {return 0;};
    /** 
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param  [in] index Device index number, starting from 0, note that it must be less than the return value of getCount{@link #IAudioDeviceCollection#getCount}.
     * @param  [out] device_name Device name
     * @param  [out] device_id Device ID
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) override {return 0;};
    /** 
     * @type api
     * @region  engine management
     * @brief  Releases the resources occupied by the current IAudioDeviceCollection{@link #IAudioDeviceCollection} object.
     * @notes This method should be called to release related resources when you do not need to return a list of audio device related information.
     */
    virtual void release()override {};
    /** 
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param  [in] index Device index number, starting from 0, note that it must be less than the return value of GetCount{@link #IAudioDeviceCollection#getCount}.
     * @param  [out] audio_device_info device info
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getDevice(int index, AudioDeviceInfo* audio_device_info) = 0;
protected:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IAudioDeviceCollection() {};
};

/** 
 * @type api
 * @brief Audio Facility Management
 */
class IAudioDeviceManager {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IAudioDeviceManager() {
    }
    /** 
     * @type api
     * @region  Audio device management
     * @brief  Gets a list of the audio playback device. When the audio playback device changes, you will receive the `OnMediaDeviceStateChanged` callback, and you need to call this API again to get the new device list.
     * @return  A list of all audio playback devices. See IAudioDeviceCollection{@link #IAudioDeviceCollection}.
     */
    virtual IAudioDeviceCollection* enumerateAudioPlaybackDevices() = 0;
    /** 
     * @type api
     * @region  Audio Facility Management
     * @brief  Get a list of audio acquisition devices in the current system. If there are subsequent device changes, you need to call this interface again to get a new device list.
     * @return An object that contains a list of all audio capture devices in the system. See IAudioDeviceCollection{@link #IAudioDeviceCollection}.
     * @notes When the returned object is no longer used, you need to call release{@link #IAudioDeviceCollection#release} to release it.
     */
    virtual IAudioDeviceCollection* enumerateAudioCaptureDevices() = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio playback device to follow the OS default setting or not.
     * @param followed <br>
     *        + true: follow the os default setting. You can not call setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} at the same time.
     *        + false: do not follow the os default setting. You can call setAudioPlaybackDevice{@link #IAudioDeviceManager#setAudioPlaybackDevice} to set the audio playback device.
     */
    virtual void followSystemPlaybackDevice(bool followed) = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Set the audio capture device to follow the OS default setting or not.
     * @param followed <br>
     *        + true: follow the os default setting. You can not call setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} at the same time.
     *        + false: do not follow the os default setting. You can call setAudioCaptureDevice{@link #IAudioDeviceManager#setAudioCaptureDevice} to set the audio capture device.
     */
    virtual void followSystemCaptureDevice(bool followed) = 0;
    /** 
     * @type api
     * @region Audio device management
     * @brief Sets the audio playback device.
     * @param  [in] device_id Audio playback device's ID. You can get the ID by calling
     * enumerateAudioPlaybackDevices{@link #enumerateAudioPlaybackDevices}.
     * @return    <br>
     *         + 0: Success <br>
     *         + < 0: Failure <br>
     * @notes After you call followSystemPlaybackDevice{@link #IAudioDeviceManager#followSystemPlaybackDevice} to set the audio playback device to follow the system setting, you cannot call this API to set the audio playback device.
     */
    virtual int setAudioPlaybackDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Set up audio capture devices.
     * @param  [in] device_id Audio capture device ID, available through enumerateAudioCaptureDevices{@link #enumerateAudioCaptureDevices}.
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     * @notes After you call followSystemCaptureDevice{@link #IAudioDeviceManager#followSystemCaptureDevice} to set the audio playback device to follow the system setting, you cannot call this API to set the audio capture device.
     */
    virtual int setAudioCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region  Audio Facility Management
     * @brief Sets the current audio playback device volume
     * @param  [in] volume Audio playback device volume, the value range is [0,255], the setting beyond this range is invalid.
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int setAudioPlaybackDeviceVolume(unsigned int volume) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Get the current audio playback device volume
     * @param  [out] volume Audio playback device volume, the range should be within [0,255].
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioPlaybackDeviceVolume(unsigned int* volume) = 0;
    /** 
     * @type api
     * @region  Audio Facility Management
     * @brief Set the current audio acquisition device volume
     * @param  [in] volume Audio acquisition device volume, the value range is [0,255], the setting beyond this range is invalid.
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int setAudioCaptureDeviceVolume(unsigned int volume) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Get the current audio capture device volume
     * @param  [out] volume Audio capture device volume, the range should be within [0,255].
     *        + [0,25] Is nearly silent; <br>
     *        + [25,75] Is low volume; <br>
     *        + [76,204] Is medium volume; <br>
     *        + [205,255] Is high volume. <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioCaptureDeviceVolume(unsigned int* volume) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Sets the current audio playback device to be mute, and the default is non-mute.
     * @param  [in] mute <br>
     *        + True: mute <br>
     *        + False: non-mute <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int setAudioPlaybackDeviceMute(bool mute) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Gets information about whether the current audio playback device is muted.
     * @param  [out] mute <br>
     *        + True: mute <br>
     *        + False: non-mute <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioPlaybackDeviceMute(bool* mute) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Sets the current audio acquisition device to be mute, and the default is non-mute.
     * @param  [in] mute <br>
     *        + True: mute <br>
     *        + False: non-mute <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int setAudioCaptureDeviceMute(bool mute) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Gets information about whether the current audio capture device is silent.
     * @param  [out] mute <br>
     *        + True: mute <br>
     *        + False: non-mute <br>
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioCaptureDeviceMute(bool* mute) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Gets the current audio playback device ID.
     * @param  [out] device_id audio playback device ID
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioPlaybackDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Gets the current audio capture device ID.
     * @param  [out] device_id audio capture device ID, the user is responsible for allocating and freeing memory according to the MAX_DEVICE_ID_LENGTH size
     * @return   Method call result   <br>
     *         + 0: Success. <br>
     *         + < 0: failure <br>
     */
    virtual int getAudioCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Try to initialize the audio playback device, and you can detect abnormal problems such as the device does not exist, permissions are denied/disabled, etc.
     * @param  [in] deviceId Device index number
     * @return Device status error code
     *         + 0: device detection result is normal
     *         + -1: The interface status is incorrect, for example, the interface is called for detection after the acquisition is started normally
     *         + -2: The acquisition device does not have microphone permission, and attempts to initialize the device fail
     *         + -3: The device does not exist, there is currently no device or return when the device is removed
     *         + -4: Device audio format not supported
     *         + -5: Error for other reasons
     * @notes 1. This interface needs to be called before entering the room; <br>
     *        2. Successful detection does not necessarily mean that the device can be started successfully. It may also fail to start due to the device being monopolized by other application processes, or CPU/memory shortage.
     */
    virtual int initAudioPlaybackDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Try to initialize the audio capture device, which can detect abnormal problems such as the device does not exist, permissions are denied/disabled, etc.
     * @param  [in] deviceId Device index
     * @return Device status error code
     *         + 0: device detection result is normal
     *         + -1: The interface status is incorrect, for example, the interface is called for detection after the acquisition is started normally
     *         + -2: The acquisition device does not have microphone permission, and attempts to initialize the device fail
     *         + -3: The device does not exist, there is currently no device or return when the device is removed
     *         + -4: Device audio format not supported
     *         + -5: Error for other reasons
     * @notes 1. This interface needs to be called before entering the room; <br>
     *        2. Successful detection does not necessarily mean that the device can be started successfully. It may also fail to start due to the device being monopolized by other application processes, or CPU/memory shortage.
     */
    virtual int initAudioCaptureDeviceForTest(const char deviceId[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Start the playback test for the local audio device. RTC will start playing the audio file specified. And RTC will notify the audio volume via the onAudioPlaybackDeviceTestVolume{@link #IRtcEngineEventHandler#onAudioPlaybackDeviceTestVolume} periodically.
     * @param  [in] test_audio_file_path  Specify the path of the audio file for the playback test, including *.mp3, *.aac, *.m4a, *.3gp, and *.wav.
     * @param  [in] indication_interval The time interval between each callback in milliseconds. We recommend setting it to 200 ms. The minimal value is 10 ms.
     * @return <br>
     *         + 0: success  <br>
     *         + < 0: failure  <br>
     * @notes <br>
     *       + You can call this API whether the user is in the room.   <br>
     *       + Call stopAudioPlaybackDeviceTest{@link #IAudioDeviceManager#stopAudioPlaybackDeviceTest} to stop the playback test before moving on to the other device tests.   
     */
     virtual int startAudioPlaybackDeviceTest(const char* test_audio_file_path, int indication_interval) = 0;

    /** 
    * @type api
    * @region Audio Facility Management
    * @brief Stop the playback test for the local audio device.
    * @return  result
    *         + 0: success  <br>
    *         + < 0: failure  <br>
    * @notes  Call this API to stop the playback test started by calling startAudioPlaybackDeviceTest{@link #IAudioDeviceManager#startAudioPlaybackDeviceTest} before moving on to the other device tests.
    */
    virtual int stopAudioPlaybackDeviceTest() = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Start the capture and playback test for local audio devices.  <br>
     *        We recommend to register `onLocalAudioPropertiesReport` callback via enableAudioPropertiesReport{{@link #enableAudioPropertiesReport}. Once the test starts, you can get the volume of the capturing audio by this callback.
     * @param [in] indication_interval  The time interval between each callback of `onLocalAudioPropertiesReport` via which you get informed of the playback volume during the test.  We recommend setting it to 200 ms. The minimal value is 10 ms.
     * @return  result
     *         + 0: success  <br>
     *         + < 0: failure  <br>
     * @notes  <br>
     *       + You can call this API whether the user is in a room.<br>
     *       + The audio capturing will stop and begins to play the recording in 30 s after calling this API. Before that, call stopAudioDeviceRecordAndPlayTest{@link #IAudioDeviceManager#stopAudioDeviceRecordAndPlayTest}  to stop capturing and start playing the recording. <br>
     *       + You must stop the test before starting another test for audio devices. <br>
     *       + Call stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} to stop the test, including capturing and playing the recording. <br>
     *       + This test performs locally and does not involve network connection testing. <br>
     */
    virtual int startAudioDeviceRecordTest(int indication_interval) = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Call this API to stop recording in the test and start to play the recording in 30 s after calling startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}. 
     * @return result
     *         + 0: success  <br>
     *         + < 0: failure  <br>
     * @notes After calling this API, the recording starts playing during which you can call stopAudioDevicePlayTest{@link #IAudioDeviceManager#stopAudioDevicePlayTest} to stop playing.
     */
    virtual int stopAudioDeviceRecordAndPlayTest() = 0;

    /** 
     * @type api
     * @region Audio Facility Management
     * @brief Stop the capture and playback test for local audio devices which is started by calling startAudioDeviceRecordTest{@link #IAudioDeviceManager#startAudioDeviceRecordTest}.<br>
     * Before the test ends by itself, you can call this API to stop the recording or playing.
     * @return <br>
     *         + 0: success  <br>
     *         + < 0: failure  
     */
    virtual int stopAudioDevicePlayTest() = 0;

    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IAudioDeviceManager() {
    }
};

}  // namespace bytertc
