/*
 *  Copyright (c) 2022 The ByteRtc project authors. All Rights Reserved.
 *  @company ByteDance.Inc
 *  @brief spatial audio interface
 */

#pragma once

#import <Foundation/Foundation.h>
#import "ByteRTCAudioDefines.h"

/** 
 * @type keytype
 * @brief  Direction Orientation Information
 */
BYTERTC_APPLE_EXPORT @interface Orientation : NSObject
/** 
 * @brief X  direction vector
 */
@property(nonatomic, assign) float x;
/** 
 * @brief Y  direction vector
 */
@property(nonatomic, assign) float y;
/** 
 * @brief Z  direction vector
 */
@property(nonatomic, assign) float z;
@end

/**  
 * @type keytype
 * @brief Three-dimensional orientation information, each pair of vectors need to be perpendicular. See Orientation{@link #Orientation}.
 */
BYTERTC_APPLE_EXPORT @interface HumanOrientation : NSObject
/**  
 * @brief Forward orientation, the default value is {1,0,0}, i.e., the forward orientation is in the positive direction of x-axis.
 */
@property(nonatomic, strong) Orientation* _Nonnull forward;
/**  
 * @brief Rightward orientation, the default value is {0,1,0}, i.e., the rightward orientation is in the positive direction of y-axis.
 */
@property(nonatomic, strong) Orientation* _Nonnull right;
/**  
 * @brief Upward orientation, the default value is {0,0,1}, i.e., the upward orientation is in the positive direction of z-axis.
 */
@property(nonatomic, strong) Orientation* _Nonnull up;
@end

/**  
 * @type api
 * @brief Spatial audio instance
 */
BYTERTC_APPLE_EXPORT @interface ByteRTCSpatialAudio :NSObject
/**  
 * @type api
 * @region Spatial Audio
 * @author majun.lvhiei
 * @brief Enable/disable spatial audio function.  <br>
 * @param enable Whether to enable spatial audio function:  <br>
 *        + true：Enable  <br>
 *        + false：Disable(Default setting)
 * @notes You need to call updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} as well to really enjoy the spatial audio effect.
 */
- (void)enableSpatialAudio:(BOOL)enable;
/**  
 * @type api
 * @region Spatial Audio
 * @author majun.lvhiei
 * @brief Updates the coordinate of the local user's position in the rectangular coordinate system in the current room.
 * @param pos 3D coordinate values, the default value is [0, 0, 0], see Position{@link #Position}.
 * @return API call result: <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @notes Before calling this API, you should call enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} first to enable spatial audio function.
 */
-(int)updatePosition:(Position* _Nonnull) pos;
/**  
 * @type api
 * @region Audio management
 * @author majun.lvhiei
 * @brief After the local user joins the room, call this API to update the orientation of the local user in the 3D coordinates for the spatial audio.  <br>
 * @param orientation Your head orientation. Refer to HumanOrientation{@link #HumanOrientation} for more information.  
 * @return API call result:  <br>
 *        + 0: Success  <br>
 *        + !0: Failure
 * @notes  <br>
 *        +  Before calling this API, you should call enableSpatialAudio:{@link #ByteRTCSpatialAudio#enableSpatialAudio:} first to enable spatial audio function, and then call updatePosition:{@link #ByteRTCSpatialAudio#updatePosition:} to update the position of the local user.  <br>
 *        +  Call disableRemoteOrientation{@link #ByteRTCSpatialAudio#disableRemoteOrientation} to neglect the orientation of the remote users. 
 */
-(int)updateSelfOrientation:(HumanOrientation* _Nonnull) orientation;

/** 
 * @type api
 * @region Audio management
 * @author luomingkang.264
 * @brief Calling this API in each client to neglect the orientation of the remote speakers. From the local user's perspective, all the remote users will be facing him/her.<br>
 *        Once the orientation is disabled by calling this API, calling updateSelfOrientation:{@link #ByteRTCSpatialAudio#updateSelfOrientation:} will notify none of the remote users. However, as a listener, the local user can experience the sound effect varies with the change of one's orientation. 
 * @notes <br>
 *        + You can call this API before or after the local user joins the room. <br>
 *        + Once the orientation is disabled by calling this API, you cannot enable it again within the lifetime of the `SpatialAudio` instance.
 */
-(void)disableRemoteOrientation;
@end
