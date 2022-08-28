/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface PublicParameterCompoments : NSObject

@property (nonatomic, copy) NSString *appId;

@property (nonatomic, copy) NSString *roomId;

+ (PublicParameterCompoments *)share;

+ (NSDictionary *)addTokenToParams:(NSDictionary * _Nullable)dic;

+ (void)clear;

@end

NS_ASSUME_NONNULL_END
