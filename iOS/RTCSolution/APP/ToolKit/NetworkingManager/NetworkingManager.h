//
// Copyright (c) 2023 BytePlus Pte. Ltd.
// SPDX-License-Identifier: MIT
//

#import "BaseUserModel.h"
#import "NetworkReachabilityManager.h"
#import "NetworkingResponse.h"
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface NetworkingManager : NSObject

#pragma mark - Base

+ (void)postWithEventName:(NSString *)eventName
                    space:(NSString *)space
                  content:(NSDictionary *)content
                    block:(void (^__nullable)(NetworkingResponse *response))block;

#pragma mark - User

/*
 * Change User Name
 * @param userName User Name
 * @param loginToken Login token
 * @param block Callback
 */
+ (void)changeUserName:(NSString *)userName
            loginToken:(NSString *)loginToken
                 block:(void (^__nullable)(NetworkingResponse *response))block;

@end

NS_ASSUME_NONNULL_END
