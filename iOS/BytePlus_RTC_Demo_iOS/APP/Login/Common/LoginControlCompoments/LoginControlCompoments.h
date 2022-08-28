/*
 * Copyright 2022 BytePlus Pte. Ltd.
 * SPDX-License-Identifier: MIT
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface LoginControlCompoments : NSObject

// 免密登录
+ (void)passwordFreeLogin:(NSString *)userName
                    block:(void (^ __nullable)(BOOL result, NSString * _Nullable errorStr))block;

@end

NS_ASSUME_NONNULL_END
