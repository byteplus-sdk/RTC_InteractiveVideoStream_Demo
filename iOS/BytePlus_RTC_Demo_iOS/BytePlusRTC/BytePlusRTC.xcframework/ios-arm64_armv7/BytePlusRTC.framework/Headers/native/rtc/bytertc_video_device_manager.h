/*
 * Copyright (c) 2020 The BytePlusRTC project authors. All Rights Reserved.
 * @brief BytePlusRTC Video Device Manager
*/

#pragma once

#include "bytertc_audio_device_manager.h"

namespace bytertc {

#ifndef ByteRTC_AUDIO_ONLY
/** 
 * @type api
 * @region  engine management
 * @brief  Video equipment related information
 */
class IVideoDeviceCollection : public IDeviceCollection {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IVideoDeviceCollection() {};
    /** 
     * @type api
     * @region engine management
     * @brief Get the number of video devices in the current system
     * @return Number of video devices
     */
    virtual int getCount() override {return 0;};
    /** 
     * @type api
     * @region Engine management
     * @brief According to the index number, get device information
     * @param  [in] index Device index number, starting from 0, note that it must be less than the return value of getCount{@link #IVideoDeviceCollection#getCount}.
     * @param  [out] device_name device name
     * @param  [out] device_id device ID
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getDevice(int index, char device_name[MAX_DEVICE_ID_LENGTH], char device_id[MAX_DEVICE_ID_LENGTH]) override {return 0;};
    /** 
     * @type api
     * @region  engine management
     * @brief  Releases the resources occupied by the current IVideoDeviceCollection{@link #IVideoDeviceCollection} object.
     * @notes This method should be called to release related resources when you do not need to return a list of video device related information.
     */
    virtual void release()override {};
    /** 
     * @type api
     * @region Engine management
     * @brief Get device information according to the 
     * @param  [in] index Device index, starting from 0. It must be less than the return value of getCount{@link #IVideoDeviceCollection#getCount}.
     * @param  [out] video_device_info Device information
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getDevice(int index, VideoDeviceInfo* video_device_info) = 0;
protected:
    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IVideoDeviceCollection() {};
};

/** 
 * @type api
 * @region Video Facility Management
 * @brief Mainly used to enumerate and set up video capture devices
 */
class IVideoDeviceManager {
public:
    /** 
     * @hidden
     * @brief  Constructor
     */
    IVideoDeviceManager() {
    }
    /** 
     * @type api
     * @region  Video Facility Management
     * @brief  Get a list of video capture devices in the current system.
     * @return  Contains a list of all video capture devices in the system. See IVideoDeviceCollection{@link #IVideoDeviceCollection}. <br>
     */
    virtual IVideoDeviceCollection* enumerateVideoCaptureDevices() = 0;
    /** 
     * @type api
     * @region  Video Facility Management
     * @brief  Set the current video capture device
     * @param  [in] device_id Video device ID, which can be obtained through enumerateVideoCaptureDevices{@link #IVideoDeviceManager#enumerateVideoCaptureDevices}
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int setVideoCaptureDevice(const char device_id[MAX_DEVICE_ID_LENGTH]) = 0;
    /** 
     * @type api
     * @region Video Facility Management
     * @brief Get the video capture device information currently used by the SDK
     * @param  [out] device_id Device ID
     * @return   <br>
     *         + 0: Success. <br>
     *         +! 0: failure <br>
     */
    virtual int getVideoCaptureDevice(char device_id[MAX_DEVICE_ID_LENGTH]) = 0;

    /** 
     * @hidden
     * @brief  Destructor
     */
    virtual ~IVideoDeviceManager() {
    }
};

#endif  // ByteRTC_AUDIO_ONLY

}  // namespace bytertc
