// 
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
// 

#import <Foundation/Foundation.h>

@class BytedEffectProtocol;

NS_ASSUME_NONNULL_BEGIN

/**
 * @type keytype
 * @brief Beauty type.
 */
typedef NS_ENUM(NSInteger, BytedEffectType) {
    /**
     * @brief Default beauty type.
     */
    BytedEffectTypeDefault = 0,
    /**
     * @brief Video call beauty type.
     */
    BytedEffectTypeVideoCall = 1,
};

@protocol BytedEffectDelegate <NSObject>

- (instancetype)protocol:(BytedEffectProtocol *)protocol
    initWithRTCEngineKit:(id)rtcEngineKit;

- (void)protocol:(BytedEffectProtocol *)protocol
    showWithView:(UIView *)superView
    dismissBlock:(void (^)(BOOL result))block;

- (void)protocol:(BytedEffectProtocol *)protocol
      showInView:(UIView *)superView
        animated:(BOOL)animated
    dismissBlock:(void (^)(BOOL result))block;

- (void)protocol:(BytedEffectProtocol *)protocol resume:(BOOL)result;

- (void)protocol:(BytedEffectProtocol *)protocol reset:(BOOL)result;

- (void)protocol:(BytedEffectProtocol *)protocol saveBeautyConfig:(BOOL)result;

@end

@interface BytedEffectProtocol : NSObject


/**
 * @brief Initialization
 * @param rtcEngineKit Rtc Engine
 */
- (instancetype)initWithRTCEngineKit:(id)rtcEngineKit;

/**
 * @brief Initialization
 * @param rtcEngineKit Rtc Engine
 * @param type Beauty type
 */
- (instancetype)initWithRTCEngineKit:(id)rtcEngineKit
                                type:(BytedEffectType)type;



/**
 * @brief Show effect beauty view
 * @param superView Super view
 * @param block Dismiss Callback
 */
- (void)showWithView:(UIView *)superView
        dismissBlock:(void (^)(BOOL result))block;

/**
 * @brief Show effect beauty view
 * @param superView Super view
 * @param animated Show animation or not
 * @param block Dismiss Callback
 */
- (void)showInView:(UIView *)superView
          animated:(BOOL)animated
      dismissBlock:(void (^)(BOOL result))block;

/**
 * @brief Resume the last selected beauty
 */
- (void)resume;

/**
 * @brief Reset the last selected beauty
 */
- (void)reset;

/**
 * @brief Save selected beauty
 */
- (void)saveBeautyConfig;

@end

NS_ASSUME_NONNULL_END
