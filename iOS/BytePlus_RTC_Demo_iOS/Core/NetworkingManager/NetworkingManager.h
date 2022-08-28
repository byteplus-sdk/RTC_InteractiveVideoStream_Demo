/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>
#import "NetworkingResponse.h"
#import "NetworkReachabilityManager.h"
#import "BaseUserModel.h"

NS_ASSUME_NONNULL_BEGIN

@interface NetworkingManager : NSObject

#pragma mark - Base

+ (void)postWithEventName:(NSString *)eventName
                  content:(NSDictionary *)content
                    block:(void (^ __nullable)(NetworkingResponse *response))block;

#pragma mark - User

/*
 * Change User Name
 * @param userName User Name
 * @param loginToken Login token
 * @param block Callback
 */
+ (void)changeUserName:(NSString *)userName
            loginToken:(NSString *)loginToken
                 block:(void (^ __nullable)(NetworkingResponse *response))block;

#pragma mark - RTM

/*
 * Join RTM
 * @param scenes Scenes name
 * @param loginToken Login token
 * @param block Callback
 */
+ (void)joinRTM:(NSString *)scenes
     loginToken:(NSString *)loginToken
          block:(void (^ __nullable)(NSString * _Nullable appID,
                                     NSString * _Nullable RTMToken,
                                     NSString * _Nullable serverUrl,
                                     NSString * _Nullable serverSig,
                                     NetworkingResponse *response))block;

@end

NS_ASSUME_NONNULL_END
