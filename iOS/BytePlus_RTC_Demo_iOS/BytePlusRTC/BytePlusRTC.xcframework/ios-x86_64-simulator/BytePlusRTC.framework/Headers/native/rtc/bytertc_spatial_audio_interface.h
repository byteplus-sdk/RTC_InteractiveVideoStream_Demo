/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief spatial audio interface
 */

#pragma once

#include "bytertc_audio_defines.h"

namespace bytertc {

/** 
 * @type keytype
 * @brief Direction Orientation Information
 */
struct Orientation {
    /**  
     * @brief X direction vector
     */
    float x;
    /**  
     * @brief Y direction vector
     */
    float y;
    /**  
     * @brief Z direction vector
     */
    float z;
};

/**  
 * @type keytype
 * @brief Three-dimensional orientation information, each pair of vectors need to be perpendicular. See Orientation{@link #Orientation}.
 */
struct HumanOrientation {
    /**  
     * @brief Forward orientation, the default value is {1,0,0}, i.e., the forward orientation is in the positive direction of x-axis.
     */
    Orientation forward =  { 1, 0, 0 };
    /**  
     * @brief Rightward orientation, the default value is {0,1,0}, i.e., the rightward orientation is in the positive direction of y-axis.
     */
    Orientation right = { 0, 1, 0 };
    /**  
     * @brief Upward orientation, the default value is {0,0,1}, i.e., the upward orientation is in the positive direction of z-axis.
     */
    Orientation up = { 0, 0, 1 };
};

/**  
 * @type api
 * @brief Spatial audio instance
 */
class ISpatialAudio {
public:
    /**  
     * @type api
     * @region Spatial Audio
     * @brief Enable/disable spatial audio function.  <br>
     * @param [in] enable Whether to enable spatial audio function:  <br>
     *        + true：Enable  <br>
     *        + false：Disable(Default setting)
     * @notes You need to call updatePosition{@link #ISpatialAudio#updatePosition} as well to really enjoy the spatial audio effect.
     */
    virtual void enableSpatialAudio(bool enable) = 0;

    /**  
     * @type api
     * @region Spatial Audio
     * @brief Updates the coordinate of the local user's position in the rectangular coordinate system in the current room.
     * @param [in] pos 3D coordinate values, the default value is [0, 0, 0], see Position{@link #Position}.
     * @return API call result: <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @notes Before calling this API, you should call enableSpatialAudio{@link #ISpatialAudio#enableSpatialAudio} first to enable spatial audio function.
     */
    virtual int updatePosition(const Position& pos) = 0;

    /**  
     * @type api
     * @region Audio management
     * @brief After the local user joins the room, call this API to update the orientation of the local user in the 3D coordinates for the spatial audio.  <br>
     * @param [in] orientation Your head orientation. Refer to HumanOrientation{@link #HumanOrientation} for more information. 
     * @return API call result:  <br>
     *        + 0: Success  <br>
     *        + !0: Failure
     * @notes  <br>
     *        +  Before calling this API, you should call enableSpatialAudio{@link #ISpatialAudio#enableSpatialAudio} first to enable spatial audio function, and then call UpdatePosition{@link #ISpatialAudio#updatePosition} to update the position of the local user.  <br>
     *        +  Call disableRemoteOrientation{@link #ISpatialAudio#disableRemoteOrientation} to neglect the orientation of the remote users. 
     */
    virtual int updateSelfOrientation(const HumanOrientation& orientation) = 0;

    /** 
     * @type api
     * @region Audio management
     * @brief Calling this API in each client to neglect the orientation of the remote speakers. From the local user's perspective, all the remote users will be facing him/her.<br>
     *        Once the orientation is disabled by calling this API, calling updateSelfOrientation{@link #ISpatialAudio#updateSelfOrientation} will notify none of the remote users. However, as a listener, the local user can experience the sound effect varies with the change of one's orientation. 
     * @notes <br>
     *        + You can call this API before or after the local user joins the room. <br>
     *        + Once the orientation is disabled by calling this API, you cannot enable it again within the lifetime of the `SpatialAudio` instance.
     */
    virtual void disableRemoteOrientation() = 0;

    /**  
     * @hidden
     * @brief  Destructor
     */
    virtual ~ISpatialAudio() = default;
};

}  // namespace bytertc
